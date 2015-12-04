/********************************************************************
	Time:	  2015/10/26
	Filename: stlite_vector
	Author:	  dinglj
	
	Purpose:  vector µœ÷
*********************************************************************/
#ifndef _STLITE_VECTOR_H_
#define _STLITE_VECTOR_H_

#include <crtdefs.h>                //  std::ptrdiff_t

#include "commom_header_files.h"
#include "stlite_iterator.h"        //  iterator  
#include "stlite_alloc.h"           //  allocator
#include "stlite_uninitialized.h"   //  uninitialized_fill_n
#include "stlite_type_traits.h"
#include "stlite_algorithm.h"       //  fill 

//////////////////////////////////////////////////////////////////////
namespace STLite
{
    //////////////////////////////////////////////////////////////////////
    //  vectorIterator
    template<class T>
    //  class vectorIterator : public iterator<random_access_iterator<T, std::ptrdiff_t>, T>
    class vectorIterator : public iterator<random_access_iterator_tag, T>
    {
//      private:
//          T *m_ptr;
    public:
        value_type *m_ptr;
    //////////////////////////////////////////////////////////////////////
    //  note, vectorIterator is NOT a smart pointer, it is not responsible for allocating and deallocating memory.
    public:
        //  construct
        explicit vectorIterator(T *ptr = NULL) : m_ptr(ptr) {}
   
        //  copy
        vectorIterator(const vectorIterator &vIter)
        {
            m_ptr = vIter.m_ptr;
        }

        // assignment
        vectorIterator & operator =(const vectorIterator &vIter)
        {
            m_ptr = vIter.m_ptr;
            return *this;
        }

        //  destroy, do nothing,
        ~vectorIterator() { }
    //////////////////////////////////////////////////////////////////////
    //  defer
    public:
        reference operator *()      
        {
            return *m_ptr;
        }
        pointer operator ->()
        {
            return m_ptr;
        }
    //////////////////////////////////////////////////////////////////////
    //  ++,--
    public:
        vectorIterator & operator ++()      //  ++prefix
        {
            m_ptr++;
            return *this;
        }
        vectorIterator operator ++(int)     //  postfix++
        {
            vectorIterator temp = *this;
            ++(*this);
            return temp;
        }

        vectorIterator & operator --()
        {
            m_ptr--;
            return *this;
        }
        vectorIterator operator --(int)
        {
            vectorIterator temp = *this;
            --(*this);
            return temp;
        }
    //////////////////////////////////////////////////////////////////////
    //  random access operation, only the RandomAccessIterator supports.
    public:
        vectorIterator & operator +=(difference_type n)
        {
            m_ptr += n;
            return *this;
        }

        vectorIterator operator +(difference_type n) const
        {
            vectorIterator temp = *this;    //  call operator +=(difference_type n)
            return temp += n;
        }

        difference_type operator +(const vectorIterator &lhs) const     //  
        {
            return m_ptr + lhs.m_ptr;
        }
        //////////////////////////////////////////////////////////////////////
        vectorIterator & operator -=(difference_type n)
        {
            return *this += -n;    //  call operator +=(difference_type n)
        }

        vectorIterator operator -(difference_type n) const
        {
            vectorIterator temp = *this;    //  call operator -=(difference_type n)
            return temp -= n;
        }
        
        difference_type operator -(const vectorIterator &lhs) const     //  
        {
            return m_ptr - lhs.m_ptr;
        }
        //////////////////////////////////////////////////////////////////////
        reference operator [](difference_type n) const
        {
            return *(*this + n);
        }
    //////////////////////////////////////////////////////////////////////
    //  operator ==, !=£¨ <, >,  <=, >=
    public:
        bool operator ==(const vectorIterator &lhs) const
        {
            return m_ptr == lhs.m_ptr;
        }

        bool operator !=(const vectorIterator &lhs) const
        {
            return !(*this == lhs);
        }

        bool operator <(const vectorIterator &lhs) const
        {
            return m_ptr < lhs.m_ptr;
        }

        bool operator >(const vectorIterator &lhs) const
        {
            return m_ptr > lhs->m_ptr;
        }

