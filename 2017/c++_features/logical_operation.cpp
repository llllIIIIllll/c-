// C++17
#include <iostream>
#include <string>
#include <algorithm>
#include <functional>

template <typename... Args>
std::enable_if_t<std::conjunction_v<std::is_integral<Args>...>> 
Func(Args... args)
{
	std::cout << "All types are integral.\n";
}

template <typename... Args>
std::enable_if_t<!std::conjunction_v<std::is_integral<Args>...>>
Func(Args... args)
{
	std::cout << "Not all types are integral.\n";
}

int main()
{
	Func(42, true);
	Func(42, "hello");

	return 0;
}
