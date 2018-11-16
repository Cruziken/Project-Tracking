// CannyStill.cpp

#include<opencv2/opencv.hpp>

#include<opencv2/core.hpp>
#include<iostream>
#include<opencv2/highgui.hpp>           // may have to modify this line if not using Windows

///////////////////////////////////////////////////////////////////////////////////////////////////

//Tutorial 1.2
int functionIt() {
	
	cv::Mat image; //creates cv image of the Mat class. Variable that holds the image
	std::cout << "This image is" << image.rows << "x" << image.cols << std::endl; //Creates an image of the size 0 by 0. 

	image = cv::imread("C:\\Users\\Titanium\\Pictures\\bersekr.jpg"); //Reads image from file. Can also make gray level image that is useful in a lot of computer vision algoritms require them c::imread("berserk", cv::IMREAD_GRAYSCALE)

	//Check if image is read. Returns true if no image data is allocated
	if (image.empty()) {

	}
	cv::namedWindow("Original Image"); //window where you want to display the images
	cv::imshow("Original Image", image); //specify image to be shown on special window

	cv::Mat result; //create an empty image
	cv::flip(image, result, 1);//specified image change. 1 represents positive horizonatl axes. 0 represents vertical axes. -1 represents both horizontal and vertical axes

	cv::namedWindow("Output Image");// window where modified image is displayed
	cv::imshow("Output Image", result); //displayed flipped image

	cv::imwrite("C:\\Users\\Titanium\\Pictures\\bersekr.jpg", result); //Save processed image to replace injected image
	cv::waitKey(); //wait for user key to end program


	return 0; //return 0 if successfull
}