#include <stdio.h>
#include <string>
#include "func.h"
#include "tfs_client_api.h"

using namespace std;
using namespace tfs::client;
using namespace tfs::common;

const char* tfs_file_name = "T1nRETByJT1RCvBVdK";
const char* nsip = "10.232.36.201:12340";

void read_file()
{
  int ret = 0;
  int fd = -1;
  TfsClient* tfsclient = TfsClient::Instance();
  tfsclient->initialize(nsip);
  // 打开待读写的文件
  fd = tfsclient->open(tfs_file_name, NULL, T_READ);
  if (ret != TFS_SUCCESS)
  {
    printf("open remote file %s error", tfs_file_name);
    return ;
  }

  // 获得文件属性
  TfsFileStat fstat;
  ret = tfsclient->fstat(fd, &fstat);
  if (ret != TFS_SUCCESS || fstat.size_ <= 0)
  {
    printf("get remote file info error");
    return ;
  }

  char* buffer = new char[fstat.size_];
  int read = 0;
  uint32_t crc = 0;
    
  // 读取文件
  while (read < fstat.size_)
  {
    ret = tfsclient->read(fd, buffer + read, fstat.size_ - read);
    if (ret < 0)
    {
      break;
    }
    else
    {
      crc = Func::crc(crc, buffer + read, ret); // 对读取的文件计算crc值
      read += ret;
    }
  }


  if (ret < 0 || crc != fstat.crc_)
  {
    printf("read remote file error!\n");
    delete []buffer;
    return ;
  }

  ret = tfsclient->close(fd);
  if (ret < 0)
  {
    printf("close remote file error!\n");
    delete []buffer;
    return ;
  }

  printf("read file success!\n");
  buffer[fstat.size_] = '\0';
  printf("%s\n", buffer);
  delete []buffer;
  return ;
}

int main(int argc, char **argv)
{
  read_file();
  return 0;
}
