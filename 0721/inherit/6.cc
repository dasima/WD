#include<iostream>
using namespace std;

class Parent
{
    public:
        void set(const string &address)
        {
            address_ = address;
        }
        void print() const
        {
            cout << " " << address_<< endl;
        }
    private: 
        string address_;
};
class Child:public Parent
{
    public:
        string school_;
        void set(const string &school)
        {
            school_ = school;
        }
};
int main(int argc, const char *argv[])
{
    Child c;
    c.school_ = "aaa";
    c.Parent::set("shenzhen");
    c.print();
    return 0;
}
