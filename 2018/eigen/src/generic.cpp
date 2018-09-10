#include <iostream>
#include <Eigen/Dense>
#include <Eigen/SVD>

using namespace std;
using namespace Eigen;

float inv_cond(const Eigen::Ref<const Eigen::MatrixXf>& a)
{
    const Eigen::VectorXf sing_vals = a.jacobiSvd().singularValues();
    return sing_vals(sing_vals.size() - 1) / sing_vals(0);
}

void cov(const Eigen::Ref<const Eigen::MatrixXf> x, const Eigen::Ref<const Eigen::MatrixXf> y, Eigen::Ref<Eigen::MatrixXf> C)
{
    const float num_observations = static_cast<float>(x.rows());
    const Eigen::RowVectorXf x_mean = x.colwise().sum() / num_observations;
    const Eigen::RowVectorXf y_mean = y.colwise().sum() / num_observations;
    C = (x.rowwise() - x_mean).transpose() * (y.rowwise() - y_mean) / num_observations;
}

template <typename Derived, typename otherDerived>
void cov(const Eigen::MatrixBase<Derived>& x, const Eigen::MatrixBase<Derived>& y,
         Eigen::MapBase<otherDerived> const & C)
{
    typedef typename Derived::Scalar Scalar;
    typedef typename internal::plain_row_type<Derived>::type RowVectorType;

    const Scalar num_observations = static_cast<Scalar>(x.rows());
    const RowVectorType x_mean = x.colwise().sum() / num_observations;
    const RowVectorType y_mean = y.colwise().sum() / num_observations;

    const_cast<Eigen::MatrixBase<otherDerived>&> (C) = 
        (x.rowwise() - x_mean).transpose() * (y.rowwise() - y_mean) / num_observations;
}

int  main()
{
    //! [inv_cond]
    Eigen::Matrix4f m = Eigen::Matrix4f::Random();

    cout << "matrix m:              " << endl                                      << m;
    cout << endl                      << endl;
    cout << "inv_cond(m):           " << inv_cond(m)                               << endl;
    cout << "inv_cond(m(1:3, 1:3)): " << inv_cond(m.topLeftCorner(3, 3))           << endl;
    cout << "inv_cond(m+I):         " << inv_cond(m + Eigen::Matrix4f::Identity()) << endl;

    //! [cov]
    Eigen::MatrixXf m1, m2, m3;
    m1 = Eigen::Matrix4f::Random();
    m2 = Eigen::Matrix4f::Random();
    m3 = Eigen::Matrix4f::Random();

    cout << " before: \n" << m3;
    cov(m1, m2, m3);
    cout << " after1: \n" << m3  << endl;
    cov(m1.leftCols<3>(), m2.leftCols<3>(), m3.topLeftCorner<3, 3>());
    cout << " after2: \n" << m3  << endl;

}
