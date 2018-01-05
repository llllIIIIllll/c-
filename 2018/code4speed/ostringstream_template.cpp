#include <iostream>
#include <sstream>
#include <string>

using namespace std;

 

// TODO:
template <typename... Args>
auto getAllString(Args... args)
{
	return (args + ...);
}

void print()
{
	cout << endl;
}

template <typename T>
void print(const T& t)
{
	cout << t << endl;
}

template <typename First, typename... Rest>
void print(const First& first, const Rest&... rest)
{
	cout << first << ",";
	print(rest...);
}

int main()
{
	int i = 1;
	int j = 2;
	wstring s1 = L"²âÊÔ";
	string s2 = "dd";
	ostringstream os;

	auto fun = [&os](auto s){ os << s;};
	std::cout << os.str();

	print("first", 2, "third", 3.33434, s2, "end");
}