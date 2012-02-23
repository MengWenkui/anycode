#include <stdio.h>
#include <string>
#include "tfs_client_api.h"

using namespace std;
using namespace tfs::client;
using namespace tfs::common;

const int buf_size = 2 * 1024 * 1024;

int random_write_file(const char* nsip, int size, int count)
{
  int ret = 0;
  TfsClient* tfsclient = TfsClient::Instance();
  ret = tfsclient->initialize(nsip);
  if (0 != ret)
  {
    fprintf(stderr, "tfs client init error");
  }
  else
  {
    char buf[buf_size];
    char tfs_file_name[TFS_FILE_LEN];
    for (int i = 0; i < count; i++)
    {
      int fd = tfsclient->open(NULL, NULL, NULL, T_WRITE);
      if (fd < 0)
      {
        fprintf(stderr, "open tfs file fail, ret: %d\n", fd);
      }
      else
      {
        tfsclient->write(fd, buf, size);
        tfsclient->close(fd, tfs_file_name, TFS_FILE_LEN);
        printf("%s\n", tfs_file_name);
      }
    }
  }
  return ret;
}

void usage(int argc, char **argv)
{
  fprintf(stderr, "usage:\n%s ns_ip(ip:port) file_size(kb) file_count\n", argv[0]);
  exit(-1);
}

int main(int argc, char **argv)
{
  if (4 != argc)
  {
    usage(argc, argv);
  }
  return random_write_file(argv[1], atoi(argv[2]) * 1024, atoi(argv[3]));
}
