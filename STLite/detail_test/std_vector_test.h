/********************************************************************
	Time:	  2015/10/31
	Filename: std_vector_test
	Author:	  dinglj
	
	Purpose:  test the std::vector
*********************************************************************/
#ifndef _PRIVATE_STD_VECTOR_TEST_H_
#define _PRIVATE_STD_VECTOR_TEST_H_

#include <iterator>
#include <vector>
#include <list>

#include "common_header_files.h"
#include "common_data.h"
#include "../stlite_uninitialized.h"
#include "../stlite_algorithm.h"

//////////////////////////////////////////////////////////////////////
namespace std_vector_private
{
    //  test std::vector.insert()
    void testCase1()
    {
        cout << "testCase1" << endl;

        typedef std::vector<int>    vec;
        typedef std::list<int>      list;

        list l(4,4);
        list::iterator iter = l.begin();
        list::iterator end = l.end();
        
        typedef std::iterator_traits<list::iterator> traits;
        cout << typeid(traits::iterator_category).name() << endl;       //  struct std::bidirectional_iterator_tag
        for (; iter != end; ++iter)
        {
            cout << *iter << "\t";      //  4 4 4 4
        }
        cout << endl;

        vec v;
        v.insert(v.begin(), l.begin(), l.end());    //  insert(vector iterator, list iterator, list iterator)
        
        int size = v.size();
        for (int i = 0; i < size; ++i)
        {
            cout << v[i] << "\t";       //  4 4 4 4
        }
        cout << endl;
    }

    //  test uninitialized_copy 
    void testCase2()
    {
        cout << "testCase2" << endl;

        typedef std::vector<int>    vec;
        typedef std::list<int>      list;

        vec v(3,1);
        list l(3, 2);

    //    STLite::uninitialized_copy(l.begin(), l.end(), v.begin());    //  error, it should call STLite::copy
        std::copy(l.begin(), l.end(), v.begin());

        int vsize = v.size();
        for (int i = 0; i < vsize; ++i)
        {
            cout << v[i] << "\t";       //  222
        }
        cout << endl;
    }

    //  test range insert 
    void testCase3()
    {
        cout << "testCase3" << endl;

        typedef std::vector<int> iVec;
        iVec v(2, 1);

        v.insert(v.end() + 1, 2, 2);    //  error, valid range is [v.begin(), v.end()]
        cout << endl;
    }

    //  test clear
    void testCase4()
    {
        cout << "testCase4" << endl;

        typedef std::vector<int> iVec;
        iVec v(2, 1);

        v.clear();

        cout << v.size() << endl;

        for (int i = 0; i < 2; ++i)
        {
            cout << v[i] << "\t";   //  1, 1, clear only destroy the elements, not destroy the space 
                                    //  but the VC report error, because out of index.
                                    //  we should not access the elements, because they are destructed.
        }
        cout << endl;
    }


    //  test assgin
    //  assgin(n, value)
    void testCase5()
    {   
        std::vector<int> v;
        v.assign(OBJECT_NUM, 1);

        int size = v.size();
        for (int i = 0; i < size; ++i)
        {
            cout << v[i] << "\t";   //  1 1 1 1 1
        }
        cout << endl;

        v.assign(2, 2);
        size = v.size();
        for (int i = 0; i < size; ++i)
        {
            cout << v[i] << "\t";   // 2 2
        }
        cout << endl;
    }
    //////////////////////////////////////////////////////////////////////
    void test()
    {
        cout << "std_vector_private test" << endl;
       
   //     testCase1();
   //     testCase2();
   //     testCase3();
   //     testCase4();
        testCase5();

        cout << endl;
    }
}

#endif