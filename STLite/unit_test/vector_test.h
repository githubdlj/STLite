/********************************************************************
	Time:	  2015/10/26
	Filename: vector_test
	Author:	  dinglj
	
	Purpose:  
*********************************************************************/
#ifndef _PUBLIC_VECTOR_TEST_H_
#define _PUBLIC_VECTOR_TEST_H_

#include <list>
#include <vector>

#include "common_header_files.h"
#include "../stlite_vector.h" 

//////////////////////////////////////////////////////////////////////
namespace vector_public
{
    //  test constructor
    void testCase1()
    {
        cout << "testCase1" << endl;

        vector<int> v1(OBJECT_NUM, 1);    //  vector(n, value)

        for (int i = 0; i < OBJECT_NUM; ++i)
        {
            cout << *(v1.start + i) << "\t";    //  1 1 1 1 1 
        }
        cout << endl;

        //////////////////////////////////////////////////////////////////////
        int arr[OBJECT_NUM] = {0, 1, 2, 3, 4};   
        vector<int> v2(arr, arr + OBJECT_NUM);       //  vector(pointer first, pointer last)
        
        for (int i = 0; i < OBJECT_NUM; ++i)
        {
            cout << *(v2.start + i) << "\t";    //  0 1 2 3 4 
        }
        cout << endl;

        //////////////////////////////////////////////////////////////////////
        typedef vectorIterator<int> vIter;
        vIter iter(arr);

        vector<int> v3(iter, iter + OBJECT_NUM);  //   vector(iterator first, iterator last)
        
        for (int i = 0; i < OBJECT_NUM; ++i)
        {
            cout << *(v3.start + i) << "\t";    //  0 1 2 3 4 
        }
        cout << endl;


        Widget w[OBJECT_NUM] = {0, 1, 2, 3, 4};
        vector<Widget> v4(w, w + OBJECT_NUM);   //  vector(iterator first, iterator last)

        for (int i = 0; i < OBJECT_NUM; ++i)
        {
            cout << (v4.start + i)->m_value << "\t";
        }
        cout << endl;

        // String
    }

    //////////////////////////////////////////////////////////////////////
    //  copy
    void testCase2()
    {
        cout << "testCase2" << endl;

        int arr[OBJECT_NUM] = {0, 1, 2, 3, 4};

        vector<int> v1(arr, arr + OBJECT_NUM);
        vector<int> v2(v1);     //  copy construct

        for (int i = 0; i < OBJECT_NUM; ++i)
        {
            cout << *(v2.start + i) << "\t";
        }
        cout << endl;
    }

    //////////////////////////////////////////////////////////////////////
    //  test assignment
    void testCase3()
    {
        cout << "testCase3" << endl;

        int arr[OBJECT_NUM] = {0, 1, 2, 3, 4};
        vector<int> v1(arr, arr + OBJECT_NUM);

        vector<int> v2;
        v2 = v1;    //  assignment 

        for (int i = 0; i < OBJECT_NUM; ++i)
        {
            cout << *(v2.start + i) << "\t";
        }
        cout << endl;


        v1 = v1;     //  self assignment
        for (int i = 0; i < OBJECT_NUM; ++i)
        {
            cout << *(v1.start + i) << "\t";
        }
        cout << endl;
    }

    void testConstructor()
    {
        cout << "testConstructor" << endl;
     
        testCase1();
        testCase2();
        testCase3();
      
        cout << endl;
    }

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
        cout << "testElementAccess" << endl;

        testCase4();
    
