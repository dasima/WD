#ifndef BUFFER_H_
#define BUFFER_H_ 

#include "queue.h"
#include "mutual.h"
#include "condition.h"

class Buffer
{
    public:
        Buffer(size_t);
        ~Buffer();

        bool isEmpty() const;
        bool isFull() const;

        void produce(int data);
        int consume();
    private:
        Queue queue_;
        mutable Mutex mutex_;
        Condition full_;
        Condition empty_;
        size_t size_;
};

#endif  /*BUFFER_H_*/
