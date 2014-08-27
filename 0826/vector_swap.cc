#include <iostream>
#include <vector>
/*
 *交换两个vector容器中的内容，
 *两个容器大小可不一样
 */

using namespace std;
int main(int argc, const char *argv[])
{
    vector<int> foo(3, 9);
    vector<int> bar(5, 8);
    foo.swap(bar);

    cout << "foo: " ;
    for(unsigned int i = 0; i != foo.size(); ++i)
        cout << ' ' << foo[i];
    cout << endl;

    cout << "bar: " ;
    for(auto vit = bar.begin(); vit != bar.end(); ++vit)
        cout << ' ' << *vit;
    cout << endl;

    return 0;
}
