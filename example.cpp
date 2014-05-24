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

//  ###################################################
//  ###################################################
//  ######### INTIALISEER FILTERS OF WHATEVER #########
//  ###################################################
//  ###################################################

    
    /*vector<Mat> lijn_afbeeldingen;*/
    

//  #################################
//  #################################
//  ######### Start reading #########
//  #################################
//  #################################

    int framenr = 0;
    namedWindow("orig");
		
    while(!frame.empty()){
        imshow("orig",frame);

        //  ################################################
        //  ######### DOE ZOTTE SHIT MET UW FRAMES #########
        //  ################################################
        
        vector<float> featurevector;        // Vul hier uw getallekes in die uw frame gaan beschrijven = de featurevector
        featurevector = (getGroen(frame));
        
		for(int i=0; i<featurevector.size(); i++){
			cout << featurevector.at(i) << " ";
		}
        //  ###########################
        //  ######### Restart #########
        //  ###########################

        framenr++;
        readVideo >> frame;
        waitKey(1);
    }
    waitKey(0);
    return 0;
}