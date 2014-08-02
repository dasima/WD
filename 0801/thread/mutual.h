#ifndef MUTUAL_H_
#define MUTUAL_H_ 
#include <pthread.h>
class Mutex
{
    public:
        Mutex();
        ~Mutex();
        void lock();
        void unlock();
        pthread_mutex_t *getMutexLockPtr()
        {
            return &lock_;
        }
    private:
        pthread_mutex_t lock_;
};

#endif  /*MUTUAL_H_*/
