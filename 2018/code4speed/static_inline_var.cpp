class MyClass
{
private:
	static int s_anInt;
	static std::string s_aString;
};

// This is needed
int MyClass::s_anInt = 42;
std::string MyClass::s_aString = "Hello World!";

// in c++ 17
class MyClass
{
private:
	static inline int s_anInt = 42;
	static inline std::string s_aString = "Hello World!";
};

// But this function is not support by Visual C++ 




class CSingleton final
{
public:
	static CSingleton& GetInstance();
	
private:
	CSingleton() = default;
	~CSingleton() = default;
	
	CSingleton(const CSingleton&) = delete;
	CSingleton& operator=(const CSingleton&) = delete;
	CSingleton(CSingleton&&) = delete;
	CSingleton& operator=(CSingleton&&) = delete;
};

CSingleton& CSingleton::GetInstance()
{
	static CSingleton instance;
	return instance;
}