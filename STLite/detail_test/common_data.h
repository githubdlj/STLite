/********************************************************************
	Time:	  2015/11/04
	Filename: common_data
	Author:	  dinglj
	
	Purpose:  Include some common data that the files need in private_test
*********************************************************************/
#ifndef _PRIVATE_COMMON_DATA_H_
#define _PRIVATE_COMMON_DATA_H_

#include <string.h>     //  for strlen

#include "common_header_files.h"

//////////////////////////////////////////////////////////////////////
namespace private_data
{
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
    public:
        char *m_data;

    };
    //////////////////////////////////////////////////////////////////////

    const int OBJECT_NUM = 5;

    }

using namespace private_data;
#endif