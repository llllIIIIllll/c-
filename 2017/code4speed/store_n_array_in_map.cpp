#include <map>
#include <iostream>
#include <algorithm>
#include <opencv2\opencv.hpp>
#include <thread>

using namespace cv;
using namespace std;

class Test
{
public:
	static map<int, Mat(*)[2][2]> t;
};

map<int, Mat(*)[2][2]> Test::t;

void readMat()
{
	Mat end[2][2];

	// ------------------------------------------------------------------------
	for (int i = 0; i < 2; ++i)
		for (int j = 0; j < 2; ++j)
			end[i][j] = Test::t.find(2)->second[0][i][j];

	for (int i = 0; i < 2; ++i)
		for (int j = 0; j < 2; ++j)
			std::cout << end[i][j];

}

void writeMat()
{
	Mat hold[2][2];

	for (int i = 0; i < 2; ++i)
		for (int j = 0; j < 2; ++j)
			hold[i][j] = Mat::eye(Size(3, 3), CV_64FC1);

	
	Test::t.emplace(make_pair(2, &hold));
	for (int i = 0; i < 2; ++i)
		for (int j = 0; j < 2; ++j)
			hold[i][j].copyTo(Test::t.find(2)->second[0][i][j]);
}

int main()
{


	std::thread run_write_test(writeMat);

	run_write_test.join();

	for (int i = 0; i < 10; i++)
	{
		std::thread run_read_test(readMat);
		run_read_test.detach();
	}

	system("pause");

}