#ifndef _THREAD_H_
#define _THREAD_H_ 
#include <pthread.h>
class Thread
{
    public:
        Thread();
        ~Thread();
        
        void start();
        static void* threadFunc(void* arg);
        void run();
        void join();
    private:
        pthread_t tid_;
        int a_;
};
#endif  /*_THREAD_H_*/
