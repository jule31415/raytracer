//#pragma once
#ifndef FORMEN_H
#define FORMEN_H
#include <opencv2/opencv.hpp>
#include "ray.h"
using namespace cv;

class formen
{
protected:
	
	int mx;
	int my;
	int mz;
	int px;
	int  py;
	int pz;
	int sx;
	int sy;
	int sz;
	int faf;
	int fa0;
	float alb_r; float alb_g; float alb_b;
	float roughness;

public:
	formen(
		int mx1,
		int my1,
		int mz1,
		int fa01, int faf1,
		float alb_r1, float alb_g1,float alb_b1, float roughness
		);

	~formen();

	virtual bool isobjectonthisray_n(int *bla, ray *ray2) = 0;
	virtual bool isobjectonthisray_s(int *bla, ray *ray2) = 0;
	virtual void refract(ray *rayin, ray *rayrefracted){};
	void albedo_mult(float *ar1, float *ag1, float *ab1);
	//void mittelpunkt(int vx1, int xy1, int vz1);
	//void mxa(int *x); void mya(int *x); void mza(int *x); int vxa(); int vya(); int vza();
};

#endif // FORMEN_H
