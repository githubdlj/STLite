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
#include "stlite_algorithm.h"
#include "stlite_function.h"

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
        //list_node(T d = T(), pointer p = NULL, pointer n = NULL) : data(d), prev(p), next(n) {}
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
            //  call range_assign, but first check self assignment.
            if (&lhs != this)
            {
                //  transfer error, see list(const list &lhs)
                //  range_assign(lhs.begin(), lhs.end());
                
                link_type first = lhs.node->next;
                link_type last = lhs.node;

                range_assign(iterator(first), iterator(last));
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
    //  modifiers
    //  insert, erase, clear, assign
    //  push_back, pop_back, push_front, pop_front
    //  swap
 
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
    //  assign, assignment does NOT check self assignment, because fill_assign can not do it(range_assign can)
    private:
        void fill_assign(size_type n, const value_type &value)
        {
            iterator first = begin();
            iterator last = end();

            for (; first != last && n > 0; ++first, --n)
            {
                *first = value;
            }

            if (0 == n)     //  the list's size > n
            {
                erase(first, last);
            }
            else            //  the list's size < n
            {
                insert(first, n, value);
            }
        }

        template<class InputIterator>
        void range_assign(InputIterator first, InputIterator last)
        {
            //  way1, swap. it is simple but has more operations on memory 

            //  way2
            iterator thisFirst = begin();
            iterator thisLast = end();

            for (; thisFirst != thisLast && first != last; ++thisFirst, ++first)
            {
                *thisFirst = *first;
            }

            if (thisFirst == thisLast)   //  the original list is shorter.
            {
                insert(thisFirst, first, last);
            }
            else                        //  the original list is longer
            {
                erase(thisFirst, thisLast);
            }
        }

    private:
        template<class Integer>
        void assign_dispatch(Integer n, const value_type &value, __true_type)
        {
            fill_assign(n, value);
        }

        template<class InputIterator>
        void assign_dispatch(InputIterator first, InputIterator last, __false_type)
        {
            range_assign(first, last);
        }

    public:
        void assign(size_type n, const value_type &value)
        {
            assign_dispatch(n, value, __true_type());
        }

        template<class InputIterator>
        void assign(InputIterator first, InputIterator last)
        {
            typedef typename _is_integer<InputIterator>::is_integer is_integer;
            assign_dispatch(first, last, is_integer());
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
    //////////////////////////////////////////////////////////////////////
    //  push, pop
    public:
        void push_back(const value_type &value)
        {
            insert(end(), value);
        }
        
        void pop_back()
        {
            erase(--end());
        }

        void push_front(const value_type &value)
        {
            insert(begin(), value);
        }
        
        void pop_front()
        {
            erase(begin());
        }
    //  swap
    public:
        void swap(list &lhs)    //  notice the parameter, list &lhs, not const list &lhs
        {
            std::swap(node, lhs.node);
        }

    //////////////////////////////////////////////////////////////////////
    //  elements access
    //  front, back
    public:
        reference front()
        {
            return *begin();
        }

        reference back()
        {
            return *(--end());
        }
    
    //////////////////////////////////////////////////////////////////////
    //  operations
    //  splice, remove, remove_if, unique, merge, sort, reverse
    public:     //  it should be private, in order to test, it can be declared public temporary.
        //  move the elements on range [first, last) to pos. 
        void transfer(iterator pos, iterator first, iterator last)
        {
            if (pos != last)
            {
                link_type posPrev = pos.node->prev;
                
                last.node->prev->next = pos.node;
                pos.node->prev = last.node->prev;
                
                first.node->prev->next = last.node;
                last.node->prev = first.node->prev;

                posPrev->next = first.node;
                first.node->prev = posPrev;
            }
        }

    public:
        void reverse()
        {
            iterator beginPos = begin();
            iterator endPos = end();

            iterator first = beginPos;   
            iterator last = beginPos;

            advance(first, 1);      //  reverse from the SECOND node.
            advance(last, 2);
            
            while (first != endPos)        //  if the list has 0 or 1 node, first equals end directly.
            {
                transfer(begin(), first, last);
              
                first = last;
                ++last;
                
            //    print(begin(), end());
            }
        }

        //  sort
        //  SGI STL use the merge sort, it is hard to understand.
        //  I use the directly insert method.
        template<class Compare>     //  functional
        void sort(Compare comp)
        {
            iterator endPos = end();

            iterator ordered = begin();
            iterator unOrdered = ++begin();

            //  init the ordered list with the first node.
            ordered.node->next = endPos.node;
            endPos.node->prev = ordered.node;

            while (unOrdered != endPos)
            {
                iterator needInsert = unOrdered;
                ++unOrdered;

                //  locate the insert position.
                iterator pos = begin();
                for (; pos != endPos && comp(*pos, *needInsert); ++pos);

                //  insert
                needInsert.node->prev = pos.node->prev;
                pos.node->prev->next = needInsert.node;
                
                needInsert.node->next = pos.node;
                pos.node->prev = needInsert.node;
            }
        }

        void sort()     //  default functional, less
        {
           sort(less<value_type>());
        }
        
        //  merge
        //  merge requires the list ordered.
        //  if the list is ascending order, the comp should be less, otherwise greater.
        template<class Compare>
        void merge(list &x, Compare comp)
        {
            iterator first1 = begin();
            iterator last1 = end();
            iterator first2 = x.begin();    
            iterator last2 = x.end();

            while (first1 != last1 && first2 != last2)
            {
                if (comp(*first2, *first1))
                {
                    iterator next = first2;
                    transfer(first1, first2, ++next);
                    first2 = next;
                }
                else
                {
                    ++first1;
                }
            }
            
            if (first2 != last2) 
            {
                transfer(last1, first2, last2);
            }
        }
        
        //  default, it requires the lists descending ordered.
        void merge(list &x)
        {
            merge(x, less<value_type>());
        }

        //  unique
        //  removes all but the first element from every consecutive group of equal elements in the list container.
        template<class BinaryPredicate>
        void unique(BinaryPredicate binaryPred)
        {
            iterator first = begin();
            iterator last = end();
            iterator next = first;
            
            while (++next != last)
            {
                if (binaryPred(*first, *next))
                {
                    erase(next);        //  notice!, erase(next) cause the iterator valid.
                    next = first;       //  assign next
                }
                else
                {
                    first = next;
                }
            }
        }

        void unique()
        {
            unique(equal_to<value_type>());
        }
        
        //  remove
        void remove(const value_type &value)
        {
            iterator first = begin();
            iterator last = end();
            
            while (first != last)
            {
                if (value == *first)
                {
                    first = erase(first);
                }
                else
                {
                    ++first;
                }
            }
        }

        template<class Predicate>
        void remove_if(Predicate pred)
        {
            iterator first = begin();
            iterator last = end();
            
            while (first != last)
            {
                if (pred(*first))
                {
                    first = erase(first);
                }
                else
                {
                    ++first;
                }
            }
        }

    //////////////////////////////////////////////////////////////////////
    //  capacity
    //  size, max_size, empty, resize
    public:
        size_type size() const
        {
            size_type n = 0;
            distance(begin(), end(), n);
            return n;
        }

        size_type max_size() const
        {
            return size_type(-1);
        }

        bool empty() const
        {
            //  call size(), call distance, call begin(), call end().
            //  return 0 == size(); 

            return node == node->next;
        }

        void resize(size_type newSize, const value_type &value)
        {
            iterator first = begin();
            iterator last = end();
            for (; first != last && newSize > 0; ++first, --newSize);

            if (newSize > 0)
            {
                insert(last, newSize, value);
            }
            else
            {
                erase(first, last);
            }
        }

        void resize(size_type newSize)
        {
            resize(newSize, value_type());
        }
    };
}
#endif
