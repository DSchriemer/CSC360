/* The effect of pthread_join() */
//#define _GNU_SOURCE
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#define NTHREADS 2

void * thread_1(void *); //adding thread
void * thread_2(void *); //notification thread
int counter = 0; // a counter
pthread_mutex_t lock; //mutex declaration
pthread_cond_t convar = PTHREAD_COND_INITIALIZER; //convar initialization


int main(){
   pthread_t thread_id[NTHREADS]; //Keeps track of threads

   if (pthread_mutex_init(&lock, NULL) != 0){ //mutex initialization
        printf("\n mutex init failed\n");
        return -1;
    }

   if(pthread_create( &thread_id[0], NULL, thread_1, NULL ) != 0) //Thread ID, Attributes, Methods, argument
	   printf("can't create thread 1\n");

   if(pthread_create( &thread_id[1], NULL, thread_2, NULL ) != 0)
	   printf("can't create thread %d\n", 2);

	pthread_join(thread_id[0], NULL); //Wait for a thread to terminate and retireve its return value
	pthread_join(thread_id[1], NULL);

  //Not to be confused with wait, which is only used for child processes (pg.49 textbook)
  	printf("Main thread exits!\n");

	pthread_mutex_destroy(&lock);
	pthread_cond_destroy(&convar);

	return 0;
}

void *thread_1(void *dummyPtr){

	sleep(1); // Do "work"
	pthread_mutex_lock(&lock);
	pthread_cond_signal(&convar);
	printf("thread_1: sending signal..\n");
	sleep(1);
	pthread_mutex_unlock(&lock);


	return NULL;
}

void * thread_2(void * arg)
{
	pthread_mutex_lock(&lock);
	printf("thread_2: waiting to be signaled!\n");
	pthread_cond_wait(&convar, &lock); // release mutex(lock), wait on convar, until it is signaled
	printf("thread_2: woke up by thread_1\n");
	pthread_mutex_unlock(&lock);
	return NULL;
}
