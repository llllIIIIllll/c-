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

	for (int i = 0; i < 20; ++i)
		pnt.push_back(Point(rand() % 1366, rand() % 768));
	
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


	vector<Point> head = pnt;
	head.erase(remove_if(head.begin(), head.end(), findHead), head.end());

	for_each(head.begin(), head.end(), [](Point x) { cout << " [ " << x.x << ", " << x.y << " ] "; });
	cout << endl;

	for (auto e : head)
	{
		vector<Point> tmp;
		tmp.push_back(e);
		pntOut.push_back(tmp);

	}

	// 按X排序
	sort(pnt.begin(), pnt.end(), PointXCom);
	pnt.erase(remove_if(pnt.begin(), pnt.end(), [&head](Point x) {return find(head.begin(), head.end(), x) != head.end(); }), pnt.end());

	for_each(pnt.begin(), pnt.end(), [](Point x) { cout << " [ " << x.x << ", " << x.y << " ] "; });
	cout << endl;

	// 分点归属的枪
	vector<Point> tmp;
	tmp.push_back(pnt.at(0));

	for (vector<Point>::iterator b = pnt.begin(); b != pnt.end() - 1; ++b)
	{
		if (pnt.at(b - pnt.begin() + 1).x - pnt.at(b - pnt.begin()).x < 30)
			tmp.push_back(pnt.at(b - pnt.begin() + 1));
		else
		{
			pntOut.push_back(tmp);
			tmp.clear();
			tmp.push_back(pnt.at(b - pnt.begin() + 1));
		}
	}

	int i = 0;
	for (auto e : pntOut)
	{
		cout << "line " << i++ << ": ";
		for_each(e.begin(), e.end(), [](Point x) { cout << " [ " << x.x << ", " << x.y << " ] "; });
		cout << endl;
	}

	imshow("test", image);

	waitKey(0);
	
}


int main()
{
	test_classify();
}