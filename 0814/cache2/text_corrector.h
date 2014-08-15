#ifndef _TEXT_CORRECTOR_H_
#define _TEXT_CORRECTOR_H_

#include <map>
#include <string>
#include <set>
#include <vector>
#include <queue>
#include <unordered_map>

struct Word
{
    bool operator < (const Word &other) const
    {
        if(distance_ == other.distance_)
            return frequence_ < other.frequence_;//?
        else
            return distance_ > other.distance_;
    }

    std::string word_;
    int distance_;//距离
    int frequence_;//频率
};


class TextCorrector
{
    public:

        TextCorrector(const std::string &);
        ~TextCorrector();
        void readFile(const std::string&);//读取系统文件
        std::string textQuery(const std::string &);//查询函数
        void buildIndex();//建立词典索引
        void buildCache(const std::string &, const std::string &);//建立缓存
        std::set<std::string> searchFromCache(const std::string &);//从缓存中查询
        void readCacheFile();//读取缓存文件
        void writeCacheFile();//写入缓存文件
        
    private:
        int editDistance(const std::string &,const std::string &);

        std::vector<std::string> lines_;//用来存放文件中一行字符串
        std::map<std::string, int> Dic_;//词典库,用来存放单词和单词的相关信息 
        std::map<char, std::map<std::string, int> > index_;//索引
        std::priority_queue<Word> queue_;//优先队列
        std::unordered_map<std::string, std::set<std::string> > cache_;//缓存
        std::unordered_map<std::string, std::set<std::string> > cache_txt_;//缓存文件与更新后的缓存之间的中间过渡

};

#endif  /*_TEXT_CORRECTOR_H_*/
