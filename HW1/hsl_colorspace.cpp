/*************************************************************************
 > EE569 Homework Assignment #1
 > Date:     February 4, 2017
 > Author:   Chenyu Peng
 > ID:       3498-8893-91
 > email:    chenyupe@usc.edu

 > Compiled on OS X with gcc
 > Input: ./hsl_colorspace cat.raw 600 398
          ./hsl_colorspace dolphin.raw 640 480
 ************************************************************************/

#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <cmath>

using namespace std;

unsigned char MAX(unsigned char R, unsigned char G, unsigned char B);
unsigned char MIN(unsigned char R, unsigned char G, unsigned char B);

int main(int argc, char *argv[])

{
	FILE *file;
	int BytesPerPixel = 3;
	int Length = 0;
	int Width = 0;
	
	if (argc < 4){
		cout << "Syntax Error - Incorrect Parameter Usage:" << endl;
		cout << "program_name input_image.raw Length Width" << endl;
		return 0;
	}
	
	if (argc >= 4)
	{
		Length = atoi(argv[2]);
		Width = atoi(argv[3]);
	}
	
	unsigned char Imagedata[Width][Length][BytesPerPixel];

	if (!(file=fopen(argv[1],"rb"))) {
		cout << "Cannot open file: " << argv[1] <<endl;
		exit(1);
	}
	fread(Imagedata, sizeof(unsigned char), Length*Width*BytesPerPixel, file);
	fclose(file);

	unsigned char ImageTrans_h[Width][Length];
	unsigned char ImageTrans_s[Width][Length];
	unsigned char ImageTrans_l[Width][Length];
	for(int i=0; i<Width; i++)
	{
		for(int j=0; j<Length; j++)
		{
			unsigned char M = MAX(Imagedata[i][j][0], Imagedata[i][j][1], Imagedata[i][j][2]);
			unsigned char m = MIN(Imagedata[i][j][0], Imagedata[i][j][1], Imagedata[i][j][2]);
			double C = M - m;
			double H = 0.0, L = 0.0, S = 0.0;

			double X1 = (Imagedata[i][j][1]-Imagedata[i][j][2])/(double)C;
			double X2 = (Imagedata[i][j][2]-Imagedata[i][j][0])/(double)C;
			double X3 = (Imagedata[i][j][0]-Imagedata[i][j][1])/(double)C;

			if(C==0)
				H = 0;
			else if(M==Imagedata[i][j][0])
				H = 60.0*(X1-6.0*floor(X1/6.0));
			else if(M==Imagedata[i][j][1])
				H = 60.0*(X2+2);
			else if(M==Imagedata[i][j][2])
				H = 60.0*(X3+4);

			L = (M + m)/2.0;

			if((L==0.0)||(L==255.0))
				S = 0;
			else if((L>0.0)&&(L<127.5))
				S = 255.0*C/(2*L);
			else if((L>=127.5)&&(L<255.0))
				S = 255.0*C/(510.0-2.0*L);

			ImageTrans_h[i][j] = 0.708*H;
			ImageTrans_s[i][j] = S;
			ImageTrans_l[i][j] = C;
		}
	}

	if (!strcmp(argv[1],"cat.raw"))
	{
		if (!(file=fopen("cat_h.raw","wb"))) {
			cout << "Cannot open file: " << "cat_h.raw" << endl;
			exit(1);
		}
		fwrite(ImageTrans_h, sizeof(unsigned char), Length*Width, file);
		fclose(file);

		if (!(file=fopen("cat_s.raw","wb"))) {
			cout << "Cannot open file: " << "cat_s.raw" << endl;
			exit(1);
		}
		fwrite(ImageTrans_s, sizeof(unsigned char), Length*Width, file);
		fclose(file);

		if (!(file=fopen("cat_l.raw","wb"))) {
			cout << "Cannot open file: " << "cat_l.raw" << endl;
			exit(1);
		}
		fwrite(ImageTrans_l, sizeof(unsigned char), Length*Width, file);
		fclose(file);
	}

	if (!strcmp(argv[1],"dolphin.raw"))
	{
		if (!(file=fopen("dolphin_h.raw","wb"))) {
			cout << "Cannot open file: " << "dolphin_h.raw" << endl;
			exit(1);
		}
		fwrite(ImageTrans_h, sizeof(unsigned char), Length*Width, file);
		fclose(file);

		if (!(file=fopen("dolphin_s.raw","wb"))) {
			cout << "Cannot open file: " << "dolphin_s.raw" << endl;
			exit(1);
		}
		fwrite(ImageTrans_s, sizeof(unsigned char), Length*Width, file);
		fclose(file);

		if (!(file=fopen("dolphin_l.raw","wb"))) {
			cout << "Cannot open file: " << "dolphin_l.raw" << endl;
			exit(1);
		}
		fwrite(ImageTrans_l, sizeof(unsigned char), Length*Width, file);
		fclose(file);
	}

	return 0;
}

unsigned char MAX(unsigned char R, unsigned char G, unsigned char B)
{
    unsigned char max = R;
    if(max<G)
    	max = G;
    if(max<B)
    	max = B;
    return max;
}

unsigned char MIN(unsigned char R, unsigned char G, unsigned char B)
{
    unsigned char min = R;
    if(min>G)
    	min = G;
    if(min>B)
    	min = B;
    return min;
}
