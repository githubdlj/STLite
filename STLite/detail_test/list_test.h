/********************************************************************
	Time:	  2015/11/22
	Filename: list_test
	Author:	  dinglj
	
	Purpose:  test STLite::list
*********************************************************************/

#ifndef _PRIVATE_LIST_TEST_H_
#define _PRIVATE_LIST_TEST_H_

#include "common_header_files.h"
#include "common_data.h"
#include "../stlite_list.h"

//////////////////////////////////////////////////////////////////////
namespace list_private
{
    //  test Iterator
  
    //  test list_node's constructor
    void testCase1()
    {
        cout << "testCase1" << endl;
        
        list_node<int> node1;
        list_node<int> node2(1);
        list_node<String> node3;
        list_node<String> node4("list_node");

        cout << node1.data << endl;
        cout << node2.data << endl;
        cout << node3.data.m_data << endl;
        cout << node4.data.m_data << endl;
        
        cout << endl;
    }

    //  test listIterator
    void testCase2()
    {
        cout << "testCase2" << endl;
        
        //  init an array of list_node
        list_node<int> nodeArr[OBJECT_NUM];
        for (int i = 0; i < OBJECT_NUM; ++i)
        {
            nodeArr[i].data = i;
        }

        for (int i = 1; i < OBJECT_NUM - 1; ++i)
        {
            nodeArr[i].prev = &nodeArr[i - 1];
            nodeArr[i].next = &nodeArr[i + 1];
        }
        nodeArr[0].next = &nodeArr[1];
        nodeArr[OBJECT_NUM - 1].prev = &nodeArr[OBJECT_NUM - 2];
        
        //  init listIterator
        listIterator<int> iter1(&nodeArr[0]);   //  constructor
        listIterator<int> end(NULL);
        //  traverse
        while (end != iter1)
        {
            cout << *iter1 << "\t";     //  operator *
            ++iter1;                    //  operator ++()
        }
        cout << endl;
    }

    void testIterator()
    {
        cout << "testIterator" << endl;

        //  testCase1();
        testCase2();

        cout << endl;
    }

    //////////////////////////////////////////////////////////////////////
    void test()
    {
        cout << "list_private test" << endl;

        testIterator();

        cout << endl;
    }
}

#endif