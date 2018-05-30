#include "addwm.h"
#include "top.h"
#include <iostream>

void Image2Array(Image image_src,Image image_dst,Image image_wm,
uchar data_src[800*800],uchar data_dst[800*800],bool data_wm[200*200])//Image Pre Processing
{
    int w = image_src.columns();
    int h = image_src.rows();
    MagickCore::Quantum *pixels_src = image_src.getPixels(0, 0, w, h);
    MagickCore::Quantum *pixels_dst = image_dst.getPixels(0, 0, w, h);

    int w_w = image_wm.columns();
    int h_w= image_wm.rows();
    MagickCore::Quantum *pixels_wm = image_wm.getPixels(0, 0, w_w, h_w);

    int row = 0;
    int column = 0;
    unsigned offset_src = image_src.channels() * (w * row + column);
    unsigned offset_dst = image_dst.channels() * (w * row + column);
    unsigned offset_wm = image_wm.channels() * (w_w * row + column);
    for(int i = 0;i < 800;i++)
    {
        for(int j = 0;j < 800;j++)
        {
    		row = i;
    		column = j;
    		offset_src = image_src.channels() * (w * row + column);
    		data_src[800*i+j] = (uchar)(pixels_src[offset_src + 0]*255/65535);
        }
    }

    for(int i = 0;i < 200;i++)
    {
        for(int j = 0;j < 200;j++)
        {
    		row = i;
    		column = j;
    		offset_wm = image_wm.channels() * (w_w * row + column);
    		if(pixels_wm[offset_wm + 3] > 40000)
    		{
    			data_wm[200*i+j] = 1;
    		}
    		else
    		{
    			data_wm[200*i+j] = 0;
    		}
        }
    }
}
void array2imageDst(Image &image_dst,uchar data_dst[800*800])
{
    int w = image_dst.columns();
    int h = image_dst.rows();
    MagickCore::Quantum *pixels_dst = image_dst.getPixels(0, 0, w, h);
    int row = 0;
    int column = 0;
    unsigned offset_dst = image_dst.channels() * (w * row + column);
    for(int i = 0;i < 800;i++)
    {
        for(int j = 0;j < 800;j++)
        {
    		row = i;
    		column = j;
    		offset_dst = image_dst.channels() * (w * row + column);
    		//pixels_dst[offset_dst + 1] = 0;
    		//pixels_dst[offset_dst + 2] = 0;
    		//pixels_dst[offset_dst + 3] = 0;
    		pixels_dst[offset_dst + 0] = (data_dst[800*i+j]*(65535/255));
        }
    }
    image_dst.syncPixels();
}
void image_getwm04(Image image_dst,Image &image_wm_dst)
{
	uchar data_dst[800*800];
	bool data_wm_dst[200*200];
	image2array800(image_dst,data_dst);
	image2array200(image_wm_dst,data_wm_dst);
    dct_data_t image_block_input[8*8];
    dct_data_t image_block_tmp[8*8];
    init_fdct(); // needed by REF  FDCT
    init_idct(); // needed by WANG IDCT
    for(int i = 0;i < 100;i++)
    {
        for(int j = 0;j < 100;j++)
        {
        	for(int m = 0;m < 8;m ++)
        	{
            	for(int n = 0;n < 8;n ++)
            	{
            		image_block_input[8*m+n] = data_dst[(8*i+m)*800+8*j+n];
            	}
            }
        	top_fdct(image_block_input,image_block_tmp);
        	if(image_block_tmp[19] > image_block_tmp[26])
        	{
        		data_wm_dst[200*(2*i)+2*j] = 1;
        	}
        	else
        	{
        		data_wm_dst[200*(2*i)+2*j] = 0;
        	}
        	if(image_block_tmp[28] > image_block_tmp[35])
        	{
        		data_wm_dst[200*(2*i)+2*j+1] = 1;
        	}
        	else
        	{
        		data_wm_dst[200*(2*i)+2*j+1] = 0;
        	}
        	if(image_block_tmp[29] > image_block_tmp[43])
        	{
        		data_wm_dst[200*((2*i)+1)+2*j] = 1;
        	}
        	else
        	{
        		data_wm_dst[200*((2*i)+1)+2*j] = 0;
        	}
        	if(image_block_tmp[20] > image_block_tmp[34])
        	{
        		data_wm_dst[200*((2*i)+1)+2*j+1] = 1;
        	}
        	else
        	{
        		data_wm_dst[200*((2*i)+1)+2*j+1] = 0;
        	}
        }
    }
    wm_iArnold(data_wm_dst);
    array2image200(image_wm_dst,data_wm_dst);

}
void image2array800(Image image,uchar data[800*800])
{
    int w = image.columns();
    int h = image.rows();
    MagickCore::Quantum *pixels = image.getPixels(0, 0, w, h);
    int row = 0;
    int column = 0;
    unsigned offset = image.channels() * (w * row + column);
    for(int i = 0;i < 800;i++)
    {
        for(int j = 0;j < 800;j++)
        {
    		row = i;
    		column = j;
    		offset = image.channels() * (w * row + column);
    		data[800*i+j] = (uchar)(pixels[offset + 0]*255/65535);
        }
    }
}
void image2array200(Image image,bool data[200*200])
{
    int w = image.columns();
    int h = image.rows();
    MagickCore::Quantum *pixels = image.getPixels(0, 0, w, h);
    int row = 0;
    int column = 0;
    unsigned offset = image.channels() * (w * row + column);
    for(int i = 0;i < 200;i++)
    {
        for(int j = 0;j < 200;j++)
        {
    		row = i;
    		column = j;
    		offset = image.channels() * (w * row + column);
    		data[200*i+j] = (uchar)(pixels[offset + 0]*255/65535);
        }
    }

}
void array2image200(Image &image,bool data[200*200])
{
    int w = image.columns();
    int h = image.rows();
    MagickCore::Quantum *pixels = image.getPixels(0, 0, w, h);
    int row = 0;
    int column = 0;
    unsigned offset = image.channels() * (w * row + column);
    for(int i = 0;i < 200;i++)
    {
        for(int j = 0;j < 200;j++)
        {
    		row = i;
    		column = j;
    		offset = image.channels() * (w * row + column);
    		pixels[offset + 0] = data[200*i+j]*50000;
        }
    }
    image.syncPixels();
}
void array2image800(Image &image,uchar data[800*800])
{
    int w = image.columns();
    int h = image.rows();
    MagickCore::Quantum *pixels = image.getPixels(0, 0, w, h);
    int row = 0;
    int column = 0;
    unsigned offset = image.channels() * (w * row + column);
    for(int i = 0;i < 800;i++)
    {
        for(int j = 0;j < 800;j++)
        {
    		row = i;
    		column = j;
    		offset = image.channels() * (w * row + column);
    		pixels[offset + 0] = data[800*i+j]*65535/255;
        }
    }
    image.syncPixels();
}
void Array2Image(Image &image_src,Image &image_dst,Image image_wm,
uchar data_src[800*800],uchar data_dst[800*800],bool data_wm[200*200])//Image Pre Processing
{
    int w = image_src.columns();
    int h = image_src.rows();
    MagickCore::Quantum *pixels_src = image_src.getPixels(0, 0, w, h);
    MagickCore::Quantum *pixels_dst = image_dst.getPixels(0, 0, w, h);

    int w_w = image_wm.columns();
    int h_w= image_wm.rows();
    MagickCore::Quantum *pixels_wm = image_wm.getPixels(0, 0, w_w, h_w);

    int row = 0;
    int column = 0;
    unsigned offset_src = image_src.channels() * (w * row + column);
    unsigned offset_dst = image_dst.channels() * (w * row + column);
    unsigned offset_wm = image_wm.channels() * (w_w * row + column);
    for(int i = 0;i < 800;i++)
    {
        for(int j = 0;j < 800;j++)
        {
    		row = i;
    		column = j;
    		offset_dst = image_dst.channels() * (w * row + column);
    		pixels_dst[offset_dst + 1] = 0;
    		pixels_dst[offset_dst + 2] = 0;
    		pixels_dst[offset_dst + 0] = (data_dst[800*i+j]*(65535/255));
        }
    }
    for(int i = 0;i < 200;i++)
    {
        for(int j = 0;j < 200;j++)
        {
    		row = i;
    		column = j;
    		offset_wm = image_wm.channels() * (w_w * row + column);
    		pixels_wm[offset_wm + 3] = 65535;
    		if(data_wm[200*i+j]>0)
    		{
    			pixels_wm[offset_wm + 0] = 50000;
    		}
    		else
    		{
    			pixels_wm[offset_wm + 0] = 0;
    		}

        }
    }
    image_dst.syncPixels();
    image_dst.display();
    image_wm.syncPixels();
    image_wm.display();
}

