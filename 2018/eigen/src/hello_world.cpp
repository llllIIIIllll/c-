#include <iostream>
#include <Eigen/Dense>

using namespace Eigen;
using namespace std;

int main()
{
    // 
    {
        MatrixXd m = MatrixXd::Random(3, 3);
        VectorXd v(3);
        m = (m + MatrixXd::Constant(3, 3, 1.2)) * 50;

        cout << m        << endl;
        v    << 1, 2, 3;
        cout << m * v    << endl;
        v.resize(4);

        cout << v << endl;
    }

    //
    {
        Matrix2d a;
        a << 1, 2,
             3, 4;
        MatrixXd b(2,2);
        b << 2, 3,
             1, 4;

        cout << "a + b =\n"     << a + b << endl;
        cout << "a - b =\n"     << a - b << endl;
        cout << "Doing a += b;" << endl;

        a += b;
        Vector3d v(1,2,3);
        Vector3d w(1,0,0);

        cout << "Now a =\n"      << a          << endl;
        cout << "-v + w - v =\n" << -v + w - v << endl;

    }
}
