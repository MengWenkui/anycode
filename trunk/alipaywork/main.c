#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>

#include "common.h"
#include "cserver.h"
#include "cclient.h"

void* client_func(void* arg)
{
	printf("client thread begin\n");
	
	CClient *client = new CClient();
	client->connect((char*)"127.0.0.1", 12888);
	client->request();
	delete client;
	
	printf("client thread end\n");
	
	return (void*)0;
}

void* server_func(void* arg)
{
	printf("server thread begin\n");
	
	int client;
	CServer *server = new CServer(12888);
	client = server->accept();
	server->process(client);
	delete server;
	
	printf("server thread end\n");
	
	return (void*)0;
}

int main()
{
	pthread_t ctid, stid;
	int err;
	
	err = pthread_create(&ctid, NULL, client_func, NULL);
	if(err < 0) {
		printf("create thread error\n");
		return -1;
	}
	
	 /*
	  * 启动客户端线程2s后再启动服务器线程
	  * 测试客户端是否能争取等待服务器启动
	  */
	  
	sleep(2);  
	
	err = pthread_create(&stid, NULL, server_func, NULL);
	if(err < 0) {
		printf("create thread error\n");
		return -1;
	}
	
	pthread_join(ctid, NULL);
	pthread_join(stid, NULL);
	
	return 0;
}