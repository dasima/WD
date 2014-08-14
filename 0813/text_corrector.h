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
    friend bool operator < (Word a, Word b)
    {
        if(a.distance_ == b.distance_)
            return a.frequence_ < b.frequence_;//?
        else
            return a.distance_ > b.distance_;
    }

    std::string word_;
    int distance_;//距离
    int frequence_;//频率
};


class TextCorrector
{
    public:

        TextCorrector(const std::string &);
        void readFile(const std::string&);
        std::string textQuery(const std::string &);
        void buildIndex();
        void buildCache(const std::string &, const std::string &);
        std::set<std::string> searchFromCache(const std::string &);
        
    private:
        int editDistance(const std::string &,const std::string &);

        std::vector<std::string> lines_;
        std::map<std::string, int> Dic_;//词典库,用来存放单词和单词的相关信息 
        std::map<char, std::map<std::string, int> > index_;//suoyin
        std::priority_queue<Word> queue_;//youxian duilie
        std::unordered_map<std::string, std::set<std::string> > cache_;//huanxun

};

#endif  /*_TEXT_CORRECTOR_H_*/