        bool operator <=(const vectorIterator &lhs) const
        {
            return operator <(lhs) || operator ==(lhs);
        }

        bool operator >=(const vectorIterator &lhs) const
        {
            return operator >(lhs) || opearator ==(lhs);
        }
    };

    template<class T>
    vectorIterator<T> operator +(typename vectorIterator<T>::difference_type n, vectorIterator<T> lhs)
    {
        return lhs + n;                                             //  const vectorIterator<T> &lhs
    }
    //////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////
    //  vector
    template<class T, class Alloc = allocator<T>>
    class vector
    {
    //////////////////////////////////////////////////////////////////////
    //  
    public:
        typedef T               value_type;
        typedef T*              pointer;
        typedef T&              reference;
        typedef size_t          size_type;
        typedef std::ptrdiff_t  difference_type;

    //////////////////////////////////////////////////////////////////////
    //   in order to test, declare them as public data
    public:
        pointer start;
        pointer finish;
        pointer end_of_storage;
    
    //////////////////////////////////////////////////////////////////////
    //  iterator
    public:
        typedef vectorIterator<T> iterator;
    
    //////////////////////////////////////////////////////////////////////
    //  allocator
    typedef allocator<T> data_allocator;

    //////////////////////////////////////////////////////////////////////
    //  private member function
    private:
        pointer allocate(size_type n)
        {
            return data_allocator::allocate(n);
        }
        
        void deallocate()
        {
            data_allocator::deallocate(start, end_of_storage - start);
        }
        //////////////////////////////////////////////////////////////////////
        
        void allocate_and_fill(size_type n, const value_type &value)
        {
            start = allocate(n);
            uninitialized_fill_n(start, n, value);
            
            finish = start + n;
            end_of_storage = finish;
        }
 
        //   in SGI STL, the InputIterator and the ForwardIterator have different allocate_adn_copy version   
        template<class InputIterator>
        void allocate_and_copy(InputIterator first, InputIterator last, input_iterator_tag)
        {
            //  do something, different from ForwardIterator
            //  because Input iterators are iterators that can be used in sequential input operations, 
            //  where each value pointed by the iterator is read only once and then the iterator is incremented.
            
            //  like this
//             for (; first != last; first++)
//             {
//                 push_back(*first); 
//             }

        }

        template<class ForwardIterator>
        void allocate_and_copy(ForwardIterator first, ForwardIterator last, forward_iterator_tag)
        {
            size_type n = (size_type) distance(first, last);
            
            start = allocate(n);
            finish = uninitialized_copy(first, last, start);
            end_of_storage = start + n;
        }

        //////////////////////////////////////////////////////////////////////
        void destroy_and_deallocate()
        {
            if (start != end_of_storage)
            {
                destroy(start, finish); 
                deallocate();
            }
        }
        //////////////////////////////////////////////////////////////////////
        //  override vector_aux
        template<class Integer>
        void vector_aux(Integer n, const value_type &value, __true_type)
        {
            allocate_and_fill(n, value);
        }
        
        template<class InputIterator>
        void vector_aux(InputIterator first, InputIterator last, __false_type)
        {
            typedef typename iterator_traits<InputIterator>::iterator_category category;
            allocate_and_copy(first, last, category());
        }   

    //////////////////////////////////////////////////////////////////////
    //  construct
    public: 
        vector(): start(0), finish(0), end_of_storage(0) { }
        explicit vector(size_type n)
        {
            vector_aux(n, value_type(), __true_type());
        }
    
        vector(size_type n, const value_type &value)
        {
            vector_aux(n, value, __true_type());
        }
        template<class InputIterator>
        vector(InputIterator first, InputIterator last)     
        {
            //  to determine call vector_aux(size_type, value_type) or vector_aux(iterator, iterator)
            typedef typename _is_integer<InputIterator>::is_integer is_integer;   
            vector_aux(first, last, is_integer());
        }
        
        //  copy
        vector(const vector &lhs)
        {
        //    allocate_and_copy(lhs.start, lhs.finish, iterator_category(iter));
            start = allocate(lhs.finish - lhs.start);
            finish = uninitialized_copy(lhs.start, lhs.finish, start);
            end_of_storage = finish;
        }
    
