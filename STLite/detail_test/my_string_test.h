/********************************************************************
	Time:	  2015/11/02
	Filename: my_string
	Author:	  dinglj
	
	Purpose:  test my String
*********************************************************************/
#ifndef _MY_STRING_TEST_H_
#define _MY_STRING_TEST_H_

#include "common.h"

//////////////////////////////////////////////////////////////////////
namespace string_detail
{
    void testCase1()
    {
        String s1;      //  constructor
        cout << s1.m_data << endl;

        //////////////////////////////////////////////////////////////////////
        String s2("hello world");   //  constructor
        cout << s2.m_data << endl;

        //////////////////////////////////////////////////////////////////////
        String s3 = s2;     //  copy
        cout << s3.m_data << endl;
        
        //////////////////////////////////////////////////////////////////////
        String s4;
        s4 = s3;        //  assignment
        cout << s4.m_data << endl;

        //  destroy 4 times
    }

    //  test self assignment
    void testCase2()
    {
        String s1("hello world");   //  constructor
        s1 = s1;

        cout << s1.m_data << endl;
    }

    void test()
    {
        cout << "string_datail test" << endl;

   //     testCase1();
        testCase2();
    }
}
#endif