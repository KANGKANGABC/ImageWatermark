#include <iostream>
#include "evaluate.h"

double getPSNR(Image* src, Image* addwtm)
{
  Image image1 = *src;
  Image image2 = *addwtm;
  int w = image1.columns();
  int h = image1.rows();
  MagickCore::Quantum *pixels = image1.getPixels(0, 0, w, h);
  MagickCore::Quantum *pixels1 = image2.getPixels(0, 0, w, h);
  int row;
  int column;
  double tmp = 0;
  unsigned offset1;
  unsigned offset2;
  double absdiff;
  double MAX = 255;

  for(row = 0; row < h; row++)
  {
    for(column = 0; column < w; column++)
    {
      offset1 = image1.channels() * (w * row + column);
      offset2 = image2.channels() * (w * row + column);
      absdiff = abs(pixels[offset1 + 0]/65535*255 - pixels1[offset2 + 0]/65535*255);
      tmp = tmp + pow(absdiff, 2);
    }
  }
  double MSE = tmp / (w*h);
  double PSNR = 10*log10(pow(MAX,2)/MSE);
  cout << PSNR;

  return PSNR;

}

double getNC(Image* src, Image* extrwtm)
{
  Image image1 = *src;
  Image image2 = *extrwtm;
  int w = image1.columns();
  int h = image1.rows();
  MagickCore::Quantum *pixels = image1.getPixels(0, 0, w, h);
  MagickCore::Quantum *pixels1 = image2.getPixels(0, 0, w, h);
  int row;
  int column;
  double tmp = 0;
  unsigned offset1;
  unsigned offset2;
  double AA=0,AB=0,BB=0;

  for(row = 0; row < h; row++)
  {
    for(column = 0; column < w; column++)
    {
      offset1 = image1.channels() * (w * row + column);
      if (pixels[offset1 + 3] > 40000)
      {
    	  pixels[offset1 + 3] = 0;
      }
      else
      {
    	  pixels[offset1 + 3] = 65535;
      }
    }
  }


  for(row = 0; row < h; row++)
  {
    for(column = 0; column < w; column++)
    {
      offset1 = image1.channels() * (w * row + column);
      offset2 = image2.channels() * (w * row + column);
      AA = AA + pow(pixels[offset1 + 3]/65535*255, 2);
      //BB = BB + pow(pixels1[offset2 + 3]/65535*255, 2); test whether NC formula is true or not
      BB = BB + pow(pixels1[offset2 + 0]/65535*255, 2);
      //AB = AB + (pixels[offset1 + 3]/65535*255) * (pixels1[offset2 + 3]/65535*255); test whether NC formula is true or not
      AB = AB + (pixels[offset1 + 3]/65535*255) * (pixels1[offset2 + 0]/65535*255);
    }
  }
  double NC = AB/(sqrt(AA)*sqrt(BB));
  cout << " " << NC;
  return NC;

}
