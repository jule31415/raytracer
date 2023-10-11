// Win32Project2.cpp : Definiert den Einstiegspunkt f�r die Anwendung.
//


//#include "Win32Project2.h"
#include <string>
#include <math.h>
//#include <zmouse.h>
#include "CSzene.h"
#include <ctime>
#include <algorithm>
#include <chrono>
using std::endl;
using std::chrono::duration_cast;
using std::chrono::milliseconds;
using std::chrono::seconds;
using std::chrono::system_clock;


#include "stdio.h"
#include <opencv2/opencv.hpp>
#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <stdio.h>


#include <iostream>



using std::cout;
//using namespace cv; neu auskommentiert



#define MAX_LOADSTRING 100
#define NUM 1000
#define MAXPOINTS 1000
#define xClient 1000
#define yClient 1000
int hi1, lo1;
bool bewegen;
Mat draw = Mat::zeros(xClient, yClient, CV_8UC3);
//int the opject of szene
//int *xspheres
//int *yspheres
int xspheres[34]={94,81,65,57,67,83,83,74,58,117,124,133,137,149,157,140,168,190,198,222,245,252,194,210,230,250,196,205,238,248, 192,215,226,251};
int yspheres[34]={60,49,49,61,78,86,102,110,115,118,92,69,49,69,93,93,   117,121,44, 120,44, 119,83, 83, 83, 83, 60,60,60,60,100,100,100,100};
//std::array<int, 34> xspheres;
//std::array<int, 34> yspheres;
//int* xpheres=150+(50+5*i1)*cos(i1/3);
//int* yspheres=150+(50+5*i1)*sin(i1/3);
//CSzene myszene;
CSzene myszene(xspheres,yspheres);  //

unsigned int wait = 0;
char key='t';
void CallBackFunc(int event, int lo, int hi, int flags, void* userdata); //void*




int main(int argc, char const *argv[])
{
	/*int xspheres[34]={94,81,65,57,67,83,83,74,58,117,124,133,137,149,157,140,168,190,198,222,245,252,194,210,230,250,196,205,238,248, 192,215,226,251};
	int yspheres[34]={60,49,49,61,78,86,102,110,115,118,92,69,49,69,93,93,   117,121,44, 120,44, 119,83, 83, 83, 83, 60,60,60,60,100,100,100,100};
	for (int i=0;i<34;i++){
        	xspheres[i]=150+(50+5*i)*cos(i/3);
        	yspheres[i]=150+(50+5*i)*sin(i/3);}
	myszene(xspheres,yspheres);*/
	
	namedWindow("geometrie", WINDOW_AUTOSIZE);
	rectangle( draw, Point(1,1), Point(1000,1000), Scalar(0,0,0), -1, 8);
	imshow("geometrie", draw);
	setMouseCallback("geometrie", CallBackFunc, NULL); //null //&myszene
	while (true){

	key=waitKey(0);
	}
	return 0;
}

void CallBackFunc(int event, int lo, int hi, int flags, void* data){ //void*

	   if  ( event == EVENT_LBUTTONDOWN )
     {
	 cout<<"key "<<key<<" ";
         lo1= lo;
         hi1= hi;
         std::cout << hi;
         rectangle( draw, Point(1,1), Point(1000,1000), Scalar(0,0,0), -1, 8);
	 Point p1(0, 250), p2(500, 250);
	 Point p3(250, 0), p4(250, 500);
	 line(draw, p1, p2, Scalar(255, 255, 255),2, LINE_8);
	 line(draw, p3, p4, Scalar(255, 255, 255),2, LINE_8);
	 auto tstart2 = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
	 if (hi<500 && hi>450 && lo>0 && lo<50){
        myszene.Draw(draw,2,1);
        imshow("geometrie", draw);
     } else if (hi<600 && hi>550 && lo>0 && lo<50){
        myszene.Draw(draw,1,1);
     } else if (hi<700 && hi>650 && lo>0 && lo<50){
        myszene.Draw(draw,1,20);
     } else
     {
	 if (key=='t'){
         	 myszene.Moveviewphi(hi1, lo1); //.
	 }
	 if (key=='f'){
		 myszene.Moveviewwalk(250-hi,0);
		 key='t';
	 }


	 myszene.Drawfast(draw);
	 imshow("geometrie", draw);
	 };
	 auto tstart3 = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
     cout<<" xClient "<<xClient<<" ";
	 imshow("geometrie", draw);
     auto tstart4 = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
	 cout<<"zeitgesamtrechnen"<<(tstart3-tstart2)<<"zeitgesamtmalen"<<(tstart4-tstart3);
     }
}


