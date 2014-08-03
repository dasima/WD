#ifndef THREAD_H_
#define THREAD_H_ 

#include "non_copyable.h"
#include <pthread.h>

//这个类是指针函数的调用
class Thread : private NonCopyable
{
    public:
        typedef void*(*ThreadFunc) (void*);//typedef

        Thread(ThreadFunc);
        ~Thread();

        void start();
        void join();

    private:
        ThreadFunc callback_;
        pthread_t tid_;
        bool is_started_;
};

#endif  /*THREAD_H_*/
