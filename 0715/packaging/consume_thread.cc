#include "buffer.h"
#include "consume_thread.h"
#include <unistd.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

ConsumeThread::ConsumeThread(Buffer &buffer)
    :tid_(0), buffer_(buffer)
{
}

ConsumeThread::~ConsumeThread()
{
}

void ConsumeThread::start()
{
    pthread_create(&tid_, NULL, threadFunc, this);
}

void *ConsumeThread::threadFunc(void *arg)
{
    ConsumeThread *pt = static_cast<ConsumeThread*> (arg);
    pt->run();
    return NULL;
}

void ConsumeThread::run()
{
    while(1)
    {
        int data = buffer_.consume();
      // cout << "consume a data " << data << endl;
        sleep(rand() % 3);
    }
}

void ConsumeThread::join()
{
    pthread_join(tid_, NULL);
}

