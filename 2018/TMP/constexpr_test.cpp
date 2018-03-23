#include <iostream>

template <typename T>
constexpr T pi = T(3.1415926535897932385);
{
	template<typename T>
	using pauli = hermitian_matrix<T, 2>;
	template<typename T>
	constexpr pauli<T> sigma1 = { { 0, 1 },{ 1, 0 } };
	template<typename T>
	constexpr pauli<T> sigma2 = { { 0, -1i },{ 1i, 0 } };
	template<typename T>
	constexpr pauli<T> sigma3 = { { 1, 0 },{ -1, 0 } };
};
	using std::cout;