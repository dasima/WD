#ifndef _THREAD_POOL_H_
#define _THREAD_POOL_H_ 
#include <pthread.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

#define TRUE 1
#define FALSE 0

typedef int BOOL;
//定义任务结构体?????
typedef struct {
    void (*thread_callback)(void*);//任务执行函数
    void *arg;//任务函数的参数
}Task_t;
//thread_callback(arg) 执行任务

//任务队列的节点
typedef struct Qnode {
    Task_t data_;
    struct Qnode *next_;
}Qnode, *Pnode;

//任务队列
typedef struct {
    Pnode head_;
    Pnode tail_;
    size_t size_;
}Queue;

//线程池
typedef struct {
     size_t size_;//线程池大小
     pthread_t *pthreads_;//线程数组
     BOOL is_started_;//pool是否开启
     Queue queue_;//任务队列
     pthread_mutex_t mutex_;//互斥锁
     pthread_cond_t cond_;//条件变量，用来通知消费者
}Pool_t;

void queue_init(Queue *);//
void queue_destroy(Queue *);
void queue_push(Queue *, Task_t);
void queue_pop(Queue *);
void queue_clear(Queue *);
Task_t queue_top(const Queue *);
BOOL queue_is_empty(const Queue *);
size_t queue_get_size(const Queue *);

void thread_pool_init(Pool_t *, size_t size);//线程池初始化
void thread_pool_destroy(Pool_t *);//销毁线程池
void thread_pool_start(Pool_t *);//启动线程池
void thread_pool_stop(Pool_t *);//停止
void thread_pool_add(Pool_t *, Task_t);//添加任务
BOOL thread_pool_get(Pool_t *, Task_t *task);//获取任务??????
BOOL thread_pool_is_started(const Pool_t *);//判断线程池是否开启
size_t thread_pool_getsize(const Pool_t *);//线程池任务队列大小

#endif  /*_THREAD_POOL_H_*/
