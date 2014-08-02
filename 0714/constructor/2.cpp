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
            :name_(name), age_(age), score_(score)
        {
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

    //可调用构造函数，而构造函数不用为const
    Student const s2("zhang", 23, 87);
    s2.print();
    return 0;
}
