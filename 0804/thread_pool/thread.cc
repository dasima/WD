#include "thread.h"

Thread::Thread(ThreadFunc func)
    :callback_(func),
    tid_(0),
    is_started_(false)
{
}

Thread::~Thread()
{
    if(is_started_)
        pthread_detach(tid_);
}

void *Thread::threadFunc(void *arg)
{
    Thread *pt = static_cast<Thread*>(arg);
    pt->callback_();//调用线程逻辑
    return NULL;
}

void Thread::start()
{
    //void *(*)(void*)
    pthread_create(&tid_, NULL, threadFunc, this);
}

void Thread::join()
{
    pthread_join(tid_, NULL);
}
