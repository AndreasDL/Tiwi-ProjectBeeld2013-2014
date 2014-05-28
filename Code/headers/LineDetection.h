#ifndef LINEDETECTION_H
#define LINEDETECTION_H


#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace cv;
using namespace std;

Mat srcLines;
int threshLines = 50;
int max_threshLines = 500;

/// Function header
void updateLines( int, void* );

void createLineDetectionWindow()
{
  /// Create a window and a trackbar
  namedWindow( "Lines detected", CV_WINDOW_NORMAL );
  createTrackbar( "Threshold: ", "Lines detected", &threshLines, max_threshLines, updateLines );
}

void showNextLine(Mat source){
    srcLines = source;
    updateLines(0, 0);
}

/** @function updateLines */
void updateLines( int, void*){
    Mat edges, gray;
    cvtColor(srcLines, gray, CV_GRAY2BGR);
    Canny(gray, edges, 50 , 150 ,3);

    vector<Vec4i> lines;

    HoughLinesP(edges, lines, 1, CV_PI/180, threshLines, 0, 0 );
    for( size_t i = 0; i < lines.size(); i++ )
    {
        Vec4i l = lines[i];
        line( srcLines, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0,0,255), 3, CV_AA);
    }

    imshow("Lines detected", srcLines);
}

#endif // LINEDETECTION_H
