/********************************************************************
	Time:	  2015/11/02
	Filename: private_test
	Author:	  dinglj
	
	Purpose:  include some common header files and data
*********************************************************************/
#ifndef _PRIVATE_TEST_H_
#define _PRIVATE_TEST_H_

//////////////////////////////////////////////////////////////////////
//  common header files
#include <iostream>
using std::cout;
using std::cin;
using std::endl;

//////////////////////////////////////////////////////////////////////
//  common data
class Widget
{
public:
    explicit Widget(int value = 0)
    {
        cout << "constructor" << endl;
        m_value = value;
    }

    Widget(const Widget &lhs)
    {
        cout << "copy constructor" << endl;
        m_value = lhs.m_value;
    }

    Widget & operator =(const Widget &lhs)
    {
        cout << "assignment" << endl;
        m_value = lhs.m_value;
        return *this;
    }

    ~Widget( )
    {
        cout << "destroy" << endl;
    }

//////////////////////////////////////////////////////////////////////
public:
    int m_value;

};

//  
class String
{
public:
    //  constructor
    String(const char *data = NULL)
    {
        cout << "constructor" << endl;
        if (NULL == data)
        {
            m_data = new char[1];
            m_data[0] = '\0';       
        }
        else
        {
            int len = strlen(data);
            m_data =  new char[len + 1];
            strcpy(m_data, data);
        }
    }

    //  copy
    String(const String &lhs)
    {
        cout << "copy" << endl;
        int len = strlen(lhs.m_data);
        m_data = new char[len + 1];
        strcpy(m_data, lhs.m_data);
    }

    //  assign
    String & operator =(const String &lhs)
    {
        cout << "assign" << endl;
        int len = strlen(lhs.m_data);
        char *temp = new char[len + 1];
        strcpy(temp, lhs.m_data);
        
        delete []m_data;
        m_data = temp;
        return *this;
    }
    //  destroy
    ~String()
    {
        cout << "destroy" << endl;
        delete []m_data;
    }
//////////////////////////////////////////////////////////////////////
public:
    char *m_data;

};
//////////////////////////////////////////////////////////////////////

const int MY_OBJECT_NUM = 5;

#endif
