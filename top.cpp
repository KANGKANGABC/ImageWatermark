#include "dct.h"
#include "top.h"
#include <stdlib.h>
#include <stdio.h>

static int a[8*7]; //we don't know why,but it's needed
void image_fdct(uchar src[640000], uchar dst[640000])
{
    dct_data_t image_block_input[8*8];
    dct_data_t image_block_tmp[8*8];
    dct_data_t image_block_output[8*8];
    init_fdct(); // needed by REF  FDCT
    init_idct(); // needed by WANG IDCT
    unsigned char alpha = 1;
    float beta = 0.5;

    for(int i = 0;i < 100;i++)
    {
        for(int j = 0;j < 100;j++)
        {
        	for(int m = 0;m < 8;m ++)
        	{
            	for(int n = 0;n < 8;n ++)
            	{
            		image_block_input[8*m+n] = src[(8*i+m)*800+8*j+n];
            	}
            }
        	top_fdct(image_block_input,image_block_tmp);
        	top_idct(image_block_tmp,image_block_output);
        	for(int m = 0;m < 8;m ++)
        	{
            	for(int n = 0;n < 8;n ++)
            	{
            		dst[(8*i+m)*800+8*j+n] = image_block_output[8*m+n];
            	}
            }

        }
    }
}

void image_idct(uchar src[640000], uchar dst[640000])
{
    dct_data_t image_block_input[8*8];
    dct_data_t image_block_tmp[8*8];
    dct_data_t image_block_output[8*8];
    init_fdct(); // needed by REF  FDCT
    init_idct(); // needed by WANG IDCT
    unsigned char alpha = 1;
    float beta = 0.5;

    for(int i = 0;i < 100;i++)
    {
        for(int j = 0;j < 100;j++)
        {
        	for(int m = 0;m < 8;m ++)
        	{
            	for(int n = 0;n < 8;n ++)
            	{
            		image_block_input[8*m+n] = src[(8*i+m)*800+8*j+n];
            	}
            }
        	top_fdct(image_block_input,image_block_tmp);
        	top_idct(image_block_tmp,image_block_output);
        	for(int m = 0;m < 8;m ++)
        	{
            	for(int n = 0;n < 8;n ++)
            	{
            		dst[(8*i+m)*800+8*j+n] = image_block_output[8*m+n];
            	}
            }

        }
    }
}
void image_addwm01(uchar src[640000], uchar dst[640000], bool wm[200*200])
{

    dct_data_t image_block_input[8*8];
    dct_data_t image_block_tmp[8*8];
    dct_data_t image_block_output[8*8];

    dct_data_t image_block_input_ref[8*8];
    dct_data_t image_block_tmp_ref[8*8];
    dct_data_t image_block_output_ref[8*8];
    init_fdct(); // needed by REF  FDCT
    init_idct(); // needed by WANG IDCT
    float alpha = 0.5;

    //1,4 2,3 3,2 4,1  ->3 10 17 32
    wm_fArnold(wm);
    wm_fArnold(wm);
    wm_fArnold(wm);

    for(int i = 0;i < 100;i++)
    {
        for(int j = 0;j < 100;j++)
        {
        	for(int m = 0;m < 8;m ++)
        	{
            	for(int n = 0;n < 8;n ++)
            	{
            		image_block_input[8*m+n] = src[(8*i+m)*800+8*j+n];
            	}
            }
        	top_fdct(image_block_input,image_block_tmp);

        	if(wm[200*(2*i)+2*j] > 0)
        	{
        		image_block_tmp[3] = (dct_data_t)((1+alpha)*image_block_tmp[3]);
        	}
        	else
        	{
        		image_block_tmp[3] = (dct_data_t)((1-alpha)*image_block_tmp[3]);
        	}
        	if(wm[200*(2*i)+2*j+1] > 0)
        	{
        		image_block_tmp[10] = (dct_data_t)((1+alpha)*image_block_tmp[10]);
        	}
        	else
        	{
        		image_block_tmp[10] = (dct_data_t)((1-alpha)*image_block_tmp[10]);
        	}
            if(wm[200*((2*i)+1)+2*j] > 0)
        	{
            	image_block_tmp[17] = (dct_data_t)((1+alpha)*image_block_tmp[17]);
        	}
        	else
        	{
        		image_block_tmp[17] = (dct_data_t)((1-alpha)*image_block_tmp[17]);
        	}
            if(wm[200*((2*i)+1)+2*j+1] > 0)
        	{
            	image_block_tmp[32] = (dct_data_t)((1+alpha)*image_block_tmp[32]);
        	}
        	else
        	{
        		image_block_tmp[32] = (dct_data_t)((1-alpha)*image_block_tmp[32]);
        	}

        	top_idct(image_block_tmp,image_block_output);
        	for(int m = 0;m < 8;m ++)
        	{
            	for(int n = 0;n < 8;n ++)
            	{
            		dst[(8*i+m)*800+8*j+n] = image_block_output[8*m+n];
            	}
            }
        }
    }

    //1,4 2,3 3,2 4,1  ->3 10 17 32
    for(int i = 0;i < 100;i++)
    {
        for(int j = 0;j < 100;j++)
        {
        	for(int m = 0;m < 8;m ++)
        	{
            	for(int n = 0;n < 8;n ++)
            	{
            		image_block_input[8*m+n] = dst[(8*i+m)*800+8*j+n];
            		image_block_input_ref[8*m+n] = src[(8*i+m)*800+8*j+n];
            	}
            }
        	top_fdct(image_block_input,image_block_tmp);
        	top_fdct(image_block_input_ref,image_block_tmp_ref);
        	if(image_block_tmp[3]>0)
        	{
        		if(image_block_tmp[3]>image_block_tmp_ref[3])
        			wm[200*(2*i)+2*j] = 1;else wm[200*(2*i)+2*j] = 0;
        	}
        	else
        	{
        		if(image_block_tmp[3]>image_block_tmp_ref[3])
        			wm[200*(2*i)+2*j] = 0;else wm[200*(2*i)+2*j] = 1;
        	}
        	if(image_block_tmp[10]>0)
        	{
        		if(image_block_tmp[10]>image_block_tmp_ref[10])
        			wm[200*(2*i)+2*j+1] = 1;else wm[200*(2*i)+2*j+1] = 0;
        	}
        	else
        	{
        		if(image_block_tmp[10]>image_block_tmp_ref[10])
        			wm[200*(2*i)+2*j+1] = 0;else wm[200*(2*i)+2*j+1] = 1;
        	}
        	if(image_block_tmp[17]>0)
        	{
        		if(image_block_tmp[17]>image_block_tmp_ref[17])
        			wm[200*(2*i+1)+2*j] = 1;else wm[200*(2*i+1)+2*j] = 0;
        	}
        	else
        	{
        		if(image_block_tmp[17]>image_block_tmp_ref[17])
        			wm[200*(2*i+1)+2*j] = 0;else wm[200*(2*i+1)+2*j] = 1;
        	}
        	if(image_block_tmp[32]>0)
        	{
        		if(image_block_tmp[32]>image_block_tmp_ref[32])
        			wm[200*(2*i+1)+2*j+1] = 1;else wm[200*(2*i+1)+2*j+1] = 0;
        	}
        	else
        	{
        		if(image_block_tmp[32]>image_block_tmp_ref[32])
        			wm[200*(2*i+1)+2*j+1] = 0;else wm[200*(2*i+1)+2*j+1] = 1;
        	}

        }
    }
    wm_iArnold(wm);
    wm_iArnold(wm);
    wm_iArnold(wm);
}
void image_addwm02(uchar src[640000], uchar dst[640000], bool wm[200*200])
{

    dct_data_t image_block_input[8*8];
    dct_data_t image_block_tmp[8*8];
    dct_data_t image_block_output[8*8];

    dct_data_t image_block_input_ref[8*8];
    dct_data_t image_block_tmp_ref[8*8];
    dct_data_t image_block_output_ref[8*8];
    init_fdct(); // needed by REF  FDCT
    init_idct(); // needed by WANG IDCT
    float alpha = 0.5;
    int beta = 2;

    //1,4 2,3 3,2 4,1  ->3 10 17 32
    wm_fArnold(wm);
    wm_fArnold(wm);
    wm_fArnold(wm);

    for(int i = 0;i < 100;i++)
    {
        for(int j = 0;j < 100;j++)
        {
        	for(int m = 0;m < 8;m ++)
        	{
            	for(int n = 0;n < 8;n ++)
            	{
            		image_block_input[8*m+n] = 2*src[(8*i+m)*800+8*j+n]-255;
            	}
            }
        	top_fdct(image_block_input,image_block_tmp);

        	if(wm[200*(2*i)+2*j] > 0)
        	{
        		image_block_tmp[7] += beta;
        	}
        	else
        	{
       			image_block_tmp[7] -= beta;
        	}
        	if(wm[200*(2*i)+2*j+1] > 0)
        	{
        		image_block_tmp[21] += beta;
        	}
        	else
        	{
        		image_block_tmp[21] -= beta;
        	}
            if(wm[200*((2*i)+1)+2*j] > 0)
        	{
            	image_block_tmp[42] += beta;
        	}
        	else
        	{
    			image_block_tmp[42] -= beta;
        	}
            if(wm[200*((2*i)+1)+2*j+1] > 0)
        	{
        		image_block_tmp[56] += beta;
        	}
        	else
        	{
      			image_block_tmp[56] -= beta;
        	}

        	top_idct(image_block_tmp,image_block_output);
        	for(int m = 0;m < 8;m ++)
        	{
            	for(int n = 0;n < 8;n ++)
            	{
            		dst[(8*i+m)*800+8*j+n] = (image_block_output[8*m+n]+255)/2;
            	}
            }
        }
    }
}

