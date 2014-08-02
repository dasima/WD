#include <iostream>

using namespace std;

template <typename T>
int compare(const T &t1, cosnt T &t2)
{
    if(t1 < t2) return -1;
    if(t1 > t2) return 1;
    return 0;
}

int main(int argc, const char *argv[])
{
    cout << compare("hi", "world") << endl;
    return 0;
}
