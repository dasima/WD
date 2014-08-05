#include "thread_pool.h"
#include "thread.h"

using namespace std;

//注意初始化的顺序
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
    MutexLockGuard lock(mutex_);
    while(queue_.size() >= queue_size_)
        empty_.wait();
    queue_.push(task);
    full_.notify();//通知消费者取任务
}

//
ThreadPool::Task ThreadPool::getTask()
{
    MutexLockGuard lock(mutex_);
    while(queue_.empty() && is_started_)//???is_started_
        full_.wait();
    /*
     *这里的wait可以被stop函数中的notifyAll所激活
     *激活之后， is_started_不再为true
     *就退出while循环
     *显然，此时队列仍然为空
     */
    Task task;
    //如果队列不为空
    if(!queue_.empty())
    {
        task = queue_.front();
        queue_.pop();
        empty_.notify();//通知生产者
    }
    return task;
}

void ThreadPool::runInThread()
{
    //当线程池关闭时，这个线程可以自动退出
    while(is_started_)
    {
        Task task(getTask());
        if(task)
            task();//真正执行任务
    }
}

void ThreadPool::start()
{
    if(is_started_)
        return ;
    is_started_ = true;
    //开启线程
    for(size_t i = 0; i != pool_size_; ++i)
        threads_.push_back(new Thread(bind(&ThreadPool::runInThread, this)));
    for(size_t i = 0; i != pool_size_; ++i)
        threads_[i]->start();
}

void ThreadPool::stop()
{
    if(is_started_ == false)
        return;
    {
        MutexLockGuard lock(mutex_);
        is_started_ = false;
        full_.notifyAll();//激活所有正在等待任务的线程
    }

    for(size_t i = 0; i != pool_size_; ++i)
        threads_[i]->join();

    while(!queue_.empty())
        queue_.pop();
}
