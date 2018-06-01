#include <iostream>
#include "attack.h"
#include "evaluate.h"
#include "addwm.h"
#include "testbench.h"

void testbench(Image image_src, Image image_dst, Image image_wm_src)
{
	getPSNR(&image_src, &image_dst);

	NoAttack(&image_dst, &image_wm_src);
	GaussNoise(&image_dst, &image_wm_src);
	ImpulseNoiseAttack(&image_dst, &image_wm_src);
	Rotate(&image_dst, &image_wm_src);
	Shear(&image_dst, &image_wm_src);
	//Compress(&image_dst, &image_wm_src);
	//TransformFormat(&image_dst, &image_wm_src);
	Narrowing(&image_dst, &image_wm_src);
	}
