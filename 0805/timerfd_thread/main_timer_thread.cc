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
    
    /*
     *1. 这里使用sleep函数是为了让读者清晰的看到程序的执行过程
    * 2.sleep(4),程序主进程会停留4秒，然后等待poll函数中设置的10秒，
    * 最后程序退出。
    *3. 其中，主进程执行主进程程序，一共4秒钟
    * 子进程执行子进程,时间为poll设置的10秒钟
    */
    //sleep(4);

    tt.cancelTimerThread();
    
    return 0;
}
