#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main(int argc, const char *argv[])
{
    vector<int> vec;
    vec.push_back(9);
    vec.push_back(99);
    cout << "size of vec :" << vec.size() << endl;

    for(vector<int>::size_type ix = 0; ix != vec.size(); ++ix)
    {
        cout << vec[ix] << endl;
    }
    
    for(vector<int>::iterator iter = vec.begin(); iter != vec.end(); ++iter)
    {
        cout << *iter << endl;
    }

    return 0;
}
