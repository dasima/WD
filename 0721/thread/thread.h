#ifndef _THREAD_H_
#define _THREAD_H_ 

#include<iostream>
class Thread
{
    public:
        Thread();
        virtual ~Thread();

        void start();
        static void *threadFunc(void *arg);
        virtual void run();
        void join();
    private:
        pthread_t tid_;
        static size_t size_;
};
#endif  /*_THREAD_H_*/
