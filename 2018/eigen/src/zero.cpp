#include <iostream>
#include <Eigen/Dense>

using namespace Eigen;
using namespace std;

int main()
{
    Eigen::Vector2d v;
    v(1) = 0;
    std::cout << v << std::endl;
}
