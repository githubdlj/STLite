/********************************************************************
	Time:	  2015/10/26
	Filename: vector_test
	Author:	  dinglj
	
	Purpose:  vcetor细节测试
*********************************************************************/
#ifndef _VECTOR_DETAIL_TEST_H_
#define _VECTOR_DETAIL_TEST_H_

#include "common.h"
#include "../stlite_vector.h"
#include "../stlite_iterator.h"
#include "../stlite_alloc.h"

#include <vector>

//////////////////////////////////////////////////////////////////////
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
    //  test insert(pos, n, value)
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
    
    //////////////////////////////////////////////////////////////////////
    //  test insert(pos, first, last)
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
    //  test insert(pos, first, last)
    void testCase9_()
    {
        Widget wArr[MY_OBJECT_NUM];
        for (int i = 0; i < MY_OBJECT_NUM; ++i)
        {
            wArr[i].m_value = i;
        }
        
        vector<Widget> v;
        v.start = allocator<Widget>::allocate(2 * MY_OBJECT_NUM);
        v.finish = v.start;
        v.end_of_storage = v.start + 2 * MY_OBJECT_NUM;

        v.insert(v.begin(), wArr, wArr + MY_OBJECT_NUM);

        for (int i = 0; i < 2 * MY_OBJECT_NUM; ++i)
        {
            cout << v[i].m_value << endl;
        }
        //  now, v[0, MY_OBJECT_NUM) has initialzed, but the v[MY_OBJECT_NUM, 2 * MY_OBJECT_NUM) has not initialized.
       
        //////////////////////////////////////////////////////////////////////
        
        //  I insert the value into the uninitialized range
        //  but no error, why?
        v.insert(v.begin(), wArr, wArr + MY_OBJECT_NUM);

        for (int i = 0; i < 2 * MY_OBJECT_NUM; ++i)
        {
            cout << v[i].m_value << endl;
        }
        cout << endl;
    }

    //  test insert again
    void testCase9__()
    {
        String sArr[MY_OBJECT_NUM] = {"hello world0", "hello world1", "hello world2", "hello world3", "hello world4"};

//         for (int i = 0; i < MY_OBJECT_NUM; ++i)
//         {
//             cout << sArr[i].m_data << endl;
//         }
        vector<String> v;
        v.start = allocator<String>::allocate(2 * MY_OBJECT_NUM);
        v.finish = v.start;
        v.end_of_storage = v.start + 2 * MY_OBJECT_NUM;

        v.insert(v.begin(), sArr, sArr + MY_OBJECT_NUM);

        for (int i = 0; i < MY_OBJECT_NUM; ++i)
        {
            cout << v[i].m_data << endl;
        }
        //  now, v[0, MY_OBJECT_NUM) has initialzed, but the v[MY_OBJECT_NUM, 2 * MY_OBJECT_NUM) has not initialized.

        //////////////////////////////////////////////////////////////////////
        //  now, continue insert, the v[0, MY_OBJECT_NUM) will move to the uninitialized range v[MY_OBJECT_NUM, 2 * MY_OBJECT_NUM)
        //  it will call operator =, in the operator =, String has operation delete []m_data.
        //  but because the range is uninitialized, so the m_data is a WILD pointer, delete it will cause exception
        //  notice, it is safe to delete a NULL pointer. 

        //  besides, in the insert function, it use uninitilized_copy() to insert the new elements to the initialized range,
        //  int uninitialized_copy(), it will call constructor(copy) to allocate new memory for m_data without delete the old memory
        //  thus lead to MEMORY LEAK!

        
        v.insert(v.begin(), sArr, sArr + MY_OBJECT_NUM);    //  error
            
    }
    //  test insert range
    void testCase10()
    {
        typedef std::vector<int> iVec;
        iVec v(2, 1);

        v.insert(v.end() + 1, 2, 2);    //  error, valid range is [v.begin(), v.end()]
        cout << endl;
    }

    //////////////////////////////////////////////////////////////////////
    //  test clear
    void testCase11()
    {
        typedef std::vector<int> iVec;
        iVec v(2, 1);

        v.clear();

        cout << v.size() << endl;
        //  按道理是输出1,1，但是vs下STL做了下标异常保护，所以执行会出错
        for (int i = 0; i < 2; i++)
        {
            cout << v[i];   //  1, 1,  random number
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
//         testCase8();
//          testCase9();
//        testCase10();
//        testCase11();
            
//            testCase9_();
            testCase9__();
        cout << endl;
    }
  
}

#endif

