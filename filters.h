#include <iostream>
#include <math.h>
#include <opencv2/core/core.hpp>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

using namespace cv;
using namespace std;
	int iLowH = 19;
    int iHighH = 146;

    int iLowS = 87; 
    int iHighS = 107;

    int iLowV = 124;
    int iHighV = 191;
	
	double iHighGreen = sqrt(iHighH*iHighH + iHighS*iHighS + iHighV*iHighV);
	double iLowGreen = sqrt(iLowH*iLowH + iLowS*iLowS + iLowV*iLowV);

	
double getMean(const Mat &imgOrignal){

	vector<Mat> channels;
	split(imgOrignal, channels);
    Scalar h = mean(channels[0]);
    Scalar s = mean(channels[1]);
    Scalar v = mean(channels[2]);
	
	return sqrt(h[0]*h[0]+s[0]*s[0]+v[0]*v[0]);
}

void greenFilter(const Mat &imgOriginal, Mat &output){
	
    namedWindow("Control",CV_WINDOW_AUTOSIZE); //create a window called "Control"
    //Create trackbars in "Control" window
    cvCreateTrackbar("LowH", "Control", &iLowH, 255);
    cvCreateTrackbar("HighH", "Control", &iHighH, 255);

    cvCreateTrackbar("LowS", "Control", &iLowS, 255);
    cvCreateTrackbar("HighS", "Control", &iHighS, 255);

    cvCreateTrackbar("LowV", "Control", &iLowV, 255);
    cvCreateTrackbar("HighV", "Control", &iHighV, 255);

    Mat imgHSV;
    cvtColor(imgOriginal, imgHSV, COLOR_BGR2HSV); //Convert the captured frame from ?? to HSV
    //Mat imgThresholded;
	//printf("%f\n", getMean(imgHSV));
	
	
    inRange(imgHSV, Scalar(iLowH, iLowS, iLowV), Scalar(iHighH, iHighS, iHighV), output); //Threshold the image => enkel groen over houden
	
    dilate( output, output, getStructuringElement(MORPH_RECT, Size(3, 3)) ); //dilate the image to get rid of holes
    //cvtColor(output,output,CV_RGB2GRAY);
}

void crossDetect(Mat input){//copy input to show crosses
    //vector<Mat> laserChannels;
    //split(input, laserChannels);
    Mat grey;
    cvtColor(input,grey,CV_RGB2GRAY);

    vector<Point2f> corners;
    // only using the red channel since it contains the interesting bits...
    goodFeaturesToTrack(grey, corners, 50, 0.1, 10, Mat());//, 3, false, 0.04);

    for (int i = 0 ; i < corners.size() ; i++){
        circle(input, corners[i], 3, Scalar(0, 255, 0), -1, 8, 0);
    }

    //imshow("laser red", laserChannels[2]);
    imshow("corner", input);
}
