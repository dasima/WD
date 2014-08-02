#ifndef _ANIMAL_H_
#define _ANIMAL_H_ 
#include <map>
#include <string>
#include <iostream>
class Animal{
    public:
        Animal(const std::string &king);
        void add(const std::string &city, const std::string &agent);
        std::string search(const std::string &city) const;
        void run();
    private:
        std::map<std::string, std::string> group_;
        std::string king_;                              
};

#endif  /*ANIMAL_H_*/
