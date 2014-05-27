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
    namedWindow("MedianBlur", CV_WINDOW_AUTOSIZE);

    Mat dst;

    medianBlur(src, dst, (19, 19));

    imshow("Original Image", src);
    imshow("MedianBlur", dst);

    waitKey(0);

    return 0;
}
