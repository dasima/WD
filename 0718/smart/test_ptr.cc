#include <iostream>
#include <string>
#include <vector>
#include "smart_ptr.h"
using namespace std;
int main(int argc, const char *argv[])
{
    SmartPtr ptr(new Animal);
    (*ptr).run();

    ptr->run();

    return 0;
}
