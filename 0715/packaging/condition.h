#ifndef _CONDITION_H_
#define _CONDITION_H_ 
#include <pthread.h>
//Condition中仅包含Mutex的引用，所以不需要使用头文件
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
        Mutex &lock_;//这里使用引用，是因为生产者和消费者需要通过mutual中信号量lock_的改变进行交互
        pthread_cond_t cond_;
};
#endif  /*_CONDITION_H_*/
