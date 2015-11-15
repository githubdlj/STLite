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
#include "../stlite_alloc.h"
#include "../stlite_construct.h"

//////////////////////////////////////////////////////////////////////
namespace uninitialized_public
{
    //  note, that the uninitialized_xx function should be called on the uninitialized memory.
    //  test for copy
    void testCase1()
    {
        cout << "testCase1" << endl;
        
        const int from[OBJECT_NUM] = {0, 1, 2, 3, 4};
     //   int to[OBJECT_NUM];   //  to[OBJECT_NUM] has initialized.
        
        allocator<int> alloc;
        int *to = alloc.allocate(OBJECT_NUM);   //  allocate memory, int *to has NOT initialized.

        //  construct the objects
        uninitialized_copy(from, from + OBJECT_NUM, to);    //  uninitialzied_copy_aux(first, last, __true_type)

        for (int i = 0; i < OBJECT_NUM; ++i)
        {
            cout << to[i] << "\t";
        }
        cout << endl;

        //  destroy the objects
        destroy(to, to + OBJECT_NUM);

        //  free memory.
        alloc.deallocate(to, OBJECT_NUM);

        cout << endl;
    }

    void testCase2()
    {
        cout << "testCase2" << endl;

        const Widget from[OBJECT_NUM] = {0, 1, 2, 3, 4};
        
        //  allocate memory
        allocator<Widget> alloc;
        Widget *to = alloc.allocate(OBJECT_NUM);

        //  construct the objects
        uninitialized_copy(from, from + OBJECT_NUM, to);    //  uninitialized_copy_aux(first, last, __false_type)

        for (int i = 0; i < OBJECT_NUM; ++i)
        {
            cout << to[i].m_value << "\t";
        }
        cout << endl;

        //  destruct the objects
        destroy(to, to + OBJECT_NUM);

        //  free memory
        alloc.deallocate(to, OBJECT_NUM);

        cout << endl;
    }

    void testCase2_()
    {
        cout << "testCase2_" << endl;

        const String from[OBJECT_NUM] = {"String0", "String1", "String2", "Sting3", "String4"};
        
        //  allocate memory
        allocator<String> alloc;
        String *to = alloc.allocate(OBJECT_NUM);

        //  construct objects
        uninitialized_copy(from, from + OBJECT_NUM, to);

        for (int i = 0; i < OBJECT_NUM; ++i)
        {
            cout << to[i].m_data << "\t";
        }
        cout << endl;

        //  destruct objects
        destroy(to, to + OBJECT_NUM);

        //  deallocate memory
        alloc.deallocate(to, OBJECT_NUM);

        cout << endl;
    }

    void testCase3()
    {
        cout << "testCase3" << endl;

        const char from[OBJECT_NUM] = {'a', 'b', 'c', 'd', 'e'};
       
        allocator<char> alloc;
        char *to  = alloc.allocate(OBJECT_NUM);

        uninitialized_copy(from, from + OBJECT_NUM, to);    //  unintialzie_copy(const char *first, const char *last, char *result)

        for (int i = 0; i < OBJECT_NUM; ++i)
        {
            cout << to[i] << "\t";
        }
        cout << endl;

        destroy(to, to + OBJECT_NUM);

        alloc.deallocate(to, OBJECT_NUM);

        cout << endl;
    }

    void testCopy()
    {
        cout << "testCopy" << endl;
       
    //    testCase1();
    //    testCase2();
        testCase2_();
    //    testCase3();
       
        cout << endl;
    }

    //////////////////////////////////////////////////////////////////////
    // test for fill
    void testCase4()
    {
        cout << "testCase4" << endl;

        allocator<int> alloc;
        int *arr = alloc.allocate(OBJECT_NUM);

        uninitialized_fill(arr, arr + OBJECT_NUM, 5);

        for (int i = 0; i < OBJECT_NUM; ++i)
        {
            cout << arr[i] << "\t";
        }
        cout << endl;

        destroy(arr, arr + OBJECT_NUM);

        alloc.deallocate(arr, OBJECT_NUM);

        cout << endl;
    }

    void testCase5()
    {
        cout << "testCase5" << endl;
        
        allocator<Widget> alloc;
        Widget *w = alloc.allocate(OBJECT_NUM);

        uninitialized_fill(w, w + OBJECT_NUM, 5);

        for (int i = 0; i < OBJECT_NUM; ++i)
        {
            cout << w[i].m_value << "\t";
        }
        cout << endl;

        destroy(w, w + OBJECT_NUM);

        alloc.deallocate(w, OBJECT_NUM);

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

        allocator<int> alloc;
        int *arr = alloc.allocate(OBJECT_NUM);

        uninitialized_fill_n(arr, OBJECT_NUM, 6);

        for (int i = 0; i < OBJECT_NUM; ++i)
        {
            cout << arr[i] << "\t";
        }
        cout << endl;

        destroy(arr, arr + OBJECT_NUM);

        alloc.deallocate(arr, OBJECT_NUM);

        cout << endl;
    }

    void testCase7()
    {
        cout << "testCase7" << endl;

        allocator<Widget> alloc;
        Widget *w = alloc.allocate(OBJECT_NUM);
         
        uninitialized_fill_n(w, OBJECT_NUM, 6);

        for (int i = 0; i < OBJECT_NUM; ++i)
        {
            cout << w[i].m_value << endl;
        }
        cout << endl;

        destroy(w, w + OBJECT_NUM);

        alloc.deallocate(w, OBJECT_NUM);

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
     //   testFill_n();
        
        cout << endl;
    }

}
#endif