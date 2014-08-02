#ifndef _THREAD_H_
#define _THREAD_H_ 
#include <pthread.h>

class Thread
{
    public:
        //函数指针实现线程调用
        typedef void*(*ThreadCallBack) (void*);
        Thread(ThreadCallBack callBack);
        void start();
        void join();
    private:
        ThreadCallBack callBack_;
        pthread_t tid_;

};
#endif  /*_THREAD_H_*/
