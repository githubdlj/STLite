/********************************************************************
	Time:	  2015/11/01
	Filename: stl_algorithm
	Author:	  dinglj
	
	Purpose:  STLite algorithm
*********************************************************************/

#ifndef _STLITE_ALGORITHM_H_
#define _STLITE_ALGORITHM_H_

#include <string.h>         //  for memmove

#include "commom_header_files.h"
#include "stlite_iterator.h"

//////////////////////////////////////////////////////////////////////
namespace STLite
{
    //  fill, fill_n
    //  fill is equal to uninitialized_fill(first, last, __true_type)
    template<class ForwardIterator, class T>
    inline void fill(ForwardIterator first, ForwardIterator last, const T &value)
    {
        for (; first != last; ++first)
        {
            *first = value;
        }
    }

    template<class OutputIterator, class Size, class T>
    inline OutputIterator fill_n(OutputIterator first, Size n, const T &value)
    {
        for (; n > 0; --n, ++first)
        {
           *first = value;
        }
        return first;
    }
    //////////////////////////////////////////////////////////////////////
    //  copy

    //  copy_aux for InputIterator
    template<class InputIterator, class OutputIterator>
    inline OutputIterator copu_aux(InputIterator first, InputIterator last, OutputIterator result, input_iterator_tag)
    {
        for (; first != last; ++first, ++result)
        {
            *result = *first;
        }
        return result;
    }

    //  copy_aux for RandomAccessIterator
    //  it has a higher performance than InputIterator
    template<class RandomAccessIterator, class OutputIterator>
    inline OutputIterator copy_aux(RandomAccessIterator first, RandomAccessIterator last, OutputIterator result,
                                   random_access_iterator_tag )
    {
        typedef typename iterator_traits<RandomAccessIterator>::difference_type distance;

        for (distance n = last - first; n > 0; --n)
        {
            *result = *first;
            ++first;
            ++result;
        }
        return result;
    }

    //  copy, generalization
    template<class InputIterator, class OutputIterator>
    inline OutputIterator copy(InputIterator first, InputIterator last, OutputIterator result)
    {
        typedef typename iterator_traits<InputIterator>::iterator_category category;
        return copy_aux(first, last, result, category());
    }

    //  copy, specialization for const char *
    inline char * copy(const char *first, const char *last, char *result)
    {
        const std::ptrdiff_t n = last - result;
        std::memmove(result, first, n);      //  memmove(destination, source, n)
        return result + n;
    }

    //////////////////////////////////////////////////////////////////////
    //  copy_backward

    //  copy_backward_aux for BidirectionalIterator
    template<class BidirectionalIterator1, class BidirectionalIterator2>
    inline BidirectionalIterator2 
    copy_backward_aux(BidirectionalIterator1 first, BidirectionalIterator1 last, BidirectionalIterator2 result, 
                      bidirectional_iterator_tag)
    {
        while (first != last)
        {
            *(--result) == *(--last); 
        }
        return result;
    }

    //  copy_backward_aux for RandomAccessIterator
    template<class RandomAccessIterator, class BidirectionalIterator>
    inline BidirectionalIterator
    copy_backward_aux(RandomAccessIterator first, RandomAccessIterator last, BidirectionalIterator result, 
                      random_access_iterator_tag) 
    {
        typedef typename iterator_traits<RandomAccessIterator>::difference_type distance;

       for (distance n = last - first; n > 0; --n)
       {
            *(--result) = *(--last);
       }
       return result;
    }

    //  copy_backward, generalization
    template<class BidirectionalIterator1, class BidirectionalIterator2>
    inline BidirectionalIterator2
    copy_backward(BidirectionalIterator1 first, BidirectionalIterator1 last, BidirectionalIterator2 result)
    {
        typedef typename iterator_traits<BidirectionalIterator1>::iterator_category category;
        return copy_backward(first, last, result, category());
    }

    //  copy_backward, specialization
    inline char * copy_backward(const char *first, const char *last, char *result)
    {
        const std::ptrdiff_t n = last - first;
        std::memmove(result - n, first, n);
        return result - n;
    }

    //////////////////////////////////////////////////////////////////////
    //  print, print the container's elements
    template<class InputIterator>
    void print(InputIterator first, InputIterator last)
    {
        for (; first != last; ++first)
        {
            cout << *first << "\t";
        }
        cout << endl;
    }
}
#endif
