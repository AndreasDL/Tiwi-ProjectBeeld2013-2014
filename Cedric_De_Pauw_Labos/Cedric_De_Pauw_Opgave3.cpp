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

    namedWindow("Original Image", WINDOW_AUTOSIZE);
    namedWindow("Sharpened Image", CV_WINDOW_AUTOSIZE);

    //show the loaded image
    imshow("Original Image", src);

    Mat dst;
    Mat result;

    //smooth the image in the "src" and save it to "dst"
    GaussianBlur(src, dst, Size(69,69), 0);

    result = 2* src - dst;

    //show the blurred image with the text
    imshow("Sharpened Image", result);

    //wait for a key press infinitely
    waitKey(0);

    return 0;
}
