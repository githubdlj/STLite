/********************************************************************
	Time:	  2015/10/21
	Filename: type_traits_test
	Author:	  dinglj
	
	Purpose:  ≤‚ ‘type_traits
*********************************************************************/
#ifndef _STLITE_TYPE_TRAITS_TEST_H_
#define _STLITE_TYPE_TRAITS_TEST_H_


#include "../stlite_type_traits.h"

#include <iostream>
using std::cout;
using std::cin;
using std::endl;

using namespace STLite;

namespace type_traites_unit
{
  
// ÷ÿ‘ÿ∫Ø ˝
void print_aux(__true_type)
{
    cout << "true" << endl;
}

void print_aux(__false_type)
{
    cout << "false" << endl;
}

template<class T>
void print(T)
{
    typedef typename __type_traits<T>::is_POD_type is_POD_type;

    cout << typeid(T).name() << ": ";
    print_aux(is_POD_type());
}

void testCase1()
{
    cout << "testCase1()" << endl;

    int a = 0;
    print(a);

    bool b = true;
    print(b);

    cout << endl;
}

void testCase2()
{
    cout << "testCase2()" << endl;

    int *pi = NULL;
    print(pi);

    char *pc1 = NULL;
    print(pc1);

    unsigned char *pc2 = NULL;
    print(pc2);

    const char *pc3 = NULL;
    print(pc3);

    cout << endl;
}

void testCase3()
{
    cout << "testCase3()" << endl;

    class A{};
    A a;
    print(a);

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