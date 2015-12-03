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

    void testCase3()
    {
        //  stimulate a devec.
        devec<int> vec;
        vec.start_of_storage = NULL;
        vec.end_of_storage = vec.start_of_storage + OBJECT_NUM + 1;    
        vec.start = 4;
        vec.finish = 2;


        cout << vec.capacity() << endl;
        cout << vec.size() << endl;

        cout << endl;
    }

    void testCapacity()
    {
        cout << "testCapacity" << endl;

        testCase3();

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

        devec<int>::iterator it2 = vec1.begin();    //  begin
        cout << *it2 << endl;

        cout << endl;
    }

    //  test iterator's ++, --
    void testCase4()
    {
        devec<int> vec1;
        
        //  allocate memory
        vec1.start_of_storage = allocator<int>::allocate(OBJECT_NUM + 1);
        vec1.end_of_storage = vec1.start_of_storage + OBJECT_NUM + 1;
        
        //  assign
        *(vec1.start_of_storage + 0) = 0;
        *(vec1.start_of_storage + 1) = 1;
        *(vec1.start_of_storage + 4) = 2;
        *(vec1.start_of_storage + 5) = 3;

        vec1.start = 4;
        vec1.finish = 2;    //  [0, 1, x, x, 2, 3]

        //  traverse
        devec<int>::iterator it = vec1.begin();
        devec<int>::iterator end = vec1.end();
        for (; it != end; ++it)
        {
            cout << *it << "\t";    //  2 3 0 1
        }
        cout << endl;

        devec<int>::iterator begin = vec1.begin();
        it  = vec1.end();
        for (; it != begin;)
        {
            --it;
            cout << *it << "\t";    //  1 0 3 2
        }
        cout << endl;
    }

    void testIterator()
    {
        cout << "testIterator" << endl;

        testCase2();
        testCase4();

        cout << endl;
    }

    void test()
    {
        cout << "devec_private test" << endl;

        //  testCase1();
          testIterator();
        //  testCapacity();

        cout << endl;
    }
}

#endif
