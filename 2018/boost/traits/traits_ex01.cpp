#include <type_traits>
#include <boost/callable_traits/remove_member_const.hpp>

struct foo
{
	void bar() const {}
};

using const_removed = boost::callable_traits::remove_member_const_t<decltype(&foo::bar)>;

static_assert(std::is_same<const_removed, void(foo::*)()>::value, "");

int main() {}