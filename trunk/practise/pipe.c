#include <stdio.h>
#include <unistd.h>

int main()
{

  int i,pid,r,x,count,p[2];
  long int sum;
  
  if(pipe(p)==-1){
  	printf("pipeerr\n");
  	exit(1);
  }
  
  if((pid = fork())==-1){
  	printf("forkerr\n");
  	exit(1);
  }

  if(pid==0){
    close(p[0]);
    dup2(p[1],1);
    srand(getpid());
    for(i=0;i<1000;i++) printf("%d\n",rand());
    exit(0);
  }

  count=0;
  sum=0;
  
  if(p<=0){
  	printf("error open\n");
  	exit(0);
  }
  
  close(p[1]);
  dup2(p[0],0);

  while(1){
    x=0;
    r=scanf("%d",&x);
    if(r<=0)
    	break;
    count++;
    sum+=x;
  }

  printf ("avg=%lf\n", (0.0+sum)/count);

  wait(&x);
  
  return 0;
}
