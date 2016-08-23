//
//  mytest.hpp
//  test
//
//  Created by Chris on 16/8/14.
//  Copyright © 2016年 Chris. All rights reserved.
//

#ifndef mytest_hpp
#define mytest_hpp

#include "common.h"

template <typename __T> struct t;

template <typename __T, typename __comp = std::less<__T>>
struct iterator_compare
{
    
    __comp __compare;

    int operator () (typename t<__T>::first_value_type first_value,
                     typename t<__T>::second_value_type second_value )

    {
        
        if(__compare(first_value, second_value)) {
            return -1;
        }
        
        if(__compare(second_value, first_value)) {
            return 1;
        }
        
        return 0;
        
    }
    
};


template <typename __T>
struct t
{
    
    typedef __T value_type;
    typedef __T first_value_type;
    typedef __T second_value_type;
    typedef __T return_value_type;
    
};


template <typename __T>
struct t<__T *> {
    
    typedef __T value_type;
    typedef __T first_value_type;
    typedef __T second_value_type;
    typedef __T return_value_type;
    
};



#endif /* mytest_hpp */
