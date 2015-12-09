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
    inline ForwardIterator 
    uninitialized_copy_aux(InputIterator first, InputIterator last, ForwardIterator result, 
                           input_iterator_tag, __true_type)
    {
        for (; first != last; ++first, ++result)
        {
            *result = *first;
        }
        return result;
    }

    template<class RandomAccessIterator, class ForwardIterator>
    inline ForwardIterator
    uninitialized_copy_aux(RandomAccessIterator first, RandomAccessIterator last, ForwardIterator result,
                           random_access_iterator_tag, __true_type)
    {
        int n = last - first;
        for (; n > 0; --n, ++first, ++result)
        {
            *result = *first;
        }
        return result;
    }

    template<class InputIterator, class ForwardIterator>
    inline ForwardIterator
    uninitialized_copy_aux(InputIterator first, InputIterator last, ForwardIterator result,
                           input_iterator_tag, __false_type )
    {
        for (; first != last; ++first, ++result)
        {
            construct(&*result, *first);
        }
        return result;
    }

    template<class RandomAccessIterator, class ForwardIterator>
    inline ForwardIterator 
    uninitialized_copy_aux(RandomAccessIterator first, RandomAccessIterator last, ForwardIterator result,
                           random_access_iterator_tag, __false_type)
    {
        int n = last - first;
        for (; n > 0; --n, ++first, ++result)
        {
            construct(&*result, *first);
        }
        return result;
    }

    template<class InputIterator, class ForwardIterator>
    inline ForwardIterator uninitialized_copy(InputIterator first, InputIterator last, ForwardIterator result)
    {
        typedef typename iterator_traits<InputIterator>::iterator_category category;
        //  first, get the VALUE_TYPE of the InputIterator
        //  second, determine whether the VALUE_TYPE is POD_type or not.
        typedef typename iterator_traits<InputIterator>::value_type value_type;
        //  cout << typeid(value_type).name() << endl;
        typedef typename __type_traits<value_type>::is_POD_type is_POD_type;

        return uninitialized_copy_aux(first, last, result, category(), is_POD_type());
    }

    //  specialization for char *
    inline char *uninitialized_copy(const char *first, const char *last, char *result)
    {
        std::memmove(result, first, last - first);  //  memmove(result, first, n)
        return result + (last - first);
    }

    //////////////////////////////////////////////////////////////////////
    //  uninitialized_copy_backward
    template<class BidirectionalIterator1, class BidirectionalIterator2>
    inline BidirectionalIterator2
    uninitialized_copy_backward_aux(BidirectionalIterator1 first, BidirectionalIterator1 last,
                                    BidirectionalIterator2 result, 
                                    bidirectional_iterator_tag, __true_type)
    {
        while (first != last)
        {
            --last;
            --result;
            *result = *last;
        }
        return result;
    }

    template<class RandomAccessIterator, class BidirectionalIterator>
    inline BidirectionalIterator
    uninitialized_copy_backward_aux(RandomAccessIterator first, RandomAccessIterator last,
                                    BidirectionalIterator result,  
                                    random_access_iterator_tag, __true_type)
    {
        int n = last - first;
        while (n > 0)
        {
            --last;
            --result;
            *result = *last;
            --n;
        }
        return result;
    }

    template<class BidirectionalIterator1, class BidirectionalIterator2>
    inline BidirectionalIterator2
    uninitialized_copy_backward_aux(BidirectionalIterator1 first, BidirectionalIterator1 last,
                                    BidirectionalIterator2 result,
                                    bidirectional_iterator_tag, __false_type)
    {
        while (first != last)
        {
            --last;
            --result;
            construct(&*result, *last);
        }

        return result;
    }

    template<class RandomAccessIterator, class BidirectionalIterator>
    inline BidirectionalIterator
    uninitialized_copy_backward_aux(RandomAccessIterator first, RandomAccessIterator last,
                                    BidirectionalIterator result, 
                                    random_access_iterator_tag, __false_type)
                
    {
        int n = last - first;
        while (n > 0)
        {
            --last;
            --result;
            construct(&*result, *last);
            --n;
        }
        return result;
    }

    template<class BidirectionalIterator1, class BidirectionalIterator2>
    inline BidirectionalIterator2
    uninitialized_copy_backward(BidirectionalIterator1 first, BidirectionalIterator1 last, BidirectionalIterator2 result)
    {
        typedef typename iterator_traits<BidirectionalIterator1>::iterator_category category;

        typedef typename iterator_traits<BidirectionalIterator1>::value_type value_type;
        typedef typename __type_traits<value_type>::is_POD_type is_POD_type;
        return uninitialized_copy_backward_aux(first, last, result, category(), is_POD_type());
    }

    //////////////////////////////////////////////////////////////////////
    //  uninitialized_fill
    template<class ForwardIterator, class T>
    inline void uninitialized_fill_aux(ForwardIterator first, ForwardIterator last, const T &value,
                                       forward_iterator_tag, __true_type)
    {
        for (; first != last; ++first)
        {
            *first = value;
        }
    }

    template<class RandomAccessIterator, class T>
    inline void uninitialized_fill_aux(RandomAccessIterator first, RandomAccessIterator last, const T &value,
                                       random_access_iterator_tag, __true_type)
    {
        int n = last - first;
        for (; n > 0; --n, ++first)
        {
            *first = value;
        }
    }

    template<class ForwardIterator, class T>
    inline void uninitialized_fill_aux(ForwardIterator first, ForwardIterator last, const T &value, 
                                       forward_iterator_tag, __false_type)
    {
                    
        for (; first != last; ++first)
        {
            construct(&*first, value);
        }
    }

    template<class RandomAccessIterator, class T>
    inline void uninitialized_fill_aux(RandomAccessIterator first, RandomAccessIterator last, const T &value,
                                       random_access_iterator_tag, __false_type)
    {
        int n = last - first;
        for (; n > 0; --n, ++first)
        {
            construct(&*first, value);
        }
    }

    template<class ForwardIterator, class T>
    inline void uninitialized_fill(ForwardIterator first, ForwardIterator last, const T &value)
    {
        typedef typename iterator_traits<ForwardIterator>:iterator_category category;
        typedef typename __type_traits<iterator_traits<ForwardIterator>::value_type>::is_POD_type is_POD_type;
        
        uninitialized_fill_aux(first, last, value, category(), is_POD_type());
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

    //////////////////////////////////////////////////////////////////////
    //  uninitialzied_fill_n_backward
    template<class BidirectionalIterator, class Size, class T>
    inline BidirectionalIterator
    uninitialized_fill_n_backward_aux(BidirectionalIterator pos, Size n, const T &value, __true_type)
    {
        for (;n > 0; --n)
        {
            --pos;
            *pos = value;
        }
        return pos;
    }

    template<class BidirectionalIterator, class Size, class T>
    inline BidirectionalIterator 
    uninitialized_fill_n_backward_aux(BidirectionalIterator pos, Size n, const T &value, __false_type)
    {
        for (; n > 0; --n)
        {
            --pos;
            construct(&*pos, value);
        }
        return pos;
    }

    template<class BidirectionalIterator, class Size, class T>
    inline BidirectionalIterator uninitialized_fill_n_backward(BidirectionalIterator pos, Size n, const T & value)
    {
        typedef typename iterator_traits<BidirectionalIterator>::value_type value_type;
        typedef typename __type_traits<value_type>::is_POD_type is_POD_type;
        return uninitialized_fill_n_backward_aux(pos, n, value, is_POD_type());
    }
}
#endif