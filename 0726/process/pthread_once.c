#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

pthread_once_t once_control = PTHREAD_ONCE_INIT;
//int pthread_once(pthread_once_t *once_control, void(*init_routine)(void))
void test_once()
{
    printf("test......\n");
}
void *pthread_func(void *arg)
{
    //即使开启多个线程，这里也只执行一次
    pthread_once(&once_control, test_once);
    printf("in thread %lu\n", (unsigned long)pthread_self());
}
int main(int argc, const char *argv[])
{
    pthread_t tids[5];
    int i;
    for(i = 0; i != 5; ++i)
    {
        pthread_create(&tids[i], NULL, pthread_func, NULL);
        printf("----create----\n");
    }

    for(i = 0; i != 5; ++i)
    {
        pthread_join(tids[i], NULL);
        printf("-----join-----\n");
    }

    return 0;
}
