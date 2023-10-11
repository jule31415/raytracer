#include "stdio.h"
#include "formen.h"
#include "math.h"
#include <opencv2/opencv.hpp>
using namespace cv;
/*
float formen::oldalph = 0;
float formen::cosalph = 0;
float formen::sinalph = 0;

int formen::sx = 0;
int formen::sy = 0;
int formen::sz = 0;

int formen::px = 0;
int formen::py = 0;
int formen::pz = 0;

int formen::oldlx = 0;
int formen::oldly = 0;
int formen::oldlz=0;
float formen::alpha=0;*/

formen::formen(
	int mx1,
	int my1,
	int mz1,
	int fa01,
	int faf1, float alb_r1, float alb_g1, float alb_b1, float roughness1
)
	:
	mx(mx1),
	my(my1),
	mz(mz1),
	fa0(fa01), faf(faf1),
	alb_r(alb_r1), alb_g(alb_g1), alb_b(alb_b1),
	roughness(roughness1)
	
	
{

}


formen::~formen()
{
}
void formen::albedo_mult(float *ar1, float *ag1, float *ab1) { *ar1=*ar1*alb_r; *ag1=*ag1*alb_g; *ab1=*ab1*(alb_b);} //;
//void formen::mittelpunkt(int ax1, int ay1, int az1) { mx = mx+(vx); my = my+(vy); mz = mz+(vz); vx = vx+(ax1); vy = vy+(ay1); vz = vz+(az1); }
//void formen::mxa(int *x) { *x = mx; }
//void formen::mya(int *x) {*x= my; }
//void formen::mza(int *x) {*x= mz; }
//int formen::vxa() { return vx; }int formen::vya() { return vy; }int formen::vza() { return vz; }
