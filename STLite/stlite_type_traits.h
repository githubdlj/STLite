/********************************************************************
	Time:	  2015/10/21
	Filename: type_traits
	Author:	  dinglj
	
    Purpose:  1. type_traits, it can get the ATTRIBUTION(attribution) of the data type
              for example, distinguish whether the data type has CONSTRUCTOR,COPY CONSTRUCTOR, ASSINGMENT, DECONSTRUCTOR or POD_TYPE.
              the override function can call the corresponding version according to the attribution. 

              2. distinguish the data type(int? pointer? iterator?), now, I can distinguish whether the data type is integer.
*********************************************************************/

#ifndef _TYPE_TRAITS_H_
#define _TYPE_TRAITS_H_

#include "commom_header_files.h"

//////////////////////////////////////////////////////////////////////
namespace STLite
{ 
    struct __true_type{};
    struct __false_type{};
    //////////////////////////////////////////////////////////////////////

    //  generalization
    template<class T>
    struct __type_traits
    {
        typedef __true_type this_dummy_must_be_first;
         /* Do not remove this member. It informs a compiler which
            automatically specializes __type_traits that this
            __type_traits template is special. It just makes sure that
            things work if an implementation is using a template
            called __type_traits for something unrelated. */
        
        typedef __false_type has_trivial_default_constructor;
        typedef __false_type has_trivial_copy_constructor;
        typedef __false_type has_trivial_assignment_operator;
        typedef __false_type has_trivial_deconstructor;
        typedef __false_type is_POD_type;
    };
    //////////////////////////////////////////////////////////////////////

    //  specialization
    //  bool, char, signed char, unsigned char, short, unsigned short, int, unsigned int,
    //  long, unsigned long, float, double, pointer
    
    //  bool
    template<>
    struct __type_traits<bool>
    {
        typedef __true_type has_trivial_default_constructor;
        typedef __true_type has_trivial_copy_constructor;
        typedef __true_type has_trivial_assignment_operator;
        typedef __true_type has_trivial_deconstructor;
        typedef __true_type is_POD_type;
    };

    //////////////////////////////////////////////////////////////////////
    //  char
   
    template<>
    struct __type_traits<char>
    {
        typedef __true_type has_trivial_default_constructor;
        typedef __true_type has_trivial_copy_constructor;
        typedef __true_type has_trivial_assignment_operator;
        typedef __true_type has_trivial_deconstructor;
        typedef __true_type is_POD_type;
    };

    template<>
    struct __type_traits<signed char>
    {
        typedef __true_type has_trivial_default_constructor;
        typedef __true_type has_trivial_copy_constructor;
        typedef __true_type has_trivial_assignment_operator;
        typedef __true_type has_trivial_deconstructor;
        typedef __true_type is_POD_type;
    };

    template<>
    struct __type_traits<unsigned char>
    {
        typedef __true_type has_trivial_default_constructor;
        typedef __true_type has_trivial_copy_constructor;
        typedef __true_type has_trivial_assignment_operator;
        typedef __true_type has_trivial_deconstructor;
        typedef __true_type is_POD_type;
    };
    
    //////////////////////////////////////////////////////////////////////
    //  short
    template<>
    struct __type_traits<short>
    {
        typedef __true_type has_trivial_default_constructor;
        typedef __true_type has_trivial_copy_constructor;
        typedef __true_type has_trivial_assignment_operator;
        typedef __true_type has_trivial_deconstructor;
        typedef __true_type is_POD_type;
    };

    template<>
    struct __type_traits<unsigned short>
    {
        typedef __true_type has_trivial_default_constructor;
        typedef __true_type has_trivial_copy_constructor;
        typedef __true_type has_trivial_assignment_operator;
        typedef __true_type has_trivial_deconstructor;
        typedef __true_type is_POD_type;
    };
    //////////////////////////////////////////////////////////////////////
    //  int
    template<>
    struct __type_traits<int>
    {
        typedef __true_type has_trivial_default_constructor;
        typedef __true_type has_trivial_copy_constructor;
        typedef __true_type has_trivial_assignment_operator;
        typedef __true_type has_trivial_deconstructor;
        typedef __true_type is_POD_type;
    };

