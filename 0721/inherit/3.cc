#include <iostream>

class Parent{
    public:
        Parent()
        {}
        Parent(int id, 
                string name,
                int age)
            :id_(id),
            name_(name),
            age_(age)
    {
    }
        void set(int id, const string &name, int age)
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
class Child{
    public:
        Child()
        {
            
        }
        void set(int id, const string &name, int age, const string &school)
        {
            id_ = id;
            name_ = name;
            age_ = age;
            school_ = school;
        }
    private:
        string school_;
        
};
int main(int argc, const char *argv[])
{
    Child cl;
    cl.set(1, "zhao", 22);
    return 0;
}
