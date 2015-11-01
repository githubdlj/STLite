/********************************************************************
	Time:	  2015/10/21
	Filename: iterator_test
	Author:	  dinglj
	
	Purpose:  测试iterator_traits
*********************************************************************/

#ifndef _ITERATOR_TEST_H_
#define _ITERATOR_TEST_H_

#include "../stlite_iterator.h"
#include <iostream>
using std::cout;
using std::cin;
using std::endl;

using namespace STLite;

namespace iterator_unit
{

//  自定义的迭代器，继承自STLite::iterator
template<class T>
class MyIterator : public iterator<random_access_iterator_tag, T>
{
private:
    T *m_ptr;

public:
    MyIterator(T *p = 0) : m_ptr(p){}
    T& operator*()const {return *m_ptr;}

    ~MyIterator() {delete(m_ptr);}

};

template<class Iterator>
typename iterator_traits<Iterator>::value_type
func(Iterator iter)
{
    return *iter;
}

void testCase1()
{
    cout << "testCase1 for int *" << endl;
    
    //  normal pointer
    int *p = new int(20);   
    cout << func(p) << endl;      //  20

    cout << typeid(p).name() << endl;  //  
    cout << typeid(iterator_category(p)).name() << endl;   //  
    cout << typeid(value_type(p)).name() << endl;  //  

    cout << endl;
}

void testCase2()
{
    cout << "testCase2 for char *" << endl;

    //  normal pointer
    char *p = new char('a');   
    cout << func(p) << endl;      //  

    cout << typeid(p).name() << endl;  //  
    cout << typeid(iterator_category(p)).name() << endl;   //  
    cout << typeid(value_type(p)).name() << endl;  //  

    cout << endl;
}

void testCase3()
{
    cout << "testCase3 for MyIterator" << endl;

    //  Iterator
    MyIterator<int> iter(new int(20));      //  20
    cout << func(iter) << endl;
   
    cout << typeid(iter).name() << endl;  //  class iterator_unit::MyIterator<int>
    cout << typeid(iterator_category(iter)).name() << endl;   //  struct STLite::random_access_iterator_tag
    cout << typeid(value_type(iter)).name() << endl;  //  int
    
    cout << endl;
}

void test()
{
    testCase1();
    testCase2();
    testCase3();
}
}
#endif