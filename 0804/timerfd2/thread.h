#ifndef _THREAD_H_
#define _THREAD_H_

#include "non_copyable.h"
#include <functional>
#include <pthread.h>

class Thread : private NonCopyable
{
    public:
        typedef std::function<void()> ThreadFunc;

        Thread();
        explicit Thread(const ThreadFunc &callback);//防止只有单个参数的默认构造函数进行隐式转化
        ~Thread();

        void setCallback(const ThreadFunc &);
        void start();
        void join();
    private:
        static void *threadFunc(void *);//

        pthread_t tid_;
        bool is_started_;
        ThreadFunc callback_;
};

#endif  /*_THREAD_H_*/
