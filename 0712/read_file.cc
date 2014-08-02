#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <stdexcept>
using namespace std;
ifstream &open_file(ifstream &is, const string &filename)
{
    is.close();
    is.clear();
    is.open(filename.c_str());
    return is;
}

int main(int argc, const char *argv[])
{
    ifstream infile;
    string inname = "in.txt";
    if(!open_file(infile, inname))
    {
        throw std::runtime_error("file open failed");
    }
    vector<string> lines;
    string line;
    vector<string> words;
    while(getline(infile, line))
    {
        lines.push_back(line);
        istringstream ss(line);
        string word;
        while(ss >> word)
        {
            words.push_back(word);
        }
    }
    cout << "size " << lines.size() << endl;
    for(vector<string>::iterator it = lines.begin(); it != lines.end(); ++it)
    {
        cout << *it << endl;    
    }

    cout << "words size " << words.size() << endl;
    for(vector<string>::iterator it = words.begin(); it != words.end(); ++it){
        cout << *it << endl;    
    }

    infile.close();
    return 0;
}
