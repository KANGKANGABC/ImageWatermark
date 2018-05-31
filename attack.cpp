#include <iostream>
#include "attack.h"
#include "evaluate.h"
#include "addwm.h"

void NoAttack(Image* src, Image* wm_src)
{
	Image img_adwm = *src;
	Image wm_extr = *wm_src;
	image_getwm04(img_adwm,wm_extr);
	//cout << "NoAttack" << endl;
	getNC(wm_src, &wm_extr);
	}

void GaussNoise(Image* src, Image* wm_src)
{
	Image img_adwm = *src;
	Image wm_extr = *wm_src;
	img_adwm.addNoise(GaussianNoise,0.01);
	image_getwm04(img_adwm,wm_extr);
	//cout << "GuassNoise(0.01)";
	getNC(wm_src, &wm_extr);
	}

void ImpulseNoiseAttack(Image* src, Image* wm_src)
{
	Image img_adwm = *src;
	Image wm_extr = *wm_src;
	img_adwm.addNoise(ImpulseNoise,0.01);
	image_getwm04(img_adwm,wm_extr);
	//cout << "ImpulseNoise(0.01)" << endl;
	getNC(wm_src, &wm_extr);
	}

void Rotate(Image* src, Image* wm_src)
{
	Image img_adwm = *src;
	Image wm_extr = *wm_src;
	img_adwm.rotate(10);
	image_getwm04(img_adwm,wm_extr);
	//cout << "Rotate(10 degree)" << endl;
	getNC(wm_src, &wm_extr);
	}

void Shear(Image* src, Image* wm_src)
{
	Image img_adwm = *src;
	Image wm_extr = *wm_src;
	for (int x=0;x<200;x++)		//height
	{
		for (int y=0;y<300;y++)		//width
		{
			img_adwm.pixelColor(y,x,Color(0,0,0,0));
		}
	}
	//img_adwm.display();
	image_getwm04(img_adwm,wm_extr);
	//cout << "Shear(300,200)" << endl;
	getNC(wm_src, &wm_extr);
	}

void Compress(Image* src, Image* wm_src)
{
	Image img_adwm = *src;
	Image wm_extr = *wm_src;
	img_adwm.quality(100);
	image_getwm04(img_adwm,wm_extr);
	//cout << "Compress(100)" << endl;
	getNC(wm_src, &wm_extr);
	}

void TransformFormat(Image* src, Image* wm_src)
{
	Image img_adwm = *src;
	Image wm_extr = *wm_src;
	//img_adwm.write("img_adm.jpg");
	//img_adwm.read("img_adm.jpg");
	img_adwm.compressType(JPEGCompression);
	//img_adwm.write("img_adm2.png");
	image_getwm04(img_adwm,wm_extr);
	//cout << "TransformFormat" << endl;
	getNC(wm_src, &wm_extr);
	}

void Narrowing(Image* src, Image* wm_src)
{
	Image img_adwm = *src;
	Image wm_extr = *wm_src;
	img_adwm.resize(Geometry(400,400));
	//img_adwm.display();
	image_getwm04(img_adwm,wm_extr);
	//cout << "Narrowing(400*400)" << endl;
	getNC(wm_src, &wm_extr);
	cout << ""<< endl;
	}
