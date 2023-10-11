#include <opencv2/opencv.hpp>
#ifndef RAY_H
#define RAY_H
#include "lightsource.h"
using namespace cv;

class ray
{
private:
	int px;
	int  py;
	int pz;
	int sx;
	int sy;
	int sz;
	float ix;
	float iy;
	float iz;
	float nx,ny,nz;


public:
	ray(
	int sx,
	int sy,
	int sz,
	int px,
	int  py,
	int pz,
	float ix,
	float iy,
	float iz,
	float nx,
	float ny,
	float nz
		);

	~ray();
	void set_sp(int sx1, int sy1, int sz1, int px1, int py1, int pz1);
	void get_sp(int *sx1, int *sy1, int *sz1, int *px1, int *py1, int *pz1);
	void get_ni(float *nx1, float *ny1, float *nz1, float *ix1, float *iy1, float *iz1);
	void set_ni(float nx1, float ny1, float nz1, float ix1, float iy1, float iz1);
	void beleuchtung(float *fa, Lightsource *lightsource1);
	void refl(ray *ray_refl);
};

#endif