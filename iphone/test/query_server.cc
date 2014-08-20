//#include "../include/query_server.h"
#include "query_server.h"
#include "../include/string_utils.h"
#include <sstream>
#include <time.h>
using namespace std;
using namespace std::placeholders;

QueryServer::QueryServer(GetConfig *config) 
    :server_(InetAddress(config->getPort())), 
    query_(config->getEnDicFile(), config->getCnDicFile()),
    pool_(1000, config->getCacheNum()),
    cache_(config->getCacheFile()),
    log_(config->getLogFile())
{
    cout << "c" << endl;
    server_.setConnection(bind(&QueryServer::onConnection, this, _1));
    server_.setMessage(bind(&QueryServer::onMessage, this, _1));
    server_.setClose(bind(&QueryServer::onClose, this, _1));
    //这里先设置计时器
    timer_.setTimer(1, 10);//5秒调用一次“往缓存文件中写缓存”函数
    timer_.setTimerCallback(bind(&QueryServer::writeCache, this));
}

QueryServer::~QueryServer()
{
    pool_.stop();
    log_.stop();
   // caches_.stop();
}

void QueryServer::start()
{
    cout << "start" << endl;
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
    //caches_.start();
    pool_.start();
    server_.start();
    log_.addLog("server start .\n");
    timer_.cancelTimerThread();
}

void QueryServer::onConnection(const TcpConnectionPtr &conn)
{
    cout << "connect" << endl;
    cout << conn->getPeerAddr().toIp() << " port "
        << conn->getPeerAddr().toPort() << " on" <<endl;
    ostringstream oss;
    oss << conn->getPeerAddr().toIp() << " port "
        << conn->getPeerAddr().toPort() << " on ";
    string log_msg = oss.str();
    time_t timep;
    time(&timep);
    log_msg += asctime(gmtime(&timep));
    cout << "----" <<log_msg << endl;
    log_.addLog(log_msg);
    conn->sendString("Welcome, please input the word:\r\n");
}

void QueryServer::onMessage(const TcpConnectionPtr &conn)
{
    cout << "message" << endl;
    string word(conn->receiveString());
    word.substr(word.length() - 2);
    
    ostringstream oss;
    oss << conn->getPeerAddr().toIp() << " port "
        << conn->getPeerAddr().toPort() << "---";
    string log_msg = oss.str();
    log_msg += word;
    time_t timep;
    time(&timep);
    log_msg += asctime(gmtime(&timep));
    log_.addLog(log_msg);

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
    //cout << string_utils::getLenOfUTF8(word[0]) << endl;
    //这里处理中文有问题--- ok
    vector<uint32_t> vec;
    string_utils::parseUTF8String(word, vec);
    string res = query_.textQuery(word);
    conn->sendString(res + "\r\n");
}

void QueryServer::writeCache()
{
    //这里需要等待5秒中才能把缓存中内容写入磁盘文件
    cout << "wcache" << endl;
    cache_.writeToCacheFile("../data/cache.txt");
}

void QueryServer::onClose(const TcpConnectionPtr &conn)
{
    cout << "close" << endl;
    cout << conn->getPeerAddr().toIp() << " port "
        << conn->getPeerAddr().toPort() << " close" << endl; 
    ostringstream oss;
    oss << conn->getPeerAddr().toIp() << " port "
        << conn->getPeerAddr().toPort() << " close"; 
    string log_msg = oss.str();
    time_t timep;
    time(&timep);
    log_msg += asctime(gmtime(&timep));
    log_.addLog(log_msg);
    conn->shutdown();
   
}
