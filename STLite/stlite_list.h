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
            return *this;
        }

        listIterator operator --(int)
        {
            node temp(*this);
            ++(*this);
            return temp;
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
        
        list(size_type n)
        {
            empty_initialize();
            insert(end(), n, value_type());
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
            
            //  error, end() is iterator, lhs.begin() is CONST iterator.
            //  it can not transfer CONST iterator to iterator.
            //  it should realized const_iterator.
            
            //  insert(end(), lhs.begin(), lhs.end());
            
            link_type first = lhs.node->next;
            link_type last = lhs.node;
            insert(end(), iterator(first), iterator(last));
        }

        //  assignment
        list & operator =(const list &lhs)
        {
//             //  swap, a simple way. 
//             //  something wrong
//             if (&lhs != this)   //  check self assignment
//             {
//                 list<T> temp(lhs);  //  a temp list, it will destroy when the function returns
//                 
//                 std::swap(node, lhs.node);  // compiler error
//                 
//             }
//             return *this;

            //  another way, it is more complex but has a higher performance.
            //  it can reduce to allocate memory and deallocate memory.
            if (&lhs != this)
            {
                iterator first1 = begin();
                iterator last1 = end();
                
//                 //  type transfer error , see list(const list &lhs)             
//                  iterator first2 = lhs.begin();
//                  iterator last2 = lhs.end();
                link_type first2 = lhs.node->next;
                link_type last2 = lhs.node;

                for(; last1 != first1 && last2 != first2; ++first1, first2 = first2->next)
                {
                    *first1 = first2->data;
                }

                if (last1 == first1)
                {
                    insert(last1, iterator(first2), iterator(last2));
                }
                else
                {
                    erase(first1, last1);
                }
            }
            return *this;
        }

        // destructor
        ~list()
        {
            clear();
            put_node(node);     //  destroy the header node
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
    //////////////////////////////////////////////////////////////////////
    //  erase, arguments: iterator
    //         return: iterator
    public:
        iterator erase(iterator pos)
        {
            link_type prev = pos.node->prev;
            link_type next = pos.node->next;
            
            prev->next = next;
            next->prev = prev;
            
            destroy_node(pos.node);     //  destruct elements and destroy memory
            
            return iterator(next);
        }
        
        //  error, because erase(pos) will destroy the pos, thus ++pos is invalid.            
//         iterator erase(iterator first, iterator last)
//         {
//             for (; last != first; ++first)
//             {
//                 erase(first);
//             }
//             return first;
//         }
        iterator erase(iterator first, iterator last)
        {
            while (last != first)
            {
                erase(first++);     //  operator ++(int) first return the old iterator object and then ++
            }
            return first;
        }

    //  clear
    public:
        void clear()
        {
            erase(begin(), end());
            
            node->next = node;
            node->prev = node;
        }
    };
}
#endif
