#ifndef _INDEX_H_
#define _INDEX_H_

#include "../include/word.h"
#include <string>
#include <map>
#include <set>
#include <stdint.h>

class Index
{
    public:
        Index()
            :Index_(26)
        {}
        void buildIndex(const std::map<std::string, Word> &);
        //void createIndexCn(const std::unordered_map<std::string, Word> &);

    private:
            std::map<uint32_t, std::set<Word> > Index_;

};

#endif  /*_INDEX_H_*/
