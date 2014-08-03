#ifndef CONDITION_H_
#define CONDITION_H_

#include <pthread.h>
#include "non_copyable.h"
class MutexLock;
class Condition : NonCopyable
{
    public:
        Condition(MutexLock &mutex);
        ~Condition();

        void wait();
        void notify();
        void notifyAll();
    private:
        pthread_cond_t cond_;
        MutexLock &mutex_;
};


#endif  /*CONDITION_H_*/
