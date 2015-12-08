/********************************************************************
	Time:	  2015/12/02
	Filename: devec_test
	Author:	  dinglj
	
	Purpose:  
*********************************************************************/
#ifndef _PRIVATE_DEVEC_TEST_H_
#define _PRIVATE_DEVEC_TEST_H_

#include "common_header_files.h"
#include "common_data.h"
#include "../stlite_devec.h"

namespace devec_private
{
    //  test constructor
    void testCase1()
    {
        //  case1
        devec<int> vec1(OBJECT_NUM, 3);
        for (int i = 0; i < OBJECT_NUM; ++i)
        {
            cout << *(vec1.start_of_storage + i) << "\t";
        }
        cout << endl;

        //  case2
        String strArr1[OBJECT_NUM] = {"String0", "String1", "String2", "String3", "String4"};
        devec<String> vec2(strArr1, strArr1 + OBJECT_NUM);
        for (int i = 0; i < OBJECT_NUM; ++i)
        {
            cout << vec2.start_of_storage[i].m_data << "\t";
        }
        cout << endl;
    }

    void testCase3()
    {
        //  stimulate a devec.
        devec<int> vec;
        vec.start_of_storage = NULL;
        vec.end_of_storage = vec.start_of_storage + OBJECT_NUM + 1;    
        vec.start = 4;
        vec.finish = 2;


        cout << vec.capacity() << endl;
        cout << vec.size() << endl;

        cout << endl;
    }

    void testCapacity()
    {
        cout << "testCapacity" << endl;

        testCase3();

        cout << endl;
    }
    //////////////////////////////////////////////////////////////////////
    //  test iterator's constructor
    void testCase2()
    {
        int arr1[OBJECT_NUM] = {0, 1, 2, 3, 4};
        devec<int> vec1(arr1, arr1 + OBJECT_NUM);
        devecIterator<int> it(&vec1, 2);    //  constructor

        cout << *it << endl;

        devec<int>::iterator it2 = vec1.begin();    //  begin
        cout << *it2 << endl;

        cout << endl;
    }

    //  test iterator's ++, --
    void testCase4()
    {
        devec<int> vec1;
        
        //  allocate memory
        vec1.start_of_storage = allocator<int>::allocate(OBJECT_NUM + 1);
        vec1.end_of_storage = vec1.start_of_storage + OBJECT_NUM + 1;
        
        //  assign
        *(vec1.start_of_storage + 0) = 0;
        *(vec1.start_of_storage + 1) = 1;
        *(vec1.start_of_storage + 4) = 2;
        *(vec1.start_of_storage + 5) = 3;

        vec1.start = 4;
        vec1.finish = 2;    //  [0, 1, x, x, 2, 3]

        //  traverse
        devec<int>::iterator it = vec1.begin();
        devec<int>::iterator end = vec1.end();
        for (; it != end; ++it)
        {
            cout << *it << "\t";    //  2 3 0 1
        }
        cout << endl;

        devec<int>::iterator begin = vec1.begin();
        it  = vec1.end();
        for (; it != begin;)
        {
            --it;
            cout << *it << "\t";    //  1 0 3 2
        }
        cout << endl;
    }

    //  test +=, operator -, operator []
    void testCase5()
    {
        devec<int> vec1;

        //  allocate memory
        vec1.start_of_storage = allocator<int>::allocate(OBJECT_NUM + 1);
        vec1.end_of_storage = vec1.start_of_storage + OBJECT_NUM + 1;

        //  assign
        *(vec1.start_of_storage + 0) = 0;
        *(vec1.start_of_storage + 1) = 1;
        *(vec1.start_of_storage + 4) = 2;
        *(vec1.start_of_storage + 5) = 3;

        vec1.start = 4;
        vec1.finish = 2;    //  [0, 1, x, x, 2, 3]

        //  iterator + n
        devec<int>::iterator it;
        it = vec1.begin() + 2;
        cout << *it << endl;    //  0

        //  n + iterator
        devec<int>::iterator it2;
        it2 = 2 + vec1.begin();
        cout << *it2 << endl;   //  0

        //  test iterator1 - iterator2
        int ptrdiff = vec1.end() - vec1.begin();
        cout << ptrdiff << endl;    //  4

        cout << it[2] << endl;      //  0  
    }

