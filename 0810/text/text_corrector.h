#ifndef _TEXT_CORRECTOR_H_
#define _TEXT_CORRECTOR_H_

#include <map>
#include <string>
#include <set>
#include <vector>
#include <queue>

struct Word
{
    bool operator<(const Word &other)
    {
        if(distance_ == other.distance_)
            return frequence_ < other.frequence_;//?
        else
            return distance_ > other.distance_;
    }

    std::string word_;
    int distance_;//距离
    int frequence_;//频率
    int is_set_;
};


class TextCorrector
{
    public:
        typedef std::vector<std::string>::size_type LineNo;

        TextCorrector(const std::string &);
        std::string textQuery(const std::string &);
        void readFile(const std::string &);
        std::string searchFromFile(const std::map<std::string, Word> &);
        void buildIndex();
        bool isIndex(const std::string &, const std::string &);
        
    private:
        int editDistance(const std::string &,const std::string &);

        std::vector<std::string> lines_;
        std::map<std::string, Word> Dic_;//词典库,用来存放单词和单词的相关信息 
        std::vector<std::set<std::string> > index_;//下标索引

};

#endif  /*_TEXT_CORRECTOR_H_*/
