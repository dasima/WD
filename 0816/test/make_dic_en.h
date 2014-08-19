#ifndef _MAKE_DIC_EN_H_
#define _MAKE_DIC_EN_H_

#include <iostream>
#include <string>
#include <vector>

class MakeDicEn
{
    public:
        MakeDicEn(const std::string &);
        void makeDicEn(const std::string &);
        
    private:
        std::vector<std::string> Lines_;
};

#endif  /*_MAKE_DIC_EN_H_*/
