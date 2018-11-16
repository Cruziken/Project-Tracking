#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "opencv2/imgcodecs.hpp"
#include <opencv2/core/utility.hpp>
#include "opencv2/highgui.hpp"
using namespace cv;
using namespace std;

void defContours(Mat myFrame);
void exportExcel(Point2f mc);
Rect2d getBound();
Point2f getCentroid();


#endif