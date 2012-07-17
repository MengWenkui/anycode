#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "jerasure.h"

#define talloc(type, num) (type *) malloc(sizeof(type)*(num))

int read_file(const char* prefix, int idx, char* buf, int size)
{
  char filename[256];
  sprintf(filename, "%s_0%d", prefix, idx);

  FILE* fp = fopen(filename, "r");
  if (NULL == fp)
  {
    printf("read %s fail\n", filename);
    return -1;
  }

  fread(buf, sizeof(char), size, fp);
  fclose(fp);
  return 0;
}

int write_file(const char* prefix, int idx , char* buf, int size)
{
  char filename[256];
  sprintf(filename, "%s_0%d", prefix, idx);
  FILE* fp = fopen(filename, "w+");
  if (NULL == fp)
  {
    printf("write %s fail\n", filename);
    return -1;
  }
  fwrite(buf, sizeof(char), size, fp);
  fclose(fp);
}

int main(int argc, char **argv)
{
  long l;
  int k, m, w, size;
  int i, j;
  int *matrix;
  char **data, **coding;
  int *erasures, *erased;
  int *decoding_matrix, *dm_ids;

  k = 5;
  m = 2;
  w = 8;
  size = 1048576;

  // generate matrix
  matrix = talloc(int, m*k);
  for (i = 0; i < m; i++) {
    for (j = 0; j < k; j++) {
      matrix[i*k+j] = galois_single_divide(1, i ^ (m + j), w);
    }
  }

  // prepare data
  data = talloc(char *, k);
  for (i = 0; i < k; i++) {
    data[i] = talloc(char, size);
    read_file("data", i, data[i], size);
  }

  // prepare coding
  coding = talloc(char *, m);
  for (i = 0; i < m; i++) {
    coding[i] = talloc(char, size);
  }

  // do encode data
  jerasure_matrix_encode(k, m, w, matrix, data, coding, size);

  for (i = 0; i < m; i++)
  {
    write_file("code", i, coding[i], size);
  }

  // erase first two data
  erasures = talloc(int, (m+1));
  erasures[0] = 0;  bzero(data[0], size);
  erasures[1] = 1;  bzero(data[1], size);
  erasures[2] = -1;

  i = jerasure_matrix_decode(k, m, w, matrix, 0, erasures, data, coding, size);

  // write recovery data to file
  write_file("reco", 0, data[0], size);
  write_file("reco", 1, data[1], size);

  // specific recovery, just recovery the first data
  decoding_matrix = talloc(int, k*k);
  dm_ids = talloc(int, k);
  erased = talloc(int, m+k);

  for (i = 0; i < m + k; i++) erased[i] = 0;
  erased[0] = 1;  bzero(data[0], size);
  erased[1] = 1;  bzero(data[1], size);

  jerasure_make_decoding_matrix(k, m, w, matrix, erased, decoding_matrix, dm_ids);

  jerasure_matrix_dotprod(k, w, decoding_matrix, dm_ids, 0, data, coding, size);

  // write recovery data to file
  write_file("dotp", 0, data[0], size);
  write_file("dotp", 1, data[1], size);

  // re-read data
  for (i = 0; i < k; i++) {
    data[i] = talloc(char, size);
    read_file("data", i, data[i], size);
  }

  // bitmatrix
  int* bitmatrix;
  bitmatrix = jerasure_matrix_to_bitmatrix(k, m, w, matrix);

  // bitmatrix encode
  struct timeval start, end;
  int encode_time = 0;
  int decode_time = 0;
  int psize = 8;
  if (argc == 2)
  {
    psize = atoi(argv[1]);
  }
  gettimeofday(&start, NULL);
  jerasure_bitmatrix_encode(k, m, w, bitmatrix, data, coding, size, psize);
  gettimeofday(&end, NULL);
  encode_time = (end.tv_sec - start.tv_sec) * 1000000 +
      (end.tv_usec - start.tv_usec);
  for (i = 0; i < m; i++)
  {
    write_file("bcode", i, coding[i], size);
  }

  erasures[0] = 0;  bzero(data[0], size);
  erasures[1] = 1;  bzero(data[1], size);
  erasures[2] = -1;

  gettimeofday(&start, NULL);
  i = jerasure_bitmatrix_decode(k, m, w, bitmatrix, 0, erasures, data, coding,
		  size, psize);
  gettimeofday(&end, NULL);
  decode_time = (end.tv_sec - start.tv_sec) * 1000000 +
      (end.tv_usec - start.tv_usec);

   // write recovery data to file
  write_file("breco", 0, data[0], size);
  write_file("breco", 1, data[1], size);

  printf("(%d %d %d %d %d)\t%d\t%d\n", k, m, w, size, psize, encode_time, decode_time);

  return 0;
}
