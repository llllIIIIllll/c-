#include <iostream>

#include <rttr/registration.h>

static void f() { std::cout << "Hello World" << std::endl; }
using namespace rttr;

RTTR_REGISTRATION
{
	using namespace rttr;
registration::method("f", &f);
}

int main()
{
	type::invoke("f", {});
}
// outputs: "Hello World