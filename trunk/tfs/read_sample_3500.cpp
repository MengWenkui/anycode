
#include <stdio.h>
#include <string>
#include "tfs_client_api.h"
#include <vector>
#include <algorithm>

using namespace std;
using namespace tfs::client;
using namespace tfs::common;

// read whole file
const int buf_size = 2 * 1024 * 1024;

int load_file_list(const char* filename, vector<string>& file_list)
{
  int ret = 0;
  FILE* fp = fopen(filename, "r");
  if (NULL == fp)
  {
    fprintf(stderr, "fopen fail");
    ret = -1;
  }
  else
  {
    char line[256];
    while (fgets(line, 256, fp) != NULL)
    {
      int pos = strlen(line);
      while (line[pos-1] == '\n') pos--;
      line[pos] = '\0';
      file_list.push_back(line);
    }
    fclose(fp);
  }
  return ret;
}

int random_read_file(const char* nsip, vector<string>& file_list, int count)
{
  int ret = 0;
  char buf[buf_size];
  srand((unsigned)time(NULL));
  TfsClient* tfsclient = TfsClient::Instance();
  ret = tfsclient->initialize(nsip);
  if (0 != ret)
  {
    fprintf(stderr, "tfs client init error");
  }
  else
  {
    // random_shuffle(file_list.begin(), file_list.end());
    for(int i = 0; i < count; i++)
    {
      int to_read = rand() % file_list.size();
      int fd = tfsclient->open(file_list[to_read].c_str(), NULL, NULL, T_READ);
      if (fd < 0)
      {
        fprintf(stderr, "open tfs file error, ret: %d\n", fd);
      }
      else
      {
        tfsclient->read(fd, buf, buf_size);
        tfsclient->close(fd);
        printf("%s\n", file_list[to_read].c_str());
      }
    }
  }
  return ret;
}

void usage(int argc, char **argv)
{
  fprintf(stderr, "usage:\n%s ns_ip file_list [file_count]\n", argv[0]);
  exit(-1);
}

int main(int argc, char **argv)
{
  if (argc < 3)
  {
    usage(argc, argv);
  }
  vector<string> file_list;
  if (0 == load_file_list(argv[2], file_list))
  {
    int count = 0;
    if (argc == 4)
    {
      count = atoi(argv[3]);
    }
    else
    {
      count = file_list.size();
    }
    return random_read_file(argv[1], file_list, count);
  }
  return 0;
}