void wm1_add(Image image_src,Image image_wm,Image &image_dst)
{
	//image_wm.resize(Magick::Geometry(100, 100));

    // Write the image to a file
    int w = image_src.columns();
    int h = image_src.rows();
    MagickCore::Quantum *pixels_src = image_src.getPixels(0, 0, w, h);
    MagickCore::Quantum *pixels_dst = image_dst.getPixels(0, 0, w, h);

    int w_w = image_wm.columns();
    int h_w= image_wm.rows();
    MagickCore::Quantum *pixels_wm = image_wm.getPixels(0, 0, w_w, h_w);

    int row = 0;
    int column = 0;
    unsigned offset_src = image_src.channels() * (w * row + column);
    unsigned offset_dst = image_dst.channels() * (w * row + column);
    unsigned offset_wm = image_wm.channels() * (w_w * row + column);

    dct_data_t image_block_input[8*8];
    dct_data_t image_block_tmp[8*8];
    dct_data_t image_block_output[8*8];
    init_fdct(); // needed by REF  FDCT
    init_idct(); // needed by WANG IDCT
    unsigned char alpha = 1;
    float beta = 0.5;

    uchar data_src[800*800];
    uchar data_dst[800*800];
    bool data_wm[200*200];
    for(int i = 0;i < 800;i++)
    {
        for(int j = 0;j < 800;j++)
        {
    		row = i;
    		column = j;
    		offset_src = image_src.channels() * (w * row + column);
    		//offset_dst = image_src.channels() * (w * row + column);
    		data_src[800*i+j] = (uchar)(pixels_src[offset_src + 0]*255/65535);
    		//data_dst = (uchar)(pixels_dst[offset_dst + 0]*255/65535);
        }
    }

    for(int i = 0;i < 200;i++)
    {
        for(int j = 0;j < 200;j++)
        {
    		row = i;
    		column = j;
    		offset_wm = image_wm.channels() * (w_w * row + column);
    		if(pixels_wm[offset_wm + 3] > 40000)
    		{
    			data_wm[200*i+j] = 1;
    		}
    		else
    		{
    			data_wm[200*i+j] = 0;
    		}
        }
    }

    image_addwm04(data_src,data_dst,data_wm);


    for(int i = 0;i < 800;i++)
    {
        for(int j = 0;j < 800;j++)
        {
    		row = i;
    		column = j;
    		offset_dst = image_dst.channels() * (w * row + column);
    		pixels_dst[offset_dst + 1] = 0;
    		pixels_dst[offset_dst + 2] = 0;
    		pixels_dst[offset_dst + 0] = (data_dst[800*i+j]*(65535/255));
    		//pixels_dst[offset_dst + 0] = 0;
    		//cout<<(int)data_dst[800*i+j]<<endl;
        }
    }
    for(int i = 0;i < 200;i++)
    {
        for(int j = 0;j < 200;j++)
        {
    		row = i;
    		column = j;
    		offset_wm = image_wm.channels() * (w_w * row + column);
    		pixels_wm[offset_wm + 3] = 65535;
    		if(data_wm[200*i+j]>0)
    		{
    			pixels_wm[offset_wm + 0] = 50000;
    		}
    		else
    		{
    			pixels_wm[offset_wm + 0] = 0;
    		}

        }
    }
    image_dst.syncPixels();
    image_dst.display();
    image_wm.resize(Magick::Geometry(200, 200));
    image_wm.syncPixels();
    image_wm.display();
    image_wm.resize(Magick::Geometry(100, 100));

    for(int i = 0;i < 100;i++)
    {
        for(int j = 0;j < 100;j++)
        {
        	for(int m = 0;m < 8;m ++)
        	{
            	for(int n = 0;n < 8;n ++)
            	{
            		row = (8 * i + m);
            		column = (8 * j + n);
            		offset_src = image_src.channels() * (w * row + column);
            		image_block_input[m*8+n] = (uchar)(pixels_src[offset_src + 0]*255/65535);
            	}
        	}
        	top_fdct(image_block_input, image_block_tmp);

        	int f_mean = (image_block_tmp[5]+image_block_tmp[12]+image_block_tmp[26]+image_block_tmp[33])/4;
			row = i;
			column = j;
			offset_wm = image_wm.channels() * (w_w * row + column);
        	if(image_block_tmp[19] > 0&& f_mean < 0 )
        	{
				if(pixels_wm[offset_wm + 3] < 40000)
				{

				}
				else
				{
					image_block_tmp[19] = 0;
				}
        	}
        	else if(image_block_tmp[19] < 0&& f_mean > 0 )
        	{
				if(pixels_wm[offset_wm + 3] < 40000)
				{
					image_block_tmp[19] = 0;
				}
				else
				{

				}
        	}
           	else if(image_block_tmp[19] >= 0&& f_mean >= 0 )
			{
				if(pixels_wm[offset_wm + 3] < 40000)
				{
					image_block_tmp[19] = min((image_block_tmp[19]-image_block_tmp[19]>>alpha),(f_mean-f_mean>>alpha));
					image_block_tmp[19] = min((uchar)(image_block_tmp[19]*(1-beta)),(uchar)(f_mean*(1-beta)));
				}
				else
				{
					image_block_tmp[19] = max((image_block_tmp[19]+image_block_tmp[19]>>alpha),(f_mean+f_mean>>alpha));
					image_block_tmp[19] = max((uchar)(image_block_tmp[19]*(1+beta)),(uchar)(f_mean*(1+beta)));
				}
			}
           	else
           	{
				if(pixels_wm[offset_wm + 3] < 40000)
				{
					image_block_tmp[19] = min((image_block_tmp[19]+image_block_tmp[19]>>alpha),(f_mean+f_mean>>alpha));
					image_block_tmp[19] = min((uchar)(image_block_tmp[19]*(1+beta)),(uchar)(f_mean*(1+beta)));
				}
				else
				{
					image_block_tmp[19] = max((image_block_tmp[19]-image_block_tmp[19]>>alpha),(f_mean-f_mean>>alpha));
					image_block_tmp[19] = max((uchar)(image_block_tmp[19]*(1-beta)),(uchar)(f_mean*(1-beta)));
				}
           	}

        	top_idct(image_block_tmp, image_block_output);
        	for(int m = 0;m < 8;m ++)
        	{
            	for(int n = 0;n < 8;n ++)
            	{
            		row = (8 * i + m);
            		column = (8 * j + n);
            		offset_dst = image_dst.channels() * (w * row + column);
            		if(image_block_output[m*8+n] <= 0)
            		{
            			image_block_output[m*8+n] = 0;
            		}
            		pixels_dst[offset_dst + 0] = (unsigned int)(image_block_output[m*8+n]*65535/255);
            	}
        	}
        }
    }
    image_dst.syncPixels();
    image_dst.display();
}

