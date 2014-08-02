#include "produce_thread.h"
#include <iostream>
#include <unistd.h>
#include <stdlib.h>
using namespace std;

ProduceThread::ProduceThread(Buffer &buffer)
    :tid_(0), buffer_(buffer)
{
    srand(time(NULL)); 
}

ProduceThread::~ProduceThread()
{

}

void ProduceThread::start()
{
    pthread_create(&tid_, NULL, threadFunc, this);
}

void* ProduceThread::threadFunc(void *arg)
{
    ProduceThread *pt = static_cast<ProduceThread *>(arg);
    pt->run();
    return NULL;
}

void ProduceThread::run()
{
    while(1)
    {
        int data = rand() % 100;
        cout << "produce a data " << data << endl;
        buffer_.produce(data);
        sleep(3);
    }
}

void ProduceThread::join()
{
    pthread_join(tid_, NULL);
}
