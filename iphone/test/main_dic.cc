#include "../include/text_corrector.h"

#include <iostream>

using namespace std;

int main(int argc, const char *argv[])
{
    TextCorrector tc("../data/dic_en.txt", "../data/dic_cn.txt");
    cout << "a" << endl;
    string word;
    while(cin >> word)
    {
        cout << "b" << endl;
        tc.textQuery(word);
    }
    return 0;
}
