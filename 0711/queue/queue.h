#ifndef QUEUE_H_
#define QUEUE_H_ 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
typedef struct q_node
{
    int data;
    struct q_node *next;
}q_node, *p_node;
typedef struct
{
    p_node head_;
    p_node tail_;
    size_t size;
}Queue;
void init(Queue *q);
int is_empty(const Queue *q);
int top(const Queue *q);
void push(Queue *q, int data);
void pop(Queue *q);
void clear(Queue *q);
void destroy(Queue *q);
int get_size(const Queue *q);
#endif  /*QUEUE_H_*/
