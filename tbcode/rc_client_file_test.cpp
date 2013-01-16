#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "tfs_rc_client_api.h"
#include "tfs_meta_client_api.h"

using namespace tfs::client;
using namespace tfs::common;

int main()
{
  const char* rc_ip = "10.232.36.203:6100";
  const char* ns_ip = "10.232.36.201:12340";
  const char* app_key = "tfscom";
  const char* app_ip = "10.232.1.5";
  int cache_times = 5;
  int cache_items = 100;
  char buff[100] = {"hello wrold, this is for testing rc client!"};
  char tfs_name[TFS_FILE_LEN];

	RcClient rc_client;
	int ret = rc_client.initialize(rc_ip, app_key, app_ip, cache_times, cache_items);
  if(ret == TFS_SUCCESS)
  {
	 	printf("init ok!\n");
  }

	int64_t saved_size = 0;
	int64_t fetched_size = 0;

	saved_size = rc_client.save_buf(1, 20120217, "hello world, this is a small file test", 40, "/hello/world/2100");
  assert(40 == saved_size);

	fetched_size = rc_client.fetch_file(1, 20120217, "testfile2", "/hello/world/2100");
	assert(40 == fetched_size);

	saved_size = rc_client.save_buf(1, 20120206, "hello world, this is a small file test", 40, "hello/world/12");
	assert(saved_size < 0);

	saved_size = rc_client.save_file(1, 20120217, "Makefile", "/hello/world/2200");
	// assert(696 == saved_size);

	fetched_size = rc_client.fetch_file(1, 20120217, "Makefile", "/hello/world/2200");
	// assert(696 == fetched_size);

  return 0;
}
