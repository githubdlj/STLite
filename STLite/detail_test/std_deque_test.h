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

    void test()
    {
        cout << "std_deque_private test" << endl;

        testCase1();

        cout << endl;
    }
}
