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
#include "stlite_construct.h"

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
        node* old = m_cur;
        m_cur = m_cur->next;    //  if cur is not NULL, the next is cur.
        if (!m_cur)             //  else
        {
            size_t bCount = m_ht->bucket_count();
            size_t index = old->val % bCount;  //  m_ht->bkt_num(old->val)
            
            ++index;
            while (!m_cur && index < bCount)
            {
                m_cur = m_ht->buckets[index];    //  access the hashtable private member, so, the iterator should be friend of the hashtable.
                ++index;
            }
        }
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
        friend struct iterator;     //  declare the iterator be the friend of the hashtable.

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
    //  auxiliary constructor
    private:
        void initialize_bucket(size_type n)
        {
            //////////////////////////////////////////////////////////////////////
            //////////////////////////////////////////////////////////////////////
            //  note!
            //  that the list does not have head node.
            //  it will convenient to INSERT or ERASE when it has head node.
            //  but it will cause bad performance!
            //  that is why the SGI STL does not use the head node.
            size_type n_buckets = n;
            buckets.reserve(n_buckets);
            buckets.insert(buckets.end(), n_buckets, (node*)0);
            num_elements = 0;

            //  if use the head node, it will be rewrite like this
//             size_type n_buckets = n;
//             buckets.reserve(n_buckets);
//             for (int index = 0; index < n_buckets; ++index)
//             {
//                 buckets.insert(buckets.end(), new_node(value_type));
//             }
//             num_elements = 0;
        }

        void copy_from(const hashtable& hb)
        {
            //  init the buckets
            size_type hbSize = hb.size();   
            buckets.clear();    //  clear itself, in order to insert (node*)0
            buckets.reserve(hbSize);
            buckets.insert(buckets.end(), hbSize, (node*)0);
            
            //  copy
            for (size_type index = 0; index < hbSize; ++index)
            {
               // if (hb.buckets[index])
                {
                    //  insert the head node.
                    node *p = hb.buckets[index];
                         //              value_type newVal = hb.buckets[index]->val;
//                     buckets[index] = new_node(hb.buckets[index]->val);
//                 
//                     //  insert the rest node.
//                     node* rear = buckets[index];
//                     for (node* cur = hb.buckets[index]->next; cur; cur = cur->next)
//                     {
//                         rear->next = new_node(cur->val);
//                         rear = rear->next;
//                     }
                }
            } 
            num_elements = hb.num_elements;
        }

    //  constructor  
    public:
        hashtable(size_type n)     //  hashtable does NOT support the default constructor
        {
            initialize_bucket(n);
        }

        hashtable(size_type n, const HashFunc& hf, const EqualKey& eql, const ExtraKey& ext)
                    : num_elements(n), hasher(hf), get_key(ext), equals(eql)
        {
            initialize_bucket(n);
        }
        
        hashtable(size_type n, const HashFunc& hf, const EqualKey& eql)
                    : num_elements(n), hasher(hf), get_key(ExtraKey()), equals(eql)
        {
            initialize_bucket(n);
        }

        hashtable(const hashtable& ht) : hasher(ht.hasher), get_key(ht.get_key), equals(ht.equals)
        {
            copy_from(ht);
        }
        
        hashtable& operator =(const hashtable &ht)
        {
            if (&ht != this)
            {
                clear();
                
                hasher = ht.hasher;
                get_key = ht.get_key;
                equals = ht.equals;
                copy_from(ht);
            }
            return *this;
        }

        ~hashtable()
        {
            clear();
        }
        
    //////////////////////////////////////////////////////////////////////
    //  iterators
    public:
        iterator begin()
        {
            size_type bCount = bucket_count();
            for (size_type index = 0; index < bCount; ++index)
            {
                if (buckets[index])
                {
                    return iterator(buckets[index], this);
                }
            }
            return iterator(NULL, this);
        }
        
        //  note, the END point the next position of the last node,
        //  so, it must be NULL.
        iterator end() 
        {
            return iterator(NULL, this);
        }
    
    //////////////////////////////////////////////////////////////////////
    //  insert
    private:
        void insert_unique_noresize(const value_type& value)    //  pair
        {
            //  size_type index  = value % bucket_count();
            size_type index = bkt_num(value);
            for (node* cur = buckets[index]; cur; cur = cur->next)
            {
                if (equals(get_key(value), get_key(cur->val)))  //  equals(get_key(value), get_ket(cur->val))
                {
                    //  return pair<iterator, bool>(iterator(cur, this), false);
                } 
            }

            node* newNode = new_node(value);
            newNode->next = buckets[index];
            buckets[index] = newNode;
            
            num_elements++;
            //  return pair<iterator, bool>(iterator(newNode, this), true);
        }

        iterator insert_equal_noresize(const value_type& value)
        {
            size_type index = bkt_num(value);  
            //  size_type index = value % bucket_count();
            for (node* cur = buckets[index]; cur; cur = cur->next)
            {
                //  if find the equal value, insert it behind the cur.
                if (equals(get_key(value), get_key(cur->val)))  //  equals(get_key(value), get_key(cur->val))
                {
                    node* newNode = new_node(value);
                    newNode->next = cur->next;
                    cur->next = newNode;
        
                    num_elements++;
                    return iterator(newNode, this);
                }
            }
            //  else, insert into the head of the bucket[index].
            node* newNode = new_node(value);
            newNode->next = buckets[index];
            buckets[index] = newNode;
            
            num_elements++;
            return iterator(newNode, this);
        }

    private:
        //  insert_unique
        template<class InputIterator>
        void insert_unique(InputIterator first, InputIterator last, input_iterator_tag)
        {
            for (; first != last; ++first)
            {
                insert_unique(*first);
            }
        }
        
        template<class ForwardIterator>
        void insert_unique(ForwardIterator first, ForwardIterator last, forward_iterator_tag)
        {
            size_type dis = distance(first, last);
            resize(num_elements + dis);
            
            for (; dis > 0; --dis, ++first)
            {
                insert_unique_noresize(*first);
            }
        }
        
        //  insert_equal
        template<class InputIterator>
        void insert_equal(InputIterator first, InputIterator last, input_iterator_tag)
        {
            for (; first != last; ++first)
            {
                insert_equal(*first);
            }
        }

        template<class ForwardIterator>
        void insert_equal(ForwardIterator first, ForwardIterator last, forward_iterator_tag)
        {
            size_type dis = distance(first, last);
            resize(num_elements + dis);

            for (; dis > 0; --dis, ++first)
            {
                insert_equal_noresize(*first);
            }
        }

    public:
        //  insert_unique
        void insert_unique(const value_type& value)     //  return pair(iterator, bool)
        {
            resize(num_elements + 1);
            insert_unique_noresize(value);
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
            resize(num_elements + 1);
            return insert_equal_noresize(value);
        }
        
        template<class InputIterator>
        void insert_equal(InputIterator first, InputIterator last)
        {
            typedef typename iterator_traits<InputIterator>::iterator_category category;
            insert_equal(first, last, category());
        }
    //////////////////////////////////////////////////////////////////////
    //  erase & clear
    public:
        size_type erase(const Key& key)     //  return the number of the deleted key
        {
            size_type erasedNum = 0;
            size_type index = bkt_num_key(key);
            node* first = buckets[index];
            if (first) 
            {
                node* cur = first;
                node* next = cur->next;
                while (next)
                {
                    if (equals(get_key(next->val), key))
                    {
                        cur->next = next->next;
                        delete_node(next);
                        next = cur->next;

                        --num_elements;
                        ++erasedNum;
                    }
                    else
                    {
                        cur = next;
                        next = next->next;
                    }
                }
                if (equals(get_key(first->val), key))    //  if delete the first node
                {
                    buckets[index] = first->next;
                    delete_node(first);
                    
                    --num_elements;
                    ++erasedNum;
                }
            }
            return erasedNum;
        }
    
        void erase(const iterator& it)      //  return void
        {
            //             Key key = get_key(it.m_cur->val);
            //             erase(key);
            size_type index = bkt_num(it.m_cur->val);
            node* first = buckets[index];
            if (it.m_cur && first)      //  it.m_cur can not be NULL 
            {
                node* cur = first;
                node* next = cur->next;
                while (next)
                {
                    if (next == it.m_cur)
                    {
                        cur->next = next->next; 
                        delete_node(next);
                        next = cur->next;

                        --num_elements;
                        break;          //  break
                    }
                    else
                    {
                        cur = next;
                        next = next->next;
                    }
                }   

                if (first == it.m_cur)  //  delete the first node
                {
                    buckets[index] = first->next;
                    delete_node(first);
                    
                    --num_elements;
                }
            }
        }
            
    private:
        //  erase the [first, last) elements in the bucket[n]
        void erase_bucket(const size_type n, node* first, node* last)
        {
            if (first == last)
                return;

            node* cur = buckets[n];
            if (cur == first)   //  if first == buckets[n]
            {
                while (cur != last)
                {
                    buckets[n] = cur->next;
                    delete_node(cur);
                    cur = buckets[n];

                    --num_elements;
                }
                
            }
            else    //  else, first != buckets[n]
            {
                node* next = cur->next;
                for (; next != first; cur = next, next = next->next);    //  find the precursor node of the first
                while (next != last)
                {
                    cur->next = next->next;
                    delete_node(next);
                    next = cur->next;

                    --num_elements;
                } 
            }
          
        }
    
        void erase_bucket(const size_type n, node* last)
        {

        }

    public:
        void erase(iterator first, iterator last)
        {
//             //  error, the first will be destroyed.
//             for (; first != last; ++first)
//             {
//                 erase(first);
//             }
            
//             //  bad performance, ++first, erase(first) do some same work.
//             while (first != last)
//             {
//                 iterator next = ++first;
//                 erase(first);
//                 first = next;
//             }

            //  the best way
            size_type first_index = bkt_num(first.m_cur->val);  //  first can not be iterator(NULL, this).
            //  if last.m_cur == NULL, last_index = buckets.size() - 1;
            size_type last_index = last.m_cur ? bkt_num(last.m_cur->val) : buckets.size() - 1;  
           
            if (first_index == last_index)      
            {
                erase_bucket(first_index, first.m_cur, last.m_cur);
            }
            else
            {
                erase_bucket(first_index, first.m_cur, NULL);

                size_type bucket_index = first_index + 1;
                for (; bucket_index < last_index; ++bucket_index)
                {
                    erase_bucket(bucket_index, buckets[bucket_index], NULL);
                }
                erase_bucket(last_index, buckets[bucket_index], last.m_cur);
            }
        }

        void clear()
        {
            //  erase(begin(), end());
            size_type bCount = bucket_count();
            for (size_type index = 0; index < bCount; ++index)
            {
                for (node* cur = buckets[index]; cur;)
                {
                    node* next = cur->next;
                    delete_node(cur);
                    cur = next;
                }
                buckets[index] = (node*)0;
            }
            num_elements = 0;
        }

    //////////////////////////////////////////////////////////////////////
    //  find
    public:
        iterator find(const Key& key) 
        {
            size_type index = bkt_num_key(key);
            node* cur = buckets[index];
            for (; cur && !equals(get_key(cur->val), key); cur = cur->next);
            return iterator(cur, this);
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
        void resize(size_type n)
        {
            size_type bucketsSize = buckets.size();
            size_type maxSize = bucketsSize;
            if (n > maxSize)
            {
                size_type newSize = n + 3;  //  newSize = next_size(newSize);
                //  note!
                //  if the the list use the head node, it will cause bad performance like initialize_bucket()
                vector<node*, allocator<node*> > temp(newSize, (node*)0);
                
                for (size_type index = 0; index < bucketsSize; ++index)
                {
                    node* first = buckets[index];
                    while (first)
                    {
                        size_type new_bucket = bkt_num(first->val, newSize);
                        buckets[index] = first->next;
                        
                        first->next = temp[new_bucket];
                        temp[new_bucket] = first;

                        first = buckets[index];
                    }
                }
                //  swap
                buckets.swap(temp);
            }
        }           
        
    //////////////////////////////////////////////////////////////////////
    //  memory operation
    private:
        node* new_node(const value_type& value)
        {
            node* newNode = node_allocator::allocate(1);

            construct(&newNode->val, value);
            newNode->next = NULL;

            return newNode;
        }      
    
        void delete_node(node* deleteNode)
        {
            destroy(&deleteNode->val);
            node_allocator::deallocate(deleteNode, 1);
        }

    //////////////////////////////////////////////////////////////////////
    //  print the hashtable, just for test.
    public:
        void show()
        {
            for (size_type index = 0; index < bucket_count(); ++index)
            {
                cout << index << ":" << "\t";
                for (node* cur = buckets[index]; cur; cur = cur->next)
                {
                    cout << cur->val << "\t";
                }
                cout << endl;
            }
        }
    };
    
    //////////////////////////////////////////////////////////////////////
    //  hash, functional
    template<class Key>
    struct hash {};

    template<>
    struct hash<int>
    {
        size_t operator () (int x) const {return x;}
    };

    template<>
    struct hash<unsigned int>
    {
        size_t operator ()(unsigned int x) const {return x;}
    };

    template<>
    struct hash<short>
    {
        size_t operator ()(short x) const {return x;}
    };

    template<>
    struct hash<unsigned short>
    {
        size_t operator ()(unsigned short x) const {return x;}
    };

    template<>
    struct hash<long>
    {
        size_t operator ()(long x) const {return x;}
    };

    template<>
    struct hash<unsigned long>
    {
        size_t operator ()(unsigned long x) const {return x;}
    };

    template<>
    struct hash<char>
    {
        size_t operator ()(char x) const {return x;}
    };

    template<>
    struct hash<signed char>
    {
        size_t operator ()(signed char x) const {return x;}
    };

    template<>
    struct hash<unsigned char>
    {
        size_t operator ()(unsigned char x) const {return x;}
    };

    //  char *
    inline size_t hash_string(const char *s)
    {
        unsigned long h = 0;
        for (; *s; ++s)
        {
            h = 5 * h + *s;
        }
        return size_t(h);
    }

    template<>
    struct hash<char*>
    {
        size_t operator ()(char *s) const {return hash_string(s);}
    };

    template<>
    struct hash<const char*>
    {
        size_t operator ()(const char *s) const {return hash_string(s);}
    };

    //  define yourself type
    template<>
    struct hash<const String>
    {
        size_t operator ()(const String s) const {return hash_string(s.str());}
    };

    template<>
    struct hash<String>
    {
        size_t operator () (String s) const {return hash_string(s.str());}
    };   
}


//////////////////////////////////////////////////////////////////////

#endif