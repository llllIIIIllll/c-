#include <type_traits>
#include <boost/callable_traits/add_member_const.hpp>

namespace ct = boost::callable_traits;
struct foo {};

int main()
{
	{
		using pmf = int(foo::*)();
		using expect = int(foo::*)() const;
		using test = ct::add_member_const_t<pmf>; 
		static_assert(std::is_same<test, expect>::value, "");
	}
	{

	}
}