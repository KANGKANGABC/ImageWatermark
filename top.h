#ifndef __TOP_H__
#define __TOP_H__

void image_fdct(uchar src[640000], uchar dst[640000]);
void image_addwm04(uchar src[640000], uchar dst[640000], bool wm[200*200]);
void image_addwm05(uchar src[640000], uchar dst[640000], bool wm[200*200]);
void image_addwm02(uchar src[640000], uchar dst[640000], bool wm[200*200]);
void swap_sint(signed short int  &a,signed short int  &b);
void enlarge_sint(signed short int  &a,signed short int  &b);//增大两值的差
void wm_fArnold(bool wm[200*200]);
void wm_iArnold(bool wm[200*200]);

#endif
