#ifndef NON_COPYABLE_H_
#define NON_COPYABLE_H_

//继承NonCopyable的类对象，均失去了值语义
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
