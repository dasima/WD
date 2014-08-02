#include "queue.h"
#include <unistd.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#define BUFFERSIZE 9

pthread_mutex_t mutex;
pthread_cond_t full;
pthread_cond_t empty;
Queue Q;

void *produce(void *arg)
{
    while(1)
    {
        sleep(3);
        srand(time(NULL));
        pthread_mutex_lock(&mutex);
        if(get_size(&Q) >= BUFFERSIZE)
            pthread_cond_wait(&empty, &mutex);
        int data = rand() % 100;
        push(&Q, data);
        printf("produce one :%d\n", data);

        pthread_cond_broadcast(&full);
       // pthread_cond_signal(&full);
        pthread_mutex_unlock(&mutex);
    }
}
void * consume(void *arg)
{
    while(1)
    {
        sleep(3);
        srand(time(NULL));
        pthread_mutex_lock(&mutex);
        while(is_empty(&Q))
        {
            pthread_cond_wait(&full, &mutex);
        }
        int data = top(&Q);
        pop(&Q);
        printf("consume one data %d\n", data);

        pthread_cond_signal(&empty);
        pthread_mutex_unlock(&mutex);
    }
}

int main(int argc, const char *argv[])
{
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&full, NULL);
    pthread_cond_init(&empty, NULL);
    init(&Q);

    pthread_t tid1, tid2, tid3, tid4;
    pthread_create(&tid1, NULL, &produce, NULL);
    pthread_create(&tid2, NULL, &consume, NULL);
    pthread_create(&tid3, NULL, &consume, NULL);
    pthread_create(&tid4, NULL, &consume, NULL);

    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
    pthread_join(tid3, NULL);
    pthread_join(tid4, NULL);

    destroy(&Q);
    pthread_cond_destroy(&empty);
    pthread_cond_destroy(&full);
    pthread_mutex_destroy(&mutex);
    return 0;
}
