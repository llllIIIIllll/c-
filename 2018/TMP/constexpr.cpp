#include <string>

// can't use to_stirng(string)

template <typename T>
std::string str(T t)
{
	if (std::is_same_v<T, stfd::string>) // or is _convertible...
		return t;
	else
		return std::to_string(t);
}

// use c++ 11/14 to solve the problem
template <typename T>
std::enable_if_t<std::is_same_v<T, std::string>, std::string> strOld(T t)
{
	return t;
}

template <typename T>
std::enable_if_t<!std::is_same_v<T, std::string>, std::string> strOld(T t)
{
	return std::to_string(t);
}

/// c++14 version
//template <class T>
//constexpr T absolute(T arg)
//{
//	return arg < 0 ? -arg : arg;
//}
//
//template <class T>
//constexpr enable_if_t<is_floating_point<T>::value, bool>
//close_enough(T a, T b) 
//{
//	return absolute(a - b) < static_cast<T>(0.000001);
//}}
//
//template <class T>
//constexpr enable_if_t<!is_floating_point<T>::value, bool>
//close_enough(T a, T b)
//{
//	return a == b;
//}

template <class T>
constexpr T absolute(T arg) {
	return arg < 0 ? -arg : arg;
}

template <class T>
constexpr auto precision_threshold = T(0.000001);

template <class T>
constexpr bool close_enough(T a, T b) {
	if constexpr (is_floating_point_v<T>) // << !!
		return absolute(a - b) < precision_threshold<T>;
	else
		return a == b;
}