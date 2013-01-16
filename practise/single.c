#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <printf.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>

#define LOCKFILE "/var/run/mydaemon.pid"
#define LOCKMODE (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)

/* set advisory lock on file */
int lockfile(int fd)
{
        struct flock fl;

        fl.l_type = F_WRLCK;  /* write lock */
        fl.l_start = 0;
        fl.l_whence = SEEK_SET;
        fl.l_len = 0;  //lock the whole file

        return(fcntl(fd, F_SETLK, &fl));
}

int already_running(const char *filename)
{
        int fd;
        char buf[16];

        fd = open(filename, O_RDWR | O_CREAT, LOCKMODE);
        if (fd < 0) {
                printf(LOG_ERR, "can't open %s: %m\n", filename);
                exit(1);
        }

        /* �Ȼ�ȡ�ļ��� */
        if (lockfile(fd) == -1) {
                if (errno == EACCES || errno == EAGAIN) {
                        printf(LOG_ERR, "file: %s already locked", filename);
                        close(fd);
                        return 1;
                }
                printf(LOG_ERR, "can't lock %s: %m\n", filename);
                exit(1);
        }

        /* д������ʵ����pid */
        ftruncate(fd, 0);
        sprintf(buf, "%ld", (long)getpid());
        write(fd, buf, strlen(buf) + 1);
        return 0;
}

int main(int argc, char *argv[])
{
        if (already_running(LOCKFILE))
                return 0;

        /* ��������ӹ������� */
        printf("start main...\n");
        sleep(100);
        printf("main done!\n");

        exit(0);
}
