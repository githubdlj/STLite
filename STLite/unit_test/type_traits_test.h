/********************************************************************
	Time:	  2015/10/21
	Filename: type_traits_test
	Author:	  dinglj
	
	Purpose:  测试type_traits
*********************************************************************/
#ifndef _TYPE_TRAITS_TEST_H_
#define _TYPE_TRAITS_TEST_H_

#include <iostream>
#include "../type_traits.h"

using namespace std;
using namespace STLite;

//  采用命名空间原因是可以在不同的测试文件中拥有相同的函数名，如test，如果调用该文件中的test，
//  则采用type_traits_test::test()
namespace type_traites_test
{

//  重载函数
void print_aux(__true_type)
{
    std::cout << "true" << endl;
}

void print_aux(__false_type)
{
    std::cout << "false" << endl;
}

template<class T>
void print(T)
{
    typedef typename __type_traits<T>::is_POD_type is_POD_type;
    print_aux(is_POD_type());
}

void test()
{
    int a = 0;
    print(a);

    bool b = true;
    print(b);

    class A{};
    A c;
    print(c);

    class B{};
    B d;
    print(d);
}

}
#endif