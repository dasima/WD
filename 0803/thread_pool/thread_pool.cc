#include "thread_pool.h"
#include "thread.h"

using namespace std;

ThreadPool::ThreadPool(size_t queue_size, size_t pool_size)
    :empty_(mutex_),
    full_(mutex_),
    queue_size_(queue_size),
    pool_size_(pool_size),
    is_started_(false)
{
}

ThreadPool::~ThreadPool()
{
    if(is_started_)
        stop();
}

void ThreadPool::addTask(const Task &task)
{
    mutex_.lock();
    while(queue_.size() >= queue_size_)
        empty_.wait();
    queue_.push(task);
    full_.notify();
    mutex_.unlock();
}

//
ThreadPool::Task ThreadPool::getTask()
{
    mutex_.lock();
    while(queue_.empty() && is_started_)
        full_.wait();
    Task task;
    if(!queue_.empty())
    {
        task = queue_.front();
        queue_.pop();
        empty_.notify();
    }
    mutex_.unlock();
    return task;
}

void ThreadPool::runInThread()
{
    while(is_started_)
    {
        Task task(getTask());
        if(task)
            task();
    }
}

void ThreadPool::start()
{
    if(is_started_)
        return ;
    is_started_ = true;
    for(size_t i = 0; i != pool_size_; ++i)
        threads_.push_back(new Thread(bind(&ThreadPool::runInThread, this)));
    for(size_t i = 0; i != pool_size_; ++i)
        threads_[i]->start();
}

void ThreadPool::stop()
{
    if(is_started_ == false)
        return;
    mutex_.lock();
    is_started_ = false;
    full_.notifyAll();
    mutex_.unlock();

    for(size_t i = 0; i != pool_size_; ++i)
        threads_[i]->join();

    while(!queue_.empty())
        queue_.pop();
}
