/********************************************************************
	Time:	  2016/03/02
	Filename: hashtable_test
	Author:	  dinglj
	
	Purpose:  hashtable_test.h
*********************************************************************/

#ifndef _PRIVATE_HASHTABLE_TEST_H_
#define _PRIVATE_HASHTABLE_TEST_H_

#include "common_header_files.h"
#include "common_data.h"

#include "../stlite_hashtable.h"
#include "../stlite_function.h"     //  identity

//////////////////////////////////////////////////////////////////////
namespace hashtable_private
{
    //  test interface
    void testCase1()
    {
        cout<< "testCase1" << endl;

        hashtableIterator<int, int, hash<int>, identity<int>, equal_to<int> > it;
        it++;

        hashtable<int, int, hash<int>, identity<int>, equal_to<int> > hb(10);
        cout << endl;
    }

    //  test 
    void testCase2()
    {
        cout << "testCase2" << endl;

        hashtable<int, int, hash<int>, identity<int>, equal_to<int> > hb1(13);
        hb1.insert_equal(1);
        hb1.insert_equal(29);
        hb1.insert_equal(17);
        hb1.insert_equal(9);
        hb1.insert_equal(35);
        hb1.insert_equal(11);
        hb1.insert_equal(12);
        hb1.insert_equal(25);
        hb1.insert_equal(22);

        //  test iterator
        hashtableIterator<int, int, hash<int>, identity<int>, equal_to<int> > it = hb1.begin();
        hashtable<int, int, hash<int>, identity<int>, equal_to<int> >::iterator last = hb1.end();
        while (it != last)
        {
            cout << *it << endl;
            ++it;
        }

        cout << endl;
    }

    //  test insert
    void testCase3()
    {
        cout << "testCase3" << endl;
        
        hashtableIterator<int, int, hash<int>, identity<int>, equal_to<int> > it;
        hashtableIterator<int, int, hash<int>, identity<int>, equal_to<int> > last;

        //  insert_unique
        hashtable<int, int, hash<int>, identity<int>, equal_to<int> > hb1(13);
        hb1.insert_unique(1);
        hb1.insert_unique(29);
        hb1.insert_unique(17);
        hb1.insert_unique(9);
        hb1.insert_unique(35);
        hb1.insert_unique(11);
        hb1.insert_unique(12);
        hb1.insert_unique(25);
        hb1.insert_unique(22);

//         it = hb1.begin();
//         last = hb1.end();
//         while (it != last)
//         {
//             cout << *it << endl;
//             ++it;
//         }
//         cout << endl;
        hb1.show();

        //  insert_unique
        hashtable<int, int, hash<int>, identity<int>, equal_to<int> > hb2(13);
        hb2.insert_equal(1);
        hb2.insert_equal(29);
        hb2.insert_equal(17);
        hb2.insert_equal(9);
        hb2.insert_equal(35);
        hb2.insert_equal(11);
        hb2.insert_equal(12);
        hb2.insert_equal(25);
        hb2.insert_equal(22);
        hb2.insert_equal(29);
        hb2.insert_equal(17);

//         it = hb2.begin();
//         last = hb2.end();
//         while (it != last)
//         {
//             cout << *it << endl;
//             ++it;
//         }
        hb2.show();
        cout << endl;
    }

    //  test HashFunc, ExtraKey, EqualKey.
    void testCase4()
    {
        cout << "testCase4" << endl;
        hashtable<int, int, hash<int>, identity<int>, equal_to<int> > hb1(4);
        hb1.insert_unique(0 + 8);
        hb1.insert_unique(0 + 16);
        hb1.insert_unique(0 + 20);
        hb1.insert_unique(1 + 8);
        hb1.insert_unique(2 + 16);
        hb1.insert_unique(3 + 16);
        
        hb1.show();
        cout << endl;
    }

    //  test insert(first, last)
    void testCase5()
    {
        cout << "testCase6" << endl;
        const int arr[OBJECT_NUM] = {0 + 10, 1 + 10, 2 + 10, 3 + 10, 4 + 10};
        hashtable<int, int, hash<int>, identity<int>, equal_to<int> > hb1(4);
        hb1.insert_unique(0 + 16);
        hb1.insert_unique(0 + 20);
        hb1.insert_unique(1 + 8);
        hb1.show();

        hb1.insert_unique(arr, arr + OBJECT_NUM);
        hb1.show();

        cout << endl;
    }

