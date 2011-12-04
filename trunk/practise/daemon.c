#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>

void init_daemon()
{
	int pid;
	int i;
	if(pid = fork()) exit(0);  //�����̣��˳�
	else if(pid < 0) exit(1);  //forkʧ��
	
	/*  �ӽ��̼���ִ��   */
	setsid();  //�����µĻỰ�飬�ӽ��̳�Ϊ�鳤����������ն˷���

   
    /*  ��ֹ�ӽ��̣��鳤����ȡ�����ն� */
	if(pid = fork()) exit(0);   //�����̣��˳�
	else if(pid < 0) exit(1);   //fork�����˳�
   
    /* �ڶ��ӽ��̼���ִ�� , �ڶ��ӽ��̲����ǻ�Ự���鳤*/
	
	for(i = 0; i < NOFILE; i++) /* �رմ򿪵��ļ�������  */
	{
		close(i);
	}
	chdir("/tmp");            /* �л�����Ŀ¼  */
	umask(0);                 /*  �����ļ���������  */
	return;
}

int main()
{
	FILE *fp;
	
	signal(SIGCHLD, SIG_IGN);  /* �����ӽ��̽����źţ���ֹ���ֽ�ʬ����  */

	init_daemon();

	while(1)
	{
		sleep(30);
		if((fp = fopen("test.log", "a")) != NULL)
		{
			fprintf(fp, "%s\n", "test message");
		fclose(fp);
		}
	}
	return 0;
}


