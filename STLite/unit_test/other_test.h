/********************************************************************
	Time:	  2015/10/21
	Filename: other_test
	Author:	  dinglj
	
	Purpose:  other test, test namespace 
*********************************************************************/
#ifndef _PUBLIC_OTHER_TEST_H_
#define _PUBLIC_OTHER_TEST_H_

#include "common_header_files.h"

//////////////////////////////////////////////////////////////////////
//  if we use the namespace, we can have the same function name among different files
//  if we want to call a function, we can do it like this:  other_public::test()
namespace other_public
{
    void test()
    {
        cout << "other_public test" << endl;
    }

}
#endif