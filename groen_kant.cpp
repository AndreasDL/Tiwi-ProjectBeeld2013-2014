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


//usage groen_kant (1|-1) inputfile outputfile
using namespace std;
using namespace cv;

float matToVal(const Mat &img);

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

	ofstream outfile;
	outfile.open(argv[3], ios_base::app);
	
	// namedWindow("00");
	// namedWindow("01");
	// namedWindow("02");
	
    while(!frame.empty()){
        vector<float> featurevector;        // Vul hier uw getallekes in die uw frame gaan beschrijven = de featurevector
        
        //groen herkennen
		int iHighH = 98;
		int iHighS = 129;
		int iHighV = 123;
        vector<vector<Mat> > blokjes; //afbeelding in 9 stukken kappen
        split(frame,blokjes, 3, 1);//default 3x3, opgeven van dimensies ook mogelijk!
		
		//outfile << argv[1];
		cout << framenr << "-" << argv[1];
		outfile << framenr << "-" << argv[1];
		for (int i = 0; i<blokjes.size(); i++){
			for (int j = 0; j<blokjes[i].size(); j++){
				int afstand = getDistance(blokjes[i][j], iHighH, iHighS, iHighV);
				
				cout  << " " << (j+1) + i * blokjes[i].size() << ":" << afstand;
				outfile  << " " << (j+1) + i * blokjes[i].size() << ":" << afstand;
			}
		}
		outfile << endl;
		cout << endl;
		
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