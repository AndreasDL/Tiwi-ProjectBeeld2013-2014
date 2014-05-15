#include <iostream>
#include <math.h>
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

double getHSV(const Mat &imgOrignal, double &h, double &s, double &v){
	vector<Mat> channels;
	split(imgOrignal, channels);
    h = (mean(channels[0])[0]);
    s = (mean(channels[1])[0]);
    v = (mean(channels[2])[0]);
}

void greenFilter(const Mat &imgOriginal, Mat &output){
	
    namedWindow("Control",CV_WINDOW_AUTOSIZE); //create a window called "Control"
    //Create trackbars in "Control" window
    cvCreateTrackbar("HighH", "Control", &iHighH, 255);
    cvCreateTrackbar("HighS", "Control", &iHighS, 255);
    cvCreateTrackbar("HighV", "Control", &iHighV, 255);

    Mat imgHSV;
    cvtColor(imgOriginal, imgHSV, COLOR_BGR2HSV); //Convert the captured frame from ?? to HSV
    //Mat imgThresholded;
	output = imgHSV;
	
	
	printf("%f\n", getDistance(imgHSV, iHighH,iHighS,iHighV));
	if (getDistance(imgHSV, iHighH,iHighS,iHighV)>60){
		vector<Mat> channels;
		split(imgHSV, channels);
		double h = (mean(channels[0])[0]);
		double s = (mean(channels[1])[0]);
		double v = (mean(channels[2])[0]);
		cout << "h: " << h << " - " << s << " - " << v << endl <<endl;
		output.setTo(cv::Scalar(h,s,v));
		cvtColor(output, output, COLOR_HSV2BGR);
	}
	
    // inRange(imgHSV, Scalar(iLowH, iLowS, iLowV), Scalar(iHighH, iHighS, iHighV), output); //Threshold the image => enkel groen over houden
	
    dilate( output, output, getStructuringElement(MORPH_RECT, Size(3, 3)) ); //dilate the image to get rid of holes
    // cvtColor(output,output,CV_RGB2GRAY);
}
