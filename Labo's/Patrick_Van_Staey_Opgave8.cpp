// Patrick_Van_Staey_Opgave8.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

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

	Mat shearedImage;
	Mat kernel(2,3, CV_64F, 0.0);

	kernel.at<double>(0, 0) = 1;
	kernel.at<double>(0, 1) = -0.2;
	kernel.at<double>(0, 2) = 50;
	kernel.at<double>(1, 0) = 0;
	kernel.at<double>(1, 1) = 1;
	kernel.at<double>(1, 2) = 0;

	Size size;
	size.width = 400;
	size.height = 400;
	warpAffine(image, shearedImage, kernel, size);

	namedWindow("ShearedImage", WINDOW_AUTOSIZE);
	imshow("ShearedImage", shearedImage);
	waitKey(0);
}