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

//////////////////////////////////////////////////////////////////////
namespace hashtable_private
{
    //  test interface
    void testCase1()
    {
        cout<< "testCase1" << endl;

        hashtableIterator<int, int, int, int, int> it;
        it++;

        hashtable<int, int, int, int, int> hb(10);
        cout << endl;
    }

    //  test 
    void testCase2()
    {
        cout << "testCase2" << endl;

        hashtable<int, int, int, int, int> hb1(13);
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
        hashtableIterator<int, int, int, int, int> it = hb1.begin();
        hashtable<int, int, int, int, int>::iterator last = hb1.end();
        while (it != last)
        {
            cout << *it << endl;
            ++it;
        }

        cout << endl;
    }

    void test()
    {
        cout << "hashtable_private test" << endl;
        //  testCase1();
        testCase2();
        cout << endl;
    }
}
#endif 
