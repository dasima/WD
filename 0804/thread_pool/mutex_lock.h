#ifndef MUTEXLOCK_H
#define MUTEXLOCK_H

#include <assert.h>
#include <pthread.h>
#include "non_copyable.h"

class MutexLock : NonCopyable
{
    friend class MutexLockGuard;
    public:
        MutexLock();
        ~MutexLock();

        //为什么不用const类型？？？
        //有要用到它的值，并进行改变
        pthread_mutex_t *getMutexPtr(){return &mutex_;}
        bool isLocked() const {return is_locked_;}
    private:
        //防止手工调用
        void lock();
        void unlock();

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
    //确保这里已经解锁
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
    is_locked_ = false;
    pthread_mutex_unlock(&mutex_);
}

class MutexLockGuard
{
    public:
        MutexLockGuard(MutexLock &mutex);
        ~MutexLockGuard();
    private:
        MutexLock &mutex_;
};

inline MutexLockGuard::MutexLockGuard(MutexLock &mutex)
    :mutex_(mutex)
{
    mutex_.lock();
}

inline MutexLockGuard::~MutexLockGuard()
{
    mutex_.unlock();
}

//MutexLockGuard(mutex_);
//帮助在编译期间发现错误
#define MutexLockGuard(m) "ERROR"

#endif  /*MUTEXLOCK_H*/
