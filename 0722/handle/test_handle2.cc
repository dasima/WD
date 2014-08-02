#include "handle.h"
#include "animal.h"

using namespace std;

int main(int argc, const char *argv[])
{
    Dog d;
    Handle h(d);
    h-> display();
    return 0;
}
