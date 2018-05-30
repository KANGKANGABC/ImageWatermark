#ifndef __ATTACK_H__
#define __ATTACK_H__
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <cmath>
#include <Magick++.h>

#include "dct.h"

using namespace Magick;
using namespace std;

void NoAttack(Image* src, Image* wm_src);
void GaussNoise(Image* src, Image* wm_src);
void ImpulseNoiseAttack(Image* src, Image* wm_src);
void Rotate(Image* src, Image* wm_src);
void Shear(Image* src, Image* wm_src);
void Compress(Image* src, Image* wm_src);
void TransformFormat(Image* src, Image* wm_src);
void Narrowing(Image* src, Image* wm_src);


#endif
