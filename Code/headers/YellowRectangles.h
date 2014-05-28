#include <iostream>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

using namespace cv;
using namespace std;

int yellowRectangleFilter(Mat &imgOriginal){
	Mat imgHSV;
	Mat img = imgOriginal;
	threshold(img, img, 235, 255, THRESH_TOZERO_INV);
	cvtColor(img, imgHSV, COLOR_BGR2HSV); //Convert the captured frame from ?? to HSV


	Mat yellow;
	inRange(imgHSV, Scalar(20, 40, 40), Scalar(23, 255, 255), yellow);

	threshold(yellow, yellow, 127, 255, 0);
	vector<vector<Point> > contours;
	findContours(yellow, contours, CV_RETR_LIST, CV_CHAIN_APPROX_SIMPLE);

	vector<Point> approx;
	int yellowRectangles = 0;

	for (size_t i = 0; i < contours.size(); i++){
		approxPolyDP(Mat(contours[i]), approx, arcLength(Mat(contours[i]), true)*0.02, true);
		if (approx.size() == 4 && isContourConvex(Mat(approx)) && fabs(contourArea(Mat(approx))) > 5000) {
			Rect rec = boundingRect(contours[i]);
			rectangle(imgOriginal, rec.tl(), rec.br(), Scalar(0, 255, 0), 2);
			yellowRectangles++;
		}
	}
	return yellowRectangles;

}