#include "stdio.h"
#include "CSzene.h"
#include "math.h"
#include <sys/time.h>
#include <ctime>
#include <algorithm>
#include <chrono>
#include <stdio.h>
#include <string>
#include <opencv2/opencv.hpp>
#include <typeinfo>
using namespace cv;
//using namespace std; //neu
//using namespace std;
using std::cout;
using std::array;
using std::endl;
using std::chrono::duration_cast;
using std::chrono::microseconds;
using std::chrono::seconds;
using std::chrono::system_clock;

#define xClient 1000
#define yClient 1000

struct MouseParams
{
    Mat draw2;
    int xwords[54]={0};
    int ywords[54]={0};
    int npoints=0;
};


void CallBackFuncSpheres(int event, int lo, int hi, int flags, void* data){

if  ( event == EVENT_LBUTTONDOWN )
     {
         MouseParams* mp = (MouseParams*)data;
         Mat & draw2 = mp->draw2;
         std::cout << " " << hi;
         mp->xwords[mp->npoints]=lo;
         mp->ywords[mp->npoints]=hi;
         mp->npoints=mp->npoints+1;
         rectangle( draw2, Point(lo,hi), Point(lo+1,hi+1), Scalar(255,255,255), -1, 8);
         imshow("CreateSpheres", draw2);
     }
}


CSzene::CSzene(int *xwort, int *ywort) //
	:

	//mykugel(0, 2000, 2500, 500, 0, 5,3,0,0,0.1),
	//Zylinder(500, 3000, 300, -300, 40, 20, 0, 5,-1,-1,0,0.1),
	//xyebene1(0, 500, 2000, 500, 500, 0, 5,0,0,0,0.1),
	//rectyz1(0, 500, 1500, 500, 500, 0, 5,0,0,0,0.1),
	//rectyz2(500, 500, 1500, 500, 500, 0, 5,0,0,0,0.1),
	//rectxz1(0, 1000, 1500, 500, 500, 0, 5,0,0,0,0.1),
	//rectxz2(0, 500, 1500, 500, 500, 0, 5,0,0,0,0.1),
	xy2(-5000, -5000, 150, 10000,10000, 0, 5,0.2,0.9,0.5,0),
	yz1(0, -1000, -400, 800,800, 0, 5,0,0,0,0),
	yz2(400, -1000, -400, 800,800, 0, 5,0,0,0,0)
	//myray(0,0,0,0,0,0,0,0,0,0,0,0),
	//myray2(0,0,0,0,0,0,0,0,0,0,0,0)
{
	/*formenliste[1] = &mykugel;
	formenliste[0] = &Zylinder;
	formenliste[2] = &xyebene1;
	formenliste[3] = &rectyz1;
	formenliste[4] = &rectyz2;
	formenliste[5] = &rectxz1;
	formenliste[6] = &rectxz2;
	*/
	formenliste[0] = &xy2;
	formenliste[1] = &yz1;
	formenliste[2] = &yz2;

	alpha=0;
	phi=0;//1.5;
	sx=0;
	sy=0;//4000;
	sz=-1000; //-2000
	oldalph=-1;
	oldphi=-1;


	formencount = 3;//55;
	CreateNewSpheres();
	ray *mr=new ray(0,0,0,0,0,0,0,0,0,0,0,0);
	ray *mr2=new ray(0,0,0,0,0,0,0,0,0,0,0,0);
	for (int ir=0;ir<4;ir++){
	        mr= new ray(0,0,0,0,0,0,0,0,0,0,0,0);
	        mr2= new ray(0,0,0,0,0,0,0,0,0,0,0,0);
	        myray[ir]=&*(mr);
	        myray2[ir]=&*(mr2);
	};
	Lightsource *li0 = new Lightsource(0,0,-50,100);
	for (int ri=1;ri<4;ri++){
	    for (int phii=0;phii<5;phii++){
	        int lix=int(150+70.0*ri*cos(1.26*phii));
	        int liy=int(100+70.0*ri*sin(1.26*phii));
	        li0= new Lightsource(10*lix,10*liy,-350,250);
	        lightsourcelist[5*(ri-1)+phii]=&*(li0);
	    };
    };
}


CSzene::~CSzene(void)
{
}

