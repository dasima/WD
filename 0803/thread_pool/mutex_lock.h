#ifndef MUTEXLOCK_H
#define MUTEXLOCK_H

#include <assert.h>
#include <pthread.h>
#include "non_copyable.h"

class MutexLock : NonCopyable
{
    public:
        MutexLock();
        ~MutexLock();
        void lock();
        void unlock();

        //why not const ???
        pthread_mutex_t *getMutexPtr(){return &mutex_;}
        bool isLocked() const {return is_locked_;}
    private:
        pthread_mutex_t mutex_;
        bool is_locked_;
};

inline MutexLock::MutexLock()
    :is_locked_(false)
{
    pthread_mutex_init(&mutex_, NULL);
}

inline MutexLock::~MutexLock()
{
    //
    assert(is_locked_ == false);
    pthread_mutex_destroy(&mutex_);
}

inline void MutexLock::lock()
{
    pthread_mutex_lock(&mutex_);
    is_locked_ = true;
}

inline void MutexLock::unlock()
{
    pthread_mutex_unlock(&mutex_);
    is_locked_ = false;
}

#endif  /*MUTEXLOCK_H*/
