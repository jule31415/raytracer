#include "stdio.h"
#include "rectyz.h"
#include "math.h"
#include <opencv2/opencv.hpp>
using namespace cv; //neu

rectyz::rectyz(int mx1, int my1, int mz1,

	int ylength1, int zlength1, int fa01, int faf1,  float alb_r1, float alb_g1, float alb_b1, float roughness1)
	:
	formen(mx1, my1, mz1, fa01, faf1, alb_r1, alb_g1, alb_b1, roughness1),
	ylength(ylength1), zlength(zlength1)
{
}


rectyz::~rectyz()
{
}


bool rectyz::isobjectonthisray_n(int *bla,  ray *ray2) {
	int q, r, u;
	ray2->get_sp(&sx,&sy,&sz,&px,&py,&pz);
	int a = px - sx;
	if (a) { *bla = (10000*(mx - sx) / (a)); }
	else { return false; };
	if (
		(*bla>0)&&
		(sy + ((*bla*(py - sy)/10000)) < (ylength + my)) &&
		(sy + ((*bla*(py - sy)/10000)) > my) &&
		(sz + ((*bla*(pz - sz)/10000)) < (zlength + mz)) &&
		(sz + ((*bla*(pz - sz)/10000)) > mz)
		)
	{
		//*fa = (int)(2 * mx);
		if((px-sx)>0){
		    ray2->set_ni(-1,0,0,mx,sy + int((*bla*(py - sy)/10000)),sz + int((*bla*(pz - sz)/10000)));
		} else {
		    ray2->set_ni(1,0,0,mx,sy + int((*bla*(py - sy)/10000)),sz + int((*bla*(pz - sz)/10000)));
		}
		return true;

	}
	else { return false; };

}

bool rectyz::isobjectonthisray_s(int *bla,  ray *ray2) {
	int q, r, u;
	ray2->get_sp(&sx,&sy,&sz,&px,&py,&pz);
	int a = px - sx;
	if (a) { *bla = (10000*(mx - sx) / (a)); }
	else { return false; };
	if (
		(*bla>0)&&
		(sy + ((*bla*(py - sy)/10000)) < (ylength + my)) &&
		(sy + ((*bla*(py - sy)/10000)) > my) &&
		(sz + ((*bla*(pz - sz)/10000)) < (zlength + mz)) &&
		(sz + ((*bla*(pz - sz)/10000)) > mz)
		)
	{
		return true;

	}
	else { return false; };

}

void rectyz::refract(ray *rayin, ray *rayrefract){
}