#ifndef _TEXT_CORRECTOR_H_
#define _TEXT_CORRECTOR_H_

#include <string>
#include <map>
#include "../include/word.h"


class TextCorrector
{
    public:
        TextCorrector(const std::string &, const std::string &);
        ~TextCorrector();
        void readFileEn(const std::string &);
        void readFileCn(const std::string &);
        std::string textQuery(const std::string &);
        std::string enQuery(const std::string &);
        std::string cnQuery(const std::string &);
    private:
        std::map<std::string, Word> Dic_en_;
        std::map<std::string, Word> Dic_cn_;

};

#endif  /*_TEXT_CORRECTOR_H_*/
