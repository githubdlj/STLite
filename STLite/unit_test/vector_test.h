/********************************************************************
	Time:	  2015/10/26
	Filename: vector_test
	Author:	  dinglj
	
	Purpose:  vector≤‚ ‘
*********************************************************************/
#ifndef _VECTOR_TEST_H_
#define _VECTOR_TEST_H_

#include "../stlite_vector.h" 
#include <iostream>

using std::cout;
using std::cin;
using std::end;
using namespace STLite;

namespace vector_unit
{
    //////////////////////////////////////////////////////////////////////
    //  test constructor
    void testCase1()
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
    void testCase2()
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
    void testCase3()
    {
        const int OBJECT_NUM = 2;
        int arr[OBJECT_NUM] = {0, 1};

        vector<int> v1(arr, arr + OBJECT_NUM);

        vector<int> v2;
        v2 = v1;    //  assignment 

        cout << *v2.start << endl;
        cout << *(v2.start + 1) << endl;

        v1 = v1;     //  assignment, ºÏ≤‚◊‘Œ“∏≥÷µ
        cout << *v1.start << endl;
        cout << *(v1.start + 1) << endl;

        cout << endl;
    }

    void testConstructor()
    {
        testCase1();
        testCase2();
        testCase3();
    }

    //////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////
    //  test elements access

    void testCase4()
    {
        vector<int> v(2, 3);

        cout << v.front() << endl;
        cout << v.back() << endl;
        
        v.at(1) = 10;
        cout << v[1] << endl;

        cout << endl;
    }
    
    //  
    void testElementAccess()
    {
        testCase4();
    }
    
    //////////////////////////////////////////////////////////////////////
    //  test modifiers
    //  test insert
    void testCase5()
    {
        const int NUM = 2;
        const int VALUE = 3;
        
        vector<int> v1;
        v1.insert(v1.begin(), NUM, VALUE);

        vectorIterator<int> begin = v1.begin();
        for (; begin != v1.end(); ++begin)
        {
            cout << *begin;
        }
        cout << endl;

        //////////////////////////////////////////////////////////////////////
        int arr[NUM] = {0, 1};
        vector<int> v2(NUM, VALUE);
        v2.insert(v2.begin() + 1, arr, arr + NUM);

        int size = v2.size();
        for (int i = 0; i < size; i++)
        {
            cout << v2[i];
        }
        
        cout << endl;
    }
    //////////////////////////////////////////////////////////////////////
    //  test erase
    void testCase6()
    {
        const int NUM = 5;
        int arr[NUM] = {0, 1, 2, 3, 4};
        
        vector<int> v1(arr, arr + NUM);
        v1.erase(v1.begin() + 1, v1.begin() + 3);

        int size =v1.size();
        for (int i = 0; i < size; i++)
        {
            cout << *(v1.start + i);    //  0 3 4
        }
        cout << endl;
        //////////////////////////////////////////////////////////////////////
        v1.erase(v1.end() - 1, v1.end());   //  erase the last element
        size = v1.size();
        for (int i = 0; i < size; i++)
        {
            cout << v1[i];
        }
        cout << endl;
    }
   
    void testModifers()
    {
        testCase5();
        testCase6();
    }
    //////////////////////////////////////////////////////////////////////
    void test()
    {
        cout << "vector test" << endl;

    //    testConstructor();
    //    testElementAccess();
        testModifers();
    }
}
#endif
