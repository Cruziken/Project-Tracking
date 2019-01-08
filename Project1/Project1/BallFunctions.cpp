#include "opencv2/imgcodecs.hpp"
#include <opencv2/core/utility.hpp>
#include "opencv2/highgui.hpp"
#include "opencv2/tracking.hpp"
#include <opencv2/videoio.hpp>
#include "opencv2/imgproc.hpp"
#include "LogicAnim.h"
using namespace std;

bool ballLeft;
bool ballDown;
float x;
float y;
using namespace std;
//void sendFile(float time, float xc, float yc);

void setBoolsLeft(bool ballLeftit) {
	ballLeft = ballLeftit;
}
void setBoolsDown(bool ballDownit) {
	ballDown = ballDownit;
}
void setX(float xint) {
	x = xint;
}
void setY(float yint) {
	y = yint;
}






void ballRand(float radius, float tim) {
	float speedchange = 0.002;
	float bouncespeed = 0.003;
	if (ballLeft) {
		if (x > -1 + (radius + 0.1)) {
			x -= (rand() % 50)*speedchange;

		}
		else {
			ballLeft = false;
			x += bouncespeed;
		}
	}
	else {
		if (x < 1 - (radius + 0.1)) {
			x += (rand() % 50)*speedchange;
		}
		else {
			ballLeft = true;
			x -= bouncespeed;
		}
	}
	//cout << x;
	if (ballDown) {
		if (y > -1 + (radius + 0.1)) {
			y -= (rand() % 50)*speedchange;
		}
		else {
			ballDown = false;
			y += bouncespeed;
		}
	}
	else {
		if (y < 1 - (radius + 0.1)) {
			y += (rand() % 50)*speedchange;
		}
		else {
			ballDown = true;
			y -= bouncespeed;
		}
	}
	//sendFile(tim, x, y);
}
/**
Make more general than just for circular objects
**/
void ballPara(float radius, float tim) {

	if (ballLeft) {
		if (x > -1 + (radius + 0.1)) {
			x -= 0.03;
			
		}
		else {
			ballLeft = false;
		}
	}
	else {
		if (x < 1 - (radius + 0.1)) {
			x += 0.03;
		}
		else {
			ballLeft = true;
		}
	}
	//cout << x;
	if (ballDown) {
		if (y > -1 + (radius + 0.1)) {
			y = -pow(x, 2);
		}
		else {
			ballDown = false;
		}
	}
	else {
		if (y < 1 - (radius + 0.1)) {
			y = -pow(x, 2);
		}
		else {
			ballDown = true;
		}
	}
	//sendFile(tim, x, y);
	//cout << ballDown;
}
bool getBoolLeft() {
	return ballLeft;
}
bool getBoolDown() {
	return ballDown;
}
float getX() {
	//cout << x;
	return x;
}
float getY() {
	//cout << x;
	return y;
}