        //  assignment, it should destruct the old objects and deallocate the old memory.
        vector & operator =(const vector &lhs)
        {
            //  allocate new memory, construct objects.
            pointer new_start = allocate(lhs.finish - lhs.start);
            pointer new_finish = uninitialized_copy(lhs.start, lhs.finish, new_start);
            pointer new_end_of_storage = new_finish;
        
            //  destruct old objects and deallocate old memory.
            destroy_and_deallocate();
    
            //  assign
            start = new_start;
            finish = new_finish;
            end_of_storage = new_end_of_storage;

            return *this;

//             //  it can also rewrite like this.
//             if (&lhs != this)   //  check self assignment
//             {
//                 vector<T> temp(lhs);    //  a temp vector, it will destroy when the function return
//                 
//                 std::swap(start, temp.start);
//                 std::swap(finish, temp.finish);
//                 std::swap(end_of_storage, temp.storage);
//             }
//             return *this;
            
            //  the SGI STL has a higher performance but more complex way.
            //  see range_assign()
        }

        ~vector()
        {
            destroy_and_deallocate();
        }

    //////////////////////////////////////////////////////////////////////
    //  iterators
    public:
        iterator begin()
        {
            return iterator(start);
        }
        
        iterator end()
        {
           return iterator(finish);
        }

    //////////////////////////////////////////////////////////////////////
    //  element access
    public:
        reference operator [](size_type n)
        {
            return *(start + n);
        }

        reference at(size_type n)
        {
            return operator [](n);  //  call operator [](n)
        }

        //  
        reference front()
        {
            return *begin();
        }

        reference back()
        {
            return *(end() - 1);
        }
    //////////////////////////////////////////////////////////////////////
    //  Capacity
    public:
        size_type size() const
        {
            return size_type(finish - start);
        }

        size_type max_size() const
        {
            return size_type(-1) / sizeof(value_type);
        }

        bool empty() const
        {
            return 0 == size();
        }

        void resize(size_type n, const value_type &x)
        {
            if (n < size())
            {
                erase(begin() + n, end());
            }
            else
            {
                insert(end(), n - size(), x);
            }
        }

        void resize(size_type new_size)
        {
            resize(new_size, value_type());
        }
        //////////////////////////////////////////////////////////////////////
        size_type capacity() const
        {
            return size_type(end_of_storage - start);
        }

