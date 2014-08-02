#include<iostream>
using namespace std;

class Parent
{
    public: 
        string address_;
};
class Child:public Parent
{
    public:
        string school_;
};
int main(int argc, const char *argv[])
{
    Child c;
    c.school_ = "aaa";
    c.address_ = "nanshan";
    return 0;
}
