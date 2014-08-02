#ifndef _CONDITION_H_
#define _CONDITION_H_ 
#include <pthread.h>
class Mutex;
class Condition
{
    public:
        Condition(Mutex &lock);
        ~Condition();
//        wait();//error: ISO C++ forbids declaration of ‘wait’ with no type [-fpermissive]
        void wait();
        void signal();
        void signalAll();
    private:
        Mutex &lock_;
        pthread_cond_t cond_;
};
#endif  /*_CONDITION_H_*/
