/********************************************************************
	Time:	  2016/03/11
	Filename: stlite_pair
	Author:	  dinglj
	
	Purpose:  pair
*********************************************************************/
#ifndef _STLITE_PAIR_H_
#define _STLITE_PAIR_H_

namespace STLite
{
    template<class T1, class T2>
    struct pair
    {
        typedef T1 first_type;
        typedef T2 second_type;

        first_type first;
        first_type second;

        //  constructor
        pair() : first(first_type()), second(second_type()) {}
        pair(const first_type& fir, const second_type& sec) : first(fir), second(sec) {}
        pair(const pair& p) : first(p.first), second(p.second) {}

    };

    template<class T1, class T2>
    inline bool operator ==(const pair<T1, T2> p1, const pair<T1, T2> p2)
    {
        return (p1.first == p2.first) && (p1.second ==  p2.second);
    }

    template<class T1, class T2>
    inline bool operator !=(const pair<T1, T2> p1, const pair<T1, T2> p2)
    {
        return !(p1 == p2);
    }

    // the base compare operator
    template<class T1, class T2>
    inline bool operator <(const pair<T1, T2> p1, const pair<T1, T2> p2)
    {
        return (p1.first < p2.first) || (!(p1.first > p2.first) && (p1.second < p2.second));
    }

    template<class T1, class T2>
    inline bool operator >(const pair<T1, T2> p1, const pair<T1, T2> p2)
    {
        return p2 < p1;
    }

    template<class T1, class T2>
    inline bool operator <=(const pair<T1, T2> p1, const pair<T1, T2> p2)
    {
        //return (p1 < p2) || (p1 == p2);
        return !(p2 < p1);
    }

    template<class T1, class T2>
    inline bool operator >=(const pair<T1, T2> p1, const pair<T1, T2> p2)
    {
        return !(p1 < p2);
    }

    template<class T1, class T2>
    inline pair<T1, T2> make_pair(T1 first, T2 second)
    {
        return pair<T1, T2>(first, second);
    }
}

#endif
