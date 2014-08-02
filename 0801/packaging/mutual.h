#ifndef _MUTUAL_H_
#define _MUTUAL_H_ 
#include <pthread.h>
#include <stdexcept>

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
#endif  /*_MUTUAL_H_*/
