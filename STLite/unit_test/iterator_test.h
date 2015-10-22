/********************************************************************
	Time:	  2015/10/21
	Filename: iterator_test
	Author:	  dinglj
	
	Purpose:  测试iterator_traits
*********************************************************************/

#ifndef _ITERATOR_TEST_H_
#define _ITERATOR_TEST_H_

#include <iostream>
#include "../stlite_iterator.h"

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

void test()
{
    cout << "iterator_test" << endl;

    //  普通指针
    int *p = new int(20);   
    cout << func(p) << endl;      //  20

    //  自定义迭代器
    MyIterator<int> iter(new int(30));      //  30
    cout << func(iter) << endl;
   
    cout << typeid(iter).name() << endl;  //  class iterator_unit::MyIterator<int>
    cout << typeid(iterator_category(iter)).name() << endl;   //  struct STLite::random_access_iterator_tag
    cout << typeid(value_type(iter)).name() << endl;  //  int
}
}
#endif