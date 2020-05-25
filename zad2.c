#define _GNU_SOURCE
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <errno.h>


void * thread_1(void *);
void * thread_2(void *);

sem_t mutex; 

int global = 0;

int main()
{
    pthread_t tid[2];
    int res = 0;

    sem_init(&mutex, 0, 1); 
    
    res += pthread_create(&tid[0], NULL, thread_1, NULL);
    res += pthread_create(&tid[1], NULL, thread_2, NULL);

    if(res != 0 )
        printf("ERROR\n");
    
    pthread_join(tid[0],NULL);
    pthread_join(tid[1],NULL);
    sem_destroy(&mutex); 
    printf("Global value: %d\n", global);
    return 0;
}

void * thread_1(void * agr_p)
{
    for(int i = 0; i < 1000; i++)
    {
        sem_wait(&mutex); 
        global++;
        sem_post(&mutex); 
        
    }
    return NULL;
}

void * thread_2(void * agr_p)
{
    for(int i = 0; i < 1000; i++)
    {
        sem_wait(&mutex); 
        global--;
        sem_post(&mutex); 
    }
    
    return NULL;
}
