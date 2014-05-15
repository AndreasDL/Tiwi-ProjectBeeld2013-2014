#ifndef CANNY_H
#define CANNY_H

#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <stdlib.h>
#include <stdio.h>

using namespace cv;

/// Global variables

Mat src, src_gray;
Mat dst, detected_edges;
RNG rng(12345);

int lowThreshold = 30;
int const max_lowThreshold = 100;
int ratio = 3;
int kernel_size = 3;
char* window_name = "Edge Map";

/**
 * @function CannyThreshold
 * @brief Trackbar callback - Canny thresholds input with a ratio 1:3
 */
void CannyThreshold(int, void*)
{
    /// Reduce noise with a kernel 3x3
    blur( src_gray, detected_edges, Size(3,3) );

    /// Canny detector
    Canny( detected_edges, detected_edges, lowThreshold, lowThreshold*ratio, kernel_size );

    /// Using Canny's output as a mask, we display our result
    dst = Scalar::all(0);

    src.copyTo( dst, detected_edges);

    vector<Vec2f> lines;
    HoughLines(dst, lines, 1, CV_PI/180, 100, 0, 0 );

    for( size_t i = 0; i < lines.size(); i++ )
    {
        float rho = lines[i][0], theta = lines[i][1];
        Point pt1, pt2;
        double a = cos(theta), b = sin(theta);
        double x0 = a*rho, y0 = b*rho;
        pt1.x = cvRound(x0 + 1000*(-b));
        pt1.y = cvRound(y0 + 1000*(a));
        pt2.x = cvRound(x0 - 1000*(-b));
        pt2.y = cvRound(y0 - 1000*(a));
        line( src, pt1, pt2, Scalar(0,0,255), 3, CV_AA);
    }

    /// Find contours
    vector<vector<Point> > contours;
    vector<Vec4i> hierarchy;
    findContours( src_gray, contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE, Point(0, 0) );

    vector<Point> approx;
    vector<vector<Point> > squares;
    // test each contour
    for( size_t i = 0; i < contours.size(); i++ )
    {
//        dilate(detected_edges, detected_edges, Mat(), Point(-1,-1));

        // approximate contour with accuracy proportional
        // to the contour perimeter
        approxPolyDP(Mat(contours[i]), approx, arcLength(Mat(contours[i]), true)*0.02, true);
        // square contours should have 4 vertices after approximation
        // relatively large area (to filter out noisy contours)
        // and be convex.
        // Note: absolute value of an area is used because
        // area may be positive or negative - in accordance with the
        // contour orientation
        if( approx.size() > 3 /*&& approx.size() < 6*/ /*&&
            fabs(contourArea(Mat(approx))) > 100 &&
            isContourConvex(Mat(approx))*/ /*&&
            fabs(contourArea(Mat(approx))) < 20000*/)
        {
//            double maxCosine = 0;

//            for( int j = 2; j < 5; j++ )
//            {
//                // find the maximum cosine of the angle between joint edges
//                double cosine = fabs(angle(approx[j%4], approx[j-2], approx[j-1]));
//                maxCosine = MAX(maxCosine, cosine);
//            }

//            // if cosines of all angles are small
//            // (all angles are ~90 degree) then write quandrange
//            // vertices to resultant sequence
//            if( maxCosine < 0.3 )
                squares.push_back(approx);
        }
    }

    /// Draw contours
//    Mat drawing = Mat::zeros( detected_edges.size(), CV_8UC3 );
//    for( int i = 0; i< squares.size(); i++ )
//    {
//        Scalar color = Scalar( rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255) );
//        drawContours( src, squares, i, color, 2, 8, hierarchy, 0, Point() );
//    }

//    /// Using Canny's output as a mask, we display our result
//    dst = Scalar::all(0);

//    src.copyTo( dst, detected_edges);
    imshow( window_name, src_gray );
}


/** @function main */
void nextCanny( Mat frame )
{
    /// Load an image
    src = frame;

    /// Create a matrix of the same type and size as src (for dst)
    dst.create( src.size(), src.type() );

    /// Convert the image to grayscale
    cvtColor( src, src_gray, CV_BGR2GRAY );

    /// Create a window
    namedWindow( window_name, CV_WINDOW_AUTOSIZE );

    /// Create a Trackbar for user to enter threshold
    createTrackbar( "Min Threshold:", window_name, &lowThreshold, max_lowThreshold, CannyThreshold );

    /// Show the image
    CannyThreshold(0, 0);
}

#endif // CANNY_H
