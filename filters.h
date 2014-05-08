#include <iostream>
#include <math.h>
#include <opencv2/core/core.hpp>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

using namespace cv;
using namespace std;
int iLowH = 19;
int iHighH = 43;

int iLowS = 87; 
int iHighS = 87;

int iLowV = 124;
int iHighV = 102;

int iDistance = 60;

double iHighGreen = sqrt(iHighH*iHighH + iHighS*iHighS + iHighV*iHighV);
double iLowGreen = sqrt(iLowH*iLowH + iLowS*iLowS + iLowV*iLowV);


	
double getDistance(const Mat &imgOrignal, double origH, double origS, double origV){

	vector<Mat> channels;
	split(imgOrignal, channels);
    double h = (mean(channels[0])[0]) - origH;
    double s = (mean(channels[1])[0]) - origS;
    double v = (mean(channels[2])[0]) - origV;
	
	return sqrt(h*h+s*s+v*v);
}

double greenFilter(const Mat &imgOriginal, Mat &output){
	
    namedWindow("Control",CV_WINDOW_AUTOSIZE); //create a window called "Control"
    //Create trackbars in "Control" window
    cvCreateTrackbar("HighH", "Control", &iHighH, 255);
    cvCreateTrackbar("HighS", "Control", &iHighS, 255);
    cvCreateTrackbar("HighV", "Control", &iHighV, 255);
    cvCreateTrackbar("Distance", "Control", &iDistance,255);

    Mat imgHSV;
    cvtColor(imgOriginal, imgHSV, COLOR_BGR2HSV); //Convert the captured frame from ?? to HSV
	output = imgHSV;
    
	double dist = getDistance(imgHSV, iHighH,iHighS,iHighV);

	//printf("%f\n", dist);
	if (dist > iDistance){
		vector<Mat> channels;
		split(imgHSV, channels);
		double h = (mean(channels[0])[0]);
		double s = (mean(channels[1])[0]);
		double v = (mean(channels[2])[0]);
		//cout << "h: " << h << " - " << s << " - " << v << endl <<endl;
		output.setTo(cv::Scalar(h,s,v)); //show mean color
		cvtColor(output, output, COLOR_HSV2BGR);
	}//else{//printf("%s\n","found some green stuffs!");}
	
    return dist;
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
