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
//         if (0 == result)
//         {
//             std::cerr << "out of memory" << endl;
//             exit(1);
//         }
//         else
//         {
//             cout << size * sizeof(T) << "byte memory has alloc" << endl;
//         }

        return result;
    }

    template<class T>
    inline void _deallocate(T* buffer)
    {
        if (NULL != buffer)
        {
            //  cout << "free memory" << endl;
            ::operator delete(buffer);
        }
    }

    //////////////////////////////////////////////////////////////////////
    //  allocator, a simple allocator, it just call ::opearator new and ::opearator delete
    //  In order to test, the interface must to conform to the VC STL. 
    template<class T>
    class allocator
    {
    public:
        typedef T               value_type;
        typedef T*              pointer;
        typedef const T*        const_pointer;
        typedef T&              reference;
        typedef const T&        const_reference;
        typedef std::ptrdiff_t  difference_type;
        typedef size_t          size_type;

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
        //  the VC STL call allocator<T>::construct and destroy in alloc.h
        //  the SGI STL construct and destroy in construct.h

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
    //  MemoryPool
    //  BlockSize must  greater than 8
    template<class T, size_t BlockSize = 4096>
    class MemoryPool
    {
    public:
        typedef T               value_type;
        typedef T*              pointer;
        typedef const T*        const_pointer;
        typedef T&              reference;
        typedef const T&        const_reference;
        typedef std::ptrdiff_t  difference_type;
        typedef size_t          size_type;

        template<class U>
        struct rebind
        {
            typedef MemoryPool<U> other;
        };

        static pointer allocate(size_type n = 0)
        {
            //  assert(BlockSize >= 16);
            if (NULL != freeSlot)
            {
                pointer result = (pointer)freeSlot;
                freeSlot = freeSlot->next;
                return result;
            }
            else
            {
                if (currentSlot >= lastSlot)
                {
                    allocateBlock();
                }
               
                slot_pointer temp = currentSlot;
                //  cout << sizeof(value_type) << endl;
                size_t offset = std::max(sizeof(value_type), sizeof(slot_pointer));
                currentSlot = (slot_pointer)( (data_pointer)currentSlot + offset );
                return (pointer)temp;
            }
        }

        static void deallocate(pointer ptr, size_type n = 0)
        {
            if (NULL != ptr)
            {
                ((slot_pointer)ptr)->next = freeSlot;
                freeSlot = (slot_pointer)ptr;
            }
        }

        //  the VC STL call allocator<T>::construct and destroy in alloc.h
        //  the SGI STL construct and destroy in construct.h
        static void construct(pointer ptr, const value_type &value)
        {
            STLite::construct(ptr, value);
        }

        static void destroy(pointer ptr)
        {
            STLite::destroy(ptr);
        }

        static void destroy(pointer first, pointer last)
        {
            STLite::destroy(first, last);
        }
        
        static void destroyMemoryPool()
        {
            slot_pointer curr = currentBlock;
            while (curr != NULL)
            {
                slot_pointer next = curr->next;
                ::operator delete(curr);
                curr = next;
            }
        }

        size_type max_size()const
        {
            return size_type(-1) / sizeof(T);       //  size_type is unsigned int
        }

//         //  constructor
        MemoryPool() {}
        MemoryPool(const MemoryPool &) {}

        template<class U>
        MemoryPool(const MemoryPool<U> &) {}
    //
    private:
//         union slot
//         {
//             value_type element;     //  value_type can not have CONSTRUCTOR!
//             slot *next;
//         };
        union slot
        {
            char client_data[1];
            slot *next;
        };

    public:
        typedef char*   data_pointer;
        typedef slot    slot_type;
        typedef slot*   slot_pointer;

    private:
        static slot_pointer currentBlock;
        static slot_pointer currentSlot;
        static slot_pointer lastSlot;
        static slot_pointer freeSlot;

        static size_type padPointer(data_pointer p, size_type align)
        {
            size_t result = (size_t)p;
            return (align - result) % align;
        }

    private:
        static void allocateBlock()
        {
            data_pointer newBlock = (data_pointer) ::operator new(BlockSize);
            ((slot_pointer)(newBlock))->next =  currentBlock;
            currentBlock = (slot_pointer)newBlock;

            data_pointer body = newBlock + sizeof(slot_pointer);    //  the block's head used to link other blocks.
            size_type bodyPading = padPointer(body, sizeof(slot_type));
            bodyPading = 0;

            currentSlot = (slot_pointer)(body + bodyPading);
            size_type offset = std::max(sizeof(value_type), sizeof(slot_pointer));
            lastSlot = (slot_pointer)(newBlock + BlockSize - offset + 1);
            //lastSlot = (data_pointer)(new)
        }
    };
    
    template<class T, size_t BlockSize>
    typename MemoryPool<T, BlockSize>::slot_pointer MemoryPool<T, BlockSize>::currentBlock = NULL;

    template<class T, size_t BlockSize>
    typename MemoryPool<T, BlockSize>::slot_pointer MemoryPool<T, BlockSize>::currentSlot = NULL;

    template<class T, size_t BlockSize>
    typename MemoryPool<T, BlockSize>::slot_pointer MemoryPool<T, BlockSize>::lastSlot = NULL;

    template<class T, size_t BlockSize>
    typename MemoryPool<T, BlockSize>::slot_pointer MemoryPool<T, BlockSize>::freeSlot = NULL;

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