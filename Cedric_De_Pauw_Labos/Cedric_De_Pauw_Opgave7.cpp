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

    Mat src = imread(argv[1], CV_LOAD_IMAGE_COLOR);
    if (!src.data){
		cout << "Could not find or open the file!" << endl;
		return -1;
	}

    namedWindow("Original Image", CV_WINDOW_AUTOSIZE);
    namedWindow("Erode", CV_WINDOW_AUTOSIZE);
    namedWindow("Dilate", CV_WINDOW_AUTOSIZE);

    Mat dstErode;

    Mat kernel = getStructuringElement(MORPH_ELLIPSE, Size(10,5));
    erode(src, dstErode, kernel);

    Mat dstDilate;
    kernel = getStructuringElement(MORPH_RECT, Size(6,12));
    dilate(dstErode, dstDilate, kernel);

    imshow("Original Image", src);
    imshow("Erode", dstErode);
    imshow("Dilate", dstDilate);

    waitKey(0);

    return 0;
}


