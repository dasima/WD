#include "produce_thread.h"
#include "buffer.h"
#include <pthread.h>
#include <stdlib.h>
#include <iostream>
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
    //pthread_create里面不能用对象的方法
}

void *ProduceThread::threadFunc(void *arg)
{
    ProduceThread *pt = static_cast<ProduceThread *> (arg);
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
        sleep(1);       
    }
}
// g++ produce_thread.cc -lpthread
// /tmp/cc57yGRg.o: In function `ProduceThread::run()':
// produce_thread.cc:(.text+0xf7): undefined reference to `Buffer::produce(int)'`

//这种原因是链接错误，原因是：函数涉及多个头文件，而链接时只链接了produce_thread.cc一个文件
void ProduceThread::join()
{
    pthread_join(tid_, NULL);
}

