#include <iostream>
#include <math.h>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

using namespace cv;
using namespace std;

double getDistance(const Mat &imgOrignal, double origH, double origS, double origV, Mat &uitvoer){
	Mat tmp, tmp2;

	blur(imgOrignal, tmp, Size(1,1));
	inRange(tmp, Scalar(30, 40, 40), Scalar(150, 250, 250), tmp2); //Threshold the image => enkel groen over houden
	tmp.copyTo(uitvoer, tmp2);
	
	vector<Mat> channels;
	split(uitvoer, channels);
	
    // double h = (mean(channels[0])[0]) - origH;
    double h = (sum(channels[0])/sum(tmp2))[0] - origH;
    // double s = (mean(channels[1])[0]) - origS;
    double s = (sum(channels[1])/sum(tmp2))[0] - origS;
    // double v = (mean(channels[2])[0]) - origS;
    double v = (sum(channels[2])/sum(tmp2))[0] - origV;
	
	return sqrt(h*h+s*s+v*v);
}

double getHSV(const Mat &imgOrignal, double &h, double &s, double &v){
	vector<Mat> channels;
	split(imgOrignal, channels);
    h = (mean(channels[0])[0]);
    s = (mean(channels[1])[0]);
    v = (mean(channels[2])[0]);
}