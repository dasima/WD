#include "timer.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;

void func()
{
    cout << "timer...callback..." << endl;
}

int main(int argc, const char *argv[])
{
    Timer t;
    t.setTimer(3, 1);
    t.setTimerCallback(func);
    t.runTimer();
    return 0;
}
