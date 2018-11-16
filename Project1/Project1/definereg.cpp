#include<opencv2/core.hpp>
#include<iostream>
#include<opencv2/highgui.hpp>
//Tutorial video 1.5
int tut3() {
	cv::namedWindow("Image"); //creates a window named Image
	cv::Mat image = cv::imread("C:\\Users\\Titanium\\Pictures\\bersekr.jpg"); //Read and create an image 
	cv::Mat logo = cv::imread("C:\\Users\\Titanium\\Pictures\\mach2.jpg"); //Read and create an image
	
	cv::Mat imageROI(image, cv::Rect(image.cols-logo.cols, image.rows-logo.rows, logo.cols, logo.rows)); //Region of Interest. Gets logo dimensions. Cv Rect instance describes rectangular area by describing the the position of the upper left corner (first 2 parameters), and the hieght, width and size are given in last two parameters 
	
	logo.copyTo(imageROI); //Copy the logo into the image

	cv::imshow("Image", image); //dislay imputed image
	cv::waitKey(0); //Wait for user key to end program

	image = cv::imread("C:\\Users\\Titanium\\Pictures\\bersekr.jpg");

	imageROI = image(cv::Rect(image.cols - logo.cols, image.rows - logo.rows, logo.cols, logo.rows));
	imageROI = image(cv::Range(image.rows - logo.rows, image.rows), cv::Range(image.cols - logo.cols, image.cols));// ROI can be defined by two ranges. Row and column ranges.

	//cv::Mat imageROI= image.rowRange(start,end); //If you want to define an ROI made up of some rows of an image
	//cv::Mat imageROI = image.colRange(start,end); //If you want to define an ROI made up or some rows 

	cv::Mat mask(logo); //Mask that limits applicability function or method. 
	logo.copyTo(imageROI, mask); //Copy only the white portion of the code into the image

	//Video stopped at 3:26

	return 0;

}