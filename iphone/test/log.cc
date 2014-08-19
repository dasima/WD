#include "log.h"
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
    Is_started_ = true;
}

void Log::stop()
{
    Is_started_ = false;
    Cond_.notifyAll();
    Thread_.join();
}

void Log::getLog()
{
    while(Is_started_)
    {
        MutexLockGuard lock(Mutex_);
        while(Is_started_ && Queue_.empty())
            Cond_.wait();
        string str;
        if(!Queue_.empty())
        {
            Queue_.pop();
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
    MutexLockGuard lock(Mutex_);
    Queue_.pop();
    if(Queue_.size() == 1)
        Cond_.notify();
}

void Log::writeToLog(const string &str)
{
    ofstream of;
    of.open(Log_file_, ofstream::app);
    if(!of)
        throw Exception("open file failed");
    of << str << endl;
    of.close();

}
