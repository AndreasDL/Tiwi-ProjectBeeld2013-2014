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
//#include "Canny.h"
#include "Squares.h"

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

//    readVideo.set(CV_CAP_PROP_POS_MSEC, 1000 * 60 * 2);
//    readVideo.set(CV_CAP_PROP_FPS, 1);

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
//    namedWindow("orig");
//    namedWindow("filter");

//    createHarrisWindow();
//    createLineDetectionWindow();
//    createFASTWindow();
//    createSquaresWindow();

//    cout<<"Frame;100-2000;2000-5000;5000-10000;10000-100000"<<endl;

    vector<int> minSizes;
    minSizes.push_back(400);
    minSizes.push_back(801);
    minSizes.push_back(2001);
    minSizes.push_back(5001);
    minSizes.push_back(9001);
    vector<int> maxSizes;
    maxSizes.push_back(800);
    maxSizes.push_back(2000);
    maxSizes.push_back(5000);
    maxSizes.push_back(9000);
    maxSizes.push_back(100000);


    vector<vector<int > > countHistory;
    countHistory.push_back(*(new vector<int>));
    countHistory.push_back(*(new vector<int>));
    countHistory.push_back(*(new vector<int>));
    countHistory.push_back(*(new vector<int>));
    countHistory.push_back(*(new vector<int>));

    ofstream outDat;
    outDat.open("halfFrame.dat", ios_base::app);
    ofstream outCsv;
    outCsv.open("halfFrame.csv", ios_base::app);

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

        contrastShizzle(frame, frame);

//        //Make the image negative
//        Mat sub_mat = Mat::ones(frame.size(), frame.type())*255;
//        subtract(sub_mat, frame, frame);

//        cout<<framenr<<";"<<nextSquares(frame, 100, 2000)
//                     <<";"<<nextSquares(frame, 2000, 5000)
//                     <<";"<<nextSquares(frame, 5000, 10000)
//                     <<";"<<nextSquares(frame, 10000, 100000)<<endl;

        vector<int> counts = nextSquares(frame, minSizes, maxSizes);
        countHistory[(framenr / 10) % 5] = counts;

        for(int countIt = 0; countIt < counts.size(); countIt++){
//            if(framenr > 30){
//                cout <</*" "<<countIt +1<<":"<<*/(countHistory[0][countIt] + countHistory[1][countIt] + countHistory[2][countIt] + countHistory[3][countIt] + countHistory[4][countIt]) / 5;
//            }
//            else
                outDat<<" "<<countIt +1<<":"<<counts[countIt];
                outCsv<<";"<<counts[countIt];
//            cout<<counts[countIt]<<";";
        }
        outDat<<" #"<<framenr<<endl;
        outCsv<<";"<<framenr<<endl;

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
        for(int it = 0; it < 5; it++){
            framenr++;
            readVideo.grab();
        }
        framenr++;
        readVideo >> frame;

        if(waitKey(1) != -1)
            waitKey(-1);
    }
//    }
//    waitKey(0);
    return 0;
}

void contrastShizzle(const Mat &imgOriginal, Mat &output){

    Mat outputLocal = Mat::zeros(imgOriginal.size(), imgOriginal.type());

    /// Initialize values
    //std::cout << " Basic Linear Transforms " << std::endl;
    //std::cout << "-------------------------" << std::endl;
    //std::cout << "* Enter the alpha value [1.0-3.0]: "; std::cin >> alpha;
    //std::cout << "* Enter the beta value [0-100]: "; std::cin >> beta;

//	namedWindow("Control", CV_WINDOW_AUTOSIZE); //create a window called "Control"
    //Create trackbars in "Control" window
//	cvCreateTrackbar("alpha", "Control", &alpha, 20);
    double a = 6 / 10.0;
    a += 1;

    /// Do the operation new_image(i,j) = alpha*image(i,j) + beta
    for (int y = 0; y < imgOriginal.rows; y++)
    {
        for (int x = 0; x < imgOriginal.cols; x++)
        {
            for (int c = 0; c < 3; c++)
            {
                outputLocal.at<Vec3b>(y, x)[c] =
                    saturate_cast<uchar>(a*(imgOriginal.at<Vec3b>(y, x)[c]) + 20);
            }
        }
    }
    output = outputLocal;
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
