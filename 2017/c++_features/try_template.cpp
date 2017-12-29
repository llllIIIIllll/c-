// C++17
#include <iostream>
#include <string>
#include <map>

int main()
{
	std::string s1("hello");
	std::map<int, std::string> myMap;
	myMap.emplace(1, "aaa");
	myMap.emplace(2, "bbb");
	myMap.emplace(3, "ccc");

  //std::cout << s1.empty() << '\n'; // 0
  //myMap.emplace(3, std::move(s1));
  //std::cout << s1.empty() << '\n'; // 1

  //std::cout << s1.empty() << '\n'; // 0
  //myMap.try_emplace(3, std::move(s1));
  //std::cout << s1.empty() << '\n'; // 0

	std::cout << s1.empty() << '\n';
	myMap.try_emplace(4, std::move(s1));
	std::cout << s1.empty() << '\n';

	return 0;
}
