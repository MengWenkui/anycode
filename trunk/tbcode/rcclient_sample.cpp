#include <stdio.h>
#include <stdlib.h>

#include "tfs_rc_client_api.h"

using namespace tfs::client;
using namespace tfs::common;

int main()
{
  const char* rc_ip = "10.232.36.203:6100";
  const char* app_key = "tfscom";
  const char* app_ip = "10.232.1.5";
  int cache_times = 5;
  int cache_items = 100;
  char buff[100] = {"hello wrold, this is for testing rc client!"};
  char tfs_name[TFS_FILE_LEN];

  tfs::client::RcClient rc_client;
  int64_t ret = rc_client.initialize(rc_ip, app_key, app_ip, cache_times, cache_items);
  rc_client.set_log_level("info");
  printf("----------------------------------------init %d\n", ret);
  for (int i = 0; i < 50; i++)
  {
    buff[i] = i;
  }
  int tfs_fd = 0;
  ret = 0;
  tfs_fd = rc_client.open(NULL, NULL, RcClient::READ);
  // tfs_fd = rc_client.open("L2xaETByxT1RCvBVdK", NULL, tfs::client::RcClient::READ);
  if (tfs_fd <= 0)
  {
    printf("open error %d", tfs_fd);
  }
  else
  {
    rc_client.write(tfs_fd, buff, 50);
    ret = rc_client.read(tfs_fd, buff, 10);
    printf("ret = %ld\n", ret);
    ret = rc_client.read(tfs_fd, buff+10, 40);
    printf("ret = %ld\n", ret);
    for (int i = 0; i < 50; i++)
    {
      printf("%d %d|", buff[i] , i);
    }

	printf("\n");
  }
  ret = rc_client.close(tfs_fd, tfs_name, 20);
  printf("-------------tfs name is %s\n", tfs_name);
  return 0;
}
