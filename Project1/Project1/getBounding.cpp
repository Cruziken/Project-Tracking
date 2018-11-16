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
Mat src_gray;
int thresh = 100;


/**
 * @function thresh_callback
 */
void thresh_callback(int, void*)
{
	//! [Canny]
	/// Detect edges using Canny
	//Initialize matrix canny_output
	Mat canny_output;
	//Call Canny function that translates src_gray into canny_output to detect edges from
	Canny(src_gray, canny_output, thresh, thresh * 2);
	//! [Canny]

	//! [findContours]
	/// Find contours
	//Initialize vector that will contain contour points
	vector<vector<Point> > contours;
	//Find image contours in canny_output 
	findContours(canny_output, contours, RETR_TREE, CHAIN_APPROX_SIMPLE);
	//! [findContours]

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
	for (size_t i = 0; i < contours.size(); i++)
	{
		// Function approximates curve of contour
		approxPolyDP(contours[i], contours_poly[i], 3, true);
		// Finds minimum enclosing circle of contour points
		minEnclosingCircle(contours_poly[i], centers[i], radius[i]);
		//Define boundRect of ROI
		boundRect[i] = boundingRect(Mat(contours_poly[i]));
	}
	//! [allthework]

	//! [zeroMat]
	Mat drawing = Mat::zeros(canny_output.size(), CV_8UC3);
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
	cout << mc[2];
	//Export coordinate values to excel file
	exportCsv(mc[2]);
	//Export bounding box for video ROI
	readVid(boundRect[2]);
	///Draw the location of the centroid onto the image
	//Defines color that the circle will use
	Scalar color = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
	//Creates circle of centriod location and pastes onto the drawing. 
	circle(drawing, mc[2], 4, color, -1, 8, 0);
	//! [forContour]
	/// Draw polygonal contour + bonding rects + circles
	for (size_t i = 0; i < contours.size(); i++)
	{
		// Defines color for circle bounding the contour points
		Scalar color = Scalar(rng.uniform(0, 256), rng.uniform(0, 256), rng.uniform(0, 256));
		//
		circle(drawing, centers[i], (int)radius[i], color, 2);
	}
	//! [forContour]

	//! [showDrawings]
	/// Show in a window
	imshow("Contours", drawing);
	//! [showDrawings]


	// Create Exceptions that throw errors within code.