void wm1_detect(Image image_src,Image image_wm)
{
	image_wm.resize(Magick::Geometry(100, 100));

    // Write the image to a file
    int w = image_src.columns();
    int h = image_src.rows();
    MagickCore::Quantum *pixels_src = image_src.getPixels(0, 0, w, h);

    int w_w = image_wm.columns();
    int h_w= image_wm.rows();
    MagickCore::Quantum *pixels_wm = image_wm.getPixels(0, 0, w_w, h_w);

    int row = 0;
    int column = 0;
    unsigned offset_src = image_src.channels() * (w * row + column);
    unsigned offset_wm = image_wm.channels() * (w_w * row + column);

    dct_data_t image_block_input[8*8];
    dct_data_t image_block_tmp[8*8];
    dct_data_t image_block_output[8*8];
    init_fdct(); // needed by REF  FDCT
    init_idct(); // needed by WANG IDCT
    unsigned char alpha = 1;
    float beta = 0.8;

    for(int i = 0;i < 100;i++)
     {
         for(int j = 0;j < 100;j++)
         {
         	for(int m = 0;m < 8;m ++)
         	{
             	for(int n = 0;n < 8;n ++)
             	{
             		row = (8 * i + m);
             		column = (8 * j + n);
             		offset_src = image_src.channels() * (w * row + column);
             		image_block_input[m*8+n] = (unsigned char)(pixels_src[offset_src + 0]*255/65535);
             	}
         	}
            top_fdct(image_block_input, image_block_tmp);
            int f_mean = (image_block_tmp[5]+image_block_tmp[12]+image_block_tmp[26]+image_block_tmp[33])/4;
         	row = i;
         	column = j;
         	offset_wm = image_wm.channels() * (w_w * row + column);
         	pixels_wm[offset_wm + 3] = 65535;
         	if(image_block_tmp[19] > 0&& f_mean < 0 )
         	{
         		pixels_wm[offset_wm + 2] = 0;
         	}
         	else if(image_block_tmp[19] < 0&& f_mean > 0 )
         	{
         		pixels_wm[offset_wm + 2] = 50000;
         	}
         	else
         	{
         		if(image_block_tmp[19] > f_mean)
         		{
         			pixels_wm[offset_wm + 2] = 50000;
         		}
         		else
         		{
         			pixels_wm[offset_wm + 2] = 0;
         		}
         	}
         }
     }
    image_wm.syncPixels();
    image_wm.resize(Magick::Geometry(200, 200));
    image_wm.display();
}

