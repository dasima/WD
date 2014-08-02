#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main(int argc, const char *argv[])
{
    int a;
    cout << "good = " << cin.good() << endl;
    //cin的good为假的时候，对cin进行bool检测，得到的是false,为真时，得到的是1
    cout << (bool)cin << endl;
    while(cin >> a)
        cout << a << endl;

    cout << "eof = " << cin.eof() << endl;
    cout << "fail = " << cin.fail() << endl;

    string s = "hi";
    cin >> s;
    cout << s << endl;

    return 0;
}
