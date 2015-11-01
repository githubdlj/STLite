/********************************************************************
	Time:	  2015/10/31
	Filename: iterator_test
	Author:	  dinglj
	
	Purpose:  ²âÊÔµü´úÆ÷¹¦ÄÜ
*********************************************************************/
#ifndef _ITERATOR_
#define _ITERATOR_

#include <iostream>
#include <iterator>
#include <vector>
#include <list>
#include "../stlite_uninitialized.h"


namespace iterator_private_unit
{
    //////////////////////////////////////////////////////////////////////
    //  test vector.insert()
    void testCase1()
    {
        typedef std::vector<int>    vec;
        typedef std::list<int>      list;

        list l(4,4);
        list::iterator iter = l.begin();
        list::iterator end = l.end();
        
        typedef std::iterator_traits<list::iterator> traits;
        cout << typeid(traits::iterator_category).name() << endl;       //  struct std::bidirectional_iterator_tag
        for (; iter != end; ++iter)
        {
            cout << *iter;      //  4444
        }
        cout << endl;

        vec v;
        v.insert(v.begin(), l.begin(), l.end());    //  insert,
        
        int size = v.size();
        for (int i = 0; i < size; i++)
        {
            cout << v[i];
        }
        cout << endl;
    }

    void testCase2()
    {
        typedef std::vector<int>    vec;
        typedef std::list<int>      list;

        vec v(3,1);
        list l(3, 2);

        STLite::uninitialized_copy(l.begin(), l.end(), v.begin());

        int vsize = v.size();
        for (int i = 0; i < vsize; i++)
        {
            cout << v[i];       //  222
        }
        cout << endl;
    }
    void test()
    {
        cout << "iterator_private_unit" << endl;
        testCase1();
    //    testCase2();
    }
}

#endif