/*************************************************************************
 > EE569 Homework Assignment #1
 > Date:     February 4, 2017
 > Author:   Chenyu Peng
 > ID:       3498-8893-91
 > email:    chenyupe@usc.edu

 > Compiled on OS X with gcc
 > Input: ./histo_equal_colorB bedroom.raw 940 400
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

	for(int i=1; i<256; i++)
	{
		histogram_r[i] = histogram_r[i-1] + histogram_r[i];
		histogram_g[i] = histogram_g[i-1] + histogram_g[i];
		histogram_b[i] = histogram_b[i-1] + histogram_b[i];
//		cout << i << ":" << histogram[i] << endl;
	}

	for(int i=0; i<Width; i++)
		for(int j=0; j<Length; j++)
		{
			Imagetrans[i][j][0] = (255.0/(Length*Width))*histogram_r[Imagedata[i][j][0]];
			Imagetrans[i][j][1] = (255.0/(Length*Width))*histogram_g[Imagedata[i][j][1]];
			Imagetrans[i][j][2] = (255.0/(Length*Width))*histogram_b[Imagedata[i][j][2]];
		}

	if (!(file=fopen("bedroom_B.raw","wb"))) {
		cout << "Cannot open file: " << "bedroom_B.raw" << endl;
		exit(1);
	}
	fwrite(Imagetrans, sizeof(unsigned char), Length*Width*BytesPerPixel, file);
	fclose(file);

	return 0;
}
