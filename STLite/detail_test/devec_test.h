/********************************************************************
	Time:	  2015/12/02
	Filename: devec_test
	Author:	  dinglj
	
	Purpose:  
*********************************************************************/
#ifndef _PRIVATE_DEVEC_TEST_H_
#define _PRIVATE_DEVEC_TEST_H_

#include "common_header_files.h"
#include "common_data.h"
#include "../stlite_devec.h"

namespace devec_private
{
    //  test constructor
    void testCase1()
    {
        //  case1
        devec<int> vec1(OBJECT_NUM, 3);
        for (int i = 0; i < OBJECT_NUM; ++i)
        {
            cout << *(vec1.start_of_storage + i) << "\t";
        }
        cout << endl;

        //  case2
        String strArr1[OBJECT_NUM] = {"String0", "String1", "String2", "String3", "String4"};
        devec<String> vec2(strArr1, strArr1 + OBJECT_NUM);
        for (int i = 0; i < OBJECT_NUM; ++i)
        {
            cout << vec2.start_of_storage[i].m_data << "\t";
        }
        cout << endl;
    }

    //////////////////////////////////////////////////////////////////////
    //  test iterator's constructor
    void testCase2()
    {
        int arr1[OBJECT_NUM] = {0, 1, 2, 3, 4};
        devec<int> vec1(arr1, arr1 + OBJECT_NUM);
        devecIterator<int> it(&vec1, 2);    //  constructor

        cout << *it << endl;

        cout << endl;
    }

    void testIterator()
    {
        cout << "testIterator" << endl;

        testCase2();

        cout << endl;
    }

    void test()
    {
        cout << "devec_private test" << endl;

        //  testCase1();
        testIterator();

        cout << endl;
    }
}

#endif
