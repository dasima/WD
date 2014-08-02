#ifndef _CONSUME_THREAD_H_
#define _CONSUME_THREAD_H_ 
#include <pthread.h>

class Buffer;
class ConsumeThread
{
    public:
        ConsumeThread(Buffer &buffer);            
        ~ConsumeThread();
        void start();
        static void *threadFunc(void *arg);
        void run();
        void join();
    private:
        pthread_t tid_;
        Buffer &buffer_;
};
#endif  /*_CONSUME_THREAD_H_*/
