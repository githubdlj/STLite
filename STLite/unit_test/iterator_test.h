/********************************************************************
	Time:	  2015/10/21
	Filename: iterator_test
	Author:	  dinglj
	
	Purpose:  test iterator_traits
*********************************************************************/

#ifndef _PUBLIC_ITERATOR_TEST_H_
#define _PUBLIC_ITERATOR_TEST_H_

#include "common_header_files.h"
#include "common_data.h"
#include "../stlite_iterator.h"

//////////////////////////////////////////////////////////////////////
namespace iterator_public
{
    //  the simple MyIterator inherit the iterator, and is a RadomAccessIterator
    template<class T>
    class MyIterator : public iterator<random_access_iterator_tag, T>
    {
    private:
        T *m_ptr;

    //  constructor, default
    public:
        MyIterator(T *p = 0) : m_ptr(p) {}
        MyIterator(const MyIterator &lhs) : m_ptr(lhs.m_ptr) {}
        MyIterator operator =(const MyIterator &lhs) {m_ptr = lhs.m_ptr;}
        ~MyIterator() {}
   
    //  other operations
    public:
        MyIterator operator ++() {++m_ptr; return *this;}    //  ++prefix
        bool operator !=(const MyIterator &lhs) {return m_ptr != lhs.m_ptr;}  //  operator !=
        reference operator *()const {return *m_ptr;}    //  reference is T &
    
    //   MyIterator has some other operations as a RandomAccessIterator, but I just need what I offers
    };

    //////////////////////////////////////////////////////////////////////
    template<class Iterator>
    typename iterator_traits<Iterator>::value_type
    func(Iterator iter)
    {
        return *iter;
    }

    //////////////////////////////////////////////////////////////////////
    void testCase1()
    {
        cout << "testCase1" << endl;
    
        //  normal pointer
        int *p = new int(20);   
        cout << func(p) << endl;      //  20

        cout << typeid(p).name() << endl;  //  
        cout << typeid(iterator_category(p)).name() << endl;   //   random_access_iterator_tag
        cout << typeid(value_type(p)).name() << endl;          //   int *

        cout << endl;
    }

    void testCase2()
    {
        cout << "testCase2" << endl;

        //  normal pointer
        char *p = new char('a');   
        cout << func(p) << endl;      //  

        cout << typeid(p).name() << endl;  //  
        cout << typeid(iterator_category(p)).name() << endl;    //  random_access_iterator_tag  
        cout << typeid(value_type(p)).name() << endl;           //  char *

        cout << endl;
    }

    void testCase3()
    {
        cout << "testCase3" << endl;
        
        Widget *w = NULL;
        cout << typeid(w).name() << endl;                       //  
        cout << typeid(iterator_category(w)).name() << endl;    //  ramdom_access_iterator_tag
        cout << typeid(value_type(w)).name() << endl;           //  Widget *

        cout << endl;
    }

    void testCase4()
    {
        cout << "testCase4" << endl;

        //  Iterator
        MyIterator<int> iter(new int(20));      //  20
        cout << func(iter) << endl;
   
        cout << typeid(iter).name() << endl;                      //  class iterator_public::MyIterator<int>
        cout << typeid(iterator_category(iter)).name() << endl;   //  struct STLite::random_access_iterator_tag
        cout << typeid(value_type(iter)).name() << endl;          //  int
    
        cout << endl;
    }

    void testCase5()
    {
        cout << "testCase5" << endl;

        int arr[OBJECT_NUM] = {0, 1, 2, 3, 4};
        
        MyIterator<int> first(arr);
        MyIterator<int> last(arr + OBJECT_NUM);
        MyIterator<int> iter = first;

        for (; iter != last; ++iter)
        {
            cout << *iter;
        }

        cout << endl;
    }

    //////////////////////////////////////////////////////////////////////
    void test()
    {
        cout << "iterator_public test" << endl;

        testCase1();
        testCase2();
        testCase3();
        testCase4();
        testCase5();

        cout << endl;
    }
}
#endif