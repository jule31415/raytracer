//#pragma once
#include "formen.h"
#include <opencv2/opencv.hpp>
using namespace cv; //neu
class rectxy :
	public formen
{
private:
	int xlength;
	int ylength;
public:
	rectxy(int mx1, int my1, int mz1,
		int xlength1, int ylength, int fa01, int faf1,  float alb_r1, float alb_g1, float alb_b1, float roughness1);
	~rectxy();

bool isobjectonthisray_n(int *bla, ray *ray2);
bool isobjectonthisray_s(int *bla, ray *ray2);
void refract(ray *rayin, ray *rayrefracted);
};