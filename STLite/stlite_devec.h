/********************************************************************
	Time:	  2015/12/02
	Filename: devec
	Author:	  dinglj
	
	Purpose:  the improvement of the vector
              it can improve the efficiency when inserting the elements close to the head 
*********************************************************************/
#ifndef _STLITE_DEVEC_H_
#define _STLITE_DEVEC_H_

#include "common_header_files.h"
#include "stlite_iterator.h"
#include "stlite_alloc.h"
#include "stlite_type_traits.h"

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
        devecIterator & operator +=(int n)
        {
            m_index = (m_index + n) % m_container->capacity();
            m_ptr = m_container->start_of_storage + m_index;

            return *this;
        }

        devecIterator & operator -=(int n)
        {
            return *this += (-n);
        }

        //  it should support n + iterator
        devecIterator operator +(int n)
        {
            devecIterator temp(*this);
            return temp += n;
        }
        
        devecIterator operator -(int n)
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
            destroy(start_of_storage + start, start_of_storage + finish);
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
        int capacity() const
        {
            return end_of_storage - start_of_storage;
        }

        int size() const
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
    };
}

#endif