#ifndef _ANIMAL_H_
#define _ANIMAL_H_ 
#include <iostream>

class Animal
{
    public:
        virtual ~Animal(){}
        virtual void display() const = 0;
        virtual Animal *copy() const = 0;
};

class Cat : public Animal
{
    public:
        void display() const 
        {
            std::cout << "Cat" << std::endl;
        }
        Cat *copy() const
        {
            return new Cat(*this);
        }
};

class Dog : public Animal 
{
    public:
        void display() const
        {
            std::cout << " Dog" << std::endl;
        }
        Dog *copy() const
        {
            return new Dog(*this);
        }
};

class Bear : public Animal
{
    public:
        void display() const
        {
            std::cout << "bear" << std::endl;
        }
        Bear *copy() const
        {
            return new Bear(*this);
        }
};
#endif  /*_ANIMAL_H_*/
