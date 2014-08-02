#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main(int argc, const char *argv[])
{
    vector<int> vec;
    for(int i = 0; i != 20; ++i)
    {
        vec.push_back(i);
    }

    for(vector<int>::iterator it = vec.begin(); it != vec.end(); ++it){
        if(*it % 2 == 0)
        {
          //  vec.erase(it);
          //???
            it = vec.erase(it);
        }
    }

    for(vector<int>::iterator it = vec.begin(); it != vec.end(); ++it){
        cout << *it << endl;    
    }
    return 0;
}
