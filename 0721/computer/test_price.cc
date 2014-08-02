#include "computer.h"
#include "dell.h"
#include "lenovo.h"
#include "mac.h"
using namespace std;
int main(int argc, const char *argv[])
{
    Computer *tt;
    Dell d;
    Lenovo l;
    Mac m;
    tt -> price();
    cout << "--------------------" << endl;
    tt = &d;
    tt -> price();
    cout << "--------------------" << endl;
    tt = &l;
    tt -> price();
    cout << "--------------------" << endl;
    tt = &m;
    tt -> price();
    return 0;
}
