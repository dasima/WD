#include <iostream>
#include <string>
#include <vector>

using namespace std;
int main(int argc, const char *argv[])
{
    vector<string> vec;
    string word;
    while(cin >> word)
    {
        vec.push_back(word);
    }

    cout << endl;
    for(vector<string>::iterator it = vec.begin(); it != vec.end(); ++it){
        cout << *it << endl;    
    }
    cout << endl;
    return 0;
}
