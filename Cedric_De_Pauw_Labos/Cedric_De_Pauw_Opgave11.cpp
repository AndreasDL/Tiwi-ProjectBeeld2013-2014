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

	Mat edges;
	Canny(image, edges, 15, 10);

	vector<Vec2f> lines;
	HoughLines(edges, lines, 1,  0.01, 80);

	for (size_t i = 0; i < lines.size(); i++)
    {
        float rho = lines[i][0], theta = lines[i][1];
        Point pt1, pt2;
        double a = cos(theta), b = sin(theta);
        double x0 = a*rho, y0 = b*rho;
        pt1.x = cvRound(x0 + 1000 * (-b));
        pt1.y = cvRound(y0 + 1000 * (a));
        pt2.x = cvRound(x0 - 1000 * (-b));
        pt2.y = cvRound(y0 - 1000 * (a));
        line(image, pt1, pt2, Scalar(0, 0, 255), 3, CV_AA);
    }

	imshow("Image", image);
	waitKey(0);
	
	return 0;
}



