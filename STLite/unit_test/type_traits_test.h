/********************************************************************
	Time:	  2015/10/21
	Filename: type_traits_test
	Author:	  dinglj
	
	Purpose:  ≤‚ ‘type_traits
*********************************************************************/
#ifndef _PUBLIC_TYPE_TRAITS_TEST_H_
#define _PUBLIC_TYPE_TRAITS_TEST_H_

#include "common_header_files.h"
#include "common_data.h"
#include "../stlite_type_traits.h"

//////////////////////////////////////////////////////////////////////
namespace type_traites_public
{
    void print_aux(__true_type)
    {
        cout << "true" << endl;
    }

    void print_aux(__false_type)
    {
        cout << "false" << endl;
    }

    template<class T>
    void print_attr(T)
    {
        typedef typename __type_traits<T>::is_POD_type is_POD_type;

        cout << typeid(T).name() << ": ";
        print_aux(is_POD_type());
    }

    template<class T>
    void print_type(T)
    {
        typedef typename _is_integer<T>::is_integer is_integer;

        cout << typeid(T).name() << ": ";
        print_aux(is_integer());
    }

    //////////////////////////////////////////////////////////////////////
    //  test attribute
    void testCase1()
    {
        cout << "testCase1" << endl;

        int a = 0;
        print_attr(a);

        bool b = true;
        print_attr(b);

        cout << endl;
    }

    void testCase2()
    {
        cout << "testCase2" << endl;

        int *pi = NULL;
        print_attr(pi);

        char *pc1 = NULL;
        print_attr(pc1);

        unsigned char *pc2 = NULL;
        print_attr(pc2);

        const char *pc3 = NULL;
        print_attr(pc3);

        cout << endl;
    }

    void testCase3()
    {
        cout << "testCase3" << endl;

        Widget w;
        print_attr(w);

        cout << endl;
    }

    void testAttr()
    {
        cout << "trestAttr" << endl;

        testCase1();
        testCase2();
        testCase3();

        cout << endl;
    }

    //////////////////////////////////////////////////////////////////////
    //  test type
    void testCase4()
    {
        cout << "testCase4" << endl;

        int intType = 0;
        print_type(intType);

        cout << endl;
    }

    void testCase5()
    {
        cout << "testCase5" << endl;

        int *ptr = NULL;
        print_type(ptr);

        cout << endl;
    }

    void testCase6()
    {
        cout << "testCase6" << endl;

        Widget w;
        print_type(w);
       
        cout << endl;
    }

    void testType()
    {
        cout << "testType" << endl;

        testCase4();
        testCase5();
        testCase6();
    
        cout << endl;
    }

    //////////////////////////////////////////////////////////////////////
    void test()
    {
        cout << "type_traits_public test" << endl;

        testAttr();
        testType();

        cout << endl;
    }

}
#endif