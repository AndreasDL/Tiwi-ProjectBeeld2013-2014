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


//usage get_hsv inputfile
using namespace std;
using namespace cv;

float matToVal(const Mat &img);

int main( int argc, char** argv ) {

    VideoCapture readVideo;
    readVideo.open(argv[1]);
    Mat frame;

    readVideo >> frame;
    if(frame.empty()){
        fprintf(stderr,"Something went wrong with the video capture.\n");
        return 1;
    }

    int framenr = 0;
	
    while(!frame.empty()){
        vector<float> featurevector;        // Vul hier uw getallekes in die uw frame gaan beschrijven = de featurevector
        
		double h,s,v;
		int afstand = getHSV(frame, h, s, v);
		cout  << h << " " << s << "  " << v << endl;
		
        //  ###########################
        //  ######### Restart #########
        //  ###########################

        framenr++;
        readVideo >> frame;
        //waitKey(1);
    }
    //waitKey(0);
    return 0;
}