    void testInsert()
    {
        cout << "testInsert" << endl;
        testCase3();
        testCase4();
        testCase5();
        cout << endl;
    }

    //////////////////////////////////////////////////////////////////////
    //  test erase
    void testCase6()
    {
        cout << "testCase6" << endl;
        hashtable<int, int, hash<int>, identity<int>, equal_to<int> > hb1(10);
        hb1.insert_equal(0 + 8);
        hb1.insert_equal(0 + 16);
        hb1.insert_equal(0 + 20);
        hb1.insert_equal(1 + 8);
        hb1.insert_equal(2 + 16);
        hb1.insert_equal(3 + 16);
        hb1.insert_equal(0 + 8);
        hb1.insert_equal(0 + 30);
         
        hb1.show();

        //////////////////////////////////////////////////////////////////////
        //  erase(key)
        hb1.erase(30);      
        hb1.erase(8);

        hb1.show();

        //////////////////////////////////////////////////////////////////////
        //  erase(iterator)
        hashtableIterator<int, int, hash<int>, identity<int>, equal_to<int> > it = hb1.begin();
        hb1.erase(it);

        it = hb1.begin();
        for (int i = 0; i < 2; ++i, ++it);
        cout << *it << endl;
        hb1.erase(it);

        hb1.show();
        cout << endl;
    }

    //  test erase(first, last)
    void testCase7()
    {
        cout << "testCase7" << endl;
        hashtable<int, int, hash<int>, identity<int>, equal_to<int> > hb1(10);
        hb1.insert_equal(0 + 8);
        hb1.insert_equal(0 + 16);
        hb1.insert_equal(0 + 20);
        hb1.insert_equal(1 + 8);
        hb1.insert_equal(2 + 16);
        hb1.insert_equal(3 + 16);
        hb1.insert_equal(0 + 8);
        hb1.insert_equal(0 + 30);
        hb1.insert_equal(0 + 10);
        hb1.show();

        hashtableIterator<int, int, hash<int>, identity<int>, equal_to<int> > first = hb1.find(30);
        hashtableIterator<int, int, hash<int>, identity<int>, equal_to<int> > last = hb1.find(9);
//         cout << *first << endl;
//         cout << *last << endl;
        
        hb1.erase(first, last);
        hb1.show();

        cout << endl;
    }
    
    void testCase8()
    {
        cout << "testCase7" << endl;
        hashtable<int, int, hash<int>, identity<int>, equal_to<int> > hb1(10);
        hb1.insert_equal(0 + 8);
        hb1.insert_equal(0 + 16);
        hb1.insert_equal(0 + 20);
        hb1.insert_equal(1 + 8);
        hb1.insert_equal(2 + 16);
        hb1.insert_equal(3 + 16);
        hb1.insert_equal(0 + 8);
        hb1.insert_equal(0 + 30);
        hb1.insert_equal(0 + 10);
        hb1.show();

        //  first != NULL, last == NULL
        hashtableIterator<int, int, hash<int>, identity<int>, equal_to<int> > first = hb1.find(30);
        hashtableIterator<int, int, hash<int>, identity<int>, equal_to<int> > last = hb1.end();
//         cout << *first << endl;
//         cout << *last << endl;

        hb1.erase(first, last);
        hb1.show();

        cout << endl;
    }
    void testErase()
    {
        cout << "testErase" << endl;
        //  testCase6();
        //  testCase7();
        testCase8();
        cout << endl;
    }
    //  test for String Type
    void testCase16()
    {
//         hashtable<int, int, int, int, int> hb1(4);
//         hb1.insert_unique("String0");
//         hb1.insert_unique("String1");
//         hb1.insert_unique("String2");
//         hb1.insert_unique("String3");
    }

    void test()
    {
        cout << "hashtable_private test" << endl;
        //testInsert();
        testErase();
        cout << endl;
    }
}
#endif 
