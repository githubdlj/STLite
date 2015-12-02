/********************************************************************
	Time:	  2015/12/02
	Filename: devec_test
	Author:	  dinglj
	
	Purpose:  
*********************************************************************/
#ifndef _PRIVATE_DEVEC_TEST_H_
#define _PRIVATE_DEVEC_TEST_H_

#include "common_header_files.h"
#include "common_data.h"
#include "../stlite_devec.h"

namespace devec_private
{
    void testCase1()
    {
        devecIterator<int> it;
        devec<int> vec;
    }

    void test()
    {
        cout << "devec_private test" << endl;

        testCase1();

        cout << endl;
    }
}

#endif
