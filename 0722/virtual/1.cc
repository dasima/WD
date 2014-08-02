#include <iostream>

using namespace std;

class Animal
{
    public:
        
        virtual void run() = 0;
};
class Cat : public Animal
{
    public:
        void run()
        {
            cout << "cat" << endl;
        }
};
int main(int argc, const char *argv[])
{
    Animal *pa = new Cat;
    pa -> run();
    delete pa;

    return 0;
}
