#ifndef FASTCORNERDETECTION_H
#define FASTCORNERDETECTION_H

#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace cv;
using namespace std;

/// Global variables
Mat srcCorners, srcCorners_gray;
int threshCorners = 9;
int max_threshCorners = 50;

/// Function header
void updateCorners( int, void* );

/** @function main */
void createFASTWindow()
{
  /// Create a window and a trackbar
  namedWindow( "Corners detected", CV_WINDOW_NORMAL );
  createTrackbar( "threshCornersold: ", "Corners detected", &threshCorners, max_threshCorners, updateCorners );
}

void showNextCorners(Mat source){
    //Load source image and convert it to gray
    srcCorners = source;
    //Show the corners
    updateCorners(0, 0);
}

/** @function cornerHarris_demo */
void updateCorners( int, void* )
{
    vector<KeyPoint> keypoints;

    cvtColor(srcCorners, srcCorners_gray, CV_BGR2GRAY);
    //FAST(srcCorners_gray,keypoints,threshCorners,true);
    goodFeaturesToTrack(srcCorners_gray, keypoints, threshCorners, 0.01, 10);

    for( int j = 0; j < keypoints.size() ; j++ ) {
          if( keypoints[j].response > threshCorners ) {
             circle( srcCorners, keypoints[j].pt, keypoints[j].size,  Scalar(0), 2, 8, 0 );
          }
    }
    /// Showing the result
    imshow( "Corners detected", srcCorners );
}



#endif // FASTCORNERDETECTION_H
