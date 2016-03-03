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
    void testCase1()
    {
        cout<< "testCase1" << endl;

        hashtableIterator<int, int, int, int, int> it;
        it++;

        hashtable<int, int, int, int, int> hb(10);
        cout << endl;
    }

    void test()
    {
        cout << "hashtable_private test" << endl;
        testCase1();
        cout << endl;
    }
}
#endif 