        cout << endl;
    }
    
    //////////////////////////////////////////////////////////////////////
    //  test modifiers
    //  test insert
    void testCase5()
    {
        const int VALUE = 3;
        
        vector<int> v1;
        v1.insert(v1.begin(), OBJECT_NUM, VALUE);

        vectorIterator<int> begin = v1.begin();
        for (; begin != v1.end(); ++begin)
        {
            cout << *begin << "\t";     //  3 3 3 3 3
        }
        cout << endl;

        //////////////////////////////////////////////////////////////////////
        int arr[OBJECT_NUM] = {0, 1, 2, 3, 4};
        vector<int> v2(OBJECT_NUM, VALUE);
        v2.insert(v2.begin() + 1, arr, arr + OBJECT_NUM);

        int size = v2.size();
        for (int i = 0; i < size; ++i)
        {
            cout << v2[i] << "\t";      //  0 3 3 3 3 3 1 2 3 4 
        }
        cout << endl;
    }

    //  test insert
    void testCase6()
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
        for (int i = 0; i < size; ++i)
        {
            cout << v1[i];
        }
        cout << endl;
        
        vector<int> v2;
        v2.insert(v2.begin(), begin, end);

        size = v2.size();
        for (int i = 0; i < size; ++i)
        {
            cout << v2[i];
        }
        cout << endl;
        */
    }
    //////////////////////////////////////////////////////////////////////
    //  test erase
    void testCase7()
    {
        int arr[OBJECT_NUM] = {0, 1, 2, 3, 4};
        
        vector<int> v1(arr, arr + OBJECT_NUM);
        v1.erase(v1.begin() + 1, v1.begin() + 3);

        int size =v1.size();
        for (int i = 0; i < size; ++i)
        {
            cout << *(v1.start + i);    //  0 3 4
        }
        cout << endl;

        //////////////////////////////////////////////////////////////////////
        v1.erase(v1.end() - 1, v1.end());   //  erase the last element
        size = v1.size();
        for (int i = 0; i < size; ++i)
        {
            cout << v1[i];
        }
        cout << endl;
    }
    
    //////////////////////////////////////////////////////////////////////
    //  test push_back, pop_back
    void testCase8()
    {
        vector<int> v;

        for (int i = 0; i < OBJECT_NUM; ++i)
        {
            v.push_back(i);         
        }

        int size = v.size();       
        for (int i = 0; i < size; ++i)
        {
            cout << v[i];           //  0 1 2 3 4 
        }
        cout << endl;
        //////////////////////////////////////////////////////////////////////
        v.pop_back();
        v.pop_back();
        
        size = v.size();
        for (int i = 0; i < size; ++i)
        {
            cout << v[i];       //  0 1 2
        }
        cout << endl;
    }
    //////////////////////////////////////////////////////////////////////
    //  test reserve
    void testCase9()
    {
        const int NUM = 3;
        vector<int> v;
        
        for (int i = 0; i < NUM; ++i)
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
        for (int i = 0; i < size; ++i)
        {
            cout << v[i];               //  012
        }
        cout << endl;

        //////////////////////////////////////////////////////////////////////
        v.resize(5, 8);
        size  = v.size();
        for (int i = 0; i < size; ++i)
        {
            cout << v[i];               //  01288
        }
        cout << endl;
        
        //////////////////////////////////////////////////////////////////////
        v.resize(4);            
        size  = v.size();
        for (int i = 0; i < size; ++i)
        {
            cout << v[i];               //  0128
        }

        cout << endl;
    }

    //  test clear
    void testCase10()
    {
        const int NUM = 5;
        const int arr[NUM] = {0,1,2,3,4};

        vector<int> v(arr, arr + NUM);

        v.clear();
        cout << v.size() << endl;   //  0

        for (int i = 0; i < NUM + 1; ++i)
        {
            cout << v[i] << endl;   //  01234,random num
        }
        cout << endl;
    }

    void testModifiers()
    {
        cout << "testModifers" << endl;
        testCase5();
//         testCase6();
//         testCase7();
//         testCase8();
//         testCase9();
//         testCase10();
        cout << endl;
    }
    //////////////////////////////////////////////////////////////////////
    void test()
    {
        cout << "vector_public test" << endl;
      
        testConstructor();
   //     testElementAccess();
        testModifiers();
        
        cout << endl;
    }
}
#endif
