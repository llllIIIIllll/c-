// C++17

#include <iostream>
#include <vector>

template<typename... Args>
auto Sum(Args... args)
{
	return (args + ...);
}

template<typename... Args>
auto Func(Args... args)
{
	return (args + ... + 100);
}

template<typename T, typename... Args>
void PushToVector(std::vector<T>& v, Args&&... args)
{
	(v.push_back(std::forward<Args>(args)), ...);
	// This code is expanded into a sequence of expressions
	// separated by commas as folloes:
	  // v.push_back(std::forward<Args_1>(arg1)),
	  // v.push_back(std::forward<Args_2>(arg2)),
	  // ...
}

int main()
{
	std::cout << Sum(1, 2, 3, 4, 5) << std::endl;
	std::cout << Func(1, 2, 3, 4, 5) << std::endl;

	std::vector<int> vct;
	PushToVector(vct, 1, 4, 5, 8, 1.1111);

	for (auto i : vct)
		std::cout << i;
	std::cout << '\n';
	return 0;
}
