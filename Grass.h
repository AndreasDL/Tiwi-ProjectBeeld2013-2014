#ifndef GRASS_H
#define GRASS_H

#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

#include <iostream>
#include <math.h>
#include <string.h>

#include "SplitImage.h"

using namespace cv;
using namespace std;

double getAantal(const Mat &imgOriginal, double origH, double origS, double origV){
    int iLowH = 29;
    int iHighH = 94;

    int iLowS = 45;
    int iHighS = 255;

    int iLowV = 36;
    int iHighV = 255;
    Mat uit;
    inRange(imgOriginal, Scalar(iLowH, iLowS, iLowV), Scalar(iHighH, iHighS, iHighV), uit); //Threshold the image => enkel groen over houden

    //morphological opening (remove small objects from the foreground)
    erode(uit, uit, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );
    dilate( uit, uit, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );

    //morphological closing (fill small holes in the foreground)
    dilate( uit, uit, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );
    erode(uit, uit, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );

    return countNonZero(uit);
}

vector<int> nextGrass(Mat frame){
    cvtColor(frame, frame, COLOR_BGR2HSV);

    //groen herkennen
    int iHighH = 60;
    int iHighS = 109;
    int iHighV = 94;

    vector<int> featurevector;

    vector<vector<Mat> > blokjes; //afbeelding in 9 stukken kappen
    split(frame,blokjes, 3, 1);//default 3x3, opgeven van dimensies ook mogelijk!

    for (int i = 0; i<blokjes.size(); i+=2){
        for (int j = 0; j<blokjes[i].size(); j++){

            //Dit stuk in 3 kappen
            double afstand = getAantal(blokjes[i][j], iHighH, iHighS, iHighV);
            featurevector.push_back(afstand);
        }
    }

    return featurevector;

}


#endif // GRASS_H
