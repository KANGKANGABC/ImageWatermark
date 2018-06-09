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

static dct_data_t input_block_test[8*8] = {
		33,-536,-52,-37,-2,-18,4,-3,
		-7,-192,247,-41,43,-5,15,-2,
		-174,725,2,6,-133,-9,-6,1,
		-1043,50,-296,-45,-37,86,-13,-6,
		-57,-136,11,177,21,20,17,2,
		-716,-43,184,7,-91,9,-11,9,
		10,-26,41,-150,-20,-20,-22,4,
		292,-27,6,-37,90,75,-15,6
};


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

void image_addwm04(uchar src[640000], uchar dst[640000], bool wm[200*200])
{
	//cout << "addwm04" << endl;
    dct_data_t image_block_input[8*8];
    dct_data_t image_block_tmp[8*8];
    dct_data_t image_block_output[8*8];
    init_fdct(); // needed by REF  FDCT
    init_idct(); // needed by WANG IDCT
    unsigned char alpha = 1;
    float beta = 0.5;
// 2/3 3/4 3/5 2/4 --> 19/26 28/35 29/43 20/34 : 1 2 3 4
// 1 2
// 3 4
    wm_fArnold(wm);
    wm_fArnold(wm);
    wm_fArnold(wm);
    //cout << "addwm04" << endl;
    for(int i = 0;i < 100;i++)
    {
        for(int j = 0;j < 100;j++)
        {
        	for(int m = 0;m < 8;m ++)
        	{
            	for(int n = 0;n < 8;n ++)
            	{
            		image_block_input[8*m+n] = src[(8*i+m)*800+8*j+n]*2 - 255;
            	}
            }
        	cout << "j = "<< j << endl;
        	cout << "i = "<< i << endl;
        	top_fdct(image_block_input,image_block_tmp);
        	//cout << wm[200*(2*i)+2*j] << endl;
        	//cout << wm[200*(2*i)+2*j+1] << endl;
        	//cout << wm[200*((2*i)+1)+2*j] << endl;
        	//cout << wm[200*((2*i)+1)+2*j+1] << endl;
        	if(wm[200*(2*i)+2*j] > 0)
        	{
        		//cout << "1" << endl;
        		if(image_block_tmp[19] < image_block_tmp[26])
        		{
        			swap_sint(image_block_tmp[19],image_block_tmp[26]);
        		}
        	}
        	else
        	{
        		if(image_block_tmp[19] > image_block_tmp[26])
        		{
        			swap_sint(image_block_tmp[19],image_block_tmp[26]);
        		}
        	}
        	if(wm[200*(2*i)+2*j+1] > 0)
        	{
        		if(image_block_tmp[28] < image_block_tmp[35])
        		{
        			swap_sint(image_block_tmp[28],image_block_tmp[35]);
        		}
        	}
        	else
        	{
        		//cout << "0" << endl;
        		if(image_block_tmp[28] > image_block_tmp[35])
        		{
        			swap_sint(image_block_tmp[28],image_block_tmp[35]);
        		}
        	}
            if(wm[200*((2*i)+1)+2*j] > 0)
        	{
            	//cout << "1" << endl;
        		if(image_block_tmp[29] < image_block_tmp[43])
        		{
        			swap_sint(image_block_tmp[29],image_block_tmp[43]);
        		}
        	}
        	else
        	{
        		if(image_block_tmp[29] > image_block_tmp[43])
        		{
        			swap_sint(image_block_tmp[29],image_block_tmp[43]);
        		}
        	}
            if(wm[200*((2*i)+1)+2*j+1] > 0)
        	{
        		if(image_block_tmp[20] < image_block_tmp[34])
        		{
        			swap_sint(image_block_tmp[20],image_block_tmp[34]);
        		}
        	}
        	else
        	{
        		//cout << "0" << endl;
        		if(image_block_tmp[20] > image_block_tmp[34])
        		{
        			swap_sint(image_block_tmp[20],image_block_tmp[34]);
        		}
        	}

            //cout << "88"<< endl;
        	top_idct(image_block_tmp,image_block_output);
            //cout << "99"<< endl;
            if (i ==94 && j == 47)
            {
            	for(int m = 0;m < 8;m ++)
            	        	{
            	            	for(int n = 0;n < 8;n ++)
            	            	{
            	            		printf("%d ",image_block_tmp[8*m+n]);
            	            	}
            	            	printf("\n");
            	            }
            }
            //cout << "11"<< endl;
        	for(int m = 0;m < 8;m ++)
        	{
            	for(int n = 0;n < 8;n ++)
            	{
            		dst[(8*i+m)*800+8*j+n] = (image_block_output[8*m+n] + 255)/2;
            	}
            }
        }
    }

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
	  cout<< "(" << 5 << "," << 2 << ") ";
	 		  		  image_dst = image_src[4];
	 		  		  ImageRgb2Ycbcr(image_src[4]);
	 		  		  ImageRgb2Ycbcr(image_dst);
	 		  		cout << "ImageRgb2Ycbcr" << endl;
	 		  		  Image2Array(image_src[4],image_dst,image_wm_src[1],data_src,data_dst,data_wm_src);
	 		  		cout << "Image2Array" << endl;
	 		  		  image_addwm04(data_src,data_dst,data_wm_src);
	 		  		  cout << "addwm04" << endl;
	 		  		  array2imageDst(image_dst,data_dst);
	 		  		cout << "array2imageDst" << endl;
	 		  		  ImageYcbcr2Rgb(image_src[4]);
	 		  		  ImageYcbcr2Rgb(image_dst);
	 		  		  //image_src[i].display();
	 		  		  //image_dst.display();
	 		  		  testbench(&image_src[4], &image_dst, &image_wm_src[1]);
  }



  catch( Exception &error_ )
    {
      cout << "Caught exception: " << error_.what() << endl;
      return 1;
    }

   return 0;
Image* CannyEdgeImage()
}
