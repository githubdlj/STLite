/********************************************************************
	Time:	  2015/10/21
	Filename: stlite_iterator
	Author:	  dinglj
	
	Purpose:  iterator 
*********************************************************************/
#ifndef _STLITE_ITERATOR_H_
#define _STLITE_ITERATOR_H_

#include <crtdefs.h>    //  for ptrdiff_t

//////////////////////////////////////////////////////////////////////
namespace STLite
{
    //  iterator type
    struct input_iterator_tag{};
    struct output_iterator_tag{};
    struct forward_iterator_tag : public input_iterator_tag{};
    struct bidirectional_iterator_tag : public forward_iterator_tag{};
    struct random_access_iterator_tag : public bidirectional_iterator_tag{};

    //  the ITERATOR, if we define our iterator, we can inherit it. (see public_test/iterator_test.h)
    template<class Category, class T, class Pointer = T*, class Reference = T&, class Distance = std::ptrdiff_t>
    struct iterator
    {
        typedef Category    iterator_category;
        typedef T           value_type;
        typedef Pointer     pointer;
        typedef Reference   reference;
        typedef Distance    difference_type;
    };

    //////////////////////////////////////////////////////////////////////
    template<class T, class Distance>
    struct input_iterator
    {
        typedef input_iterator_tag  iterator_category;     
        typedef T                   value_type;
        typedef T*                  pointer;
        typedef T&                  reference;
        typedef Distance            difference_type;
    };

    struct output_iterator
    {
        typedef output_iterator_tag     iterator_category;   
        typedef void                    value_type;
        typedef void                    pointer;
        typedef void                    reference;
        typedef void                    difference_type;
    };

    template<class T, class Distance>
    struct forward_iterator
    {
        typedef forward_iterator_tag    iterator_category;  
        typedef T                       value_type;
        typedef T*                      pointer;
        typedef T&                      reference;
        typedef Distance                difference_type;
    };

    template<class T, class Distance>
    struct bidirectional_iterator
    {
        typedef bidirectional_iterator_tag  iterator_category;   
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
    //  generalization, iterator
    template<class Iterator>
    struct iterator_traits
    {                              
        typedef typename Iterator::iterator_category    iterator_category;
        typedef typename Iterator::value_type           value_type;
        typedef typename Iterator::pointer              pointer;
        typedef typename Iterator::reference            reference;
        typedef typename Iterator::difference_type      difference_type;
    };

    //  partial specialization
    //  the special iterator: raw pointer
    template<class T>
    struct iterator_traits<T*>
    {
        typedef random_access_iterator_tag  iterator_category;
        typedef T                           value_type;
        typedef T*                          pointer;
        typedef T&                          reference;
        typedef std::ptrdiff_t              difference_type;
    };

    template<class T>
    struct iterator_traits<const T*>
    {
        typedef random_access_iterator_tag  iterator_category;
        typedef T                           value_type;
        typedef T*                          pointer;
        typedef T&                          reference;
        typedef std::ptrdiff_t              difference_type;
    };

    //////////////////////////////////////////////////////////////////////
    template<class Iterator>
    inline typename iterator_traits<Iterator>::iterator_category
    iterator_category(const Iterator &)
    {
        typedef typename iterator_traits<Iterator>::iterator_category category;
        return category();  // call constructor, return a xx_iterator_tag
    }

    template<class Iterator>
    inline typename iterator_traits<Iterator>::value_type*          //  why return value_type * rather than value_type
    value_type(const Iterator &)
    {
        return static_cast<typename iterator_traits<Iterator>::value_type *>(0);
    }

    template<class Iterator>
    inline typename iterator_traits<Iterator>::difference_type*
    distance_type(const Iterator &)
    {
        return static_cast<typename iterator_traits<Iterator>::difference_type *>(0);
    }
    
    //  the SGI STL offer reverse_iterator, istream_iterator, ostream_iterator...    
    
    //////////////////////////////////////////////////////////////////////
    //  function about iterator
   
    //  distance
    template<class InputIterator>
    inline typename iterator_traits<InputIterator>::difference_type
    _distance(InputIterator first, InputIterator last, input_iterator_tag)
    {
        typedef typename iterator_traits<InputIterator>::difference_type n;
        while (first != last)
        {
            ++first;
            ++n;
        }

        return n;
    }

    template<class RandomAccessIterator>
    inline typename iterator_traits<RandomAccessIterator>::difference_type
    _distance(RandomAccessIterator first, RandomAccessIterator last, random_access_iterator_tag)
    {
        return last - first;
    }

    template<class InputIterator>
    inline typename iterator_traits<InputIterator>::difference_type
    distance(InputIterator first, InputIterator last)
    {
        typedef typename iterator_traits<InputIterator>::iterator_category category;
        return _distance(first, last, category());
    }

    //////////////////////////////////////////////////////////////////////
    //  advance
    template<class InputIterator, class Distance>
    inline void _advance(InputIterator &iter, Distance n, input_iterator_tag)
    {
        while (n--)
        {
            ++iter;
        }
    }
    
    template<class BidirectionalIterator, class Distance>
    inline void _advance(BidirectionalIterator &iter, Distance n, bidirectional_iterator_tag)
    {
        if (n > 0)
        {
            while (n--)
            {
                ++iter;
            }
        }
        else
        {
            while (n++)
            {
                --iter;
            }
        }
    }
        
    template<class RandomAccessIterator, class Distance>
    inline void _advance(RandomAccessIterator &iter, Distance n, random_access_iterator_tag)
    {
        iter += n;
    }

    template<class InputIterator, class Distance>
    inline void advance(InputIterator &iter, Distance n)
    {
        typedef iterator_traits<InputIterator>::iterator_category category;
        _advance(iter, n, category());
    }
}
#endif
