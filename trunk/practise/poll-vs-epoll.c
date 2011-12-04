#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/poll.h>
#include <sys/epoll.h>
#include <sys/signal.h>
#include <unistd.h>
#include <sys/resource.h>
#include <string.h>
#include <stdlib.h>

int got_alarm;

void alarm_handle(int sig)
{
	got_alarm = 1;
}

#define OFFSET 10

int main(int argc, char *argv[])
{
	int pfd[2];
	int count;
	int numfds;
	struct pollfd *pollfds;
	struct epoll_event *events;
	struct epoll_event ev;
	
	int epfd;
	int i;
	struct rlimit lim;
	
	if(argc != 2) {
		fprintf(stderr, "number expected\n");
		return -1;
	}
	
	numfds = atoi(argv[1]);
	
	/* 解除打开文件数限制 */
	lim.rlim_cur = numfds + OFFSET;
	lim.rlim_max = numfds + OFFSET;
	if(setrlimit(RLIMIT_NOFILE, &lim)) {
		perror("setrlimit");
		return -1;
	}
	
	// 创建管道
	pipe(pfd);
	
	pollfds = (struct pollfd *)malloc(sizeof(struct pollfd) * numfds);
	events = (struct epoll_event *)malloc(sizeof(struct epoll_event) * numfds);
	epfd = epoll_create(numfds);
	ev.events = EPOLLIN;
	
	for(i = OFFSET; i < OFFSET + numfds; i++) {
		if(dup2(pfd[0], i) != i) {
			perror("dup2");
			return -1;
		}
		
		pollfds[i - OFFSET].fd = i;
		pollfds[i - OFFSET].events = POLLIN;
		
		ev.data.fd = i;
		epoll_ctl(epfd, EPOLL_CTL_ADD, i, &ev);
	}
	
	signal(SIGALRM, alarm_handle);
	
	count = 0; 
	got_alarm = 0;
	alarm(1);
	while(!got_alarm) {
		poll(pollfds, numfds, 0);
		count++;
	}
	printf("poll() calls %d times per second\n", count);
	
	count = 0; 
	got_alarm = 0;
	alarm(1);
	while(!got_alarm) {
		epoll_wait(epfd, events, numfds, 0);
		count++;
	}
	printf("epoll_wait() calls %d times per second\n", count);
	
	
	free(events);
	free(pollfds);
	
	return 0;
	
}