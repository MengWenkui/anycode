#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <time.h>
#include <stdlib.h>

#define targetdisk "D:"
#define targetfile "F:\\Fedora-11\\NewHardDisk1.vdi"

int my_read(char *filename, int flag, unsigned size)
{
    int fd = open(filename, flag);
    if(fd < 0) {
        perror("open");
    }

    char *buf = (char*)malloc(size * sizeof(char));

    unsigned int start, end;
    start = clock();
    int ret = read(fd, buf, size);
    if(ret != size) {
        perror("read");
    }
    end = clock();

    printf("consume time: %d\n", end - start);

	free(buf);
    close(fd);

    return 0;
}

int main(int argc, char *argv[])
{
    unsigned int read_size = 10000000;
    my_read(targetdisk, O_RDONLY, read_size);
    my_read(targetfile, O_RDONLY, read_size);
 	return 0;
}

