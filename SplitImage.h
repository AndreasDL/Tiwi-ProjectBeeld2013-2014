#ifndef SPLITIMAGE_H
#define SPLITIMAGE_H

#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

#include <iostream>
#include <math.h>
#include <string.h>

using namespace cv;
using namespace std;

void split(const Mat &input,vector<vector<Mat> > &output,const int dimX = 3, const int dimY = 3){
    output.clear();
    output.resize(dimX);

    int width  = input.cols / dimX;
    int height = input.rows / dimY;

    for (int x = 0 ; x < dimX; x++){
        //create new vector & init size
        output[x] = vector<Mat>(dimY);
        for (int y = 0; y < dimY; y++){
            output[x][y] = input( Rect(x*width, y*height, width, height) );
        }
    }
}

#endif // SPLITIMAGE_H
