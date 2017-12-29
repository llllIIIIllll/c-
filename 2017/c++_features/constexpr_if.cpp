// C++17
#include <iostream>
#include <type_traits>

template <typename T>
auto GetValue(T t)
{
	if constexpr(std::is_pointer<T>::value)
	{
		return *t;
	}
	else
	{
		return t;
	}
}

int main()
{
	int v = 10;
	std::cout << GetValue(v) << '\n';
	std::cout << GetValue(&v) << '\n';
	return 0;
}
