#ifndef TEXT_QUERY_H
#define TEXT_QUERY_H 

#include <string>
#include <set>
#include <map>
#include <vector>
#include <queue>
#include <unordered_map>

struct candidate {
    friend bool operator < (candidate a, candidate b) {
        if(a.distance_ == b.distance_) {
            return a.frequence_ < b.frequence_;
        }else {
            return a.distance_ > b.distance_;
        }
    }

    std::string word_;
    int distance_;
    int frequence_;
};


class TextQuery
{
    public:
       // typedef std::vector<std::string>::size_type LineNo;
        typedef std::unordered_map<std::string, std::set<std::string> >HashWord;    //哈希
        TextQuery(const std::string &filename);
        void readFile(const std::string &filename);
        std::string runQuery(const std::string &word);//查询
       // std::string printResult(const std::string &word, const std::set<LineNo> &results) const;//
        void buildHashWord(const std::string &word, const std::string &candidate);//建立哈希表
        std::set<std::string> searchHashWord(const std::string &word);//查找哈希表
        void buildIndex(const std::map<std::string, int> &Dic_);//建立索引算法
    private:
        int editDistance(const char* word, const char* des_word);//编辑距离算法

        //std::vector<std::string> lines_; //存放每行的内容
        std::map<char, std::map<std::string, int> >indexOfWords_;//单词索引
        //std::map<std::string, std::set<LineNo> > wordMap_;  //单词以及他们出现的行号;
        std::priority_queue<candidate> candidate_;//优先级队列
        std::map<std::string, int> Dic;//词典库
        HashWord hash_word;//哈希表（缓存）
};



#endif  /*TEXT_QUERY_H*/
