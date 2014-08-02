#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Student
{
    private:
        string name_;
        int age_;
        int score_;
    public:
        void setName(const string &name)
        {
            name_ = name;
        }
        const string &getName() const
        {
            return name_;
        }
        void setAge(int age)
        {
            age_ = age;
        }
        const int &getAge() const
        {
            return age_;
        }
        void setScore(int score)
        {
            score_ = score;
        }
        const int &getScore() const
        {
            return score_;
        }
        void print(ostream &os)
        {
            os << name_ << " " << age_ << " " << score_ << endl;
        }
};
int main(int argc, const char *argv[])
{
    Student s;
    s.setName("kobe");
    s.setAge(31);
    s.setScore(98);
    s.print(cout);
    return 0;
}
