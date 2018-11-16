#include "opencv2/imgcodecs.hpp"
#include <opencv2/core/utility.hpp>
#include "opencv2/highgui.hpp"
#include <opencv2/tracking.hpp>
#include <opencv2/videoio.hpp>
#include "opencv2/imgproc.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>



using namespace cv;
using namespace std;
Mat sorc_gray;
//Initialize matrix canny_output
Mat can_output;
//Initialize vector that will contain contour points
vector<vector<Point> > contours;
int threshit = 100;
void thresh_callback(int, void*);

/**
 * @function thresh_callback
 */
void defContours(Mat myFrame)
{

	/// Convert image to gray and blur it
	cvtColor(myFrame, sorc_gray, COLOR_BGR2GRAY);
	//Smooths the image using a kernel
	blur(sorc_gray, sorc_gray, Size(3, 3));
	//! [setup]
	//! [createWindow]
	/// Create Window
	//Create char holding window name
	const char* source_window = "Source";
	//Name window
	namedWindow(source_window);
	//Show image of frame matrix
	imshow(source_window, myFrame);
	//! [Canny]
	/// Detect edges using Canny
	//Initialize matrix canny_output
	//Mat canny_output;
	//Call Canny function that translates src_gray into canny_output to detect edges from
	Canny(sorc_gray, can_output, threshit, threshit * 2);
	//! [Canny]

	//! [findContours]
	/// Find contours
	//Initialize vector that will contain contour points
	//vector<vector<Point> > contours;
	//Find image contours in canny_output 
	findContours(can_output, contours, RETR_TREE, CHAIN_APPROX_SIMPLE);
	//! [findContours]
}

/**
 * @function getBound()
 */
Rect2d getBound() {

	//! [allthework]
	/// Approximate contours to polygons + get bounding rects and circles
	//Get vector of contour size
	vector<vector<Point> > contours_poly(contours.size());
	//Initalize point of contour center
	vector<Point2f>centers(contours.size());
	// Intialize value of contour radious
	vector<float>radius(contours.size());
	// Initialize bbox for ROI
	vector<Rect2d> boundRect(contours.size());
	cout << contours.size();
	for (size_t i = 0; i < contours.size(); i++)
	{
		// Function approximates curve of contour
		approxPolyDP(contours[i], contours_poly[i], 3, true);
		// Finds minimum enclosing circle of contour points
		minEnclosingCircle(contours_poly[i], centers[i], radius[i]);
		//Define boundRect of ROI
		Mat dst;
		boundRect[i] = boundingRect(Mat(contours_poly[i]));
	}
	//! [allthework]
	//! [zeroMat]
	//vector<Rect2d> addRect(3 : 3);
	//vector<Rect2d> sumRect = addRect + boundRect[2];
	//Export bounding box for video ROI
	//manual addition to rectangle dimensions.
	Rect2d bigger_rect = boundRect[2];
	//Offset center of ROI by 25 pixels
	Point2d inflationPoint(-25, -25);
	//Inflate size by to 50 pixels width and height
	Size2d inflationSize(50, 50);
	//Offset origin to center ROI
	bigger_rect += inflationPoint;
	//Increase rectangle size to 50
	bigger_rect += inflationSize;
	//Return Rectangle
	return (bigger_rect);
	

	// Create Exceptions that throw errors within code.
}


/**
* @function getCentroid()
*/
Point2f getCentroid() {

	//! [zeroMat]
	Mat drawing = Mat::zeros(can_output.size(), CV_8UC3);
	//! [zeroMat]
	/// [Get the moments]
	//Initialize vector that contains countor location
	vector<Moments> mu(contours.size());

	//Calculate the monment of the contours
	for (int i = 0; i < contours.size(); i++)
	{
		mu[i] = moments(contours[i], false);

	}

	///  Get the mass centers:
	//Initialize vector that containes contour size
	vector<Point2f> mc(contours.size());
	//Initialize matrix containing contour ROI
	vector<Mat> contour_rois;

	//Calculate the first moment to get centroid of the contour.
	for (int i = 0; i < contours.size(); i++)
	{
		mc[i] = Point2f(mu[i].m10 / mu[i].m00, mu[i].m01 / mu[i].m00);
	}

	//Output centroid, x,y coordinate of the contour in relation to "drawing" matrix as an output
	//cout << mc[2];
	
	return mc[2];
}