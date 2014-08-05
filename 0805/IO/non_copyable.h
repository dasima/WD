#ifndef _NON_COPYABLE_H_
#define _NON_COPYABLE_H_

class NonCopyable
{
    public:
        NonCopyable(){}
        ~NonCopyable(){}
    private:
        NonCopyable(const NonCopyable &);
        void operator=(const NonCopyable &);
        
};

#endif  /*_NON_COPYABLE_H_*/
