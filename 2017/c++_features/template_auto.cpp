// C++17

template<auto n>
void Func()
{
}

int main()
{
	Func<42>(); // will issue int type
	Func<'c'>(); // will issue char type
	return 0;
}
