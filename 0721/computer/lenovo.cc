#include "computer.h"
#include "lenovo.h"
using namespace std;
double Lenovo::price()
{
    count_ = count_ + 5000;
    cout << "after buy a lenovo count = " << "------ " << count_ << endl;
}
