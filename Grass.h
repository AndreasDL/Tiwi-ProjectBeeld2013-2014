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

double getDistance(const Mat &imgOrignal, double origH, double origS, double origV){

    vector<Mat> channels;
    split(imgOrignal, channels);
    double h = (mean(channels[0])[0]) - origH;
    double s = (mean(channels[1])[0]) - origS;
    double v = (mean(channels[2])[0]) - origV;

    return sqrt(h*h+s*s+v*v);
}

vector<int> nextGrass(Mat frame){
    cvtColor(frame, frame, COLOR_BGR2HSV);

    //groen herkennen
    int iHighH = 73;
    int iHighS = 109;
    int iHighV = 94;

    vector<int> featurevector;        // Vul hier uw getallekes in die uw frame gaan beschrijven = de featurevector

    vector<vector<Mat> > blokjes; //afbeelding in 9 stukken kappen
    split(frame,blokjes, 3, 1);//default 3x3, opgeven van dimensies ook mogelijk!

    for (int i = 0; i<blokjes.size(); i++){
        for (int j = 0; j<blokjes[i].size(); j+=2){

            //Dit stuk in 9 kappen
            vector<vector<Mat> > kleineblokjes; //afbeelding in 9 stukken kappen
            split(blokjes[i][j],kleineblokjes);//default 3x3, opgeven van dimensies ook mogelijk!
            double afstand=9999999999;
            for (int x = 0; x<blokjes.size(); x++){
                for (int y = 0; y<blokjes[i].size(); y++){
                    afstand = min(afstand, getDistance(kleineblokjes[x][y], iHighH, iHighS, iHighV));
                }
            }
            featurevector.push_back(afstand);
        }
    }

    return featurevector;

}


#endif // GRASS_H
