#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;
bool cmp(int a, int b)
{
    return a < b;
}
int main(int argc, const char *argv[])
{
    srand(1000);
    vector<int> vec;

    vec.push_back(rand() % 100);
    vec.push_back(rand() % 100);
    vec.push_back(rand() % 100);
    vec.push_back(rand() % 100);
    vec.push_back(rand() % 100);
    vec.push_back(rand() % 100);
    for(vector<int>::iterator it = vec.begin(); it != vec.end(); ++it){
        cout << *it << endl;    
    }
    cout << endl;
    
    sort(vec.begin(), vec.end(), cmp);
    for(vector<int>::iterator it = vec.begin(); it != vec.end(); ++it){
        cout << *it << endl;    
    }
    cout << endl;
}
