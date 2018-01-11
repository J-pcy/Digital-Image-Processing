/*************************************************************************
 > EE569 Homework Assignment #1
 > Date:     February 4, 2017
 > Author:   Chenyu Peng
 > ID:       3498-8893-91
 > email:    chenyupe@usc.edu

 > Compiled on OS X with gcc
 > Input: ./mix_noise pepper.raw pepper_noisy.raw 512 512
 ************************************************************************/

#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <cmath>

using namespace std;

int main(int argc, char *argv[])

{
	FILE *file;
	int BytesPerPixel = 3;
	int Length = 0;
	int Width = 0;
	
	if (argc < 5){
		cout << "Syntax Error - Incorrect Parameter Usage:" << endl;
		cout << "program_name input_image.raw noisy_image.raw Length Width" << endl;
		return 0;
	}
	
	if (argc >= 5)
	{
		Length = atoi(argv[3]);
		Width = atoi(argv[4]);
	}
	
	unsigned char Imagedata1[Width][Length][BytesPerPixel];
	unsigned char Imagedata2[Width][Length][BytesPerPixel];
	unsigned char Imagedata3[Width+2][Length+2][BytesPerPixel];
	unsigned char Imagedata4[Width][Length][BytesPerPixel];
	unsigned char Imagetrans[Width][Length][BytesPerPixel];

	if (!(file=fopen(argv[1],"rb"))) {
		cout << "Cannot open file: " << argv[1] <<endl;
		exit(1);
	}
	fread(Imagedata1, sizeof(unsigned char), Length*Width*BytesPerPixel, file);
	fclose(file);

	if (!(file=fopen(argv[2],"rb"))) {
		cout << "Cannot open file: " << argv[2] <<endl;
		exit(1);
	}
	fread(Imagedata2, sizeof(unsigned char), Length*Width*BytesPerPixel, file);
	fclose(file);

	unsigned int sum[3] = {0};
	for(int i=0; i<Width; i++)
		for(int j=0; j<Length; j++)
		{
			for(int k=0; k<BytesPerPixel; k++)
			{
				Imagetrans[i][j][k] = Imagedata2[i][j][k] - Imagedata1[i][j][k];
			}
//			printf("%u ", Imagetrans[i][j][0]);
		}

	int histogram_r[256] = {0};
	int histogram_g[256] = {0};
	int histogram_b[256] = {0};
	for(int i=0; i<Width; i++)
		for(int j=0; j<Length; j++)
		{
			histogram_r[Imagetrans[i][j][0]]++;
			histogram_g[Imagetrans[i][j][1]]++;
			histogram_b[Imagetrans[i][j][2]]++;
		}
	
	if (!(file=fopen("pepper_mix.raw","wb"))) {
		cout << "Cannot open file: " << "pepper_mix.raw" << endl;
		exit(1);
	}
	fwrite(Imagetrans, sizeof(unsigned char), Length*Width*BytesPerPixel, file);
	fclose(file);

	return 0;
}
