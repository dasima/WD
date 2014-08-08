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
    tt.setTimerCallback(test);
    tt.startTimerThread();//poll触发了计时器
    
    sleep(4);

    tt.cancelTimerThread();
    
    return 0;
}
