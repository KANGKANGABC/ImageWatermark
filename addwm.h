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

#define addwm02

void wm1_add(Image image_src,Image image_wm,Image &image_dst);
void wm1_detect(Image image_src,Image image_wm);
void wm2_add(Image image_src,Image image_wm,Image &image_dst);
void wm2_detect(Image image_src,Image image_ref,Image image_wm);
void ImageY2Array(Image image_src,Image image_dst,Image image_wm,
uchar data_src[800*800],uchar data_dst[800*800],bool data_wm[200*200]);
void image_putwm01(Image image_src,Image &image_dst,Image image_wm_src);
void image_putwm02(Image image_src,Image &image_dst,Image image_wm_src);
void image_getwm02(Image image_src,Image image_dst,Image &image_wm_dst);
void image_putwm04(Image image_src,Image &image_dst,Image image_wm_src);
void image_getwm04(Image image_dst,Image &image_wm_dst);
void image_putwm05(Image image_src,Image &image_dst,Image image_wm_src);
void image_getwm05(Image image_dst,Image &image_wm_dst);
void image_putwm06(Image image_src,Image &image_dst,Image image_wm_src);
void image_getwm06(Image image_dst,Image &image_wm_dst);
void image_getdirwm06(Image image_dst,Image &image_wm_dst);
void array2imageDst(Image &image_dst,uchar data_dst[800*800]);
void array2imageDstCb(Image &image_dst,uchar data_dst[800*800]);
void image2array800(Image image,uchar data[800*800]);
void imageCb2array800(Image image,uchar data[800*800]);
void image2array200(Image image,bool data[200*200]);
void array2image200(Image &image,bool data[200*200]);
void array2image800(Image &image,uchar data[800*800]);
void ImageRgb2Ycbcr(Image &image_src);
void ImageYcbcr2Rgb(Image &image_src);

const float YCbCrYRF = 0.299F;              // RGB转YCbCr的系数(浮点类型）
const float YCbCrYGF = 0.587F;
const float YCbCrYBF = 0.114F;
const float YCbCrCbRF = -0.168736F;
const float YCbCrCbGF = -0.331264F;
const float YCbCrCbBF = 0.500000F;
const float YCbCrCrRF = 0.500000F;
const float YCbCrCrGF = -0.418688F;
const float YCbCrCrBF = -0.081312F;

const float RGBRYF = 1.00000F;            // YCbCr转RGB的系数(浮点类型）
const float RGBRCbF = 0.0000F;
const float RGBRCrF = 1.40200F;
const float RGBGYF = 1.00000F;
const float RGBGCbF = -0.34414F;
const float RGBGCrF = -0.71414F;
const float RGBBYF = 1.00000F;
const float RGBBCbF = 1.77200F;
const float RGBBCrF = 0.00000F;

const int Shift = 20;
const int HalfShiftValue = 1 << (Shift - 1);

const int YCbCrYRI = (int)(YCbCrYRF * (1 << Shift) + 0.5);         // RGB转YCbCr的系数(整数类型）
const int YCbCrYGI = (int)(YCbCrYGF * (1 << Shift) + 0.5);
const int YCbCrYBI = (int)(YCbCrYBF * (1 << Shift) + 0.5);
const int YCbCrCbRI = (int)(YCbCrCbRF * (1 << Shift) + 0.5);
const int YCbCrCbGI = (int)(YCbCrCbGF * (1 << Shift) + 0.5);
const int YCbCrCbBI = (int)(YCbCrCbBF * (1 << Shift) + 0.5);
const int YCbCrCrRI = (int)(YCbCrCrRF * (1 << Shift) + 0.5);
const int YCbCrCrGI = (int)(YCbCrCrGF * (1 << Shift) + 0.5);
const int YCbCrCrBI = (int)(YCbCrCrBF * (1 << Shift) + 0.5);

const int RGBRYI = (int)(RGBRYF * (1 << Shift) + 0.5);              // YCbCr转RGB的系数(整数类型）
const int RGBRCbI = (int)(RGBRCbF * (1 << Shift) + 0.5);
const int RGBRCrI = (int)(RGBRCrF * (1 << Shift) + 0.5);
const int RGBGYI = (int)(RGBGYF * (1 << Shift) + 0.5);
const int RGBGCbI = (int)(RGBGCbF * (1 << Shift) + 0.5);
const int RGBGCrI = (int)(RGBGCrF * (1 << Shift) + 0.5);
const int RGBBYI = (int)(RGBBYF * (1 << Shift) + 0.5);
const int RGBBCbI = (int)(RGBBCbF * (1 << Shift) + 0.5);
const int RGBBCrI = (int)(RGBBCrF * (1 << Shift) + 0.5);

#endif
