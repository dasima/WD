#ifndef _QUEUE_H_
#define _QUEUE_H_ 
#include <iostream>
#include <stddef.h>
#include <assert.h>
template <typename T>
class Queue;//这里前向声明用于后面的friend
template <typename T>
class Node
{
    friend class Queue<T>;
    private:
        T data_;
        Node *next_;
};

template <typename T>
class Queue
{
    public:
        typedef Node<T>* NodePtr;
        Queue();
        Queue(const Queue &);
        ~Queue();
        Queue &operator=(const Queue &);

        bool isEmpty() const;
        void push(const T &data);
        void pop();
        void clear();
        const T &top() const;
        size_t getSize() const;
    private:
        NodePtr head_;
        NodePtr tail_;
        size_t size_;
        void copyElements(const Queue &);
};

template <typename T>
inline Queue<T>::Queue()
    :head_(NULL),
    tail_(NULL),
    size_(-1)
{
}

template <typename T>
inline Queue<T>::Queue(const Queue &other)
    :head_(NULL), 
    tail_(NULL),
    size_(-1)
{
    copyELements(other);
}

//前面的Queue还未处于类的内部？？？？
template <typename T>
inline Queue<T> &Queue<T>::operator=(const Queue &other)
{
    if(this != &other)
    {
        clear();
        copyElements(other);
    }
    return *this;
}

template <typename T>
inline void Queue<T>::copyElements(const Queue &other)
{
    for(NodePtr pt = other.head_; pt; pt = pt -> next_)
    {
        push(pt -> data_);//将other中的每个元素的副本push到这个Queue中
    }
}

template <typename T>
inline bool Queue<T>::isEmpty() const
{
    return head_ == NULL;
}

template <typename T>
inline void Queue<T>::push(const T &data)
{
    //NOde不是Queue类内部的类型，
    //所以，需要指定模板参数
    // NodePtr pt = new Node<T> (data);//等价与后面三行
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
inline void Queue<T>::clear()
{
    while(!isEmpty())
    {
        pop();
    }
}

template <typename T>
inline const T &Queue<T>::top() const 
{
    return head_ -> data_;
}

template <typename T>
inline size_t Queue<T>::getSize() const
{
    return size_;
}

template <typename T>
inline Queue<T>::~Queue()
{
    clear();
}

#endif  /*_QUEUE_H_*/
