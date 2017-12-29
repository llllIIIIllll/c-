class SomeClass
{
public:
	int m_x = 0;

	void f() const
	{
		std::cout << m_x << '\n';
	}

	void g() 
	{
		m_x++;
	}

	// C++14
	void Func()
	{
		// const *this copy
		auto lambda1 =[self = *this]() { self.f(); }; 
		// non-const *this copy
		auto lambda2 =[self = *this]() mutable { self.g(); }; 
		lambda1();
		lambda2();
	}

	// C++17 
	void FuncNew()
	{
		// const *this copy
		auto lambda1 = [*this]() { f(); };
		// non-const *this copy
		auto lambda1 = [*this]() mutable { g(); };
		lambda1();
		lambda2();
	}
};
