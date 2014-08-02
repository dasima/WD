#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Person
{
    public:
        Person()
            :id_(-1),
            name_(""),
            age_(0)
    {
    };
        Person(int id, const string &name, int age)
            :id_(id),
            name_(name),
            age_(age)
    {
    }
        bool operator<(const Person &other) const
        {
            return id_ < other.id_;
        }
        void print()
        {
            cout << "id_" << id_ << " name" << name_ << " age" << age_ << endl;
        }
    private:
        int id_;
        string name_;
        int age_;
};
int main(int argc, const char *argv[])
{
    vector<Person> vec;
    vec.push_back(Person(1, "zhao", 22));
    vec.push_back(Person(2, "liu", 32));

    sort(vec.begin(), vec.end());
    return 0;
}
