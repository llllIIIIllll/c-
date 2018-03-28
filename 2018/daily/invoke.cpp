#include <functional>

template <typename Callable>
class Proxy
{
	Callable c;
public:
	Proxy(Callable c) : c(c) {}
	
	template <class... Args>
	decltype(auto) operator()(Args&&... args)
	{
		//...
		return std::invoke(std::forward<Args>(args)...);
	}
};


auto add = [](int x, int y)
{
	return x + y;
};

Proxy<decltype(add)> p{ add };

int main()
{
	p(1, 2);
}