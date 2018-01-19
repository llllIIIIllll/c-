#include <opencv2\opencv.hpp>
#include <iostream>
#include <algorithm>
#include <vector>

using namespace cv;
using namespace std;

void find_rect()
{
	vector<Rect> rect;
	//! Init data
	// ------------------------------------------------------------------------
	srand((unsigned)time(NULL));
	for (int i = 0; i < 20; ++i)
	{
		Point tmp = Point(rand() % 640, rand() % 480);
		Rect t = Rect(tmp, Point(tmp.x + rand() % 60, tmp.y + rand() % 60));
		rect.push_back(t);
	}
	Mat img = Mat::zeros(Size(640, 480), CV_8UC3);
	img.setTo(Scalar(0, 0, 0));
	//! draw rect
	// ------------------------------------------------------------------------
	for_each(rect.begin(), rect.end(), [&img](auto x)
	{
		rectangle(img, x, Scalar(200, 200, 200), 1, 8, 0);
	});

	//
	rect.at(0);

	//! Show result
	// ------------------------------------------------------------------------
	imshow("test", img);
	waitKey(0);
	system("pause");
}

int main()
{
	find_rect();
	return 0;
}