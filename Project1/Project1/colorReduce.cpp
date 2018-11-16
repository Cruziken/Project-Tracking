// Tutorial Video 2.2, Color Reduction Function
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

//User provides and image and the per channel reduction factor
void colorReduce(cv::Mat image, int div = 64) {

	int nl = image.rows; //Number of pixel values per row
	int nc = image.cols * image.channels(); //number of pixels per column

	//loops through pixels and groups colors
	for (int j = 0; j < nl; j++) {
		uchar* data = image.ptr<uchar>(j); //returns the address of row number j

		//loops through column values
		for (int i = 0; i < nc; i++) {
				data[i] = data[i] / div * div + div / 2; //method for simplying number of colors to reduce complexity. returns the value for the column
			} 
	}
}
//Input image passed as constant method, image not modified)
void colorReduceIO(const cv::Mat &image, cv::Mat&result, int div = 64) {

	//Get number of rows from image
	int nl = image.rows;
	//Get number of columns from image
	int nc = image.cols;
	//Get number of channels from image. What is a channel?
	int nchannels = image.channels();

	//create an image using the same number of rows and columns and type as original
	result.create(image.rows, image.cols, image.type());

	//
	for (int j = 0; j < nl; j++) {
		const uchar* data_in = image.ptr<uchar>(j);
		uchar* data_out = result.ptr<uchar>(j); //returns the address of row number j

		for (int i = 0; i < nc*nchannels; i++) {
			data_out[i] = data_in[i] / div * div + div / 2; //method for simplying number of colors to reduce complexity. returns the value for the column
		}
	}
}
void colorReduce6(cv::Mat image, int div = 64 ){
	
	if (image.isContinuous()) {
		image.reshape(1, 1); //First is channels, 2nd is rows
	}
	int nl = image.rows; //Number of lines
	int nc = image.cols*image.channels(); // Total Number of elements per line
	 // Can tell us if an image has been padded or not
	if (image.isContinuous()) {
		nc = nc * nl; //checks for padded pixels
		nl = 1; //defines 1 d array
	}
	int n = static_cast<int>(log(static_cast<double>(div)) / log(2.0) + 0.5);

	
	uchar mask = 0xFF << n;//define a mask
	uchar div2 = div >> 1; //round the pixel value
	
	for (int j = 0; j < nl; j++) {
		uchar* data = image.ptr<uchar>(j);

		for (int i = 0; i < nc; i++) {
			*data &= mask;
			*data++ += div2;

		}
	}
}
