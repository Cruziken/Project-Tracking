#include<iostream>
#include<opencv2/core.hpp>
#include<opencv2/highgui.hpp>

//Tutorial video 1.4
cv::Mat function() {

	cv::Mat ima(500, 500, CV_8U, 50);
	return ima; //funciton that returns this image
}

int main() {
	cv::Mat image1(240, 320, CV_8U, 100); //specifiy size of image created. By default is size 0. CV_8U specify type corresponds to 1 bite pixel.
	image1.create(200, 200, CV_8U); //allocates or realoocates image properties. Deallocates previous image setting
	image1 = 200; //Question? Is this realocating image size for all dimesnions?

	cv::Mat image2(240, 320, CV_8UC3, cv::Scalar(0, 0, 255)); //create a colored image made of red pixels

	cv::Mat image3 = cv::imread("C:\\Users\\Titanium\\Pictures\\bersekr.jpg"); //Read the image and assign it the value of image3

	cv::Mat image4(image3); //
	image1 = image3;
	image3.copyTo(image2); //creates a deepcopy of an image. Create method is called on the destination image
	cv::Mat image5 = image3.clone();// Clone method creates a new identiacal method
	cv::flip(image3, image3, 1); //flip image

	cv::imshow("Image 3", image3); //display image3
	cv::imshow("Image 1", image1); //display image1
	cv::imshow("Image 2", image2); //display image2
	cv::imshow("Image 4", image4); //display image4
	cv::imshow("Image 5", image5); //display image5
	cv::waitKey(0); //Wait for user input

	cv::Mat gray = function(); //only a shallow copy will be returned to the gray image

	image1 = cv::imread("C:\\Users\\Titanium\\Pictures\\bersekr.jpg"); //read 

	image1.convertTo(image2, CV_32F, 1 / 255.0, 0.0); //Used to copy an image that may not have the same image type. Two optional parameter, scaling factor, and an offset

	//Three by three matrix of double precision floating point numbers in a three element vector. OpenCV.org has rest of equatiosn
	cv::Matx33d matrix(3.0, 2.0, 1.0,
		2.0, 1.0, 3.0,
		1.0, 2.0, 3.0);
	cv::Matx31d vector(5.0, 1.0, 3.0);
	cv::Matx31d result = matrix * vector;

	cv::waitKey(0);
	return 0;
}