#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#include "common.h"
#include "cclient.h"

CClient::CClient()
{
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
}

int CClient::connect(char *ip, int port)
{
	int err = -1;
	sockaddr_in sa;
	bzero(&sa, sizeof(struct sockaddr_in));
	
	sa.sin_family = AF_INET;
	inet_pton(AF_INET, ip, &sa.sin_addr);
	sa.sin_port = htons(port);
	
	while(err < 0) {
		err = ::connect(sockfd, (struct sockaddr*)&sa, sizeof(sa));
	}
	
	return 0;
}

void CClient::request()
{
	char rqst[] = "hello world";
	char buf[BUF_SIZE];
	int r;
	
	write(sockfd, rqst, strlen(rqst));
	
	r = read(sockfd, buf, BUF_SIZE - 1);
	buf[r] = '\0';
	printf("response: %s\n", buf);
}

CClient::~CClient()
{
	close(sockfd);
}


