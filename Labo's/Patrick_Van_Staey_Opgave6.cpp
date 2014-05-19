// Patrick_Van_Staey_Opgave1.cpp : Defines the entry point for the console application.
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

	Mat filteredImage;

	Mat kernel(15, 15, CV_32F, 0.0);
	Point anchor;
	anchor.x = 14;
	anchor.y = 14;

	double value = 1.0 / 7;

	cout << value << endl;

	kernel.at<float>(0, 0) = value;
	kernel.at<float>(1, 1) = value;
	kernel.at<float>(2, 2) = value;
	kernel.at<float>(3, 3) = value;
	kernel.at<float>(4, 4) = value;
	kernel.at<float>(5, 5) = value;
	kernel.at<float>(6, 6) = value;

	filter2D(image, filteredImage, -1, kernel , anchor);

	namedWindow("FilteredImage", WINDOW_AUTOSIZE);
	imshow("FilteredImage", filteredImage);
	waitKey(0);
}
