#include <memory>
#include <utility>
#include <iostream>

int ex_01()
{
	int a = 42;
	int b = 43;

	// a and b are both l-values:
	a = b; // ok
	b = a; // ok
	a = a * b; //ok

	// a * b is a rvalue:
	int c = a * b; // ok rvalue on right hand side of assignment
	//a * b = 42; // error rvalue on left hand side of assignment

	// lvalues:
	int i = 42;
	i = 43;
	int *p = &i;
	int& foo();
	foo() = 42;
	int* p1 = &foo();

	// rvalues:
	int foobar();
	int j = 0;
	j = foobar(); // ok foobar is an rvalue
	//int* p2 = &foobar(); //error
	j = 42; // ok 42 is a rvalue
}

int ex_02()
{
	class Base
	{
	public:
		Base(Base const& rhs); // non-move semantics
		Base(Base&& rhs);      //     move semantics
	};

	class Derived : public Base
	{
	public:
		Derived(Derived const& rhs) : Base(rhs) {}
		Derived(Derived&& rhs) : Base(rhs) {} // wrong : rhs is an lvalue
		Derived(Derived&& rhs) : Base(std::move(rhs)) {} // wrong : rhs is an lvalue
	};
}

template <typename T, typename Arg>
std::shared_ptr<T> factory(Arg arg)
{
	return std::shared_ptr<T>(new T(arg));
}

// common solution
template <typename T, typename Arg>
std::shared_ptr<T> factory(Arg& arg)
{
	return std::shared_ptr<T>(new T(arg));
}

// factory<X>(foo()); //error
// factory<X>(41);    //error

template <typename T, typename Arg>
std::shared_ptr<T> factory(Arg const & arg)
{
	return std::shared_ptr<T>(new T(arg));
}

//A& &   -> A&
//A& &&  -> A&
//A&& &  -> A&
//A&& && -> A&&

template <typename T, typename Arg>
std::shared_ptr<T> factory(Arg&& arg)
{
	return std::shared_ptr<T>(new T(std::forward<Arg>(arg));
}

template <class S>
S&& forward(typename remove_reference<S>::type& a) noexcept
{
	return static_cast<S&&>(a);
}