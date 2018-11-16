#include <vector>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

int main()
{
	cv::Mat image1;
	cv::Mat image2;

	image1 = cv::imread("boldt.jpg");
	image2 = cv::imread("rain.jpg");
	if (!image1.data)
		return 0;
	if (!image2.data)
		return 0;

	cv::namedWindow("Image 1");
	cv::imshow("Image 1", image1);
	cv::namedWindow("Image 2");
	cv::imshow("Image 2", image2);

	cv::Mat result;

	cv::addWeighted(image1, 0.7, image2, 0.9, 0., result); //add two images together

	cv::namedWindow("result");
	cv::imshow("result", result);

	result = 0.7*image1 + 0.9*image2; // add two images together
	cv::namedWindow("result with overloaded operators");
	cv::imshow("result with overloaded operators", result);

	image2 = cv::imread("rain.jpg", 0);

	std::vector<cv::Mat> planes;

	cv::split(image1, planes);
	planes[0] += image2;

	cv::merge(planes, result); //Its creates a color image out of 3 1 channels

	cv::namedWindow("Result on blue channel");
	cv::imshow("Result on blue channel", result);
}