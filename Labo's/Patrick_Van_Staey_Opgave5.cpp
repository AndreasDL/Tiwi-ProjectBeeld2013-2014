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

	Mat greyImage;

	cvtColor(image, greyImage, CV_RGB2GRAY);

	Mat sobelImage;
	Sobel(greyImage, sobelImage, -1, 1, 0, 3);

	namedWindow("SobelImage", WINDOW_AUTOSIZE);
	imshow("SobelImage", sobelImage);
	waitKey(0);
}

