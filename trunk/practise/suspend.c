#include<stdio.h>
#include<signal.h>
#include<sys/types.h>


volatile sig_atomic_t quitflag;


static void sig_int(int signo)
{
        if(signo==SIGINT)printf("\ninterrupt\n");
        
        if(signo==SIGQUIT){
        printf("get SIGQUIT \n");
        quitflag=1;
        }
}       


int main(void)
{
        sigset_t newmask,oldmask,zeromask;


        if(signal(SIGINT,sig_int)==SIG_ERR){
        printf("signal SIGINT error\n");
        return -1;
        }


        if(signal(SIGQUIT,sig_int)==SIG_ERR){
        printf("signal SIGQUIT error\n");
        return -1;
        }


        sigemptyset(&zeromask);
        sigemptyset(&newmask);
        sigaddset(&newmask,SIGINT);
        sigaddset(&newmask,SIGQUIT);


        if(sigprocmask(SIG_BLOCK,&newmask,&oldmask)<0){
        printf("sigprocmask SIG_BLOCK\n");
        return -1;
        }


        while(quitflag==0)sigsuspend(&zeromask);
        quitflag=0;


        if(sigprocmask(SIG_SETMASK,&oldmask,NULL)<0){
        printf("sigprocmask SIG_SETMASK\n");
        return -1;
        }


        return 0;
}
