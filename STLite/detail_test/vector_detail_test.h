/********************************************************************
	Time:	  2015/10/26
	Filename: vector_test
	Author:	  dinglj
	
	Purpose:  vcetor细节测试
*********************************************************************/
#ifndef _VECTOR_DETAIL_TEST_H_
#define _VECTOR_DETAIL_TEST_H_
#include "../stlite_vector.h"
#include "../stlite_iterator.h"

#include <iostream>
using std::cout;
using std::cin;
using std::endl;

namespace vector_detail
{
    //  测试前缀++，后缀++
    void testCase1()
    {
        int num1 = 1;
        //  num1++ = 10;     //  后缀只能作为右值
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
    //////////////////////////////////////////////////////////////////////
    //  测试*, ->
    void testCase2()
    {
        int *p = new int(10);
        cout << *p << endl;

        int num = 5;
        num = *p;
        cout << num << endl;

        num = 6;
        *p = num;
        cout << *p << endl;
    }
    //////////////////////////////////////////////////////////////////////
    //  测试vectorIterator 构造相关函数
    void testCase3()
    {
        const int OBJECT_NUM = 5;
        int arr[OBJECT_NUM] = {0, 1, 2, 3, 4};

        typedef vectorIterator<int> vIter;
        //  construct, ok
        vIter iter(arr);

        //  operator * (), ok
        cout << *iter << endl;      //  0
        
        //  copy construct
        vIter iter2(iter);
        cout << *iter2 << endl;      //  0

        //  assignment
        vIter iter3;
        iter3 = iter;
        cout << *iter3 << endl;     //  0
      
    }
    void testCase4()
    {
        const int OBJECT_NUM = 5;
        int arr[OBJECT_NUM] = {0, 1, 2, 3, 4};

        typedef vectorIterator<int> vIter;
        vIter iter(arr);

        //  operator ++ (), ok
        iter++;
        cout << *iter << endl;      //  1
        *iter = 10;
        cout << arr[1] << endl;     //  10

    }

    //////////////////////////////////////////////////////////////////////
    //  测试随机存取
    void testCase5()
    {
        const int OBJECT_NUM = 5;
        int arr[OBJECT_NUM] = {0, 1, 2, 3, 4};
        typedef vectorIterator<int> vIter;
        vIter iter(arr);

        cout << *(iter + 3) << endl;
        cout << iter[3] << endl;    //  operator []

    }
    //////////////////////////////////////////////////////////////////////
    void testCase6()
    {
        int *p = new int(10);

        typedef vectorIterator<int> vIter;
        vIter iter1(p);
        vIter iter2(p);

        if (iter1 == iter2)
        {
            cout << "equal" << endl;
        }

        //  note!!, free memory by itself, vectorIterator do not free memory
        free(p);
        cout << endl;
    }
    
    //  测试迭代器属性
    void testCase7()
    {
        typedef vectorIterator<int> vIter;
        vIter iter;     //  空迭代器

        cout << typeid(iter).name() << endl;  //  vectorIerator<int>
        cout << typeid(iterator_category(iter)).name() << endl;   //  struct STLite::random_access_iterator_tag
        cout << typeid(value_type(iter)).name() << endl;  //  int *
        cout << typeid(distance_type(iter)).name() << endl;
    }
    
    //////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////
    void testIterator()
    {
        testCase1();
        testCase2();
        testCase3();
        testCase4();
        testCase5();
        testCase6();
        testCase7();

        cout << endl;
    }
    //////////////////////////////////////////////////////////////////////
    //  test constructor
    void testCase8()
    {
        const int OBJECT_NUM = 2;
        vector<int> v1(2, 1);    //  vector(n, value)

        cout << *v1.start << endl;           //  1
        cout << *(v1.start + 1) << endl;     //  1

        //////////////////////////////////////////////////////////////////////
        int arr[OBJECT_NUM] = {1, 2};   
        vector<int> v2(arr, arr + OBJECT_NUM);       //  vector(pointer first, pointer last)
        cout << *v2.start << endl;                  //  1
        cout << *(v2.start + 1) << endl;            //  2

        //////////////////////////////////////////////////////////////////////
        typedef vectorIterator<int> vIter;
        vIter iter(arr);

        vector<int> v3(iter, iter + OBJECT_NUM);  //  /  vector(iterator first, iterator last)
        cout << *v3.start << endl;
        cout << *(v3.start + 1) << endl;

        //////////////////////////////////////////////////////////////////////
        //  
        struct structType
        {
            structType(int value = 0)
            {
                m_value = value;
                cout << "construct" << endl;
            }
            ~structType()
            {
                cout << "deconstruct" << endl;
            }
            int m_value;
        };

        structType structArr[OBJECT_NUM] = {0, 1};
        vector<structType> v4(structArr, structArr + OBJECT_NUM);
        
        cout << v4.start->m_value << endl;
        cout << (v4.start + 1)->m_value << endl;

        cout << endl;
    }

    //  copy
    void testCase9()
    {
        const int OBJECT_NUM = 2;
        int arr[OBJECT_NUM] = {0, 1};

        vector<int> v1(arr, arr + OBJECT_NUM);
        vector<int> v2(v1);     //  copy construct

        cout << *(v2.start) << endl;
        cout << *(v2.start + 1) << endl;

        cout << endl;
    }

    //  test assingment
    void testCase10()
    {
        const int OBJECT_NUM = 2;
        int arr[OBJECT_NUM] = {0, 1};

        vector<int> v1(arr, arr + OBJECT_NUM);

        vector<int> v2;
        v2 = v1;    //  assignment 

        cout << *v2.start << endl;
        cout << *(v2.start + 1) << endl;

        v1 = v1;     //  assignment, 检测自我赋值
        cout << *v1.start << endl;
        cout << *(v1.start + 1) << endl;

        cout << endl;
    }
    void testContainer()
    {
   //     testCase8();
        testCase9();
    //    testCase10();
    }

    void test()
    {
        cout << "vector_detail test" << endl;
    //    testIterator();
        testContainer();
    }
}

#endif

