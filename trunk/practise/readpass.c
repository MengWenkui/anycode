#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <shadow.h>
#include <string.h>

#define AUTH_SIZE 1024

int main(int argc, char* argv[])
{
	struct termios ts, ots;
	char userbuf[AUTH_SIZE];
	char passbuf[AUTH_SIZE];

	tcgetattr(STDIN_FILENO, &ts);
	ots = ts;

	printf("Login:");
	fflush(stdout);
	gets(userbuf);

    /* �����ն˻��� */
	ts.c_lflag &= ~ECHO;
	ts.c_lflag |= ECHONL;
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &ts);

	printf("Password:");
	fflush(stdout);
	gets(passbuf);

	struct spwd *sp = getspnam(userbuf);
	if(sp == NULL) {
		printf("set sp error\n");
	}

    /* ��֤�û������������ȷ�� */
	if(!strcmp(sp->sp_pwdp, (char*)crypt(passbuf, sp->sp_pwdp))) {
		printf("correct\n");
	}
	else {
		printf("user or password error\n");
	}

    /* �ָ��ն�ԭ�������� */
	tcsetattr(STDIN_FILENO, TCSANOW, &ots);

	return 0;
}
