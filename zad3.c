#define _GNU_SOURCE
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

#include <unistd.h>
#include <errno.h>

#define CLIENTS 20
#define MUGS    5
#define MAX_WAIT    10

void * client(void *);

pthread_mutex_t mugs[MUGS];

int main()
{
    for(int i = 0; i < MUGS; i++)
    {
        if(pthread_mutex_init(&mugs[i], NULL) != 0)
        {
            printf("ERROR - mutex init - %d\n", i);
            return 1;
        }
    }
    pthread_t tid[CLIENTS];
    int args[CLIENTS];
    for(int i = 0; i < CLIENTS; i++)
    {
        args[i] = i;
        if(pthread_create(&tid[i], NULL, client, &args[i]) != 0)
        {
            printf("ERROR - %d\n", i);
            return 1;
        }
    }
    

    for(int i = 0; i < CLIENTS; i++) 
    {
        if(pthread_join(tid[i],NULL) != 0)
        {
            printf("ERROR - thread join - %d\n", i);
            return 1;
        }
    }
    for(int i = 0; i < MUGS; i++)
    {
        if(pthread_mutex_destroy(&mugs[i]) != 0)
        {
                printf("ERROR - mutex destroy - %d\n", i);
                return 1;
        }
    }

    return 0;
}

void * client(void * arg_p)
{
    int id = *(int *)arg_p;

    printf("Do baru wchodzi klient nr %d\n", id);
    for(int i = 0; i < 2; i++)
    {
        int mug = 0;
        while(pthread_mutex_trylock(&mugs[mug]) != 0)
        {//szukaj wolnego kufla
            if(mug < MUGS-1) mug++;
            else mug = 0; 
        }
        printf("klient %d - pije piwo nr %d z kufla %d \n", id, i+1, mug);

        int random =  (int)(rand() / (RAND_MAX + 1.0) * MAX_WAIT);
        sleep(random);
        
        printf("klient %d - odkłada kufel nr %d po czasie %ds\n", id, mug, random);
        pthread_mutex_unlock(&mugs[mug]); 
    }
    printf("Z Baru wychodzi klient nr %d\n", id);
    return NULL;
}

