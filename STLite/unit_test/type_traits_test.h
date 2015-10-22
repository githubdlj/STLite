/********************************************************************
	Time:	  2015/10/21
	Filename: type_traits_test
	Author:	  dinglj
	
	Purpose:  ≤‚ ‘type_traits
*********************************************************************/
#ifndef _STLITE_TYPE_TRAITS_TEST_H_
#define _STLITE_TYPE_TRAITS_TEST_H_

#include <iostream>
#include "../stlite_type_traits.h"

using std::cout;
using std::cin;
using std::endl;

using namespace STLite;

namespace type_traites_unit
{

//  ÷ÿ‘ÿ∫Ø ˝
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

    int *pi = NULL;
    print(pi);

    char *pc1 = NULL;
    print(pc1);

    unsigned char *pc2 = NULL;
    print(pc2);

    const char *pc3 = NULL;
    print(pc3);
   
}

}
#endif