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
#include "headers/Squares.h"
#include "headers/Grass.h"
#include "headers/Yellow.h"
#include "headers/zebra.h"
#include "headers/YellowRectangles.h"

using namespace std;
using namespace cv;

float matToVal(const Mat &img);
void contrastShizzle(const Mat &imgOriginal, Mat &output);

int main( int argc, char** argv ) {

    if(argv[1] == "")
        argv[1] = "20140226_h_10fps.avi";
    VideoCapture readVideo;
    readVideo.open(argv[1]);
    Mat frame;

    readVideo >> frame;
    if(frame.empty()){
        fprintf(stderr,"Something went wrong with the video capture.\n");
        return 1;
    }

    int framenr = 0;

    vector<int> minSizes;
    minSizes.push_back(801);
    minSizes.push_back(4501);
    minSizes.push_back(19001);
    vector<int> maxSizes;
    maxSizes.push_back(4500);
    maxSizes.push_back(19000);
    maxSizes.push_back(100000);

    ofstream outDat;
    outDat.open("featurevectors.dat", ios_base::app);
    while(!frame.empty()){
        vector<int> grassFeatures = nextGrass(frame);
        vector<int> counts = nextSquares(frame, minSizes, maxSizes);

        outDat<<"-1";
        for(int countIt = 0; countIt < counts.size(); countIt++){
            outDat<<" "<<countIt + 1<<":"<<counts[countIt];
        }
        outDat<<" 4:"<<grassFeatures[0]<<" 5:"<<grassFeatures[1];
        outDat<<" 6:"<<yellowFilter(frame);
		outDat<<" 7:"<< yellowRectangleFilter(frame);
        //outDat << " 8:"<< zebraFilter(frame);
        outDat<<" #"<<framenr<<endl;

//skip frames
//        for(int it = 0; it < 5; it++){
//            framenr++;
//            readVideo.grab();
//        }
        framenr++;
        readVideo >> frame;
        cout<< "Frame: " << framenr<<endl;

        if(waitKey(1) != -1)
            waitKey(-1);
    }
    return 0;
}
