// Patrick_Van_Staey_Opgave13.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <opencv2/features2d/features2d.hpp>
#include <vector>

using namespace cv;
using namespace std;

int main(int argc, char** argv)
{
	if (argc != 3){
		cout << "Give two filenames" << endl;
		return -1;
	}

	Mat image1 = imread(argv[1], CV_LOAD_IMAGE_COLOR);
	if (!image1.data){
		cout << "Could not find or open the first file!" << endl;
		return -1;
	}

	Mat image2 = imread(argv[2], CV_LOAD_IMAGE_COLOR);
	if (!image2.data){
		cout << "Could not find or open the second file!" << endl;
		return -1;
	}
	namedWindow("Image1", WINDOW_AUTOSIZE);
	imshow("Image1", image1);

	namedWindow("Image2", WINDOW_AUTOSIZE);
	imshow("Image2", image2);

	waitKey(0);

	FastFeatureDetector ffd;
	BriefDescriptorExtractor bde;
	BFMatcher bfm;

	vector<KeyPoint> keypoints1;
	ffd.detect(image1, keypoints1);

	vector<KeyPoint> keypoints2;
	ffd.detect(image2, keypoints2);

	Mat descriptors1;
	bde.compute(image1, keypoints1, descriptors1);

	Mat descriptors2;
	bde.compute(image2, keypoints2, descriptors2);

	vector<vector<DMatch> > matches;
	bfm.knnMatch(descriptors1, descriptors2, matches, 32);
	Mat output;
	drawMatches(image1, keypoints1, image2, keypoints2, matches, output);

	namedWindow("OutputImage", WINDOW_AUTOSIZE);
	imshow("OutputImage", output);

	waitKey(0);
}







