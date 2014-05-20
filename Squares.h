#ifndef SQUARES_H
#define SQUARES_H

// The "Square Detector" program.
// It loads several images sequentially and tries to find squares in
// each image

#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

#include <iostream>
#include <math.h>
#include <string.h>

#include "SplitImage.h"

using namespace cv;
using namespace std;

int thresh = 50, maxThresh = 300, N = 11;
int threshOppMin = 100, maxThreshOppMin = 100000;
int threshOppMax = 2000, maxThreshOppMax = 100000;

int sqRed = 0, sqGreen = 255, sqBlue = 0;

vector<vector<vector<Point> > >squares;

vector<int> minSizes, maxSizes;

const char* wndname = "Square Detection Demo";
Mat image;


void update(int, void*);

// helper function:
// finds a cosine of angle between vectors
// from pt0->pt1 and from pt0->pt2
static double angle( Point pt1, Point pt2, Point pt0 )
{
    double dx1 = pt1.x - pt0.x;
    double dy1 = pt1.y - pt0.y;
    double dx2 = pt2.x - pt0.x;
    double dy2 = pt2.y - pt0.y;
    return (dx1*dx2 + dy1*dy2)/sqrt((dx1*dx1 + dy1*dy1)*(dx2*dx2 + dy2*dy2) + 1e-10);
}

// returns sequence of squares detected on the image.
// the sequence is stored in the specified memory storage
static void findSquares( const Mat& image, vector<vector<vector<Point> > >& squares )
{
    Mat pyr, timg, gray0(image.size(), CV_8U), gray;

    // down-scale and upscale the image to filter out the noise
    pyrDown(image, pyr, Size(image.cols/2, image.rows/2));
    pyrUp(pyr, timg, image.size());
    vector<vector<Point> > contours;

    // find squares in every color plane of the image
    for( int c = 0; c < 3; c++ )
    {
        int ch[] = {c, 0};
        mixChannels(&timg, 1, &gray0, 1, ch, 1);

        // try several threshold levels
        for( int l = 0; l < N; l++ )
        {
            // hack: use Canny instead of zero threshold level.
            // Canny helps to catch squares with gradient shading
            if( l == 0 )
            {
                // apply Canny. Take the upper threshold from slider
                // and set the lower to 0 (which forces edges merging)
                Canny(gray0, gray, 80, 200, 5);
                // dilate canny output to remove potential
                // holes between edge segments
                dilate(gray, gray, Mat(), Point(-1,-1));
                erode(gray, gray, Mat(), Point(-1,-1));
            }
            else
            {
                // apply threshold if l!=0:
                //     tgray(x,y) = gray(x,y) < (l+1)*255/N ? 255 : 0
                gray = gray0 >= (l+1)*255/N;
            }

            // find contours and store them all as a list
            findContours(gray, contours, CV_RETR_LIST, CV_CHAIN_APPROX_SIMPLE);

            vector<Point> approx;

            // test each contour
            for( size_t i = 0; i < contours.size(); i++ )
            {
                // approximate contour with accuracy proportional
                // to the contour perimeter
                approxPolyDP(Mat(contours[i]), approx, arcLength(Mat(contours[i]), true)*0.02, true);

                // square contours should have 4 vertices after approximation
                // relatively large area (to filter out noisy contours)
                // and be convex.
                // Note: absolute value of an area is used because
                // area may be positive or negative - in accordance with the
                // contour orientation
                int calculatedArea = fabs(contourArea(Mat(approx)));
                if( approx.size() == 4 &&                    
                    isContourConvex(Mat(approx)))
                {
                    for(int sizes = 0; sizes < minSizes.size();sizes++){
                        if(calculatedArea > minSizes[sizes] &&
                                calculatedArea < maxSizes[sizes]){
                            double maxCosine = 0;

                            for( int j = 2; j < 5; j++ )
                            {
                                // find the maximum cosine of the angle between joint edges
                                double cosine = fabs(angle(approx[j%4], approx[j-2], approx[j-1]));
                                maxCosine = MAX(maxCosine, cosine);
                            }

                            // if cosines of all angles are small
                            // (all angles are ~90 degree) then write quandrange
                            // vertices to resultant sequence
                            if( maxCosine < 0.2 )
                                squares[sizes].push_back(approx);
                        }
                    }
                }
            }
        }
    }
}


// the function draws all the squares in the image
static void drawSquares( Mat& image, const vector<vector<vector<Point> > >& squares )
{
    vector<Scalar> colours;
    colours.push_back(Scalar(255,0,0));     //Blue
    colours.push_back(Scalar(255,255,0));   //Cyan
    colours.push_back(Scalar(0,255,0));     //Green
    colours.push_back(Scalar(0,0,255));     //Red
    colours.push_back(Scalar(255,0,255));   //Purple
    colours.push_back(Scalar(0,255,255));   //Yellow
    for(int j = 0; j < squares.size(); j++){
        for( size_t i = 0; i < squares[j].size(); i++ )
        {
            const Point* p = &squares[j][i][0];
            int n = (int)squares[j][i].size();
            polylines(image, &p, &n, 1, true, colours[j], 3, CV_AA);
        }
    }

    imshow(wndname, image);
}


void createSquaresWindow(){

    namedWindow( wndname, CV_WINDOW_NORMAL );
    createTrackbar( "Threshold: ", wndname, &thresh, maxThresh, update );
//    createTrackbar( "Min opp: ", wndname, &threshOppMin, maxThreshOppMin, update );
//    createTrackbar( "Max opp: ", wndname, &threshOppMax, maxThreshOppMax, update );
}

//vector<int> nextSquares(Mat src)
//{
//    image = src;
//    update(0,0);
//    return squares.size();
//}

vector<int> nextSquares(Mat src, vector<int> minSize, vector<int> maxSize){
    image = src;
    minSizes = minSize;
    maxSizes = maxSize;

    squares.clear();
    for(int i = 0; i < minSizes.size(); i++){
        vector<vector<Point> > newVector;
        squares.push_back(newVector);
    }

    update(0,0);

    vector<int> counts;
    for(int i = 0; i < squares.size(); i++)
        counts.push_back(squares[i].size());

    return counts;
}

void update(int, void*){
    vector<vector<Mat> > splitImages;
    split(image, splitImages, 1, 2);
    image = splitImages[0][1];
    findSquares(splitImages[0][1], squares);
//    drawSquares(image, squares);
}



#endif // SQUARES_H
