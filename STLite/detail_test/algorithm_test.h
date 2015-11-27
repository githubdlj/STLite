/********************************************************************
	Time:	  2015/11/27
	Filename: algorithm_test
	Author:	  dinglj
	
	Purpose:  
*********************************************************************/
#ifndef _ALGORITHM_TEST_H_
#define _ALGORITHM_TEST_H_

#include <algorithm>
#include <list>

#include "common_header_files.h"
#include "common_data.h"
#include "../stlite_algorithm.h"
#include "../stlite_list.h"

//////////////////////////////////////////////////////////////////////
namespace algorithm_private
{
    //  test reverse
    void testCase1()
    {
        int arr[OBJECT_NUM] = {0, 1, 2, 3, 4};
        std::list<int> list1(arr, arr + OBJECT_NUM);

        std::reverse(list1.begin(), list1.end());
        print(list1.begin(), list1.end());

        cout << endl;
    }

    void testCase2()
    {
        // case1
        int arr1[OBJECT_NUM] = {0, 1, 2, 3, 4};
        reverse(arr1, arr1 + OBJECT_NUM);
        print(arr1, arr1 + OBJECT_NUM);

        //  case2
        int arr2[OBJECT_NUM] = {0, 1, 2, 3, 4};
        list<int> list1(arr2, arr2 + OBJECT_NUM);
        reverse(list1.begin(), list1.end());
        print(list1.begin(), list1.end());

        //  case
        int arr3[6] = {0, 1, 2, 3, 4, 5};
        list<int> list2(arr3, arr3 + 6);
        reverse(list2.begin(), list2.end());
        print(list2.begin(), list2.end());

        cout << endl;
    }

    void testReverse()
    {
        cout << "testReverse" << endl;

        //  testCase1();
        testCase2();

        cout << endl;
    }

    //////////////////////////////////////////////////////////////////////
    void test()
    {
        cout << "algorithom_private test" << endl;
        
        testReverse();

        cout << endl;
    }
}

#endif