#include <opencv2/core/utility.hpp>
#include <opencv2/tracking.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <cstring>
using namespace std;
int main(int argc) {
	// show help
	if (argc < 2) {
		cout <<
			" Usage: tracker <video_name>\n"
			" examples:\n"
			" example_tracking_kcf Bolt/img/%04d.jpg\n"
			" example_tracking_kcf faceocc2.webm\n"
			<< endl;
		return 0;
	}

	// create a tracker object
	Ptr<Tracker> tracker = TrackerKCF::create();
	// set input video
	VideoCapture video("C:\\Users\\Titanium\\source\\repos\\Project1\\videos\\dot.mp4\n");

	// Exit if video is not opened
	if (!video.isOpened())
	{
		cout << "Could not read video file" << endl;
		return 1;
	}

	// Read first frame 
	Mat frame;
	bool ok = video.read(frame);

	// Define initial bounding box 
	//Rect2d bbox(287, 23, 86, 320);

	// Uncomment the line below to select a different bounding box 
	Rect2d bbox = selectROI(frame, false);
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