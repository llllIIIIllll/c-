#include <iostream>
#include <string>
#include <memory>

// can't use to_stirng(string)

template <typename T>
std::string str(T t)
{
	if (std::is_same_v<T, std::string>) // or is _convertible...
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
	if constexpr (std::is_floating_point_v<T>) // << !!
		return absolute(a - b) < precision_threshold<T>;
	else
		return a == b;
}

//! C++ 17
// before C++17
template <typename Concrete, typename... Ts>
std::enable_if_t<std::is_constructible<Concrete, Ts...>::value, std::unique_ptr<Concrete>>
constructArgsOld(Ts&&... params)
{
    return std::make_unique<Concrete>(std::forward<Ts>(params)...);
}

template <typename Concrete, typename... Ts>
std::enable_if_t<!std::is_constructible<Concrete, Ts...>::value, std::unique_ptr<Concrete> >
constructArgsOld(...)
{
    return nullptr;
}

// using C++17
// - if constexpr
// - is_constructible_v
// - fold expression to print arguments
template <typename Concrete, typename... Ts>
std::unique_ptr<Concrete> constructArgs(Ts&&... params)
{ 
	std::cout << __func__ << ": ";
	((std::cout << params << ", "), ...);
	std::cout << "\n";
    
	if constexpr (std::is_constructible_v<Concrete, Ts...>)
		return std::make_unique<Concrete>(std::forward<Ts>(params)...);
	else
		return nullptr;
}
class Investment;
/// factory with variable arguments
template <typename... Ts>
std::unique_ptr<Investment>
makeInvestMent(Ts&&... params);

class Investment
{
public:
	virtual ~Investment() {}
	virtual void calcRisk() = 0;
}; 

class Stock : public Investment
{
public:
	explicit Stock(const std::string&){}
	void calcRisk() override{}
};

class Bond : public Investment
{
public:
	explicit Bond(const std::string&, const std::string&, int) {}
	void calcRisk() override{}
};

class RealEstate : public Investment
{
public:
    explicit RealEstate(const std::string&, double, int) { }
    void calcRisk() override { }
};

template <typename... Ts>
std::unique_ptr<Investment>
makeInvestment(const std::string &name, Ts&&... params)
{
    std::unique_ptr<Investment> pInv;

    if (name == "Stock")
        pInv = constructArgs<Stock, Ts...>(std::forward<Ts>(params)...);
    else if (name == "Bond")
        pInv = constructArgs<Bond, Ts...>(std::forward<Ts>(params)...);
    else if (name == "RealEstate")
        pInv = constructArgs<RealEstate, Ts...>(std::forward<Ts>(params)...);

    // call additional methods to init pInv...

    return pInv;
}

int main()
{
}
