/*************************************************************************
 > EE569 Homework Assignment #1
 > Date:     February 4, 2017
 > Author:   Chenyu Peng
 > ID:       3498-8893-91
 > email:    chenyupe@usc.edu

 > Compiled on OS X with gcc
 > Input: ./NLM_filter pepper_noisy.raw pepper.raw 512 512
          ./NLM_filter sailboat_noisy.raw sailboat.raw 512 512
 ************************************************************************/

#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <cmath>

#define PI 3.14159265
#define STANDARD_DEV 20
#define SEARCH_WINDOW 21
#define SIMILARITY_WINDOW 3
#define H_CO 1.0

using namespace std;

double MAX(double ax, double by);

int main(int argc, char *argv[])

{
	FILE *file;
	const int BytesPerPixel = 3;
	int Length = 0;
	int Width = 0;
	
	if (argc < 5){
		cout << "Syntax Error - Incorrect Parameter Usage:" << endl;
		cout << "program_name noisy_image.raw clean_image.raw Length Width" << endl;
		return 0;
	}
	
	if (argc >= 5)
	{
		Length = atoi(argv[3]);
		Width = atoi(argv[4]);
	}
	
	unsigned char Imagedata_noisy[Width][Length][BytesPerPixel];
	unsigned char Imagedata_clean[Width][Length][BytesPerPixel];

	if (!(file=fopen(argv[1],"rb"))) {
		cout << "Cannot open file: " << argv[1] <<endl;
		exit(1);
	}
	fread(Imagedata_noisy, sizeof(unsigned char), Length*Width*BytesPerPixel, file);
	fclose(file);

	if (!(file=fopen(argv[2],"rb"))) {
		cout << "Cannot open file: " << argv[2] <<endl;
		exit(1);
	}
	fread(Imagedata_clean, sizeof(unsigned char), Length*Width*BytesPerPixel, file);
	fclose(file);

	unsigned char Imagetrans_1[Width+6][Length+6][BytesPerPixel];
	unsigned char Imagetrans_2[Width][Length][BytesPerPixel];

	for(int i=0; i<3; i++)
		for(int j=3; j<Length+3; j++)
			for(int k=0; k<BytesPerPixel; k++)
				Imagetrans_1[i][j][k] = Imagedata_noisy[2-i][j-3][k];

	for(int i=3; i<Width+3; i++)
		for(int j=3; j<Length+3; j++)
			for(int k=0; k<BytesPerPixel; k++)
				Imagetrans_1[i][j][k] = Imagedata_noisy[i-3][j-3][k];

	for(int i=Width+3; i<Width+6; i++)
		for(int j=3; j<Length+3; j++)
			for(int k=0; k<BytesPerPixel; k++)
				Imagetrans_1[i][j][k] = Imagetrans_1[2*Width+5-i][j][k];

	for(int i=0; i<Width+6; i++)
		for(int j=0; j<3; j++)
			for(int k=0; k<BytesPerPixel; k++)
				Imagetrans_1[i][j][k] = Imagetrans_1[i][5-j][k];

	for(int i=0; i<Width+6; i++)
		for(int j=Length+3; j<Length+6; j++)
			for(int k=0; k<BytesPerPixel; k++)
				Imagetrans_1[i][j][k] = Imagetrans_1[i][2*Length+5-j][k];

	int start_flag_i = 0;
	int end_flag_i = 0;
	int start_flag_j = 0;
	int end_flag_j = 0;

	for(int i=3; i<Width+3; i++)
		for(int j=3; j<Length+3; j++)
		{
			if((i-10)<=3)
			{
				start_flag_i = 3;
				if((i+10)>=Width+3)
					end_flag_i = Width+3;
				else
					end_flag_i = i+10;
			}
			else
			{
				start_flag_i = i-10;
				if((i+10)>=Width+3)
					end_flag_i = Width+3;
				else
					end_flag_i = i+10;
			}
				
			if((j-10)<=3)
			{
				start_flag_j = 3;
				if((j+10)>=Length+3)
					end_flag_j = Length+3;
				else
					end_flag_j = j+10;
			}
			else
			{
				start_flag_j = j-10;
				if((j+10)>=Length+3)
					end_flag_j = Length+3;
				else
					end_flag_j = j+10;
			}

			double weight[SEARCH_WINDOW][SEARCH_WINDOW] = {0.0};
			double result_weight[SEARCH_WINDOW][SEARCH_WINDOW][BytesPerPixel] = {0.0};
			double distance =0.0;
			double weight_co =0.0;
			double result_weight_final[BytesPerPixel] = {0.0};

			for(int x=start_flag_i; x<end_flag_i+1; x++)
				for(int y=start_flag_j; y<end_flag_j+1; y++)
				{
					for(int a=x-1; a<x+2; a++)
						for(int b=y-1; b<y+2; b++)
							for(int k=0; k<BytesPerPixel; k++)
								distance = distance + pow((Imagetrans_1[a][b][k]-Imagetrans_1[i+a-x][j+b-y][k]),2);
					distance = distance/27.0; //27 = 3*pow(SIMILARITY_WINDOW,2)
					weight[x-start_flag_i][y-start_flag_j] = exp(-(MAX(distance-2*pow(STANDARD_DEV,2),0.0))/(pow(H_CO*STANDARD_DEV,2)));
					for(int k=0; k<BytesPerPixel; k++)
						result_weight[x-start_flag_i][y-start_flag_j][k] = weight[x-start_flag_i][y-start_flag_j] * Imagetrans_1[x][y][k];
				}
				
			for(int x=0; x<end_flag_i-start_flag_i+1; x++)
				for(int y=0; y<end_flag_j-start_flag_j+1; y++)
					weight_co = weight_co + weight[x][y];

			for(int x=0; x<end_flag_i-start_flag_i+1; x++)
				for(int y=0; y<end_flag_j-start_flag_j+1; y++)
					for(int k=0; k<BytesPerPixel; k++)
						result_weight_final[k] = result_weight_final[k] + result_weight[x][y][k];

			for(int k=0; k<BytesPerPixel; k++)
				Imagetrans_2[i-3][j-3][k] = result_weight_final[k]/weight_co;

		}

	unsigned int sum_filter[3] = {0};
	double MSE_filter[3] = {0.0};
	double PSNR_filter[3] = {0.0};
	for(int i=0; i<Width; i++)
		for(int j=0; j<Length; j++)
			for(int k=0; k<BytesPerPixel; k++)
				sum_filter[k] = sum_filter[k] + (Imagetrans_2[i][j][k]-Imagedata_clean[i][j][k])*(Imagetrans_2[i][j][k]-Imagedata_clean[i][j][k]);

	MSE_filter[0] = sum_filter[0]/(Length*Width);
	MSE_filter[1] = sum_filter[1]/(Length*Width);
	MSE_filter[2] = sum_filter[2]/(Length*Width);

	PSNR_filter[0] = 10*log10(65025/MSE_filter[0]);
	PSNR_filter[1] = 10*log10(65025/MSE_filter[1]);
	PSNR_filter[2] = 10*log10(65025/MSE_filter[2]);

	cout <<"R:" << PSNR_filter[0] << endl;
	cout <<"G:" << PSNR_filter[1] << endl;
	cout <<"B:" << PSNR_filter[2] << endl;

	if (!strcmp(argv[1],"pepper_noisy.raw"))
	{
		if (!(file=fopen("pepper_NLM.raw","wb"))) {
			cout << "Cannot open file: " << "pepper_NLM.raw" << endl;
			exit(1);
		}
		fwrite(Imagetrans_2, sizeof(unsigned char), Length*Width*BytesPerPixel, file);
		fclose(file);
	}

	if (!strcmp(argv[1],"sailboat_noisy.raw"))
	{
		if (!(file=fopen("sailboat_NLM.raw","wb"))) {
			cout << "Cannot open file: " << "sailboat_NLM.raw" << endl;
			exit(1);
		}
		fwrite(Imagetrans_2, sizeof(unsigned char), Length*Width*BytesPerPixel, file);
		fclose(file);
	}

	return 0;
}

double MAX(double ax, double by)
{
    double max = ax;
    if(max<by)
    	max = by;
    return max;
}

