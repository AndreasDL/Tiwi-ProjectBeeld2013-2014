#include <iostream>
#include <math.h>
#include <opencv2/core/core.hpp>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

using namespace cv;
using namespace std;
int iLowH = 19;
int iHighH = 43;
int iLowS = 87; 
int iHighS = 87;
int iLowV = 124;
int iHighV = 102;
int iDistance = 60;
double iHighGreen = sqrt(iHighH*iHighH + iHighS*iHighS + iHighV*iHighV);
double iLowGreen = sqrt(iLowH*iLowH + iLowS*iLowS + iLowV*iLowV);


double getDistance(const Mat &imgOrignal, double origH, double origS, double origV){

	vector<Mat> channels;
	split(imgOrignal, channels);
    double h = (mean(channels[0])[0]) - origH;
    double s = (mean(channels[1])[0]) - origS;
    double v = (mean(channels[2])[0]) - origV;
	
	return sqrt(h*h+s*s+v*v);
}

double greenFilter(const Mat &imgOriginal, Mat &output){ 
    Mat imgHSV;
    cvtColor(imgOriginal, imgHSV, COLOR_BGR2HSV); //Convert the captured frame from ?? to HSV
	output = imgHSV;
    
	double dist = getDistance(imgHSV, iHighH,iHighS,iHighV);

	if (dist > iDistance){
		vector<Mat> channels;
		split(imgHSV, channels);
		double h = (mean(channels[0])[0]);
		double s = (mean(channels[1])[0]);
		double v = (mean(channels[2])[0]);
		output.setTo(cv::Scalar(h,s,v)); //show mean color
		cvtColor(output, output, COLOR_HSV2BGR);
	}
	
    return dist;
}

static double angle( Point pt1, Point pt2, Point pt0 )
{
    double dx1 = pt1.x - pt0.x;
    double dy1 = pt1.y - pt0.y;
    double dx2 = pt2.x - pt0.x;
    double dy2 = pt2.y - pt0.y;
    return (dx1*dx2 + dy1*dy2)/sqrt((dx1*dx1 + dy1*dy1)*(dx2*dx2 + dy2*dy2) + 1e-10);
}

static void findSquares( const Mat& image, vector<vector<Point> >& squares, int minSize,int maxSize ){
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
                //Canny(gray0, gray, 0, thresh, 5);
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
                        double cosine = fabs(angle(approx[j%4], approx[j-2], approx[j-1]));
                        maxCosine = MAX(maxCosine, cosine);
                    }

                    // if cosines of all angles are small
                    // (all angles are ~90 degree) then write quandrange
                    // vertices to resultant sequence
                    if( maxCosine < 0.3 )
                        squares.push_back(approx);
                }
            }
        }
    }
}

static void drawSquares( Mat& image, const vector<vector<Point> >& squares )
{
    for( size_t i = 0; i < squares.size(); i++ )
    {
        const Point* p = &squares[i][0];
        int n = (int)squares[i].size();
        polylines(image, &p, &n, 1, true, Scalar(0,255,0), 3, CV_AA);
    }

    namedWindow("test",CV_WINDOW_AUTOSIZE);
    imshow("test", image);
}


double zebraFilter(const Mat &img) {//, Mat &out){
    /*
    int minVal=170;
    int maxVal=225;
    int blurVal=30;
    
    int thresh = 50;
    cvtColor(img,out,COLOR_BGR2GRAY);
    blur( out,out, Size(blurVal,blurVal) );
    threshold(out,out,minVal,maxVal,0);

    Mat t;
    img.copyTo(t,out);*/

    //Werkt beter zonder witte filtering, blurren zorgt ervoor dat vervormt wordt & werkt het vuil dus niet
    vector<vector<Point> > squares;
    findSquares(img,squares,150000,180000);
/*
    Mat out;
    img.copyTo(out);
    drawSquares(out,squares);*/
    return squares.size();
    //cout << "\nfound " << squares.size() << " squares" << endl;
}