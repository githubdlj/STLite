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
#include <list>
#include <vector>

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

        vector<int> v3(iter, iter + OBJECT_NUM);  //   vector(iterator first, iterator last)
        cout << *v3.start << endl;
        cout << *(v3.start + 1) << endl;          //  1 2

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
    //  test insert
    void testCase5_()
    {
        typedef std::list<int> list;
        list l(2, 2);

        list::iterator begin = l.begin();
        list::iterator end = l.end();
        
        //  1.
        //  compiler error, because in function insert_aux, I have locationNeed = last - first,
        //  but begin & end are bidirectional_iterator, they do not offer operator -(iterator &lhs),
        //  I can check the error by distance(first, last)
       
        //  2.
        //  there is still compiler error
        //  can not transfer "std::bidirectional_iterator_tag" to "STLite::input_iterator_tag"

        /*
        vector<int> v1(10, 1);
        v1.finish = v1.finish - 5;
        v1.insert(v1.begin(), begin, end);   

        int size = v1.size();
        for (int i = 0; i < size; i++)
        {
            cout << v1[i];
        }
        cout << endl;
        
        vector<int> v2;
        v2.insert(v2.begin(), begin, end);

        size = v2.size();
        for (int i = 0; i < size; i++)
        {
            cout << v2[i];
        }
        cout << endl;
        */
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
    
    //////////////////////////////////////////////////////////////////////
    //  test push_back, pop_back
    void testCase7()
    {
        const int NUM = 3;
        vector<int> v;

        for (int i = 0; i < NUM; i++)
        {
            v.push_back(i);         
        }

        int size = v.size();       
        for (int i = 0; i < size; i++)
        {
            cout << v[i];           //  012
        }
        cout << endl;
        //////////////////////////////////////////////////////////////////////
        v.pop_back();
        v.pop_back();
        size = v.size();
        for (int i = 0; i < size; i++)
        {
            cout << v[i];       //  0
        }
        cout << endl;
    }
    //////////////////////////////////////////////////////////////////////
    //  test reserve
    void testCase8()
    {
        const int NUM = 3;
        vector<int> v;
        
        for (int i = 0; i < NUM; i++)
        {
            v.push_back(i);
        }

        cout << v.size() << endl;       //  3
        cout << v.capacity() << endl;   //  4

        v.reserve(5);

        cout << v.size() << endl;       //  3
        cout << v.capacity() << endl;   //  5
// 
        cout << v[5] << endl;       //  cout random number
        int size = v.size();
        for (int i = 0; i < size; i++)
        {
            cout << v[i];               //  012
        }
        cout << endl;

        //////////////////////////////////////////////////////////////////////
        v.resize(5, 8);
        size  = v.size();
        for (int i = 0; i < size; i++)
        {
            cout << v[i];               //  01288
        }
        cout << endl;
        
        //////////////////////////////////////////////////////////////////////
        v.resize(4);            
        size  = v.size();
        for (int i = 0; i < size; i++)
        {
            cout << v[i];               //  0128
        }

        cout << endl;
    }

    //  test clear
    void testCase9()
    {
        const int NUM = 5;
        const int arr[NUM] = {0,1,2,3,4};

        vector<int> v(arr, arr + NUM);

        v.clear();
        cout << v.size() << endl;   //  0

        for (int i = 0; i < NUM + 1; i++)
        {
            cout << v[i] << endl;   //  01234,random num
        }
        cout << endl;
    }
    void testModifers()
    {
        testCase5();
        //testCase6();
        //testCase7();
        //testCase8();
        //testCase9();
        testCase5_();
    }
    //////////////////////////////////////////////////////////////////////
    void test()
    {
        cout << "vector test" << endl;

     //   testConstructor();
    //    testElementAccess();
        testModifers();
    }
}
#endif
