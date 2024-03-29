/* The effect of pthread_join() */
#define _GNU_SOURCE
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#define NTHREADS 5

void *thread_function(void *); //adding thread
int counter = 0; // a global counter
pthread_mutex_t lock; //mutexlock declaration

int main(){
   pthread_t thread_id[NTHREADS];
   int i, j, err;
   
   if (pthread_mutex_init(&lock, NULL) != 0){ //mutexlock initialization
        printf("\n mutexlock init failed\n");
        return 1;
    }
   
   for(i = 0; i < NTHREADS; i++){ //create threads array
	   err = pthread_create( &thread_id[i], NULL, thread_function, NULL );
	   if (err != 0){
		   printf("can't create thread :[%s]\n", strerror(err));
		      
	   }
   }
   
   /* wait for completion of all threads */
   /* kind of thread synchronization     */
   for(j = 0; j < NTHREADS; j++) //wait for completion of all threads
      pthread_join( thread_id[j], NULL);

 	printf("Final counter value: %d\n", counter);
	pthread_mutex_destroy(&lock);
	
	return 0;
}
 
void *thread_function(void *dummyPtr){
	int i;
	pthread_mutex_lock(&lock); //lock critical section
	
	for (i = 0; i < 100000000; i++)
   		counter++;
	printf("thread-%ld: The counter value is %2d\n", (long)pthread_self(), counter);
	
	pthread_mutex_unlock(&lock); //unlock critical section
  	return((void *) 0);
}
