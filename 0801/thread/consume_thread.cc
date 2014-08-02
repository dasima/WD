#include "buffer.h"
#include "consume_thread.h"
#include <stdlib.h>
#include <iostream>
using namespace std;
ConsumeThread::ConsumeThread(Buffer &buffer)
    :tid_(0), buffer_(buffer)
{
    srand(time(NULL));
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
    ConsumeThread *pt = static_cast<ConsumeThread*>(arg);
    pt->run();
}

void ConsumeThread::run()
{
    while(1)
    {
        int data = buffer_.consume();
        cout << "consume a data " << data << endl;
        sleep(5);
    }
}

void ConsumeThread::join()
{
    pthread_join(tid_, NULL);
}
