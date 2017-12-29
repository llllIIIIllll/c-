// C++17
#include <set>
#include <iostream>

int main()
{
	int arr[] = { 1, 2, 3, 4 };
	auto[a, b, c, d] = arr;
	std::cout << a << b << c << d << '\n';

	return 0;
}
