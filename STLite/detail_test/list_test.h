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
#include "../stlite_vector.h"

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
    void testCase3()
    {
        cout << "testCase3" << endl;

        list<int> list1;    //  list()

        //  list(n, value)  
        list<int> list2(OBJECT_NUM, 1);    

        list_node<int> *begin = list2.node->next;
        while (list2.node != begin)
        {
            cout << begin->data << "\t";    //  1 1 1 1 1
            begin = begin->next;
        }
        cout << endl;

        //  list(first, last)
        int arr[OBJECT_NUM] = {0, 1, 2, 3, 4};
        list<int> list3(arr, arr + OBJECT_NUM);

        list<int>::iterator it = list3.begin();
        list<int>::iterator end = list3.end();

        for (; end != it; ++it)
        {
            cout << *it << "\t";    //  0 1 2 3 4
        }
        cout << endl;

        //  list(first, last)
        list<int> list4(list3.begin(), list3.end());

        it = list4.begin();
        end = list4.end();
        for (; end != it; ++it)
        {
            cout << *it << "\t";    // 0 1 2 3 4 
        }
        cout << endl;

        //  list(first, last)
        vector<int> v(arr, arr + OBJECT_NUM);   
        list<int> list5(v.begin(), v.end());

        it = list5.begin();
        end = list5.end();
        for (; end != it; ++it)
        {
            cout << *it << "\t";    //  0 1 2 3 4
        }
        cout << endl;
    }

    void testCase4()
    {
        cout << "testCase4" << endl;

        //  list<String>(first, last)
        String strArr[OBJECT_NUM] = {"String0", "String1", "String2", "String3", "String4"};
        list<String> list1(strArr, strArr + OBJECT_NUM);

        listIterator<String> it = list1.begin();
        listIterator<String> end = list1.end();
        for (; end != it; ++it)
        {
            //  cout << (*it).m_data << "\t";
            cout << it->m_data << "\t"; 
        }
        cout << endl;

        //  traverse list reversely
        it = list1.end();
        end = list1.begin();
        for (; end != it; --it)
        {
            cout << it.node->prev->data.m_data << "\t";
        }
        cout << endl;
    }

    //  test copy && assignment
    void testCase5()
    {
        cout << "testCase5" << endl;

        String strArr[OBJECT_NUM] = {"String0", "String1", "String2", "String3", "String4"};
        list<String> list1(strArr, strArr + OBJECT_NUM);

        //  copy constructor
        list<String> list2(list1);      
        
        listIterator<String> it = list2.begin();
        listIterator<String> end = list2.end();
        for (; end != it; ++it)
        {
            cout << it->m_data << "\t";
        }
        cout << endl;

        //////////////////////////////////////////////////////////////////////
        //  operator =
        //  case1
        list<String> list3(2, "String");     
        list3 = list2;                 

        it = list3.begin();
        end = list3.end();
        for (; end != it; ++it)
        {
            cout << it->m_data << "\t";
        }
        cout << endl;

        //  case2
        list<String> list4(10, "String"); 
        list4 = list2;

        it = list4.begin();
        end = list4.end();
        for (; end != it; ++it)
        {
            cout << it->m_data << "\t";
        }
        cout << endl;
    }

    void testConstruct()
    {
        cout << "testConstruct" << endl;

    //    testCase3();
    //    testCase4();
        testCase5();

        cout << endl;
    }

    //////////////////////////////////////////////////////////////////////

    //  test Insert
    void testCase6()
    {
        cout << "testCase6" << endl;

        String strArr[OBJECT_NUM] = {"String0", "String1", "String2", "String3", "String4"};
        list<String> list1(strArr, strArr + OBJECT_NUM);

        listIterator<String> it = list1.begin();
        list1.insert(it, "InsertString0");      //  insert(pos, value)

        ++it;
        list1.insert(it, 2, "InsertString1_2");   //  insert(pos, n, value)

        it = list1.end();
        String insertStrArr[2] = {"InsertString3", "InsertString4"};
        list1.insert(it, insertStrArr, insertStrArr + 2);   //  insert(pos, first, last);

        //  traverse list
        listIterator<String> end  = list1.end();
        for (it = list1.begin(); end != it; ++it)
        {
            cout << it->m_data << "\t";
        }
        cout << endl;

        list<String> list2;
        list2.insert(list2.begin(), list1.begin(), list1.end());    //  insert(pos, first, last)
        
        end = list2.end();
        for (it = list2.begin(); end != it; ++it)
        {
            cout << it->m_data << "\t";
        }
        cout << endl;
    }

    //  test erase
    void testCase7()
    {
        cout << "testCase7" << endl;

        String strArr[OBJECT_NUM] = {"String0", "String1", "String2", "String3", "String4"};
        list<String> list1(strArr, strArr + OBJECT_NUM);

        list<String>::iterator first = ++list1.begin();
        list<String>::iterator last = --list1.end();
        list<String>::iterator it = list1.erase(first, last);
        cout << it->m_data << endl;     //  String4
       
        list<String>::iterator end = list1.end();
        for (it = list1.begin(); end != it; ++it)
        {
            cout << it->m_data << "\t";     //  String0 String4
        }
        cout << endl;
    }

    //  test assign
    void testCase8()
    {
        //  3 kinds of data type, it can reduce 3 kinds of iterators.
        String strArr[OBJECT_NUM] = {"String0", "String1", "String2", "String3", "String4"};
        vector<String> vec(strArr, strArr + OBJECT_NUM);
        list<String> list1(vec.begin(), vec.end());

        //  case1, the original list is shorter
        list<String> list2(2, "String");
        list2.assign(strArr, strArr + OBJECT_NUM);
        
        list<String>::iterator it = list2.begin();
        list<String>::iterator end = list2.end();
        for (; it != end; ++it)
        {
            cout << it->m_data << "\t";
        }
        cout << endl;

        //  case2, the origin list is longer
        list<String> list3(10, "String");
        list3.assign(vec.begin(), vec.end());

        it = list3.begin();
        end = list3.end();
        for (; it != end; ++it)
        {
            cout << it->m_data << "\t";
        }

        //  case3, equal
        list<String> list4(OBJECT_NUM, "String");
        list4.assign(list1.begin(), list1.end());

        it = list4.begin();
        end = list4.end();
        for (; it != end; ++it)
        {
            cout << it->m_data << "\t";
        }
        cout << endl;
    }

    void testModifies()
    {
        cout << "testModifies" << endl;

        //  testCase6();
        //  testCase7();
        testCase8();

        cout << endl;
    }

    void test()
    {
        cout << "list_private test" << endl;

   //     testIterator();
   //     testConstruct();
        testModifies();
        
        cout << endl;
    }
}

#endif