#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Person
{
    public:
        Person()
            :id_(-1), name_(""), age_(-1)
        {
            
        }
       Person(int id,
               string name,
               int age)
       {
            id_ = id;
            name_ = name;
            age_ = age;
       }
    private:
        int id_;
        string name_;
        int age_;
};
int main(int argc, const char *argv[])
{
    Person p;
    return 0;
}
