// C++14
#include <iostream>
#include <type_traits>

template <typename T>
typename std::enable_if<std::is_pointer<T>::value, std::remove_pointer_t<T>>::type
GetValue(T t)
{
	return *t;
}

template <typename T>
typename std::enable_if<!std::is_pointer<T>::value, T>::type
GetValue(T t)
{
	return t;
}

int main()
{
	int v = 10;
	std::cout << GetValue(v) << '\n';
	std::cout << GetValue(&v) << '\n';
	return 0;
}
