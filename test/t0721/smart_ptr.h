#ifndef _SMART_PTR_H
#define _SMART_PTR_H 
#include <iostream>

class Student
{
    public:
        Student(int id, const std::string &name)
            :id_(id), name_(name)
        {
            std::cout << "create student" << endl;
        }

        ~Student()
        {
            std::cout << "destroy Student" << std::endl;
        }

        void print()
        {
            std::cout << id_ << "  " << name_ << std::endl;
        }
    private:
        int id_;
        string name_;
};

class SmartPtr
{
    public:
        SmartPtr();
        SmartPtr(Student *ptr);
        ~SmartPtr();

        void resetPtr(Student *ptr);
        const Student *getPtr() const;

        Student *operator->();
        const Student *operator->() const;

        Student &operator*();
        const Student &operator*() const;

    private:
        Student *ptr_;
        SmartPtr(const SmartPtr &);
        SmartPtr &operator=(const SmartPtr &);
};
#endif  /*_SMART_PTR_H*/