void wm2_add(Image image_src,Image image_wm,Image &image_dst)
{
	image_wm.resize(Magick::Geometry(100, 100));

    // Write the image to a file
    int w = image_src.columns();
    int h = image_dst.rows();
    MagickCore::Quantum *pixels_src = image_src.getPixels(0, 0, w, h);
    MagickCore::Quantum *pixels_dst = image_dst.getPixels(0, 0, w, h);

    int w_w = image_wm.columns();
    int h_w= image_wm.rows();
    MagickCore::Quantum *pixels_wm = image_wm.getPixels(0, 0, w_w, h_w);

    int row = 0;
    int column = 0;
    unsigned offset_src = image_src.channels() * (w * row + column);
    unsigned offset_dst = image_dst.channels() * (w * row + column);
    unsigned offset_wm = image_wm.channels() * (w_w * row + column);

    dct_data_t image_block_input[8*8];
    dct_data_t image_block_tmp[8*8];
    dct_data_t image_block_output[8*8];
    init_fdct(); // needed by REF  FDCT
    init_idct(); // needed by WANG IDCT
    unsigned char alpha = 1;

    for(int i = 0;i < 100;i++)
    {
        for(int j = 0;j < 100;j++)
        {
        	for(int m = 0;m < 8;m ++)
        	{
            	for(int n = 0;n < 8;n ++)
            	{
            		row = (8 * i + m);
            		column = (8 * j + n);
            		offset_src = image_src.channels() * (w * row + column);
            		image_block_input[m*8+n] = (unsigned char)(pixels_src[offset_src + 0]*255/65535);
            	}
        	}
        	top_fdct(image_block_input, image_block_tmp);

			row = i;
			column = j;
			offset_wm = image_wm.channels() * (w_w * row + column);
			if(pixels_wm[offset_wm + 3] < 40000)
			{
				image_block_tmp[19] = (image_block_tmp[19]-image_block_tmp[19]>>alpha);
				image_block_tmp[19] = 0;
			}
			else
			{
				image_block_tmp[19] = (image_block_tmp[19]+image_block_tmp[19]>>alpha);
				image_block_tmp[19] = 10;
			}

        	top_idct(image_block_tmp, image_block_output);
        	for(int m = 0;m < 8;m ++)
        	{
            	for(int n = 0;n < 8;n ++)
            	{
            		row = (8 * i + m);
            		column = (8 * j + n);
            		offset_dst = image_dst.channels() * (w * row + column);
            		pixels_dst[offset_dst + 0] = (unsigned int)(image_block_output[m*8+n]*65535/255);
            	}
        	}
        }
    }
    image_dst.syncPixels();
    image_dst.display();
}

