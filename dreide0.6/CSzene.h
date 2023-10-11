//#pragma once
#include "Kugel.h"
#include "zylinder.h"
#include "rectyz.h"
#include "rectxz.h"
#include "quadrat.h"
#include "ray.h"
#include <opencv2/opencv.hpp>
using namespace cv; //neu

//#define TRHEADNUM 8


class CSzene
{
public:
	CSzene(int *xwort,int *ywort); //änderung void //
	~CSzene(void);
	void Moveviewphi(int mousey, int mousex);
	void Draw(Mat draw1, int res, int nrender);
	void Drawfast(Mat draw1);
	int xClient, yClient;
	void Moveviewwalk(int forw, int right);
	void CreateNewSpheres();
	void  raythroughscreen(int lx, int ly);

private:
	/*Kugel mykugel;
	zylinder Zylinder;
	rectxy xyebene1;
	rectyz rectyz1;
	rectyz rectyz2;
	rectxz rectxz1;
	rectxz rectxz2;
	*/
	rectxy xy2;
	rectyz yz1;
	rectyz yz2;


    //ray myray,myray2;
    int sx=100;
    int sy=0;
    int sz=-2000;
    float alpha=0;
    float phi=0;
	float oldalph;
	float cosalph;
	float sinalph;
	float oldphi;
    float cosphi;
    float sinphi;
	//ray myray;


	formen * formenliste[56];
	int formencount;
	Lightsource * lightsourcelist[16];
	ray * myray[4];
	ray  * myray2[4];

};

