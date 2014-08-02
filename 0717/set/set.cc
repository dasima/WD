#include <iostream>
#include <set>
using namespace std;

int main(int argc, const char *argv[])
{
    set<int> s;
    for(size_t ix = 0; ix != 9; ++ix)
    {
        s.insert(ix);
        s.insert(ix);
    }
    cout << s.size() << endl;

    s.insert(11);
    cout << s.size() << endl;

    return 0;
}
