#include "buffer.h"
#include <iostream>
using namespace std;
Buffer::Buffer(size_t size)
    :queue_(),
    mutex_(),
    full_(mutex_),
    empty_(mutex_),
    size_(size)
{
}

Buffer::~Buffer()
{
}

//这两个函数是为了供外部调用的
//类内部不能调用，否则造成死锁
bool Buffer::isEmpty() const
{
    mutex_.lock();
    bool ret = queue_.isEmpty();
    mutex_.unlock();
    return ret;
}

bool Buffer::isFull() const/////const
{
    mutex_.lock();////lock??
    bool ret = queue_.getSize() >= size_;
    mutex_.unlock();
    return ret;
}

//如果中间assert失败，此时mutex没有解锁，造成析构失败
void Buffer::produce(int data)
{
    mutex_.lock();
    //这里不能调用buffer本身的isEmpty,否则造成死锁
    while(queue_.getSize() >= size_)///////
        empty_.wait();
    queue_.push(data);
    cout << "produce size= " << queue_.getSize() << endl;
    full_.signal();
    mutex_.unlock();
}

int Buffer::consume()///////int?
{
    mutex_.lock();
    while(queue_.isEmpty())
        full_.wait();
    int ret = queue_.top();
    queue_.pop();
    cout << "consume data " << ret << endl;
    cout << "consume size = " << queue_.getSize() << endl;
    empty_.signal();
    mutex_.unlock();
    return ret;
}
