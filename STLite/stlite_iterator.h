/********************************************************************
	Time:	  2015/10/21
	Filename: stlite_iterator
	Author:	  dinglj
	
	Purpose:  迭代器实现
*********************************************************************/
#ifndef _STLITE_ITERATOR_H_
#define _STLITE_ITERATOR_H_

namespace STLite
{
    //  五种迭代器类型
    struct input_iterator_tag{};
    struct output_iterator_tag{};
    struct forward_iterator_tag : public input_iterator_tag{};
    struct bidirectional_iterator_tag : public forward_iterator_tag{};
    struct random_access_iterator_tag : public bidirectional_iterator_tag{};

    //  迭代器基类，若自定义迭代器，可以继承它,参见unit_test/iterator_traits_test.h
    template<class Category, class T, class Pointer = T*, class Reference = T&, class Distance = ptrdiff_t>
    struct iterator
    {
        typedef Category    iterator_category;
        typedef T           value_type;
        typedef Pointer     pointer;
        typedef Reference   reference;
        typedef Distance    difference_type;
    };

    //////////////////////////////////////////////////////////////////////
    //  五种迭代器定义
    //  五种类型的迭代器仅仅是一个空壳，有什么具体作用？如果自定义迭代器，可以继承iterator；
    //  如果涉及容器迭代器，则需要完全设计，也没有利用到这五种迭代器呀？
    template<class T, class Distance>
    struct input_iterator
    {
        typedef input_iterator_tag  iterator_category;      //  确定迭代器类型，类似于类型识别
        typedef T                   value_type;
        typedef T*                  Pointer;
        typedef T&                  reference;
        typedef Distance            difference_type;
    };

    struct output_iterator
    {
        typedef output_iterator_tag     iterator_category;   //  确定迭代器类型，类似于类型识别
        typedef void                    value_type;
        typedef void                    pointer;
        typedef void                    reference;
        typedef void                    difference_type;
    };

    template<class T, class Distance>
    struct forward_iterator
    {
        typedef forward_iterator_tag    iterator_category;   //  确定迭代器类型，类似于类型识别
        typedef T                       value_type;
        typedef T*                      pointer;
        typedef T&                      reference;
        typedef Distance                difference_type;
    };
    template<class T, class Distance>
    struct bidirectional_iterator
    {
        typedef bidirectional_iterator_tag  iterator_category;   //  确定迭代器类型，类似于类型识别
        typedef T                           value_type;
        typedef T*                          pointer;
        typedef T&                          reference;
        typedef Distance                    difference_type;
    };

    template<class T, class Distance>
    struct random_access_iterator
    {
        typedef random_access_iterator_tag  iterator_category;
        typedef T                           value_type;
        typedef T*                          pointer;
        typedef T&                          reference;
        typedef Distance                    difference_type;
    };

    //////////////////////////////////////////////////////////////////////
    //  迭代器萃取器
    template<class Iterator>
    struct iterator_traits
    {                              
        typedef typename Iterator::iterator_category    iterator_category;
        typedef typename Iterator::value_type           value_type;
        typedef typename Iterator::pointer              pointer;
        typedef typename Iterator::reference            reference;
        typedef typename Iterator::difference_type      difference_type;
    };
    //////////////////////////////////////////////////////////////////////

    //  偏特化原生指针,原始指针为random_access_iterator_tag
    template<class T>
    struct iterator_traits<T*>
    {
        typedef random_access_iterator_tag  iterator_category;
        typedef T                           value_type;
        typedef T*                          pointer;
        typedef T&                          reference;
        typedef ptrdiff_t                   difference_type;
    };

    template<class T>
    struct iterator_traits<const T*>
    {
        typedef random_access_iterator_tag  iterator_category;
        typedef T                           value_type;
        typedef T*                          pointer;
        typedef T&                          reference;
        typedef ptrdiff_t                   difference_type;
    };

    //  识别函数，分别可以识别出迭代器category, value_type, difference_type。内联函数
    template<class Iterator>
    inline typename iterator_traits<Iterator>::iterator_category
    iterator_category(const Iterator &)
    {
        typedef typename iterator_traits<Iterator>::iterator_category category;
        return category();  //  调用一个默认构造函数，相当于int()
    }

    template<class Iterator>
    inline typename iterator_traits<Iterator>::value_type
    value_type(const Iterator &)
    {
        return static_cast<typename iterator_traits<T>::value_type *>(0);
    }

    template<class Iterator>
    inline typename iterator_traits<Iterator>::difference_type*
    distance_type(const Iterator &)
    {
        return static_cast<typename iterator_traits<Iterator>::difference_type *>(0);
    }
    
    /*
        上述的定义位于SGI STL中iterator_base.h文件中，此外iterator_base中还包含函数distance(Iterator first, Iterator last),
        advance(Iterator iter, Distancen n)。
        
        在iterator.h中，还定义了reverse_itertor，istream_iterator, ostream_iterator等各类迭代器。
    */
}
#endif
