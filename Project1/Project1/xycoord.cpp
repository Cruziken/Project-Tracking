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
//VideoCapture video("C:\\Users\\Titanium\\source\\repos\\Project1\\videos\\dot.mp4\n");
void readVid(Rect2d bbox);
Mat frame;
Mat src_gray;
int thresh = 100;
RNG rng(12345);                              

/// Function header
void thresh_callback(int, void*);
void exportCsv(Point2f mu);

/**
 * @function main
 */
/**int main(int argc, char** argv)
{
	
	//! [setup]
	/// Load source video

	// set input video
	//VideoCapture video("C:\\Users\\Titanium\\source\\repos\\Project1\\videos\\dot.mp4\n");

	// Exit if video is not opened
	if (!video.isOpened())
	{
		cout << "Could not read video file" << endl;
		return 1;
	}

	// Read first frame 
	bool ok = video.read(frame);

	
	/// Convert image to gray and blur it
	cvtColor(frame, src_gray, COLOR_BGR2GRAY);
	//Smooths the image using a kernel
	blur(src_gray, src_gray, Size(3, 3));
	//! [setup]

	//! [createWindow]
	/// Create Window
	//Create char holding window name
	const char* source_window = "Source";
	//Name window
	namedWindow(source_window);
	//Show image of frame matrix
	imshow(source_window, frame);
	//! [createWindow]
	
	//Call thresh_callback function
	thresh_callback(0, 0);

	waitKey();
	return 0;
}
*/

/**
 * @function thresh_callback
 */
/**
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
}
*/
/**
 * @function exportCsv
 */
void exportCsv(Point2f mc) {
	//Initilize a data stream to myFile 
	ofstream myFile;
	//Stream data to testing.csv
	myFile.open("testing.csv");
	
	//Initialize a data stream to stream 
	stringstream myPoint;
	//store x and y coordinates of 2-D vector in stream 
	myPoint << mc.x << "," << mc.y;
	//Pass the 2-D vector ( (x,y) coordinates) to excel file testing.csv
	myFile << "X Y" << "," << myPoint.str();
}


/**
 * @function readVid
 */
/**
void readVid(Rect2d bbox){
// create a tracker object
Ptr<Tracker> tracker = TrackerKCF::create();
// Display bounding box. 
rectangle(frame, bbox, Scalar(255, 0, 0), 2, 1);

imshow("Tracking", frame);
tracker->init(frame, bbox);

while (video.read(frame))
{
	// Start timer
	double timer = (double)getTickCount();

	// Update the tracking result
	bool ok = tracker->update(frame, bbox);

	// Calculate Frames per second (FPS)
	float fps = getTickFrequency() / ((double)getTickCount() - timer);

	if (ok)
	{
		// Tracking success : Draw the tracked object
		rectangle(frame, bbox, Scalar(255, 0, 0), 2, 1);
		//Put code to calculate the centroid of rectangle here

	}
	else
	{
		// Tracking failure detected.
		putText(frame, "Tracking failure detected", Point(100, 80), FONT_HERSHEY_SIMPLEX, 0.75, Scalar(0, 0, 255), 2);
	}

	// Display tracker type on frame
	putText(frame, " Tracker", Point(100, 20), FONT_HERSHEY_SIMPLEX, 0.75, Scalar(50, 170, 50), 2);

	// Display FPS on frame
	putText(frame, "FPS : ", Point(100, 50), FONT_HERSHEY_SIMPLEX, 0.75, Scalar(50, 170, 50), 2);

	// Display frame.
	imshow("Tracking", frame);

	// Exit if ESC pressed.
	int k = waitKey(1);
	if (k == 27)
	{
		break;
	}

}
}
*/