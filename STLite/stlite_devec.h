/********************************************************************
	Time:	  2015/12/02
	Filename: devec
	Author:	  dinglj
	
	Purpose:  the improvement of the vector
              it can improve the efficiency when inserting the elements close to the head 
*********************************************************************/
#ifndef _STLITE_DEVEC_H_
#define _STLITE_DEVEC_H_

#include "common_header_files.h"
#include "stlite_iterator.h"
#include "stlite_alloc.h"
#include "stlite_type_traits.h"

//////////////////////////////////////////////////////////////////////
namespace STLite
{
    template<class T, class Alloc>
    class devec;

    template<class T, class Alloc = allocator<T> >
    struct devecIterator : public iterator<random_access_iterator_tag, T>
    {
    //  member data
        T *m_ptr;
        int index;      //  because the m_ptr is circular, so it need a index.
        devec<T, Alloc> *vec;  //  the devecIterator should know the devec's attribute, so it should contain the *vec.
    
    //  member function
       
    };

    template<class T, class Alloc = allocator<T> >
    class devec
    {
    //  type
    public:
        typedef T               value_type;
        typedef T*              pointer;
        typedef T&              reference;
        typedef size_t          size_type;
        typedef std::ptrdiff_t  difference_type;
    //////////////////////////////////////////////////////////////////////
    //  member data
    //  private:    //  in order to test, declare them public temporary
    public:
        //  memory space
        pointer start_of_storage;
        pointer end_of_storage;

        //  object space
        int start;
        int end;
    //////////////////////////////////////////////////////////////////////
    //  iterator 
    public:
        typedef devecIterator<T> iterator;
    //////////////////////////////////////////////////////////////////////
    //  allocator
    public:
        typedef allocator<T> data_allocator;

    //////////////////////////////////////////////////////////////////////
    //  member function
    //  constructor, copy constructor, assignment, destructor
    private:
        void allocate_and_fill(size_type n, const value_type &value)
        {
            start_of_storage = data_allocator::allocate(n);
            uninitialized_fill_n(start_of_storage, n, value);
            end_of_storage = start_of_storage + n;
            
            start = 0;
            end = start + n;
        }

        template<class ForwardIterator>
        void allocate_and_copy(ForwardIterator first, ForwardIterator last, forward_iterator_tag)
        {
            difference_type n = distance(first, last);
            start_of_storage = data_allocator::allocate(n);
            uninitialized_copy(first, last, start_of_storage);
            end_of_storage = start_of_storage + n;

            start = 0;
            end = start + n;
        }

    private:
        template<class Integer>
        void devec_aux(Integer n, const value_type &value, __true_type)
        {
            allocate_and_fill(n, value);
        }

        template<class InputIterator>
        void devec_aux(InputIterator first, InputIterator last, __false_type)
        {
            typedef iterator_traits<InputIterator>::iterator_category category;
            allocate_and_copy(first, last, category());
        }

    public:
        devec() : start_of_storage(0), end_of_storage(0), start(0), end(0) {}

        devec(int n, const value_type &value)
        {
            devec_aux(n, value, __true_type());
        }

        devec(int n)
        {
            devec_aux(n, value_type());
        }

        template<class InputIterator>
        devec(InputIterator first, InputIterator last)
        {
            typedef typename _is_integer<InputIterator>::is_integer is_integer;
            devec_aux(first, last, is_integer());
        }
    };
}

#endif