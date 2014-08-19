#ifndef _TEXT_CORRECTOR_H_
#define _TEXT_CORRECTOR_H_

#include <string>
#include <map>


class TextCorrector
{
    public:
        TextCorrector(const std::string &);
        ~TextCorrector();
        void readFile(const std::string &);
        std::string textQuery(const std::string &);
    private:
        std::map<std::string, int> Dic_;

};

#endif  /*_TEXT_CORRECTOR_H_*/
