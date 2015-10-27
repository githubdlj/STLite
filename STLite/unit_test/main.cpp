/********************************************************************
	Time:	  2015/10/21
	Filename: main
	Author:	  dinglj
	
	Purpose:  主测试函数，用于测试各个测试单元
*********************************************************************/

//////////////////////////////////////////////////////////////////////
#include "iterator_test.h"
#include "type_traits_test.h"
#include "construct_test.h"
#include "alloc_test.h"
#include "uninitialized_test.h"
//////////////////////////////////////////////////////////////////////
#include "../detail_test/vector_detail_test.h"
//////////////////////////////////////////////////////////////////////
#include "vector_test.h"
#include "list_test.h"
#include "other_test.h"


#include <iostream>

using std::cout;
using std::cin;
using std::endl;

using namespace STLite;

int main()
{
    cout << "Hello STLite" << endl;
    
    //  分别调用不同文件的test()
    //  type_traites_unit::test();  
    //  iterator_unit::test();
    //  construct_unit::test();
    //  alloc_unit::test();
    //  uninitialized_unit::test();
    //  list_unit::test();
//     vector_unit::test();
    vector_detail::test();
    other_unit::test();
 
    system("pause");
    return true;
}

