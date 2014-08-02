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

void Buffer::produce(int data)
{
    mutex_.lock();
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
    cout << "consume size = " << queue_.getSize() << endl;
    empty_.signal();
    mutex_.unlock();
    return ret;
}
