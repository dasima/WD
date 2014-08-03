#ifndef THREAD_H_
#define THREAD_H_ 

#include "non_copyable.h"
#include <functional>
#include <pthread.h>

class Thread : private NonCopyable
{
    public:
        typedef std::function<void()> ThreadFunc;

        Thread(ThreadFunc);
        ~Thread();

        void start();
        void join();

    private:
        //这里设为static，是因为：
        //如果是普通成员函数，类型为void* Thread::threadFunc(void *)
        //而pthread_create调用的是void *threadFunc(void*)类型
        //他们类型不匹配，
        //设为static，类型就能够匹配
        static void* threadFunc(void*);

        ThreadFunc callback_;
        pthread_t tid_;
        bool is_started_;
};

#endif  /*THREAD_H_*/
