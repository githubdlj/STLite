/********************************************************************
	Time:	  2015/11/04
	Filename: base_test
	Author:	  dinglj
	
	Purpose:  test the fundamental knowledge
*********************************************************************/
#ifndef _PRIVATE_BASE_TEST_H_
#define _PRIVATE_BASE_TEST_H_

#include "common_data.h"
#include "common_header_files.h"

//////////////////////////////////////////////////////////////////////
namespace base_private
{
    //  ++prefix, postfix++
    //  ++prefix returns a value_type &, postfix++ returns a value_type(a temp object)
    void testCase1()
    {
        cout << "testCase1" << endl;

        int num1 = 1;
        //  num1++ = 10;     //  postfix++ can not be a left value
        cout << num1 << endl;

        int num2 = 1;      
        ++num2 = 10;    
        cout << num2 << endl;   //  10

        int num = 3;
        int prefix = ++num;
        cout << prefix << endl;     //  4

        num = 3;
        int post = num++;       //  3
        cout << post << endl;

        cout << endl;
    }

    //  test operator *()
    void testCase2()
    {
        cout << "testCase2" << endl;

        int *p = new int(10);
        cout << *p << endl;

        int num = 5;
        num = *p;
        cout << num << endl;

        num = 6;
        *p = num;
        cout << *p << endl;

        cout << endl;
    }

    void testOperator()
    {
        cout << "testOperator" << endl;

        testCase1();
        testCase2();

        cout << endl;
    }
    //////////////////////////////////////////////////////////////////////
  
    void fun1(Widget)   //  call copy 
    {

    }

    void fun2(const Widget &)   //  do not call copy
    {

    }

    Widget fun3()   //  call copy when return 
    {
        Widget w;
        return w;
    }

//     Widget & fun4()     // do not call copy
//     {
//         return *this;
//     }

    void testConstructor()
    {
        cout << "testConstructor" << endl;

        Widget w;
        fun1(w);
        fun2(w);
        fun3();
        //   fun4();

        cout << endl;
    }

    //////////////////////////////////////////////////////////////////////
    void swap0(int *p, int *q)
    {
        int temp = *p;
        *p = *q;
        *q = temp;
    }

    void swap1(int &p, int &q)
    {
        int temp = p;
        p = q;
        q = temp;
    }

    void swap2(int * &p, int * &q)
    {
        int *temp = p;
        p = q;
        q = temp;
    }

    void swap3(int * &p, int * &q)
    {
        int temp = *p;
        *p = *q;
        *q = temp;
    }

    void swap4(int **p, int **q)
    {
        int *temp = *p;
        *p = *q;
        *q = temp;
    }

    void swap5(int **p, int **q)
    {
        int temp = **p;
        **p = **q;
        **q = temp;
    }

    void testCase3()
    {
        cout << "testCase3" << endl;
        int a = 3;
        int b = 4;

        //  all the swap can work right
        swap0(&a, &b);
        swap1(a, b);

        cout << a << endl;     
        cout << b << endl;
    }

    void testCase4()
    {
        cout << "testCase4" << endl;

        int a = 3;
        int b = 4;
        int *p = &a;
        int *q = &b;

        //  all the swap can work right
        swap2(p, q);
        swap3(p, q);

        swap4(&p, &q);
        swap5(&p, &q);

        cout << endl;
    }

    void testSwap()
    {
        cout << "testSwap" << endl;

        testCase3();
        testCase4();

        cout << endl;
    }

    //////////////////////////////////////////////////////////////////////
    //  test friend class
    class Container;
   
    class ContainerIterator
    {
    public:
        void showContainerSize(const Container &c) const;
//         {
//         //    cout << c.size() << endl;  //  it should NOT define here.
//         //    cout << c.m_size << endl;
//         }
    };
  
    class Container
    {
    public:
        friend class ContainerIterator;
    private:
        int m_size;

