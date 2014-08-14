#include "query_server.h"
using namespace std;
using namespace std::placeholders;

QueryServer::QueryServer(const InetAddress &addr, 
                       const std::string &filename)
    :server_(addr), 
    query_(filename),
    pool_(1000, 4)
{

    server_.setConnection(bind(&QueryServer::onConnection, this, _1));
    server_.setMessage(bind(&QueryServer::onMessage, this, _1));
    server_.setClose(bind(&QueryServer::onClose, this, _1));
}

void QueryServer::start()
{

    pool_.start();
    server_.start();
    timer_.setTimer(5, 10);
    timer_.setTimerCallback(bind(&QueryServer::writeCache, this));
    timer_.startTimerThread();
    sleep(300);
    timer_.cancelTimerThread();
}

void QueryServer::onConnection(const TcpConnectionPtr &conn)
{
    cout << conn->getPeerAddr().toIp() << " port "
        << conn->getPeerAddr().toPort() << endl;
    conn->sendString("Welcome, please input the word:\r\n");
}

void QueryServer::onMessage(const TcpConnectionPtr &conn)
{
    string word(conn->receiveString());
    word.substr(word.length() - 2);
    pool_.addTask(bind(&QueryServer::runQuery, this, word, conn));
}

void QueryServer::runQuery(const string &s, const TcpConnectionPtr &conn)
{
    string word = s;
    if(word.substr(word.size()-2, 2) == "\r\n")
    {
        word.erase(word.size()-1);//???erase
        word.erase(word.size()-1);
    }
    string res = query_.textQuery(word);
    conn->sendString(res + "\r\n");
}

void QueryServer::writeCache()
{
    query_.writeCacheFile();
}

void QueryServer::onClose(const TcpConnectionPtr &conn)
{
    //加了这一行
  //  pool_.addTask(bind(&QueryServer::writeCache, this));
    cout << conn->getPeerAddr().toIp() << " port "
        << conn->getPeerAddr().toPort() << " close" << endl; 
    conn->shutdown();
}
