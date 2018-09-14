#include <iostream>
#include <Eigen/Dense>


using namespace std;
using namespace Eigen;

int main() 
{
    Matrix3f A;
    Vector3f b;

    A << 1, 2, 3, 4, 5, 6, 7, 8, 10;
    b << 3, 3, 4;

    cout << "A:\n"        << A << endl;
    cout << "b:\n"        << b << endl;


    Vector3f x = A.colPivHouseholderQr().solve(b);

    cout << "Solution:\n" << x << endl;
}
