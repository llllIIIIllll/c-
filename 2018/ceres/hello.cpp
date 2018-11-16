#include "ceres/ceres.h"
#include "ceres/local_parameterization.h"

using namespace ceres;

class QuadraticCostFunction : public ceres::SizedCostFunction<1, 1> 
{
public:
    virtual ~QuadraticCostFunction() {}
    virtual bool Evaluate(double const* const * parameters,
                          double* residuals,
                          double** jacobians) const 
    {
        const double x = parameters[0][0];
        residuals[0] = 10 - x;
        // compute the jacobian
        if (jacobians != NULL && jacobians[0] != NULL)
        {
            jacobians[0][0] = -1;
        }
        return true;
    }
};

struct CostFunctor {
   template <typename T>
   bool operator()(const T* const x, T* residual) const {
     residual[0] = T(10.0) - x[0];
     return true;
   }
};

int main(int argc, char** argv)
{

  // The variable to solve for with its initial value.
  double initial_x = 5.0;
  double x = initial_x;

  // Build the problem.
  Problem problem;

  // Set up the only cost function (also known as residual). This uses
  // auto-differentiation to obtain the derivative (jacobian).
  CostFunction* cost_function =
      new AutoDiffCostFunction<CostFunctor, 1, 1>(new CostFunctor);
  problem.AddResidualBlock(cost_function, NULL, &x);

  // Run the solver!
  Solver::Options options;
  options.linear_solver_type = ceres::DENSE_QR;
  options.minimizer_progress_to_stdout = true;
  Solver::Summary summary;
  Solve(options, &problem, &summary);

  std::cout << summary.BriefReport() << "\n";
  std::cout << "x : " << initial_x
            << " -> " << x << "\n";
  return 0;
}