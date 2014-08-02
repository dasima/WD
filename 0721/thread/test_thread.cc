#include "thread.h"
#include "produce_thread.h"
#include "consume_thread.h"
int main(int argc, const char *argv[])            
{
    Thread *t1, *t2;
    ProduceThread pt;
    ConsumeThread ct;

    t1 = &pt;
    t2 = &ct;
    t1 -> start();
    t2 -> start();

    t1 -> join();
    t2 -> join();
    
    return 0;
}
