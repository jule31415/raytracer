#include "stdio.h"
#include "rectxz.h"
#include "math.h"
#include <opencv2/opencv.hpp>
using namespace cv; //neu

rectxz::rectxz(int mx1, int my1, int mz1,

	int xlength1, int zlength1, int fa01, int faf1,  float alb_r1, float alb_g1, float alb_b1, float roughness1)
	:
	formen(mx1, my1, mz1, fa01, faf1,  alb_r1,  alb_g1,  alb_b1, roughness1
		),
	xlength(xlength1), zlength(zlength1)
{
}


rectxz::~rectxz()
{
}


bool rectxz::isobjectonthisray_n(int *bla,  ray *ray2) {
	int q, r, u;

	ray2->get_sp(&sx,&sy,&sz,&px,&py,&pz);
	int a = py - sy;
	if (a) { *bla = (10000*(my - sy) / (a)); }
	else {

		return false;
	}
	if ((*bla>0)&&
		(sx + (*bla*(px - sx)/10000) < (xlength + mx)) &&
		(sx + (*bla*(px - sx)/10000) > mx) &&
		(sz + (*bla*(pz - sz)/10000) < (zlength + mz)) &&
		(sz + (*bla*(pz - sz)/10000) > mz)
		)
	{
		//*fa = (int)(2*my);
		//ray2->set_ni(0,-1,0,sx + int((*bla*(px - sx)/10000)),my,sz + int((*bla*(pz - sz)/10000)));
        if((py-sy)>0){
		    ray2->set_ni(0,-1,0,sx + int((*bla*(px - sx)/10000)),my,sz + int((*bla*(pz - sz)/10000)));
		} else {
		    ray2->set_ni(0,1,0,sx + int((*bla*(px - sx)/10000)),my,sz + int((*bla*(pz - sz)/10000)));
		}
		return true;

	}
	else {

		return false;
	};

}

bool rectxz::isobjectonthisray_s(int *bla,  ray *ray2) {
	int q, r, u;

	ray2->get_sp(&sx,&sy,&sz,&px,&py,&pz);
	int a = py - sy;
	if (a) { *bla = (10000*(my - sy) / (a)); }
	else {

		return false;
	}
	if ((*bla>0)&&
		(sx + (*bla*(px - sx)/10000) < (xlength + mx)) &&
		(sx + (*bla*(px - sx)/10000) > mx) &&
		(sz + (*bla*(pz - sz)/10000) < (zlength + mz)) &&
		(sz + (*bla*(pz - sz)/10000) > mz)
		)
	{
		return true;

	}
	else {

		return false;
	};

}

void rectxz::refract(ray *rayin, ray *rayrefract){
}