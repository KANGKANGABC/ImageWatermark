#include <iostream>
#include "attack.h"
#include "evaluate.h"
#include "addwm.h"


void NoAttack(Image* src, Image* wm_src, Image ref)
{
	Image img_adwm = *src;
	Image wm_extr = *wm_src;
#ifdef addwm02
	image_getwm02(ref,img_adwm,wm_extr);
#endif
#ifdef addwm05
	image_getwm05(img_adwm,wm_extr);
#endif
	getNC(wm_src, &wm_extr);
	}

void GaussNoise(Image* src, Image* wm_src, Image ref)
{
	Image img_adwm = *src;
	Image wm_extr = *wm_src;
	img_adwm.addNoise(GaussianNoise,0.01);
#ifdef addwm02
	image_getwm02(ref,img_adwm,wm_extr);
#endif
#ifdef addwm05
	image_getwm05(img_adwm,wm_extr);
#endif
	cout<<" ";
	getPSNR(&ref,&img_adwm);
	getNC(wm_src, &wm_extr);
	}

void ImpulseNoiseAttack(Image* src, Image* wm_src, Image ref)
{
	Image img_adwm = *src;
	Image wm_extr = *wm_src;
	img_adwm.addNoise(ImpulseNoise,0.01);
#ifdef addwm02
	image_getwm02(ref,img_adwm,wm_extr);
#endif
#ifdef addwm05
	image_getwm05(img_adwm,wm_extr);
#endif
	cout<<" ";
	getPSNR(&ref,&img_adwm);
	getNC(wm_src, &wm_extr);
	}

void Rotate(Image* src, Image* wm_src, Image ref)
{
	Image img_adwm = *src;
	Image wm_extr = *wm_src;
	img_adwm.rotate(30);
	img_adwm.crop(Geometry(800,800));
#ifdef addwm02
	image_getwm02(ref,img_adwm,wm_extr);
#endif
#ifdef addwm05
	image_getwm05(img_adwm,wm_extr);
#endif
	cout<<" ";
	getPSNR(&ref,&img_adwm);
	getNC(wm_src, &wm_extr);
	}

void Shear(Image* src, Image* wm_src, Image ref)
{
	Image img_adwm = *src;
	Image wm_extr = *wm_src;
	for (int x=0;x<160;x++)		//height
	{
		for (int y=0;y<800;y++)		//width
		{
			img_adwm.pixelColor(y,x,Color(0,0,0,0));
		}
	}
#ifdef addwm02
	image_getwm02(ref,img_adwm,wm_extr);
#endif
#ifdef addwm05
	image_getwm05(img_adwm,wm_extr);
#endif
	cout<<" ";
	getPSNR(&ref,&img_adwm);
	getNC(wm_src, &wm_extr);
	}

void Compress(Image* src, Image* wm_src, Image ref)
{
	Image img_adwm = *src;
	Image wm_extr = *wm_src;
	img_adwm.compressType(UndefinedCompression);
	img_adwm.write("img_adm_src.png");
	//img_adwm.read("img_adm_dst.jpg");
#ifdef addwm02
	image_getwm02(ref,img_adwm,wm_extr);
#endif
#ifdef addwm05
	image_getwm05(img_adwm,wm_extr);
#endif
	getNC(wm_src, &wm_extr);
	}

void TransformFormat(Image* src, Image* wm_src, Image ref)
{
	Image img_adwm = *src;
	Image wm_extr = *wm_src;
	//img_adwm.write("img_adm.jpg");
	//img_adwm.read("img_adm.jpg");
	img_adwm.compressType(JPEGCompression);
	//img_adwm.write("img_adm2.png");
#ifdef addwm02
	image_getwm02(ref,img_adwm,wm_extr);
#endif
#ifdef addwm05
	image_getwm05(img_adwm,wm_extr);
#endif
	//cout << "TransformFormat" << endl;
	getNC(wm_src, &wm_extr);
	}

void Narrowing(Image* src, Image* wm_src, Image ref)
{
	Image img_adwm = *src;
	Image wm_extr = *wm_src;
	img_adwm.resize(Geometry(640,640));
#ifdef addwm02
	image_getwm02(ref,img_adwm,wm_extr);
#endif
#ifdef addwm05
	image_getwm05(img_adwm,wm_extr);
#endif
	img_adwm.resize(Geometry(800,800));
	cout<<" ";
	getPSNR(&ref,&img_adwm);
	img_adwm.resize(Geometry(640,640));
	getNC(wm_src, &wm_extr);
	cout << ""<< endl;
	}
