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

void Thread::start()
{
    is_started_ = true;
    pthread_create(&tid_, NULL, callback_, NULL);
}

void Thread::join()
{
    pthread_join(tid_, NULL);
    is_started_ = false;
}