void wm2_detect(Image image_src,Image image_ref,Image image_wm)
{
	image_wm.resize(Magick::Geometry(100, 100));

    // Write the image to a file
    int w = image_src.columns();
    int h = image_src.rows();
    MagickCore::Quantum *pixels_src = image_src.getPixels(0, 0, w, h);
    MagickCore::Quantum *pixels_ref = image_ref.getPixels(0, 0, w, h);

    int w_w = image_wm.columns();
    int h_w= image_wm.rows();
    MagickCore::Quantum *pixels_wm = image_wm.getPixels(0, 0, w_w, h_w);

    int row = 0;
    int column = 0;
    unsigned offset_src = image_src.channels() * (w * row + column);
    unsigned offset_ref = image_ref.channels() * (w * row + column);
    unsigned offset_wm = image_wm.channels() * (w_w * row + column);

    dct_data_t image_block_input_src[8*8];
    dct_data_t image_block_input_ref[8*8];
    dct_data_t image_block_tmp_src[8*8];
    dct_data_t image_block_tmp_ref[8*8];
    init_fdct(); // needed by REF  FDCT
    init_idct(); // needed by WANG IDCT
    unsigned char alpha = 1;

    for(int i = 0;i < 100;i++)
     {
         for(int j = 0;j < 100;j++)
         {
        	 for(int m = 0;m < 8;m ++)
			{
				for(int n = 0;n < 8;n ++)
				{
					row = (8 * i + m);
					column = (8 * j + n);
					offset_src = image_src.channels() * (w * row + column);
					image_block_input_src[m*8+n] = (unsigned char)(pixels_src[offset_src + 0]*255/65535);
				}
			}
			for(int m = 0;m < 8;m ++)
			{
				for(int n = 0;n < 8;n ++)
				{
					row = (8 * i + m);
					column = (8 * j + n);
					offset_ref = image_ref.channels() * (w * row + column);
					image_block_input_ref[m*8+n] = (unsigned char)(pixels_ref[offset_ref + 0]*255/65535);
				}
			}
			top_fdct(image_block_input_src, image_block_tmp_src);
			top_fdct(image_block_input_ref, image_block_tmp_ref);
			row = i;
			column = j;
			unsigned offset_wm = image_wm.channels() * (w_w * row + column);
			pixels_wm[offset_wm + 3] = 65535;

			if(image_block_tmp_src[19] > 8 && image_block_tmp_src[19] < 12)
			{
				pixels_wm[offset_wm + 0] = 65535;
			}
			else
			{
				pixels_wm[offset_wm + 0] = 0;
			}
         }
     }
    image_wm.syncPixels();
    image_wm.resize(Magick::Geometry(200, 200));
    image_wm.display();
}
