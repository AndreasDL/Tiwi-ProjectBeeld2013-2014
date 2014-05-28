#include <iostream>
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

    inRange(imgHSV, Scalar(iLowH, iLowS, iLowV), Scalar(iHighH, iHighS, iHighV), output); //Threshold the image => enkel groen over houden
    dilate( output, output, getStructuringElement(MORPH_RECT, Size(3, 3)) ); //dilate the image to get rid of holes
    //cvtColor(output,output,CV_RGB2GRAY);
}
