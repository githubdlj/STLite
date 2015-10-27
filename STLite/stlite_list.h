/********************************************************************
	Time:	  2015/10/25
	Filename: stlite_list
	Author:	  dinglj
	
	Purpose:  list实现
*********************************************************************/
#ifndef _STLIST_LIST_H_
#define _STLIST_LIST_H_

#include "stlite_alloc.h"   //  allocator
using namespace STLite;

namespace STLlite
{
    //  node
    template<class T>
    struct list_node
    {
        typedef list_node<T> pointer;
        pointer prev;
        pointer next;
    };

    //  list
    template<class T, class Alloc = allocator<T>>
    class list
    {
    protected:
        typedef list_node<T> list_node;
        typedef allocator<T> list_node_allocator;   //  节点内存分配器
    
    };

}
#endif
