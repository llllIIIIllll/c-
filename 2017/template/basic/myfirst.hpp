// basic/myfirst.hpp

#ifndef MYFIRST_HPP
#define MYFIRST_HPP

#include <iostream>
#include <typeinfo>
// template declaration
template <typename T>
void print_typeof (T const&);


template <typename T>
void print_typeof (T const& x)
{
    std::cout << typeid(x).name() << std::endl;
}

#endif      // MYFIRST_HPP