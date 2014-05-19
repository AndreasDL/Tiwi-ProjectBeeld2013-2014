// Patrick_Van_Staey_Opgave9.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int amountOfClicks = 0;
Point2f cornerPoints[4];
const int xlinks = 100;
const int xrechts = 280;
const int yonder = 550;
const int yboven = 80;
Point2f dst[4] = { Point2f(xlinks, yonder),
Point2f(xlinks, yboven),
Point2f(xrechts, yboven),
Point2f(xrechts, yonder)
};

static void onMouse(int event, int x, int y, int, void* d)
{
	Mat* image = (Mat*)d;
	if (event != EVENT_LBUTTONDOWN)
		return;
	else
		cout << "Left button of the mouse is clicked - position (" << x << ", " << y << ")" << endl;

	cornerPoints[amountOfClicks] = Point2f(x, y);
	amountOfClicks++;

	if (amountOfClicks == 4){
		Mat pt = getPerspectiveTransform(cornerPoints, dst);
		Mat outputImage;
		warpPerspective(*image, outputImage, pt, (*image).size());

		namedWindow("OutputImage", WINDOW_AUTOSIZE);
		imshow("OutputImage", outputImage);
	}
}

int main(int argc, char** argv)
{
	if (argc != 2){
		cout << "Give a filename" << endl;
		return -1;
	}

	Mat image = imread(argv[1], CV_LOAD_IMAGE_COLOR);
	if (!image.data){
		cout << "Could not find or open the file!" << endl;
		return -1;
	}

	namedWindow("Image", WINDOW_AUTOSIZE);
	imshow("Image", image);
	
	setMouseCallback("Image", onMouse, &image);

	waitKey(0);
}
