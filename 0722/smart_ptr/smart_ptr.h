#ifndef SMART_PTR_H_
#define SMART_PTR_H_ 
#include <iostream>
class Animal
{
    public:
        Animal()
        {
            std::cout << "Animal..." << std::endl;
        }
         ~Animal()
         {
            std::cout << "~Animal..." << std::endl;
         }

};

class SmartPtr
{
    public:
        SmartPtr();
        explicit SmartPtr(Animal *ptr);
        ~SmartPtr();
        void resetPtr(Animal *ptr);
        const Animal *getPtr() const;
        Animal &operator*();
        const Animal &operator*() const;
        Animal *operator->();
        const Animal *operator->() const;
        //这里提供了对象到bool类型的转化
        operator bool() const
        {
            return ptr_;
        }
    private:
        Animal *ptr_;
        SmartPtr(const Animal &);
        void operator=(const SmartPtr &);//???
};
#endif  /*SMART_PTR_H_*/
