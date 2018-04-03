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

//============================================================
template <class T, class Dimensions>
struct quantity
{
	explicit quantity(T x) : m_value(x) {}
	T value() const { return m_value; }
private:
	T m_value;
};
quantity<float, length> l(1.0f);
quantity<float, mass> m(2.0f);
//============================================================
template <class T, class D>
quantity<T, D> operator+(quantity<T, D> x, quantity<T, D> y)
{
	return quantity<T, D>(x.value() + y.value());
}
template <class T, class D>
quantity<T, D> operator-(quantity<T, D> x, quantity<T, D> y)
{
	return quantity<T, D>(x.value() - y.value());
}
//============================================================
#include <boost/static_assert.hpp>
#include <boost/mpl/plus.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mpl/transform.hpp>

void test_implementing()
{
BOOST_STATIC_ASSERT((
	mpl::plus<
	mpl::int_<2>,
	mpl::int_<3>
	>::type::value == 5
	));
}

// metafunction
struct plus_f
{
	template <class T1, class T2>
	struct apply
	{
		typedef typename mpl::plus<T1, T2>::type type;
	};
};

template <class T, class D1, class D2>
quantity<T, typename mpl::transform<D1, D2, plus_f>::type>
operator*(quantity<T, D1> x, quantity<T, D2> y)
{
	typedef typename mpl::transform<D1, D2, plus_f>::type dim;
	return quantity<T, dim>(x.value() * y.value());
}

