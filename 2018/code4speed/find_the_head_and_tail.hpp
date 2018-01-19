#include <opencv2\opencv.hpp>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <list>
#include <algorithm>
#include <cstddef>

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

struct
{
	template <typename T>
	bool operator()(T a, T b)
	{
		return a.y > b.y;
	}
} sortByY;

template<template <typename, typename> class Container, typename T>
void Print_Container_Point(Container<T, std::allocator<T>> out)
{
	// print vector points
	for_each(out.begin(), out.end(), [](T x) {cout << " [ " << x.x << ", " << x.y << " ] "; });
	cout << endl;
}

void find_the_head_and_tail(vector<vector<Point>> &outPutPnt, vector<Point> &pnt, Mat &img)
{
	//! Init data
	// ------------------------------------------------------------------------
	//srand((unsigned)time(NULL));
	//for (int i = 0; i < 20; ++i)
	//	pnt.push_back(Point(rand() % 640, rand() % 480));

	//Mat img = Mat::zeros(Size(640, 480), CV_8UC3);
	//img.setTo(Scalar(100, 0, 0));
	//! draw points
	// ------------------------------------------------------------------------
	for_each(pnt.begin(), pnt.end(), [&img](Point x)
	{
		ostringstream os;
		os << "[ " << x.x << ", " << x.y << " ] ";
		putText(img, os.str(), x, 1, 1, Scalar(0, 255, 0), 1, 8, false);
		circle(img, x, 1, Scalar(0, 0, 255), 3, 8, 0);
	});
	//! get head points
	// ------------------------------------------------------------------------
	vector<Point> head;
	head = pnt;
	head.erase(remove_if(head.begin(), head.end(), findHead), head.end());
	// sort head points by x
	sort(head.begin(), head.end(), sortByX);
	// remove if head  points are too close
	head.erase(unique(head.begin(), head.end(), [](Point a, Point b) { return abs(a.x - b.x) < 100; }), head.end());

	cout << "Head: " << endl;
	Print_Container_Point<vector, Point>(head);

	//! get bound
	// ------------------------------------------------------------------------
	vector<pair<int, int>> bound;
	int floor, ceil;
	int frameWeight = 1280;
	for (vector<Point>::iterator it = head.begin(); it != head.end(); ++it)
	{
		floor = (it == head.begin())   ? 0           : head.at(it - head.begin() - 1).x / 2 + head.at(it - head.begin()).x / 2;
		ceil  = (it == head.end() - 1) ? frameWeight : head.at(it - head.begin() + 1).x / 2 + head.at(it - head.begin()).x / 2;
		bound.push_back(pair<int, int>(floor, ceil));
	}
	cout << "bound: " << endl;
	for_each(bound.begin(), bound.end(), [](pair<int, int> a) {cout << " [ " << a.first << ", " << a.second << " ] "; });
	cout << endl;

	//! get tail points
	// ------------------------------------------------------------------------
	vector<Point> tail;
	int i = 0;
	for (vector<Point>::iterator itH = head.begin(); itH != head.end(); ++itH, ++i)
	{
		vector<Point> tmp;
		for_each(pnt.begin(), pnt.end(), [&tmp, &bound, &i](Point a) 
		{
			if (a.x >= bound.at(i).first && a.x <= bound.at(i).second)
				tmp.push_back(a);
		}
		);
		sort(tmp.begin(), tmp.end(), sortByY);
		tail.push_back(tmp.at(0));
	}
	cout << "Tail: " << endl;
	Print_Container_Point<vector, Point>(tail);

	//! return values
	// ------------------------------------------------------------------------
	outPutPnt.push_back(head);
	outPutPnt.push_back(tail);
	//! draw lines
	// ------------------------------------------------------------------------
	while (head.begin() != head.end())
	{
		line(img, head.back(), tail.back(), Scalar(238, 238, 0), 2, 8, 0);
		head.pop_back();
		tail.pop_back();
	}
	//! Show result
	// ------------------------------------------------------------------------
	imshow("test", img);
	waitKey(0);
	system("pause");
}

//
//int main()
//{
//	vector<vector<Point>> outPutPnt;
//	vector<Point> pnt;
//	find_the_head_and_tail(outPutPnt, pnt);
//
//	return 0;
//}