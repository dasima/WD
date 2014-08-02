#ifndef _QUEUE_H_
#define _QUEUE_H_ 

#include <iostream>
#include <assert.h>

template <typename T> 
class Queue;
template <typename T> 
class Node 
{
    friend class Queue<T>;
    private:
    T data_;
    Node* next_;
};
template <typename T>
class Queue
{
    public:
        typedef Node<T> *NodePtr;
        Queue();
        Queue(const Queue &other);
        ~Queue();
        Queue &operator=(const Queue &other);
        void push(const T &data);
        void pop();
        bool isEmpty() const;
        const T &top() const;
        void clear();
        size_t getSize() const;
    private:
        void copyElements(const Queue &other);
        NodePtr head_;
        NodePtr tail_;
        size_t size_;
};

    template <typename T>
    inline Queue<T>::Queue()
:head_(NULL),
    tail_(NULL),
    size_(0)
{
}

    template <typename T>
    inline Queue<T>::Queue(const Queue &other)
:head_(NULL),
    tail_(NULL),
    size_(0)
{
    copyElements(other);
}

    template <typename T>
inline Queue<T>::~Queue()
{
    clear();
}

    template <typename T>
inline void Queue<T>::copyElements(const Queue &other)
{
    for(NodePtr pt = other.head_; pt; pt = pt -> next_)
    {
        push(pt -> data_);
    }
}

    template <typename T>
inline Queue<T> &Queue<T>::operator=(const Queue &other)
{
    if(this != &other)
    {
        clear();
        copyElement(other);
    }
    return *this;
}

    template <typename T>
inline void Queue<T>::push(const T &data)
{
    NodePtr pt = new Node<T>;
    pt -> data_ = data;
    pt -> next_ = NULL;
    if(isEmpty())
    {
        head_ = tail_ = pt;
    }
    else
    {
        tail_ -> next_ = pt;
        tail_ = pt;
    }
    ++size_;
}

    template <typename T>
inline void Queue<T>::pop()
{
    assert(!isEmpty());
    NodePtr pt = head_;
    head_ = head_ -> next_;
    delete pt;
    --size_;
}

template <typename T>
inline const T &Queue<T>::top() const
{
    assert(!isEmpty());
    return head_ -> data_;
}

template <typename T>
bool Queue<T>::isEmpty() const
{
    return head_ == NULL;
}

    template <typename T>
void Queue<T>::clear()
{
    while(!isEmpty())
    {
        pop();
    }
}

template <typename T>
size_t Queue<T>::getSize() const
{
    return size_;
}
#endif  /*_QUEUE_H_*/
