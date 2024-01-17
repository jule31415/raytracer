#include "stdio.h"
#include "zylinder.h"
#include "math.h"
#include <inttypes.h>
#pragma omp declare target
#include <opencv2/opencv.hpp>
using namespace cv; //neu
#include <iostream> //neu
using std::cout; //neu

zylinder::zylinder(
	int mx1, int my1, int mz1,
	int yu1, int yo1,
	int Radius1,
	int fa01, int faf1,  float alb_r1, float alb_g1, float alb_b1, float roughness1
)
	:
	formen(mx1, my1, mz1, fa01, faf1,  alb_r1, alb_g1, alb_b1, roughness1),
	yu(yu1),
	yo(yo1),
	Radius(Radius1)
	
{
}

zylinder::~zylinder()
{
}

inline int64_t powi(int64_t a) { return a*a; }


bool zylinder::isobjectonthisray_n(int *bla,ray *ray2) {
	int64_t q, r, u;
	ray2->get_sp(&sx,&sy,&sz,&px,&py,&pz);

	q = (powi(px - sx) +  powi(pz - sz))/10;
	r =( 2 * ((px - sx)*(sx - mx)  + ((pz - sz)*(sz - mz))))/10;
	u = (powi(sx - mx) + powi(sz - mz) - powi(Radius))/10;

	if (pow(r,2) - (4 * q*u) > 0) {
		*bla =( -(r + sqrt(powi(r) - (4 * q*u))) / (2 * q))*10000;
		if ((*bla) > 0) {
			int x;
			x = (sy + (*bla*(py - (sy))/10000));

			if ((x < yo+my) && (x > (yu+my))) {
				//*fa = 5 * (x-my);
				//light reflexion
				float psx=float(*bla)/10000.0*(px-sx)+sx;
			    float psy=float(*bla)/10000.0*(py-sy)+sy;
			    float psz=float(*bla)/10000.0*(pz-sz)+sz;
                float nx1=(psx-mx)/sqrt(float(pow(psx-mx,2)+pow(psz-mz,2)));
                float nz1=(psz-mz)/sqrt(float(pow(psx-mx,2)+pow(psz-mz,2)));
                ray2->set_ni(nx1,0,nz1, psx, psy, psz);
				return true;
			}
			else {
				*bla = ((-(r - sqrt(powi(r) - (4 * q*u))) / (2 * q)))*10000;
				if ((*bla) > 0) {
					int x;
					x = (sy + (*bla*(py - (sy))/10000));
					//*fa = 5 * x;
					if ((x < yo+my) && (x > (yu+my))) {
						//*fa = 5 * (x-my); //neu auskommentiert
						//float nx1=(psx-mx)/sqrt(float(pow(psx-mx,2)+pow(psz-mz,2)));
                        //float nz1=(psz-mz)/sqrt(float(pow(psx-mx,2)+pow(psz-mz,2)));
                        //ray2->set_ni(nx1,0,nz1, psx, psy, psz);
						return true;
					}
					else { return false; }
				};
			}
		}
		else { return false; }
	}
	else { return false; }
}

bool zylinder::isobjectonthisray_s(int *bla,ray *ray2) {
	int64_t q, r, u;
	ray2->get_sp(&sx,&sy,&sz,&px,&py,&pz);

	q = (powi(px - sx) +  powi(pz - sz))/10;
	r =( 2 * ((px - sx)*(sx - mx)  + ((pz - sz)*(sz - mz))))/10;
	u = (powi(sx - mx) + powi(sz - mz) - powi(Radius))/10;

	if (pow(r,2) - (4 * q*u) > 0) {
		*bla =( -(r + sqrt(powi(r) - (4 * q*u))) / (2 * q))*10000;
		if ((*bla) > 0) {
			int x;
			x = (sy + (*bla*(py - (sy))/10000));
			if ((x < yo+my) && (x > (yu+my))) {
				return true;
			}
			else {
				*bla = ((-(r - sqrt(powi(r) - (4 * q*u))) / (2 * q)))*10000;
				if ((*bla) > 0) {
					int x;
					x = (sy + (*bla*(py - (sy))/10000));
					//*fa = 5 * x;
					if ((x < yo+my) && (x > (yu+my))) {
						return true;
					}
					else { return false; }
				};
			}
		}
		else { return false; }
	}
	else { return false; }
}

void zylinder::refract(ray *rayin, ray *rayrefract){

}