    void testIterator()
    {
        cout << "testIterator" << endl;

        //  testCase2();
        //  testCase4();
        testCase5();

        cout << endl;
    }

    //////////////////////////////////////////////////////////////////////
    //  test insert

    //  case1, spaceLeft >= spaceNeed, move forward, insert a random position
    void testCase6()
    {
        String strArr1[OBJECT_NUM] = {"String0", "String1", "String2", "String3", "String4"};

        devec<String> vec1;
        vec1.start_of_storage = allocator<String>::allocate(OBJECT_NUM * 2 + 1); 
        vec1.end_of_storage = vec1.start_of_storage + OBJECT_NUM * 2 + 1;
        
        uninitialized_fill_n(vec1.start_of_storage + 2, OBJECT_NUM, "String");  //  [x,x,S,S,S,S,S,x,x,x,x]
        vec1.start = 2;
        vec1.finish = 7;
        
      
        vec1.insert(vec1.begin() + 2, strArr1, strArr1 + 3);   

        devec<String>::iterator it = vec1.begin();
        devec<String>::iterator end = vec1.end();
        for (; it != end; ++it)
        {
            cout << it->m_data << "\t";     //  [S,0,1,2,S,S,S,x,x,x,S], start = 10, finish = 7.
        }
        cout << endl;
    }

    //  case1_, spaceLeft >= spaceNeed, move forard, objFront > objInsert
    void testCase6_()
    {
        String strArr1[OBJECT_NUM] = {"String0", "String1", "String2", "String3", "String4"};

        devec<String> vec1;
        vec1.start_of_storage = allocator<String>::allocate(OBJECT_NUM * 2 + 1); 
        vec1.end_of_storage = vec1.start_of_storage + OBJECT_NUM * 2 + 1;

        uninitialized_fill_n(vec1.start_of_storage + 2, OBJECT_NUM, "String");  //  [x,x,S,S,S,S,S,x,x,x,x]
        vec1.start = 2;
        vec1.finish = 7;

        vec1.insert(vec1.begin() + 2, strArr1, strArr1 + 1);   

        devec<String>::iterator it = vec1.begin();
        devec<String>::iterator end = vec1.end();
        for (; it != end; ++it)
        {
            cout << it->m_data << "\t";     //  [x, S, S, 0, S, S, S, x,x,x,x], start = 1, finish = 6
        }
        cout << endl;
    }

    //  case2, spaceLeft >= spaceNeed, move forward, insert begin()
    void testCase7()
    {
        String strArr1[OBJECT_NUM] = {"String0", "String1", "String2", "String3", "String4"};

        devec<String> vec1;
        vec1.start_of_storage = allocator<String>::allocate(OBJECT_NUM * 2 + 1); 
        vec1.end_of_storage = vec1.start_of_storage + OBJECT_NUM * 2 + 1;

        uninitialized_fill_n(vec1.start_of_storage + 2, OBJECT_NUM, "String");  //  [x,x,S,S,S,S,S,x,x,x,x]
        vec1.start = 2;
        vec1.finish = 7;


        vec1.insert(vec1.begin(), strArr1, strArr1 + 3);   

        devec<String>::iterator it = vec1.begin();
        devec<String>::iterator end = vec1.end();
        for (; it != end; ++it)
        {
            cout << it->m_data << "\t";     //  [1,2,S,S,S,S,S,x,x,x,0], start = 10, finish = 7.
        }
        cout << endl;
    }

    //  case3, spaceLeft >= spaceNeed, move backward, insert random position
    void testCase8()
    {
        String strArr1[OBJECT_NUM] = {"String0", "String1", "String2", "String3", "String4"};

        devec<String> vec1;
        vec1.start_of_storage = allocator<String>::allocate(OBJECT_NUM * 2 + 1); 
        vec1.end_of_storage = vec1.start_of_storage + OBJECT_NUM * 2 + 1;

        uninitialized_fill_n(vec1.start_of_storage + 4, OBJECT_NUM, "String");  //  [x,x,x,x,S,S,S,S,S,x,x]
        vec1.start = 4;
        vec1.finish = 9;


        vec1.insert(vec1.end() - 2, strArr1, strArr1 + 3);   

        devec<String>::iterator it = vec1.begin();
        devec<String>::iterator end = vec1.end();
        for (; it != end; ++it)
        {
            cout << it->m_data << "\t";     //  [S,x,x,x,S,S,S,0,1,2,S], start = 4, finish = 0.
        }
        cout << endl;
    }

