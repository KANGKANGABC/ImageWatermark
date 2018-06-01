/************************************************
Copyright (c) 2016, Xilinx, Inc.
All rights reserved.
Redistribution and use in source and binary forms, with or without modification,
are permitted provided that the following conditions are met:
1. Redistributions of source code must retain the above copyright notice,
this list of conditions and the following disclaimer.
2. Redistributions in binary form must reproduce the above copyright notice,
this list of conditions and the following disclaimer in the documentation
and/or other materials provided with the distribution.
3. Neither the name of the copyright holder nor the names of its contributors
may be used to endorse or promote products derived from this software
without specific prior written permission.
THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
************************************************/

/* ************ starting point of  module qfloatdct.c *************************** */
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <Magick++.h>


#include "dct.h"
#include "top.h"
#include "top_test.h"
#include "addwm.h"

#include "attack.h"
#include "evaluate.h"
#include "testbench.h"


using namespace Magick;
using namespace std;

void GetImage(Image *image_src,Image &image_dst,Image *image_wm_src,Image &image_wm_dst)
{
	image_src[0].read("1.png");
	image_src[1].read("2.png");
	image_src[2].read("3.png");
	image_src[3].read("4.png");
	image_src[4].read("5.png");
	image_src[5].read("6.png");
	image_src[6].read("7.png");
	image_src[7].read("8.png");
	image_src[8].read("9.png");
	image_dst.read("1.png");
	image_wm_src[0].read("a01.png");
	image_wm_src[1].read("a02.png");
	image_wm_src[2].read("a03.png");
	image_wm_dst.read("a01.png");
}

int main(void)
{

  InitializeMagick(NULL);

  Image image_src[9];
  Image image_dst;
  Image image_wm_src[3];
  Image image_wm_dst;
  uchar data_src[800*800];
  uchar data_dst[800*800];
  bool data_wm_src[200*200];
  bool data_wm_dst[200*200];
  try {
	  GetImage(image_src,image_dst,image_wm_src,image_wm_dst);
	  cout << " PSNR NoAttack GaussNoise(0.01) ImpulseNoise(0.01) Rotate(10') Shear(300*200) Narrowing(400*400)" << endl;
	  for (int i = 0; i < 9; i++)
		  {
		  	  for (int j = 0; j < 3; j++)
		  	  {
		  		  cout<< "(" << i+1 << "," << j+1 << ") ";
		  		  Image2Array(image_src[i],image_dst,image_wm_src[j],data_src,data_dst,data_wm_src);
		  		  image_addwm04(data_src,data_dst,data_wm_src);
		  		  array2imageDst(image_dst,data_dst);
		  		  testbench(&image_src[i], &image_dst, &image_wm_src[j]);
		  	  }
		  }

  }
  catch( Exception &error_ )
    {
      cout << "Caught exception: " << error_.what() << endl;
      return 1;
    }

   return 0;

}
