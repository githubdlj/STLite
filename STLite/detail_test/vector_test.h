/********************************************************************
	Time:	  2015/10/26
	Filename: vector_test
	Author:	  dinglj
	
	Purpose:  test STLite::vector 
*********************************************************************/
#ifndef _PRIVATE_VECTOR_TEST_H_
#define _PRIVATE_VECTOR_TEST_H_

#include <vector>

#include "common_header_files.h"
#include "common_data.h"
#include "../stlite_vector.h"
#include "../stlite_iterator.h"
#include "../stlite_alloc.h"
#include "../stlite_uninitialized.h"

//////////////////////////////////////////////////////////////////////
namespace vector_private
{
    //  test vectorIterator' s constructor
    void testCase1()
    {
        cout << "testCase1" << endl;

        int arr[OBJECT_NUM] = {0, 1, 2, 3, 4};

        typedef vectorIterator<int> vIter;
        //  construct, ok
        vIter iter1(arr);

        //  operator * (), ok
        cout << *iter1 << endl;      //  0
        
        //  copy construct
        vIter iter2(iter1);
        cout << *iter2 << endl;      //  0

        //  assignment
        vIter iter3;
        iter3 = iter1;
        cout << *iter3 << endl;     //  0

        cout << endl;
    }

    //  test operator ++
    void testCase2()
    {
        cout << "testCase2" << endl;

        int arr[OBJECT_NUM] = {0, 1, 2, 3, 4};

        typedef vectorIterator<int> vIter;
        vIter iter(arr);

        //  operator ++ (), ok
        iter++;
        cout << *iter << endl;      //  1
        *iter = 10;
        cout << arr[1] << endl;     //  10

    }

    //  test operator []
    void testCase3()
    {
        cout << "testCase3" << endl;

        int arr[OBJECT_NUM] = {0, 1, 2, 3, 4};
        typedef vectorIterator<int> vIter;
        vIter iter(arr);

        cout << *(iter + 3) << endl;
        cout << iter[3] << endl;    //  operator []

        cout << endl;
    }

