#include <opencv2\opencv.hpp>
#include <Windows.h>
#include <iostream>
#include <sstream>
#include <string>
#include <thread>

using namespace cv;
using namespace std;

static Mat showMat[2];
void readAFrame(string s)
{
	int j = 0;
	//namedWindow(s, CV_WINDOW_AUTOSIZE);
	Mat out;
	while (true)
	{
		j++;
		ostringstream os;
		os << s << "_" << j;
		out = imread("0000.jpg");
		putText(out, os.str(), Point(10, 10), 1, 1, Scalar(0, 255, 0), 1, 8, false);

		if (s == "a")
			out.copyTo(showMat[0]);
		else
			out.copyTo(showMat[1]);

		//imshow(s, out);
		//waitKey(1);
	}
}

int main()
{
	string s1 = "test1";
	string s2 = "test2";

	string s[2] = { "a", "b" };
	//#pragma omp parallel for
	for (int i = 0; i < 2; ++i)
	{
		thread test(&readAFrame, s[i]);
		test.detach();
	}

	namedWindow(s[0], CV_WINDOW_AUTOSIZE);
	namedWindow(s[1], CV_WINDOW_AUTOSIZE);
	while (true)
	{
		if (showMat[0].empty() || showMat[1].empty())
			continue;
		imshow(s[0], showMat[0]);
		imshow(s[1], showMat[1]);
		waitKey(1);
	}
	Sleep(1000000);
}