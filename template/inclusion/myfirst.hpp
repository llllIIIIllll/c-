#ifndef MYFIRST_HPP
#define MYFIRST_HPP
#include <iostream>
#include <typeinfo>

template<typename T>
void printTypeof(T const&);

template<typename T>
void printTypeof(T const& x)
{
    std::cout << typeid(x).name() << '\n';
}

#endif // MYFIRST_HPP