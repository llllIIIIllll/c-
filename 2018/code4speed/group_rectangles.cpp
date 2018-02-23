#include <opencv2\opencv.hpp>
#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>

using namespace cv;
using namespace std;

struct
{
	bool operator()(Point a)
	{
		return a.y > 100;
	}
}findHead;

struct
{
	bool operator()(Point a, Point b)
	{
		return a.x < b.x;
	}
}PointXCom;

struct
{
	bool operator()(Point a, Point b)
	{
		return a.y < b.y;
	}
}PointYCom;

void test_classify()
{
	vector<Point> pnt;
	vector<vector<Point>> pntOut;
	vector<Rect> rect_v;

	srand(time(NULL));

	for (int i = 0; i < 20; ++i)
	{
		pnt.push_back(Point(rand() % 1366, rand() % 768));
		rect_v.push_back(Rect(pnt.back(), Point(pnt.back().x + rand() % 300, pnt.back().y + rand() % 300)));
	}
	
	cv::Mat image = cv::Mat::zeros(768, 1366, CV_8UC3);
	image.setTo(cv::Scalar(100, 0, 0));

	// 显示 点 和 坐标
	for_each(pnt.begin(), pnt.end(), [&image](Point x) 
	{
		circle(image, x, 5, cv::Scalar(0, 0, 255), 2, 8, 0);  
		ostringstream position;
		position << x.x << ", " << x.y;
		putText(image, position.str(), x, 1, 1, Scalar(0, 255, 0), 1, 8, false);
	});

	for_each(rect_v.begin(), rect_v.end(), [&image](Rect r)
	{
		rectangle(image, r, Scalar(0, 255, 0), 1, 8, 0);
	});


	groupRectangles(rect_v, 1, 0.9);

	for_each(rect_v.begin(), rect_v.end(), [&image](Rect r)
	{
		rectangle(image, r, Scalar(0, 0, 255), 1, 8, 0);
	});

	

	imshow("test", image);

	waitKey(0);
	
}


int main()
{
	test_classify();
}