void image_addwm04(uchar src[640000], uchar dst[640000], bool wm[200*200])
{
    dct_data_t image_block_input[8*8];
    dct_data_t image_block_tmp[8*8];
    dct_data_t image_block_output[8*8];
    init_fdct(); // needed by REF  FDCT
    init_idct(); // needed by WANG IDCT
// 2/3 3/4 3/5 2/4 --> 19/26 28/35 29/43 20/34 : 1 2 3 4
// 1 2
// 3 4
    wm_fArnold(wm);
    wm_fArnold(wm);
    wm_fArnold(wm);
    for(int i = 0;i < 100;i++)
    {
        for(int j = 0;j < 100;j++)
        {
        	for(int m = 0;m < 8;m ++)
        	{
            	for(int n = 0;n < 8;n ++)
            	{
            		short int tmp = src[(8*i+m)*800+8*j+n]*2 - 255;
            		image_block_input[8*m+n] = tmp;
            		//src[(8*i+m)*800+8*j+n];
            		//src[(8*i+m)*800+8*j+n]*2 - 255;
            	}
            }
        	top_fdct(image_block_input,image_block_tmp);
        	if(wm[200*(2*i)+2*j] > 0)
        	{
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
        		if(image_block_tmp[28] > image_block_tmp[35])
        		{
        			swap_sint(image_block_tmp[28],image_block_tmp[35]);
        		}
        	}
            if(wm[200*((2*i)+1)+2*j] > 0)
        	{
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
        		if(image_block_tmp[20] > image_block_tmp[34])
        		{
        			swap_sint(image_block_tmp[20],image_block_tmp[34]);
        		}
        	}

        	top_idct(image_block_tmp,image_block_output);
        	for(int m = 0;m < 8;m ++)
        	{
            	for(int n = 0;n < 8;n ++)
            	{
            		dst[(8*i+m)*800+8*j+n] = (image_block_output[8*m+n] + 255)/2;
            		//printf("%d ",dst[(8*i+m)*800+8*j+n]);
            		//image_block_output[8*m+n];//(image_block_output[8*m+n] + 255)/2;
            	}
            }
        	//printf("\r\n");
        }
    }


}

