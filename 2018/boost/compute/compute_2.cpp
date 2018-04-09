#include <iostream>
#include <chrono>
#include <thread>
#include <string>

#include <boost/compute/algorithm/copy.hpp>
#include <boost/compute/algorithm/accumulate.hpp>
#include <boost/compute/container/vector.hpp>
#include <boost/compute/types/fundamental.hpp>
#include <boost/compute/function.hpp>
#include <boost/compute/algorithm/transform.hpp>
#include <boost/compute/lambda/placeholders.hpp>

namespace compute = boost::compute;
using namespace std::literals::chrono_literals;
using boost::compute::lambda::_1;
using boost::compute::lambda::_2;

// use function
compute::function<int(int)> add_t =
compute::make_function_from_source<int(int)>(
	"add_t",
	"int add_t(int x) { return x + 4; }"
	);
// another
BOOST_COMPUTE_FUNCTION(int, add_four, (int x),
{
	return x + 4;
});
// usage:
// compute::transform(input.begin(), input.end(), output.begin(), add_four, queue);

int main()
{
	auto start = std::chrono::system_clock::now();
	//////////////////////////////////////////////////////////////////////////////
	using compute::float4_;
	//
	compute::device device = compute::system::default_device();
	compute::context context(device);
	compute::command_queue queue(context, device);

	float points[] = 
	{
	  1.0f,  2.0f,  3.0f, 0.0f,
	 -2.0f, -3.0f,  4.0f, 0.0f,
	  1.0f, -2.0f,  2.5f, 0.0f,
	 -7.0f, -3.0f, -2.0f, 0.0f,
	  3.0f,  4.0f, -5.0f, 0.0f
	};

	compute::vector<float4_> device_vector(5, context);

	compute::copy(
		reinterpret_cast<float4_*>(points),
		reinterpret_cast<float4_*>(points) + 5,
		device_vector.begin(),
		queue
	);

	float4_ sum = compute::accumulate(
		device_vector.begin(), device_vector.end(), float4_(0, 0, 0, 0), queue
	);

	float4_ centroid;
	for (size_t i = 0; i < 3; i++)
	{
		centroid[i] = sum[i] / 5.0f;
	}

	std::cout << "centroid: " << centroid << std::endl;

	//////////////////////////////////////////////////////////////////////////////
	auto end = std::chrono::system_clock::now();
	std::chrono::duration<double> diff = end - start;
	std::cout << "cost: " << diff.count() << std::endl;
	std::this_thread::sleep_for(100s);
}