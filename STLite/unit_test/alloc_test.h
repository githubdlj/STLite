/********************************************************************
	Time:	  2015/10/22
	Filename: alloc_test
	Author:	  dinglj
	
	Purpose:  测试alloc内存配置器
*********************************************************************/

#include "../stlite_alloc.h"
#include <vector>

using std::cout;
using std::cin;
using std::endl;
using namespace STLite;

namespace alloc_unit
{
const int OBJECT_NUM = 10;

void test_alloc_on_container()
{
    int arr[OBJECT_NUM];
    for (int i = 0; i < OBJECT_NUM; i++)
    {
        arr[i] = i;
    }
    NULL
    //  调用了两次内存分配construct函数
    //  第一次分配8Byte，第二次分配sizeof(int) * OBJECT_NUM byte
    //  通过调试，发现第一次分配的8byte内存返回类型为std::_Container_proxy *
    std::vector< int, STLite::allocator<int> > v(arr, arr + OBJECT_NUM);

    for (int i = 0; i < OBJECT_NUM; i++)
    {
        cout << v[i];
    }
    cout << endl;
}

void test_alloc_on_basedata()
{
    STLite::allocator<int> alloc;
    
    //  alloc memory
    int *ptr = alloc.allocate(OBJECT_NUM);

    //  construct;
    for (int i = 0; i < OBJECT_NUM; i++)
    {
        alloc.construct(ptr + i, i);    
    }

    //  print
    for (int i = 0; i < OBJECT_NUM; i++)
    {
        cout << ptr[i];
    }

    //  destroy
    alloc.destroy(ptr);

    //  deallocate
    alloc.deallocate(ptr, OBJECT_NUM);


}
void test()
{
       cout << "alloc test" << endl;
       //   test_alloc_on_basedata();
       cout << endl;
       test_alloc_on_container();
}
}