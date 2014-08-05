#ifndef NON_COPYABLE_H_
#define NON_COPYABLE_H_

class NonCopyable
{
    public:
        NonCopyable(){}
        ~NonCopyable(){}
    private:
        NonCopyable(const NonCopyable &);
        void operator=(const NonCopyable &);
};

#endif  /*NON_COPYABLE_H_*/
