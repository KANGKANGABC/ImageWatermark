#ifndef __TESTBENCH_H__
#define __TESTBENCH_H__

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <Magick++.h>

#include "addwm.h"
#include "attack.h"
#include "evaluate.h"

using namespace Magick;
using namespace std;

void testbench(Image image_src, Image image_dst, Image image_wm_src);

#endif
