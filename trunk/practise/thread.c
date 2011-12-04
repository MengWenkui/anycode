#include <pthread.h>
#include <stdio.h>

struct test_arg
{
	int a;
	char b;
};

void* print_xs (void* arg)
{
	int i = 0;
  //      while(1)   	
        printf("%d", ((struct test_arg*)arg)->a);

	free(arg);

	pthread_detach(pthread_self());
   
       static int res = 100;
       pthread_exit(&res);
 }
 
int main ()
{

	struct test_arg *arg = (struct test_arg*)malloc(sizeof(struct test_arg));

	arg->a = 5;
	arg->b = 'c';

     	pthread_t thread_id;

	pthread_attr_t attr;
	pthread_attr_init(&attr);
//	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

    	pthread_create(&thread_id, &attr, &print_xs, (void*)arg);

	pthread_detach(thread_id);

	pthread_attr_destroy(&attr);

	pthread_join(thread_id, NULL);

//	sleep(1);
//	printf("Hello\n");

     
    	void *res;
     	pthread_join(thread_id, &res);
    	printf("%d", *((int*)res));    
  
//	sleep(1);
     	return 0;
}
