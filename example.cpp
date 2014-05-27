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
//#include "filters.h"
//#include "Canny.h"
#include "Squares.h"
#include "Grass.h"
#include "Yellow.h"
#include "zebra.h"

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
    //string filename = argv[2];
    //remove(filename.c_str());
    //namedWindow("orig",CV_WINDOW_NORMAL);
//    namedWindow("filter");
//    createHarrisWindow();
//    createLineDetectionWindow();
//    createFASTWindow();
//    createSquaresWindow();

//    cout<<"Frame;100-2000;2000-5000;5000-10000;10000-100000"<<endl;

    vector<int> minSizes;
//    minSizes.push_back(400);
//    minSizes.push_back(801);
    minSizes.push_back(801);
    minSizes.push_back(4501);
    minSizes.push_back(19001);
    vector<int> maxSizes;
//    maxSizes.push_back(800);
//    maxSizes.push_back(2000);
    maxSizes.push_back(4500);
    maxSizes.push_back(19000);
    maxSizes.push_back(100000);


//    vector<vector<int > > countHistory;
//    countHistory.push_back(*(new vector<int>));
//    countHistory.push_back(*(new vector<int>));
//    countHistory.push_back(*(new vector<int>));
//    countHistory.push_back(*(new vector<int>));
//    countHistory.push_back(*(new vector<int>));

//    ofstream outDat;
//    outDat.open("halfFrame.dat", ios_base::app);
//    ofstream outCsv;
//    outCsv.open("halfFrame.csv", ios_base::app);

    ofstream outDat;
    outDat.open("featurevectors.dat", ios_base::app);
    while(!frame.empty()){
        //cvtColor(frame,frame,CV_RGB2GRAY); => grijs waarden overhouden
//        imshow("orig",frame);

        //  ################################################
        //  ######### DOE ZOTTE SHIT MET UW FRAMES #########
        //  ################################################
        
//        vector<float> featurevector;        // Vul hier uw getallekes in die uw frame gaan beschrijven = de featurevector
        
        //groen herkennen
//        Mat green;
//        greenFilter(frame,green);
//        imshow("filter",green);
        ///*featurevector.push_back(*/matToVal(green);//);

        //andere filters
//        showNextLine(frame);
//        showNextCorners(frame);
//        showNext(frame);
//        nextCanny(frame);

       int zebraFeatures = zebraFilter(frame);//:(
        vector<int> grassFeatures = nextGrass(frame);


//        //Make the image negative
//        Mat sub_mat = Mat::ones(frame.size(), frame.type())*255;
//        subtract(sub_mat, frame, frame);

//        cout<<framenr<<";"<<nextSquares(frame, 100, 2000)
//                     <<";"<<nextSquares(frame, 2000, 5000)
//                     <<";"<<nextSquares(frame, 5000, 10000)
//                     <<";"<<nextSquares(frame, 10000, 100000)<<endl;

        vector<int> counts = nextSquares(frame, minSizes, maxSizes);
//        countHistory[(framenr / 10) % 3] = counts;

        outDat<<"-1";
        for(int countIt = 0; countIt < counts.size(); countIt++){
//            if(framenr > 30){
//                cout <</*" "<<countIt +1<<":"<</(countHistory[0][countIt] + countHistory[1][countIt] + countHistory[2][countIt] + countHistory[3][countIt] + countHistory[4][countIt]) / 5;
//            }
//            else
//                outDat<<" "<<countIt +1<<":"<<counts[countIt];
//                outCsv<<";"<<counts[countIt];
//            cout<<counts[countIt]<<";";
            outDat<<" "<<countIt + 1<<":"<<counts[countIt];
        }
        outDat<<" 4:"<<grassFeatures[0]<<" 5:"<<grassFeatures[1];
        outDat<<" 6:"<<yellowFilter(frame);
        outDat<<" 7:"<<counts[3];

        outDat<<" #"<<framenr<<endl;
//        outCsv<<";"<<framenr<<endl;


//        outColorDat<<" #"<<framenr<<endl;
//        outColorCsv<<";"<<framenr<<endl;

        //  ######################################################
        //  ######### SCHRIJF UW FEATURES NAAR TEXTFILES #########
        //  ######################################################

//                writeToFile(filename,0);
//                writeSpace(filename);

//            for(int i=0; i<featurevector.size(); i++){
//                cout << featurevector.at(i) << " ";
//                    writeToFile(filename,i+1);
//                    writeDoublePoint(filename);
//                writeToFile(filename,featurevector.at(i));
//                writeSpace(filename);

//                if(i!=featurevector.size()-1) writeDoublePoint(filename);
//            }
//            writeEndl(filename);
//            cout << endl;

        //  ###########################
        //  ######### Restart #########
        //  ###########################
//        for(int it = 0; it < 5; it++){
//            framenr++;
//            readVideo.grab();
//        }
        framenr++;
        readVideo >> frame;
        cout<<framenr<<endl;

        if(waitKey(1) != -1)
            waitKey(-1);
    }
//    }
//    waitKey(0);
    return 0;
}



//float matToVal(const Mat &img){
//    //matrix omzetten naar getal
//    Size s = img.size();
//    int cols = s.width;
//    int rows = s.height;

//    double totaal = 0;
//    for (int y  = 0 ; y < rows ; y++){
//        for (int x =0 ; x < cols ; x++){
//            totaal += img.at<double>(x,y);
//        }
//    }
//    return totaal/(cols*rows);


//}
