#include <iostream>
#include <string>
#include <vector>
#include <string.h>
#include <stdlib.h>
using namespace std;

/*
 *i和j分别表示两个字符串的字符数量
 *参数i表示字符串A的前i个字符, j表示B的前j个字符
 */
int emon[100][100];
int longestCommonSubsequence(const string &A,
                            const string &B,
                            int i, 
                            int j)
{
    if(i == 0 || j == 0)
        return 0;
    if(emon[i][j] != -1)//计算过,直接返回备忘录的内容
        return emon[i][j];
    if(A[i-1] == B[j-1])
    {
        emon[i][j] = longestCommonSubsequence(A, B, i-1, j-1) + 1;
        return emon[i][j];
    }
    else
    {
        int t1 = longestCommonSubsequence(A, B, i-1, j);
        int t2 = longestCommonSubsequence(A, B, i, j-1);
        emon[i][j] = t1 > t2 ? t1 : t2;
        return emon[i][j];
    }
}


int main(int argc, const char *argv[])
{
    string s1, s2;
    cin >> s1 >> s2;
    
    memset(emon, -1, sizeof(emon));
    int a = longestCommonSubsequence(s1, s2, s1.length(), s2.length());
    cout << a << endl;
    a = longestCommonSubsequence(s1, s2, s1.size(), s2.size());
    cout << a << endl;
    //s1转换为字符数组后才能使用strlen
    a = longestCommonSubsequence(s1, s2, strlen(s1.c_str()), strlen(s2.c_str()));
    cout << a << endl;
    return 0;
}
