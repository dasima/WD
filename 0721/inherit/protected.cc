#include<iostream>
using namespace std;

class Parent
{
    protected:
        string address_;
};

class Child:public Parent
{
    private:
        string school_;
    public:
        void test()
        {
            address_ = "shenzhen";
        }
};
int main(int argc, const char *argv[])
{
    
    return 0;
}
