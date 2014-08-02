#include "smart_ptr.h"

using namespace std;

int main(int argc, const char *argv[])
{
    SmartPtr p(new Animal);
    cout << "............" << endl;
    p.resetPtr(NULL);
    cout << "............" << endl;
    if(!p)
        cout << "p == NULL" << endl;

    p.resetPtr(new Animal);
    cout << "............" << endl;
    if(p)
        cout << "p != NULL" << endl;
    return 0;
}
