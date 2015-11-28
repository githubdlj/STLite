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
    inline OutputIterator copy_aux(InputIterator first, InputIterator last, OutputIterator result, input_iterator_tag)
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
    //  reverse
    template<class BidirectionalIterator>
    void reverse_aux(BidirectionalIterator first, BidirectionalIterator last, bidirectional_iterator_tag)
    {
        while (first != last)
        {
            if(--last == first)     //  if the range's length is odd.
                break;
            std::swap(*first, *last);
            ++first;
        }
    }

    template<class RandomAccessIterator>
    void reverse_aux(RandomAccessIterator first, RandomAccessIterator last, random_access_iterator_tag)
    {
        while (first < last)    //  only the RandomAccessIterator supports operator <
        {
            --last;
            std::swap(*first, *last);
            ++first;
        }
    }

    template<class BidirectionalIterator>
    void reverse(BidirectionalIterator first, BidirectionalIterator last)
    {
        typedef typename iterator_traits<BidirectionalIterator>::iterator_category category;
        reverse_aux(first, last, category());
    }

    //////////////////////////////////////////////////////////////////////
    //  adjacent_find
    template<class ForwardIterator, class BinaryPredicate>
    ForwardIterator adjacent_find(ForwardIterator first, ForwardIterator last, BinaryPredicate BinaryPred)
    {
        if (first == last)
        {
            return last;
        }

        ForwardIterator next = first;
        ++next;
        for (; next != last; ++next)
        {
            if (!BinaryPred(*first, *next))    //  *first != *next;
            {
                ++first;
            }
            else
            {
                return first;
            }
        }
        return last;
    }

    template<class ForwardIterator>
    ForwardIterator adjacent_find(ForwardIterator first, ForwardIterator last)
    {
        typedef typename iterator_traits<ForwardIterator>::value_type value_type;
        return adjacent_find(first, last, equal_to<value_type>());
    }

    //////////////////////////////////////////////////////////////////////
    //  unique_copy
    template<class InputIterator, class ForwardIterator, class BinaryPredicate>
    ForwardIterator 
    unique_copy_aux(InputIterator first, InputIterator last, 
                    ForwardIterator result, forward_iterator_tag, BinaryPredicate BinaryPred)
    {
        *result = *first;
        ++first;
        for (; first != last; ++first)
        {
            //  *result != *first
            //  the list's unique is *result == *first(BinaryPre(*result, *first))
            //  so, it should call !BinaryPred
            if (!BinaryPred(*result, *first))      
            {
                *(++result) = *first;
            }
        }
        return ++result;
    }

    template<class InputIterator, class OutputIterator, class BinaryPredicate>
    OutputIterator 
    unique_copy_aux(InputIterator first, InputIterator last, 
                    OutputIterator result, output_iterator_tag, BinaryPredicate BinaryPred)
    {
        //  the version for OutputIterator
        //  ...

        return result;
    }

    template<class InputIterator, class OutputIterator, class BinaryPredicate>
    inline OutputIterator
    unique_copy(InputIterator first, InputIterator last, OutputIterator result, BinaryPredicate BinaryPred)
                                
    {
        if (first == last)
        {
            return result;
        }

        typedef typename iterator_traits<OutputIterator>::iterator_category category;
        return unique_copy_aux(first, last, result, category(), BinaryPred);
    }

    template<class InputIterator, class OutputIterator>
    inline OutputIterator
    unique_copy(InputIterator first, InputIterator last, OutputIterator result)
    {
        typedef typename iterator_traits<OutputIterator>::value_type value_type;
        return unique_copy(first, last, result, equal_to<value_type>());
    }

    template<class ForwardIterator, class BinaryPredicate>
    ForwardIterator unique(ForwardIterator first, ForwardIterator last, BinaryPredicate BinaryPred)
    {
        first = adjacent_find(first, last, BinaryPred);
        return unique_copy(first, last, first, BinaryPred);
    }

    template<class ForwardIterator>
    ForwardIterator unique(ForwardIterator first, ForwardIterator last)
    {
        typedef typename iterator_traits<ForwardIterator>::value_type value_type;
        return unique(first, last, equal_to<value_type>());
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
