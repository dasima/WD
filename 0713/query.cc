#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <stdexcept>
using namespace std;
ifstream &open_file(ifstream &is, const string &file_name)
{
    is.close();
    is.clear();
    is.open(file_name.c_str());
    return is;
}
struct Query
{
    vector<string> words;
    void read_file(const string &file_name)
    {
        ifstream infile;
        if(!open_file(infile, file_name))
        {
            throw std::runtime_error("file open failed");
        }
        words.clear();
        string word;
        while(infile >> word)
        {
            words.push_back(word);
        }
        infile.close();
       infile.clear();
    }
    vector<string> queryWord(const string &word)
    {
        vector<string> result;
        for(vector<string>::iterator it = words.begin(); it != words.end(); ++it){
            string::size_type pos = it -> find(word);
            if(pos != string::npos)
            {
                result.push_back(*it);
            }
        }
        return result;
    }
};
int main(int argc, const char *argv[])
{
    string filename = "in.txt";
    Query Q;
    Q.read_file(filename);
    string word;
    while(cin >> word)
    {
        vector<string> res = Q.queryWord(word);
        cout << "size = " << res.size() << endl;
        for(vector<string>::iterator it = res.begin(); it != res.end(); ++it){
            cout << *it << endl;    
        }
    }

    return 0;
}
