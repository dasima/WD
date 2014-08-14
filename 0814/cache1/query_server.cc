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
    //这里先设置计时器
    timer_.setTimer(1, 5);//5秒调用一次“往缓存文件中写缓存”函数
    timer_.setTimerCallback(bind(&QueryServer::writeCache, this));
}

void QueryServer::start()
{
    /*
     *这里执行顺序为：
     *1.执行计时器函数调用，
     *  1.1调用writeCache()函数，
     *  1.2writeCache()函数调用textCorrector类中的writeCacheFile()函数
     *     这里会根据计时器设置的时间，5秒调用一次writeCacheFile()函数，进行缓存的更新
     *
     *2.执行pool_.start()函数
     *
     *3.执行server_.start()函数
     *  3.1这里server_.start()函数会在有客户端连接时调用onConnection()函数，
     *  3.2程序执行过程中(即客户端往服务器端发送消息过程中)，调用onMessage()函数,
     *    这里onMessage()函数会调用runQuery()函数，
     *    而runQuery()函数会调用textCorrector类中的textQuery()函数，
     *    然后执行textQuery()函数，进行单词查询和纠错输出
     *  3.3如果有客户端退出，程序就调用onClose()函数
     *
     */
    timer_.startTimerThread();
    pool_.start();
    server_.start();
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
    cout << conn->getPeerAddr().toIp() << " port "
        << conn->getPeerAddr().toPort() << " close" << endl; 
    conn->shutdown();
}
