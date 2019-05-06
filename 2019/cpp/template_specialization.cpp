#include <iostream>

template<class T> void g( T const & ) // function template
{
    std::cout << 1 << std::endl;
}
template<> void g( int const & ) // explicit specialization
{
    std::cout << 2 << std::endl;
}
void g( double ) // function
{
    std::cout << 3 << std::endl;
}

int main()
{
    g(42);
    g(4.2);
    g('4');
    g("4");
}