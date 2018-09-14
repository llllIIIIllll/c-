#include <array>
#include <iostream>
#include <cstdint>

constexpr int factorial(int n)
{
    return n <= 1 ? 1 : (n * factorial(n - 1));
}

constexpr int fibonacci(unsigned n)
{
    return n <= 1 ? n : fibonacci(n - 1) + fibonacci(n - 2);
}

constexpr uint64_t fibonacci_1(uint64_t n) 
{
    uint64_t F0{0};
    uint64_t F1{1};
    uint64_t F{};
 
    if(n <= 1) 
    {
        return n;
    } 
    else 
    {
        for(uint64_t i = 2; i <= n; ++i) 
        {
            F = F0 + F1;
            F0 = F1;
            F1 = F;
        }
   return F;
   }
}

//const uint64_t NN = 50;
//constexpr std::array<uint64_t, NN> fill_array()
//{
//    std::array<uint64_t, NN> v{0};
//    for (uint64_t i = 0; i < NN; ++i)
//    {
//        v[i] = fibonacci_1(i);
//    }
//    return v;
//}

int main()
{
    constexpr int a = factorial(12);
    constexpr int b = fibonacci(10);

    // Check if the values are actually calculated at compile time
    static_assert(a == 479001600, "factorial failed\n");
    static_assert(b == 55, "fibonacci failed\n");

    std::cout << a << "\n";
    std::cout << b << "\n";
    
    std::cout << fibonacci_1(10) << "\n";

    //constexpr std::array<uint64_t, NN> v = fill_array();
    //std::cout << v[9] << "\n";
    //std::cout << v[10] << "\n";
}
