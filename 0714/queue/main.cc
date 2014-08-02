#include "queue.h"
#include <iostream>
#include <stdlib.h>
#include <assert.h>
using namespace std;
int main(int argc, const char *argv[])
{
    srand(time(NULL));
    Queue Q;
    Q.push(rand() % 100);
    Q.push(rand() % 100);
    Q.push(rand() % 100);
    Q.push(rand() % 100);
    Q.push(rand() % 100);
    std::cout << Q.getSize() << std::endl;

    Q.pop();
    Q.pop();
    Q.pop();
    cout << Q.getSize() << endl;

    Q.pop();
    Q.pop();
    cout << Q.getSize() << endl;
    return 0;
}
