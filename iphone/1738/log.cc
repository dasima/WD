#include "../include/log.h"
#include "../include/lib/exception.h"
#include <iostream>
#include <fstream>
using namespace std;

Log::Log(const string &log_file)
    :Log_file_(log_file),
    Is_started_(false),
    Cond_(Mutex_),
    Thread_(bind(&Log::getLog, this))
{
    Thread_.start();
    cout << "1" << endl;
    Is_started_ = true;
}

void Log::stop()
{
    cout << "5" << endl;
    Is_started_ = false;
    Cond_.notifyAll();
    Thread_.join();
}

void Log::getLog()
{
    cout << "2" << endl;
    while(Is_started_)
    {
        MutexLockGuard lock(Mutex_);
        while(Is_started_ && Queue_.empty())
        {
            cout << "000" << endl;
            Cond_.wait();
        }
        string str;
        if(!Queue_.empty())
        {
            str = Queue_.front();
            Queue_.pop();
            cout << "41" << endl;
            writeToLog("hi");
            cout << "42" << endl;
            writeToLog(str);
        }
        else
        {
            writeToLog("server has stop");
        }
    }
}

void Log::addLog(const string &str)
{
    cout << "3" << endl;
    MutexLockGuard lock(Mutex_);
    Queue_.push(str);
    if(Queue_.size() == 1)
        Cond_.notify();
}

void Log::writeToLog(const string &log_file)
{
    cout << "4" << endl;
    ofstream of;
    of.open(Log_file_, ofstream::app);
    if(!of)
        throw Exception("open file failed");
    of << log_file << endl;
    of.close();

}
