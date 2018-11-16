#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <math.h>
//Transformation function that will create a wavy effect on the image
void wave(const cv::Mat &image, cv::Mat &result) {
	cv::Mat srcX(image.rows, image.cols, CV_32F);
	cv::Mat srcY(image.rows, image.cols, CV_32F);

	for (int i = 0; i < image.rows; i++) {
		for (int j = 0; j < image.cols; j++) {
			srcX.at<float>(i, j) = j;
			srcY.at<float>(i, j) = i + 3 * sin(j / 6.0);
			//or
			//srcX.at<float>(i,j) = image.col-j-1;
			//src.at<float>(i,j)= i;
		}
	}
	cv::remap(image, result, srcX, srcY, cv::INTER_LINEAR); //produces new version of the image and changes it

}
