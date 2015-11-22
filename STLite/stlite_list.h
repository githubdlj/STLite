/********************************************************************
	Time:	  2015/10/25
	Filename: stlite_list
	Author:	  dinglj
	
	Purpose:  list, circular bidirectional list
*********************************************************************/
#ifndef _STLIST_LIST_H_
#define _STLIST_LIST_H_

#include <crtdefs.h>                //  std::ptrdiff_t

#include "common_header_files.h"
#include "stlite_alloc.h"   //  allocator
#include "stlite_iterator.h"

//////////////////////////////////////////////////////////////////////
namespace STLlite
{
    //  node
    template<class T>
    struct list_node
    {
        typedef list_node<T> pointer;
        pointer prev;
        pointer next;

        T data;
    };
    
    //////////////////////////////////////////////////////////////////////
    //  iterator, BidirectionalIterator
    template<class T>
    struct listIterator : public iterator<bidirectional_iterator_tag, T>
    {
    //////////////////////////////////////////////////////////////////////
    //  data
        typedef list_node<T> * link_type;

        link_type node;     //  point to list_node
    };

    //////////////////////////////////////////////////////////////////////
    //  list
    template<class T, class Alloc = allocator<list_node<T> > >
    class list
    {
    public:
        typedef T               value_type;
        typedef T*              pointer;
        typedef T&              reference;
        typedef size_t          size_type;
        typedef std::ptrdiff_t  difference_type;
    //////////////////////////////////////////////////////////////////////
    //  in order to test, set it as public.
    public:
        typedef list_node<T> * link_type;

        link_type node;     //  it can present the list.
    
    //////////////////////////////////////////////////////////////////////
    //  iterator
    public:
        typedef listIterator<T> iterator;

    //////////////////////////////////////////////////////////////////////
    //  allocator
    public:
        typedef allocator<list_node<T> > node_allocator;
    };
}
#endif
