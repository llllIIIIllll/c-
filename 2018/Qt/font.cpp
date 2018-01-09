#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;

int main()
{
	Mat image = imread("0000.jpg", 199);

	//载入后先显示
	cvNamedWindow("test", WINDOW_NORMAL);

	QtFont font = fontQt("Times", 10, Scalar(0, 255, 0), 50, 0, 0);

	addText(image, "世界", Point(20, 20), font);

	imshow("test", image);
	waitKey(0);

	system("pause");
}