    template<>
    struct __type_traits<unsigned int>
    {
        typedef __true_type has_trivial_default_constructor;
        typedef __true_type has_trivial_copy_constructor;
        typedef __true_type has_trivial_assignment_operator;
        typedef __true_type has_trivial_deconstructor;
        typedef __true_type is_POD_type;
    };

    //////////////////////////////////////////////////////////////////////
    //  long
    template<>
    struct __type_traits<long>
    {
        typedef __true_type has_trivial_default_constructor;
        typedef __true_type has_trivial_copy_constructor;
        typedef __true_type has_trivial_assignment_operator;
        typedef __true_type has_trivial_deconstructor;
        typedef __true_type is_POD_type;
    };

    template<>
    struct __type_traits<unsigned long>
    {
        typedef __true_type has_trivial_default_constructor;
        typedef __true_type has_trivial_copy_constructor;
        typedef __true_type has_trivial_assignment_operator;
        typedef __true_type has_trivial_deconstructor;
        typedef __true_type is_POD_type;
    };

    //////////////////////////////////////////////////////////////////////
    //  float
    template<>
    struct __type_traits<float>
    {
        typedef __true_type has_trivial_default_constructor;
        typedef __true_type has_trivial_copy_constructor;
        typedef __true_type has_trivial_assignment_operator;
        typedef __true_type has_trivial_deconstructor;
        typedef __true_type is_POD_type;
    };

    //////////////////////////////////////////////////////////////////////
    //  double
    template<>
    struct __type_traits<double>
    {
        typedef __true_type has_trivial_default_constructor;
        typedef __true_type has_trivial_copy_constructor;
        typedef __true_type has_trivial_assignment_operator;
        typedef __true_type has_trivial_deconstructor;
        typedef __true_type is_POD_type;
    };

    //////////////////////////////////////////////////////////////////////
    //  pointer
    template<class T>
    struct __type_traits<T*>
    {
        typedef __true_type has_trivial_default_constructor;
        typedef __true_type has_trivial_copy_constructor;
        typedef __true_type has_trivial_assignment_operator;
        typedef __true_type has_trivial_deconstructor;
        typedef __true_type is_POD_type;
    };

    //////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////
    //  data_type
    //  The following could be written in terms of numeric_limits.  
    //  We're doing it separately to reduce the number of dependencies.
    template<class T>
    struct _is_integer
    {
        typedef __false_type is_integer;
    };
    
    //////////////////////////////////////////////////////////////////////
    //  integer
    //  bool, char, short, int, long are INT type
    template<>
    struct _is_integer<bool>
    {
        typedef __true_type is_integer;
    };
        
    template<>
    struct _is_integer<char>
    {
        typedef __true_type is_integer;
    };
    
    template<>
    struct _is_integer<signed char>
    {
        typedef __true_type is_integer;
    };
        
    template<>
    struct _is_integer<unsigned char>
    {
        typedef __true_type is_integer;
    };
        
    template<>
    struct _is_integer<short>
    {
        typedef __true_type is_integer;
    };
        
    template<>
    struct _is_integer<unsigned short>
    {
        typedef __true_type is_integer;
    };
        
    template<>
    struct _is_integer<int>
    {
        typedef __true_type is_integer;
    };
        
    template<>
    struct _is_integer<unsigned int>
    {
        typedef __true_type is_integer;
    };
    
    template<>
    struct _is_integer<long>
    {
        typedef __true_type is_integer;
    };
    
    template<>
    struct _is_integer<unsigned long>
    {
        typedef __true_type is_integer;
    };

}

#endif