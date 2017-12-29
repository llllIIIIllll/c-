#include <iostream>
#include <string>
#include <any>

using namespace std;

int main()
{
	any a = 42;
	cout << any_cast<int>(a) << '\n';

	a = 11.34f;
	cout << any_cast<float>(a) << '\n';

	a = string{ "hello" };
	cout << any_cast<string>(a) << '\n';

	return 0;
}
