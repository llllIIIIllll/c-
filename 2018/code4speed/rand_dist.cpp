#include <iostream>
#include <iomanip>
#include <string>
#include <map>
#include <random>
#include <cmath>
int main()
{
    std::random_device rd{};
    std::mt19937 gen{rd()};
 
    // 值最可能接近平均
    // 标准差影响生成的值距离平均数的分散
    std::normal_distribution<> d{5,2};
 
    std::cout << (d(gen)) << std::endl;
}
