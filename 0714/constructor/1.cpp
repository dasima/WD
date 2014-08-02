#include <iostream>
#include <string>
#include <vector>
using namespace std;
class Student
{
    public:
        Student(const string name,
                int age,
                int score)
        {
            name_ = name;
            age_ = age;
            score_ = score;
        }
        void print() const 
        {
            cout << name_ << " " << age_ << " " << score_ << endl;
        }

    private:
        string name_;
        int age_;
        int score_;       
};
int main(int argc, const char *argv[])
{
    Student s("zhangsan", 29, 98);
    s.print();

//    Student const s1;
  //  s1.print();
    return 0;
}
