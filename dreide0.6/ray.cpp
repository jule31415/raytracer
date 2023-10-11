#include "stdio.h"
#include "ray.h"
#include "math.h"
#include <opencv2/opencv.hpp>
using namespace cv;


ray::ray(
	int sx1,
	int sy1,
	int sz1,
	int px1,
	int  py1,
	int pz1,
	float ix1,
	float iy1,
	float iz1,
	float nx1,
	float ny1,
	float nz1
)
	:
	sx(sx1),
	sy(sy1),
	sz(sz1),
	px(px1),
	py(py1),
	pz(pz1),
	ix(ix1),
	iy(iy1),
	iz(iz1),
	nx(nx1),
	ny(ny1),
	nz(nz1)


{

}


ray::~ray()
{
}
void ray::set_sp(int sx1, int sy1, int sz1, int px1, int py1, int pz1){
	sx=sx1;
	sy=sy1;
	sz=sz1;
	px=px1;
	py=py1;
	pz=pz1;
	};

void ray::get_sp(int *sx1, int *sy1, int *sz1, int *px1, int *py1, int *pz1){
    *sx1=sx;
    *sy1=sy;
    *sz1=sz;
    *px1=px;
    *py1=py;
    *pz1=pz;
};

void ray::get_ni(float *nx1, float *ny1, float *nz1, float *ix1, float *iy1, float *iz1){
    *nx1=nx;
    *ny1=ny;
    *nz1=nz;
    *ix1=ix;
    *iy1=iy;
    *iz1=iz;
}

void ray::set_ni(float nx1, float ny1, float nz1, float ix1, float iy1, float iz1){
    nx=nx1;
    ny=ny1;
    nz=nz1;
    ix=ix1;
    iy=iy1;
    iz=iz1;
}

void ray::beleuchtung(float *fa, Lightsource *lightsource1){
    int lsx,lsy,lsz,br1;
    lightsource1->get_xyzb(&lsx,&lsy,&lsz,&br1);
    float cosanglelight=float(((lsx-ix)*nx+(lsy-iy)*ny+(lsz-iz)*nz))/sqrt(float(pow(lsx-ix,2)+pow(lsy-iy,2)+pow(lsz-iz,2)));
	float cosangleeye=float(((sx-ix)*nx+(sy-iy)*ny+(sz-iz)*nz))/sqrt(float(pow(sx-ix,2)+pow(sy-iy,2)+pow(sz-iz,2)));
	float parallelcomp=float(((lsx-ix)*nx+(lsy-iy)*ny+(lsz-iz)*nz));
	float reflx=2*nx*parallelcomp-(lsx-ix); //no sqrt in parallelcomp
	float refly=2*ny*parallelcomp-(lsy-iy); //no sqrt in parallelcomp
	float reflz=2*nz*parallelcomp-(lsz-iz); //no sqrt in parallelcomp
	float cosanglespecular=float(((sx-ix)*reflx+(sy-iy)*refly+(sz-iz)*reflz))/sqrt(float(pow(sx-ix,2)+pow(sy-iy,2)+pow(sz-iz,2)))/sqrt(float(pow(reflx,2)+pow(refly,2)+pow(reflz,2)));
	float disttolight=float(pow(lsx-ix,2)+pow(lsy-iy,2)+pow(lsz-iz,2))/250000;
	if (cosanglelight>0) {
		*fa=*fa+(br1*0.4*cosangleeye*cosanglelight/disttolight); //0.6
		if (cosanglespecular>0) {
            *fa=*fa+(br1*0.6*pow(cosanglespecular,32)*cosanglelight/disttolight);}
	}
}

void ray::refl(ray *ray_refl){
    float parcomp=-nx*(ix-sx)-ny*(iy-sy)-nz*(iz-sz);
    float rex=sx-ix-2*(sx-ix-parcomp*nx);
    float rey=sy-iy-2*(sy-iy-parcomp*ny);
    float rez=sz-iz-2*(sz-iz-parcomp*nz);
    ray_refl->set_sp(ix,iy,iz,ix+rex,iy+rey,iz+rez);
}