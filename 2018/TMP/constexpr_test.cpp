#include <iostream>

template <typename T>
constexpr T pi = T(3.1415926535897932385);template <typename T>T area_of_cirle_with_radius(T r){	return pi<T> * r * r;}struct matrix_constants 
{
	template<typename T>
	using pauli = hermitian_matrix<T, 2>;
	template<typename T>
	constexpr pauli<T> sigma1 = { { 0, 1 },{ 1, 0 } };
	template<typename T>
	constexpr pauli<T> sigma2 = { { 0, -1i },{ 1i, 0 } };
	template<typename T>
	constexpr pauli<T> sigma3 = { { 1, 0 },{ -1, 0 } };
};int main(){
	using std::cout;	using std::endl;	using std::cin;	cout << area_of_cirle_with_radius<int>(1) << endl;	system("pause");}