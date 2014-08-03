#ifndef THREAD_H_
#define THREAD_H_ 

#include "non_copyable.h"
#include <functional>
#include <pthread.h>

//c++11 
//function实现回调函数功能
class Thread : private NonCopyable
{
    public:
        //function<void()>
        typedef std::function<void()> ThreadFunc;

        //ThreadFunc threadFunc_;
        Thread(ThreadFunc func);
        ~Thread();

        void start();
        void join();

    private:
        ThreadFunc callback_;
        pthread_t tid_;
        bool is_started_;
};

#endif  /*THREAD_H_*/
