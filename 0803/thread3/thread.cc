#include "thread.h"
#include "non_copyable.h"

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
    pt->callback_();
}

void Thread::start()
{
    pthread_create(&tid_, NULL, threadFunc,this);
}

void Thread::join()
{
    pthread_join(tid_, NULL);
}
