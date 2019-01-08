#define PI 3.141592653589793238462643383279502884
#include "opencv2/imgcodecs.hpp"
#include <opencv2/core/utility.hpp>
#include "opencv2/highgui.hpp"
#include "opencv2/tracking.hpp"
#include <opencv2/videoio.hpp>
#include "opencv2/imgproc.hpp"
#include <GLFW/glfw3.h>
#include <Windows.h>
#include "linmath.h"
#include "functions.h"
#include "LogicAnim.h"
#include <stdlib.h>
#include <stdio.h>


using namespace std;
using namespace cv;
class BallVid {
	int wid, hgt = 480;
	VideoWriter outputVideo;
	string myVid;
	void ballPara(float radius, float tim);
	//void ballRand(float radius, float tim);
	bool getBoolLeft();
	bool getBoolDown();
	float getX();
	float getY();
	void setBoolsLeft(bool boolleft);
	void setBoolsDown(bool boolright);
	void setX(float x);
	void setY(float y);
	void sendFile(float time, float xc, float yc);
	void realeaseVid();
	void openVideo();
	void saveFramebuffer();
	void myAnimate(GLFWwindow* myWin);

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
		//float x = -1;
		//float y = -1;


		//Open the video to be read to
		openVideo();

		while (!glfwWindowShouldClose(window)) {

			///Setup View
			// For each 20 t equals 1 second for the video. t = 400 equals 20 seconds
			///2-D projectile motion
				//Magnitude of velocity


			float magVel = 0.3;
			//Launch angle
			float angle = 45 * (PI / 180);
			//X component of velocity
			float velx = magVel * cos(angle);
			//Y component of velocity 
			float vely = magVel * sin(angle);
			//Initial y position
			float y = 0;
			//Initial x position
			float x = 0;
			bool ballLeft = true;
			bool ballDown = true;
			//Initial acceleration
			//float accel = -1.0;

			//Loop through time. 20 t's are equal to one second. Major key!
			for (int t = 0; t <= 400; t++) {

				//Dimensions of frame
				int width, height;
				//Pointers write data to width and height variables
				glfwGetFramebufferSize(window, &width, &height);

				//Create viewport for what we will actually see
				glViewport(0, 0, width, height);
				glClear(GL_COLOR_BUFFER_BIT);


				float time_of_vid = t / 20.0;


				//cout << ballLeft;
				setBoolsLeft(ballLeft);
				setBoolsDown(ballDown);
				setX(x);
				setY(y);
				ballRand(radius, time_of_vid);
				//ballPara(radius, time_of_vid);
				ballLeft = getBoolLeft();
				ballDown = getBoolDown();
				x = getX();
				y = getY();
				//cout << x;
				//cout << x ;
				//cout << y;
				///Drawing Circle
				glColor3f(red, green, blue);
				glBegin(GL_POLYGON);
				for (int i = 0; i < 360; i++) {
					float degInRad = i * DEG2RAD;
					glVertex2f((cos(degInRad)*radius) + x, (sin(degInRad)*radius) + y);
				}
				//xint = xt;
				//yint = yt;
				// DO NOT SWAP BUFFERS OR TRACKER WILL NOT READ CONTOURS IN FIRST FRAME
				glEnd();

				//cout << t;
				//Pass frames to the video
				saveFramebuffer();

			}
			//Close the video
			realeaseVid();
			//Close the loop man!
			glfwSetWindowShouldClose(window, 1);
		}
		//Deletes and closes window
		glfwDestroyWindow(window);
		//End process;
		glfwTerminate;
		cout << "Code was successful";

	}
	void openVideo() {
		int height = 480;
		int width = 480;
		outputVideo.open(myVid, 'DIVX', 20.0f, Size(width, height), true);
	}
	void saveFramebuffer() {
		int fid = 1;
		int height = 480;
		int width = 480;
		int total_frame = 100;
		if (fid < total_frame) {
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
			fid++;
		}

	}
	void realeaseVid() {
		//Close the video streaming
		outputVideo.release();
		cout << "Video should be released";
	}
}
