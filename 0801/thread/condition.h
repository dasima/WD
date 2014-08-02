#ifndef CONDITION_H_
#define CONDITION_H_ 
#include <pthread.h>
class Mutex;//这里只需要前向声明即可
class Condition
{
    public:
        Condition(Mutex &);
        ~Condition();
        void wait();
        void signal();
        void signalAll();
    private:
        Mutex &lock_;
        pthread_cond_t cond_;
        
};

#endif  /*CONDITION_H_*/
