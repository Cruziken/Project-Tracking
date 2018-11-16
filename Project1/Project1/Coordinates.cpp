#include "opencv2/imgcodecs.hpp"
#include <opencv2/core/utility.hpp>
#include "opencv2/highgui.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace cv;
using namespace std;


/*
 * @function exportExcel
 */
void exportExcel(Point2f mc) {
	//Initilize a data stream to myFile 
	ofstream myFile;
	//Stream data to testing.csv
	myFile.open("testing.csv",ios_base::app);
	//Initialize a data stream to stream 
	stringstream myPoint;
	//store x and y coordinates of 2-D vector in stream 
	//cout << mc;
	myPoint << mc.x << "," << mc.y;
	//Pass the 2-D vector ( (x,y) coordinates) to excel file testing.csv
	myFile << myPoint.str() << "\n" ;
}