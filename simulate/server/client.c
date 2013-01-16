#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <string.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <time.h>
#include <sys/time.h>
#include <pthread.h>


#define BUFFER_SIZE    1024
#define MAX_SERVER_NUM 100
#define MAX_CLIENT_NUM 100
#define MAX_ADDR_LEN   20

typedef struct server_info {
	char ip[MAX_ADDR_LEN];
	int port;
} server_info;

int server_num = 3;
server_info server_list[MAX_CLIENT_NUM] = {
	{"127.0.0.1", 12340},
	{"127.0.0.1", 12341},
	{"127.0.0.1", 12342}
};

uint64_t request_count = 0;
uint64_t process_time = 0; // ms

void *thread_task(void *data)
{
	int request_num = *(int*)data;
	int ret = 0;
	int idx = 0;

	srand((unsigned)time(NULL));
	for(int i = 0; i < request_num; i++) {
		int cfd = socket(AF_INET, SOCK_STREAM, 0);
		if(cfd < 0) {
			perror("socket");
			exit(-1);
		}

		// randomly choose a server
		idx = rand() % server_num;

		struct sockaddr_in addr;
		memset(&addr, 0, sizeof(struct sockaddr_in));
		addr.sin_family = AF_INET;
		addr.sin_addr.s_addr = inet_addr(server_list[idx].ip);
		addr.sin_port = htons(server_list[idx].port);
		
		ret = connect(cfd, (struct sockaddr *)&addr, sizeof(addr));
		if(ret < 0) {
			perror("connect");
			exit(-1);
		}

		int rlen = 0;
		int wlen = 0;
		char buffer[BUFFER_SIZE] = "hello world";
		struct timeval start;
		struct timeval end;

		wlen = write(cfd, buffer, 11);

		gettimeofday(&start, NULL);
		rlen = read(cfd, buffer, BUFFER_SIZE);
		gettimeofday(&end, NULL);
		
		request_count += 1;
		process_time += (end.tv_sec - start.tv_sec) * 1000000 + 
			(end.tv_usec - start.tv_usec);
		
		close(cfd);
	}
}


int main(int argc, char *argv[]) 
{
	if(3 != argc) {
		printf("./client thread_num request_num\n");
		return -1;
	}

	int thread_num = atoi(argv[1]);
	int request_num = atoi(argv[2]);
	pthread_t pid[MAX_CLIENT_NUM];
	int ret = 0;

	for(int i =  0; i < thread_num; i++) {
		ret = pthread_create(&pid[i], NULL, thread_task, (void *)(&request_num));
		if(ret < 0) {
			perror("pthread_create");
			return -1;
		}
	}

	for(int i = 0; i < thread_num; i++) {
		pthread_join(pid[i], NULL);
	}

	printf("average process time: %d ms\n", process_time / request_count / 1000);

	return 0;
}
