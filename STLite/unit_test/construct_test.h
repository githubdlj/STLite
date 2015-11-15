/********************************************************************
	Time:	  2015/10/22
	Filename: construct_test
	Author:	  dinglj
	
	Purpose:  test constructor
*********************************************************************/
#ifndef _PUBLIC_CONSTRUCT_TEST_H_
#define _PUBLIC_CONSTRUCT_TEST_H_

#include "common_header_files.h"
#include "common_data.h"
#include "../stlite_construct.h"

//////////////////////////////////////////////////////////////////////
namespace construct_public
{
    void testCase1()
    {
        cout << "testCase1" << endl;

        //  allocate memory
        //  operator new only allocate memory.
        //  new allocate memory and construct object.
        int *p = (int *) ::operator new(sizeof(int) * OBJECT_NUM);
  
        //  construct
        for (int i = 0; i < OBJECT_NUM; ++i)
        {
            construct(p + i, i);    
        }
   
        for (int i = 0; i < OBJECT_NUM; ++i)
        {
            cout << p[i] << endl;   //  0 1 2 3 4 
        }

        //  destructor the objects
        destroy(p, p + OBJECT_NUM);     //  call destroy_aux(first, last, __true_type) ==> do nothing

        //  free memory
        //  operator delete has 2 version
        //  operator delete(pointer *p), operator delete(pointer *p, size)
        ::operator delete(p);   
    
        cout << endl;
    }

    void testCase2()
    {
        cout << "testCase2" << endl;

        int arr[OBJECT_NUM];

        for (int i = 0; i < OBJECT_NUM; ++i)
        {
            construct(arr + i, i);
        }

        for (int i = 0; i < OBJECT_NUM; ++i)
        {
            cout << arr[i] << endl;
        }

        destroy(arr, arr + OBJECT_NUM);  //  call destroy_aux(first, last, __true_type) ==> do nothing
       
        cout << endl;
    }

    void testCase3()
    {
        cout << "testCase3" << endl;
       
        //  alloc memory
        Widget *w = (Widget *) ::operator new(sizeof(w) * OBJECT_NUM);
      
        //  construct
        for (int i = 0; i < OBJECT_NUM; ++i)
        {
            construct(w + i, i);    //  call w[i]'s constructor
        }

        for (int i = 0; i < OBJECT_NUM; ++i)
        {
            cout << w[i].m_value << endl;
        }

        //  destroy
        destroy(w, w + OBJECT_NUM);     //  call destroy_aux(first, last, __false_type) ==> call p[i]'s deconstructor

        //  free memory
        ::operator delete(w);

        cout << endl;
    }


    void testCase4()
    {
        cout << "testCase4" << endl;

        String *s = (String *) ::operator new(sizeof(String) * OBJECT_NUM);
        for (int i = 0; i < OBJECT_NUM; ++i)
        {
            construct(s + i, "a");
        }

        for (int i = 0; i < OBJECT_NUM; ++i)
        {
            cout << s[i].m_data << endl;
        }

        destroy(s, s + OBJECT_NUM);

        ::operator delete(s);

        cout << endl;
    }

    //////////////////////////////////////////////////////////////////////
    void test()
    {
        cout << "construct_public test" << endl;
    
        testCase1();
        testCase2();
        testCase3();
        testCase4();

        cout << endl;
    }
}
#endif