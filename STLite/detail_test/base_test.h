/********************************************************************
	Time:	  2015/11/04
	Filename: base_test
	Author:	  dinglj
	
	Purpose:  test the fundamental knowledge
*********************************************************************/
#ifndef _PRIVATE_BASE_TEST_H_
#define _PRIVATE_BASE_TEST_H_

#include "common_data.h"
#include "common_header_files.h"

//////////////////////////////////////////////////////////////////////
namespace base_private
{
    //  ++prefix, postfix++
    //  ++prefix returns a value_type &, postfix++ returns a value_type(a temp object)
    void testCase1()
    {
        cout << "testCase1" << endl;

        int num1 = 1;
        //  num1++ = 10;     //  postfix++ can not be a left value
        cout << num1 << endl;

        int num2 = 1;      
        ++num2 = 10;    
        cout << num2 << endl;   //  10

        int num = 3;
        int prefix = ++num;
        cout << prefix << endl;     //  4

        num = 3;
        int post = num++;       //  3
        cout << post << endl;

        cout << endl;
    }

    //  test operator *()
    void testCase2()
    {
        cout << "testCase2" << endl;

        int *p = new int(10);
        cout << *p << endl;

        int num = 5;
        num = *p;
        cout << num << endl;

        num = 6;
        *p = num;
        cout << *p << endl;

        cout << endl;
    }

    void testOperator()
    {
        cout << "testOperator" << endl;

        testCase1();
        testCase2();

        cout << endl;
    }
    //////////////////////////////////////////////////////////////////////
  
    void fun1(Widget)   //  call copy 
    {

    }

    void fun2(const Widget &)   //  do not call copy
    {

    }

    Widget fun3()   //  call copy when return 
    {
        Widget w;
        return w;
    }

//     Widget & fun4()     // do not call copy
//     {
//         return *this;
//     }

    void testConstructor()
    {
        cout << "testConstructor" << endl;

        Widget w;
        fun1(w);
        fun2(w);
        fun3();
        //   fun4();

        cout << endl;
    }

    //////////////////////////////////////////////////////////////////////
    void swap0(int *p, int *q)
    {
        int temp = *p;
        *p = *q;
        *q = temp;
    }

    void swap1(int &p, int &q)
    {
        int temp = p;
        p = q;
        q = temp;
    }

    void swap2(int * &p, int * &q)
    {
        int *temp = p;
        p = q;
        q = temp;
    }

    void swap3(int * &p, int * &q)
    {
        int temp = *p;
        *p = *q;
        *q = temp;
    }

    void swap4(int **p, int **q)
    {
        int *temp = *p;
        *p = *q;
        *q = temp;
    }

    void swap5(int **p, int **q)
    {
        int temp = **p;
        **p = **q;
        **q = temp;
    }

    void testCase3()
    {
        cout << "testCase3" << endl;
        int a = 3;
        int b = 4;

        //  all the swap can work right
        swap0(&a, &b);
        swap1(a, b);

        cout << a << endl;     
        cout << b << endl;
    }

    void testCase4()
    {
        cout << "testCase4" << endl;

        int a = 3;
        int b = 4;
        int *p = &a;
        int *q = &b;

        //  all the swap can work right
        swap2(p, q);
        swap3(p, q);

        swap4(&p, &q);
        swap5(&p, &q);

        cout << endl;
    }

    void testSwap()
    {
        cout << "testSwap" << endl;

        testCase3();
        testCase4();

        cout << endl;
    }
    //////////////////////////////////////////////////////////////////////
    void test()
    {
        cout << "base_private test" << endl;
        
        testOperator();
        testConstructor();

        cout << endl;
    }
}

#endif