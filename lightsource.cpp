#include "stdio.h"
#include "lightsource.h"
#include "math.h"
#include <opencv2/opencv.hpp>
using namespace cv;


Lightsource::Lightsource(
	int lix1,
	int liy1,
	int liz1,
	int br1
)
	:
	lix(lix1),
	liy(liy1),
	liz(liz1),
    br(br1)


{

}


Lightsource::~Lightsource()
{
}
void Lightsource::set_xyzb(int lx1, int ly1, int lz1, int br1){
	lix=lx1;
	liy=ly1;
	liz=lz1;
	br=br1;
	};

void Lightsource::get_xyzb(int *lx1, int *ly1, int *lz1, int *br1){
    *lx1=lix;
    *ly1=liy;
    *lz1=liz;
    *br1=br;
}