// /********************************************************************
// 	Time:	  2015/10/23
// 	Filename: stlite_uninitialized
// 	Author:	  dinglj
// 	
// 	Purpose:  内存基本处理工具，配合construct，用于初始化内存
//               1. uninitialized_copy(first, last, result)
//               2. uninitialized_fill(first, last, value)
//               3. uninitialized_fill_n(first, n, value)
// *********************************************************************/
// #ifndef _STLITE_UNINITIALIZED_H_
// #define _STLITE_UNINITIALIZED_H_
// 
// namespace STLite
// {
//     //////////////////////////////////////////////////////////////////////
//     //  uninitialized_copy
//     template<class InputIterator, class ForwardIterator>
//     inline ForwardIterator uninitialized_copy_aux(InputIterator first, InputIterator last, ForwardIterator result, __true_type)
//     {
//         memmove(result, first, last - first);
//         return result + (last - first);
//     }
// 
//     template<class InputIterator, class ForwardIterator>
//     inline ForwardIterator uninitialized_copy_aux(InputIterator first, InputIterator last, ForwardIterator result, __false_type)
//     {
//         ForwardIterator cur = result;
//         while (first != last)
//         {
//             construct(&*cur, *first);
//             first++;
//             cur++;
//         }
//         return cur;
//     }
// 
//     template<class InputIterator, class ForwardIterator>
//     inline ForwardIterator uninitialized_copy(InputIterator first, InputIterator last, ForwardIterator result)
//     {
//         typedef typename iterator_traits<InputIterator>::value_type value_type(InputIterator);
//         typedef typename __type_traits<value_type>::is_POD_type is_POD_type;
//         cout << typeid(is_POD_type()).name();
//         return uninitialized_copy_aux(first, last, result, is_POD_type());
//             
//     }
// 
//     //////////////////////////////////////////////////////////////////////
// }
// #endif