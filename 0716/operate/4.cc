#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <map>
#include <set>
#include <algorithm>
using namespace std;
int main(int argc, const char *argv[])
{
    vector<string> vec;
    vec.push_back("bj");
    vec.push_back("sh");
    vec.push_back("gz");
    for(vector<string>::iterator it = vec.begin(); it != vec.end(); ++it){
        cout << *it << endl;    
    }

    vec.erase(vec.begin(), vec.end());
   // vec.pop_back();
    for(vector<string>::iterator it = vec.begin(); it != vec.end(); ++it){
        cout << *it << endl;    
    }
    return 0;
}
