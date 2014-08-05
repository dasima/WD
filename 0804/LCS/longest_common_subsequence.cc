#include <iostream>
#include <string>
#include <vector>
#include <string.h>
#include <stdlib.h>
using namespace std;

int longestCommonSubsequence(const string &A,
                            const string &B,
                            int i, 
                            int j)
{
    if(i == 0 || j == 0)
        return 0;
    if(A[i-1] == B[j-1])
        return longestCommonSubsequence(A, B, i-1, j-1) + 1;
    else
    {
        int t1 = longestCommonSubsequence(A, B, i-1, j);
        int t2 = longestCommonSubsequence(A, B, i, j-1);
        return t1 > t2 ? t1 : t2;
    }

}


int main(int argc, const char *argv[])
{
    string s1, s2;
    cin >> s1 >> s2;
    
    int a = longestCommonSubsequence(s1, s2, s1.length(), s2.length());
    cout << a << endl;
    a = longestCommonSubsequence(s1, s2, s1.size(), s2.size());
    cout << a << endl;
    //s1转换为字符数组后才能使用strlen
    a = longestCommonSubsequence(s1, s2, strlen(s1.c_str()), strlen(s2.c_str()));
    cout << a << endl;
    return 0;
}
