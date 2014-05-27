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
    namedWindow("Edit", CV_WINDOW_AUTOSIZE);

    Mat dst;

    Point center = Point(src.cols / 2, src.rows / 2);
    double angle = -15.0;
    double scale = 0.6;

    Mat kernel = getRotationMatrix2D(center, angle, scale);

    warpAffine(src, dst, kernel,src.size());

    imshow("Original Image", src);
    imshow("Edit", dst);

    waitKey(0);

    return 0;
}
