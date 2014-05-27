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
	waitKey(0);

	const int COLS = 45;
	//1
	Mat gaussianKernel = getGaussianKernel(COLS, 10.5, CV_32F);

	//2
	Mat square = Mat::zeros(COLS, COLS, CV_32F);
	Mat middle = square.col(COLS / 2);
	gaussianKernel.col(0).copyTo(middle);

	//3
	Mat rowGaussianKernel = getGaussianKernel(COLS, 0.1, CV_32F);
	rowGaussianKernel = rowGaussianKernel.t();

	//4
	Mat filtered;
	filter2D(square, filtered, CV_32F, rowGaussianKernel);

	//5
	Mat dogFilter;
	Sobel(filtered, dogFilter, CV_32F, 1, 0);

	//6
	Point2f center(COLS / 2, COLS / 2);
	Mat rotateMat = getRotationMatrix2D(center, -15, 1);

	//7
	Mat rotatedFiltered;
	warpAffine(dogFilter, rotatedFiltered, rotateMat, dogFilter.size());

	waitKey(0);
	//8
	Mat grey;
	cvtColor(image, grey, CV_RGB2GRAY);

	imshow("Image", grey);

	waitKey(0);
	filter2D(grey, grey, CV_32F, rotatedFiltered);

	//9
	grey = abs(grey/512);

	imshow("Image", grey);
	waitKey(0);
	
	return 0;
}


