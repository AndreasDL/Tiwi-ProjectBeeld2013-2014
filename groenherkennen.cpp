#include <stdio.h>
#include <iostream>
#include <numeric>
#include "opencv/cv.h"
#include "opencv/highgui.h"
#include <string>
#include <cstdio>
#include <ctime>
#include <iostream>
#include <fstream>
#include <opencv2/core/core.hpp>
#include "splitter.h"
#include "filters.h"

using namespace std;
using namespace cv;

int main( int argc, char** argv ) {

	VideoCapture readVideo;
    readVideo.open(argv[2]);
    Mat frame;

    readVideo >> frame;
    if(frame.empty()){
        fprintf(stderr,"Something went wrong with the video capture.\n");
        return 1;
    }


    int framenr = 0;
    string filename = argv[2];
    	
	ofstream outfile;
	outfile.open(argv[3], ios_base::app);

    while(!frame.empty()){
		Mat imgHSV;
		cvtColor(frame, imgHSV, COLOR_BGR2HSV); //Convert the captured frame from ?? to HSV
	
        double h, s, v;
		getHSV(imgHSV, h, s, v);
		outfile << filename << " @ " << framenr << ";" << h << ";" << s << ";" << v << ";" << argv[1] << endl;
		
        framenr++;
        readVideo >> frame;
        waitKey(1);
    }
	
	
	return 0;
	
}