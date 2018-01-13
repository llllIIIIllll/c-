#include <type_traits>
#include <tuple>
#include <boost/callable_traits.hpp>

namespace ct = boost::callable_traits;

template <typename A, typename B>
void assert_same() { static_assert(std::is_same<A, B>::value, ""); }

struct foo
{
	void operator()(int, char, float) const {}
};

int main()
{
	assert_same<
		ct::args_t<foo>,
		std::tuple<int, char, float>
	>();

	static_assert(ct::has_void_return<foo>::value, "");

	static_assert(!ct::has_varargs<foo>::value, "");

	using pmf = decltype(&foo::operator());

	assert_same<
		ct::remove_member_const_t<pmf>,
		void (foo::*)(int, char, float)
	>();

	assert_same<
		pmf,
		ct::add_member_const_t<void (foo::*)(int, char, float)>
	>();

	static_assert(ct::is_const_member<pmf>::value, "");
}