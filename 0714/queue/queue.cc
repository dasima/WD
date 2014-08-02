#include "queue.h"
#include <assert.h>

Queue::Queue()
    :head_(NULL), tail_(NULL), size_(0)
{
}

Queue::~Queue()
{
    clear();
}

void Queue::push(int data)
{
    NodePtr node = new Node;
    node -> data_ = data;
    node -> next_ == NULL;
    if(isEmpty())
    {
        head_ = tail_ = node;
    }
    else
    {
        tail_ -> next_ = node;
        tail_ = node;
    }
    ++size_;
}

void Queue::pop()
{
    assert(!isEmpty());
    NodePtr node = head_;
    head_ = head_ -> next_;
    delete node;
    --size_;
}

int Queue::top() const
{
    assert(!isEmpty());
    return head_ -> data_;
}

bool Queue::isEmpty() const
{
    return head_ == NULL;
}

void Queue::clear()
{
    while(!isEmpty())
    {
        pop();
    }
}

size_t Queue::getSize() const
{
    return size_;
}
