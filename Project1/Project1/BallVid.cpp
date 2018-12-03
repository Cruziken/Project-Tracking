#include "opencv2/imgcodecs.hpp"
#include <opencv2/core/utility.hpp>
#include "opencv2/highgui.hpp"
#include "opencv2/tracking.hpp"
#include <opencv2/videoio.hpp>
#include "opencv2/imgproc.hpp"
#include <GLFW/glfw3.h>
#include <Windows.h>
#include "linmath.h"
#include <stdlib.h>
#include <stdio.h>


int wid, hgt = 480;
VideoWriter outputVideo;
string myVid;
void realeaseVid(); 
void openVideo();
void saveFramebuffer(int x);
void myAnimate(GLFWwindow* myWin);

using namespace std;
using namespace cv;
/*
Function that creates window and sets context for window
*/
GLFWwindow* makeVid(string myVideo)
{
	myVid = myVideo;
	int width = 480;
	int height = 480;
	// Initialize the library. This is correct 
	if (!glfwInit()) {
		cout << "Failed to Initialize the library";
	}
	//Tells what version of openGl is being used
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

	//Create a windowed mode window.
	GLFWwindow* window = glfwCreateWindow(width, height, "OpenGl Example", NULL, NULL);
	if (!window) {
		glfwTerminate();
		cout << "Error occured in creating window";
	}
	//Create OpenGL context
	glfwMakeContextCurrent(window);
	//Talking about the refresh between each frame. Has a little bit of delay for the buffer to read, no tear
	glfwSwapInterval(1);
	return window;
}

/*
Method that controls behavior of the ball animation
*/
void myAnimate(GLFWwindow* myWin) {
	//Define variables for circle
	GLFWwindow* window = myWin;
	const float DEG2RAD = 3.14159 / 180;
	float radius = 0.1;
	float red = 0.0;
	float green = 0.3;
	float blue = 0.6;
	float x = -1;
	float y = -1;

	bool ballLeft = true;
	bool ballDown = true;
	//double initsec = 
	//glfwSetTime(0);
	openVideo();
	while (!glfwWindowShouldClose(window)) {
		///Setup View

		for (int t = 0; t <= 1000; t++) {
			float ratio;
			int width, height;
			//Pointers write data to width and height variables
			glfwGetFramebufferSize(window, &width, &height);
			ratio = width / (float)height;
			//Create viewport for what we will actually see

			glViewport(0, 0, width, height);
			glClear(GL_COLOR_BUFFER_BIT);


			if (ballLeft) {
				if (x > -1 + radius) {
					x -= 0.05;
				}
				else {
					ballLeft = false;
				}
			}
			else {
				if (x < 1 - radius) {
					x += 0.05;
				}
				else {
					ballLeft = true;
				}
			}

			if (ballDown) {
				if (y > -1 + radius) {
					y -= 0.05;
				}
				else {
					ballDown = false;
				}
			}
			else {
				if (y < 1 - radius) {
					y += 0.05;
				}
				else {
					ballDown = true;
				}
			}
			///Drawing Circle
			glColor3f(red, green, blue);
			glBegin(GL_POLYGON);
			for (int i = 0; i < 360; i++) {
				float degInRad = i * DEG2RAD;
				glVertex2f((cos(degInRad)*radius) + x, (sin(degInRad)*radius) + y);
			}
			glEnd();
			cout << t;

			saveFramebuffer(t);
		}
		realeaseVid();
		glfwSetWindowShouldClose(window, 1);
	}
	//saveFramebuffer();
	//Deletes and closes window
	glfwDestroyWindow(window);
	//End process;
	glfwTerminate;
	//saveFramebuffer();
	exit(EXIT_SUCCESS);

}
void openVideo(){
	int height = 480;
	int width = 480;
	outputVideo.open(myVid, 'DIVX', 20.0f, Size(width, height), true);
}
void saveFramebuffer(int x) {

	int fid = x;
	int height = 480;
	int width = 480;
	int const total_frame = 100;
	//time_t start = time(0);
		//if (fid == 0) {
			//outputVideo.open(myVid, 'DIVX', 20.0f, Size(width, height), true);
			//cout << fid;
			//fid++;
		//}
		//else if (fid < total_frame) {
			// cout << "It is not skipping";
			Mat pixels(height, width, CV_8UC3);
			glReadPixels(0, 0, width, height, GL_RGB, GL_UNSIGNED_BYTE, pixels.data);
			Mat cv_pixels(height, width, CV_8UC3);
			//cout << "It is not skipping";
			for (int y = 0; y < height; y++) for (int x = 0; x < width; x++)
			{
				cv_pixels.at<cv::Vec3b>(y, x)[2] = pixels.at<cv::Vec3b>(height - y - 1, x)[0];
				cv_pixels.at<cv::Vec3b>(y, x)[1] = pixels.at<cv::Vec3b>(height - y - 1, x)[1];
				cv_pixels.at<cv::Vec3b>(y, x)[0] = pixels.at<cv::Vec3b>(height - y - 1, x)[2];
			}
			outputVideo << cv_pixels;
			//if (difftime(time(0), start) == 30);
			//fid++;
		//}
}
void realeaseVid() {

	outputVideo.release();
	cout << "Video should be released";
}

