#ifndef THREAD_POOL_H
#define THREAD_POOL_H

#include "non_copyable.h"
#include "mutex_lock.h"
#include "condition.h"
#include "ptr_vector.h"
#include <queue>
#include <functional>

class Thread;
class ThreadPool : private NonCopyable
{
    public:
        typedef std::function<void()> Task;
        ThreadPool(size_t, size_t);
        ~ThreadPool();

        void start();//启动线程池
        void stop();//停止线程池

        void addTask(const Task &);
        Task getTask();            
    private:
        void runInThread();//线程池内线程的回调函数

        mutable MutexLock mutex_;
        Condition empty_;
        Condition full_;
        size_t queue_size_;//队列大小
        std::queue<Task> queue_;
        size_t pool_size_;//线程池大小
        PtrVector<Thread> threads_;
        bool is_started_;//线程池是否开启
};

#endif  /*THREAD_POOL_H*/
