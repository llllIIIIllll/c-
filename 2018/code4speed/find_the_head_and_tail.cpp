#include <opencv2\opencv.hpp>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;
using namespace cv;

struct
{
	template <typename T>
	bool operator()(T a)
	{
		return a.y > 50;
	}
}findHead;

struct
{
	template <typename T>
	bool operator()(T a, T b)
	{
		return a.x < b.x;
	}
} sortByX;

template<template <typename, typename> class Container, typename T>
void Print_Container_Point(Container<T, std::allocator<T>> out)
{
	// print vector points
	for_each(out.begin(), out.end(), [](T x) {cout << " [ " << x.x << ", " << x.y << " ] "; });
	cout << endl;
}

void find_the_head_and_tail()
{
	//! Init data
	// ------------------------------------------------------------------------
	vector<vector<Point>> outPutPnt;
	vector<Point> pnt;
	srand((unsigned)time(NULL));
	for (int i = 0; i < 20; ++i)
		pnt.push_back(Point(rand() % 640, rand() % 480));

	Mat img = Mat::zeros(Size(640, 480), CV_8UC3);
	img.setTo(Scalar(100, 0, 0));

	for_each(pnt.begin(), pnt.end(), [&img](Point x)
	{
		ostringstream os;
		os << "[ " << x.x << ", " << x.y << " ] ";
		putText(img, os.str(), x, 1, 1, Scalar(0, 255, 0), 1, 8, false);
		circle(img, x, 1, Scalar(0, 0, 255), 3, 8, 0);
	});
	//! Start algotirhm
	// ------------------------------------------------------------------------
	vector<Point> head;
	head = pnt;
	// get head points
	head.erase(remove_if(head.begin(), head.end(), findHead), head.end());
	// sort head points by x
	sort(head.begin(), head.end(), sortByX);
	// remove if head  points are too close
	head.erase(unique(head.begin(), head.end(), [](Point a, Point b) { return abs(a.x - b.x) < 100; }), head.end());
	Print_Container_Point<vector, Point>(head);

	//! Show result
	// ------------------------------------------------------------------------
	imshow("test", img);
	waitKey(0);
	system("pause");
}

int main()
{
	find_the_head_and_tail();

	return 0;
}