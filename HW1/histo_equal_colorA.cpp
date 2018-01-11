/*************************************************************************
 > EE569 Homework Assignment #1
 > Date:     February 4, 2017
 > Author:   Chenyu Peng
 > ID:       3498-8893-91
 > email:    chenyupe@usc.edu

 > Compiled on OS X with gcc
 > Input: ./histo_equal_colorA bedroom.raw 940 400
 ************************************************************************/

#include <stdio.h>
#include <iostream>
#include <stdlib.h>

using namespace std;

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
	unsigned char Imagetrans[Width][Length][BytesPerPixel];

	if (!(file=fopen(argv[1],"rb"))) {
		cout << "Cannot open file: " << argv[1] <<endl;
		exit(1);
	}
	fread(Imagedata, sizeof(unsigned char), Length*Width*BytesPerPixel, file);
	fclose(file);

	int histogram_r[256] = {0};
	int histogram_g[256] = {0};
	int histogram_b[256] = {0};
	for(int i=0; i<Width; i++)
		for(int j=0; j<Length; j++)
		{
			histogram_r[Imagedata[i][j][0]]++;
			histogram_g[Imagedata[i][j][1]]++;
			histogram_b[Imagedata[i][j][2]]++;
		}
			
	int sum_r = 0, sum_g = 0, sum_b = 0;
	int lowerlimit_r=0, upperlimit_r=0, lowerlimit_g=0, upperlimit_g=0, lowerlimit_b=0, upperlimit_b=0;
	for(int i=0; i<256; i++)
	{
		//R
		sum_r = sum_r + histogram_r[i];
		if(((sum_r-histogram_r[i])<(0.05*Length*Width))&&(sum_r>=(0.05*Length*Width)))
			lowerlimit_r = i;
		if(((sum_r-histogram_r[i])<(0.95*Length*Width))&&(sum_r>=(0.95*Length*Width)))
			upperlimit_r = i;
		//G
		sum_g = sum_g + histogram_g[i];
		if(((sum_g-histogram_g[i])<(0.05*Length*Width))&&(sum_g>=(0.05*Length*Width)))
			lowerlimit_g = i;
		if(((sum_g-histogram_g[i])<(0.95*Length*Width))&&(sum_g>=(0.95*Length*Width)))
			upperlimit_g = i;
		//B
		sum_b = sum_b + histogram_b[i];
		if(((sum_b-histogram_b[i])<(0.05*Length*Width))&&(sum_b>=(0.05*Length*Width)))
			lowerlimit_b = i;
		if(((sum_b-histogram_b[i])<(0.95*Length*Width))&&(sum_b>=(0.95*Length*Width)))
			upperlimit_b = i;
	}

	for(int i=0; i<Width; i++)
		for(int j=0; j<Length; j++)
		{
			if(Imagedata[i][j][0]<lowerlimit_r)
				Imagetrans[i][j][0] = 0;
			else if(Imagedata[i][j][0]>upperlimit_r)
				Imagetrans[i][j][0] = 255;
			else
				Imagetrans[i][j][0] = (255/(upperlimit_r-lowerlimit_r))*(Imagedata[i][j][0]-lowerlimit_r);

			if(Imagedata[i][j][1]<lowerlimit_g)
				Imagetrans[i][j][1] = 0;
			else if(Imagedata[i][j][1]>upperlimit_g)
				Imagetrans[i][j][1] = 255;
			else
				Imagetrans[i][j][1] = (255/(upperlimit_g-lowerlimit_g))*(Imagedata[i][j][1]-lowerlimit_g);

			if(Imagedata[i][j][2]<lowerlimit_b)
				Imagetrans[i][j][2] = 0;
			else if(Imagedata[i][j][2]>upperlimit_b)
				Imagetrans[i][j][2] = 255;
			else
				Imagetrans[i][j][2] = (255/(upperlimit_b-lowerlimit_b))*(Imagedata[i][j][2]-lowerlimit_b);
		}
			
	if (!(file=fopen("bedroom_A.raw","wb"))) {
		cout << "Cannot open file: " << "bedroom_A.raw" << endl;
		exit(1);
	}
	fwrite(Imagetrans, sizeof(unsigned char), Length*Width*BytesPerPixel, file);
	fclose(file);

	return 0;
}
