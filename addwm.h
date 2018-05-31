#ifndef __ADDWM_H__
#define __ADDWM_H__
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <Magick++.h>

#include "dct.h"

using namespace Magick;
using namespace std;

void wm1_add(Image image_src,Image image_wm,Image &image_dst);
void wm1_detect(Image image_src,Image image_wm);
void wm2_add(Image image_src,Image image_wm,Image &image_dst);
void wm2_detect(Image image_src,Image image_ref,Image image_wm);
void Image2Array(Image image_src,Image image_dst,Image image_wm,
uchar data_src[800*800],uchar data_dst[800*800],bool data_wm[200*200]);
void image_getwm04(Image image_dst,Image &image_wm_dst);
void array2imageDst(Image &image_dst,uchar data_dst[800*800]);
void image2array800(Image image,uchar data[800*800]);
void image2array200(Image image,bool data[200*200]);
void array2image200(Image &image,bool data[200*200]);
void array2image800(Image &image,uchar data[800*800]);

#endif
