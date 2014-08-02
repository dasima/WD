#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void *thread_func(void *arg)
{
    pthread_detach(pthread_self());
    printf("hhhh\n");
    pthread_exit(NULL);    
}
int main(int argc, const char *argv[])
{
    pthread_t tid;
    pthread_create(&tid, NULL, thread_func, NULL);
    while(1)
        ;
    
    return 0;
}
