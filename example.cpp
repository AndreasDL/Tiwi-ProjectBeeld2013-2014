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
//#include "fileWriter.h" //dees gaan we der echt wel uithalen
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
    //string filename = argv[2];
    //remove(filename.c_str());
    namedWindow("orig");
    namedWindow("filter");

    while(!frame.empty()){
        //cvtColor(frame,frame,CV_RGB2GRAY); => grijs waarden overhouden
        imshow("orig",frame);

        //  ################################################
        //  ######### DOE ZOTTE SHIT MET UW FRAMES #########
        //  ################################################
        
        vector<float> featurevector;        // Vul hier uw getallekes in die uw frame gaan beschrijven = de featurevector
        
        //groen herkennen
        Mat green;
        greenFilter(frame,green);
        imshow("filter",green);
        //featurevector.push_back(matToVal(green));
        
        //andere filters
        
        
        


        //  ######################################################
        //  ######### SCHRIJF UW FEATURES NAAR TEXTFILES #########
        //  ######################################################

//                writeToFile(filename,0);
//                writeSpace(filename);

            for(int i=0; i<featurevector.size(); i++){
                cout << featurevector.at(i) << " ";
//                    writeToFile(filename,i+1);
//                    writeDoublePoint(filename);
//                writeToFile(filename,featurevector.at(i));
//                writeSpace(filename);

//                if(i!=featurevector.size()-1) writeDoublePoint(filename);
            }
//            writeEndl(filename);
//            cout << endl;

        //  ###########################
        //  ######### Restart #########
        //  ###########################

        framenr++;
        readVideo >> frame;
        waitKey(2);
    }
//    }
    waitKey(0);
    return 0;
}

float matToVal(const Mat &img){
    //matrix omzetten naar getal
}