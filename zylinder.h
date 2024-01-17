//#pragma once
#include "formen.h"
#include <opencv2/opencv.hpp>
using namespace cv; //neu
class zylinder: public formen
{
private:
	
	int yo;
	int yu;
	int Radius;

public:
	zylinder(
		int mx1, int my1, int mz1,
		int yu1, int yo1,
		int Radius1, int fa01, int faf1,  float alb_r1, float alb_g1, float alb_b1, float roughness1
	);
	~zylinder();

	//void  punktaufprojektionsebeneberechnen(float alpha, float lx, float ly);

	bool isobjectonthisray_n(int *bla, ray *ray2);
	bool isobjectonthisray_s(int *bla, ray *ray2);
	void refract(ray *rayin, ray *rayrefracted);
	
	//;
};
