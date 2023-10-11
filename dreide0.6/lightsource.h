#include <opencv2/opencv.hpp>
#ifndef LIGHTSOURCE_H
#define LIGHTSOURCE_H
using namespace cv;

class Lightsource
{
private:
	int lix;
	int liy;
	int liz;
	int br;


public:
	Lightsource(
    int lix,
	int liy,
	int liz,
	int br
		);

	~Lightsource();
	void set_xyzb(int lx1, int ly1, int lz1, int br1);
	void get_xyzb(int *lx1, int *ly1, int *lz1, int *br1);
};

#endif