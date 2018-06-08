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

void NoAttack(Image* src, Image* wm_src, Image ref);
void GaussNoise(Image* src, Image* wm_src, Image ref);
void ImpulseNoiseAttack(Image* src, Image* wm_src, Image ref);
void Rotate(Image* src, Image* wm_src, Image ref);
void Shear(Image* src, Image* wm_src, Image ref);
void Compress(Image* src, Image* wm_src, Image ref);
void TransformFormat(Image* src, Image* wm_src, Image ref);
void Narrowing(Image* src, Image* wm_src, Image ref);



#endif
