#include "queue.hpp"

using namespace std;

int main(int argc, const char *argv[])
{
    Queue<string> q;
    q.push("hello:");
    q.push("world:");
    q.push("china:");
    q.push("shen:");
    
    //输出
    while(!q.isEmpty())
    {
        cout << q.top() << endl;
        q.pop();
    }
    return 0;
}
