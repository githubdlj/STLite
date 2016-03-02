/********************************************************************
	Time:	  2015/10/22
	Filename: alloc_test
	Author:	  dinglj
	
	Purpose:  test allocator
*********************************************************************/
#ifndef _PUBLIC_ALLOC_TEST_H_
#define _PUBLIC_ALLOC_TEST_H_

#include <vector>
#include <list>
#include <time.h>

#include "common_header_files.h"
#include "common_data.h"
#include "../stlite_alloc.h"
#include "../stlite_algorithm.h"

#include "../stlite_list.h"
//////////////////////////////////////////////////////////////////////
namespace alloc_public
{
    //  alloc, constructor, destroy elements, destroy space
    void testCase1()
    {
        cout << "testCase1" << endl;

        allocator<int> alloc;

        //  alloc memory
        int *ptr = alloc.allocate(OBJECT_NUM);

        //  construct
        for (int i = 0; i < OBJECT_NUM; ++i)
        {
            alloc.construct(ptr + i, i);    
        }

        //  print
        for (int i = 0; i < OBJECT_NUM; ++i)
        {
            cout << ptr[i] << "\t";
        }
        cout << endl;

        //////////////////////////////////////////////////////////////////////
        //  destroy, destroy has 2 version, 
        //  version 1, has a higher performance
        alloc.destroy(ptr, ptr + OBJECT_NUM); 

        //  version 2
    //     for (int i = 0; i < OBJECT_NUM; ++i)
    //     {
    //         alloc.destroy(ptr + i);     
    //                                    
    //     }

        //  deallocate
        alloc.deallocate(ptr, OBJECT_NUM);

        cout << endl;
    }

    //  
    void testCase2()
    {
        cout << "testCase2" << endl; 

        int arr[OBJECT_NUM];
        for (int i = 0; i < OBJECT_NUM; ++i)
        {
            arr[i] = i;
        }
       
        //  it calls 2 times constructor 
        //  the first one allocate 8 byte, the second allocate OBJECT_NUM * sizof(int) byte
        //  debug it, I find that the first allocate returns std::_Container_proxy *
        std::vector< int, STLite::allocator<int> > v(arr, arr + OBJECT_NUM);

        for (int i = 0; i < OBJECT_NUM; ++i)
        {
            cout << v[i] << "\t";
        }
        cout << endl;
    }

    //  test allocator on list
    void testCase3()
    {
        String strArr1[OBJECT_NUM] = {"String0", "String1", "String2", "String3", "String4"};
        std::list<String, STLite::allocator<String> > list1;
       
        for (int i = 0; i < OBJECT_NUM; ++i)
        {
            list1.push_back(strArr1[i]);
        }

        for (int i = 0; i < OBJECT_NUM; ++i)
        {
            cout << list1.back() << "\t";
            list1.pop_back();
        }
        cout << endl;
    }

    //////////////////////////////////////////////////////////////////////
    //  test MemoryPool
   
    void testCase5()
    {
        cout << sizeof(long long) << endl;          //  8
        //  MemoryPool<int>::allocateBlock();
        //  MemoryPool<long long>::allocateBlock();
    }

    //  test for int
    void testCase6()
    {
        int *ptr = NULL;
        for (int i = 0; i < OBJECT_NUM; ++i)
        {
            ptr = MemoryPool<int>::allocate(0);     
            *ptr = i;

            cout << ptr << endl;
            cout << *ptr << endl;   //  [0 5)
        }

        MemoryPool<int>::destroyMemoryPool();

        cout << endl;
    }

    //  test for long long
    void testCase7()
    {
        long long *ptr = NULL;
        for (int i = 0; i < OBJECT_NUM; ++i)
        {
            ptr = MemoryPool<long long>::allocate(0);   //  MemoryPool<int, 21(4 + 8 + 8 + 1)>
            *ptr = i;

            cout << ptr << endl;
            cout << *ptr << endl;   //  
        }

        MemoryPool<long long>::destroyMemoryPool();
        cout << endl;
    }

    //  test for String
    void testCase8()
    {
        String *ptr = NULL;
        for (int i = 0; i < OBJECT_NUM; ++i)
        {
            ptr = MemoryPool<String>::allocate(0);
            construct(ptr, "String");

            cout << ptr << endl;
            cout << *ptr << endl;
        }

        MemoryPool<String>::destroyMemoryPool();
        cout << endl;
    }

    //  test on STLite::list
    void testCase9()
    {
        list<int, MemoryPool<int> > l1;

        for (int i = 0; i < OBJECT_NUM; ++i)
        {
            l1.push_back(i);
        }

        print(l1.begin(), l1.end());
    }

