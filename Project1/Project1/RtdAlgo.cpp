#include "opencv2/imgcodecs.hpp"
#include <opencv2/core/utility.hpp>
#include "opencv2/highgui.hpp"
#include "opencv2/tracking.hpp"
#include <opencv2/videoio.hpp>
#include "opencv2/imgproc.hpp"
#include "functions.h"

using namespace cv;
using namespace std;


class BoundingBox;
class Coordinates;
void defContours(Mat frame);
void exportExcel(Point2f mc, float time);
string vidname = "bentest.avi";
VideoCapture video(vidname);
GLFWwindow* makeVid(string myVideo);
void myAnimate(GLFWwindow* myWin);
//void makeCoords(Point2f mc);
Rect2d getBound();
Point2f getCentroid();
//VideoCapture video(string Filename);
// create a tracker object
Ptr<Tracker> tracker = TrackerKCF::create();

int main(int argc, char** argv)
{

    GLFWwindow* myWin = makeVid(vidname);
	myAnimate(myWin);
	/**
    Mat frame;
	// Exit if video is not opened

	if (!video.isOpened())
	{
		cout << "Could not read video file" << endl;
		return 1;
	}

	// Read first frame
	bool ok = video.read(frame);
	//Define Contours for first frame
	defContours(frame);
	//Calculate the ROI of circle from image
	Rect2d bbox = getBound();
	///Next two lines get the center of the circle based off the cirle which is a float. 
	///I believe its a more accurate center. Ask Nour
	//Point2f centroids = getCentroid();
	//exportExcel(centroids);
	rectangle(frame, bbox, Scalar(255, 0, 0), 2, 1);
	imshow("Tracking", frame);
	tracker->init(frame, bbox);
	float frame_number = 0;
	while (video.read(frame))
	{	
		
		// Start timer
		double timer = (double)getTickCount();
		float tofvid = frame_number / 20;
		// Update the tracking result
		bool ok = tracker->update(frame, bbox);
		// Calculate Frames per second (FPS)
		float fps = getTickFrequency() / ((double)getTickCount() - timer);
		//If its able to track it, below code works
		if (ok)
		{
			/// Tracking success : Draw the tracked object
			//Modify this code based on time
			rectangle(frame, bbox, Scalar(255, 0, 0), 2, 1);
			//Calculate contours of the sphere. 
			//cout << "About to define contours";
			defContours(frame);
			//cout << "Contours defined";
			//Calculate the center of the ROI as it is being tracked. Returns one decimal
			Point2f center_of_rect = (bbox.br() + bbox.tl())*0.5;
			//Calulates center of the circle. Returns a float
			//Point2f centroids = getCentroid();
			//cout << center_of_rect;
			//Exports (x,y) coordinate of rectangle center
			//makeCoords(center_of_rect);
			exportExcel(center_of_rect, tofvid);

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
		frame_number ++;

		//cout << (frame_number / 20);
		//cout << " , ";

	}

	
	//*/
	waitKey();
	return 0;
}