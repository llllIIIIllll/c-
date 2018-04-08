#include <boost/compute/core.hpp>
#include <boost/compute/algorithm/copy.hpp>
#include <boost/compute/algorithm/transform.hpp>
#include <boost/compute/container/vector.hpp>
#include <boost/compute/functional/math.hpp>

#include <iostream>
#include <thread>
#include <vector>
#include <chrono>

namespace compute = boost::compute;
using namespace std::literals::chrono_literals;

void print_device_platform_info()
{
	// get the default device
	compute::device device = compute::system::default_device();

	// print the device's name and platform
	std::cout << "hello from " << device.name();
	std::cout << " (platform: " << device.platform().name() << ")" << std::endl;
}

void transferring_data()
{
	auto start = std::chrono::system_clock::now();
	///////////////////////////////////////////////////////////////////////////////
	compute::device device = compute::system::default_device();
	compute::context context(device);
	compute::command_queue queue(context, device);

	// create data array on host
	int host_data[] = { 1, 3, 5, 7, 9 };

	// create vector on device
	compute::vector<int> device_vector(5, context);
	
	// copy host to device
	compute::copy(
		host_data, host_data + 5, device_vector.begin(), queue
	);

	// create vector on host
	std::vector<int> host_vector(5);
	
	// copy data back to host
	compute::copy(
		device_vector.begin(), device_vector.end(), host_vector.begin(), queue
	);
	///////////////////////////////////////////////////////////////////////////////
	auto end = std::chrono::system_clock::now();
	std::chrono::duration<double> diff = end - start;
	std::cout << " cost: " << diff.count() << std::endl;
}

void float_transferred()
{
	auto start = std::chrono::system_clock::now();
	///////////////////////////////////////////////////////////////////////////////
	compute::device device = compute::system::default_device();
	compute::context context(device);
	compute::command_queue queue(context, device);

	std::vector<float> host_vector(10000);
	std::generate(host_vector.begin(), host_vector.end(), rand);

	compute::vector<float> device_vector(host_vector.size(), context);
	compute::copy(
		host_vector.begin(), host_vector.end(), device_vector.begin(), queue
	);
	
	// calculate the square-root of each element in-place
	compute::transform(
		device_vector.begin(),
		device_vector.end(),
		device_vector.begin(),
		compute::sqrt<float>(),
		queue
	);

	// copy values back
	compute::copy(
		device_vector.begin(), device_vector.end(), host_vector.begin(), queue
	);
	///////////////////////////////////////////////////////////////////////////////
	auto end = std::chrono::system_clock::now();
	std::chrono::duration<double> diff = end - start;
	std::cout << " cost: " << diff.count() << std::endl;
}

int main()
{
	//print_device_platform_info();

	//transferring_data();

	float_transferred();

	std::this_thread::sleep_for(100s);
	return 0;
}