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
#include "std_list_test.h"
#include "std_deque_test.h"

#include "vector_test.h"
#include "list_test.h"
#include "devec_test.h"

#include "algorithm_test.h"
//////////////////////////////////////////////////////////////////////
void private_test()
{
    cout << "private test" << endl;
    
//    base_private::test();
//    String_private::test();
// 
     std_vector_private::test();
//    std_list_private::test();
//        std_deque_private::test();
// 
//     vector_private::test();
//     list_private::test();
//        devec_private::test();

//    algorithm_private::test();
    cout << endl;
}