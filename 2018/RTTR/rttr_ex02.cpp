#include <rttr/registration.h>

#include <cstdlib>
#include <cmath>
#include <iostream>
#include <thread>

RTTR_REGISTRATION
{
	using namespace rttr;
	registration::method("atoi", &atoi);
	registration::method("pow", select_overload<float(float, float)>(&pow))
				 .method("pow", select_overload<double(double, double)>(&pow));
	registration::method("sin", select_overload<float(float)>(&sin))
				 .method("sin", select_overload<double(double)>(&sin));
}

using namespace rttr;
int main()
{
	// let asume we have registered the pow function:
	// double pow(double base, double exp);
	// option 1
	variant return_value = type::invoke("pow", { 9.0, 2.0 });
	if (return_value.is_valid() && return_value.is_type<double>())
		std::cout << return_value.get_value<double>() << std::endl;

	// option 2
	method meth = type::get_global_method("pow");
	if (meth) // check if the function was found
	{
		return_value = meth.invoke({}, 9.0, 3.0);
		// invoke with empty instance
		if (return_value.is_valid() && return_value.is_type<double>())
			std::cout << return_value.get_value<double>() << std::endl;
	}

	using namespace std::literals::chrono_literals;
	std::this_thread::sleep_for(100s);
}