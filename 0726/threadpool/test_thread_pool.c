#include "thread_pool.h"

void task_func(void *arg)
{
    int t = (int) arg;
    printf("%d\n", t);
}

int main(int argc, const char *argv[])
{
    Pool_t pool;
    thread_pool_init(&pool, 4);
    thread_pool_start(&pool);

    srand(100);
    while(1)
    {
        sleep(1);
        Task_t task;
        size_t size;
        task.thread_callback = task_func;
        task.arg = (void*)(rand() % 100);
        thread_pool_add(&pool, task);
        size = thread_pool_getsize(&pool);
        printf("size --- %d\n", size);
    }

    pthread_pool_stop(&pool);
    pthread_pool_destroy(&pool);
    return 0;
}
