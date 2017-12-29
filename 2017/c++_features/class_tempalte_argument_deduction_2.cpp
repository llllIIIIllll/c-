// C++17
#include <iostream>

template<typename T, typename U>
struct S
{
	T m_first;
	U m_second;
};

template<typename T, typename U>
S(const T &first, const U &second) -> S<T, U>;

int main()
{
	S s = { 42, "hello" };
	std::cout << s.m_first << s.m_second << '\n';
	return 0;

}
