#include <boost/mpl/transform.hpp>

template <class F, class X>
struct twice
{
	typedef typename F::template apply<X>::type once;
	typedef typename F::template apply<once>::type type;
};

// or use forward
template <class F, class X>
struct twice : F::template apply<typename F::template apply<X>::type>
{};

// 
template <class UnaryMetaFuhnctionClass, class Arg>
struct apply1 : UnaryMetaFuhnctionClass::template apply<Arg>
{};

template <class F, class X>
struct twice : apply1<F, typename apply1<F, X>::type>
{};
