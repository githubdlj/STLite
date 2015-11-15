/********************************************************************
	Time:	  2015/10/23
	Filename: uninitialized_test
	Author:	  dinglj
	
	Purpose:  
*********************************************************************/
#ifndef _PUBLIC_UNINITIALIZED_TEST_H_
#define _PUBLIC_UNINITIALIZED_TEST_H_

#include "common_header_files.h"
#include "common_data.h"
#include "../stlite_uninitialized.h"

//////////////////////////////////////////////////////////////////////
namespace uninitialized_public
{
    //  test for copy
    void testCase1()
    {
        cout << "testCase1" << endl;
        
        const int from[OBJECT_NUM] = {0, 1, 2, 3, 4};
        int to[OBJECT_NUM];

        uninitialized_copy(from, from + OBJECT_NUM, to);    //  uninitialzied_copy_aux(first, last, __true_type)

        for (int i = 0; i < OBJECT_NUM; ++i)
        {
            cout << to[i];
        }

        cout << endl;
    }

    void testCase2()
    {
        cout << "testCase2" << endl;

        const Widget from[OBJECT_NUM] = {0, 1, 2, 3, 4};
        Widget to[OBJECT_NUM];

        uninitialized_copy(from, from + OBJECT_NUM, to);    //  uninitialized_copy_aux(first, last, __false_type)

        for (int i = 0; i < OBJECT_NUM; ++i)
        {
            cout << to[i].m_value;
        }

        cout << endl;
    }

    void testCase2_()
    {
        cout << "testCase2_" << endl;

        //  test String

        cout << endl;
    }

    void testCase3()
    {
        cout << "testCase3" << endl;

        const char from[OBJECT_NUM] = {'a', 'b', 'c', 'd', 'e'};
        char to[OBJECT_NUM];

        uninitialized_copy(from, from + OBJECT_NUM, to);    //  unintialzie_copy(const char *first, const char *last, char *result)

        for (int i = 0; i < OBJECT_NUM; ++i)
        {
            cout << to[i];
        }

        cout << endl;
    }

    void testCopy()
    {
        cout << "testCopy" << endl;
       
        testCase1();
        testCase2();
//         testCase2_();
//         testCase3();
       
        cout << endl;
    }

    //////////////////////////////////////////////////////////////////////
    // test for fill
    void testCase4()
    {
        cout << "testCase4" << endl;

        int arr[OBJECT_NUM];

        uninitialized_fill(arr, arr + OBJECT_NUM, 5);

        for (int i = 0; i < OBJECT_NUM; ++i)
        {
            cout << arr[i];
        }

        cout << endl;
    }

    void testCase5()
    {
        cout << "testCase5" << endl;
        
        Widget w[OBJECT_NUM];

        uninitialized_fill(w, w + OBJECT_NUM, 5);

        for (int i = 0; i < OBJECT_NUM; ++i)
        {
            cout << w[i].m_value;
        }

        cout << endl;
    }

    void testFill()
    {
        cout << "testFill" << endl;
        
        testCase4();
        testCase5();
        
        cout << endl;
    }

    //////////////////////////////////////////////////////////////////////
    //  test for uninitialized_fill_n
    void testCase6()
    {
        cout << "testCase6" << endl;

        int arr[OBJECT_NUM];

        uninitialized_fill_n(arr, OBJECT_NUM, 6);

        for (int i = 0; i < OBJECT_NUM; ++i)
        {
            cout << arr[i];
        }

        cout << endl;
    }

    void testCase7()
    {
        cout << "testCase7" << endl;

        Widget w[OBJECT_NUM];

        uninitialized_fill_n(w, OBJECT_NUM, 6);

        for (int i = 0; i < OBJECT_NUM; ++i)
        {
            cout << w[i].m_value;
        }

        cout << endl;
    }

    void testFill_n()
    {
        cout << "testFill_n" << endl;
        
        testCase6();
        testCase7();
        
        cout << endl;
    }

    //////////////////////////////////////////////////////////////////////
    void test()
    {
        cout << "uninitialized_public test" << endl;
        
        testCopy();
     //   testFill();
      //  testFill_n();
        
        cout << endl;
    }

}
#endif