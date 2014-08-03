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

struct ThreadData
{
    typedef Thread::ThreadFunc ThreadFunc;
    ThreadFunc func_;

    ThreadData(ThreadFunc func)
        :func_(func)
    {
    }

    void runThread()
    {
        func_();
    }
};

void *threadFunc(void *arg)
{
    //1, 这里t不能调用callback_,因为callback_是私有的。
   /* Thread *t = static_cast<Thread*>(arg);
    t->callback_();*/
   
    //2,如果在Thread类中public定义一个threadFunc,则调用会成功，不再需要ThreadData结构体。如下
   /* Thread *t = static_cast<Thread*>(arg);
    t->threadFunc_();*/

    //3, 通过一个结构体中间体来调用
    ThreadData *td = static_cast<ThreadData *>(arg);
    td->runThread();
   // td->func_();//4， 这里可以直接调用func_()，不用再套用一层runThread调用
    delete td;
}

//pthread_create调用的是void *threadFunc(void*)类型，而function是void（）类型
//结构体中func_也是void类型，所以通过void* threadFunc(void *arg)函数调用func_()函数
void Thread::start()
{
    ThreadData *data = new ThreadData(callback_);
    if(pthread_create(&tid_, NULL, threadFunc, data))
        delete data;
}

void Thread::join()
{
    pthread_join(tid_, NULL);
}
