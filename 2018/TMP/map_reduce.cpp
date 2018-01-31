#include <algorithm>
#include <cctype>
#include <iostream>
#include <string>
#include <vector>

int main()
{
	std::string s("hello");
	std::transform(s.begin(), s.end(), s.begin(),
		[](unsigned char c) { return std::toupper(c); });

	std::vector<std::size_t> ordinals;
	std::transform(s.begin(), s.end(), std::back_inserter(ordinals),
		[](unsigned char c) { return c; });

	std::cout << s << ':';
	for (auto ord : ordinals) {
		std::cout << ' ' << ord;
	}
}