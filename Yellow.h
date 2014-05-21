#ifndef YELLOW_H
#define YELLOW_H

#include <iostream>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

using namespace cv;
using namespace std;
int iLowH = 19;
int iHighH = 43;

int iLowHY = 20;
int iHighHY = 25;

int iLowS = 87;
int iHighS = 87;

int iLowSY = 40;
int iHighSY = 150;

int iLowV = 124;
int iHighV = 102;

int iLowVY = 200;
int iHighVY = 255;

int yellowFilter(const Mat &imgOriginal){

    namedWindow("Control", CV_WINDOW_AUTOSIZE); //create a window called "Control"
    //Create trackbars in "Control" window
    cvCreateTrackbar("HighH", "Control", &iHighHY, 255);
    cvCreateTrackbar("HighS", "Control", &iHighSY, 255);
    cvCreateTrackbar("HighV", "Control", &iHighVY, 255);

    Mat imgHSV;
    cvtColor(imgOriginal, imgHSV, COLOR_BGR2HSV); //Convert the captured frame from ?? to HSV
    Mat output = imgHSV;

    inRange(imgHSV, Scalar(iLowHY, iLowSY, iLowVY), Scalar(iHighHY, iHighSY, iHighVY), output);
    int count = countNonZero(output);
    return count;
}

#endif // YELLOW_H
