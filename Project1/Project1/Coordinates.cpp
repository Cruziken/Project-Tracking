#include "opencv2/imgcodecs.hpp"
#include <opencv2/core/utility.hpp>
#include "opencv2/highgui.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace cv;
using namespace std;

float t;
float xcoord;
float ycoord;
float halfmatrix = 1.0/240.0;
float fullmatrix = 1.0 / 480.0;
void sendFile(float time, float xc, float yc);
/*
 * @function exportExcel
 */
void exportExcel(Point2f mc, float time) {
	xcoord = mc.x;
	ycoord = mc.y;
	//cout << ycoord;
	t = time;
	if ((xcoord < 240) && (ycoord < 240)) {
		//cout << xcoord;
		xcoord = -halfmatrix* xcoord;
		//cout << xcoord;
		ycoord = halfmatrix * ycoord;
		sendFile(t, xcoord, ycoord);
	}
	else if ((xcoord > 240) && (ycoord < 240)) {
		xcoord = fullmatrix * xcoord;
		ycoord = halfmatrix * ycoord;
		sendFile(t, xcoord, ycoord);
	}
	else if ((xcoord > 240) && (ycoord > 240)) {
		xcoord = fullmatrix * xcoord;
		ycoord = -fullmatrix * ycoord;
		sendFile(t, xcoord, ycoord);
	}
	else {
		xcoord = -halfmatrix * xcoord;
		ycoord = -fullmatrix * ycoord;
		sendFile(t, xcoord, ycoord);
	}
}

void sendFile(float time, float xc, float yc) {
	//Initilize a data stream to myFile 
	ofstream myFile;
	//Stream data to testing.csv
	myFile.open("testing.csv", ios_base::app);
	//Initialize a data stream to stream 
	stringstream myPoint;
	//store x and y coordinates of 2-D vector in stream 
	//cout << mc;

	myPoint << xc << "," << yc << "," << time;
	//Pass the 2-D vector ( (x,y) coordinates) to excel file testing.csv
	myFile << myPoint.str() << "\n";
}
