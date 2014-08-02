#include "thread_pool.h"
#include <assert.h>
#include <stdlib.h>

void queue_init(Queue *Q)
{
    Q -> head_ = NULL;
    Q -> tail_ = NULL;
    Q -> size_ = 0;
}

BOOL queue_is_empty(const Queue *Q)
{
    return Q -> head_ == NULL;
}

void queue_pop(Queue *Q)
{
    assert(!queue_is_empty(Q));
    Pnode pt = Q -> head_;
    Q -> head_ = Q->head_ -> next_;
    free(pt);
    --Q -> size_;
}

void queue_clear(Queue *Q)
{
    while(!queue_is_empty(Q))
        queue_pop(Q);
}

void queue_destroy(Queue *Q)
{
    queue_clear(Q);
}

void queue_push(Queue *Q, Task_t data)
{
    Pnode pt = (Pnode)malloc(sizeof(Qnode));
    pt -> data_ = data;
    pt -> next_ = NULL;
    if(queue_is_empty(Q))
    {
        Q -> head_ = Q -> tail_ = pt;
    }else
    {
        Q -> tail_ -> next_ = pt;
        Q -> tail_ = pt;
    }
    ++Q -> size_;
}

Task_t queue_top(const Queue *Q)
{
    assert(!queue_is_empty(Q));
    return Q -> head_ -> data_;
}

size_t queue_get_size(const Queue *Q)
{
    return Q -> size_;
}
