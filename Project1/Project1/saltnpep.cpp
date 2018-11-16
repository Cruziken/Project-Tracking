#include<opencv2/core.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <random>
#include<iostream>
#include<opencv2/highgui.hpp>
//Tutorial 2.1: Accessing Pixel Values. Creating a function to add salt-and-pepprer noise. Calculating pixel's values

void salt(cv::Mat image, int n) {
	//This block of code generates the randown number for both the row and the column.
	std::default_random_engine generator;
	std::uniform_int_distribution<int> randomRow(0, image.row-1);
	std::uniform_int_distribution<int> randomCol(0, image.col-1);

	int i, j; //pixel colum i and row j

	//since n is number of pixels we want to overwrite with white values. Assigns the value of 255 to n random pixels
	for (int k = 0; k < n; k++) {
		i = randomCol(generator); //generates random number for column value
		j = randomRow(generator); //generates random number fo row value
		
		//Loop replaces pixel type with white color. If gray it goes to first part. If color goes in else if statement.
		if (image.type() == CV_8UC1) {
			image.at<uchar>(j, i) = 255; // for gray image.
		}
		else if (image.type() == CV_8UC3) {
			//for color image. Specificy white for rbg 
			image.at<cv::Vec3b>(j, i)[0] = 255; //blue. Vec3b is vector of three unsigned characters
			image.at<cv::Vec3b>(j, i)[1] = 255; //green
			image.at<cv::Vec3b>(j, i)[2] = 255; //red
			//
			//image.at<cv::Vec3b>(j, i) = cv::Vec3b(255, 255, 255); // Shortens the command for the people
		}
	}
}

void salty()
{
	cv::Mat image = cv::imread("C:\\Users\\Titanium\\Pictures\\6man.jpg"); // create an image
    salt(image, 3000); //pass image into function above

	cv::namedWindow("Image"); //create Window for image to be displayed in
	cv::imshow("Image", image); //Display image in the window created

	cv::waitKey(); //Wait for user input to end the program
	 // return 0 upon closure of the program.


}
