/********************************************************************
	Time:	  2015/11/02
	Filename: String_test
	Author:	  dinglj
	
	Purpose:  test my String
*********************************************************************/
#ifndef _PRIVATE_STRING_TEST_H_
#define _PRIVATE_STRING_TEST_H_

#include "common_header_files.h"
#include "common_data.h"

//////////////////////////////////////////////////////////////////////
namespace String_private
{
    void testCase1()
    {
        cout << "testCase1" << endl;

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
        cout << endl;
    }

    //  test self assignment
    void testCase2()
    {
        cout << "testCase2" << endl;

        String s1("hello world");   //  constructor
        s1 = s1;

        cout << s1.m_data << endl;

        cout << endl;
    }

    //////////////////////////////////////////////////////////////////////
    void test()
    {
        cout << "String_private test" << endl;

        testCase1();
        testCase2();

        cout << endl;
    }
}
#endif