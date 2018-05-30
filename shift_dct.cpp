#include <iostream>

using namespace std;

//定义一维dct正变换
void dct(int data[8]);
void idct(int data[8]);
void shift_dct2d(int (*data)[8], int height, int width);
void shift_idct2d(int(*data)[8], int height, int width);

void dct(int data[8])
{
	int datatmp[8];
	datatmp[0] = data[0] + data[7];
	datatmp[1] = data[1] + data[6];
	datatmp[2] = data[2] + data[5];
	datatmp[3] = data[3] + data[4];
	datatmp[4] = data[3] - data[4];
	datatmp[5] = data[2] - data[5];
	datatmp[6] = data[1] - data[6];
	datatmp[7] = data[0] - data[7];

	data[0] = datatmp[0] + datatmp[3];
	data[1] = datatmp[1] + datatmp[2];
	data[2] = datatmp[1] - datatmp[2];
	data[3] = datatmp[0] - datatmp[3];

	data[0] += data[1];                    //// data[0] = X0
	data[1] = -data[1] + ((data[0]) >> 1);     /// data[1] = X4

	data[3] = data[3] - (data[2] >> 1) - (data[2] >> 3);
	data[2] += data[3];
	data[3] = data[3] - (data[2] >> 1) - (data[2] >> 3);
	// data[2] = X2    data[3] = X6

	datatmp[5] = datatmp[5] - (datatmp[6] >> 1) + (datatmp[6] >> 4);
	datatmp[6] = datatmp[6] + (datatmp[5] >> 1) + (datatmp[5] >> 2);
	datatmp[5] = -datatmp[5] + (datatmp[6] >> 1) - (datatmp[6] >> 4);

	data[4] = datatmp[4] + datatmp[5];
	data[5] = datatmp[4] - datatmp[5];
	data[6] = -datatmp[6] + datatmp[7];
	data[7] = datatmp[6] + datatmp[7];

	data[7] = data[7] - (data[4] >> 1) - (data[4] >> 2) - (data[4] >> 4);
	data[4] = data[4] + data[7];
	data[7] = data[7] - (data[4] >> 1) - (data[4] >> 2) - (data[4] >> 4);
	// data[4] = X1      data[7] = X7

	data[6] = data[6] - (data[5] >> 2);
	data[5] = data[5] + (data[6] >> 1);
	data[6] = data[6] - (data[5] >> 2);
	// data[5] = X3    data[7] = X5

	/*   datatmp[0] = data[0];            datatmp[1] = data[2];
	datatmp[2] = data[1];    datatmp[3] = data[3];
	datatmp[4] = data[4];    datatmp[5] = data[6];
	datatmp[6] = data[5];    datatmp[7] = data[7];
	*/
	datatmp[0] = data[0];    datatmp[1] = data[4];
	datatmp[2] = data[2];    datatmp[3] = data[6];
	datatmp[4] = data[1];    datatmp[5] = data[5];
	datatmp[6] = data[3];    datatmp[7] = data[7];

int i;
for (i = 0; i < 8; i++)  data[i] = datatmp[i];
}

