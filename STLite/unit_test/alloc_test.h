/********************************************************************
	Time:	  2015/10/22
	Filename: alloc_test
	Author:	  dinglj
	
	Purpose:  test allocator
*********************************************************************/
#ifndef _PUBLIC_ALLOC_TEST_H_
#define _PUBLIC_ALLOC_TEST_H_

#include <vector>
#include <list>

#include "common_header_files.h"
#include "common_data.h"
#include "../stlite_alloc.h"

//////////////////////////////////////////////////////////////////////
namespace alloc_public
{
    //  alloc, constructor, destroy elements, destroy space
    void testCase1()
    {
        cout << "testCase1" << endl;

        allocator<int> alloc;

        //  alloc memory
        int *ptr = alloc.allocate(OBJECT_NUM);

        //  construct
        for (int i = 0; i < OBJECT_NUM; ++i)
        {
            alloc.construct(ptr + i, i);    
        }

        //  print
        for (int i = 0; i < OBJECT_NUM; ++i)
        {
            cout << ptr[i] << "\t";
        }
        cout << endl;

        //////////////////////////////////////////////////////////////////////
        //  destroy, destroy has 2 version, 
        //  version 1, has a higher performance
        alloc.destroy(ptr, ptr + OBJECT_NUM); 

        //  version 2
    //     for (int i = 0; i < OBJECT_NUM; ++i)
    //     {
    //         alloc.destroy(ptr + i);     
    //                                    
    //     }

        //  deallocate
        alloc.deallocate(ptr, OBJECT_NUM);

        cout << endl;
    }

    //  
    void testCase2()
    {
        cout << "testCase2" << endl; 

        int arr[OBJECT_NUM];
        for (int i = 0; i < OBJECT_NUM; ++i)
        {
            arr[i] = i;
        }
       
        //  it calls 2 times constructor 
        //  the first one allocate 8 byte, the second allocate OBJECT_NUM * sizof(int) byte
        //  debug it, I find that the first allocate returns std::_Container_proxy *
        std::vector< int, STLite::allocator<int> > v(arr, arr + OBJECT_NUM);

        for (int i = 0; i < OBJECT_NUM; ++i)
        {
            cout << v[i] << "\t";
        }
        cout << endl;
    }

    //  test allocator on list
    void testCase3()
    {
        String strArr1[OBJECT_NUM] = {"String0", "String1", "String2", "String3", "String4"};
        std::list<String, STLite::allocator<String> > list1;
       
        for (int i = 0; i < OBJECT_NUM; ++i)
        {
            list1.push_back(strArr1[i]);
        }

        for (int i = 0; i < OBJECT_NUM; ++i)
        {
            cout << list1.back() << "\t";
            list1.pop_back();
        }
        cout << endl;
    }

    //////////////////////////////////////////////////////////////////////
    void test()
    {
        cout << "alloc_public test" << endl;

        //  testCase1();
        //  testCase2();
        testCase3();

        cout << endl;
    }
}

#endif