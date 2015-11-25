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
#include "../stlite_algorithm.h"    //  for print
#include "../stlite_function.h"     //  for greater, less

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
        cout << "testCase8" << endl;

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

    //  test push, pop
    void testCase9()
    {
        cout << "testCase9" << endl;

        list<String> list1;

        list1.push_back("String0");
        list1.push_back("String1");

        list1.push_front("String2");
        
        list1.pop_back();

        list1.push_front("String3");
        
        list1.pop_front();
        
        listIterator<String> it = list1.begin();
        listIterator<String> end = list1.end();
        for (; it != end; ++it)
        {
            cout << it->m_data << "\t";     //  String2 String0
        }
        cout << endl;
    }

    //  test swap
    void testCase10()
    {
        cout << "testCase10" << endl;

        list<String> list1(OBJECT_NUM, "String0");
        list<String> list2(2, "String1");

        list1.swap(list2);

        list<String>::iterator it = list1.begin();
        list<String>:: iterator end = list1.end();
        for (; it != end; ++it)
        {
            cout << it->m_data << "\t";
        }
        cout << endl;

        it = list2.begin();
        end = list2.end();
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
        //  testCase8();
        //  testCase9();
        testCase10();

        cout << endl;
    }

    //////////////////////////////////////////////////////////////////////
    //  test transfer
    void testCase11()
    {
        cout << "testCase11" << endl;

        int arr[OBJECT_NUM * 2] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
        list<int> list1(arr, arr + OBJECT_NUM * 2);

        list<int>::iterator pos = list1.begin();
        list<int>::iterator first = list1.begin();
        list<int>::iterator last = list1.begin();

        advance(pos, 3);
        advance(first, 5);
        advance(last, 7);

//         //  3, 5, 7
//         cout << *pos << endl;
//         cout << *first << endl;
//         cout << *last << endl;

        //  case1, transfer on 1 list
        list1.transfer(pos, first, last);

        list<int>::iterator it = list1.begin();
        list<int>::iterator end = list1.end();
        for (; it != end; ++it)
        {
            cout << *it << "\t";    // 0 1 2 5 6 3 4 7 8 9
        }   
        cout << endl;

        //  case2, transfer on 2 lists
        list<int> list2(arr, arr + OBJECT_NUM);     //  0 1 2 3 4 

        pos = list2.begin();
        advance(pos, 2);    //  *pos = 2

        first = list1.begin();
        last = list1.begin();
        advance(first, 3);  //  *first = 5
        advance(last, 5);  //  *last = 3

        list1.transfer(pos, first, last);   //  it can also call list2.transfer(pos, first, last)

        it = list1.begin();
        end = list1.end();
        for (; it != end; ++it)
        {
            cout << *it << "\t";    //  0 1 2 3 4 7 8 9
        }
        cout << endl;

        it = list2.begin();
        end = list2.end();
        for (; it != end; ++it)
        {
            cout << *it << "\t";    //  0 1 5 6 2 3 4
        }
        cout << endl;
    }

    //  test reverse
    void testCase12()
    {
        cout << "testCase12" << endl;

        int arr[OBJECT_NUM] = {0, 1, 2, 3, 4};
        list<int> list1(arr, arr + OBJECT_NUM);
        print(list1.begin(), list1.end());

        list1.reverse();
        print(list1.begin(), list1.end());

        //
        list<int> list2(arr, arr + 1);  //  1 nodes
        list2.reverse();
        print(list2.begin(), list2.end());

        // 
        list<int> list3;    //  0 nodes
        list3.reverse();
    }

    //  test sort
    bool isLess(int first, int second)
    {
        return first < second;
    }

    bool isGreater(int first, int second)
    {
        return first > second;
    }

    void testCase14()
    {
        cout << "testCase14" << endl;
        const int NUM = 2 * OBJECT_NUM;
        int order1[NUM] = {3,4,4,1,2,6,5,2,3,0};
        int order2[NUM] = {0,1,2,2,3,3,4,4,5,6};
        int order3[NUM] = {6,5,4,4,3,3,2,2,1,0};
        list<int> list1;
        
        //  case1
        list1.assign(order1, order1 + NUM);
        print(list1.begin(), list1.end());

        list1.sort(greater<int>());
        print(list1.begin(), list1.end());
        cout << endl;

        //  print the elements reversely, make sure that the list is right.
        listIterator<int> it = list1.end();
        listIterator<int> end = list1.begin();
        while (it != end)
        {
            cout << *(--it) <<  "\t";
        }
        cout << endl;

        //  case2
        list1.assign(order2, order2 + NUM);
        print(list1.begin(), list1.end());

        list1.sort();
        print(list1.begin(), list1.end());

        //  case3
        list1.assign(order3, order3 + NUM);
        print(list1.begin(), list1.end());

        list1.sort();
        print(list1.begin(), list1.end());
        cout << endl;
    }

    void testOperations()
    {
        cout << "testOperaions" << endl;

        //  testCase11();
        //  testCase12();
        testCase14();
        cout << endl;
    }

    //////////////////////////////////////////////////////////////////////
    void testCase13()
    {
        cout << "testCase13" << endl;

        list<int> list1(OBJECT_NUM, 1);

        //  case1, newSize > size()
        list1.resize(2 * OBJECT_NUM, 2);
        print(list1.begin(), list1.end());

        //  case2, newSize < size()
        list1.resize(OBJECT_NUM, 3);
        print(list1.begin(), list1.end());

        cout << endl;
    }

    void testCapacity()
    {
        cout << "testCapacity" << endl;
    
        testCase13();

        cout << endl;
    }
    void test()
    {
        cout << "list_private test" << endl;

   //     testIterator();
   //     testConstruct();
   //     testModifies();
        testOperations();
   //     testCapacity();

        cout << endl;
    }
}

#endif