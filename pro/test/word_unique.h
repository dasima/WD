#ifndef _WORD_UNIQUE_H_
#define _WORD_UNIQUE_H_

#include <echo/rio.h>
#include <vector>
#include <iostream>
#include "../lib/cppjieba/src/ISegment.hpp"

class WordUnique
{
    public:
        WordUnique();
        void getDoc();
        void cutWord(const ISegment &, const char * const);
        void makeCut(const string &);
    private:
        //Rio Rio_;
        std::vector<std::string> Vec_;
};

#endif  /*_WORD_UNIQUE_H_*/
