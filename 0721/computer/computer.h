#ifndef _COMPUTER_H_
#define _COMPUTER_H_ 
#include <iostream>
class Computer{
    public:
        Computer();
        virtual double price();
        virtual ~Computer();
    protected:
        double price_;
        static double count_;
};
#endif  /*_COMPUTER_H_*/
