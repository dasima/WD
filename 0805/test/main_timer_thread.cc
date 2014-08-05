#include "timer_thread.h"
#include <iostream>
using namespace std;

void test()
{
    cout << "timer_thread_test..." << endl;
}

int main(int argc, const char *argv[])
{
    /*Timer t;
    t.setTimer(3, 1);
    t.setTimerCallback(test);
    t.runTimer();*/
    TimerThread tt;
    tt.setTimer(3, 1);
    printf("1\n");
    tt.setTimerCallback(test);
    printf("2\n");
    tt.startTimerThread();//poll触发了计时器？
    printf("3\n");
    
    sleep(10);

    tt.cancelTimerThread();
    
    return 0;
}
