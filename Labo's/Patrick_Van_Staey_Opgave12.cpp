// Patrick_Van_Staey_Opgave12.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <vector>

using namespace cv;
using namespace std;

int main(int argc, char** argv)
{
	if (argc != 3){
		cout << "Give two filenames" << endl;
		return -1;
	}

	Mat image1 = imread(argv[1], CV_LOAD_IMAGE_GRAYSCALE);
	if (!image1.data){
		cout << "Could not find or open the first file!" << endl;
		return -1;
	}

	Mat image2 = imread(argv[2], CV_LOAD_IMAGE_GRAYSCALE);
	if (!image2.data){
		cout << "Could not find or open the second file!" << endl;
		return -1;
	}
	namedWindow("Image1", WINDOW_AUTOSIZE);
	imshow("Image1", image1);

	namedWindow("Image2", WINDOW_AUTOSIZE);
	imshow("Image2", image2);
	waitKey(0);

	vector<Point2f> v1;
	goodFeaturesToTrack(image1, v1, 20, 0.01, 10);
	int radius = 5;
	for (int i = 0; i < v1.size(); i++){
		circle(image1, v1[i], radius, Scalar(255));
	}

	vector<Point2f> v2;
	goodFeaturesToTrack(image2, v2, 20, 0.01, 10);
	for (int i = 0; i < v2.size(); i++){
		circle(image2, v2[i], radius, Scalar(255));
	}

	namedWindow("Image1", WINDOW_AUTOSIZE);
	imshow("Image1", image1);

	namedWindow("Image2", WINDOW_AUTOSIZE);
	imshow("Image2", image2);

	waitKey(0);

	
}





