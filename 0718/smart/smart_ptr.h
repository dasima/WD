#ifndef _SMART_PTR_H_
#define _SMART_PTR_H_ 

#include <iostream>
#define DISALLOW_COPY_AND_ASSIGN(TypeName)\
    TypeName(const TypeName&);\
    void operator=(const TypeName&)

class Animal{
    public: 
        Animal()
        {
            std::cout << "construct....." << std::endl;
        }
        ~Animal()
        {
            std::cout << "deconstruct...." << std::endl;
        }
        void run()
        {
            std::cout << "running...." << std::endl;
        }
        
};
class SmartPtr
{
    public:
        SmartPtr(Animal *ptr);
        ~SmartPtr();

        Animal &operator*();
        const Animal &operator*() const;

        Animal *operator->();
        const Animal *operator->() const;
    private:
            Animal *ptr_;
            DISALLOW_COPY_AND_ASSIGN(SmartPtr);

};
#endif  /*_SMART_PTR_H_*/
