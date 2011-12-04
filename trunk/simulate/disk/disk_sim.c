#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>
#include <stdint.h>
#include <malloc.h>

#define BLOCK_SIZE 4096

void do_read(int fd, int max, int count, int times) 
{
    srand((unsigned)time(NULL));
    char *buf = (char*)memalign((size_t)BLOCK_SIZE, (size_t)BLOCK_SIZE);
    if(NULL == buf) {
        printf("memalign error\n");
        return;
    }
    for(int i = 0; i < times; i++) {
        int seek = rand() % max; 
        lseek(fd, seek * BLOCK_SIZE, SEEK_SET);
        read(fd, buf, count * BLOCK_SIZE);
    }
    free(buf);
}

int main(int argc, char *argv[])
{
    if(argc != 4) {
        printf("./disk_sim file count times\n");
        return -1;
    }

    char *file_to_read = argv[1];
    int count = atoi(argv[2]);
    int times = 1;

    if(4 == argc) {
        times = atoi(argv[3]);
    }

    int fd = open(file_to_read, O_RDONLY | O_DIRECT);
    if(fd < 0) {
        printf("open error\n");
        return -1;
    }

    uint64_t file_size = lseek(fd, 0, SEEK_END);
    do_read(fd, file_size / BLOCK_SIZE, count, times);
    
    close(fd);

    return 0;
}
