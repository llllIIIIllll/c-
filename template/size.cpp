#include <iostream>
#include <functional>
#include <vector>

template<typename T>
auto len(T const& t)
{
    return t.size();
}

int main()
{
    std::vector<int> x;
    std::allocator<int> y;
}