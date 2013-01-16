#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/poll.h>
#include <sys/select.h>
#include <sys/signal.h>
#include <sys/epoll.h>


int got_alarm;

void alarm_handle(int sig)
{
    got_alarm = 1;
}

#define HIGH_FD 1000
#define MAX_EVENTS 10

int main()
{
    int zerofd;
    int count;
    fd_set fds;
    struct pollfd pollfds;

    zerofd = open("/dev/zero", O_RDONLY);
    dup2(zerofd, HIGH_FD);

    signal(SIGALRM, alarm_handle);

    /* test for select syscall */
    count = 0;
    got_alarm = 0;
    alarm(1);
    while(!got_alarm) {
        FD_ZERO(&fds);
        FD_SET(HIGH_FD, &fds);

        select(HIGH_FD + 1, &fds, NULL, NULL, NULL);
        count++;
    }

    printf("select() calls %d times per second\n", count);

   /* test for select syscall */
    pollfds.fd = HIGH_FD;
    pollfds.events = POLLIN;
    count = 0;
    got_alarm = 0;
    alarm(1);
    while(!got_alarm) {
        poll(&pollfds, 1, -1);
        count++;
    }

    printf("poll() calls %d times per second\n", count);

    /* test for epoll syscall */

    struct epoll_event ev;
    struct epoll_event event[MAX_EVENTS];

    int epfd = epoll_create(MAX_EVENTS);

    ev.events = EPOLLIN;
    ev.data.fd = HIGH_FD;

    if (epoll_ctl(epfd, EPOLL_CTL_ADD, HIGH_FD, &ev) < 0) {
        perror("epoll_ctl");
        return -1;
    }

    count = 0;
    got_alarm = 0;
    alarm(1);
    while(!got_alarm) {
        epoll_wait(epfd, event, MAX_EVENTS, -1);
        count++;
    }

    printf("epoll_wait() calls %d times per second\n", count);

    return 0;
}
