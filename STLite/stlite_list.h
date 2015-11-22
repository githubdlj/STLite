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
#include "stlite_type_traits.h"

//////////////////////////////////////////////////////////////////////
namespace STLite
{
    //  node
    template<class T>
    struct list_node
    {
        //  data
        typedef list_node<T> * pointer;
        pointer prev;
        pointer next;

        T data;

        //  constructor
        list_node(T d = T(), pointer p = NULL, pointer n = NULL) : data(d), prev(p), next(n) {}
    };
    
    //////////////////////////////////////////////////////////////////////
    //  iterator, BidirectionalIterator
    template<class T>
    struct listIterator : public iterator<bidirectional_iterator_tag, T>
    {
    //  data
        typedef list_node<T> * link_type;

        link_type node;     //  point to list_node

    //////////////////////////////////////////////////////////////////////
    //  function

        //  constructor, copy, assignment, destructor
        explicit listIterator(link_type nodePtr = NULL) : node(nodePtr) {}
        listIterator(const listIterator &lhs) : node(lhs.node) {}
        listIterator & operator =(const listIterator &lhs) { node = lhs.node; }
        ~listIterator() { }

        //  defer
        reference operator *()
        {
            return node->data;
        }

        pointer operator ->()
        {
            return &(operator *());
        }

        //  increase, decrease
        listIterator & operator ++()  //    ++prefix
        {
            node = node->next;
            return *this;
        }

        listIterator operator ++(int)   //  postfix++
        {
            listIterator temp(*this);
            ++(*this);
            return temp;
        }

        listIterator & operator --()  
        {
            node = node->prev;
            return this;
        }

        listIterator operator --(int)
        {
            node temp(*this);
            ++(*this);
            return node;
        }

        //  comparison
        bool operator == (const listIterator &lhs) const 
        {
            return node == lhs.node;
        }

        bool operator != (const listIterator &lhs) const
        {
            return !operator ==(lhs);
        }
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
