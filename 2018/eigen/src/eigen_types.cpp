#include <iostream>
#include <Eigen/Core>
#include <Eigen/SVD>

using namespace Eigen;

template <typename Derived>
void print_size(const Eigen::EigenBase<Derived>& b)
{
    std::cout   << "size (rows, cols): " << b.size() << " (" << b.rows()
                << ", "                  << b.cols() << ") " << std::endl;
}

template <typename Derived>
void print_block(const Eigen::DenseBase<Derived>& b, int x, int y, int r, int c)
{
    std::cout << "block: " << b.block(x, y, r, c) << std::endl;
}

template <typename Derived>
void print_max_coeff(const Eigen::ArrayBase<Derived>& a)
{
    std::cout << "max: " << a.maxCoeff() << std::endl;
}

template <typename Derived>
void print_inv_cond(const Eigen::MatrixBase<Derived>& a)
{
  const typename Eigen::JacobiSVD<typename Derived::PlainObject>::SingularValuesType&
    sing_vals = a.jacobiSvd().singularValues();
  std::cout << "inv cond: " << sing_vals(sing_vals.size()-1) / sing_vals(0) << std::endl;
}

template <typename DerivedA, typename DerivedB>
typename DerivedA::Scalar squaredist(const Eigen::MatrixBase<DerivedA>& p1, 
                                     const Eigen::MatrixBase<DerivedB>& p2)
{
    return (p1 - p2).squaredNorm();
}

int main()
{
    Eigen::Vector3f v;
    print_size(v);
    // v.asDiagonal() returns a 3x3 diagonal matrix pseudo-expression
    print_size(v.asDiagonal());

    //! [print_inv_cnd]
    Eigen::Matrix3f m;
    m(0, 0) = 1;
    m(1, 1) = 2;
    m(2, 2) = 3;
    print_inv_cond(m);
}
