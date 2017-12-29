// C++ 14

#include <iostream>

auto Sum()
{
	return 0;
}

template<typename Arg, typename... Args>
auto Sum(Arg first, Args... rest)
{
	return first + Sum(rest...);
}

int main()
{
	std::cout << Sum(1, 2, 3, 4) << '\n';
	return 0;
}
