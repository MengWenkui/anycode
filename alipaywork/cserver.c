#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#include "common.h"
#include "cserver.h"

CServer::CServer(int port) 
{
	struct sockaddr_in sa;
		
	listenfd = socket(AF_INET, SOCK_STREAM, 0);
		
	bzero(&sa, sizeof(sa));
	sa.sin_family = AF_INET;
	sa.sin_addr.s_addr = htonl(INADDR_ANY);
	sa.sin_port = htons(port);
		
	bind(listenfd, (struct sockaddr*)&sa, sizeof(sa));
	listen(listenfd, LISTEN_QUEUE);
}

int CServer::accept()
{
	return ::accept(listenfd, NULL, NULL);
}

void CServer::process(int fd)
{
	char buf[BUF_SIZE];
	int r;
	
	r = read(fd, buf, BUF_SIZE - 1);
	buf[r] = '\0';
	printf("request: %s\n", buf);
	
	char rsps[] = "good boy";
	write(fd, rsps, strlen(rsps));
}

CServer::~CServer()
{
	close(listenfd);
}


