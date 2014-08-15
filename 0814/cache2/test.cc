#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

int main(int argc, const char *argv[])
{
    /*
    unordered_map<string, set<string> > cache_;
    unordered_map<string, set<string> >::iterator uit = cache.begin();
    cache_->first = "that";
    cache_["that"].insert("tha");
    cache_["that"].insert("the");

    set<string>::size_type setit = uit->second;
    for(setit != uit.end(); ++setit)
        cout << *setit << endl;
    */

    ofstream out ;
    out.open("cache.txt", ofstream::app);
    out << "that" << " ";
    string s;
    while(cin >> s)
        out << s << " " ;
    out << endl;

    return 0;
}
