#ifndef THREAD_H_
#define THREAD_H_ 

#include "non_copyable.h"
#include <functional>
#include <pthread.h>
class Thread : private NonCopyable
{
    public:
        typedef std::function<void ()> ThreadFunc;

        Thread(ThreadFunc);
        ~Thread();

        void start();
        void join();
    private:
        static void *threadFunc(void*);

        ThreadFunc callback_;
        pthread_t tid_;
        bool is_started_;
};

#endif  /*THREAD_H_*/
