/********************************************************************
	Time:	  2015/10/21
	Filename: type_traits_test
	Author:	  dinglj
	
	Purpose:  测试type_traits
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
  
// 重载函数
void print_aux(__true_type)
{
    cout << "true" << endl;
}

void print_aux(__false_type)
{
    cout << "false" << endl;
}

template<class T>
void print_attr(T)
{
    typedef typename __type_traits<T>::is_POD_type is_POD_type;

    cout << typeid(T).name() << ": ";
    print_aux(is_POD_type());
}

template<class T>
void print_type(T)
{
    typedef typename _is_integer<T>::is_integer is_integer;

    cout << typeid(T).name() << ": ";
    print_aux(is_integer());
}

//////////////////////////////////////////////////////////////////////
//  测试属性
void testCase1()
{
    cout << "testCase1()" << endl;

    int a = 0;
    print_attr(a);

    bool b = true;
    print_attr(b);

    cout << endl;
}

void testCase2()
{
    cout << "testCase2()" << endl;

    int *pi = NULL;
    print_attr(pi);

    char *pc1 = NULL;
    print_attr(pc1);

    unsigned char *pc2 = NULL;
    print_attr(pc2);

    const char *pc3 = NULL;
    print_attr(pc3);

    cout << endl;
}

void testCase3()
{
    cout << "testCase3()" << endl;

    class A{};
    A a;
    print_attr(a);

    cout << endl;
}
//////////////////////////////////////////////////////////////////////
//  测试数据类型
void testCase4()
{
    int intType = 0;
    print_type(intType);


    cout << endl;
}

void testCase5()
{
    int *ptr = NULL;
    print_type(ptr);

    cout << endl;
}

void testCase6()
{
    class A{};
    A a;

    print_type(a);
    cout << endl;
}

//////////////////////////////////////////////////////////////////////

void test()
{
//     testCase1();
//     testCase2();
//     testCase3();
    //////////////////////////////////////////////////////////////////////
    testCase4();
    testCase5();
    testCase6();
}

}
#endif