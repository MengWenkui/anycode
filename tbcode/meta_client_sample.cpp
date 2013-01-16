#include <stdio.h>
#include <stdlib.h>

#include "tfs_rc_client_api.h"
#include "tfs_meta_client_api.h"

using namespace tfs::client;
using namespace tfs::common;

int main()
{
  // const char* rc_ip = "10.232.36.203:6100";
  const char* ns_ip = "10.232.36.201:12340";
  const char* rc_ip = "10.232.36.203:3500";
  const char* app_key = "tfscom";
  const char* app_ip = "10.232.1.5";
  int cache_times = 5;
  int cache_items = 100;
  char buff[100] = {"hello wrold, this is for testing rc client!"};
  char tfs_name[TFS_FILE_LEN];

  NameMetaClient meta_client;
  int ret = meta_client.initialize(rc_ip);
  //meta_client.set_log_level("info");
  printf("----------------------------------------init %d\n", ret);


  // create dir
  ret = meta_client.create_dir(1, 20120201, "/");
  if(ret == TFS_SUCCESS)
  {
	 printf("create dir ok!\n");
  }


  // save file
  meta_client.save_file(ns_ip, 20120201, 1, "Makefile", "/test1");
  if(ret == TFS_SUCCESS)
  {
	  printf("save file ok!\n");
  }

  // fetch file
  meta_client.fetch_file(ns_ip, 20120201, 1, "test1", "/test1");
  if(ret == TFS_SUCCESS)
  {
	  printf("fetch file ok!\n");
  }


  return 0;
}
