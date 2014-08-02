#ifndef HANDLE_H_
#define HANDLE_H_ 
class Animal;

class Handle
{
    public:
        Handle();
        Handle(const Animal &);
        Handle(const Handle &);
        Handle &operator=(const Handle &);
        ~Handle();

        Animal *operator->();
        const Animal *operator->() const;
    private:
        Animal *ptr_;
};
#endif  /*HANDLE_H_*/
