/********************************************************************
	Time:	  2015/10/26
	Filename: stlite_vector
	Author:	  dinglj
	
	Purpose:  vectorʵ��
*********************************************************************/
#ifndef _STLITE_VECTOR_H_
#define _STLITE_VECTOR_H_
#include "stlite_iterator.h"        //  iterator  
#include "stlite_alloc.h"           //  allocator
#include "stlite_uninitialized.h"   //  uninitialized_fill_n
#include "stlite_type_traits.h"
#include <crtdefs.h>                //  std::ptrdiff_t

#include <iostream>
using namespace STLite;

namespace STLite
{
    //////////////////////////////////////////////////////////////////////
    //  vectorIterator
    template<class T>
    class vectorIterator : public iterator<random_access_iterator<T, std::ptrdiff_t>, T>
    {
    private:
        T *m_ptr;
    
    //////////////////////////////////////////////////////////////////////
    //  construct, copy, assignment, destroy
    //  ע�⣬vectorIterator���������ڴ������ͷţ���������ԭʼָ���һ����װ
    //  ������Щ����������ʹ��Ĭ�ϵ�
    public:
        //  construct
        explicit vectorIterator(T *ptr = NULL) : m_ptr(ptr) {} 
        
        //  copy
        vectorIterator(const vectorIterator &vIter)
        {
            m_ptr = vIter.m_ptr;
        }

        // assignment
        vectorIterator & operator =(const vectorIterator &vIter)
        {
            if (this != &vIter)
            {
                m_ptr = vIter.m_ptr;
            }
            return *this;
        }

        //  destroy, do nothing,
        ~vectorIterator() { }
    //////////////////////////////////////////////////////////////////////
    //  defer
    public:
        reference operator *()      //    ������Ϊ��ֵ������ֵ
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
    //  �����ȡ����������
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

        difference_type operator +(const vectorIterator &lhs) const     //  �������ӷ�
        {
            return m_ptr + lhs.m_ptr;
        }
        //////////////////////////////////////////////////////////////////////
        vectorIterator & operator -=(difference_type n)
        {
            return *this += -n;    //  call operator +=(difference_type n)
        }

        vectorIterator operator -(difference_type n) const
        {
            vectorIterator temp = *this;    //  call operator -=(difference_type n)
            return temp -= n;
        }
        
        difference_type operator -(const vectorIterator &lhs) const     //  ����������
        {
            return m_ptr - lhs.m_ptr;
        }
        //////////////////////////////////////////////////////////////////////
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


    //////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////
    //  vector
    template<class T, class Alloc = allocator<T>>
    class vector
    {
    //////////////////////////////////////////////////////////////////////
    //  Ƕ���ͱ���
    public:
        typedef T               value_type;
        typedef T*              pointer;
        typedef T&              reference;
        typedef size_t          size_type;
        typedef std::ptrdiff_t  difference_type;

    //////////////////////////////////////////////////////////////////////
    //   �ڲ�����,  Ϊ�˷�����ԣ�������Ϊpublic
    public:
        pointer start;
        pointer finish;
        pointer end_of_storage;     //  ָ��洢�ռ��ĩβ
    
    //////////////////////////////////////////////////////////////////////
    //  iterator
    public:
        typedef vectorIterator<T> iterator;
    
    //////////////////////////////////////////////////////////////////////
    //  allocator
    typedef allocator<T> data_allocator;

    //////////////////////////////////////////////////////////////////////
    //  private member function
    private:
        pointer allocate(size_type n)
        {
            return data_allocator::allocate(n);
        }
        
        void deallocate()
        {
            data_allocator::deallocate(start, end_of_storage - start);
        }
        //////////////////////////////////////////////////////////////////////
        
        void allocate_and_fill(size_type n, const value_type &value)
        {
            start = allocate(n);
            uninitialized_fill_n(start, n, value);
            
            finish = start + n;
            end_of_storage = finish;
        }
        
        template<class InputIterator>
        void allocate_and_copy(InputIterator first, InputIterator last)
        {
             start = allocate(last - first);     //  ���ص���������
             finish = uninitialized_copy(first, last, start);
             end_of_storage = finish;
        }
        
        void destroy_and_deallocate()
        {
            if (start != end_of_storage)
            {
                destroy(start, finish); 
                deallocate();
            }
        }
        //////////////////////////////////////////////////////////////////////
        //  override vector_aux
        template<class Integer>
        void vector_aux(Integer n, const value_type &value, __true_type)
        {
            allocate_and_fill(n, value);
        }
        
        template<class InputIterator>
        void vector_aux(InputIterator first, InputIterator last, __false_type)
        {
            allocate_and_copy(first, last);
        }   

    //////////////////////////////////////////////////////////////////////
    //  construct
    public: 
        vector(): start(0), finish(0), end_of_storage(0) { }
        explicit vector(size_type n)
        {
            vector_aux(n, value_type(), __true_type());
        }
        vector(size_type n, const value_type &value)
        {
            vector_aux(n, value, __true_type());
        }
        template<class InputIterator>
        vector(InputIterator first, InputIterator last)     
        {
            typedef typename _is_integer<InputIterator>::is_integer is_integer;    //  ע�⣬��vector<size_type n, const value_type &value>����һ����Ҫ�жϲ�������
            vector_aux(first, last, is_integer());
        }
        
        //  copy
        vector(const vector &lhs)
        {
            allocate_and_copy(lhs.start, lhs.finish);
        }
    
        //  assignment, ע�⣬��ֵ��ʱ��Ҫ�ͷ�ԭ����ָ����ڴ�ռ�
        const vector & operator =(const vector &lhs)
        {
            //  ��ʼ���¿ռ�
            pointer new_start = allocate(lhs.finish - lhs.start);
            pointer new_finish = uninitialized_copy(lhs.start, lhs.finish, new_start);
            pointer new_end_of_storage = new_finish;
        
            //  �ͷ������ռ�
            destroy_and_deallocate();
    
            //  ��ʼ�������ռ�
            start = new_start;
            finish = new_finish;
            end_of_storage = new_end_of_storage;

            return *this;
        }
        //  destroy
        ~vector()
        {
            destroy_and_deallocate();
        }
    
}

#endif