        void reserve(size_type n)
        {
            if (capacity() < n)     //  reserve can only add capacity
            {
                //  allocate new space
                pointer new_start = allocate(n);
                pointer new_end_of_storage = new_start + n;
                
                //  copy
                pointer new_finish = uninitialized_copy(start, finish, new_start);
                
                //  free old space
                destroy_and_deallocate();
                
                //  init new space
                start = new_start;
                finish = new_finish;
                end_of_storage = new_end_of_storage;
            }
        }
    //////////////////////////////////////////////////////////////////////
    //  Modifiers
    //  insert 
    private:
        void fill_insert(iterator pos, size_type n, const T &value)
        {
            size_type locationLeft = end_of_storage - finish;
            size_type locationNeed = n;

//             if (locationNeed <= locationLeft)
//             {
//                 iterator temp = pos;     //  [pos, finish) -> [pos + locationNeed, finish + locationNeed)
//                 while (temp != end())
//                 {
//                     *(temp + locationNeed) = *(temp);   
//                     temp++;
//                     //  bug1, [finish, finish + locationNeed) is the uninitialized range,
//                     //  it can not call operator = on this range,
//                     //  it will cause delete WILD(wild) pointer. see the definition of String
//                 }
//                 //  bug2, [pos, finish) is the initialized range, 
//                 //  it can not call constructor on this range,
//                 //  it will cause memory leak. see the definition of String.
//                 uninitialized_fill_n(pos, locationNeed, value);
// 
//                 finish = finish + locationNeed;
//             }
            if (locationNeed <= locationLeft)
            {
                vector<T> temp(pos, end());
                destroy(pos, end());    //  now, [pos, end_of_storage) is uninitialized range
                
                //  insert new elements on the uninitialized range
                iterator new_finish = uninitialized_fill_n(pos, n, value);
                
                //  copy old elements on the uninitialized range
                new_finish = uninitialized_copy(temp.begin(), temp.end(), new_finish);
                finish = new_finish.m_ptr;

                //  this way is easy, but it may cause bad performance when the insert position close to start.
                //  but we always use the INSERT to init the vector and in the function push_back,
                //  in this case, the INSERT perform well.

                //  the SGI STL offer a higher performance but more complex INSERT version.
            }
            else
            {
                size_type old_size = size();
                size_type new_capacity = old_size + std::max(old_size, locationNeed);
                
                //  allocate new space
                pointer new_start = allocate(new_capacity);  
                pointer new_end_of_storage = new_start + new_capacity;
                
                //  copy and fill
                pointer new_finish = uninitialized_copy(begin(), pos, new_start);
                new_finish = uninitialized_fill_n(new_finish, n, value);
                new_finish = uninitialized_copy(pos, end(), new_finish);
                
                //  free old space
                destroy_and_deallocate();

                //  init new space
                start = new_start;
                finish = new_finish;
                end_of_storage = new_end_of_storage;
            }
        }
        //////////////////////////////////////////////////////////////////////
        //  the SGI STL has different range_insert version for InputIterator & ForwardIterator
        template<class InputIterator>
        void range_insert(iterator pos, InputIterator first, InputIterator last, input_iterator_tag)
        {
            //  can not calculate the capacity that the new elements need, it only can be inserted one by one 

            //  insert one by one, like this
//             for (; first != last; first++)
//             {
//                 pos = insert(pos, *first);
//                 ++pos;
//             }
        }

        template<class ForwardIterator>
        void range_insert(iterator pos, ForwardIterator first, ForwardIterator last, forward_iterator_tag)
        {
            size_type locationLeft  = end_of_storage - finish;
            size_type locationNeed = (size_type) distance(first, last);
           
            //  bug, see fill_insert
//             if (locationNeed <= locationLeft)
//             {
//                 iterator temp = pos;
//                 while (temp != end())
//                 {
//                     *(temp + locationNeed) = *(temp);
//                     temp++;
//                 }
//                 STLite::uninitialized_copy(first, last, pos);
//                 finish = finish + locationNeed;
//             }
            if (locationNeed <= locationLeft)
            {
                vector<T> temp(pos, end());
                destroy(pos, end());
                iterator new_finish = uninitialized_copy(first, last, pos);
                new_finish = uninitialized_copy(temp.begin(), temp.end(), new_finish);
                finish = new_finish.m_ptr;    
            }
            else
            {
                size_type old_size = size();
                size_type new_capacity = old_size + std::max(old_size, locationNeed);
                
                //  allocate new space
                pointer new_start = allocate(new_capacity);
                pointer new_end_of_storage = new_start + new_capacity;
                
                //  copy
                pointer new_finish = STLite::uninitialized_copy(begin(), pos, new_start);
                new_finish = STLite::uninitialized_copy(first, last, new_finish);
                new_finish = STLite::uninitialized_copy(pos, end(), new_finish);

                //  free old space
                destroy_and_deallocate();
                
                //  init new space;
                start = new_start;
                finish = new_finish;
                end_of_storage = new_end_of_storage;
            }
        }
        //////////////////////////////////////////////////////////////////////
        template<class InputIterator> 
        void insert_dispatch(iterator pos, InputIterator first, InputIterator last, __false_type)
        {
            typedef typename iterator_traits<InputIterator>::iterator_category category;
            range_insert(pos, first, last, category());
        }
    
        template<class Integer>
        void insert_dispatch(iterator pos, Integer n, const value_type &x, __true_type)
        {
            fill_insert(pos, n, x);
        }
         
    //  insert
    public:
      
        void insert(iterator pos, size_type n, const T &value)
        {
            insert_dispatch(pos, n, value, __true_type());
        }

