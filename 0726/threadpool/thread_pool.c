#include "thread_pool.h"

void thread_pool_init(Pool_t *pool, size_t size)
{
    pool -> size_ = size;
    pool -> pthreads_ = (pthread_t *)malloc(sizeof(pthread_t) * pool -> size_);
    pool -> is_started_ = FALSE;
    queue_init(&pool -> queue_);
    pthread_mutex_init(&pool -> mutex_, NULL);
    pthread_cond_init(&pool -> cond_, NULL);
}

void thread_pool_destroy(Pool_t *pool)
{
    thread_pool_stop(pool);
    free(pool -> pthreads_);
    queue_destroy(&pool -> queue_);
    pthread_mutex_destroy(&pool -> mutex_);
    pthread_cond_destroy(&pool -> cond_);
}

void *thread_func(void *arg)
{
    printf("hhhhh\n"); 
    
}

void thread_pool_start(Pool_t *pool)
{
    if(pool -> is_started_ == FALSE)
    {
        pool -> is_started_ = TRUE;
        int i;
        for(i = 0; i < pool->size_; ++i)
        {
            pthread_create(&pool->pthreads_[i], NULL, thread_func, NULL);
        }
    }
}

void thread_pool_stop(Pool_t *pool)
{
    if(pool -> is_started_ == FALSE)
        return ;
    pool -> is_started_ = FALSE;
    pthread_cond_broadcast(&pool -> cond_);
    int i;
    for(i = 0; i < pool -> size_; ++i)
    {
        pthread_join(pool -> pthreads_[i], NULL);
    }
    queue_clear(&pool -> queue_);
}

void thread_pool_add(Pool_t *pool, Task_t task)
{
    pthread_mutex_lock(&pool -> mutex_);
    queue_push(&pool -> queue_, task);
   // printf("produce one : %d\n", (int)(task->arg));
    pthread_cond_signal(&pool -> cond_);
    pthread_mutex_unlock(&pool -> mutex_);
}

BOOL thread_pool_get(Pool_t *pool, Task_t* task)
{
    pthread_mutex_lock(&pool -> mutex_);
    while(queue_is_empty(&pool -> queue_) && pool -> is_started_)
    {
        pthread_cond_wait(&pool -> cond_, &pool -> mutex_);
    }
    //???????????????
    if(pool -> is_started_ == FALSE)
    {
        pthread_mutex_unlock(&pool -> mutex_);
        return FALSE;
    }
    *task = queue_top(&pool->queue_);
    queue_pop(&pool -> queue_);
   // printf("get a tata : %d\n", (int*)((*task)->arg));

    pthread_mutex_unlock(&pool -> mutex_);
    return TRUE;
}

BOOL thread_pool_is_started(const Pool_t *pool)
{
    return pool ->  is_started_;    
}

size_t thread_pool_getsize(const Pool_t *pool)
{
    return pool -> size_;
}