void idct(int data[8])
{
	int datatmp[8];
	int i;
	for (i = 0; i < 8; i++)  datatmp[i] = data[i];
	data[0] = datatmp[0];    data[1] = datatmp[2];
	data[2] = datatmp[4];    data[3] = datatmp[6];
	data[4] = datatmp[1];    data[5] = datatmp[3];
	data[6] = datatmp[5];    data[7] = datatmp[7];

	datatmp[1] = -data[2] + (data[0] >> 1);
	datatmp[0] = data[0] - datatmp[1];

	datatmp[3] = data[3] + (data[1] >> 1) + (data[1] >> 3);
	datatmp[2] = data[1] - datatmp[3];
	datatmp[3] = datatmp[3] + (datatmp[2] >> 1) + (datatmp[2] >> 3);

	datatmp[6] = data[5] + (data[6] >> 2);
	datatmp[5] = data[6] - (datatmp[6] >> 1);
	datatmp[6] = datatmp[6] + (datatmp[5] >> 2);

	datatmp[7] = data[7] + (data[4] >> 1) + (data[4] >> 2) + (data[4] >> 4);
	datatmp[4] = data[4] - datatmp[7];
	datatmp[7] = datatmp[7] + (datatmp[4] >> 1) + (datatmp[4] >> 2) + (datatmp[4] >> 4);
	// four inverse lifting step

	data[0] = (datatmp[0] + datatmp[3]) >> 1;
	data[3] = (datatmp[0] - datatmp[3]) >> 1;
	data[1] = (datatmp[1] + datatmp[2]) >> 1;
	data[2] = (datatmp[1] - datatmp[2]) >> 1;

	data[4] = (datatmp[4] + datatmp[5]) >> 1;
	data[5] = (datatmp[4] - datatmp[5]) >> 1;
	data[6] = (-datatmp[6] + datatmp[7]) >> 1;
	data[7] = (datatmp[6] + datatmp[7]) >> 1;
	// four inverse butterfly

	data[5] = -data[5] + (data[6] >> 1) - (data[6] >> 4);
	data[6] = data[6] - (data[5] >> 1) - (data[5] >> 2);
	data[5] = data[5] + (data[6] >> 1) - (data[6] >> 4);

	/////////////////
	datatmp[0] = (data[0] + data[7]) >> 1;
	datatmp[1] = (data[1] + data[6]) >> 1;
	datatmp[2] = (data[2] + data[5]) >> 1;
	datatmp[3] = (data[3] + data[4]) >> 1;
	datatmp[4] = (data[3] - data[4]) >> 1;
	datatmp[5] = (data[2] - data[5]) >> 1;
	datatmp[6] = (data[1] - data[6]) >> 1;
	datatmp[7] = (data[0] - data[7]) >> 1;

	//int i;
	for (i = 0; i < 8; i++) data[i] = datatmp[i];
}

void shift_dct2d(int(*data)[8], int height, int width)
{
#pragma HLS INTERFACE ap_bus port=data
	int nheight, nwidth;
	int i, j, k, l;
	int ni, nj;

	int datatmp[8];
	nheight = height >> 3;
	nwidth = width >> 3;

	ni = 0;
	for (i = 0; i < nheight; i++)
	{
		nj = 0;
		for (j = 0; j < nwidth; j++)
		{
			for (k = 0; k < 8; k++)
			{
				for (l = 0; l < 8; l++)
					datatmp[l] = data[ni + k][nj + l];
				dct(datatmp);
				for (l = 0; l < 8; l++)
					data[ni + k][nj + l] = datatmp[l];
			}

			for (k = 0; k < 8; k++)
			{
				for (l = 0; l < 8; l++)
					datatmp[l] = data[ni + l][nj + k];
				dct(datatmp);
				for (l = 0; l < 8; l++)
					data[ni + l][nj + k] = datatmp[l];
			}
			nj = nj + 8;
		}
		ni = ni + 8;

	}
}

void shift_idct2d(int(*data)[8], int height, int width)
{
#pragma HLS INTERFACE ap_bus port=data
	int nheight, nwidth;
	int i, j, k, l;
	int ni, nj;

	int datatmp[8];
	nheight = height >> 3;
	nwidth = width >> 3;

	ni = 0;
	for (i = 0; i<nheight; i++)
	{
		nj = 0;
		for (j = 0; j<nwidth; j++)
		{
			for (k = 0; k<8; k++)
			{
				for (l = 0; l<8; l++)
					datatmp[l] = data[ni + l][nj + k];
				idct(datatmp);
				for (l = 0; l<8; l++)
					data[ni + l][nj + k] = datatmp[l];
			}
			for (k = 0; k<8; k++)
			{

				for (l = 0; l<8; l++)
					datatmp[l] = data[ni + k][nj + l];
				idct(datatmp);
				for (l = 0; l<8; l++)
					data[ni + k][nj + l] = datatmp[l];
			}
			nj = nj + 8;
		}
		ni = ni + 8;
	}
}
