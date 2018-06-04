#ifndef __EVALUATE_H__
#define __EVALUATE_H__
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <cmath>
#include <Magick++.h>

#include "dct.h"

using namespace Magick;
using namespace std;

double getPSNR(Image* src, Image* addwtm);
double getNC(Image* src, Image* extrwtm);

#endif
