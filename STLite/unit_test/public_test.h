/********************************************************************
	Time:	  2015/11/14
	Filename: public_test
	Author:	  dinglj
	
	Purpose:  public test
*********************************************************************/
#include "common_header_files.h"

#include "type_traits_test.h"
#include "iterator_test.h"
#include "construct_test.h"
#include "uninitialized_test.h"
#include "alloc_test.h"

#include "vector_test.h"
#include "list_test.h"

#include "other_test.h"
//////////////////////////////////////////////////////////////////////

void public_test()
{
    cout << "public test" << endl;

//    type_traites_public::test();
//    iterator_public::test();
//     construct_public::test();
//    uninitialized_public::test();
     alloc_public::test();

 
//     vector_public::test();
//     list_public::test();
 
//     other_public::test();

    cout << endl;
}
