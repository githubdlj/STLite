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

    //  test for String Type
    void testCase5()
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
        //  testCase1();
        //  testCase2();
        //  testCase3();
          testCase4();
        cout << endl;
    }
}
#endif 
