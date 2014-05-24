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


using namespace std;
using namespace cv;

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
		string file;          // string which will contain the result
		ostringstream convert;   // stream used for the conversion
		convert << argv[2] << "/" << framenr << ".jpg";      // insert the textual representation of 'Number' in the characters in the stream
		file = convert.str(); // set 'Result' to the contents of the stream

		vector<int> compression_params;
		compression_params.push_back(CV_IMWRITE_JPEG_QUALITY);
		compression_params.push_back(95);
		imwrite(file, frame, compression_params);

		framenr++;
		framenr++;
		framenr++;
		framenr++;
		framenr++;
        readVideo >> frame;
        readVideo >> frame;
        readVideo >> frame;
        readVideo >> frame;
        readVideo >> frame;
    }
    return 0;
}