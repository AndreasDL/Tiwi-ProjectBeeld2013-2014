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

//config values
//split image in 3x3 blocks & set descriptions for windows (debug)
const int dimX = 3;const string descX[] = {"links", "midden", "rechts"};
const int dimY = 3;const string descY[] = {"boven", "midden", "onder"};

int main( int argc, char** argv ) {

    VideoCapture readVideo;
    if (argc < 1){
        cout << "Derp! You need to specify a video and/or image" << endl;
        return 1;
    }
    readVideo.open(argv[1]);
    Mat frame;

    readVideo >> frame;
    if(frame.empty()){
        fprintf(stderr,"Something went wrong with the video capture.\n");
        return 2;
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
    namedWindow("orig"); //display the original video
    namedWindow(descX[0]+descY[2]);
	/*for (int y = 0 ; y < dimY ; y++){
		for (int x = 0 ; x < dimX ; x++){
		  namedWindow(descX[x]+descY[y]);
          cout << descX[x]+descY[y] << endl;
		}
	}*/

    int key = -1;
    while(!frame.empty() && key == -1){

        //  ################################################
        //  ######### DOE ZOTTE SHIT MET UW FRAMES #########
        //  ################################################
        
        vector<float> featurevector;        // Vul hier uw getallekes in die uw frame gaan beschrijven = de featurevector
        
        //orig weergeven
        //imshow("orig",frame);

        //Afbeelding splitsen in 3x3
        vector<vector<Mat> > blokjes; //afbeelding in 9 stukken kappen
        split(frame,blokjes,dimX,dimY);//default 3x3, opgeven van dimensies ook mogelijk!
		
		
		Mat green;
		//enkel blok 0, 2 => links onder
        featurevector.push_back(greenFilter(blokjes[0][2],green));
		imshow(descX[0]+descY[2],green);
		imshow("orig",blokjes[0][2]);
		/*/
        //alle blokjes
		for (int y = 0; y< dimY; y++){
			for (int x = 0; x< dimX; x++){
				featurevector.push_back(greenFilter(blokjes[x][y],green)); //opslaan in feature vector
				imshow(descX[x]+descY[y],green); //weergeven
			}
		}*/
        
        //andere filters
        
        //  ######################################################
        //  ######### SCHRIJF UW FEATURES NAAR TEXTFILES #########
        //  ######################################################

//                writeToFile(filename,0);
//                writeSpace(filename);

        cout << "Frame: " << framenr << " ft.: ";
        for(int i=0; i<featurevector.size(); i++){

            cout << featurevector.at(i) << " ";
//                    writeToFile(filename,i+1);
//                    writeDoublePoint(filename);
//                writeToFile(filename,featurevector.at(i));
//                writeSpace(filename);

//                if(i!=featurevector.size()-1) writeDoublePoint(filename);
        }
        cout << endl;
//            writeEndl(filename);
//            cout << endl;

        //  ###########################
        //  #########  next  ##########
        //  ###########################

        framenr++;
        readVideo >> frame;
        key = waitKey(1);
    }
    cout << "press any key to exit" << endl;
    waitKey(0);
    return 0;
}