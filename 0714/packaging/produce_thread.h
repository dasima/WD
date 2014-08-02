#ifndef _PRODUCE_THREAD_H_
#define _PRODUCE_THREAD_H_ 
#include <pthread.h>
class Buffer;
class ProduceThread
{
    public:
        ProduceThread(Buffer &biffer);            
        ~ProduceThread();                              
        void start();
        static void *threadFunc(void * arg);
        void run();
        void join();
    private:
        pthread_t tid_;
        Buffer &buffer_;
};
#endif  /*_PRODUCE_THREAD_H_*/
