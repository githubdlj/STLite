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

struct Mystruct
{
    Mystruct(int value = 0)
    {
        m = value;
    }
    int m;
};

//  test for copy
void testCase1()
{
    int from[OBJECT_NUM] = {1, 2, 3, 4, 5};
    int to[OBJECT_NUM];

    uninitialized_copy(from, from + OBJECT_NUM, to);

    for (int i = 0; i < OBJECT_NUM; i++)
    {
        cout << to[i];
    }

    cout << endl;
}

void testCase2()
{
    Mystruct from[OBJECT_NUM] = {1, 2, 3, 4, 5};
    Mystruct to[OBJECT_NUM];

    uninitialized_copy(from, from + OBJECT_NUM, to);

    for (int i = 0; i < OBJECT_NUM; i++)
    {
        cout << to[i].m;
    }
    cout << endl;
}

void testCase3()
{
    const char from[OBJECT_NUM] = {'a', 'b', 'c', 'd', 'e'};
    char to[OBJECT_NUM];

    uninitialized_copy(from, from + OBJECT_NUM, to);

    for (int i = 0; i < OBJECT_NUM; i++)
    {
        cout << to[i];
    }

    cout << endl;
}
// test for fill
void testCase4()
{
    int arr[OBJECT_NUM];

    uninitialized_fill(arr, arr + OBJECT_NUM, 5);

    for (int i = 0; i < OBJECT_NUM; i++)
    {
        cout << arr[i];
    }

    cout << endl;
}

void testCase5()
{
    Mystruct structArr[OBJECT_NUM];

    uninitialized_fill(structArr, structArr + OBJECT_NUM, 5);

    for (int i = 0; i < OBJECT_NUM; i++)
    {
        cout << structArr[i].m;
    }

    cout << endl;
}

//  test for uninitialized_fill_n
void testCase6()
{
    int arr[OBJECT_NUM];

    uninitialized_fill_n(arr, OBJECT_NUM, 6);

    for (int i = 0; i < OBJECT_NUM; i++)
    {
        cout << arr[i];
    }
    cout << endl;
}

void testCase7()
{
    Mystruct structArr[OBJECT_NUM];

    uninitialized_fill_n(structArr, OBJECT_NUM, 6);

    for (int i = 0; i < OBJECT_NUM; i++)
    {
        cout << structArr[i].m;
    }

    cout << endl;
}
//////////////////////////////////////////////////////////////////////
void test()
{
    cout << "uninitialized test" << endl;
    testCase1();
    testCase2();
    testCase3();

    testCase4();
    testCase5();

    testCase6();
    testCase7();
}

}
#endif