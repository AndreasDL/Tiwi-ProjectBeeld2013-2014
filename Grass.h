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

vector<Scalar> nextGrass(Mat frame){
    vector<Scalar> output;

    vector<vector<Mat> > splitImages;
    split(frame, splitImages, 3, 1);

    //computes mean over roi
    Scalar avgPixelIntensityLeft = cv::mean( splitImages[0][0] );
    Scalar avgPixelIntensityRight = cv::mean( splitImages[2][0] );

    output.push_back(avgPixelIntensityLeft);
    output.push_back(avgPixelIntensityRight);

    return output;
}


#endif // GRASS_H
