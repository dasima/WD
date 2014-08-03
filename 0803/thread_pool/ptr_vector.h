#ifndef PTR_VECTOR_H_
#define PTR_VECTOR_H_
#include "non_copyable.h"
#include <vector>
//写这个类是为了存放线程
//这里用到多重继承
template <typename T>
class PtrVector : public std::vector<T*>,
                  private NonCopyable
{
    public:
        ~PtrVector()
        {
            clear();
        }
        void push_back(T *val)
        {
            std::vector<T*>::push_back(val);
        }
        void clear()
        {
            typename std::vector<T*>::iterator it;
            for(it = std::vector<T*>::begin(); it != std::vector<T*>::end(); ++it)
                delete *it;//*it is T*
            //base clear , free 
            std::vector<T*>::clear();
        }
};

#endif  /*PTR_VECTOR_H_*/
