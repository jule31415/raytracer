//#pragma once
#include "formen.h"
#include <opencv2/opencv.hpp>
using namespace cv; //neu
class rectyz :
	public formen
{
	private:
	int ylength;
	int zlength;
public:
	rectyz(int mx1, int my1, int mz1,
		int ylength1, int zlength, int fa01, int faf1,  float alb_r1, float alb_g1, float alb_b1, float roughness1);
	~rectyz();

	bool isobjectonthisray_n(int *bla, ray *ray2);
	bool isobjectonthisray_s(int *bla, ray *ray2);
	void refract(ray *rayin, ray *rayrefracted);
};

