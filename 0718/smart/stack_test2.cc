#include <iostream>
#include <string>
#include <vector>
#include "smart_ptr.h"
#include <stdexcept>
using namespace std;
int main(int argc, const char *argv[])
{
    try
    {
        //Animal a;
        Animal *ps = new Animal[3];
        throw runtime_error("animal");
        //这里不会执行14行，造成内存泄露
        dezlete[] ps;
        
    }catch(runtime_error &e)
    {
        cout << e.what() << endl;
    }

    return 0;
}
