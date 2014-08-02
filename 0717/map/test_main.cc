#include "animal.h"
using namespace std;
int main(int argc, const char *argv[])
{
    Animal A("lion");
    A.add("beijing", "elphant");
    A.add("shanghai", "dog");
    A.add("guangzhou", "cat");
    A.add("shenzhen", "tiger");
    A.add("nanjing", "wolf");
    A.add("wuhan", "horse");
    cout << "金融风波来了" << endl;
    A.run();
    return 0;
}
