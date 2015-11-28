/********************************************************************
	Time:	  2015/11/27
	Filename: algorithm_test
	Author:	  dinglj
	
	Purpose:  
*********************************************************************/
#ifndef _ALGORITHM_TEST_H_
#define _ALGORITHM_TEST_H_

#include <algorithm>
#include <vector>
#include <list>

#include "common_header_files.h"
#include "common_data.h"
#include "../stlite_algorithm.h"
#include "../stlite_function.h"
#include "../stlite_vector.h"
#include "../stlite_list.h"

//////////////////////////////////////////////////////////////////////
namespace algorithm_private
{
    struct is_odd
    {
        bool operator() (int value)
        {
            return 1 == value % 2;
        }
    };

    //  test reverse
    void testCase1()
    {
        int arr[OBJECT_NUM] = {0, 1, 2, 3, 4};
        std::list<int> list1(arr, arr + OBJECT_NUM);

        std::reverse(list1.begin(), list1.end());   //  list has it's own reverse function
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

        //  case, use the reverse on list
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
    //  test adjacent_find
    void testCase5()
    {
        const int NUM = 2 * OBJECT_NUM;
        int arr1[NUM] = {3,5,4,4,2,6,5,2,3,3};  //  unordered

        int *pos = adjacent_find(arr1, arr1 + NUM, equal_to<int>());    
        cout << *pos << endl;   //  4

        pos = adjacent_find(arr1 + 3, arr1 + 9);    //  [4 2 6 5 2 3 3)
        cout << *pos << endl;   //  not find, return arr + 9, 3

        cout << endl;
    }

    void testAdjacentFind()
    {
        cout << "testAdjacentFind" << endl;

        testCase5();

        cout << endl;
    }

    //////////////////////////////////////////////////////////////////////
    //  test unique
    void testCase3()
    {
        const int NUM = 2 * OBJECT_NUM; 
        //  case1
        int arr1[NUM] = {3,4,4,1,2,6,5,2,3,0};  //  unordered
        std::unique_copy(arr1, arr1 + NUM, arr1, equal_to<int>());
        print(arr1, arr1 + NUM);    //  3 4 1 2 6 5 2 3 0 [0]

        //  case2
        int arr2[NUM] = {0,1,2,2,3,3,4,5,6,6};  //  ordered
        std::unique_copy(arr2, arr2 + NUM, arr2);
        print(arr2, arr2 + NUM);    // 0 1 2 3 4 5 6 [5 6 6]

        cout << endl;
    }

    void testCase4()
    {
        const int NUM = 2 * OBJECT_NUM; 
        //  case1
        int arr1[NUM] = {3,4,4,1,2,6,5,2,3,0};  //  unordered
        unique_copy(arr1, arr1 + NUM, arr1, equal_to<int>());
        print(arr1, arr1 + NUM);    //  3 4 1 2 6 5 2 3 0 [0]

        //  case2
        int arr2[NUM] = {0,1,2,2,3,3,4,5,6,6};  //  ordered
        int *pos = unique_copy(arr2, arr2 + NUM, arr2);
        cout << *pos << endl;       //  5
        print(arr2, arr2 + NUM);    //  0 1 2 3 4 5 6 [5 6 6]


        cout << endl;
    }

    struct same_integer_part
    {
        bool operator() (double first, double second)
        {
            return (int)first == (int)second;
        }
    };

    void testCase6()
    {
        double arr1[OBJECT_NUM * 2] = {2.72, 3.14, 12.15, 12.77, 12.77,
            15.3, 72.25, 72.25, 73.0, 73.35};
        list<double> list1(arr1, arr1 + OBJECT_NUM * 2);
        // 
        double *pos = unique(arr1, arr1 + OBJECT_NUM * 2, same_integer_part());
        cout << *pos << endl;   //  72.75
        print(arr1, arr1 + OBJECT_NUM * 2); 
        //  2.72, 3.14, 12.15, 15.3, 72.25, 73.0 [72.25, 72.25, 73.0, 73.35]

        //  use unique on list
        listIterator<double> it = unique(list1.begin(), list1.end(), same_integer_part());
        cout << *it << endl;
        print(list1.begin(), list1.end());
        //  2.72, 3.14, 12.15, 15.3, 72.25, 73.0 [72.25, 72.25, 73.0, 73.35]

        cout << endl;
    }

    void testUnique()
    {
        cout << "testUnique" << endl;

        //  testCase3();
        //  testCase4();
        testCase6();

        cout << endl;
    }

    //////////////////////////////////////////////////////////////////////
    void testCase10()
    {
        const int NUM = 2 * OBJECT_NUM;
        int arr1[NUM] = {0,2,3,2,4,5,6,8,7,9};
        
        int *pos = find_if(arr1, arr1 + NUM, is_odd());
        cout << *pos << endl;

    }
    //  test find, find_if
    void testFind()
    {
        cout << "testFind" << endl;

        testCase10();

        cout << endl;
    }

    //////////////////////////////////////////////////////////////////////
    //  test remove_copy, remove
    void testCase8()
    {
        const int NUM = 2 * OBJECT_NUM;
        int arr1[NUM] = {0,1,3,2,4,5,6,8,7,9};

        int *pos = remove_copy_if(arr1, arr1 + NUM, arr1, is_odd());   
        cout << *pos << endl;       //  5
        print(arr1, arr1 + NUM);    //  0 2 4 6 8 [5 6 7 8 9]

        cout << endl;
    }

    void testCase9()
    {
        //  case1
        const int NUM = 2 * OBJECT_NUM;
        int arr1[NUM] = {0,1,3,2,4,5,6,8,7,9};

        int *pos = remove_if(arr1, arr1 + NUM, is_odd());   
        cout << *pos << endl;       //  5
        print(arr1, arr1 + NUM);    //  0 2 4 6 8 [5 6 7 8 9]

        //  case2, use remove on list
        int arr2[NUM] = {3,4,4,1,2,6,5,2,3,0};
        list<int> list1(arr2, arr2 + NUM);
        
        listIterator<int> it = remove(list1.begin(),list1.end(), 3);
        cout << *it << endl;
        print(list1.begin(), list1.end());  //  4 4 1 2 6 5 2 0 [3 0]
        
        cout << endl;
    }

    void testRemove()
    {
        cout << "testRemove" << endl;

        //  testCase8();
        testCase9();

        cout << endl;
    }

    //////////////////////////////////////////////////////////////////////
    void testCase7()
    {
        int arr1[OBJECT_NUM] = {0, 1, 2, 3, 4};

        //  case1, first is RandomAccessIterator
        list<int> list1;
        list1.resize(OBJECT_NUM);
        copy(arr1, arr1 + OBJECT_NUM, list1.begin());
        print(list1.begin(), list1.end());

        //  case2, first is InputIterator
        vector<int> vec1;
        vec1.resize(OBJECT_NUM);
        copy(list1.begin(), list1.end(), vec1.begin());
        print(vec1.begin(), vec1.end());

        cout << endl;
    }

    void testCopy()
    {
        cout << "testCopy" << endl;

        testCase7();

        cout << endl;
    }

    //////////////////////////////////////////////////////////////////////
    void test()
    {
        cout << "algorithom_private test" << endl;
        
        //  testReverse();
        //  testAdjacentFind();
        //  testUnique();
        //  testCopy();
        //    testFind();
        testRemove();
        
        cout << endl;
    }
}

#endif