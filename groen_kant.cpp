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

	ofstream outfile, xml;
	outfile.open(argv[3], ios_base::app);
	xml.open(argv[4], ios_base::app);
	
	// namedWindow("00");
	namedWindow("film");
	// namedWindow("02");
	
    while(!frame.empty()){
        vector<float> featurevector;        // Vul hier uw getallekes in die uw frame gaan beschrijven = de featurevector
		// resize(frame, frame, Size(640,480));
		// imshow("film",frame);
		// Mat uit;
		// blur(frame, frame, Size(5,5));
		// inRange(frame, Scalar(35, 120, 100), Scalar(110, 255, 255), uit); //Threshold the image => enkel groen over houden
		// imshow("uit", uit);
		
        cvtColor(frame, frame, COLOR_BGR2HSV);
		
        //groen herkennen
		int iHighH = 60;
		int iHighS = 109;
		int iHighV = 94;
        vector<vector<Mat> > blokjes; //afbeelding in 9 stukken kappen
        split(frame,blokjes, 3, 1);//default 3x3, opgeven van dimensies ook mogelijk!
		
		//outfile << argv[1];
		cout << argv[1];
		outfile << argv[1];
		xml << argv[1];
		for (int i = 0; i<blokjes.size(); i++){
			for (int j = 0; j<blokjes[i].size(); j++){
				// imshow("film",frame);
				//Dit stuk in 9 kappen
				// vector<vector<Mat> > kleineblokjes; //afbeelding in 9 stukken kappen
				// split(blokjes[i][j],kleineblokjes, 3, 3);//default 3x3, opgeven van dimensies ook mogelijk!
				
				double afstand = getAantal(blokjes[i][j], iHighH, iHighS, iHighV);
				// double groot = afstand;
				// for (int x = 0; x<kleineblokjes.size(); x++){
					// for (int y = 0; y<kleineblokjes[x].size(); y++){
						// double tmpAfstand = getAantal(kleineblokjes[x][y], iHighH, iHighS, iHighV);
						// if (afstand < tmpAfstand){
							// afstand = tmpAfstand;
							// getHSV(kleineblokjes[x][y], h, s, v);
						// }
					// }
				// }
				// double afstand = getDistance(blokjes[i][j], iHighH, iHighS, iHighV);
				cout << " " << i + 1 << ":" << afstand;
				outfile << " " << i + 1 << ":" << afstand;
				xml << ";" << afstand;
				// outfile << " " << i*3 + 1 << ":" << h << " " << i*3 + 2 << ":" << s << " " << i*3 + 3 << ":" << v;
				// cout << " " << i*3 + 1 << ":" << h << " " << i*3 + 2 << ":" << s << " " << i*3 + 3 << ":" << v;
			}
		}
		
		outfile <<" #" << framenr << " @ " << argv[2] << endl;
		cout <<" #" << framenr << " @ " << argv[2] << endl;
		xml <<";#" << framenr << " @ " << argv[2] << endl;
		
        //  ###########################
        //  ######### Restart #########
        //  ###########################

		// cvtColor(frame, frame, COLOR_HSV2BGR);
		// imshow("film", frame);
		// waitKey(0);
		
		
        framenr++;
        readVideo >> frame;
        waitKey(1);
    }
    // waitKey(0);
    return 0;
}