    //  case3_, spaceLeft >= spaceNeed, move backward, objBack >= objInsert, insert random position
    void testCase8_()
    {
        String strArr1[OBJECT_NUM] = {"String0", "String1", "String2", "String3", "String4"};

        devec<String> vec1;
        vec1.start_of_storage = allocator<String>::allocate(OBJECT_NUM * 2 + 1); 
        vec1.end_of_storage = vec1.start_of_storage + OBJECT_NUM * 2 + 1;

        uninitialized_fill_n(vec1.start_of_storage + 4, OBJECT_NUM, "String");  //  [x,x,x,x,S,S,S,S,S,x,x]
        vec1.start = 4;
        vec1.finish = 9;


        vec1.insert(vec1.end() - 2, strArr1, strArr1 + 1);   

        devec<String>::iterator it = vec1.begin();
        devec<String>::iterator end = vec1.end();
        for (; it != end; ++it)
        {
            cout << it->m_data << "\t";     //  [x,x,x,x,S,S,S,0,S,S,x], start = 5, finish = 10.
        }
        cout << endl;
    }
    //  case4, spaceLeft >= spaceNeed, move backward, insert end() position
    void testCase9()
    {
        String strArr1[OBJECT_NUM] = {"String0", "String1", "String2", "String3", "String4"};

        devec<String> vec1;
        vec1.start_of_storage = allocator<String>::allocate(2 * OBJECT_NUM + 1);
        vec1.end_of_storage = vec1.start_of_storage + 2 * OBJECT_NUM + 1;

        uninitialized_fill_n(vec1.start_of_storage + 4, OBJECT_NUM, "String");  //  [x,x,x,x,S,S,S,S,S,x,x]
        vec1.start = 4;
        vec1.finish = 4 + OBJECT_NUM;

        vec1.insert(vec1.end(), strArr1, strArr1 + 3);

        devec<String>::iterator it = vec1.begin();
        devec<String>::iterator end = vec1.end();
        for (; it != end; ++it)
        {
            cout << it->m_data << "\t";     //  [2,x,x,x,S,S,S,S,S,0,1], start = 4, finish = 0
        }
        cout << endl;
    }

    //  case5, spaceLeft < spaceNeed
    void testCase10()
    {
        String strArr1[OBJECT_NUM] = {"String0", "String1", "String2", "String3", "String4"};

        devec<String> vec1;
        vec1.start_of_storage = allocator<String>::allocate(7);
        vec1.end_of_storage = vec1.start_of_storage + 7;

        uninitialized_fill_n(vec1.start_of_storage + 1, OBJECT_NUM, "String");  //  [x,S,S,S,S,S,x]
        vec1.start = 1;
        vec1.finish = vec1.start + OBJECT_NUM;

        vec1.insert(vec1.begin() + 2, strArr1, strArr1 + 4);

        devec<String>::iterator it = vec1.begin();
        devec<String>::iterator end = vec1.end();
        for (; it != end; ++it)
        {
            cout << it->m_data << "\t";     //  [S,S,0,1,2,3,S,S,S,x,x], start = 0, finish = 9.
        }
        cout << endl;

    }

    void testInsert()
    {
        cout << "testInsert" << endl;

        //  testCase6();
        //  testCase6_();
        //  testCase7();
        //  testCase8();
        //  testCase8_();
        //  testCase9();
        //  testCase10();

        cout << endl;
    }

    void testModifiers()
    {
        cout << "testModifiers" << endl;

        testInsert();

        cout << endl;
    }

    void test()
    {
        cout << "devec_private test" << endl;

        //  testCase1();
        //  testIterator();
        //  testCapacity();
        testModifiers();

        cout << endl;
    }
}

#endif
