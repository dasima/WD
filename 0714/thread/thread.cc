#include <iostream>
#include <string>
#include <vector>
#include "thread.h"
using namespace std;

Thread::Thread()
    :tid_(-1)
{
}

Thread::~Thread()
{
}

void Thread::start()
{
    pthread_create(&tid_, NULL, threadFunc, this);
}

void *Thread::threadFunc(void* arg)
{
    Thread *pt = static_cast<Thread*>(arg);
    pt -> run();
}

void Thread::run()
{
    a_ = 1;
    while(1)
    {
        cout << ++a_ << endl;
        sleep(1);
    }
}

void Thread::join()
{
    pthread_join(tid_, NULL);
}

