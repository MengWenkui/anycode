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

  // ����tfs�ͻ��ˣ�����һ���µ��ļ�׼��д��	
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
    // ��buffer�е�����д��tfs
    ret = tfsclient->write(fd, buffer + wrote, left);
    if (ret < 0 || ret >= left)  // ��дʧ�ܻ����
    {
      break;
    }
    else // ��ret>0����retΪʵ��д���������
    {
      wrote += ret;
      left -= ret;
    }
  }

  // ��дʧ��	
  if (ret < 0)
  {
    printf("write data error!");
    return ;
  }

  // �ύд��	
  ret = tfsclient->close(fd, tfs_file_name, TFS_FILE_LEN);
	
  if (ret != TFS_SUCCESS) // �ύʧ��
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