    public:
        Container(int size = 0) : m_size(size){}
        int size() const
        {
            return m_size;
        }
        
//         void showSize()
//         {
//             ContainerIterator it;
//             it.showContainerSize(*this);
//         }
    };

    void ContainerIterator::showContainerSize(const Container &c) const     //  define
    {
        cout << c.size() << endl;
        cout << c.m_size << endl;
    }

    void testCase5()
    {
        Container c(10);
        ContainerIterator it;
        it.showContainerSize(c);
    //    c.showSize();
    }

    //////////////////////////////////////////////////////////////////////
    template<class T>
    class Widget_
    {
    private:
        static int index;
    public:
        static void addIndex()
        {
            ++index;
        }

        static void showIndex();
    private:
        union Slot_ 
        {
            int element;
            Slot_* next;
        };
    public:
        typedef Slot_ * slot_pointer;
    public:
        static slot_pointer pointer;
    };

    //  init the static variables
    template<class T>
    int Widget<T>::index = 0;

    template<class T>
    typename Widget<T>::slot_pointer Widget<T>::pointer = 0;

    //  define  static function
    template<class T>
    void Widget_<T>::showIndex()
    {
        cout << index << endl;
    }

    //  test static variables. 
    //  test how to define a function outside the class.
    void testCase6()
    {
        //  int
        Widget_<int>::showIndex();      //  0
        Widget_<int>::addIndex();       //  1
        Widget_<int>::addIndex();       //  2
        Widget_<int>::showIndex();      //  2

        //
        Widget_<double>::showIndex();   //  0
        Widget_<double>::addIndex();    //  1
        Widget_<double>::addIndex();    //  2
        Widget_<double>::showIndex();   //  2

        // 
        Widget_<int>::addIndex();       //  3
        Widget_<int>::showIndex();      //  3
        //     Widget_<int>::index++;   //  error, can not access private member
        //     Widget_<int>::showIndex();
        cout << Widget_<int>::pointer << endl;  //  00000000
    }

    //////////////////////////////////////////////////////////////////////
    void testCase7_()
    {
        union slot1
        {
            char c[10];
            int i;
        };

        union slot2
        {
            slot2 *next;
            long long l;
        };

        cout << sizeof(slot1) << endl;      //  12, 4 * 3
        cout << sizeof(slot2) << endl;      //  8
    }


    //  test malloc
    //  what means malloc??
    struct Node
    {
        int a;
        double b;
    };

    void testCase7()
    {
        Node *pNode = (Node *)malloc(sizeof(Node));     //  malloc memory
        cout << pNode << endl;
        cout << &(pNode->a) << endl;
        cout << &(pNode->b) << endl;                    //  sizeof(double) 8
        ++pNode;                                        //  ++pNode
        cout << pNode << endl;                          

        pNode->a = 0;                                   //  access the next Node
        pNode->b = 1;

        cout << pNode->a << endl;
        cout << pNode->b << endl;

        --pNode;
        cout << pNode << endl;
        free(pNode);                                    //  error
    }

    void testCase8()
    {
        double *data = (double *)malloc(sizeof(double) * 12);
        cout << data << endl;

        data++;
        free(data);     //  error
    }

    void testCase9()
    {
        int *data = (int *)malloc(sizeof(int));
        cout << data;

        double *ptr = (double *)data;
        *ptr = 0;                           //  1) access invalid memory
        cout << ptr << endl;
        cout << *ptr << endl;

        free(ptr);                          //  2) if 1) happen, it will error!
    }

    void testMalloc()
    {
        cout << "testMalloc" << endl;

        testCase7();
        testCase8();
        testCase9();

        cout << endl;
    }
    //////////////////////////////////////////////////////////////////////
    void test()
    {
        cout << "base_private test" << endl;
        
        //  testOperator();
        //  testConstructor();
        testCase5();
        cout << endl;
    }
}

#endif