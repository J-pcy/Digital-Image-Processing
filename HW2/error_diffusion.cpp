/*************************************************************************
 > EE569 Homework Assignment #2
 > Date:     February 24, 2017
 > Author:   Chenyu Peng
 > ID:       3498-8893-91
 > email:    chenyupe@usc.edu

 > Compiled on OS X with gcc
 > Input: g++ -o error_diffusion error_diffusion.cpp
 		  ./error_diffusion man.raw 512 512
 ************************************************************************/

#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <cmath>

using namespace std;

int main(int argc, char *argv[])
{
	FILE *file;
	int BytesPerPixel = 1;
	int Length = 0;
	int Width = 0;
	
	if (argc < 4)
	{
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

	int ImageTrans1[Width+2][Length+2][BytesPerPixel];
	unsigned char ImageTrans2[Width][Length][BytesPerPixel];
	int ImageTrans3[Width+2][Length+2][BytesPerPixel];
	unsigned char ImageTrans4[Width][Length][BytesPerPixel];
	int ImageTrans5[Width+2][Length+2][BytesPerPixel];
	unsigned char ImageTrans6[Width][Length][BytesPerPixel];

/*************************************************line-by-line scan***********************************************/
/*
//T=1/16*[0,0,0;0,0,7;3,5,1]
	for(int i=0; i<Width; i++)
		for(int j=0; j<Length; j++)
			for(int k=0; k<BytesPerPixel; k++)
			{
				if((Imagedata[i][j][k]+ImageTrans1[i][j][k])>=128)
				{
					ImageTrans1[i][j+1][k] = ImageTrans1[i][j+1][k]+7.0/16*(Imagedata[i][j][k]+ImageTrans1[i][j][k]-255);
					ImageTrans1[i+1][j-1][k] = ImageTrans1[i+1][j-1][k]+3.0/16*(Imagedata[i][j][k]+ImageTrans1[i][j][k]-255);
					ImageTrans1[i+1][j][k] = ImageTrans1[i+1][j][k]+5.0/16*(Imagedata[i][j][k]+ImageTrans1[i][j][k]-255);
					ImageTrans1[i+1][j+1][k] = ImageTrans1[i+1][j+1][k]+1.0/16*(Imagedata[i][j][k]+ImageTrans1[i][j][k]-255);
					ImageTrans2[i][j][k] = 255;
				}
				else
				{
					ImageTrans1[i][j+1][k] = ImageTrans1[i][j+1][k]+7.0/16*(Imagedata[i][j][k]+ImageTrans1[i][j][k]-0);
					ImageTrans1[i+1][j-1][k] = ImageTrans1[i+1][j-1][k]+3.0/16*(Imagedata[i][j][k]+ImageTrans1[i][j][k]-0);
					ImageTrans1[i+1][j][k] = ImageTrans1[i+1][j][k]+5.0/16*(Imagedata[i][j][k]+ImageTrans1[i][j][k]-0);
					ImageTrans1[i+1][j+1][k] = ImageTrans1[i+1][j+1][k]+1.0/16*(Imagedata[i][j][k]+ImageTrans1[i][j][k]-0);
					ImageTrans2[i][j][k] = 0;
				}
			}

//T=1/48*[0,0,0,0,0;0,0,0,0,0;0,0,0,7,5;3,5,7,5,3;1,3,5,3,1]
	for(int i=0; i<Width; i++)
		for(int j=0; j<Length; j++)
			for(int k=0; k<BytesPerPixel; k++)
			{
				if((Imagedata[i][j][k]+ImageTrans3[i][j][k])>=128)
				{
					ImageTrans3[i][j+1][k] = ImageTrans3[i][j+1][k]+7.0/48*(Imagedata[i][j][k]+ImageTrans3[i][j][k]-255);
					ImageTrans3[i][j+2][k] = ImageTrans3[i][j+2][k]+5.0/48*(Imagedata[i][j][k]+ImageTrans3[i][j][k]-255);
					ImageTrans3[i+1][j-2][k] = ImageTrans3[i+1][j-2][k]+3.0/48*(Imagedata[i][j][k]+ImageTrans3[i][j][k]-255);
					ImageTrans3[i+1][j-1][k] = ImageTrans3[i+1][j-1][k]+5.0/48*(Imagedata[i][j][k]+ImageTrans3[i][j][k]-255);
					ImageTrans3[i+1][j][k] = ImageTrans3[i+1][j][k]+7.0/48*(Imagedata[i][j][k]+ImageTrans3[i][j][k]-255);
					ImageTrans3[i+1][j+1][k] = ImageTrans3[i+1][j+1][k]+5.0/48*(Imagedata[i][j][k]+ImageTrans3[i][j][k]-255);
					ImageTrans3[i+1][j+2][k] = ImageTrans3[i+1][j+2][k]+3.0/48*(Imagedata[i][j][k]+ImageTrans3[i][j][k]-255);
					ImageTrans3[i+2][j-2][k] = ImageTrans3[i+2][j-2][k]+1.0/48*(Imagedata[i][j][k]+ImageTrans3[i][j][k]-255);
					ImageTrans3[i+2][j-1][k] = ImageTrans3[i+2][j-1][k]+3.0/48*(Imagedata[i][j][k]+ImageTrans3[i][j][k]-255);
					ImageTrans3[i+2][j][k] = ImageTrans3[i+2][j][k]+5.0/48*(Imagedata[i][j][k]+ImageTrans3[i][j][k]-255);
					ImageTrans3[i+2][j+1][k] = ImageTrans3[i+2][j+1][k]+3.0/48*(Imagedata[i][j][k]+ImageTrans3[i][j][k]-255);
					ImageTrans3[i+2][j+2][k] = ImageTrans3[i+2][j+2][k]+1.0/48*(Imagedata[i][j][k]+ImageTrans3[i][j][k]-255);
					ImageTrans4[i][j][k] = 255;
				}
				else
				{
					ImageTrans3[i][j+1][k] = ImageTrans3[i][j+1][k]+7.0/48*(Imagedata[i][j][k]+ImageTrans3[i][j][k]-0);
					ImageTrans3[i][j+2][k] = ImageTrans3[i][j+2][k]+5.0/48*(Imagedata[i][j][k]+ImageTrans3[i][j][k]-0);
					ImageTrans3[i+1][j-2][k] = ImageTrans3[i+1][j-2][k]+3.0/48*(Imagedata[i][j][k]+ImageTrans3[i][j][k]-0);
					ImageTrans3[i+1][j-1][k] = ImageTrans3[i+1][j-1][k]+5.0/48*(Imagedata[i][j][k]+ImageTrans3[i][j][k]-0);
					ImageTrans3[i+1][j][k] = ImageTrans3[i+1][j][k]+7.0/48*(Imagedata[i][j][k]+ImageTrans3[i][j][k]-0);
					ImageTrans3[i+1][j+1][k] = ImageTrans3[i+1][j+1][k]+5.0/48*(Imagedata[i][j][k]+ImageTrans3[i][j][k]-0);
					ImageTrans3[i+1][j+2][k] = ImageTrans3[i+1][j+2][k]+3.0/48*(Imagedata[i][j][k]+ImageTrans3[i][j][k]-0);
					ImageTrans3[i+2][j-2][k] = ImageTrans3[i+2][j-2][k]+1.0/48*(Imagedata[i][j][k]+ImageTrans3[i][j][k]-0);
					ImageTrans3[i+2][j-1][k] = ImageTrans3[i+2][j-1][k]+3.0/48*(Imagedata[i][j][k]+ImageTrans3[i][j][k]-0);
					ImageTrans3[i+2][j][k] = ImageTrans3[i+2][j][k]+5.0/48*(Imagedata[i][j][k]+ImageTrans3[i][j][k]-0);
					ImageTrans3[i+2][j+1][k] = ImageTrans3[i+2][j+1][k]+3.0/48*(Imagedata[i][j][k]+ImageTrans3[i][j][k]-0);
					ImageTrans3[i+2][j+2][k] = ImageTrans3[i+2][j+2][k]+1.0/48*(Imagedata[i][j][k]+ImageTrans3[i][j][k]-0);
					ImageTrans4[i][j][k] = 0;
				}
			}

//T=1/42*[0,0,0,0,0;0,0,0,0,0;0,0,0,8,4;2,4,8,4,2;1,2,4,2,1]
	for(int i=0; i<Width; i++)
		for(int j=0; j<Length; j++)
			for(int k=0; k<BytesPerPixel; k++)
			{
				if((Imagedata[i][j][k]+ImageTrans5[i][j][k])>=128)
				{
					ImageTrans5[i][j+1][k] = ImageTrans5[i][j+1][k]+8.0/42*(Imagedata[i][j][k]+ImageTrans5[i][j][k]-255);
					ImageTrans5[i][j+2][k] = ImageTrans5[i][j+2][k]+4.0/42*(Imagedata[i][j][k]+ImageTrans5[i][j][k]-255);
					ImageTrans5[i+1][j-2][k] = ImageTrans5[i+1][j-2][k]+2.0/42*(Imagedata[i][j][k]+ImageTrans5[i][j][k]-255);
					ImageTrans5[i+1][j-1][k] = ImageTrans5[i+1][j-1][k]+4.0/42*(Imagedata[i][j][k]+ImageTrans5[i][j][k]-255);
					ImageTrans5[i+1][j][k] = ImageTrans5[i+1][j][k]+8.0/42*(Imagedata[i][j][k]+ImageTrans5[i][j][k]-255);
					ImageTrans5[i+1][j+1][k] = ImageTrans5[i+1][j+1][k]+4.0/42*(Imagedata[i][j][k]+ImageTrans5[i][j][k]-255);
					ImageTrans5[i+1][j+2][k] = ImageTrans5[i+1][j+2][k]+2.0/42*(Imagedata[i][j][k]+ImageTrans5[i][j][k]-255);
					ImageTrans5[i+2][j-2][k] = ImageTrans5[i+2][j-2][k]+1.0/42*(Imagedata[i][j][k]+ImageTrans5[i][j][k]-255);
					ImageTrans5[i+2][j-1][k] = ImageTrans5[i+2][j-1][k]+2.0/42*(Imagedata[i][j][k]+ImageTrans5[i][j][k]-255);
					ImageTrans5[i+2][j][k] = ImageTrans5[i+2][j][k]+4.0/42*(Imagedata[i][j][k]+ImageTrans5[i][j][k]-255);
					ImageTrans5[i+2][j+1][k] = ImageTrans5[i+2][j+1][k]+2.0/42*(Imagedata[i][j][k]+ImageTrans5[i][j][k]-255);
					ImageTrans5[i+2][j+2][k] = ImageTrans5[i+2][j+2][k]+1.0/42*(Imagedata[i][j][k]+ImageTrans5[i][j][k]-255);
					ImageTrans6[i][j][k] = 255;
				}
				else
				{
					ImageTrans5[i][j+1][k] = ImageTrans5[i][j+1][k]+8.0/42*(Imagedata[i][j][k]+ImageTrans5[i][j][k]-0);
					ImageTrans5[i][j+2][k] = ImageTrans5[i][j+2][k]+4.0/42*(Imagedata[i][j][k]+ImageTrans5[i][j][k]-0);
					ImageTrans5[i+1][j-2][k] = ImageTrans5[i+1][j-2][k]+2.0/42*(Imagedata[i][j][k]+ImageTrans5[i][j][k]-0);
					ImageTrans5[i+1][j-1][k] = ImageTrans5[i+1][j-1][k]+4.0/42*(Imagedata[i][j][k]+ImageTrans5[i][j][k]-0);
					ImageTrans5[i+1][j][k] = ImageTrans5[i+1][j][k]+8.0/42*(Imagedata[i][j][k]+ImageTrans5[i][j][k]-0);
					ImageTrans5[i+1][j+1][k] = ImageTrans5[i+1][j+1][k]+4.0/42*(Imagedata[i][j][k]+ImageTrans5[i][j][k]-0);
					ImageTrans5[i+1][j+2][k] = ImageTrans5[i+1][j+2][k]+2.0/42*(Imagedata[i][j][k]+ImageTrans5[i][j][k]-0);
					ImageTrans5[i+2][j-2][k] = ImageTrans5[i+2][j-2][k]+1.0/42*(Imagedata[i][j][k]+ImageTrans5[i][j][k]-0);
					ImageTrans5[i+2][j-1][k] = ImageTrans5[i+2][j-1][k]+2.0/42*(Imagedata[i][j][k]+ImageTrans5[i][j][k]-0);
					ImageTrans5[i+2][j][k] = ImageTrans5[i+2][j][k]+4.0/42*(Imagedata[i][j][k]+ImageTrans5[i][j][k]-0);
					ImageTrans5[i+2][j+1][k] = ImageTrans5[i+2][j+1][k]+2.0/42*(Imagedata[i][j][k]+ImageTrans5[i][j][k]-0);
					ImageTrans5[i+2][j+2][k] = ImageTrans5[i+2][j+2][k]+1.0/42*(Imagedata[i][j][k]+ImageTrans5[i][j][k]-0);
					ImageTrans6[i][j][k] = 0;
				}
			}
*/

/*************************************************snake scan**************************************************/
//T=1/16*[0,0,0;0,0,7;3,5,1]
	for(int i=0; i<Width; i++)
		if(i%2)
		{
			for(int j=0; j<Length; j++)
				for(int k=0; k<BytesPerPixel; k++)
				{
					if((Imagedata[i][j][k]+ImageTrans1[i][j][k])>=128)
					{
						ImageTrans1[i][j+1][k] = ImageTrans1[i][j+1][k]+7.0/16*(Imagedata[i][j][k]+ImageTrans1[i][j][k]-255);
						ImageTrans1[i+1][j-1][k] = ImageTrans1[i+1][j-1][k]+3.0/16*(Imagedata[i][j][k]+ImageTrans1[i][j][k]-255);
						ImageTrans1[i+1][j][k] = ImageTrans1[i+1][j][k]+5.0/16*(Imagedata[i][j][k]+ImageTrans1[i][j][k]-255);
						ImageTrans1[i+1][j+1][k] = ImageTrans1[i+1][j+1][k]+1.0/16*(Imagedata[i][j][k]+ImageTrans1[i][j][k]-255);
						ImageTrans2[i][j][k] = 255;
					}
					else
					{
						ImageTrans1[i][j+1][k] = ImageTrans1[i][j+1][k]+7.0/16*(Imagedata[i][j][k]+ImageTrans1[i][j][k]-0);
						ImageTrans1[i+1][j-1][k] = ImageTrans1[i+1][j-1][k]+3.0/16*(Imagedata[i][j][k]+ImageTrans1[i][j][k]-0);
						ImageTrans1[i+1][j][k] = ImageTrans1[i+1][j][k]+5.0/16*(Imagedata[i][j][k]+ImageTrans1[i][j][k]-0);
						ImageTrans1[i+1][j+1][k] = ImageTrans1[i+1][j+1][k]+1.0/16*(Imagedata[i][j][k]+ImageTrans1[i][j][k]-0);
						ImageTrans2[i][j][k] = 0;
					}
				}
		}
		else
		{
			for(int j=Length-1; j>=0; j--)
				for(int k=0; k<BytesPerPixel; k++)
				{
					if((Imagedata[i][j][k]+ImageTrans1[i][j][k])>=128)
					{
						ImageTrans1[i][j+1][k] = ImageTrans1[i][j+1][k]+7.0/16*(Imagedata[i][j][k]+ImageTrans1[i][j][k]-255);
						ImageTrans1[i+1][j-1][k] = ImageTrans1[i+1][j-1][k]+3.0/16*(Imagedata[i][j][k]+ImageTrans1[i][j][k]-255);
						ImageTrans1[i+1][j][k] = ImageTrans1[i+1][j][k]+5.0/16*(Imagedata[i][j][k]+ImageTrans1[i][j][k]-255);
						ImageTrans1[i+1][j+1][k] = ImageTrans1[i+1][j+1][k]+1.0/16*(Imagedata[i][j][k]+ImageTrans1[i][j][k]-255);
						ImageTrans2[i][j][k] = 255;
					}
					else
					{
						ImageTrans1[i][j+1][k] = ImageTrans1[i][j+1][k]+7.0/16*(Imagedata[i][j][k]+ImageTrans1[i][j][k]-0);
						ImageTrans1[i+1][j-1][k] = ImageTrans1[i+1][j-1][k]+3.0/16*(Imagedata[i][j][k]+ImageTrans1[i][j][k]-0);
						ImageTrans1[i+1][j][k] = ImageTrans1[i+1][j][k]+5.0/16*(Imagedata[i][j][k]+ImageTrans1[i][j][k]-0);
						ImageTrans1[i+1][j+1][k] = ImageTrans1[i+1][j+1][k]+1.0/16*(Imagedata[i][j][k]+ImageTrans1[i][j][k]-0);
						ImageTrans2[i][j][k] = 0;
					}
				}
		}

//T=1/48*[0,0,0,0,0;0,0,0,0,0;0,0,0,7,5;3,5,7,5,3;1,3,5,3,1]
	for(int i=0; i<Width; i++)
		if(i%2)
		{
			for(int j=0; j<Length; j++)
				for(int k=0; k<BytesPerPixel; k++)
				{
					if((Imagedata[i][j][k]+ImageTrans3[i][j][k])>=128)
					{
						ImageTrans3[i][j+1][k] = ImageTrans3[i][j+1][k]+7.0/48*(Imagedata[i][j][k]+ImageTrans3[i][j][k]-255);
						ImageTrans3[i][j+2][k] = ImageTrans3[i][j+2][k]+5.0/48*(Imagedata[i][j][k]+ImageTrans3[i][j][k]-255);
						ImageTrans3[i+1][j-2][k] = ImageTrans3[i+1][j-2][k]+3.0/48*(Imagedata[i][j][k]+ImageTrans3[i][j][k]-255);
						ImageTrans3[i+1][j-1][k] = ImageTrans3[i+1][j-1][k]+5.0/48*(Imagedata[i][j][k]+ImageTrans3[i][j][k]-255);
						ImageTrans3[i+1][j][k] = ImageTrans3[i+1][j][k]+7.0/48*(Imagedata[i][j][k]+ImageTrans3[i][j][k]-255);
						ImageTrans3[i+1][j+1][k] = ImageTrans3[i+1][j+1][k]+5.0/48*(Imagedata[i][j][k]+ImageTrans3[i][j][k]-255);
						ImageTrans3[i+1][j+2][k] = ImageTrans3[i+1][j+2][k]+3.0/48*(Imagedata[i][j][k]+ImageTrans3[i][j][k]-255);
						ImageTrans3[i+2][j-2][k] = ImageTrans3[i+2][j-2][k]+1.0/48*(Imagedata[i][j][k]+ImageTrans3[i][j][k]-255);
						ImageTrans3[i+2][j-1][k] = ImageTrans3[i+2][j-1][k]+3.0/48*(Imagedata[i][j][k]+ImageTrans3[i][j][k]-255);
						ImageTrans3[i+2][j][k] = ImageTrans3[i+2][j][k]+5.0/48*(Imagedata[i][j][k]+ImageTrans3[i][j][k]-255);
						ImageTrans3[i+2][j+1][k] = ImageTrans3[i+2][j+1][k]+3.0/48*(Imagedata[i][j][k]+ImageTrans3[i][j][k]-255);
						ImageTrans3[i+2][j+2][k] = ImageTrans3[i+2][j+2][k]+1.0/48*(Imagedata[i][j][k]+ImageTrans3[i][j][k]-255);
						ImageTrans4[i][j][k] = 255;
					}
					else
					{
						ImageTrans3[i][j+1][k] = ImageTrans3[i][j+1][k]+7.0/48*(Imagedata[i][j][k]+ImageTrans3[i][j][k]-0);
						ImageTrans3[i][j+2][k] = ImageTrans3[i][j+2][k]+5.0/48*(Imagedata[i][j][k]+ImageTrans3[i][j][k]-0);
						ImageTrans3[i+1][j-2][k] = ImageTrans3[i+1][j-2][k]+3.0/48*(Imagedata[i][j][k]+ImageTrans3[i][j][k]-0);
						ImageTrans3[i+1][j-1][k] = ImageTrans3[i+1][j-1][k]+5.0/48*(Imagedata[i][j][k]+ImageTrans3[i][j][k]-0);
						ImageTrans3[i+1][j][k] = ImageTrans3[i+1][j][k]+7.0/48*(Imagedata[i][j][k]+ImageTrans3[i][j][k]-0);
						ImageTrans3[i+1][j+1][k] = ImageTrans3[i+1][j+1][k]+5.0/48*(Imagedata[i][j][k]+ImageTrans3[i][j][k]-0);
						ImageTrans3[i+1][j+2][k] = ImageTrans3[i+1][j+2][k]+3.0/48*(Imagedata[i][j][k]+ImageTrans3[i][j][k]-0);
						ImageTrans3[i+2][j-2][k] = ImageTrans3[i+2][j-2][k]+1.0/48*(Imagedata[i][j][k]+ImageTrans3[i][j][k]-0);
						ImageTrans3[i+2][j-1][k] = ImageTrans3[i+2][j-1][k]+3.0/48*(Imagedata[i][j][k]+ImageTrans3[i][j][k]-0);
						ImageTrans3[i+2][j][k] = ImageTrans3[i+2][j][k]+5.0/48*(Imagedata[i][j][k]+ImageTrans3[i][j][k]-0);
						ImageTrans3[i+2][j+1][k] = ImageTrans3[i+2][j+1][k]+3.0/48*(Imagedata[i][j][k]+ImageTrans3[i][j][k]-0);
						ImageTrans3[i+2][j+2][k] = ImageTrans3[i+2][j+2][k]+1.0/48*(Imagedata[i][j][k]+ImageTrans3[i][j][k]-0);
						ImageTrans4[i][j][k] = 0;
					}
				}
		}
		else
		{
			for(int j=Length-1; j>=0; j--)
				for(int k=0; k<BytesPerPixel; k++)
				{
					if((Imagedata[i][j][k]+ImageTrans3[i][j][k])>=128)
					{
						ImageTrans3[i][j+1][k] = ImageTrans3[i][j+1][k]+7.0/48*(Imagedata[i][j][k]+ImageTrans3[i][j][k]-255);
						ImageTrans3[i][j+2][k] = ImageTrans3[i][j+2][k]+5.0/48*(Imagedata[i][j][k]+ImageTrans3[i][j][k]-255);
						ImageTrans3[i+1][j-2][k] = ImageTrans3[i+1][j-2][k]+3.0/48*(Imagedata[i][j][k]+ImageTrans3[i][j][k]-255);
						ImageTrans3[i+1][j-1][k] = ImageTrans3[i+1][j-1][k]+5.0/48*(Imagedata[i][j][k]+ImageTrans3[i][j][k]-255);
						ImageTrans3[i+1][j][k] = ImageTrans3[i+1][j][k]+7.0/48*(Imagedata[i][j][k]+ImageTrans3[i][j][k]-255);
						ImageTrans3[i+1][j+1][k] = ImageTrans3[i+1][j+1][k]+5.0/48*(Imagedata[i][j][k]+ImageTrans3[i][j][k]-255);
						ImageTrans3[i+1][j+2][k] = ImageTrans3[i+1][j+2][k]+3.0/48*(Imagedata[i][j][k]+ImageTrans3[i][j][k]-255);
						ImageTrans3[i+2][j-2][k] = ImageTrans3[i+2][j-2][k]+1.0/48*(Imagedata[i][j][k]+ImageTrans3[i][j][k]-255);
						ImageTrans3[i+2][j-1][k] = ImageTrans3[i+2][j-1][k]+3.0/48*(Imagedata[i][j][k]+ImageTrans3[i][j][k]-255);
						ImageTrans3[i+2][j][k] = ImageTrans3[i+2][j][k]+5.0/48*(Imagedata[i][j][k]+ImageTrans3[i][j][k]-255);
						ImageTrans3[i+2][j+1][k] = ImageTrans3[i+2][j+1][k]+3.0/48*(Imagedata[i][j][k]+ImageTrans3[i][j][k]-255);
						ImageTrans3[i+2][j+2][k] = ImageTrans3[i+2][j+2][k]+1.0/48*(Imagedata[i][j][k]+ImageTrans3[i][j][k]-255);
						ImageTrans4[i][j][k] = 255;
					}
					else
					{
						ImageTrans3[i][j+1][k] = ImageTrans3[i][j+1][k]+7.0/48*(Imagedata[i][j][k]+ImageTrans3[i][j][k]-0);
						ImageTrans3[i][j+2][k] = ImageTrans3[i][j+2][k]+5.0/48*(Imagedata[i][j][k]+ImageTrans3[i][j][k]-0);
						ImageTrans3[i+1][j-2][k] = ImageTrans3[i+1][j-2][k]+3.0/48*(Imagedata[i][j][k]+ImageTrans3[i][j][k]-0);
						ImageTrans3[i+1][j-1][k] = ImageTrans3[i+1][j-1][k]+5.0/48*(Imagedata[i][j][k]+ImageTrans3[i][j][k]-0);
						ImageTrans3[i+1][j][k] = ImageTrans3[i+1][j][k]+7.0/48*(Imagedata[i][j][k]+ImageTrans3[i][j][k]-0);
						ImageTrans3[i+1][j+1][k] = ImageTrans3[i+1][j+1][k]+5.0/48*(Imagedata[i][j][k]+ImageTrans3[i][j][k]-0);
						ImageTrans3[i+1][j+2][k] = ImageTrans3[i+1][j+2][k]+3.0/48*(Imagedata[i][j][k]+ImageTrans3[i][j][k]-0);
						ImageTrans3[i+2][j-2][k] = ImageTrans3[i+2][j-2][k]+1.0/48*(Imagedata[i][j][k]+ImageTrans3[i][j][k]-0);
						ImageTrans3[i+2][j-1][k] = ImageTrans3[i+2][j-1][k]+3.0/48*(Imagedata[i][j][k]+ImageTrans3[i][j][k]-0);
						ImageTrans3[i+2][j][k] = ImageTrans3[i+2][j][k]+5.0/48*(Imagedata[i][j][k]+ImageTrans3[i][j][k]-0);
						ImageTrans3[i+2][j+1][k] = ImageTrans3[i+2][j+1][k]+3.0/48*(Imagedata[i][j][k]+ImageTrans3[i][j][k]-0);
						ImageTrans3[i+2][j+2][k] = ImageTrans3[i+2][j+2][k]+1.0/48*(Imagedata[i][j][k]+ImageTrans3[i][j][k]-0);
						ImageTrans4[i][j][k] = 0;
					}
				}
		}

//T=1/42*[0,0,0,0,0;0,0,0,0,0;0,0,0,8,4;2,4,8,4,2;1,2,4,2,1]
	for(int i=0; i<Width; i++)
		if(i%2)
		{
			for(int j=0; j<Length; j++)
				for(int k=0; k<BytesPerPixel; k++)
				{
					if((Imagedata[i][j][k]+ImageTrans5[i][j][k])>=128)
					{
						ImageTrans5[i][j+1][k] = ImageTrans5[i][j+1][k]+8.0/42*(Imagedata[i][j][k]+ImageTrans5[i][j][k]-255);
						ImageTrans5[i][j+2][k] = ImageTrans5[i][j+2][k]+4.0/42*(Imagedata[i][j][k]+ImageTrans5[i][j][k]-255);
						ImageTrans5[i+1][j-2][k] = ImageTrans5[i+1][j-2][k]+2.0/42*(Imagedata[i][j][k]+ImageTrans5[i][j][k]-255);
						ImageTrans5[i+1][j-1][k] = ImageTrans5[i+1][j-1][k]+4.0/42*(Imagedata[i][j][k]+ImageTrans5[i][j][k]-255);
						ImageTrans5[i+1][j][k] = ImageTrans5[i+1][j][k]+8.0/42*(Imagedata[i][j][k]+ImageTrans5[i][j][k]-255);
						ImageTrans5[i+1][j+1][k] = ImageTrans5[i+1][j+1][k]+4.0/42*(Imagedata[i][j][k]+ImageTrans5[i][j][k]-255);
						ImageTrans5[i+1][j+2][k] = ImageTrans5[i+1][j+2][k]+2.0/42*(Imagedata[i][j][k]+ImageTrans5[i][j][k]-255);
						ImageTrans5[i+2][j-2][k] = ImageTrans5[i+2][j-2][k]+1.0/42*(Imagedata[i][j][k]+ImageTrans5[i][j][k]-255);
						ImageTrans5[i+2][j-1][k] = ImageTrans5[i+2][j-1][k]+2.0/42*(Imagedata[i][j][k]+ImageTrans5[i][j][k]-255);
						ImageTrans5[i+2][j][k] = ImageTrans5[i+2][j][k]+4.0/42*(Imagedata[i][j][k]+ImageTrans5[i][j][k]-255);
						ImageTrans5[i+2][j+1][k] = ImageTrans5[i+2][j+1][k]+2.0/42*(Imagedata[i][j][k]+ImageTrans5[i][j][k]-255);
						ImageTrans5[i+2][j+2][k] = ImageTrans5[i+2][j+2][k]+1.0/42*(Imagedata[i][j][k]+ImageTrans5[i][j][k]-255);
						ImageTrans6[i][j][k] = 255;
					}
					else
					{
						ImageTrans5[i][j+1][k] = ImageTrans5[i][j+1][k]+8.0/42*(Imagedata[i][j][k]+ImageTrans5[i][j][k]-0);
						ImageTrans5[i][j+2][k] = ImageTrans5[i][j+2][k]+4.0/42*(Imagedata[i][j][k]+ImageTrans5[i][j][k]-0);
						ImageTrans5[i+1][j-2][k] = ImageTrans5[i+1][j-2][k]+2.0/42*(Imagedata[i][j][k]+ImageTrans5[i][j][k]-0);
						ImageTrans5[i+1][j-1][k] = ImageTrans5[i+1][j-1][k]+4.0/42*(Imagedata[i][j][k]+ImageTrans5[i][j][k]-0);
						ImageTrans5[i+1][j][k] = ImageTrans5[i+1][j][k]+8.0/42*(Imagedata[i][j][k]+ImageTrans5[i][j][k]-0);
						ImageTrans5[i+1][j+1][k] = ImageTrans5[i+1][j+1][k]+4.0/42*(Imagedata[i][j][k]+ImageTrans5[i][j][k]-0);
						ImageTrans5[i+1][j+2][k] = ImageTrans5[i+1][j+2][k]+2.0/42*(Imagedata[i][j][k]+ImageTrans5[i][j][k]-0);
						ImageTrans5[i+2][j-2][k] = ImageTrans5[i+2][j-2][k]+1.0/42*(Imagedata[i][j][k]+ImageTrans5[i][j][k]-0);
						ImageTrans5[i+2][j-1][k] = ImageTrans5[i+2][j-1][k]+2.0/42*(Imagedata[i][j][k]+ImageTrans5[i][j][k]-0);
						ImageTrans5[i+2][j][k] = ImageTrans5[i+2][j][k]+4.0/42*(Imagedata[i][j][k]+ImageTrans5[i][j][k]-0);
						ImageTrans5[i+2][j+1][k] = ImageTrans5[i+2][j+1][k]+2.0/42*(Imagedata[i][j][k]+ImageTrans5[i][j][k]-0);
						ImageTrans5[i+2][j+2][k] = ImageTrans5[i+2][j+2][k]+1.0/42*(Imagedata[i][j][k]+ImageTrans5[i][j][k]-0);
						ImageTrans6[i][j][k] = 0;
					}
				}
		}
		else
		{
			for(int j=Length-1; j>=0; j--)
				for(int k=0; k<BytesPerPixel; k++)
				{
					if((Imagedata[i][j][k]+ImageTrans5[i][j][k])>=128)
					{
						ImageTrans5[i][j+1][k] = ImageTrans5[i][j+1][k]+8.0/42*(Imagedata[i][j][k]+ImageTrans5[i][j][k]-255);
						ImageTrans5[i][j+2][k] = ImageTrans5[i][j+2][k]+4.0/42*(Imagedata[i][j][k]+ImageTrans5[i][j][k]-255);
						ImageTrans5[i+1][j-2][k] = ImageTrans5[i+1][j-2][k]+2.0/42*(Imagedata[i][j][k]+ImageTrans5[i][j][k]-255);
						ImageTrans5[i+1][j-1][k] = ImageTrans5[i+1][j-1][k]+4.0/42*(Imagedata[i][j][k]+ImageTrans5[i][j][k]-255);
						ImageTrans5[i+1][j][k] = ImageTrans5[i+1][j][k]+8.0/42*(Imagedata[i][j][k]+ImageTrans5[i][j][k]-255);
						ImageTrans5[i+1][j+1][k] = ImageTrans5[i+1][j+1][k]+4.0/42*(Imagedata[i][j][k]+ImageTrans5[i][j][k]-255);
						ImageTrans5[i+1][j+2][k] = ImageTrans5[i+1][j+2][k]+2.0/42*(Imagedata[i][j][k]+ImageTrans5[i][j][k]-255);
						ImageTrans5[i+2][j-2][k] = ImageTrans5[i+2][j-2][k]+1.0/42*(Imagedata[i][j][k]+ImageTrans5[i][j][k]-255);
						ImageTrans5[i+2][j-1][k] = ImageTrans5[i+2][j-1][k]+2.0/42*(Imagedata[i][j][k]+ImageTrans5[i][j][k]-255);
						ImageTrans5[i+2][j][k] = ImageTrans5[i+2][j][k]+4.0/42*(Imagedata[i][j][k]+ImageTrans5[i][j][k]-255);
						ImageTrans5[i+2][j+1][k] = ImageTrans5[i+2][j+1][k]+2.0/42*(Imagedata[i][j][k]+ImageTrans5[i][j][k]-255);
						ImageTrans5[i+2][j+2][k] = ImageTrans5[i+2][j+2][k]+1.0/42*(Imagedata[i][j][k]+ImageTrans5[i][j][k]-255);
						ImageTrans6[i][j][k] = 255;
					}
					else
					{
						ImageTrans5[i][j+1][k] = ImageTrans5[i][j+1][k]+8.0/42*(Imagedata[i][j][k]+ImageTrans5[i][j][k]-0);
						ImageTrans5[i][j+2][k] = ImageTrans5[i][j+2][k]+4.0/42*(Imagedata[i][j][k]+ImageTrans5[i][j][k]-0);
						ImageTrans5[i+1][j-2][k] = ImageTrans5[i+1][j-2][k]+2.0/42*(Imagedata[i][j][k]+ImageTrans5[i][j][k]-0);
						ImageTrans5[i+1][j-1][k] = ImageTrans5[i+1][j-1][k]+4.0/42*(Imagedata[i][j][k]+ImageTrans5[i][j][k]-0);
						ImageTrans5[i+1][j][k] = ImageTrans5[i+1][j][k]+8.0/42*(Imagedata[i][j][k]+ImageTrans5[i][j][k]-0);
						ImageTrans5[i+1][j+1][k] = ImageTrans5[i+1][j+1][k]+4.0/42*(Imagedata[i][j][k]+ImageTrans5[i][j][k]-0);
						ImageTrans5[i+1][j+2][k] = ImageTrans5[i+1][j+2][k]+2.0/42*(Imagedata[i][j][k]+ImageTrans5[i][j][k]-0);
						ImageTrans5[i+2][j-2][k] = ImageTrans5[i+2][j-2][k]+1.0/42*(Imagedata[i][j][k]+ImageTrans5[i][j][k]-0);
						ImageTrans5[i+2][j-1][k] = ImageTrans5[i+2][j-1][k]+2.0/42*(Imagedata[i][j][k]+ImageTrans5[i][j][k]-0);
						ImageTrans5[i+2][j][k] = ImageTrans5[i+2][j][k]+4.0/42*(Imagedata[i][j][k]+ImageTrans5[i][j][k]-0);
						ImageTrans5[i+2][j+1][k] = ImageTrans5[i+2][j+1][k]+2.0/42*(Imagedata[i][j][k]+ImageTrans5[i][j][k]-0);
						ImageTrans5[i+2][j+2][k] = ImageTrans5[i+2][j+2][k]+1.0/42*(Imagedata[i][j][k]+ImageTrans5[i][j][k]-0);
						ImageTrans6[i][j][k] = 0;
					}
				}

		}

	if (!(file=fopen("man_Floyd.raw","wb"))) {
		cout << "Cannot open file: " << "man_Floyd.raw" << endl;
		exit(1);
	}
	fwrite(ImageTrans2, sizeof(unsigned char), Length*Width*BytesPerPixel, file);
	fclose(file);

	if (!(file=fopen("man_JJN.raw","wb"))) {
		cout << "Cannot open file: " << "man_JJN.raw" << endl;
		exit(1);
	}
	fwrite(ImageTrans4, sizeof(unsigned char), Length*Width*BytesPerPixel, file);
	fclose(file);

	if (!(file=fopen("man_Stucki.raw","wb"))) {
		cout << "Cannot open file: " << "man_Stucki.raw" << endl;
		exit(1);
	}
	fwrite(ImageTrans6, sizeof(unsigned char), Length*Width*BytesPerPixel, file);
	fclose(file);

	return 0;
}
