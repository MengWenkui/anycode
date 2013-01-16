#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <string.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define BUFFER_SIZE    1024
#define LISTEN_BACKLOG 1024
#define TIME_PER_TASK  200

int tcp_server(char *ip, int port) 
{
	int lfd = socket(AF_INET, SOCK_STREAM, 0);
	if(lfd < 0) {
		perror("socket");
		return -1;
	}

	int ret = 0;
	struct sockaddr_in addr;
	memset(&addr, 0, sizeof(struct sockaddr_in));
	addr.sin_family = AF_INET;
	if(0 == strcmp(ip, "*")) {
		addr.sin_addr.s_addr = htonl(INADDR_ANY);
	} else {
		addr.sin_addr.s_addr = inet_addr(ip);
	}
	addr.sin_port = htons(port);
	
	ret = bind(lfd, (struct sockaddr *)&addr, sizeof(addr));
	if(ret < 0) {
		perror("bind");
		return - 1;
	}

	ret = listen(lfd, LISTEN_BACKLOG);
	if(ret < 0) {
		perror("bind");
		return - 1;
	}

	return lfd;
}

void server_task(int cfd) 
{
	int buffer[BUFFER_SIZE];
	int rlen = 0;
	int wlen = 0;
	
	rlen = read(cfd, buffer, BUFFER_SIZE);
	buffer[rlen] = '\0';
	printf("%s\n", buffer);
	
	struct timespec ts;
	ts.tv_sec = TIME_PER_TASK / 1000;
	ts.tv_nsec = (TIME_PER_TASK % 1000) * 1000000;

	nanosleep(&ts, NULL);

	wlen = write(cfd, buffer, rlen);
	if(wlen != rlen) {
		perror("write");
	}

	close(cfd);
}

int main(int argc, char *argv[])
{
	if(3 != argc) {
		printf("./server ip port\n");
		return -1;
	}

	char *ip = argv[1];
	int port = atoi(argv[2]);

	int lfd = tcp_server(ip, port);
	if(lfd < 0) {
		perror("tcp server");
		return -1;
	}

	while(1) {
		int cfd = accept(lfd, NULL, NULL);
		server_task(cfd);
	}

	close(lfd);

	return 0;
}
