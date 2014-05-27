#include <iostream>
#include <math.h>
#include <opencv2/core/core.hpp>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

using namespace cv;
using namespace std;

static bool squareEdgeRatio(const vector<Point> &square, double ratioMin, double ratioMax){
    //returns true if ratio of square is between min & max.
    double minX = square[0].x;
    double minY = square[0].y;
    double maxX = square[0].x;
    double maxY = square[0].y;

    for (int i = 1 ; i < square.size(); i++){
        if (square[i].x < minX)
            minX = square[i].x;
        else if (square[i].x > maxX)
            maxX = square[i].x;

        if (square[i].y < minY)
            minY = square[i].y;
        else if (square[i].y > maxY)
            maxY = square[i].y;
    }
    double rat = (maxY - minY) / (maxX - minX);
    return rat > ratioMin && rat < ratioMax ;
}

static double zebra_angle( Point pt1, Point pt2, Point pt0 ){
    double dx1 = pt1.x - pt0.x;
    double dy1 = pt1.y - pt0.y;
    double dx2 = pt2.x - pt0.x;
    double dy2 = pt2.y - pt0.y;
    return (dx1*dx2 + dy1*dy2)/sqrt((dx1*dx1 + dy1*dy1)*(dx2*dx2 + dy2*dy2) + 1e-10);
}
/*
static void findSquaresWithRatio( const Mat& image, vector<vector<Point> >& squares, int minSize,int maxSize ,double minRat, double maxRat){
    int N = 11;
    squares.clear();

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
                Canny(gray0, gray, 0, thresh, 5);
                // dilate canny output to remove potential
                // holes between edge segments
                dilate(gray0, gray, Mat(), Point(-1,-1));
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
                if( approx.size() == 4 &&
                    fabs(contourArea(Mat(approx))) > minSize &&
                    isContourConvex(Mat(approx)) &&
                    fabs(contourArea(Mat(approx))) < maxSize)
                {
                    double maxCosine = 0;

                    for( int j = 2; j < 5; j++ )
                    {
                        // find the maximum cosine of the angle between joint edges
                        double cosine = fabs(zebra_angle(approx[j%4], approx[j-2], approx[j-1]));
                        maxCosine = MAX(maxCosine, cosine);
                    }

                    // if cosines of all angles are small
                    // (all angles are ~90 degree) then write quandrange
                    // vertices to resultant sequence
                    if( maxCosine < 0.3 && squareEdgeRatio(approx,minRat,maxRat))
                        squares.push_back(approx);
                }
            }
        }
    }
}

static void zebra_drawSquares( Mat &image, const vector<vector<Point> >& squares )
{
    for( size_t i = 0; i < squares.size(); i++ )
    {
        const Point* p = &squares[i][0];
        int n = (int)squares[i].size();
        polylines(image, &p, &n, 1, true, Scalar(0,255,0), 1, CV_AA);
    }

    namedWindow("test",CV_WINDOW_AUTOSIZE);
    imshow("test", image);
}
*/
double zebraFilter(const Mat &img){
    //eventueel nog een perspectief toevoegen
    int minVal=150;
    int maxVal=175;
    int blurVal=30;
    int minSize = 100000;//150000;
    int maxSize = 250000;//180000;
    double minRat = 0.16;
    double maxRat = 0.30;

    //Wit uithalen
    Mat t;
    pyrDown(img, t, Size(img.cols/2, img.rows/2));
    pyrUp(t, t, img.size());
    cvtColor(t,t,COLOR_BGR2GRAY);
    blur( t,t, Size(blurVal,blurVal) );
    threshold(t,t,minVal,maxVal,0);
    //Mat kernel = getStructuringElement(MORPH_RECT, Size(50,20));
    //dilate(t,t,kernel);

    //edges deruithalen
    Canny(t,t,100,100,3);

    //Houghtransform
    std::vector<cv::Vec4i> lines;
    cv::HoughLinesP(t, lines, 1, CV_PI/180, 70, 30, 10);
/*
    namedWindow("brol",CV_WINDOW_AUTOSIZE);
    imshow("brol", t);
*/
    vector<vector<Point> > contours;
    findContours(t,contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);//NONE);
    //cout << " found: " << contours.size() << " contours";

    vector<Point> approx;
    vector<vector<Point> > squares;
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
        if( approx.size() == 4 &&
            fabs(contourArea(Mat(approx))) > minSize &&
            isContourConvex(Mat(approx)) &&
            fabs(contourArea(Mat(approx))) < maxSize)
        {
            double maxCosine = 0;

            for( int j = 2; j < 5; j++ )
            {
                // find the maximum cosine of the angle between joint edges
                double cosine = fabs(zebra_angle(approx[j%4], approx[j-2], approx[j-1]));
                maxCosine = MAX(maxCosine, cosine);
            }

            // if cosines of all angles are small
            // (all angles are ~90 degree) then write quandrange
            // vertices to resultant sequence
            if( maxCosine < 0.75 && squareEdgeRatio(approx,minRat,maxRat)) //ROMMEL
                squares.push_back(approx);
        }
    }
    /*
    if (squares.size() > 0 ){
        cout << " | squares: " << squares.size() << endl;
    }*/

//vorige methode
//    img.copyTo(out,t);
//    vector<vector<Point> > squares;
//    findSquaresWithRatio(out,squares,minsize,maxsize,minRat,maxRat);

//tekenen
//    Mat brol = img.clone();
//    zebra_drawSquares(brol,squares);
    return squares.size();
}