void CSzene::CreateNewSpheres(){

    Kugel *p = new Kugel(70 * 1, 20 * 1 + 200, 500, 50 + 7 * 0, 0, 5,0,0,0,0.1);
	formenliste[3] = &*p;
	namedWindow("CreateSpheres", WINDOW_AUTOSIZE);
    MouseParams mopa;
    mopa.draw2= Mat::zeros(250, 250, CV_8UC3);
	setMouseCallback("CreateSpheres", CallBackFuncSpheres, &mopa); //null //&myszene

	char key='a';
	while (key=='a'){

	key=waitKey(0);
	}
    for (int i = 0; i < 52; i++) {
        p = new Kugel( 10*mopa.xwords[i], 10*mopa.ywords[i] , 50, 100, 0.2+0.2*sin(i), 5,0,0.5+0.5*sin(i+4),0.5+0.5*sin(i+6),0.1+0.1*sin(3*i));
		//p = new Kugel( *(xwort+i), *(ywort+i) , 50, 10, 0, 5,0,0,0);
		formenliste[4+i] = &*(p); //9+i
		formencount=formencount+1;
	}
}

void CSzene::Moveviewphi(int mousey, int mousex) {

#pragma omp target

        sz = sz;// + ((250.0 - mousey)*cos(alpha));
        sx = sx;// - ((250.0 - mousey)*sin(alpha));
        alpha = alpha + (atan((250.0 - mousex)/1300));
        phi = phi + (atan((250.0 - mousey)/1300));
}

void CSzene::Moveviewwalk(int forw, int right) {

#pragma omp target

        sz = sz + 10*forw*cos(alpha)*cos(phi);
        sx = sx - 10*forw*sin(alpha)*cos(phi);
	sy = sy - forw*cos(alpha)*sin(phi);

}

void CSzene::Draw(Mat draw1, int res,int nrender) {

//#pragma omp target
	int len_ray, len_ray1;
	float fa_r,fa_g, fa_b,fa1;
	float fa_r_sum,fa_g_sum, fa_b_sum;
	float ix1,iy1,iz1;
	float nx1,ny1,nz1;
	int lx1,ly1,lz1,b1;
	time_t tstart0, tstart1, tend;
    int ibest;
    bool isshadow,isshadow1;
    bool hitsobject;
    float alb_r, alb_g, alb_b;
	cout << xClient ;
	for (int lx =0; lx < 1000; lx=lx+res) {
		for (int ly = 0; ly < 1000; ly=ly+res) {
		    fa_r_sum=0;fa_g_sum=0;fa_b_sum=0;
		    for (int irender = 0; irender < nrender;irender++) {
		    alb_r=1;alb_g=1;alb_b=1;
		    hitsobject=true;
			fa_r=0;fa_g=0;fa_b=0;
			auto tstart0 = duration_cast<microseconds>(system_clock::now().time_since_epoch()).count();
			raythroughscreen(lx,ly);
			for (int ireflexion=0;ireflexion<3;ireflexion++){
                fa1=0;
                len_ray = 10000000;
                if (hitsobject==true){
                    for (int i = 0; i < formencount; i++) {
                        bool isooa3 = formenliste[i]->isobjectonthisray_s(&len_ray1, &*myray[ireflexion]);
                        if (isooa3 && len_ray1 < len_ray) {
                            len_ray = len_ray1;
                            ibest=i;
                        }
                    }
                    auto tstart1 = duration_cast<microseconds>(system_clock::now().time_since_epoch()).count();
                    if (len_ray < 10000000) {
                        bool isooa3 = formenliste[ibest]->isobjectonthisray_n(&len_ray1, &*myray[ireflexion]);
                        formenliste[ibest]->albedo_mult(&alb_r,&alb_g,&alb_b);
                        for (int li=0;li<15;li++){
                            myray[ireflexion]->get_ni(&nx1,&ny1,&nz1,&ix1,&iy1,&iz1);
                            lightsourcelist[li]->get_xyzb(&lx1,&ly1,&lz1,&b1);
                            myray2[ireflexion]->set_sp(int(ix1),int(iy1),int(iz1),lx1,ly1,lz1);
                            isshadow=false;
                            for(int i_obj=0;i_obj<formencount;i_obj++){
                                isshadow1=formenliste[i_obj]->isobjectonthisray_s(&len_ray1, &*myray2[ireflexion]);
                                if (isshadow1 && len_ray1>0 && len_ray1<10000){
                                    isshadow=true;
                                };
                            };
                            if (not isshadow){
                                myray[ireflexion]->beleuchtung(&fa1, &(*(lightsourcelist[li])));
                            };
                            myray[ireflexion]->refl(&*myray[ireflexion+1]);
                        };
                    fa_r=fa_r+(alb_r*fa1);
                    fa_g=fa_g+(alb_g*fa1);
                    fa_b=fa_b+(alb_b*fa1);
                    } else {
                        hitsobject=false;
                    };
                };
			};
			fa_r_sum=fa_r_sum+fa_r;fa_g_sum=fa_g_sum+fa_g;fa_b_sum=fa_b_sum+fa_b;
			 //0.5*fa+20
			auto tend = duration_cast<microseconds>(system_clock::now().time_since_epoch()).count();
			}
			rectangle(draw1, Point(lx, ly), Point(lx+res-1, ly+res-1),Scalar(fa_r_sum/nrender,fa_g_sum/nrender, fa_b_sum/nrender), -1, 8);
		}
	}
	rectangle(draw1, Point(1, 450), Point(50, 500),Scalar(150, 50, 150), -1, 8);
	rectangle(draw1, Point(1, 550), Point(50, 600),Scalar(150, 50, 150), -1, 8);
	rectangle(draw1, Point(1, 650), Point(50, 700),Scalar(150, 50, 150), -1, 8);
}

