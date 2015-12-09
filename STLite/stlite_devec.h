/********************************************************************
	Time:	  2015/12/02
	Filename: devec
	Author:	  dinglj
	
	Purpose:  the improvement of the vector
              it can improve the efficiency when inserting the elements close to the head 
*********************************************************************/
#ifndef _STLITE_DEVEC_H_
#define _STLITE_DEVEC_H_

#include <crtdefs.h>    //  std::ptrdiff_t

#include "common_header_files.h"

#include "stlite_algorithm.h"
#include "stlite_alloc.h"
#include "stlite_construct.h"
#include "stlite_iterator.h"    
#include "stlite_type_traits.h"          
#include "stlite_uninitialized.h"

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
        int m_index;      //  because the m_ptr is circular, so it need a index.
        typedef devec<T, Alloc> devec;
        devec *m_container;  //  the devecIterator should know the devec's attribute, so it should contain the *vec.
    
    //  member function
        //  constructor
        devecIterator() : m_container(NULL), m_ptr(NULL), m_index(0) {}
        devecIterator(devec *container, int index)
        {
            m_container = container;
            m_index = index;
            m_ptr = m_container->start_of_storage + index;
        }
        // copy, assignment, destructor use the default version    
        
        //  defer
        reference operator *()
        {
            return *m_ptr;
        }

        pointer operator ->()
        {
            return m_ptr;
        }

        //  ++,--
        devecIterator & operator ++()
        {
            m_index = (m_index + 1) % m_container->capacity();
            m_ptr = m_container->start_of_storage + m_index;

            return *this;
        }

        devecIterator operator ++(int)
        {
            devecIterator temp(m_container, m_index);
            m_index = (m_index + 1) % m_container->capacity();
            m_ptr = m_container->start_of_storage + m_index;

            return temp;
        }

        devecIterator &operator --()
        {
            m_index = (m_index - 1 + m_container->capacity()) % m_container->capacity();
            m_ptr = m_container->start_of_storage + m_index;

            return *this;
        }

        devecIterator operator --(int)
        {
            devecIterator temp(m_container, m_index);
            m_index = (m_index - 1 + m_container->capacity()) % m_container->capacity();
            m_ptr = m_container->start + m_index;

            return temp;
        }
        
        //  =, !=
        bool operator ==(const devecIterator &lhs) const
        {
            return m_container == lhs.m_container && m_ptr == lhs.m_ptr;
        }

        bool operator !=(const devecIterator &lhs) const
        {
            return m_container == lhs.m_container && m_ptr != lhs.m_ptr;
        }   

        //////////////////////////////////////////////////////////////////////
        //  RandomAccessIterator's properties
        //  + n, - n
        devecIterator & operator +=(difference_type n)
        {
            m_index = (m_index + n + m_container->capacity()) % m_container->capacity();
            m_ptr = m_container->start_of_storage + m_index;

            return *this;
        }

        devecIterator & operator -=(difference_type n)
        {
            return *this += (-n);
        }

        //  it should support n + iterator
        devecIterator operator +(difference_type n)
        {
            devecIterator temp(*this);
            return temp += n;
        }
        
        devecIterator operator -(difference_type n)
        {
            devecIterator temp(*this);
            return temp -= n;
        }
        
        //  an important function
        typename devec::size_type true_index() const
        {
            if (m_index >= m_container->start)
            {
                return m_index - m_container->start;
            }
            else
            {
                return m_index + m_container->capacity() - m_container->start;
            }
        }
        
        //  iterator1 - iterator2      
        difference_type operator -(const devecIterator &lhs)
        {
            return true_index() - lhs.true_index();
        }

        //  comparison
        bool operator < (const devecIterator &lhs) const
        {
            return m_container == lhs.m_container && true_index() < lhs.true_index();
        }
        
        bool operator <=(const devecIterator &lhs) const
        {
            return m_container == lhs.m_container && true_index() <= lhs.true_index();
        }

        bool operator > (const devecIterator &lhs) const
        {
            return m_container == lhs.m_container && true_index() > lhs.true_index();
        }

        bool operator >= (const devecIterator &lhs) const
        {
            return m_container == lhs.m_container && true_index() >= lhs.true_index();
        }

        //  []
        reference operator [](difference_type n)
        {
            pointer temp = m_ptr + (m_container->start + n) % m_container->capacity();
            return *temp;
        }
    };
  
    //  operator +, non_member function, supports n + iterator.
    template<class T, class Alloc>
    inline devecIterator<T, Alloc> operator +(typename devecIterator<T, Alloc>::difference_type n,
                                              devecIterator<T, Alloc> lhs)  //  const devecIterator<T, Alloc> &lhs
    {
            return lhs + n;
    }

   
    //////////////////////////////////////////////////////////////////////
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
    //  private:    //  in order to test, declare them public temporary
    public:
        //  memory space
        pointer start_of_storage;
        pointer end_of_storage;

        //  object space
        int start;
        int finish;
    //////////////////////////////////////////////////////////////////////
    //  iterator 
    public:
        typedef devecIterator<T, Alloc> iterator;
    //////////////////////////////////////////////////////////////////////
    //  allocator
    public:
        typedef allocator<T> data_allocator;

    //////////////////////////////////////////////////////////////////////
    //  member function
    //  constructor, copy constructor, assignment, destructor
    private:
        void allocate_and_fill(size_type n, const value_type &value)
        {
            start_of_storage = data_allocator::allocate(n + 1);     //  a free space, to determine full or empty
            uninitialized_fill_n(start_of_storage, n, value);
            end_of_storage = start_of_storage + n + 1;
            
            start = 0;
            finish = start + n;
        }

        template<class ForwardIterator>
        void allocate_and_copy(ForwardIterator first, ForwardIterator last, forward_iterator_tag)
        {
            difference_type n = distance(first, last);
            start_of_storage = data_allocator::allocate(n + 1);
            uninitialized_copy(first, last, start_of_storage);
            end_of_storage = start_of_storage + n + 1;

            start = 0;
            finish = start + n;
        }

        void destroy_and_deallocate()
        {
            destroy(begin(), end());
            data_allocator::deallocate(start_of_storage, end_of_storage - start_of_storage);
        }

    private:
        template<class Integer>
        void devec_aux(Integer n, const value_type &value, __true_type)
        {
            allocate_and_fill(n, value);
        }

        template<class InputIterator>
        void devec_aux(InputIterator first, InputIterator last, __false_type)
        {
            typedef iterator_traits<InputIterator>::iterator_category category;
            allocate_and_copy(first, last, category());
        }

    public:
        //  constructor
        devec() : start_of_storage(0), end_of_storage(0), start(0), finish(0) {}

        devec(int n, const value_type &value)
        {
            devec_aux(n, value, __true_type());
        }

        devec(int n)
        {
            devec_aux(n, value_type());
        }

        template<class InputIterator>
        devec(InputIterator first, InputIterator last)
        {
            typedef typename _is_integer<InputIterator>::is_integer is_integer;
            devec_aux(first, last, is_integer());
        }

        //  copy constructor
        devec(const devec &lhs)
        {
            devec_aux(lhs.start_of_storage + start, lhs.start_of_storage + finish);
        }

        ~devec()
        {
            destroy_and_deallocate();
        }
    //////////////////////////////////////////////////////////////////////
    //  iterators
    //  begin, end
        iterator begin()
        {
            return iterator(this, start);
        }

        iterator end()
        {
            return iterator(this, finish);
        }
    //////////////////////////////////////////////////////////////////////
    //  Capacity
    //  size, capacity, empty, full
    public:
        size_type capacity() const
        {
            return end_of_storage - start_of_storage;
        }

        size_type size() const
        {
            return finish > start ? (finish - start) : (finish + capacity() - start);
        }

        bool empty() const
        {
            return start == finish;
        }

        bool full() const
        {
            return size() + 1 == capacity();
        }
    //////////////////////////////////////////////////////////////////////
    //  modifiers
    //  insert, erase, assign, push, pop, clear
    
    //  insert
    private:
        template<class ForwardIterator>
        void range_insert(iterator pos, ForwardIterator first, ForwardIterator last, forward_iterator_tag)
        {
            size_type spaceNeed = (size_type)distance(first, last);
            size_type spaceLeft = capacity() - size() - 1;  //  note, left a space!

            if (spaceLeft >= spaceNeed)
            {
                //  an more complex but higher performance way
                size_type numOfBack = (size_type)(end() - pos);
                if (numOfBack <= (size() >> 1))     //  move [pos, end())
                {
                    size_type objInsert = spaceNeed;
                    size_type objBack = numOfBack;
                    
                    iterator endIterator = end();

                    if (objBack >= objInsert)
                    {
                        //  [end() - objInsert, end()) -> [end(), end() + objInsert)
                        //  [pos, end() - objInsert) -> [pos + objInsert, end())
                        //  [first, last) -> [pos, pos + objInsert)

                        uninitialized_copy(endIterator - objInsert, endIterator, endIterator);
                        copy_backward(pos, endIterator - objInsert, endIterator);
                        copy(first, last, pos);
                    }
                    else
                    {
                        //  [first + objBack, last) -> [end(), end() + (objInsert - objBack))
                        //  [pos, end()) -> [end() + (objInsert - objBack), ...)
                        //  [first, first + objBack) -> [pos, pos + objBack)
                        uninitialized_copy(pos, endIterator, uninitialized_copy(first + objBack, last, endIterator));
                        copy(first, first + objBack, pos);
                    }
                    finish = (finish + objInsert) % capacity();
                }
                else    //  move [begin(), pos)
                {
                    iterator beginIterator = begin();

                    size_type objInsert = spaceNeed;
                    size_type objFront = pos - beginIterator;

                    if (objFront >= objInsert)
                    {
                        uninitialized_copy_backward(beginIterator, beginIterator + objInsert, beginIterator);
                        copy(beginIterator + objInsert, pos, beginIterator);
                        copy_backward(first, last, pos);
                    }
                    else
                    {
                        uninitialized_copy_backward(beginIterator, pos, 
                                            uninitialized_copy_backward(first, last - objFront, beginIterator));
                        copy(last - objFront, last, beginIterator);
                    }
                    start = (start - objInsert + capacity()) % capacity();
                }

                //  an easier but low performance way 
//                 size_type numOfBack = (size_type)(end() - pos);
//                 if (numOfBack <= (size() >> 1))     //  move [pos, end())
//                 {
//                     iterator endIterator = end();
//                     devec<T, Alloc> temp(pos, endIterator);
//                     destroy(pos, endIterator);
//                                         
//                     uninitialized_copy(temp.begin(), temp.end(), uninitialized_copy(first, last, pos));
//                     finish = (finish + spaceNeed) % capacity();
//                 }
//                 else    //  move [begin(), pos)
//                 {
//                     iterator beginIterator = begin();
//                     devec<T, Alloc> temp(beginIterator, pos);
//                     destroy(beginIterator, pos);
//                     
//                     uninitialized_copy_backward(temp.begin(), temp.end(), 
//                                                 uninitialized_copy_backward(first, last, pos));
//                     start = (start - spaceNeed + capacity()) % capacity();
//                 }
            }   
            else
            {
                size_type oldSize = size();
                size_type newSize = oldSize + spaceNeed;
                size_type newCapacity = oldSize + std::max(oldSize, spaceNeed) + 1;
                
                //  allocate new space
                pointer new_start_of_storage = data_allocator::allocate(newCapacity);
                pointer new_end_of_storage = new_start_of_storage + newCapacity;

                //  initialize objects
                pointer pos1 = uninitialized_copy(begin(), pos, new_start_of_storage);
                pointer pos2 = uninitialized_copy(first, last, pos1);
                uninitialized_copy(pos, end(), pos2);
             
                //  destroy old devec
                destroy_and_deallocate();
                
                //  initialize new devec
                start_of_storage = new_start_of_storage;
                end_of_storage = new_end_of_storage;
                start = 0;
                finish = start + newSize;
            }    
        }
        
        template<class Integer>
        void fill_insert(iterator pos, Integer n, const value_type &value)
        {
            size_type spaceNeed = n;
            size_type spaceLeft = capacity() - size() - 1;
            if (spaceLeft >= spaceNeed)
            {
                size_type numOfBack = end() - pos;
                if (numOfBack <= (size() >> 1))     //  move backward
                {
                    size_type objInsert = n;
                    size_type objBack = numOfBack;
                    iterator endIterator = end();

                    if (objBack >= objInsert)
                    {
                        uninitialized_copy(endIterator - objInsert, endIterator, endIterator);
                        copy_backward(pos, endIterator - objInsert, endIterator);
                        fill_n(pos, objInsert, value);
                    }
                    else
                    {
                        uninitialized_copy(pos, endIterator,
                            uninitialized_fill_n(endIterator, objInsert - objBack, value));
                        fill_n(pos, objBack, value);
                    }
                    finish = (finish + objInsert) % capacity();
                }
                else    //  move forward
                {
                    iterator beginIterator = begin();
                    size_type objInsert = n;
                    size_type objFront = pos - beginIterator;

                    if (objFront >= objInsert)
                    {
                        uninitialized_copy_backward(beginIterator, beginIterator + objInsert, beginIterator);
                        copy(beginIterator + objInsert, pos, beginIterator);
                        fill_n_backward(pos, objInsert, value);
                    }
                    else
                    {
                        uninitialized_copy_backward(beginIterator, pos, 
                            uninitialized_fill_n_backward(beginIterator, objInsert - objFront, value));
                        fill_n(beginIterator, objFront, value);
                    }
                    start = (start - objInsert + capacity()) % capacity();
                }
            }
            else    //  if (spaceLeft >= spaceNeed)
            {
                size_type oldSize = size();
                size_type newSize = oldSize + spaceNeed;
                size_type newCapacity = oldSize + std::max(oldSize, spaceNeed) + 1;

                pointer new_start_of_storage = data_allocator::allocate(newCapacity);
                pointer new_end_of_storage =  new_start_of_storage + newCapacity;

                pointer pos1 = uninitialized_copy(begin(), pos, new_start_of_storage);
                pointer pos2 = uninitialized_fill_n(pos1, n, value);
                uninitialized_copy(pos, end(), pos2);

                destroy_and_deallocate();

                start_of_storage = new_start_of_storage;
                end_of_storage = new_end_of_storage;
                start = 0;
                finish = start + newSize;
            }
        }

    private:
        template<class InputIterator>
        void insert_dispatch(iterator pos, InputIterator first, InputIterator last, __false_type)
        {
            typedef typename iterator_traits<InputIterator>::iterator_category category;
            range_insert(pos, first, last, category());
        }           

        template<class Integer>
        void insert_dispatch(iterator pos, Integer n, const value_type &value, __true_type)
        {
            fill_insert(pos, n, value);
        }

    public:
        template<class InputIterator>
        void insert(iterator pos, InputIterator first, InputIterator last)
        {
            typedef typename _is_integer<InputIterator>::is_integer is_integer;
            insert_dispatch(pos, first, last, is_integer());
        }
        
        void insert(iterator pos, size_type n, const value_type &value)
        {
            insert_dispatch(pos, n, value, __true_type());
        }

        void insert(iterator pos, const value_type &value)
        {
            insert(pos, 1, value);
        }

        //////////////////////////////////////////////////////////////////////
        //  erase
    public:
        iterator erase(iterator first, iterator last)
        {
            iterator beginIterator = begin();
            iterator endIterator = end();
            size_type objFront = first - beginIterator;
            size_type objBack = endIterator - last;
            size_type objErase = last - first;

            if (objBack < objFront)    //  move forward
            {
                iterator pos = copy(last, endIterator, first);
                destroy(pos, endIterator);
                finish = (finish - objErase + capacity()) % capacity();

                return first;
            }
            else    // move backward
            {
                iterator pos = copy_backward(beginIterator, first, last);
                destroy(beginIterator, pos);
                start = (start + objErase) % capacity();

                return last;
            }
        }
        
        iterator erase(iterator pos)
        {
            return erase(pos, pos + 1);
        }
    };
}

#endif