/********************************************************************
	Time:	  2015/10/22
	Filename: construct_test
	Author:	  dinglj
	
	Purpose:  测试全局的构造，析构函数
*********************************************************************/
#ifndef _CONSTRUCT_TEST_H_
#define _CONSTRUCT_TEST_H_

#include "../stlite_construct.h"
using namespace STLite;

namespace construct_unit
{
const int OBJECT_NUM = 5;

// 
void testCase1()
{
    cout << "testCase1 for int*" << endl;
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
    
    cout << endl;
}

void testCase2()
{
    cout << "testCase2 for int a[]" << endl;
    int arr[OBJECT_NUM];

    for (int i = 0; i < OBJECT_NUM; i++)
    {
        construct(arr + i, i);
    }

    for (int i = 0; i < OBJECT_NUM; i++)
    {
        cout << arr[i] << endl;
    }

    destroy(arr, arr + OBJECT_NUM);  //  do nothing
    cout << endl;
}
//  
void testCase3()
{
    cout << "testCase3" << endl;
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

    cout << endl;
}

void test()
{
    cout << "construct_test" << endl;
    
    testCase1();
    testCase2();
    testCase3();
}

}
#endif