// C++17
#include <iostream>

enum E
{
	A = 0;
	B = 1;
	C = 2;
	First[[deprecated]] = A,
};

namespace[[deprecated]] DeprecatedFeatures
{
	void OldFunc() {};
}

int main()
{
	// Compiler warning will be issued
	DeprecatedFeatures::OldFunc();

	// Compiler warning will be issued
	std::cout << E.First << '\n';

	return 0;
}
