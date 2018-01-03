#include <string>
#include <iostream>
#include <sstream>
#include <algorithm>

using namespace std;

int main()
{
	string test = "°¢»ªÌï";
	ostringstream os;

	std::cout << test << std::endl;

	for (int i = 0; i < test.length() - 1; i += 2)
	{
		os << test[i] << test[i + 1] << "\n";
	}

	test = os.str();
	std::cout << test << std::endl;

	system("pause");
}