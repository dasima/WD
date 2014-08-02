#include "consume_thread.h"
using namespace std;
void ConsumeThread::run()
{
    while(1)
    {
        cout << "consume a data " << endl;
        sleep(3);
    }
}
