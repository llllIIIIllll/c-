#include <opencv2\opencv.hpp>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
using namespace cv;

//! cast Container<T> ===> Container<U>
// ----------------------------------------------------------------------------
template <template <typename, typename> class Container, typename T, typename U>
Container<U, std::allocator<U>> Container_element_cast(Container<T, std::allocator<T>> in)
{
	Container<U, std::allocator<U>> out;
	for (auto e : in)
	{
		out.push_back(e);
	}
	return out;
}

//! cast Container<T> ===> Container<U>
// ----------------------------------------------------------------------------
template <template <typename, typename> class Container, typename T, typename U>
void Container_element_cast(Container<T, std::allocator<T>>& in, Container<U, std::allocator<U>>& out)
{
	out.clear();
	for (auto& e : in)
	{
		out.push_back(static_cast<U>(e));
	}
	return;
}

/// TODO:
//! cast Container<Container<T>> ===> Container<Container<U>>
// ----------------------------------------------------------------------------
//template <template <typename, typename> class Container, typename T, typename U>
//void Container_element_cast_n(Container<T, std::allocator<T>>& in, Container<U, std::allocator<U>>& out, int n)
//{
//	if (n == 1)
//	{
//		Container_element_cast(in, out);
//	}
//	else
//	{
//		Container<U, std::allocator<U>> tmp;
//		n--;
//		for (size_t i = 0; i < in.size(); ++i)
//			Container_element_cast_n(in[i], out[i], n);
//		out.push_back(tmp);
//	}
//}



//! print result
// ----------------------------------------------------------------------------
template<template <typename, typename> class Container, typename T>
void Print_Container_Point(Container<T, std::allocator<T>> out)
{
	// print vector points
	for_each(out.begin(), out.end(), [](T x) {cout << " [ " << x.x << ", " << x.y << " ] "; });
	cout << endl;
}

void test_1()
{
	// init data
	vector<Point2f> in;
	srand((unsigned)time(NULL));
	for (int i = 0; i < 5; ++i)
		in.push_back(Point2f(rand() / (double)123, rand() / (double)123));

	// cast 
	vector<Point> out1, out2;
	out1 = Container_element_cast<vector, Point2f, Point>(in);

	Container_element_cast<vector, Point2f, Point>(in, out2);


	// show result
	Print_Container_Point<vector, Point2f>(in);
	cout << "========================================" << endl;
	Print_Container_Point<vector, Point>(out1);
	cout << "========================================" << endl;
	Print_Container_Point<vector, Point>(out2);
}

void test_n()
{
	// init data
	vector<vector<Point2f>> in;
	srand((unsigned)time(NULL));
	for (int j = 0; j < 5; ++j)
	{
		vector<Point2f> tmp;
		for (int i = 0; i < 5; ++i)
			tmp.push_back(Point2f(rand() / (double)123, rand() / (double)123));
		in.push_back(tmp);
	}
	// cast 
	vector<vector<Point>> out1;

	for_each(in.begin(), in.end(), [&out1](auto e) {
		out1.push_back(Container_element_cast<vector, Point2f, Point>(e));
	});

	// show result
	Print_Container_Point<vector, Point2f>(in[0]);
	cout << "========================================" << endl;
	Print_Container_Point<vector, Point>(out1[0]);

}


int main()
{

	test_n();


	system("pause");
}