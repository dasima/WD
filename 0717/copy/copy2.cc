#include <iostream>
#include <string>
using namespace std;

class Student
{
    public:
        Student()
            :name_("none"), age_(0), score_(0)
    {}
        Student(const string &name, int age, int score)
            :name_(name),
            age_(age),
            score_(score)
    {
    }
        void debug()
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
    Student s1("zhao", 22, 98);
    s1.debug();
    
    Student s2;
    s2.debug();
    return 0;
}
