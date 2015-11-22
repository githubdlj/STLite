/********************************************************************
	Time:	  2015/11/14
	Filename: private_test
	Author:	  dinglj
	
	Purpose:  private test
*********************************************************************/
//  private_test header files
#include "common_header_files.h"

#include "base_test.h"
#include "String_test.h"

#include "std_vector_test.h"

#include "vector_test.h"
#include "list_test.h"

//////////////////////////////////////////////////////////////////////
void private_test()
{
    cout << "private test" << endl;
    
//    base_private::test();
//    String_private::test();
// 
//     std_vector_private::test();
// 
//     vector_private::test();
     list_private::test();

    cout << endl;
}