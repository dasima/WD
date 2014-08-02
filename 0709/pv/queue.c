#include "queue.h"
void init(Queue *q)
{
    q -> head_ = NULL;
    q -> tail_ = NULL;
    q -> size_ = 0;
}
int is_empty(const Queue *q)
{
    return q -> head_ == NULL;
}
int top(const Queue *q)
{
    assert(!is_empty(q));
    return q -> head_ -> data_;
}
void push(Queue *q, int data)
{
    p_node pt = (p_node)malloc(sizeof(q_node));
    pt -> data_ = data;
    pt -> next_ = NULL;
    if(is_empty(q))
    {
        q -> head_ = q -> tail_ = pt;
    }
    else
    {
        q -> tail_ -> next_ = pt;
        q -> tail_ = pt;
    }
    ++q -> size_;
}
void pop(Queue *q)
{
    assert(!is_empty(q));
    p_node pt = q -> head_;
    q -> head_ = q -> head_ -> next_;
    free(pt);
    --q -> size_;
}
void destroy(Queue *q)
{
    clear(q);
}
void clear(Queue *q)
{
    while(!is_empty(q))
    {
        pop(q);
    }
}
int get_size(const Queue *q)
{
    return q -> size_;
}
