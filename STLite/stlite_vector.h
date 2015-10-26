/********************************************************************
	Time:	  2015/10/26
	Filename: stlite_vector
	Author:	  dinglj
	
	Purpose:  vector实现
*********************************************************************/
#ifndef _STLITE_VECTOR_H_
#define _STLITE_VECTOR_H_
#include "stlite_iterator.h"        //  iterator  
#include <crtdefs.h>                //  std::ptrdiff_t
#include <iostream>
using namespace STLite;

namespace STLite
{
    template<class T>
    class vectorIterator : public iterator<random_access_iterator<T, std::ptrdiff_t>, T>
    {
    private:
        T *m_ptr;
    
    //////////////////////////////////////////////////////////////////////
    //  construct, copy, assignment, destroy
    public:
        explicit vectorIterator(T *ptr = NULL) : m_ptr(ptr) {} 
        vectorIterator(const vectorIterator &vIter)
        {
            m_ptr = vIter.m_ptr;
        }
        vectorIterator & operator =(const vectorIterator &vIter)
        {
            if (this != &vIter)
            {
                m_ptr = vIter.m_ptr;
            }
            return *this;
        }
    //////////////////////////////////////////////////////////////////////
    //  defer
    public:
        reference operator *()      //    可以作为左值或者右值
        {
            return *m_ptr;
        }
        pointer operator ->()
        {
            return m_ptr;
        }
    //////////////////////////////////////////////////////////////////////
    //  ++,--
    public:
        vectorIterator & operator ++()
        {
            m_ptr++;
            return *this;
        }
        vectorIterator operator ++(int)
        {
            vectorIterator temp = *this;
            ++(*this);
            return temp;
        }

        vectorIterator & operator --()
        {
            m_ptr--;
            return *this;
        }
        vectorIterator operator --(int)
        {
            vectorIterator temp = *this;
            --(*this);
            return temp;
        }
    //////////////////////////////////////////////////////////////////////
    //  随机存取迭代器操作
    public:
        vectorIterator & operator +=(difference_type n)
        {
            m_ptr += n;
            return *this;
        }

        vectorIterator operator +(difference_type n) const
        {
            vectorIterator temp = *this;    //  call operator +=(difference_type n)
            return temp += n;
        }

        vectorIterator & operator -=(difference_type n)
        {
            *this += -n;    //  call operator +=(difference_type n)
        }

        vectorIterator operator -(difference_type n) const
        {
            vectorIterator temp = *this;    //  call operator -=(difference_type n)
            return temp -= n;
        }
    
        reference operator [](difference_type n) const
        {
            return *(*this + n);
        }
    //////////////////////////////////////////////////////////////////////
    //  operator ==, !=
    public:
        bool operator ==(const vectorIterator &lhs) const
        {
            return m_ptr == lhs.m_ptr;
        }

        bool operator !=(const vectorIterator &lhs) const
        {
            return !(*this == lhs);
        }
    };
}

#endif
