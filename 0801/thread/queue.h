#ifndef QUEUE_H_
#define QUEUE_H_ 
#include <stddef.h>
class Node
{
    friend class Queue;
    private:
        int data_;
        Node *next_;
};

typedef Node* NodePtr;
class Queue
{
    public:
        Queue();
        Queue(const Queue &other);
        ~Queue();
        Queue &operator=(const Queue &other);
        void push(int data);
        void pop();
        bool isEmpty() const;
        int top() const;
        void clear();
        size_t getSize() const;
    private:
        void copyElements(const Queue &other);
        NodePtr head_;
        NodePtr tail_;
        size_t size_;
};
#endif  /*QUEUE_H_*/
