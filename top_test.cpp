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

void GetImage(Image &image_src,Image &image_dst,Image &image_wm_src,Image &image_wm_dst,int index,int index_wm)
{
	switch(index)
	{
		case 0: image_src.read("1.png"); break;
		case 1: image_src.read("2.png"); break;
		case 2: image_src.read("3.png"); break;
		case 3: image_src.read("4.png"); break;
		case 4: image_src.read("5.png"); break;
		case 5: image_src.read("6.png"); break;
		case 6: image_src.read("7.png"); break;
		case 7: image_src.read("8.png"); break;
		case 8: image_src.read("9.png"); break;
		default: image_src.read("1.png"); break;
	}
	switch(index_wm)
	{
		case 0: image_wm_src.read("a01.png"); break;
		case 1: image_wm_src.read("a02.png"); break;
		case 2: image_wm_src.read("a03.png"); break;
		default: image_wm_src.read("a01.png"); break;
	}
	image_dst = image_src;
	image_wm_dst = image_wm_src;
}

int main(void)
{

	InitializeMagick(NULL);

	Image image_src;
	Image image_dst;
	Image image_wm_src;
	Image image_wm_dst;
	Image image_dirwm_dst;

	try {
		  cout << " PSNR NoAttack GaussNoise(0.01) ImpulseNoise(0.01) Rotate(10') Shear(300*200) Compress Narrowing(400*400)" << endl;

		  for (int i = 0; i < 9; i++)
		  {
			  int j = 0;
			  GetImage(image_src,image_dst,image_wm_src,image_wm_dst,i,j);
			  cout<< "(" << i+1 << "," << j+1 << ") ";
#ifdef addwm02
			  image_putwm02(image_src,image_dst,image_wm_src);
#endif
#ifdef addwm05
			  image_putwm05(image_src,image_dst,image_wm_src);
#endif
			  image_dst.display();
			  testbench(image_src, image_dst, image_wm_src);

		  }
	    }
	  catch( Exception &error)
		{
		  cout << "Caught exception: " << error.what() << endl;
		  return 1;
		}

	   return 0;

}