void CSzene::Drawfast(Mat draw1) {

//#pragma omp target
	int len_ray, len_ray1;
	float fa, fa1;
	float ix1,iy1,iz1;
	float nx1,ny1,nz1;
	int lx1,ly1,lz1,b1;
	float alb_r, alb_g, alb_b;
	time_t tstart0, tstart1, tend;
    int ibest;
    bool isshadow,isshadow1;
    bool hitsobject;
	cout << xClient ;
	for (int lx =0; lx < 1000; lx=lx+3) {
		for (int ly = 0; ly < 1000; ly=ly+3) {
		    hitsobject=true;
			fa=0;
			auto tstart0 = duration_cast<microseconds>(system_clock::now().time_since_epoch()).count();
			raythroughscreen(lx,ly);
			alb_r=1;alb_g=1;alb_b=1;
			for (int ireflexion=0;ireflexion<1;ireflexion++){
                fa1=0;
                len_ray = 10000000;
                if (hitsobject==true){
                    for (int i = 0; i < formencount; i++) {
                        bool isooa3 = formenliste[i]->isobjectonthisray_s(&len_ray1, &*myray[ireflexion]);
                        if (isooa3 && len_ray1 < len_ray) {
                            len_ray = len_ray1;
                            ibest=i;
                        }
                    }
                    auto tstart1 = duration_cast<microseconds>(system_clock::now().time_since_epoch()).count();
                    if (len_ray < 10000000) {
                        formenliste[ibest]->albedo_mult(&alb_r,&alb_g,&alb_b);
                        bool isooa3 = formenliste[ibest]->isobjectonthisray_n(&len_ray1, &*myray[ireflexion]);
                        for (int li=0;li<15;li++){
                            myray[ireflexion]->get_ni(&nx1,&ny1,&nz1,&ix1,&iy1,&iz1);
                            lightsourcelist[li]->get_xyzb(&lx1,&ly1,&lz1,&b1);

                            myray[ireflexion]->beleuchtung(&fa1, &(*(lightsourcelist[li])));
                        };
                    fa=fa+pow(0.5,ireflexion)*fa1;
                    } else {
                        hitsobject=false;
                    };
                };
			};

			rectangle(draw1, Point(lx, ly), Point(lx+2, ly+2),Scalar(fa*alb_r, fa*alb_g, fa*alb_b), -1, 8);
			auto tend = duration_cast<microseconds>(system_clock::now().time_since_epoch()).count();
		}
	}
	rectangle(draw1, Point(1, 450), Point(50, 500),Scalar(150, 50, 150), -1, 8);
	rectangle(draw1, Point(1, 550), Point(50, 600),Scalar(150, 50, 150), -1, 8);
	rectangle(draw1, Point(1, 650), Point(50, 700),Scalar(150, 50, 150), -1, 8);
	Point p1(0, 250), p2(500, 250);
	Point p3(250, 0), p4(250, 500);
	line(draw1, p1, p2, Scalar(255, 255, 255),2, LINE_8);
	line(draw1, p3, p4, Scalar(255, 255, 255),2, LINE_8);
}

void CSzene::raythroughscreen(int lx2,int ly2) {

		if (oldalph != alpha) {
			cosalph = cos(alpha);
			sinalph = sin(alpha);
			oldalph = alpha;
		}
		if (oldphi != phi) {
                        cosphi = cos(phi);
                        sinphi = sin(phi);
                        oldphi = phi;
                }
		int p1x = (lx2 - 250)*cosalph - (1300 * sinalph);
		int p1y = ly2  - 250;
		int p1z = (lx2 - 250)*sinalph + (1300 * cosalph);
		int py = (p1y)*cosphi - (p1z * sinphi) + sy;
        int px = p1x + sx;
        int pz = (p1y)*sinphi + (p1z * cosphi) + sz;

		/*int p1y = (ly2-250)*cosphi - (1300 * sinphi);
        int p1x = lx2-250 ;
        int p1z = (ly2-250)*sinphi + (1300 * cosphi);
        int px = (p1x)*cosalph - (p1z * sinalph)+sx;
		int py = p1y+sy;
		int pz = (p1x)*sinalph + (p1z * cosalph)+sz;*/
        myray[0]->set_sp(sx,sy,sz,px,py,pz);

}

