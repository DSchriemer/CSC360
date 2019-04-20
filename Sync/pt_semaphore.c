#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t semaphore;
const int CRITICAL_THREADS = 2;
const int N_THREADS = 5;

void* thread(void* arg){
    sem_wait(&semaphore);
    // Critical section
    printf("A thread has ENTERED the critical section.\n");
    
    sleep(1); // Do "work"

    printf("A thread is about to LEAVE the critical section.\n");
    sem_post(&semaphore);
    return NULL;
}

int main(){
    sem_init(&semaphore, 0, CRITICAL_THREADS);
    pthread_t threads[N_THREADS];
    int i;

    for(i = 0; i < N_THREADS; i++){
        if(pthread_create(&threads[i], NULL, thread, NULL)){
            printf("Couldn't create thread\n");
            return -1;
        }
    }

    for(i = 0; i < N_THREADS; i++){
        pthread_join(threads[i], NULL);
    }

    sem_destroy(&semaphore);
}