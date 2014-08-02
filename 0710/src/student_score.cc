#include <iostream>
#include <string>
#include <vector>

using namespace std;

typedef struct _stu {
    string name_;
    float score_;
}stu;

int student_score(vector<stu> &vec, vector<stu> &names)
{
    stu stu1;
    int cnt = 0;
    cout << "input your name and score:" << endl;
    while(cin >> stu1.name_ >> stu1.score_)
    {
        vec.push_back(stu1);
        if(stu1.score_ >= 60)
        {
            ++cnt;
            names.push_back(stu1);
        }
    }
    return cnt;
}
int main(int argc, const char *argv[])
{
    vector<stu> vec;
    stu stu1;
    vector<stu> names;
    int cnt = 0;

    cnt = student_score(vec, names);
    cout << cnt << endl;

    for(vector<stu>::iterator it = names.begin(); it != names.end(); ++it)
    {
        cout << (*it).name_ << " ";    
    }
    cout << endl;
    return 0;
}
