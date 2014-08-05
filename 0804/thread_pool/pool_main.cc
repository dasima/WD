#include "thread_pool.h"
#include <iostream>
#include <stdlib.h>
#include <unistd.h>
using namespace std;

void func(int i)
{
    cout << i << endl;
}

int main(int argc, const char *argv[])
{
    ThreadPool pool(5, 3);
    pool.start();

    srand(time(NULL));
    while(1)
    {
        pool.addTask(bind(&func, rand() % 100));
        sleep(3);
    }

    pool.stop();
    return 0;
}
