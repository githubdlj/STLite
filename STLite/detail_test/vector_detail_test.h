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
    //  test operator ++
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
    //  test operator []
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
    //  test operator ==
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
    //  test insert
    void testCase8()
    {
        const int NUM = 10;
        const int VALUE = 1;

        const int ADD_NUM = 3;
        const int NEW_VALUE = 2;

        //////////////////////////////////////////////////////////////////////
        //  case1, the space is enough
        int arr[NUM] = {0,1,2,3,4,5,6,7,8,9};
        vector<int> v1(arr, arr + NUM);
        v1.finish = v1.finish - 5;  //  为了使剩余空间大于所需空间

        vectorIterator<int> pos = v1.begin() + 2;
        v1.insert(pos, ADD_NUM, NEW_VALUE);

        for (pos = v1.begin(); pos != v1.end(); ++pos)
        {
            cout << *pos;           //  01222234
        }
        cout << endl;

        //  case2, the space is not enough
        vector<int> v2(arr, arr + NUM);
        pos = v2.begin() + 2;

        v2.insert(pos, ADD_NUM, NEW_VALUE);

        for(pos = v2.begin(); pos != v2.end(); ++pos)
        {
            cout << *pos;           //  0122223456789
        }

        cout << endl;
    }
    
    void testCase9()
    {
        const int NUM = 10;
        const int VALUE = 1;

        const int ADD_NUM = 3;

        int arr[ADD_NUM] = {2, 3, 4};

        //  case1, the space is enough
        vector<int> v1(NUM, VALUE);
        v1.finish = v1.finish - 5;

        v1.insert(v1.begin() + 2, arr, arr + ADD_NUM);

        int size = v1.size();
        for (int i = 0; i < size; i++)
        {
            cout << v1[i];
        }
        cout << endl;

        //  case2, the space is not enough
        vector<int> v2(NUM, VALUE);
        v2.finish = v2.finish - 2;

        v2.insert(v2.begin() + 2, arr, arr + ADD_NUM);

        cout << v2.capacity() << endl;
        size = v2.size();
        for (int i = 0; i < size; i++)
        {
            cout << v2[i];
        }

        cout << endl;
    }

   
    //////////////////////////////////////////////////////////////////////
    void test()
    {
        cout << "vector_detail test" << endl;

//         testCase1();
//         testCase2();
//         testCase3();
//         testCase4();
//         testCase5();
//         testCase6();
//         testCase7();
         testCase8();

//        testCase9();
        cout << endl;
    }
  
}

#endif

