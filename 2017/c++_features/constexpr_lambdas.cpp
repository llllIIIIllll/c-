// C++17

constexpr int Func(int x)
{
	auto f = [x]() { return x * x; };
	return x + f();
}

int main()
{
	constexpr int v = Func(10);
	static_assert(v == 110);

	return 0;
}

