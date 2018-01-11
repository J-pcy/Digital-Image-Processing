/*************************************************************************
 > EE569 Homework Assignment #1
 > Date:     February 4, 2017
 > Author:   Chenyu Peng
 > ID:       3498-8893-91
 > email:    chenyupe@usc.edu

 > Compiled on OS X with gcc
 > Input: ./mix_noise_mean pepper.raw pepper_noisy.raw 512 512
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
				sum[k] = sum[k] + (Imagedata2[i][j][k] - Imagedata1[i][j][k])*(Imagedata2[i][j][k] - Imagedata1[i][j][k]);
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

	double MSE[3] = {0.0};
	double PSNR[3] = {0.0};

	MSE[0] = sum[0]/(Length*Width);
	MSE[1] = sum[1]/(Length*Width);
	MSE[2] = sum[2]/(Length*Width);

	PSNR[0] = 10*log10(65025/MSE[0]);
	PSNR[1] = 10*log10(65025/MSE[1]);
	PSNR[2] = 10*log10(65025/MSE[2]);

	cout <<"R:" << PSNR[0] << endl;
	cout <<"G:" << PSNR[1] << endl;
	cout <<"B:" << PSNR[2] << endl;

	for(int i=1; i<Width+1; i++)
		for(int k=0; k<BytesPerPixel; k++)
			Imagedata3[i][0][k] = Imagedata2[i][0][k];

	for(int i=1; i<Width+1; i++)
		for(int k=0; k<BytesPerPixel; k++)
			Imagedata3[i][Length+1][k] = Imagedata2[i][Length-1][k];

	for(int i=1; i<Width+1; i++)
		for(int j=1; j<Length+1; j++)
			for(int k=0; k<BytesPerPixel; k++)
				Imagedata3[i][j][k] = Imagedata2[i-1][j-1][k];

	for(int j=0; j<Width+2; j++)
		for(int k=0; k<BytesPerPixel; k++)
			Imagedata3[0][j][k] = Imagedata3[1][j][k];

	for(int j=0; j<Width+2; j++)
		for(int k=0; k<BytesPerPixel; k++)
			Imagedata3[Width+1][j][k] = Imagedata3[Width][j][k];

	for(int i=0; i<Width; i++)
		for(int j=0; j<Length; j++)
			for(int k=0; k<BytesPerPixel; k++)
				Imagedata4[i][j][k] = (Imagedata3[i][j][k]+Imagedata3[i][j+1][k]+Imagedata3[i][j+2][k]+Imagedata3[i+1][j][k]+Imagedata3[i+1][j+1][k]+Imagedata3[i+1][j+2][k]+Imagedata3[i+2][j][k]+Imagedata3[i+2][j+1][k]+Imagedata3[i+2][j+2][k])/9;

	unsigned int sum_filter[3] = {0};
	double MSE_filter[3] = {0.0};
	double PSNR_filter[3] = {0.0};
	for(int i=0; i<Width; i++)
		for(int j=0; j<Length; j++)
			for(int k=0; k<BytesPerPixel; k++)
				sum_filter[k] = sum_filter[k] + (Imagedata4[i][j][k] - Imagedata1[i][j][k])*(Imagedata4[i][j][k] - Imagedata1[i][j][k]);

	MSE_filter[0] = sum_filter[0]/(Length*Width);
	MSE_filter[1] = sum_filter[1]/(Length*Width);
	MSE_filter[2] = sum_filter[2]/(Length*Width);

	PSNR_filter[0] = 10*log10(65025/MSE_filter[0]);
	PSNR_filter[1] = 10*log10(65025/MSE_filter[1]);
	PSNR_filter[2] = 10*log10(65025/MSE_filter[2]);

	cout <<"R:" << PSNR_filter[0] << endl;
	cout <<"G:" << PSNR_filter[1] << endl;
	cout <<"B:" << PSNR_filter[2] << endl;

	if (!(file=fopen("pepper_mean.raw","wb"))) {
		cout << "Cannot open file: " << "pepper_mean.raw" << endl;
		exit(1);
	}
	fwrite(Imagedata4, sizeof(unsigned char), Length*Width*BytesPerPixel, file);
	fclose(file);

	return 0;
}
