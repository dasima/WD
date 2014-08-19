#ifndef _MAKE_DICT_CN_H_
#define _MAKE_DICT_CN_H_

#include <iostream>
#include "../cppjieba/src/MixSegment.hpp"
#define LOGGER_LEVEL LL_WARN

class MakeDictCn
{
    public:
        MakeDictCn();
        void cut(const CppJieba::ISegment&, const char* const);
        void makeDic();
    private:

};

#endif  /*_MAKE_DICT_CN_H_*/
