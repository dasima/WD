#include "queue.h"
int main(int argc, const char *argv[])
{
    Queue q;
    init(&q);
    push(&q, 3);
    push(&q, 5);
    assert(!is_empty(&q));
    assert(get_size(&q) == 2);

    int t = top(&q);
    printf("%d\n", t);
    pop(&q);
    t = top(&q);
    printf("%d\n", t);
    pop(&q);
    assert(is_empty(&q));
    
    return 0;
}
