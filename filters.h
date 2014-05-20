#include <iostream>
#include <math.h>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

using namespace cv;
using namespace std;

double getDistance(const Mat &imgOrignal, double origH, double origS, double origV){

	vector<Mat> channels;
	split(imgOrignal, channels);
    double h = (mean(channels[0])[0]) - origH;
    double s = (mean(channels[1])[0]) - origS;
    double v = (mean(channels[2])[0]) - origV;
	
	return sqrt(h*h+s*s+v*v);
}

double getHSV(const Mat &imgOrignal, double &h, double &s, double &v){
	vector<Mat> channels;
	split(imgOrignal, channels);
    h = (mean(channels[0])[0]);
    s = (mean(channels[1])[0]);
    v = (mean(channels[2])[0]);
}