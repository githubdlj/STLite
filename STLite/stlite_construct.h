/********************************************************************
	Time:	  2015/10/22
	Filename: stlite_construct
	Author:	  dinglj
	
	Purpose:  全局构造、析构函数
              SGI STL将对象的内存分配和构造分离出来了。
              1.    construct(T1 *ptr, const T2 &value)
              2.    destroy_aux(ForwardIterator first, ForwardIterator last, xx_type)
              3.    destroy(ForwardIterator first, ForwardIterator last)

*********************************************************************/

#ifndef _STLITE_CONSTRUCT_H_
#define _STLITE_CONSTRUCT_H_

#include <new.h>    //  placement new
#include "stlite_type_traits.h"
#include "stlite_iterator.h"

#include <iostream>
using std::cout;
using std::cin;
using std::endl;

using namespace STLite;

namespace STLite
{
    //  construct
    template<class T1, class T2>
    inline void construct(T1 *ptr, const T2 &value)
    {
        new(ptr) T1(value); //  placement new, 在ptr所指空间上构建对象
    }
    //////////////////////////////////////////////////////////////////////

    //  deconstruct, 命名为destroy而不是deconstruct?
    //  第一个版本
    template<class T>
    inline void destroy(T *ptr)
    {
        ptr->~T();
    }

    //  第二个版本

    //////////////////////////////////////////////////////////////////////
    //  先获取迭代器所指类型，根据迭代器所指类型调用对应的destroy函数
    template<class ForwardIterator>
    inline void destroy_aux(ForwardIterator first, ForwardIterator last, __true_type)
    {
        //  if has_trivial_deconstructor, do nothing
        cout << "do nothing" << endl;
    }

    template<class ForwardIterator>
    inline void destroy_aux(ForwardIterator first, ForwardIterator last, __false_type)
    {
        //  if not has_trivial_deconstructor, call destroy(&*first)
        for (; first < last; first++)
        {
            destroy(&*first);
        }
    }

    template<class ForwardIterator>
    inline void destroy(ForwardIterator first, ForwardIterator last)
    {
        //  note! 先获取迭代器所指类型，再根据类型判断是否has trivial deconstructor
        typedef typename __type_traits<iterator_traits<ForwardIterator>::value_type>::has_trivial_deconstructor has_trivial_deconstructor;  
        destroy_aux(first, last, has_trivial_deconstructor());
    }

    /*
        为什么construct不和destroy保持一致，即定义
        construct(T *prt)
        construct(ForwardIterator first, ForwardIterator last, T value)

        实际上，SGI STL中使用了uninitialized.h中的uninitialize_XX函数等价代替construct(first, last, value)
    */
}

#endif