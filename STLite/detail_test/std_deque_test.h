/********************************************************************
	Time:	  2015/11/30
	Filename: std_deque_test
	Author:	  dinglj
	
	Purpose:  
*********************************************************************/

#include <deque>

#include "common_header_files.h"

//////////////////////////////////////////////////////////////////////
namespace std_deque_private
{
    void testCase1()
    {
        std::deque<int> deque(3, 0);
        int n = deque.end() - deque.end();
        cout << n << endl;
    }

    void testCase2()
    {
        std::deque<int> d(5, 1);
        std::deque<int>::iterator it = d.begin();

        it = 2 + it;
        cout << *it << endl;
    }

    void test()
    {
        cout << "std_deque_private test" << endl;

        //  testCase1();
        testCase2();

        cout << endl;
    }
}
