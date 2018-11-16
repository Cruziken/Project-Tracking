#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
//#include <grabCut>

int main() {
	cv::Mat image = cv::imread("C:\\Users\\Titanium\\Pictures");
	if (!image.data)
		return 0;
	cv::Rect rectangle(50, 25, 210, 180);

	cv::Mat result;
	cv::Mat bgModel, fgModel;

	cv::grabCut(image, result, rectangle, bgModel, fgModel, 5, cv::GC_INIT_WITH_RECT);

	cv::compare(result, cv::GC_PR_FGD, result, cv::CMP_EQ);

	cv::Mat foreground(image.size(), CV_8UC3, cv::Scalar(255, 255, 255));

	result = result & 1;
	cv::Mat foreground(image.size(), CV_8UC3, cv::Scalar(255, 255, 255));
	image.copyTo(foreground, result);

	cv::rectangle(image, rectangle, cv::Scalar(255, 255, 255), 1);
}