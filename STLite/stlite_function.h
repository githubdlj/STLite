/********************************************************************
	Time:	  2015/11/25
	Filename: stlite_function
	Author:	  dinglj
	
	Purpose:  functional
*********************************************************************/

#ifndef _STLITE_FUNCTION_H_
#define _STLITE_FUNCTION_H_

//////////////////////////////////////////////////////////////////////
namespace STLite
{
    //  binary function
    template<class Arg1, class Arg2, class Result>
    struct binary_function
    {
        typedef Arg1 arg1;
        typedef Arg2 arg2;
        typedef Result result;
    };

    template<class T>
    struct less : public binary_function<T, T, bool>
    {
        result operator ()(const arg1 &x, const arg2 &y)
        {
            return x < y;
        }
    };

    template<class T>
    struct greater : binary_function<T, T, bool>
    {
        result operator ()(const arg1 &x, const arg2 &y)
        {
            return x > y;
        }
    };

    template<class T>
    struct equal_to : binary_function<T, T, bool>
    {
        result operator ()(const arg1 &x, const arg2 &y)
        {
            return x == y;
        }
    };

    template<class T>
    struct not_equal_to : binary_function<T, T, bool>
    {
        result operator() (const arg1 &x, const arg2 &y)
        {
            return x != y;
        }
    };
}

#endif