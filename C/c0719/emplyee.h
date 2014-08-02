#ifndef _EMPLYEE_H_
#define _EMPLYEE_H_ 
#include <iostream>
class Emplyee{
    public:
        Emplyee();
        ~Emplyee();
        Emplyee(std::string name);
        Emplyee(const Emplyee &emp);
        Emplyee &operator=(const Emplyee &emp);
    private:
        std::string name_;
        int id_;
        static int count_; 
};

#endif  /*_EMPLYEE_H_*/
