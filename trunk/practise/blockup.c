#include <signal.h>
#include <setjmp.h>
#include <stdio.h>
#include <unistd.h>

#define MAXLINE 128

static jmp_buf env_alrm;

static void sig_alrm(int signo) 
{
//	longjmp(env_alrm, 1);
	return ;
}

int main()
{
	int n;
	char line[MAXLINE];

	if (signal(SIGALRM, sig_alrm) == SIG_ERR) 
		printf("signal error\n");
//	if(setjmp(env_alrm) != 0) 
//		return -1;
	alarm(10);
	if ((n = read(STDIN_FILENO, line, MAXLINE)) < 0) 
		printf("read error\n");
	alarm(0);
//	write(STDOUT_FILENO, line, n);
	printf("hello\n");
	return 0;
}
