// C++14

template<typename Type, Type n>
void Func() 
{
}

int main()
{
	Func<int, 42>();
	Func<char, 'c'>();
	return 0;
}
