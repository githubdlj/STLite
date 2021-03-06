/********************************************************************
	Time:	  2015/11/04
	Filename: common_data
	Author:	  dinglj
	
	Purpose:  Include some common data that the files need in public_test
*********************************************************************/
#ifndef _PUBLIC_COMMON_DATA_H_
#define _PUBLIC_COMMON_DATA_H_

#include <string.h>     //  for strlen
#include "common_header_files.h"

//////////////////////////////////////////////////////////////////////

namespace public_data
{

//  common data
class Widget
{
public:
    //   explicit Widget(int value = 0)
    Widget(int value = 0)
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

//////////////////////////////////////////////////////////////////////
//  String has a pointer  
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

    //  
    friend std::ostream & operator <<(std::ostream &os, const String &s);
public:
    char *m_data;
};

std::ostream & operator <<(std::ostream &os, const String &s)
{
    os << s.m_data;
    return os;
}
//////////////////////////////////////////////////////////////////////

const int OBJECT_NUM = 5;

}

using namespace public_data;
#endif