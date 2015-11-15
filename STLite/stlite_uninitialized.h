/********************************************************************
	Time:	  2015/10/23
	Filename: stlite_uninitialized
	Author:	  dinglj
	
	Purpose:  construct objects
              1. uninitialized_copy(first, last, result)
              2. uninitialized_fill(first, last, value)
              3. uninitialized_fill_n(first, n, value)
*********************************************************************/
#ifndef _STLITE_UNINITIALIZED_H_
#define _STLITE_UNINITIALIZED_H_

#include <string.h>     //  for memmove

#include "stlite_construct.h"
#include "stlite_iterator.h"
#include "stlite_type_traits.h"

//////////////////////////////////////////////////////////////////////
namespace STLite
{
    //////////////////////////////////////////////////////////////////////
    //  uninitialized_copy
    template<class InputIterator, class ForwardIterator>
    inline ForwardIterator uninitialized_copy_aux(InputIterator first, InputIterator last, ForwardIterator result, __true_type)
    {
        for (; first != last; ++first, ++result)
        {
            *result = *first;
        }
        return result;
    }

    template<class InputIterator, class ForwardIterator>
    inline ForwardIterator uninitialized_copy_aux(InputIterator first, InputIterator last, ForwardIterator result, __false_type)
    {
        for (; first != last; ++first, ++result)
        {
            construct(&*result, *first);
        }
        return result;
    }

    template<class InputIterator, class ForwardIterator>
    inline ForwardIterator uninitialized_copy(InputIterator first, InputIterator last, ForwardIterator result)
    {
        //  first, get the VALUE_TYPE of the InputIterator
        //  second, determine whether the VALUE_TYPE is POD_type or not.
        typedef typename iterator_traits<InputIterator>::value_type value_type;
        //  cout << typeid(value_type).name() << endl;
        typedef typename __type_traits<value_type>::is_POD_type is_POD_type;
        return uninitialized_copy_aux(first, last, result, is_POD_type());
    }

    //  specialization for char *
    inline char *uninitialized_copy(const char *first, const char *last, char *result)
    {
        std::memmove(result, first, last - first);  //  memmove(result, first, n)
        return result + (last - first);
    }

    //////////////////////////////////////////////////////////////////////
    //  uninitialized_fill
    template<class ForwardIterator, class T>
    inline void uninitialized_fill_aux(ForwardIterator first, ForwardIterator last, const T &value, __true_type)
    {
        for (; first != last; ++first)
        {
            *first = value;
        }
    }

    template<class ForwardIterator, class T>
    inline void uninitialized_fill_aux(ForwardIterator first, ForwardIterator last, const T &value, __false_type)
    {
        for (; first != last; ++first)
        {
            construct(&*first, value);
        }
    }

    template<class ForwardIterator, class T>
    inline void uninitialized_fill(ForwardIterator first, ForwardIterator last, const T &value)
    {
        typedef typename __type_traits<iterator_traits<ForwardIterator>::value_type>::is_POD_type is_POD_type;
        uninitialized_fill_aux(first, last, value, is_POD_type());
    }

    //////////////////////////////////////////////////////////////////////
    //  uninitialized_fill_n
    template<class ForwardIterator, class Size, class T>
    inline ForwardIterator uninitialized_fill_n_aux(ForwardIterator first, Size n, const T &value, __true_type)
    {
        for (; n > 0; --n, ++first)
        {
            *first = value;
        }

        return first;
    }

    template<class ForwardIterator, class Size, class T>
    inline ForwardIterator uninitialized_fill_n_aux(ForwardIterator first, Size n, const T &value, __false_type)
    {
        for (; n > 0; --n, ++first)
        {
            construct(&*first, value);
        }

        return first;
    }

    template<class ForwardIterator, class Size, class T>
    inline ForwardIterator uninitialized_fill_n(ForwardIterator first, Size n, const T & value)
    {
        typedef typename __type_traits<iterator_traits<ForwardIterator>::value_type>::is_POD_type is_POD_type;
        return uninitialized_fill_n_aux(first, n, value, is_POD_type());
    }
}
#endif