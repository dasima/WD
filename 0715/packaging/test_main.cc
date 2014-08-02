#include "buffer.h"
#include "produce_thread.h"
#include "consume_thread.h"
#include "factory.h"
int main(int argc, const char *argv[])
{
    
    Factory fac(5, 3, 2);
    fac.start();
       
    /*
    Buffer buffer(5);
    ProduceThread p1(buffer);
    ProduceThread p2(buffer);
    ProduceThread p3(buffer);

    ConsumeThread c1(buffer);
    ConsumeThread c2(buffer);
    ConsumeThread c3(buffer);
    
    p1.start();
    p2.start();
    p3.start();

    c1.start();
    c2.start();
    c3.start();

    p1.join();
    p2.join();
    p3.join();
    c1.join();
    c2.join();
    c3.join();
*/
    return 0;
}
