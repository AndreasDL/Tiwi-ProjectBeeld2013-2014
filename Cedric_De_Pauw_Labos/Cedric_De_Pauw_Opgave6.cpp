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

    //create 2 empty windows
    namedWindow("Original Image", CV_WINDOW_AUTOSIZE);
    namedWindow("Filter2D", CV_WINDOW_AUTOSIZE);

    Mat dst;

    Mat kernel(15, 15, CV_64F, 0.0);
    for (int i = 0; i < 7; i++){
        kernel.at<double>(i, i) = 1.0 / 7;
    }

    filter2D(src, dst, -1, kernel, Point(14,14));

    imshow("Original Image", src);
    imshow("Filter2D", dst);

    waitKey(0);

    return 0;
}
