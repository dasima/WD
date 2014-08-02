#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main(int argc, const char *argv[])
{
    int a;
    vector<int> vec;
    cin >> a;
    while(a % 10)
    {
        vec.push_back(a % 10);
        a = a/10;
    }
    for(vector<int>::iterator it = vec.begin(); it != vec.end(); ++it){
        cout << *it ;    
    }
    cout << endl;

    return 0;
}
