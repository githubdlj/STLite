/********************************************************************
	Time:	  2015/10/21
	Filename: main
	Author:	  dinglj
	
	Purpose:  主测试函数，用于测试各个测试单元
*********************************************************************/

#include "type_traits_test.h"
#include "iterator_test.h"
#include "other_test.h"

#include <iostream>

using namespace STLite;

int main()
{
    std::cout << "Hello STLite" << std::endl;
    
    //  分别调用不同文件的test()
   //  type_traites_unit::test();  
    iterator_unit::test();
    other_unit::test();
 
    system("pause");
    return true;
}

