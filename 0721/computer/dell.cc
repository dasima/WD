#include "dell.h"
#include "computer.h"

using namespace std;

double Dell::price()
{
    count_ = count_ + 4000;
    cout << "after buy a dell count = " << "--------" << count_ << endl; 
}
