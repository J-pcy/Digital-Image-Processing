/*************************************************************************
 > EE569 Homework Assignment #1
 > Date:     February 4, 2017
 > Author:   Chenyu Peng
 > ID:       3498-8893-91
 > email:    chenyupe@usc.edu

 > Compiled on OS X with gcc
 > Input: ./histo_trans forest_1.raw 940 600
          ./histo_trans forest_2.raw 550 413
 ************************************************************************/

#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <cmath>

#define PI 3.14159265

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

	double histogram_gaussian_pdf[256] = {0.0};
	double histogram_gaussian_cdf[256] = {0.0};
	for(int i=0; i<256; i++)
		histogram_gaussian_pdf[i] = (1/sqrt(800*PI)) * exp(-(((i-70)*(i-70))/800.0));

	histogram_gaussian_cdf[0] = histogram_gaussian_pdf[0];
	for(int i=1; i<256; i++)
	{
		histogram_gaussian_cdf[i] = histogram_gaussian_cdf[i-1] + histogram_gaussian_pdf[i];
//		cout << i << ":" << histogram_gaussian_cdf[i] << endl;
	}

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

//	cout << "0:" << histogram[0] << endl;

	for(int i=1; i<256; i++)
	{
		histogram_r[i] = histogram_r[i-1] + histogram_r[i];
		histogram_g[i] = histogram_g[i-1] + histogram_g[i];
		histogram_b[i] = histogram_b[i-1] + histogram_b[i];
//		cout << i << ":" << histogram[i] << endl;
	}

	for(int i=0; i<Width; i++)
		for(int j=0; j<Length; j++)
			for(int k=0; k<255; k++)
			{
				if((histogram_r[Imagedata[i][j][0]]>=(histogram_gaussian_cdf[k]*Length*Width))&&(histogram_r[Imagedata[i][j][0]]<(histogram_gaussian_cdf[k+1]*Length*Width)))
					Imagetrans[i][j][0] = k;
				else if(histogram_r[Imagedata[i][j][0]]>=(histogram_gaussian_cdf[255]*Length*Width))
					Imagetrans[i][j][0] = Imagedata[i][j][0];

				if((histogram_r[Imagedata[i][j][1]]>=(histogram_gaussian_cdf[k]*Length*Width))&&(histogram_r[Imagedata[i][j][1]]<(histogram_gaussian_cdf[k+1]*Length*Width)))
					Imagetrans[i][j][1] = k;
				else if(histogram_r[Imagedata[i][j][1]]>=(histogram_gaussian_cdf[255]*Length*Width))
					Imagetrans[i][j][1] = Imagedata[i][j][1];

				if((histogram_r[Imagedata[i][j][2]]>=(histogram_gaussian_cdf[k]*Length*Width))&&(histogram_r[Imagedata[i][j][2]]<(histogram_gaussian_cdf[k+1]*Length*Width)))
					Imagetrans[i][j][2] = k;
				else if(histogram_r[Imagedata[i][j][2]]>=(histogram_gaussian_cdf[255]*Length*Width))
					Imagetrans[i][j][2] = Imagedata[i][j][2];
			}

	if (!strcmp(argv[1],"forest_1.raw"))
	{
		if (!(file=fopen("forest_1_trans.raw","wb"))) {
			cout << "Cannot open file: " << "forest_1_trans.raw" << endl;
			exit(1);
		}
		fwrite(Imagetrans, sizeof(unsigned char), Length*Width*BytesPerPixel, file);
		fclose(file);
	}

	if (!strcmp(argv[1],"forest_2.raw"))
	{
		if (!(file=fopen("forest_2_trans.raw","wb"))) {
			cout << "Cannot open file: " << "forest_2_trans.raw" << endl;
			exit(1);
		}
		fwrite(Imagetrans, sizeof(unsigned char), Length*Width*BytesPerPixel, file);
		fclose(file);
	}

	return 0;
}
