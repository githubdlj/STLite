/********************************************************************
	Time:	  2016/03/02
	Filename: stlite_hashtable
	Author:	  dinglj
	
	Purpose:  stl_hashtable
*********************************************************************/

#ifndef _STLITE_HASHTABLE_H_
#define _STLITE_HASHTABLE_H_

#include "stlite_iterator.h"
//////////////////////////////////////////////////////////////////////
namespace STLite
{
    //  node
    template<class Value>
    struct hashtable_node
    {
        hashtable_node *next;
        Value val;
    };

    //////////////////////////////////////////////////////////////////////
    //  hashtable, prefix declare, because the hashtableIterator use it.
    template<class Value, class Key, class HashFunc,
             class ExtraKey, class EqualKey>    //  class Alloc
    class hashtable;

    //////////////////////////////////////////////////////////////////////
    //  hashtableIterator, forwardIterator
    template<class Value, class Key, class HashFunc,
             class ExtraKey, class EqualKey>    //  class Alloc
    struct hashtableIterator : public iterator<forward_iterator_tag, Value>
    {
        typedef hashtableIterator<Value, Key, HashFunc, ExtraKey, EqualKey> iterator;
        typedef hashtable_node<Value> node;
        typedef hashtable<Value, Key, HashFunc, ExtraKey, EqualKey> hashtable;
        
        //  member data
        hashtable *m_ht;      //  the hashtableIterator should know the information of the hashtable.
        node *m_cur;

        //////////////////////////////////////////////////////////////////////
        //  constructor, copy, assignment, destructor. default
        hashtableIterator(node *cur = NULL, hashtable *ht = NULL) : m_cur(cur), m_ht(ht) {}

        //////////////////////////////////////////////////////////////////////
        //  forwardIterator operation
        //  *, ->, ==, !=, ++
        //  defer
        reference operator *() const
        {
            return m_cur->val;
        }

        pointer operator ->() const
        {
            return &(operator *());
        }

        //  compare
        bool operator ==(iterator &lhs) const
        {
            return lhs.m_cur == m_cur;
        }

        bool operator !=(iterator &lhs) const
        {
            return !(operator ==(lhs));
        }

        //  ++
        iterator& operator ++();
        iterator operator ++(int);
    };

    template<class Value, class Key, class HashFunc,
             class ExtraKey, class EqualKey>
    hashtableIterator<Value, Key, HashFunc, ExtraKey, EqualKey>&
    hashtableIterator<Value, Key, HashFunc, ExtraKey, EqualKey>::operator ++()
    {
        return *this;
    }

    template<class Value, class Key, class HashFunc,
             class ExtraKey, class EqualKey>
    inline hashtableIterator<Value, Key, HashFunc, ExtraKey, EqualKey>
    hashtableIterator<Value, Key, HashFunc, ExtraKey, EqualKey>::operator ++(int)
    {
        iterator temp;
        ++(*this);
        return temp;
    }
}

#endif