/********************************************************************
	Time:	  2015/10/22
	Filename: stlite_alloc
	Author:	  dinglj
	
	Purpose:  allocator
              1. allocator
              2. __malloc_alloc_template, simple allocator. 
              3. __default_alloc_template, complex allocator.

              4. simple_alloc, packaging __malloc_alloc_template or __default_alloc_temple.
*********************************************************************/

#ifndef _STLITE_ALLOC_H_
#define _STLITE_ALLOC_H_

#include <new.h>        //  placement new, set_new_handler
#include <crtdefs.h>    //  std::ptrdiff_t
#include <stdlib.h>     //  exit(0)

#include "commom_header_files.h"
#include "stlite_construct.h"    //  for construct, destroy

//////////////////////////////////////////////////////////////////////
namespace STLite
{
    //  allocate, deallocate
    template<class T>
    inline T* _allocate(std::ptrdiff_t size, T*)    //  the parameter T * used to deduce tempate 
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
    //  In order to test, the interface must to conform to the VC STL. 
    template<class T>
    class allocator
    {
    public:
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

        static void deallocate(pointer p, size_type n)      //  offering 2 parameters to conform to the VC STL
        {
            _deallocate(p);
        }

        //////////////////////////////////////////////////////////////////////
        //  to conform to VC STL, I must to offer the interface as follows.
        //  in fact, the SGI STL separate the ALLOCATE and CONSTRUCT 
        static void construct(pointer p, const_reference value)
        {
            STLite::construct(p, value);    
        }

        static void destroy(pointer p)
        {
            STLite::destroy(p);   
        }
        
        //  has greater efficiency compared to destroy(pointer),
        //  because it calls corresponding destroy version according to the pointer type 
        static void destroy(pointer first, pointer last)
        {
            STLite::destroy(first, last);
        }

        //////////////////////////////////////////////////////////////////////
        size_type max_size()const
        {
            return size_type(-1) / sizeof(T);       //  size_type is unsigned int
        }
        
        //  constructor
        allocator() {}
        allocator(const allocator &) {}
        
        template<class U>
        allocator(const allocator<U> &) {}
         
    };

    //////////////////////////////////////////////////////////////////////
    //  simple allocator
    class __malloc_alloc
    {

    };

    //////////////////////////////////////////////////////////////////////
    //  complex allocator
    class __default_alloc
    {

    };

    //  
    template<class T, class Alloc>
    class simple_alloc
    {

    };
}

#endif