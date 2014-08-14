#ifndef _TEXT_QUERY_H_
#define _TEXT_QUERY_H_

#include <set>
#include <string>
#include <map>
#include <vector>

class TextQuery
{
    public:
        TextQuery(const std::string &);
        void readFile(const std::string &);
        std::string runQuery(const std::string &) const;
        //int shortestLength(const std::string &, const std::string &, int, int);
       // std::string wordCompare(const std::string &);

    private:
        std::vector<std::string> lines_;//存放每行的内容
        std::map<std::string, std::set<LineNo> > wordMap_;//单词和它出现的行号的映射
        std::map<std::string, int> dic_;//存放符合编辑距离的单词

};


#endif  /*_TEXT_QUERY_H_*/
