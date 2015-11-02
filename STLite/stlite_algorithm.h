/********************************************************************
	Time:	  2015/11/01
	Filename: stl_algorithm
	Author:	  dinglj
	
	Purpose:  STLite algorithm
*********************************************************************/

#ifndef _STLITE_ALGORITHM_H_
#define _STLITE_ALGORITHM_H_

//////////////////////////////////////////////////////////////////////
//  fill, fill_n
//  fill is equal to uninitialized_fill(first, last, __true_type)
template<class ForwardIterator, class T>
void fill(ForwardIterator first, ForwardIterator last, const T &value)
{
    for (; first != last; ++first)
    {
        *first = value;
    }
}

template<class OutputIterator, class Size, class T>
OutputIterator fill_n(OutputIterator first, Size n, const T &value)
{
    while (n > 0)
    {
        *first = value;
        ++first;
        --n;
    }
}
//////////////////////////////////////////////////////////////////////
//  copy
//template<>
#endif
