/*
 * Linux文件系统下一切都是文件
 * 可以像使用普通文件一样使用设备
 * 文件系统在设备之上组织文件
 * 可直接操作设备扇区内容（如dd命令)
 * 这种方式不经过文件系统
 */
 

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <libgen.h>
#include <unistd.h>

static void usage(char *prog_name)
{
	fprintf(stderr, "usage: %s device start count\n", prog_name);
	fprintf(stderr, "example: %s /dev/sda 0 512\n", prog_name);
}

int main(int argc, char *argv[])
{
	char buf[4096];
	int fd = 0;
	int i = 0;
	int j = 0;
	int start = 0;
	int count = 0;
	char *device = NULL;

	if(argc != 4){
		usage(basename(argv[0]));
		exit(1);
	}
	
	device = argv[1];
	start = atol(argv[2]);
	count = atol(argv[3]);

	fd = open(device, O_RDONLY);
	if(-1 == fd){
		fprintf(stderr, "cannot open /dev/hda");
		exit(1);
	}	
	
	if(lseek(fd, start, SEEK_SET) != start){
		fprintf(stderr, "cannot seek at %d", start);
		exit(1);
	}
	
	while(count > 0){
		int size = count > sizeof(buf) ? sizeof(buf) : count;

		read(fd, buf, size);
		
		/* 每行显示16个字节 每两个字节间以空格分开 */
		for(i = 0; i < size/16; i++){
			fprintf(stdout,"%08x:", i*16+start);
			for(j = 0; j < 16; j++){
				fprintf(stdout, " %02x", (int)buf[i*16+j] & 0xFF);	
			}
			fprintf(stdout,"\n");
			fflush(stdout);
		}
		count -= size;
		start += size;
	}
	
	close(fd);
	return 0;
}


