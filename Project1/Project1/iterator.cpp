//Tutorial 2.3 scanning image with iterotors
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

void colorReduce10(cv::Mat image, int div = 64) {

	int n = static_cast<int>(log(static_cast<double>(div)) / log(2.0) + 0.5);
	uchar mask = 0xFF << n;
	uchar div2 = div >> 1;

	cv::Mat_<cv::Vec3b>::iterator it = image.begin<cv::Vec3b>(); // begin iterator method
	//image.begin<cv::Vec3b>()+image.cols to start at second row
	cv::Mat_<cv::Vec3b>::iterator itend = image.end<cv::Vec3b>(); //end iterator method. Returns Vec3b because it is a color mehtod.

	for ( ; it!= itend; ++it) {
		(*it)[0] &= mask;
		(*it)[0] += div2;
		(*it)[1] &= mask;
		(*it)[1] += div2;
		(*it)[2] &= mask;
		(*it)[2] += div2;
	}
	//Alternatively
	//cv::Mat_<cv::Vec3b> cimage = image;
	//cv::Mat_<cv::Vec3b>::iterator= it= cimage.begin();
	//cv::Mat_<cv::Vec3b>::iterator itend= cimage.end();
	//uchar div2 = div >> 1;
	//for (; it != itend; it++) {
	//	(*it)[0] = (*it)[0] / div * div + div2;
	//	(*it)[1] = (*it)[1] / div * div + div2;
	//	(*it)[2] = (*it)[2] / div * div + div2;
	//}
	//while(it!= itend){
	//process each pixel
	//...
	//end of pixel processing
	//++it;
	//}

	

}