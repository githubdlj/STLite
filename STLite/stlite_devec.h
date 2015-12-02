/********************************************************************
	Time:	  2015/12/02
	Filename: devec
	Author:	  dinglj
	
	Purpose:  the improvement of the vector
              it can improve the efficiency when inserting the elements close to the head 
*********************************************************************/
#ifndef _STLITE_DEVEC_H_
#define _STLITE_DEVEC_H_

#include "common_header_files.h"
#include "stlite_iterator.h"
#include "stlite_alloc.h"

//////////////////////////////////////////////////////////////////////
namespace STLite
{
    template<class T, class Alloc>
    class devec;

    template<class T, class Alloc = allocator<T> >
    struct devecIterator : public iterator<random_access_iterator_tag, T>
    {
    //  member data
        T *m_ptr;
        int index;      //  because the m_ptr is circular, so it need a index.
        devec<T, Alloc> *vec;  //  the devecIterator should know the devec's attribute, so it should contain the *vec.
    
    //  member function
       
    };

    template<class T, class Alloc = allocator<T> >
    class devec
    {
    //  type
    public:
        typedef T               value_type;
        typedef T*              pointer;
        typedef T&              reference;
        typedef size_t          size_type;
        typedef std::ptrdiff_t  difference_type;
    //////////////////////////////////////////////////////////////////////
    //  member data
    private:
        //  memory space
        pointer start_of_storage;
        pointer end_of_storage;

        //  object space
        int start;
        int end;
    //////////////////////////////////////////////////////////////////////
    //  iterator 
    public:
        typedef devecIterator<T> iterator;
    //////////////////////////////////////////////////////////////////////
    //  allocator
    public:
        typedef allocator<T> data_allocator;

}

#endif