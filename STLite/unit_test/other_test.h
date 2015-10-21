/********************************************************************
	Time:	  2015/10/21
	Filename: other_test
	Author:	  dinglj
	
	Purpose:  代表其他测试函数，主要测试命名空间的使用
*********************************************************************/
#ifndef _OTHER_TEST_H_
#define _OTHER_TEST_H_

#include <iostream>

using namespace STLite;
using namespace std;

//  采用命名空间原因是可以在不同的测试文件中拥有相同的函数名，如test，如果调用该文件中的test，
//  则采用other_test::test()
namespace other_test
{

void test()
{
    std::cout << "other test" << endl;
}

}
#endif