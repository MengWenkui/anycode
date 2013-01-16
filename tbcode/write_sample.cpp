#include <stdio.h>
#include <string>
#include "tfs_client_api.h"

using namespace std;
using namespace tfs::client;
using namespace tfs::common;

const int length = 256;
const char* nsip = "10.232.36.201:12340";

void write_file()
{
  int ret = 0;
  int fd = -1;
  char buffer[length] = "aaaaaaaaaaaaaaaaaaa";
  char buffer2[length] = "bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb";
  char tfs_file_name[TFS_FILE_LEN];

  // init
  TfsClient* tfsclient = TfsClient::Instance();
  ret = tfsclient->initialize(nsip);

  // write a file
  fd = tfsclient->open(NULL, NULL, NULL, T_WRITE);
  tfsclient->write(fd, buffer, strlen(buffer));
  tfsclient->close(fd, tfs_file_name, TFS_FILE_LEN);
  printf("%s\n", tfs_file_name);

  // read it
  char result[100] = {0};
  fd = tfsclient->open(tfs_file_name, NULL, NULL, T_READ);
  int len = tfsclient->read(fd, result, 100);
  result[len] = '\0';
  printf("%s\n", result);
  tfsclient->close(fd);

  // update it
  fd = tfsclient->open(tfs_file_name, NULL, NULL, T_WRITE);
  ret = tfsclient->lseek(fd, 10 , SEEK_SET);
  printf("ret  = %d\n", ret);
  len = tfsclient->write(fd, buffer2 + 10, strlen(buffer2) - 10);
  ret = tfsclient->close(fd, tfs_file_name, TFS_FILE_LEN);
  printf("ret: %d\n", ret);

  printf("update: %d\n", len);
  printf("%s\n", tfs_file_name);

  // read it again
  char result2[100] = {0};
  fd = tfsclient->open(tfs_file_name, NULL, NULL, T_READ);
  len = tfsclient->read(fd, result2, 100);
  result2[len] = '\0';
  printf("%s\n", result2);
  tfsclient->close(fd);

}

int main(int argc, char **argv)
{
	write_file();
	return 0;
}
