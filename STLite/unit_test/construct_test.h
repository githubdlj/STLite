/********************************************************************
	Time:	  2015/10/22
	Filename: construct_test
	Author:	  dinglj
	
	Purpose:  测试全局的构造，析构函数
*********************************************************************/
#ifndef _CONSTRUCT_TEST_H_
#define _CONSTRUCT_TEST_H_

#include <iostream>
#include "../stlite_construct.h"

using std::cout;
using std::cin;
using std::endl;
using namespace STLite;

namespace construct_unit
{
const int OBJECT_NUM = 5;

// 
void test_POD_object()
{
    //  allocate memory
    int *p = (int *) ::operator new(sizeof(int) * OBJECT_NUM);
  
    //  construct
    for (int i = 0; i < OBJECT_NUM; i++)
    {
        construct(p + i, i);    
    }
    
    //  print
    for (int i = 0; i < OBJECT_NUM; i++)
    {
        cout << p[i] << endl;   //  1, 2, 3, 4 ,5
    }

    //  destroy
    destroy(p, p + OBJECT_NUM);     //  call destroy_aux(first, last, __true_type) ==> do nothing

    //  free memory
    ::operator delete(p);   //  operator delete有两种形式，operator delete(pointer *p), operator delete(pointer *p, size)
}

//  
void test_NotPOD_object()
{
    //  struct A is not POD type, it's has constructor & deconstructor
    struct A
    {
        A(int a = 0) 
        {
            m_a = a;
            cout << "construct" << endl;
        }
        ~A() 
        {
            cout << "deconstruct" << endl;
        }
        int m_a;
    };

    //  alloc memory
    A *p = (A *) ::operator new(sizeof(A) * OBJECT_NUM);

    //  construct
    for (int i = 0; i < OBJECT_NUM; i++)
    {
        construct(p + i, i);    //  call p[i] constructor
    }

    //  print
    for (int i = 0; i < OBJECT_NUM; i++)
    {
        cout << p[i].m_a << endl;
    }

    //  destroy
    destroy(p, p + OBJECT_NUM);     //  call destroy_aux(first, last, __false_type) ==> call p[i] deconstructor

    //  free memory
    ::operator delete(p);
}

void test()
{
    cout << "construct_test" << endl;
    
    test_POD_object();

    cout << endl << endl;

    test_NotPOD_object();    
}

}
#endif