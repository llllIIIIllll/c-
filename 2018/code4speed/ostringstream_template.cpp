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
int main()
{
	int i = 1;
	int j = 2;
	string s1 = "测试";
	string s2 = "dd";
	ostringstream os;


	auto fun = [&os](auto s){ os << s;};


	std::cout << os.str();

}