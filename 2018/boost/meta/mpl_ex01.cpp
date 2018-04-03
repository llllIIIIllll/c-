#include <boost/mpl/vector.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mpl/vector_c.hpp>

namespace mpl = boost::mpl;
static int const five = mpl::int_<5>::value;

typedef boost::mpl::vector<
	signed char, short, int, long> signed_types;

typedef mpl::vector_c<int, 1, 0, 0, 0, 0, 0, 0> mass;
typedef mpl::vector_c<int, 0, 1, 0, 0, 0, 0, 0> length;
typedef mpl::vector_c<int, 0, 0, 1, 0, 0, 0, 0> time;
typedef mpl::vector_c<int, 0, 0, 0, 1, 0, 0, 0> charge;
typedef mpl::vector_c<int, 0, 0, 0, 0, 1, 0, 0> temperature;
typedef mpl::vector_c<int, 0, 0, 0, 0, 0, 1, 0> intensity;
typedef mpl::vector_c<int, 0, 0, 0, 0, 0, 0, 1> angle;

typedef mpl::vector_c<int, 0, 1, -1, 0, 0, 0, 0> velocity;
typedef mpl::vector_c<int, 0, 1, -2, 0, 0, 0, 0> acceleration;
typedef mpl::vector_c<int, 1, 1, -1, 0, 0, 0, 0> momentum;
typedef mpl::vector_c<int, 1, 1, -2, 0, 0, 0, 0> force;

typedef mpl::vector_c<int, 0, 0, 0, 0, 0, 0, 0> scalar;