        template<class InputIterator>
        void insert(iterator pos, InputIterator first, InputIterator last)
        {
            typedef typename _is_integer<InputIterator>::is_integer is_integer;
            insert_dispatch(pos, first, last, is_integer());
        }

        iterator insert(iterator pos, const T &value)
        {
            insert(pos, 1, value);  //  call insert(pos, n, value)

            return pos;
        }
    //////////////////////////////////////////////////////////////////////
    //  erase
    public:
        //  note, the argument of the erase is ITERATPR(iterator),
        //  while the argument of the insert is InputIterator.
        //  because erase can only erase itself elements.
        iterator erase(iterator first, iterator last)
        {   
            //  copy and destroy
        //    iterator i = uninitialized_copy(last, end(), first);   //   bug, see fill_insert
            
            iterator i = copy(last, end(), first);
            destroy(i, end());              //  erase only destroy elements, not destroy the space!!
    
            finish = finish - (last - first);
            
            return first;
        }

        iterator erase(iterator pos)
        {
            return erase(pos, pos + 1);    //  call erase(first, last)
        }
    //  erase
    public:
        //  clear only destroy elements, not destroy space !
        void clear()
        {
            erase(begin(), end());
        }
    //////////////////////////////////////////////////////////////////////
    //  push_back, pop_back
    public:
        void push_back(const value_type &x)
        {
            insert(end(), x);
        }
        
        void pop_back()
        {
            erase(end() - 1);
        }
    
    //////////////////////////////////////////////////////////////////////
    //  assign
    //  some auxiliary functions
    private:
        void fill_assign(size_type n, const value_type &value)
        {
            if (n > capacity())
            {
                vector<T> temp(n, value);
                
                std::swap(start, temp.start);
                std::swap(finish, temp.finish);
                std::swap(end_of_storage, temp.end_of_storage);
                
                //  the temp vector will be destroyed when the func exit
            }
            else if (n > size())
            {
                fill(begin(), end(), value);
                finish = uninitialized_fill_n(finish, n - size(), value);

                //  another way, low efficiency.
                //  destroy(begin(), end());
                //  uninitialized_fill_n(begin(), n, value);
            }
            else
            {
                iterator mid = fill_n(begin(), n, value);
                erase(mid, end());
            }
        }
        
        //////////////////////////////////////////////////////////////////////
        //  the SGI STL has different range_insert version for InputIterator & ForwardIterator
        template<class InputIterator>
        void range_assign(InputIterator first, InputIterator last, input_iterator_tag)
        {
            //  InputIterator can not calculate the [first, last) 's length
//             iterator cur = begin();
//             for (; first != last && cur != end(); ++first, ++cur)
//             {
//                 *cur = *first;
//             } 
//         
//             if (first == last)          //  size() > [first, last)'s length
//             {
//                 erase(cur, end());
//             }
//             else
//             {
//                 insert(end(), first, last);     //  call range_insert(first, last, input_iterator_tag)
//             }
        }
        
        template<class ForwardIterator>
        void range_assign(ForwardIterator first, ForwardIterator last, forward_iterator_tag)
        {
            size_type n = distance(first, last);
            if (n > capacity())
            {
                vector<T> temp(first, last);
                
                std::swap(start, temp.start);
                std::swap(finish, temp.finish);
                std::swap(end_of_storage, temp.end_of_storage);    
            } 
            else if (n > size())
            {
                ForwardIterator mid = first;           
                advance(mid, size());

                copy(first, mid, start);
                finish = uninitialized_copy(mid, last, finish);
            }
            else
            {
                iterator mid = copy(first, last, begin());
                erase(mid, end());
            }
        }
        
        //////////////////////////////////////////////////////////////////////
        template<class Integer>
        void assign_dispatch(Integer n, const value_type &value, __true_type)
        {
            fill_assign(n, value);
        }

        template<class InputIterator>
        void assign_dispatch(InputIterator first, InputIterator last, __false_type)
        {
            typedef typename iterator_traits<InputIterator>::iterator_category category;
            range_assign(first, last, category());
        }
        
    //////////////////////////////////////////////////////////////////////
    //  assign
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
    };
}

#endif
