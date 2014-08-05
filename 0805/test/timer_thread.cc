#include "timer_thread.h"
#include <iostream>
using namespace std;

void TimerThread::setTimer(int value, int interval)
{
    timer_.setTimer(value, interval);
}

void TimerThread::setTimerCallback(const TimerCallback &tc)
{
    cout << "setTimerCallback..." << endl;
    timer_.setTimerCallback(tc);
    thread_.setCallback(bind(&Timer::runTimer, &timer_));//bind();把Timer的函数指针传进来
}

void TimerThread::startTimerThread()
{
    thread_.start();
}

void TimerThread::cancelTimerThread()
{
    timer_.cancelTimer();
    thread_.join();
}
