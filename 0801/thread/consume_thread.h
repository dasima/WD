#ifndef CONSUME_THREAD_H_
#define CONSUME_THREAD_H_

#include <pthread.h>
class Buffer;
class ConsumeThread
{
    public:
        ConsumeThread(Buffer &);
        ~ConsumeThread();
        void start();
        static void *threadFunc(void* arg);
        void run();
        void join();
    private:
        pthread_t tid_;
        Buffer &buffer_;
};

#endif  /*CONSUME_THREAD_H_*/
