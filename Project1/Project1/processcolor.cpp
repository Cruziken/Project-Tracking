#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#include "C:\\Users\\Titanium\\Downloads\\opencv-2-cookbook-src-master\\opencv-2-cookbook-src-master\\Chapter 03\\colordetector.h"

int main()
{
	ColorDetector cdetect;

	cv::Mat image = cv::imread("boldt.jpg");
	if (image.empty()) return 0;

	cdetect.setTargetColor(230, 190, 130); //set the output parameters

	cv::namedWindow("result");
	cv::Mat result = cdetect.process(image);
	cv::imshow("result", result);

	cv::waitKey();
	return 0;
}

