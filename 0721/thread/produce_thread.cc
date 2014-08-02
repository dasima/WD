#include "thread.h"
#include "produce_thread.h"
using namespace std;
void ProduceThread::run()
{
    int data;
    while(1)
    {
        data = rand() % 100;
        cout << "produce a data -----" << data << endl;
        sleep(1);
    }
}
