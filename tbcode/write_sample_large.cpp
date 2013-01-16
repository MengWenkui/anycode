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
  char buffer[2048000] = "hello world! this is a small file!";
  char tfs_file_name[TFS_FILE_LEN];

  // 创建tfs客户端，并打开一个新的文件准备写入	
  TfsClient* tfsclient = TfsClient::Instance();
  ret = tfsclient->initialize(nsip);
  if (ret != TFS_SUCCESS)
  {
    printf("init tfs client fail");
    return ;
  }

  fd = tfsclient->open((char*)NULL, NULL, NULL, T_WRITE | T_LARGE, "local");
  if (fd <= 0)
  {
    printf("create remote file error!");
    return ;
  }
	
  int wrote = 0;
  int left = 2000000;
  while (left > 0)
  {
    // 将buffer中的数据写入tfs
    ret = tfsclient->write(fd, buffer + wrote, left);
    if (ret < 0 || ret >= left)  // 读写失败或完成
    {
      break;
    }
    else // 若ret>0，则ret为实际写入的数据量
    {
      wrote += ret;
      left -= ret;
    }
  }

  // 读写失败	
  if (ret < 0)
  {
    printf("write data error!");
    return ;
  }

  // 提交写入	
  ret = tfsclient->close(fd, tfs_file_name, TFS_FILE_LEN);
	
  if (ret != TFS_SUCCESS) // 提交失败
  {
    printf("write remote file failed! ret: %s", ret);
  }
  else
  {
    printf("write remote file: %s successful!", tfs_file_name);
  }
		
}

int main(int argc, char **argv)
{
	write_file();
	return 0;
}
