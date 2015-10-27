/********************************************************************
	Time:	  2015/10/22
	Filename: stlite_alloc
	Author:	  dinglj
	
	Purpose:  内存配置器设计
              1、   最简单的内存配置器 allocator(也是SGI标准的内存配置器)
              2、   一级配置器 __malloc_alloc_template
              3、   二级配置器 __default_alloc_template

              4、   simple_alloc 对内存配置器的封装
*********************************************************************/

#ifndef _STLITE_ALLOC_H_
#define _STLITE_ALLOC_H_

#include "stlite_construct.h"    //  for construct, destroy
#include <new.h>    //  placement new, set_new_handler
#include <iostream>
using std::cout;
using std::cin;
using std::endl;

using namespace STLite;

namespace STLite
{
    //  allocate，deallocate
    template<class T>
    inline T* _allocate(ptrdiff_t size, T*)
    {
        set_new_handler(0);
        T *result = (T *) ::operator new((size_t) (size * sizeof(T)));
        if (0 == result)
        {
            std::cerr << "out of memory" << endl;
            exit(1);
        }
        else
        {
            cout << size * sizeof(T) << "byte memory has alloc" << endl;
        }

        return result;
    }

    template<class T>
    inline void _deallocate(T* buffer)
    {
        if (NULL != buffer)
        {
            cout << "free memory" << endl;
            ::operator delete(buffer);
        }
    }

    //////////////////////////////////////////////////////////////////////
    //  allocator
    //  allocator符合VC版本的STL标准接口，可以直接使用
    template<class T>
    class allocator
    {
    public:
        //  如果是SGI STL，则作为容器的内存配置器必须满足如下的接口
        typedef T           value_type;
        typedef T*          pointer;
        typedef const T*    const_pointer;
        typedef T&          reference;
        typedef const T&    const_reference;
        typedef ptrdiff_t   difference_type;
        typedef size_t      size_type;

        template<class U>
        struct rebind{
            typedef allocator<U> other;
        };

        static pointer allocate(size_type n)
        {
            return _allocate((difference_type)n, (pointer)0);
        }

        static void deallocate(pointer p, size_type n) //  VC下STL deallcate接口带2个参数
        {
            _deallocate(p);
        }

        //////////////////////////////////////////////////////////////////////
        //  如果是SGI STL,作为容器的配置器，不必要提供下面的接口，构造对象利用了全局的construct函数。
        //  将内存配置和构造分离出来了。
        //  但是，vc下的STL版本为了配合容器必须提供以下接口。
        static void construct(pointer p, const_reference value)
        {
            STLite::construct(p, value);  //  调用全局的构造函数，位于stlite_construct.h
                  
        }

        static void destroy(pointer p)
        {
            STLite::destroy(p);   //  调用全局的析构函数，位于stlite.construct.h
        }
        
        //  效率更高的destroy函数
        static void destroy(pointer first, pointer last)
        {
            STLite::destroy(first, last);
        }
        //////////////////////////////////////////////////////////////////////
        size_type max_size()const
        {
            return size_type(-1) / sizeof(T);
        }
        
        //  constructor，为了符合VC版本STL接口标准
        allocator() {}
        allocator(const allocator &) {}
        
        template<class U>
        allocator(const allocator<U> &) {}
         
    };

    //  一级配置器，符合SGI STL版本接口
    //  简单的封装了malloc，free
    class __malloc_alloc
    {

    };

    //////////////////////////////////////////////////////////////////////
    //  二级配置器，符合SGI STL版本接口
    //  维护内存空闲链表
    class __default_alloc
    {

    };

    //  对一、二级配置器进行包装，使得其符合相应的STL版本接口
    //  VC版本的STL和SGI STL接口不一样。
    template<class T, class Alloc>
    class simple_alloc
    {

    };
    //////////////////////////////////////////////////////////////////////

    //  
}

#endif