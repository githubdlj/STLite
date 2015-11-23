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
#include "stlite_construct.h"

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
        listIterator & operator =(const listIterator &lhs) 
        {
            node = lhs.node; 
            return *this;
        }
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

    //////////////////////////////////////////////////////////////////////
    //  function

    //  memory operation
    private:    
        link_type get_node()     
        {
            return node_allocator::allocate(1);
        }

        void put_node(link_type p)
        {
            node_allocator::deallocate(p, 1);
        }

        link_type create_node(const value_type &value)
        {
            link_type newNode = get_node();
        //    construct(newNode, list_node<T>(value));
            construct(&newNode->data, value);
            return newNode;
        }

        void destroy_node(link_type p)
        {
            destroy(&p->data);
            put_node(p);
        }
    
    //////////////////////////////////////////////////////////////////////
    //  constructor, copy, assignment, destructor
    private:
        //  initialize list with a header node
        void empty_initialize()
        {
            node = get_node();
            node->next = node;
            node->prev = node;
        }

    public:
        //  constructor
        list()
        {
            empty_initialize();
        }

        list(size_type n, const value_type &value)
        {
            empty_initialize();
            insert(end(), n, value);
        }

        template<class InputIterator>
        list(InputIterator first, InputIterator last)
        {
            empty_initialize();
            insert(end(), first, last);
        }

        //  copy constructor
        list(const list &lhs)
        {
            empty_initialize();
            insert(end(), lhs.begin(), lhs.end());
        }

    //////////////////////////////////////////////////////////////////////
    //  iterators
    public:
        iterator begin()
        {
            return iterator(node->next);
        }

        iterator end()
        {
            return iterator(node);
        }
    //////////////////////////////////////////////////////////////////////
    //  insert
    private:
        void fill_insert(iterator pos, size_type n, const value_type &value)
        {
            while (n > 0)
            {
                insert(pos, value);     //  call insert(pos, value)
                --n;
            }
        }

        template<class InputIterator>
        void range_insert(iterator pos, InputIterator first, InputIterator last)
        {
            for (; first != last; ++first)
            {
                insert(pos, *first);    //  call insert(pos, value)
            }
        }

    private:
        template<class Integer>
        void insert_dispatch(iterator pos, Integer n, const value_type &value, __true_type)
        {
            fill_insert(pos, n, value);
        }

        template<class InputIterator>
        void insert_dispatch(iterator pos, InputIterator first, InputIterator last, __false_type)
        {
            range_insert(pos, first, last);
        }

    public:
        iterator insert(iterator pos, const value_type &value)      //  this is the kernel insert
        {
            link_type newNode = create_node(value);

            newNode->next = pos.node;
            newNode->prev = pos.node->prev;
            pos.node->prev->next = newNode;
            pos.node->prev = newNode;

            return iterator(newNode);
        }

        void insert(iterator pos, size_type n, const value_type &value)
        {
            insert_dispatch(pos, n, value, __true_type());
        }

        template<class InputIterator>
        void insert(iterator pos, InputIterator first, InputIterator last)
        {
            typedef typename _is_integer<InputIterator>::is_integer is_integer;
            insert_dispatch(pos, first, last, is_integer());
        }
    };
}
#endif
