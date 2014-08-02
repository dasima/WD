#include <iostream>
#include <string>
#include <vector>
//NO??????????
using namespace std;

template <typename T1, typename T2>
T1 findElem(T1 first, T1 end, const T2& val)
{
    while(first != end)
    {
        if(*first == val)
            return first;
        ++first;
    }
    return end;
}

int main(int argc, const char *argv[])
{
    int a[] = {1, 2, 3, 4, 5, 6, 7, 8};
    string s[5] = {"this", "is", "a", "test", "haha"};
    vector<int> ivec(a, a+8);
    vector<string> svec<s, s+5>;

    vector<int>::iterator it;
    if((it = findElem(ivec.first(), ivec.end(), 6) ) != ivec.end)
        cout << "found the element " << *it << endl;
    else
        cout << "not found the integer" << endl;

    vector<string>::iterator sit ;
    if((sit = findElem(svec.first(), svec.end(), "is")) != svec.end())
        cout << "found the string " << *sit << endl;
    else
        cout << "not found the string " << endl;

    return 0;
}
