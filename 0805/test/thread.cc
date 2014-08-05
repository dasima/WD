#include "thread.h"
#include <iostream>
using namespace std;

Thread::Thread()
    :tid_(0), is_started_(false)
{
}

Thread::Thread(const ThreadFunc &callback)
    :tid_(0),
    is_started_(false),
    callback_(callback)
{
}

Thread::~Thread()
{
    if(is_started_)
        pthread_detach(tid_);
}

void Thread::setCallback(const ThreadFunc &tf)
{
    callback_ = tf;
}

void *Thread::threadFunc(void *arg)
{
    cout << "in thread..." << endl;
    Thread *pt = static_cast<Thread *>(arg);
    pt->callback_();//timer_thread中threadCallback中的bind()的Timer，这里会调用Timer的runTimer
    return NULL;
}


void Thread::start()
{
    //void *(*)(void *)
    pthread_create(&tid_, NULL, threadFunc, this);
}

void Thread::join()
{
    pthread_join(tid_, NULL);
}
