#include "stdio.h"
#include "Kugel.h"
#include "math.h"
#include "formen.h"
#include <inttypes.h>
#include <stdio.h>
#include <string>
#include <iostream> //neu
#include <opencv2/opencv.hpp>
using namespace cv; //neu
using std::cout; //neu
using std::rand;

#pragma omp declare target

Kugel::Kugel(
	int mx1,int my1, int mz1, 
	int Radius1, int fa01, int faf1, float alb_r1, float alb_g1, float alb_b1, float roughness1

)
	:
	Radius(pow(Radius1,2)),
	formen(mx1, my1, mz1, fa01, faf1, alb_r1,alb_g1,alb_b1,roughness1)
	
{

	
}

Kugel::~Kugel()
{
}
inline int64_t powi(int64_t a) { return a*a; }


unsigned int sqrt32(unsigned long n)
{
	unsigned int c = 0x8000;
	unsigned int g = 0x8000;

	for (;;) {
		if (g*g > n)
			g ^= c;
		c >>= 1;
		if (c == 0)
			return g;
		g |= c;
	}
}



bool Kugel::isobjectonthisray_n(int *bla, ray *ray2) {
	int64_t q,u,r;
	//long int thats important;
	ray2->get_sp(&sx,&sy,&sz,&px,&py,&pz);

	q = (powi(px - sx)+ powi(py - sy)+ powi(pz - sz))/10;
	r = 2 * ((px - sx)*(sx - mx) + ((py - sy)*(sy - my)) + ((pz - sz)*(sz - mz)))/10;
	u =( powi(sx - mx) + powi(sy - my) + powi(sz - mz) - Radius)/10;
	if (pow(r, 2) - (4 * q*u) > 0) {
		unsigned long ul = (powi(r) - (4 * q*u));

		*bla = -((( r+(sqrt(ul)))) / (2 * q))*10000;
		if ((*bla) > 0) {
			int x=0;

			x = (*bla*(pz - (sz))/10000)+sz;

			float lsx=0.0;
			float lsy=0.0;
			float lsz=0.0;
			float psx=float(*bla)/10000.0*(px-sx)+sx;
			float psy=float(*bla)/10000.0*(py-sy)+sy;
			float psz=float(*bla)/10000.0*(pz-sz)+sz;
			float rr=sqrt(Radius);
                float ra_x=(0.5-rand()*rr/RAND_MAX)*roughness;
                float ra_y=(0.5-rand()*rr/RAND_MAX)*roughness;
                float ra_z=(0.5-rand()*rr/RAND_MAX)*roughness;
                float nx1=(psx-mx+ra_x)/sqrt(float(pow(psx-mx+ra_x,2)+pow(psy-my+ra_y,2)+pow(psz-mz+ra_z,2)));
                float ny1=(psy-my+ra_y)/sqrt(float(pow(psx-mx+ra_x,2)+pow(psy-my+ra_y,2)+pow(psz-mz+ra_z,2)));
                float nz1=(psz-mz+ra_z)/sqrt(float(pow(psx-mx+ra_x,2)+pow(psy-my+ra_y,2)+pow(psz-mz+ra_z,2)));
                ray2->set_ni(nx1,ny1,nz1, psx, psy, psz);
			return true;
		}
		else { return false; }
	}
	else { return false; }
}

bool Kugel::isobjectonthisray_s(int *bla, ray *ray2) {
	int64_t q,u,r;
	//long int thats important;
	ray2->get_sp(&sx,&sy,&sz,&px,&py,&pz);

	q = (powi(px - sx)+ powi(py - sy)+ powi(pz - sz))/10;
	r = 2 * ((px - sx)*(sx - mx) + ((py - sy)*(sy - my)) + ((pz - sz)*(sz - mz)))/10;
	u =( powi(sx - mx) + powi(sy - my) + powi(sz - mz) - Radius)/10;
    if (pow(r, 2) - (4 * q*u) > 0) {
		unsigned long ul = (powi(r) - (4 * q*u));
		*bla = -((( r+(sqrt(ul)))) / (2 * q))*10000;
		if ((*bla) > 0) {
			return true;
		}
		else { return false; }
	}
	else { return false; }
}

void Kugel::refract(ray *rayin, ray *rayrefract){

}



#pragma omp end declare target
