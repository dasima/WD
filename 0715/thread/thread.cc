#include "thread.h"

Thread::Thread(ThreadCallBack callBack)
    :tid_(0), callBack_(callBack)
{
}

void Thread::start()
{
    pthread_create(&tid_, NULL, callBack_, NULL);
}

void Thread::join()
{
    pthread_join(tid_, NULL);
}
