/********************************************************************
	Time:	  2015/10/23
	Filename: stlite_uninitialized
	Author:	  dinglj
	
	Purpose:  内存基本处理工具，配合construct，用于初始化内存,注意三个函数的返回值
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

using namespace STLite;

namespace STLite
{
    //////////////////////////////////////////////////////////////////////
    //  uninitialized_copy
    template<class InputIterator, class ForwardIterator>
    inline ForwardIterator uninitialized_copy_aux(InputIterator first, InputIterator last, ForwardIterator result, __true_type)
    {
    //    return std::copy(first, last, result);
       //   暂时用这个代替标准库std::copy()
        while (first != last)
        {
            *result++ = *first++;
        }
        return result;
    }

    template<class InputIterator, class ForwardIterator>
    inline ForwardIterator uninitialized_copy_aux(InputIterator first, InputIterator last, ForwardIterator result, __false_type)
    {
        while (first != last)
        {
            construct(&*result, *first);
            ++first;
            ++result;
        }
        return result;
    }

    template<class InputIterator, class ForwardIterator>
    inline ForwardIterator uninitialized_copy(InputIterator first, InputIterator last, ForwardIterator result)
    {
        //  先获取迭代器所指类型，然后获取类型属性，根据属性调用对应的函数
        typedef typename iterator_traits<InputIterator>::value_type value_type;
        //  cout << typeid(value_type).name() << endl;
        typedef typename __type_traits<value_type>::is_POD_type is_POD_type;
        return uninitialized_copy_aux(first, last, result, is_POD_type());
    }

    //  特化的const char *版本
    inline char *uninitialized_copy(const char *first, const char *last, char *result)
    {
        std::memmove(result, first, last - first);
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
        while (n > 0)
        {
            *first = value;
            --n;
            ++first;
        }

        return first;
    }

    template<class ForwardIterator, class Size, class T>
    inline ForwardIterator uninitialized_fill_n_aux(ForwardIterator first, Size n, const T &value, __false_type)
    {
        while (n > 0)
        {
            construct(&*first, value);
            --n;
            ++first;
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