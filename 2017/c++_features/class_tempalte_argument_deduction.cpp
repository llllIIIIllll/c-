#include <tuple>
#include <array>

template<typename T, typename U>
struct S
{
	T m_first;
	U m_second;
	S(T first, U second) : m_first(first), m_second(second) {}
};

int main()
{
// C++14
	
	std::pair<char, int> p1 = { 'c', 42};
	std::tuple<char, int, double> t1 = { 'c', 42, 3.14 };
	S<int, char> s1 = { 10, 'c' };

// C++17

	std::pair p2 = { 'c', 42 };
	std::tuple t2 = { 'c', 42, 3.14 };
	S s2 = { 10, 'c' }; 

	return 0;
}