    void testCase10()
    {
        list<String, MemoryPool<String> > l1;

        for (int i = 0; i < OBJECT_NUM; ++i)
        {
            l1.push_back("String");
        }

        print(l1.begin(), l1.end());
    }

    //  test on Other type
    class Widget_   //  
    {
    private:
        int data;
    public:
        Widget_(int d)
        {
            data = d;
        }
    };

    void testCase11()
    {
        //  list<Widget_, MemoryPool<Widget_> > l1;
    }

    //  test on std::list
    void testCase12()
    {
        std::list<int, MemoryPool<int> > l1;

        for (int i = 0; i < 10; ++i)
        {
            l1.push_back(i);
        }

        print(l1.begin(), l1.end());

//         for (int i = 0; i < 10; ++i)
//         {
//             l1.pop_front();
//         }
    }

    void testCase13()
    {
        std::list<String, MemoryPool<String> > l1;

        for (int i = 0; i < OBJECT_NUM; ++i)
        {
            l1.push_back("String");
        }

        print(l1.begin(), l1.end());
        cout << endl;
    }

    //  test performance
//     void testCase14()
//     {
//         list<int> l1;
// 
//         clock_t start;
//         start = clock();
// 
//         for (int i = 0; i < 10000000; ++i)  
//         {
//             l1.push_back(i);
//         }
// 
//         std::cout << (((double)clock() - start) / CLOCKS_PER_SEC) << "\n\n";
//         //  1) 4.458    STLite::list<int, MemoryPool<int> >
//         //  2) 28.158   STLite::list<int, allocator<int> >
//         //  print(l1.begin(), l1.end());
//     }

    void testMemoryPoolAllocate()
    {
        //  testCase4();
        //  testCase5();
        //  testCase6();
        //  testCase7();
        //  testCase8();
        //  testCase9();
        //  testCase10();
        //  testCase11();
        //  testCase12();
        testCase13();
    }

    //  test MemoryPool::deallocate
    void testCase15()
    {
        int *ptr[OBJECT_NUM];
        ptr[0] = MemoryPool<int, 13>::allocate(0);
        cout << ptr[0] << endl;

        ptr[1] = MemoryPool<int, 13>::allocate();
        cout << ptr[1] << endl;

        ptr[2] = MemoryPool<int, 13>::allocate();
        cout << ptr[2] << endl;

        MemoryPool<int, 13>::deallocate(ptr[1]);
        MemoryPool<int, 13>::deallocate(ptr[2]);

        ptr[3] = MemoryPool<int, 13>::allocate();
        cout << ptr[3] << endl;                         //  same to ptr[2]

        ptr[4] = MemoryPool<int, 13>::allocate();       //  same to ptr[1]
        cout << ptr[4] << endl;

        MemoryPool<int, 13>::destroyMemoryPool();
    }

    void testCase16()
    {
        int *ptr[OBJECT_NUM];
        ptr[0] = MemoryPool<int, 13>::allocate(0);
        cout << ptr[0] << endl;

        ptr[1] = MemoryPool<int, 13>::allocate();
        cout << ptr[1] << endl;

        ptr[2] = MemoryPool<int, 13>::allocate();
        cout << ptr[2] << endl;

        MemoryPool<int, 13>::deallocate(ptr[1]);
        MemoryPool<int, 13>::deallocate(ptr[2]);
        *ptr[2] = 2;    //  ptr[2] has deallocated, access it will destroy the free list!
        cout << *ptr[2] << endl;    //  0

        ptr[3] = MemoryPool<int, 13>::allocate();
        cout << ptr[3] << endl;                         //  same to ptr[2]

        ptr[4] = MemoryPool<int, 13>::allocate();       //  should same to ptr[1], but access ptr[2] has damaged it.
        cout << ptr[4] << endl;

        MemoryPool<int, 13>::destroyMemoryPool();
    }

    //  test on STLite::list
    void testCase17()
    {
        //  cout << sizeof(list_node<int>) << endl;     //  12Byte
        list<int> l1;                                   //  MemoryPool<int, 28(4 + 12 + 12)>
        
        l1.push_back(0);
        l1.push_back(1);
        l1.push_back(2);

        l1.pop_front();
        l1.pop_back();

        l1.push_back(3);    //  address same to 2
        l1.push_back(4);    //  address same to 0

        print(l1.begin(), l1.end());    //  1 3 4
    }
    
    //  test on std::list
    void testCase18()
    {
        std::list<int, MemoryPool<int> > l1;        //  MemoryPool<int, 28(4 + 12 + 12)>

        l1.push_back(0);
        l1.push_back(1);
        l1.push_back(2);

        l1.pop_front();
        l1.pop_back();

        l1.push_back(3);    //  address same to 2
        l1.push_back(4);    //  address same to 0

        print(l1.begin(), l1.end());    //  1 3 4
    }

