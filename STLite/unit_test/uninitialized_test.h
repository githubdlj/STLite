/********************************************************************
	Time:	  2015/10/23
	Filename: uninitialized_test
	Author:	  dinglj
	
	Purpose:  ≤‚ ‘uninitialized
*********************************************************************/
#ifndef _UNINITIALIZED_TEST_H_
#define _UNINITIALIZED_TEST_H_

#include "../stlite_uninitialized.h"
using namespace STLite;
using std::cout;
using std::cin;
using std::endl;

namespace uninitialized_unit
{

const int OBJECT_NUM = 5;
void testCase1()
{
    int from[OBJECT_NUM] = {1, 2, 3, 4, 5};
    int to[OBJECT_NUM];

    uninitialized_copy(from, from + OBJECT_NUM, to);

    for (int i = 0; i < OBJECT_NUM; i++)
    {
  //      cout << to[i];
    }

    cout << endl;
}
void test()
{
    cout << "uninitialized test" << endl;
    testCase1();
}

}
#endif