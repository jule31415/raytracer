//#pragma once
#include "formen.h"
//using namespace std; //neu auskommentiert
#include <opencv2/opencv.hpp>
using namespace cv;

class Kugel: public formen
{
private:
	int Radius;

public:
	Kugel(
		int mx1, int my1, int mz1, 
		int Radius1, int fa01, int faf,  float alb_r1, float alb_g1, float alb_b1, float roughness1
	);
	~Kugel();

    bool isobjectonthisray_n(int *bla, ray *ray2);
    bool isobjectonthisray_s(int *bla, ray *ray2);
    void refract(ray *rayin, ray *rayrefracted);
};