    //  test operator ==
    void testCase4()
    {
        cout << "testCase4" << endl;

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
    
    //  test vectorIterator's attribute
    void testCase5()
    {
        cout << "testCase5" << endl;

        typedef vectorIterator<int> vIter;
        vIter iter;     //  

        cout << typeid(iter).name() << endl;  //  vectorIerator<int>
        cout << typeid(iterator_category(iter)).name() << endl;   //  struct STLite::random_access_iterator_tag
        cout << typeid(value_type(iter)).name() << endl;  //  int *
        cout << typeid(distance_type(iter)).name() << endl;

        cout << endl;
    }

    void testIterator()
    {
        cout << "testIterator" << endl;

        testCase1();
        testCase2();
        testCase3();
        testCase4();
        testCase5();
        
        cout << endl;
    }

    //////////////////////////////////////////////////////////////////////
    //  test insert(pos, n, value)
    void testCase6()
    {
        cout << "testCase6" << endl;

        const int VALUE = 1;

        const int ADD_NUM = 3;
        const int NEW_VALUE = 2;

        //////////////////////////////////////////////////////////////////////
        //  case1, the space is enough
        //  case error,
        //  in fact, the [finish, end_of_storgae) is a uninitialized range,
        //  but now, it is initialized.
//         int arr[NUM] = {0,1,2,3,4,5,6,7,8,9};
//         vector<int> v1(arr, arr + NUM);
//         v1.finish = v1.finish - 5;      //  in order to let the locationLeft > LocationNeed
                                          
        //  the right
        int arr[OBJECT_NUM] = {0, 1, 2, 3, 4};
        vector<int> v1;
        v1.start = allocator<int>::allocate(2 * OBJECT_NUM);
        v1.finish = uninitialized_copy(arr, arr + OBJECT_NUM, v1.start);
        v1.end_of_storage = v1.start + 2 * OBJECT_NUM;     // now, v1 = [0,1,2,3,4,x,x,x,x,x]

        vectorIterator<int> pos = v1.begin() + 2;
        v1.insert(pos, ADD_NUM, NEW_VALUE);

        for (pos = v1.begin(); pos != v1.end(); ++pos)
        {
            cout << *pos << "\t";           //  0 1 2 2 2 2 3 4 
        }
        cout << endl;

        //  case2, the space is not enough
        vector<int> v2(arr, arr + OBJECT_NUM);
        pos = v2.begin() + 2;

        v2.insert(pos, ADD_NUM, NEW_VALUE);     // now, v2 = [0 1 2 2 2 2 3 4 x x]

        for(pos = v2.begin(); pos != v2.end(); ++pos)
        {
            cout << *pos << "\t";           //  0 1 2 2 2 2 3 4 
        }

        cout << endl;
    }
    
    //////////////////////////////////////////////////////////////////////
    //  test insert(pos, first, last)
    void testCase7()
    {
        cout << "testCase7" << endl;
       
        const int VALUE = 1;
       
        const int ADD_NUM = 3;
        int arr[ADD_NUM] = {2, 3, 4};

        //  case1, the space is enough

        //  the same error as testCase6
//         vector<int> v1(NUM, VALUE);
//         v1.finish = v1.finish - 5;
        vector<int> v1;
        v1.start = allocator<int>::allocate(OBJECT_NUM);
        v1.finish = uninitialized_fill_n(v1.start, OBJECT_NUM, VALUE);
        v1.end_of_storage = v1.start + 2 * OBJECT_NUM;      //  now, v1 = [1 1 1 1 1 x x x x x]

        v1.insert(v1.begin() + 2, arr, arr + ADD_NUM);      //  now, v1 = [1 1 2 3 4 1 1 1 x x]

        int size = v1.size();
        for (int i = 0; i < size; ++i)
        {
            cout << v1[i] << "\t";      //  1 1 2 3 4 1 1 1 
        }
        cout << endl;

        //  case2, the space is not enough
        vector<int> v2(OBJECT_NUM, VALUE);

        v2.insert(v2.begin() + 2, arr, arr + ADD_NUM);      // mow, v1 = [1 1 2 3 4 1 1 1 x x]

        cout << v2.capacity() << endl;
        size = v2.size();
        for (int i = 0; i < size; ++i)
        {
            cout << v2[i] << "\t";
        }
        cout << endl;
    }

    //////////////////////////////////////////////////////////////////////
    //  test insert(pos, first, last)
    void testCase8()
    {
        cout << "testCase8" << endl;

        Widget wArr[OBJECT_NUM];
        for (int i = 0; i < OBJECT_NUM; ++i)
        {
            wArr[i].m_value = i;
        }
        
        vector<Widget> v;
        v.start = allocator<Widget>::allocate(2 * OBJECT_NUM);
        v.finish = v.start;
        v.end_of_storage = v.start + 2 * OBJECT_NUM;        //  now , v = [x x x x x x x x x x]

        v.insert(v.begin(), wArr, wArr + OBJECT_NUM);       //  v = [0 1 2 3 4 x x x x x]

        for (int i = 0; i < OBJECT_NUM; ++i)
        {
            cout << v[i].m_value << "\t";
        }
        cout << endl;
        //  now, v[0, OBJECT_NUM) has initialzed, but the v[OBJECT_NUM, 2 * OBJECT_NUM) has not initialized.
       
        //////////////////////////////////////////////////////////////////////
        
        //  I insert the value into the uninitialized range
        //  but no error, why?
        //  see the next testCase.  //  these comments for the old version INSERT, now, it out of date.
        v.insert(v.begin(), wArr, wArr + OBJECT_NUM);       //  v = [0 1 2 3 4 0 1 2 3 4]

        for (int i = 0; i < 2 * OBJECT_NUM; ++i)
        {
            cout << v[i].m_value << "\t";
        }
        cout << endl;
    }

    //  test insert again
    //  insert String
    //  the testCase9 is out of data
    /*
    void testCase9()
    {
        cout << "testCase9" << endl;

        String sArr[OBJECT_NUM] = {"hello world0", "hello world1", "hello world2", "hello world3", "hello world4"};

//         for (int i = 0; i < OBJECT_NUM; ++i)
//         {
//             cout << sArr[i].m_data << endl;
//         }
        vector<String> v;
        v.start = allocator<String>::allocate(2 * OBJECT_NUM);
        v.finish = v.start;
        v.end_of_storage = v.start + 2 * OBJECT_NUM;

        v.insert(v.begin(), sArr, sArr + OBJECT_NUM);

        for (int i = 0; i < OBJECT_NUM; ++i)
        {
            cout << v[i].m_data << endl;
        }
        //  now, v[0, OBJECT_NUM) has initialzed, but the v[OBJECT_NUM, 2 * OBJECT_NUM) has not initialized.

        //////////////////////////////////////////////////////////////////////
        //  now, continue insert, the v[0, OBJECT_NUM) will move to the uninitialized range v[OBJECT_NUM, 2 * OBJECT_NUM)
        //  it will call operator =, in the operator =, String has operation delete []m_data.
        //  but because the range is uninitialized, so the m_data is a WILD pointer, delete it will cause exception
        //  notice, it is safe to delete a NULL pointer. 

        //  besides, in the insert function, it use uninitilized_copy() to insert the new elements to the initialized range,
        //  int uninitialized_copy(), it will call constructor(copy) to allocate new memory for m_data without delete the old memory
        //  thus lead to MEMORY LEAK!

        
        v.insert(v.begin(), sArr, sArr + OBJECT_NUM);    //  error

        cout << endl;    
    }
    */

    //  test String
    void testCase9()
    {
        String arr[OBJECT_NUM] = {"String0", "String1", "String2", "String3", "String4"};
        
        vector<String> v1;
        v1.reserve(OBJECT_NUM);  //  v = [x x x x x]
        v1.finish = uninitialized_fill_n(v1.start, 2, "String");     //  v = [String, String, x, x, x]
       
        //  case1, the space is enough
        v1.insert(v1.begin() + 1, arr, arr + 2);           //  v = [String, String0, String1, String, x]
    
        int size = v1.size();
        for (int i = 0; i < size; ++i)
        {
            cout << v1[i].m_data << "\t";
        }
        cout << endl;
// 
        //  case2, the space is not enough
        v1.insert(v1.begin() + 2, arr + 2, arr + OBJECT_NUM);   
        //  v = [String, String0, String2, String3, String4, String1, String, x]

        cout << v1.capacity() << endl;
        size = v1.size();
        for (int i = 0; i < size; ++i)
        {
            cout << v1[i].m_data <<  "\t";
        }
        cout << endl;
    }

    void testVector()
    {
        cout << "testVector" << endl;

        testCase6();
        testCase7();
        testCase8();
        testCase9();
     
        cout << endl;
    }

    //////////////////////////////////////////////////////////////////////
    void test()
    {
        cout << "vector_private test" << endl;
       
        testIterator();
        testVector();

        cout << endl;
    }
}

#endif

