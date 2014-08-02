#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;
class Person
{
    public:
        Person()
            :id_(0),
            name_(""),
            age_(0)
    {

    }
        Person(int id, const string &name, int age)
            :id_(id),
            name_(name),
            age_(age)
    {

    }
        bool operator<(const Person &p) const
        {
            return id_ < p.id_;
        }
        void print()
        {
            cout << "id_ = " << id_ << endl;
        }
        ~Person()
        {
             
        }
    private:
        int id_;
        string name_;
        int age_;

};
int main(int argc, const char *argv[])
{
    vector<Person> vec;
    vec.push_back(Person(1, "zhang", 23));
    vec.push_back(Person(2, "zhan", 32));
    vec.push_back(Person(3, "zha", 29));
    sort(vec.begin(), vec.end());
    return 0;
}
