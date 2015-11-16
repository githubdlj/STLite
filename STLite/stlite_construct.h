/********************************************************************
	Time:	  2015/10/22
	Filename: stlite_construct
	Author:	  dinglj
	
	Purpose:  construct && destroy
              cooperate with the stlite_uninitialzed.h's function to construct and destroy objector(s) 

*********************************************************************/

#ifndef _STLITE_CONSTRUCT_H_
#define _STLITE_CONSTRUCT_H_

#include <new.h>    //  placement new

#include "common_header_files.h"
#include "stlite_type_traits.h"
#include "stlite_iterator.h"

//////////////////////////////////////////////////////////////////////
namespace STLite
{
    //  construct
    template<class T1, class T2>
    inline void construct(T1 *ptr, const T2 &value)
    {
        new(ptr) T1(value);     //  placement new, construct a object on the memory that the ptr point.
    }
    //////////////////////////////////////////////////////////////////////
    //  destroy
    
    template<class T>
    inline void destroy(T *ptr)
    {
        ptr->~T();  //  call the object's destructor
    }

    //////////////////////////////////////////////////////////////////////
    // call the corresponding version according to the data type
    template<class ForwardIterator>
    inline void destroy_aux(ForwardIterator first, ForwardIterator last, __true_type)
    {
        //  if the object has_trivial_deconstructor, do nothing
        cout << "do nothing" << endl;
    }

    template<class ForwardIterator>
    inline void destroy_aux(ForwardIterator first, ForwardIterator last, __false_type)
    {
        //  if the object not has_trivial_deconstructor, call destroy(&*first)
        for (; first != last; ++first)
        {
            destroy(&*first);
        }
    }

    template<class ForwardIterator>
    inline void destroy(ForwardIterator first, ForwardIterator last)
    {
        //  first, get the VALUE_TYPE of the ForwardIterator
        //  second, determine whether the VALUE_TYPE has_traivial_deconstuctor or not. 
        typedef typename iterator_traits<ForwardIterator>::value_type value_type;
        typedef typename __type_traits<value_type>::has_trivial_deconstructor has_trivial_deconstructor;
        destroy_aux(first, last, has_trivial_deconstructor());
    }

}

#endif