#include <iostream>
#include <math.h>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

using namespace cv;
using namespace std;




double getDistance(const Mat &imgOriginal, double origH, double origS, double origV){
	Mat tmp, uit, rood, rood2;
	Mat uitvoer;
	
	blur(imgOriginal, tmp, Size(3,3));
	inRange(tmp, Scalar(0, 20, 100), Scalar(15, 255, 255), rood); //Threshold the image => enkel groen over houden
	inRange(tmp, Scalar(165, 20, 100), Scalar(180, 255, 255), rood2); //Threshold the image => enkel groen over houden
	rood = rood | rood2;
	
	
	inRange(tmp, Scalar(30, 10, 10), Scalar(100, 255, 255), uit); //Threshold the image => enkel groen over houden
	tmp.copyTo(uitvoer, uit);
	
	
	vector<Mat> channels, channels2;
	split(uitvoer, channels);
	split(tmp, channels2);
	
	equalizeHist(channels2[2], channels2[2]);

	int aantalWit = (countNonZero(uit)+1);
	
	double fractie = aantalWit / ((tmp.rows * tmp.cols) * 1.0);
	double fractieRood = (countNonZero(rood)+1) / ((tmp.rows * tmp.cols) * 1.0);
	
	double h=0;
	double s=0;
	double v=0;
	double straf = 0;
	
	// h+= ((sum(channels[0])/aantalWit)[0] - origH);
	// s+= ((sum(channels[2])/aantalWit)[0] - origS);
	// v+= ((sum(channels[2])/aantalWit)[0] - origV);

	h+= (mean(channels2[0])[0]) - origH;	
	s+= (mean(channels2[1])[0]) - origS;
	v+= (mean(channels2[2])[0]) - origV;
	
	if (fractie<0.25){
		straf += 20;
		// cout << "staf deel" << endl;
	} else if (fractie > 0.50){
		straf -=20;
		// cout << "bonus deel" << endl;
	}
	// cout << "S: " << (mean(channels2[1])[0]) << endl;
	if ((mean(channels2[1])[0]) < 30 ){
		straf+= 20;
		// cout << "staf S" << endl;
	}
	
	if (fractieRood>0.25){
		straf += fractieRood * 60 * (0.75-fractie);
		// cout << "staf rood - "<< fractie << endl;
	}
	
	// cout << "Score: " << sqrt(h*h+s*s+v*v) + straf << endl;
	
	// cvtColor(uitvoer, uitvoer, COLOR_HSV2BGR);
	// cvtColor(tmp, tmp, COLOR_HSV2BGR);
	// imshow("uit", rood);
	// imshow("uitvoer", uitvoer);
	// imshow("tmp", tmp);
	// waitKey(0);
	
	
	return sqrt(h*h+s*s+v*v) + straf;
}


vector<float> getGroen(Mat frame){
	vector<float> waarden;
	cvtColor(frame, frame, COLOR_BGR2HSV);
	
	//groenwaarden om afstand te berekenen
	int iHighH = 60;
	int iHighS = 109;
	int iHighV = 94;
	
	vector<vector<Mat> > blokjes; //afbeelding in 9 stukken kappen
	split(frame,blokjes, 3, 1);//default 3x3, opgeven van dimensies ook mogelijk!
	
	for (int i = 0; i<2; i++){
	
		// Dit stuk in 9 kappen
		vector<vector<Mat> > kleineblokjes; //afbeelding in 9 stukken kappen
		split(blokjes[i*2][0],kleineblokjes, 3, 3);//default 3x3, opgeven van dimensies ook mogelijk!
		
		double afstand=9999999999;
		for (int x = 0; x<kleineblokjes.size(); x++){
			for (int y = 0; y<kleineblokjes[x].size(); y++){
				double tmpAfstand = getDistance(kleineblokjes[x][y], iHighH, iHighS, iHighV);
				if (afstand > tmpAfstand){
					afstand = tmpAfstand;
				}
			}
		}
		waarden.push_back(afstand);
	}
	
	return waarden;
}

double getHSV(const Mat &imgOrignal, double &h, double &s, double &v){
	vector<Mat> channels;
	split(imgOrignal, channels);
    h = (mean(channels[0])[0]);
    s = (mean(channels[1])[0]);
    v = (mean(channels[2])[0]);
}