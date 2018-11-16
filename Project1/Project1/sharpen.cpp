//Tutorial 2.5 Sharpening an image
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

void sharpen(const cv::Mat &image, cv::Mat &result) {
	result.create(image.size(), image.type());
	int nchannels = image.channels();

	for (int j = 1; j < image.rows - 1; j++) {

		const uchar* previous = image.ptr<const uchar>(j - 1); //Neighboring pixels essentially: this is previous pixel
		const uchar* current = image.ptr<const uchar>(j); // Current pixel in image
		const uchar* next = image.ptr<const uchar>(j + 1); //The next pixel in the sequence
		uchar* output = result.ptr<uchar>(j);

		for (int i = nchannels; i < (image.cols - 1)*nchannels; i++) {
			*output++ = cv::saturate_cast<uchar>(5 * current[i] - current[i - nchannels] - current[i + nchannels] - previous[i] - next[i]);
		}
	}
	result.row(0).setTo(cv::Scalar(0)); //sets border pixel rows to zero
	result.row(result.rows - 1).setTo(cv::Scalar(0));
	result.col(0).setTo(cv::Scalar(0)); //sets column pixel rows to zero
	result.col(result.cols - 1).setTo(cv::Scalar(0));

}
void sharpen2D(const cv::Mat &image, cv::Mat &result) {
	cv::Mat kernel(3, 3, CV_32F, cv::Scalar(0));
	//Kernel defines a filter that is defined to an image
	kernel.at<float>(1, 1) = 5.0;
	kernel.at<float>(0, 1) = -1.0;
	kernel.at<float>(2, 1) = -1.0;
	kernel.at<float>(1, 0) = -1.0;
	kernel.at<float>(1, 2) = -1.0;

	//Functioned is called with kernal and image and returns filtered image
	cv::filter2D(image, result, image.depth(), kernel);
}