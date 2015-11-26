/********************************************************************
	Time:	  2015/11/26
	Filename: std_list_test
	Author:	  dinglj
	
	Purpose:  
*********************************************************************/

#ifndef _STD_LIST_TEST_H_
#define _STD_LIST_TEST_H_

#include <list>

#include "common_header_files.h"
#include "common_data.h"
#include "../stlite_algorithm.h"
//////////////////////////////////////////////////////////////////////
namespace std_list_private
{
    //  test merge
    //  merge require the lists are ordered.
    bool isGreater(int a, int b)
    {
        return a > b;
    }

    bool isLess(int a, int b)
    {
        return a < b;
    }

    void testCase1()
    {   
        cout << "testCase1" << endl;

        int arr1[OBJECT_NUM] = {0, 2, 4, 6, 8};
        int arr2[OBJECT_NUM] = {1, 3, 5, 7, 9};
        std::list<int> list1(arr1, arr1 + OBJECT_NUM);
        std::list<int> list2(arr2, arr2 + OBJECT_NUM);
        
        list1.merge(list2);

        print(list1.begin(), list1.end());
        print(list2.begin(), list2.end());

        cout << endl;
    }

    void testCase2()
    {
        cout << "testCase1" << endl;

        int arr1[OBJECT_NUM] = {8, 6, 4, 2, 0};
        int arr2[OBJECT_NUM] = {9, 7, 5, 3, 1};
        std::list<int> list1(arr1, arr1 + OBJECT_NUM);
        std::list<int> list2(arr2, arr2 + OBJECT_NUM);

        list1.merge(list2, isGreater);  //  the lists are ordered(greater), so the function needs isGreater.

        print(list1.begin(), list1.end());
        print(list2.begin(), list2.end());

        cout << endl;
    }

    void testOperations()
    {
        cout << "testOperations" << endl;

   //     testCase1();
        testCase2();

        cout << endl;
    }

    void test()
    {
        cout << "std_list_private test" << endl;

        testOperations();

        cout << endl;
    }
}

#endif