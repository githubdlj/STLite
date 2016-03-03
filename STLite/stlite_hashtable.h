/********************************************************************
	Time:	  2016/03/02
	Filename: stlite_hashtable
	Author:	  dinglj
	
	Purpose:  stl_hashtable
*********************************************************************/

#ifndef _STLITE_HASHTABLE_H_
#define _STLITE_HASHTABLE_H_

#include <crtdefs.h>

#include "stlite_iterator.h"
#include "stlite_alloc.h"
#include "stlite_vector.h"

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

    //////////////////////////////////////////////////////////////////////
    //  hashtable
    template<class Value, class Key, class HashFunc,
             class ExtraKey, class EqualKey>
    class hashtable
    {
    public:
        typedef Value           value_type;
        typedef Value*          pointer;
        typedef Value&          reference;
        typedef size_t          size_type;
        typedef std::ptrdiff_t  difference_type;
    
    public:
        typedef hashtableIterator<Value, Key, HashFunc, ExtraKey, EqualKey> iterator;
    
    private:
        typedef hashtable_node<Value> node;
        typedef allocator<node> node_allocator;

    private:
        STLite::vector<node*, allocator<node*> > buckets;
        size_type num_elements;
    
    private:
        HashFunc hasher;
        ExtraKey get_key;
        EqualKey equals; 

    //////////////////////////////////////////////////////////////////////
    //  
    private:
        void initialize_bucket(size_type n)
        {

        }
    //  constructor  
    public:
        hashtable()     //  hashtable does NOT support the default constructor
        {

        }
        hashtable(size_type n, const HashFunc& hf, const EqualKey& eql, const ExtraKey& ext)
                    : num_elements(n), hasher(hf), get_key(ext), equals(eql)
        { }
        
        hashtable(size_type n, const HashFunc& hf, const EqualKey& eql)
                    : num_elements(n), hasher(hf), get_key(ExtraKey()), equals(eql)
        { }

        hashtable(const hashtable& ht)
        {

        }
        
        hashtable& operator =(const hashtable &ht)
        {
            return *this;
        }

        ~hashtable()
        {

        }
        
    //////////////////////////////////////////////////////////////////////
    //  iterators
    public:
        iterator begin()
        {
            return iterator(NULL, NULL);
        }
        
        iterator end()
        {
            return iterator(NULL, NULL);
        }
    
    //////////////////////////////////////////////////////////////////////
    //  insert
    private:
        iterator insert_unique_noresize(const value_type& value)
        {
            return iterator(NULL, NULL);
        }

        iterator insert_equal_noresize(const value_type& value)
        {
            return iterator(NULL, NULL);
        }

    private:
        //  insert_unique
        template<class InputIterator>
        void insert_unique(InputIterator first, InputIterator last, input_iterator_tag)
        {

        }
        
        template<class ForwardIterator>
        void insert_unique(ForwardIterator first, ForwardIterator last, forward_iterator_tag)
        {

        }
        
        //  insert_equal
        template<class InputIterator>
        void insert_equal(InputIterator first, InputIterator last, input_iterator_tag)
        {
        
        }

        template<class ForwardIterator>
        void insert_equal(ForwardIterator first, ForwardIterator last, forward_iterator_tag)
        {
        
        }

    public:
        //  insert_unique
        void insert_unique(const value_type& value)     //  return pair(iterator, bool)
        {

        }
        
        template<class InputIterator>
        void insert_unique(InputIterator first, InputIterator last)
        {
            typedef typename iterator_traits<InputIterator>::iterator_category category;
            insert_unique(first, last, category());
        }
        
        //  insert_equal
        iterator insert_equal(const value_type& value)
        {
            return iterator(NULL, NULL);
        }
        
        template<class InputIterator>
        void insert_equal(InputIterator first, InputIterator last)
        {
            typedef typename iterator_traits<InputIterator>::iterator_category category;
            insert_equal(first, last, category());
        }
    //////////////////////////////////////////////////////////////////////
    //  erase & clear
    private:
        //  erase the [first, last) elements in the bucket[n]
        void erase_bucket(const size_type n, iterator first, iterator last)
        {

        }
    
        void erase_bucket(const size_type n, iterator last)
        {

        }

    public:
        size_type erase(const Key& key)     //  return the number of the deleted key
        {
            return 0;
        }
    
        void erase(const iterator& it)
        {

        }

        void erase(iterator first, iterator last)
        {
            
        }

        void clear()
        {

        }
    //////////////////////////////////////////////////////////////////////
    //  find
    public:
        iterator find() const
        {
            return iterator(NULL, NULL);
        }
    
        value_type find_or_insert(const value_type& value)
        {
            return value;
        }
    //////////////////////////////////////////////////////////////////////
    //  
    public:
        HashFunc hash_func() const
        {
            return hasher;
        }
        
        EqualKey key_equal() const
        {
            return equals;
        }
    //////////////////////////////////////////////////////////////////////
    //  capacity
    size_type size() const
    {
        return num_elements;
    }
    
    size_type max_size() const
    {
        return size_type(-1);
    }

    bool empty() const
    {
        return num_elements == 0;
    }
    
    size_type bucket_count() const
    {
        return buckets.size();
    }
    
    size_type max_bucket_count() const
    {
        return 0;
    }
    
    size_type elems_in_bucket(size_type bucket) const
    {
        return 0;
    }
    //////////////////////////////////////////////////////////////////////
    //  locate the obj
    private:
        size_type bkt_num_key(const Key& key, size_type n) const
        {
            return hasher(key) % n;
        }

        size_type bkt_num_key(const Key& key) const
        {
            return bkt_num_key(key, bucket_count());
        }

        size_type bkt_num(const value_type& value, size_type n) const
        {
            return bkt_num_key(get_key(value), n);
        }

        size_type bkt_num(const value_type& value) const
        {
            return bkt_num_key(get_key(value));
        }
    //////////////////////////////////////////////////////////////////////
    //  resize
    private:
        void resize(int n)
        {
        }
        
    //////////////////////////////////////////////////////////////////////
    //  memory operation
    private:
        node* new_node(const value_type& value)
        {
            node* newNode;
            return newNode;
        }      
    
        void delete_node(node* deleteNode)
        {

        }

    };
}

#endif