    void testMemoryPoolDeallocate()
    {
        //  testCase15();
        //  testCase16();
        //  testCase17();
        testCase18();
    }

    //  test MemoryPool's performance
    //  compare allocate
    void testCase19()
    {
        clock_t start;
        
        start = clock();
        for (int i = 0; i < 1000000; ++i)
        {
            int *ptrMemoryPool = MemoryPool<int, 4096>::allocate(0);
        }
        std::cout << (((double)clock() - start) / CLOCKS_PER_SEC) << "\n\n";

        start = clock();
        for (int i = 0; i < 1000000; ++i)
        {
            int *ptrAllocator = allocator<int>::allocate(1);
        }
        std::cout << (((double)clock() - start) / CLOCKS_PER_SEC) << "\n\n";

        //  1000000
        //  MemoryPool  0.045
        //  allocator   10.041  
    }

    //  test allocate and deallocate
    void testCase20()
    {
        clock_t start;

        start = clock();
        for (int i = 0; i < 1000000; ++i)
        {
            int *ptrMemoryPool = MemoryPool<int, 4096>::allocate(0);
            MemoryPool<int, 4096>::deallocate(ptrMemoryPool);
        }
        std::cout << (((double)clock() - start) / CLOCKS_PER_SEC) << "\n\n";

        start = clock();
        for (int i = 0; i < 1000000; ++i)
        {
            int *ptrAllocator = allocator<int>::allocate(1);
            allocator<int>::deallocate(ptrAllocator, 1);
        }
        std::cout << (((double)clock() - start) / CLOCKS_PER_SEC) << "\n\n";
    }

    //  test on STLite::list
    void testCase21()
    {
        list<int> l1;
        
        clock_t start;
        start = clock();

        for (int i = 0; i < 100000; ++i)
        {
            l1.push_back(i);
        }
        
        for (int i = 0; i < 50000; ++i)
        {
            l1.pop_back();
        }

        for (int i = 0; i < 100000; ++i)
        {
            l1.push_front(i);
        }
        std::cout << (((double)clock() - start) / CLOCKS_PER_SEC) << "\n\n";

        //  STLIte::MemoryPool  0.111
        //  STLite::allocator   8.256
    }

    //  test on std::list
    void testCase22()
    {
        std::list<int> l1;

        clock_t start;
        start = clock();

        for (int i = 0; i < 100000; ++i)
        {
            l1.push_back(i);
        }

        for (int i = 0; i < 50000; ++i)
        {
            l1.pop_back();
        }

        for (int i = 0; i < 100000; ++i)
        {
            l1.push_front(i);
        }
        std::cout << (((double)clock() - start) / CLOCKS_PER_SEC) << "\n\n";

        //  STLite::MemoryPool  0.659
        //  STLite::allocator   8.94
        //  std::allocator      8.774
    }

    void testPerformance()
    {
        cout << "testPrformance" << endl;

        //  testCase19();
        //  testCase20();
        //  testCase21();
        testCase22();

        cout << endl;
    }

    //  test char, short.
    //  sizeof(char) < sizeof(slot_pointer)
    void testCase23()
    {
        char *ptr[OBJECT_NUM];

        ptr[0] = MemoryPool<char>::allocate(0);
        *ptr[0] = 'a';
        cout << ptr[0] << endl;
        cout << *ptr[0] << endl;

        ptr[1] = MemoryPool<char>::allocate(0);
        *ptr[1] = 'b';
        cout << ptr[1] << endl;
        cout << *ptr[1] << endl;

        ptr[2] = MemoryPool<char>::allocate(0);
        *ptr[2] = 'c';
        cout << ptr[2] << endl;
        cout << *ptr[2] << endl;

        MemoryPool<char>::deallocate(ptr[1]);
        MemoryPool<char>::deallocate(ptr[2]);

        ptr[3] = MemoryPool<char>::allocate(0);
        *ptr[3] = 'd';
        cout << ptr[3] << endl;
        cout << *ptr[3] << endl;

        MemoryPool<char>::destroyMemoryPool();
    }

    void testCase24()
    {
        char *ptr[2];
        ptr[0] = allocator<char>::allocate(1);
        *ptr[0] = 'a';
        cout << ptr[0] << endl;
        cout << *ptr[0] << endl;
    }

    void testMemoryPool()
    {
        cout << "testMemoryPool" << endl;

        //  testMemoryPoolAllocate();
        //  testMemoryPoolDeallocate();
        //  testPerformance();

        testCase23();
     //   testCase24();

        cout << endl;
    }

    //////////////////////////////////////////////////////////////////////
    void test()
    {
        cout << "alloc_public test" << endl;

        //  testCase1();
        //  testCase2();
        //  testCase3();
        testMemoryPool();

        cout << endl;
    }
}

#endif