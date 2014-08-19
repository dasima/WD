#ifndef _MUTUAL_H_
#define _MUTUAL_H_ 
#include <pthread.h>
#include <stdexcept>

class Mutex
{
    public:
        Mutex()
        {
            if(pthread_mutex_init(&lock_, NULL))
                throw std::runtime_error("init lock failed");
        }

        ~Mutex()
        {
            if(pthread_mutex_destroy(&lock_))
            {
                throw std::runtime_error("destroy lock failed");
            }
        }

        void lock()
        {
            if(pthread_mutex_lock(&lock_))
            {
                throw std::runtime_error("lock failed");
            }
        }

        void unlock()
        {
            if(pthread_mutex_unlock(&lock_))
            {
                throw std::runtime_error("unlock failed");
            }
        }

        pthread_mutex_t *getMutexLockPtr()
        {
            return &lock_;
        }
    private:
        pthread_mutex_t lock_;
};
#endif  /*_MUTUAL_H_*/