void image_addwm05(uchar src[640000], uchar dst[640000], bool wm[200*200])
{
    dct_data_t image_block_input[8*8];
    dct_data_t image_block_tmp[8*8];
    dct_data_t image_block_output[8*8];
    init_fdct(); // needed by REF  FDCT
    init_idct(); // needed by WANG IDCT
// 1-6/2-5 3-4/4-3 3-3/4-4 5-2/6-1 --> 5/12 19/26 18/27 33/40 : 1 2 3 4
// 1 2
// 3 4
    wm_fArnold(wm);
    wm_fArnold(wm);
    wm_fArnold(wm);
    for(int i = 0;i < 100;i++)
    {
        for(int j = 0;j < 100;j++)
        {
        	for(int m = 0;m < 8;m ++)
        	{
            	for(int n = 0;n < 8;n ++)
            	{
            		short int tmp = src[(8*i+m)*800+8*j+n]*2 - 255;
            		image_block_input[8*m+n] = tmp;
            	}
            }
        	top_fdct(image_block_input,image_block_tmp);
        	if(wm[200*(2*i)+2*j] > 0)
        	{
        		if(image_block_tmp[5] < image_block_tmp[12])
        		{
        			swap_sint(image_block_tmp[5],image_block_tmp[12]);
        		}
        		enlarge_sint(image_block_tmp[5],image_block_tmp[12]);
        	}
        	else
        	{
        		if(image_block_tmp[5] > image_block_tmp[12])
        		{
        			swap_sint(image_block_tmp[5],image_block_tmp[12]);
        		}
        		enlarge_sint(image_block_tmp[12],image_block_tmp[5]);
        	}
        	if(wm[200*(2*i)+2*j+1] > 0)
        	{
        		if(image_block_tmp[19] < image_block_tmp[26])
        		{
        			swap_sint(image_block_tmp[19],image_block_tmp[26]);
        		}
        		enlarge_sint(image_block_tmp[19],image_block_tmp[26]);
        	}
        	else
        	{
        		if(image_block_tmp[19] > image_block_tmp[26])
        		{
        			swap_sint(image_block_tmp[19],image_block_tmp[26]);
        		}
        		enlarge_sint(image_block_tmp[26],image_block_tmp[19]);
        	}
            if(wm[200*((2*i)+1)+2*j] > 0)
        	{
        		if(image_block_tmp[18] < image_block_tmp[27])
        		{
        			swap_sint(image_block_tmp[18],image_block_tmp[27]);
        		}
        		enlarge_sint(image_block_tmp[18],image_block_tmp[27]);
        	}
        	else
        	{
        		if(image_block_tmp[18] > image_block_tmp[27])
        		{
        			swap_sint(image_block_tmp[18],image_block_tmp[27]);
        		}
        		enlarge_sint(image_block_tmp[27],image_block_tmp[18]);
        	}
            if(wm[200*((2*i)+1)+2*j+1] > 0)
        	{
        		if(image_block_tmp[33] < image_block_tmp[40])
        		{
        			swap_sint(image_block_tmp[33],image_block_tmp[40]);
        		}
        		enlarge_sint(image_block_tmp[33],image_block_tmp[40]);
        	}
        	else
        	{
        		if(image_block_tmp[33] > image_block_tmp[40])
        		{
        			swap_sint(image_block_tmp[33],image_block_tmp[40]);
        		}
        		enlarge_sint(image_block_tmp[40],image_block_tmp[33]);
        	}

        	top_idct(image_block_tmp,image_block_output);
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

void swap_sint(signed short int  &a,signed short int  &b)
{
	signed int tmp = 0;
	tmp = a;
	a = b;
	b = tmp;
}

void enlarge_sint(signed short int  &a,signed short int  &b)//增大两值的差
{
	int alpha = 0;
	if((a+alpha)>32767)
		a = 32767;
	else
		a+=alpha;
	if((b-alpha)<-32767)
		b = -32767;
	else
		b-=alpha;
}

void wm_fArnold(bool wm[200*200])
{
	bool wm_dst[200*200];
	int n = 200;
	int a = 5;
	int b = 7;
	for(int i=0;i < 200;i++)
	{
		for(int j=0;j < 200;j++)
		{
			int x = (i+b*j)%n;
			int y = (a*i+(a*b+1)*j)%n;
			if(x<0)
			{
				x =x +200;
			}
			if(y<0)
			{
				y =y +200;
			}
			wm_dst[200*x+y] = wm[200*i+j];

		}
	}
	for(int i=0;i < 200;i++)
	{
		for(int j=0;j < 200;j++)
		{
			wm[200*i + j] = wm_dst[200*i + j];
		}

	}

}
void wm_iArnold(bool wm[200*200])
{
	bool wm_dst[200*200];
	int n = 200;
	int a = 5;
	int b = 7;
	for(int i=0;i < 200;i++)
	{
		for(int j=0;j < 200;j++)
		{
			int x = ((a*b+1)*i-b*j)%n;
			int y = (j-a*i)%n;
			if(x<0)
			{
				x =x +200;
			}
			if(y<0)
			{
				y =y +200;
			}
			wm_dst[200*x+y] = wm[200*i+j];

		}
	}
	for(int i=0;i < 200;i++)
	{
		for(int j=0;j < 200;j++)
		{
			wm[200*i + j] = wm_dst[200*i + j];
		}

	}

}
