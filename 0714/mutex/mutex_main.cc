#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
#include "mutex_lock.h"
using namespace std;

int main(int argc, const char *argv[])
{
    MutexLock lock;
    lock.lock();
    cout << "lock " << endl;

    lock.lock();
    cout << "lock2 " << endl;
    return 0;
}
