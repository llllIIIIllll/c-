#include <iostream>
#include <iterator>
#include <algorithm>
#include <type_traits>
#include <vector>

#include <opencv2\opencv.hpp>
using namespace std;
using namespace cv;

template<class A>
typename std::enable_if< std::rank<A>::value == 1 >::type
print_1d(const A& a)
{
	copy(a, a + std::extent<A>::value,
		std::ostream_iterator<typename std::remove_extent<A>::type>(std::cout, " "));
	std::cout << '\n';
}

template <class inputContainer, typename T>
void decltype_container(inputContainer in)
{
	for (auto& e : in)
	{
		if (typeid(e).name() == typeid(T).name())
			std::cout << "success" << std::endl;

	}
}

void test_print_1d()
{
	int a[][3] = { { 1,2,3 },{ 4,5,6 } };
	//  print_1d(a); // compile-time error
	//std::cout << std::is_same_v<decltype(in), int> << std::endl;
	//std::cout << std::is_same_v<decltype(in), std::vector<int>> << std::endl;
	//std::cout << std::is_same_v<decltype(in), std::vector<std::vector<int>>> << std::endl;
}

void test_decltype()
{
	vector<vector<Point3f>> in;
	vector<Point3f> in2;
	in2.push_back(Point3f(123.4, 223.0, 32.67));
	in.push_back(in2);

	decltype_container<vector<Point3f>, Point3f>(in2);
	decltype_container<vector<vector<Point3f>>, Point3f>(in);

}

int main()
{
	test_decltype();
	system("pause");
	return 0;
}
