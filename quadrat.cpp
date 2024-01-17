#include "stdio.h"
#include "quadrat.h"
#include "math.h"
#include <opencv2/opencv.hpp>
using namespace cv; //neu

rectxy::rectxy(int mx1, int my1, int mz1,
	
	int xlength1, int ylength1, int fa01, int faf1,  float alb_r1, float alb_g1, float alb_b1, float roughness1)
	:
	formen(mx1, my1, mz1, fa01, faf1,  alb_r1,  alb_g1,  alb_b1,roughness1),
	xlength(xlength1), ylength(ylength1)
{
}


rectxy::~rectxy()
{
}


bool rectxy::isobjectonthisray_n(int *bla,  ray *ray2) {
	int q, r, u;
	ray2->get_sp(&sx,&sy,&sz,&px,&py,&pz);
	if (pz != sz) { *bla = (10000 * (mz - sz) / (pz - sz)); }
	if (
		(*bla>0)&&
		(sx + ((*bla*(px - sx)/10000)) < (xlength + mx)) &&
		(sx+((*bla*(px - sx)/10000)) > mx) &&
		(sy + ((*bla*(py - sy)/10000)) < (ylength + my))&&
		(sy+((*bla*(py - sy)/10000)) > my)
		)
	{
		if((pz-sz)>0){
		    ray2->set_ni(0,0,-1,sx + int((*bla*(px - sx)/10000)),sy + int((*bla*(py - sy)/10000)),mz);
		} else {
		    ray2->set_ni(0,0,1,sx + int((*bla*(px - sx)/10000)),sy + int((*bla*(py - sy)/10000)),mz);
		}
		return true;

	}
	else { return false; };

}

bool rectxy::isobjectonthisray_s(int *bla,  ray *ray2) {
	int q, r, u;
	ray2->get_sp(&sx,&sy,&sz,&px,&py,&pz);
	if (pz != sz) { *bla = (10000 * (mz - sz) / (pz - sz)); }
	if (
		(*bla>0)&&
		(sx + ((*bla*(px - sx)/10000)) < (xlength + mx)) &&
		(sx+((*bla*(px - sx)/10000)) > mx) &&
		(sy + ((*bla*(py - sy)/10000)) < (ylength + my))&&
		(sy+((*bla*(py - sy)/10000)) > my)
		)
	{
		return true;

	}
	else { return false; };

}

void rectxy::refract(ray *rayin, ray *rayrefract){
}