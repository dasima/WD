#include "computer.h"
using namespace std;
double Computer::count_ = 0;
Computer::Computer()
    :price_(0)
{
}

Computer::~Computer()
{
}

double Computer::price()
{
    cout << "computer price: " << count_ << endl;
}
