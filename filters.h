#include <iostream>
#include <math.h>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

using namespace cv;
using namespace std;

double getDistance(const Mat &imgOrignal, double origH, double origS, double origV){
	Mat tmp, uit;
	Mat uitvoer;
	
	blur(imgOrignal, tmp, Size(3,3));
	inRange(tmp, Scalar(35, 20, 100), Scalar(75, 255, 255), uit); //Threshold the image => enkel groen over houden
	tmp.copyTo(uitvoer, uit);
	
	uitvoer = (tmp + 1 * uitvoer)/2;
	vector<Mat> channels;
	split(uitvoer, channels);
	int aantalWit = (countNonZero(uit)+1);
	
	if (false){
		return 500;
	} else{
		double h,s,v;
		// double h = (mean(channels[0])[0]) - origH;
		h = (sum(channels[0])/aantalWit)[0] - origH;
		s = (sum(channels[1])/aantalWit)[0] - origS;
		// double s = (mean(channels[1])[0]) - origS;
		// if ((mean(channels[1])[0])<40 )
			// s+= 100;
		// double v = (mean(channels[2])[0]) - origV;
		v = (sum(channels[2])/aantalWit)[0] - origV;
		// if ((mean(channels[2])[0])<40 )
			// v+= 100;
		return sqrt(h*h+s*s+v*v);
	}
	
}

double getHSV(const Mat &imgOrignal, double &h, double &s, double &v){
	vector<Mat> channels;
	split(imgOrignal, channels);
    h = (mean(channels[0])[0]);
    s = (mean(channels[1])[0]);
    v = (mean(channels[2])[0]);
}