#include "thread.h"
#include <unistd.h>
#include <stdlib.h>
#include <iostream>
using namespace std;
    Thread::Thread()
:tid_(-1)
{
    srand(time(NULL));
}

Thread::~Thread()
{
}

void Thread::start()
{
    pthread_create(&tid_, NULL, threadFunc, this);
}

void *Thread::threadFunc(void *arg)
{
    Thread *pt = static_cast<Thread *> (arg);
    pt -> run();
    return NULL;
}

void Thread::run()
{
    while(1)
    {
        sleep(3);
        cout << "thread " << endl;    
    }
}

void Thread::join()
{
    pthread_join(tid_, NULL);
}
