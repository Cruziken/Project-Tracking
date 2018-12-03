#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "opencv2/imgcodecs.hpp"
#include <opencv2/core/utility.hpp>
#include "opencv2/highgui.hpp"
#include <GLFW/glfw3.h>

using namespace cv;
using namespace std;

void defContours(Mat myFrame);
void exportExcel(Point2f mc);
Rect2d getBound();
Point2f getCentroid();
GLFWwindow* makeVid(string myVideo);
void myAnimate(GLFWwindow* myWin);

#endif