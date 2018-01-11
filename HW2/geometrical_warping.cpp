/*************************************************************************
 > EE569 Homework Assignment #2
 > Date:     February 24, 2017
 > Author:   Chenyu Peng
 > ID:       3498-8893-91
 > email:    chenyupe@usc.edu

 > Compiled on OS X with gcc
 > Input: g++ -o geometrical_warping geometrical_warping.cpp
 		  ./geometrical_warping cup1.raw 500 500
 		  ./geometrical_warping cup2.raw 500 500
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

/*******************************************Triangle Transformation*****************************************/
	unsigned char ImageTrans[Width][Length][BytesPerPixel];
	int x=0, y=0;

//t1=[2.0081,-0.0000,-251.0081;1.0000,1.0000,-249.0000;0.0000,0,1.0000]
	for(int i=0; i<250; i++)
		for(int j=i; j<250; j++)
			for(int k=0; k<BytesPerPixel; k++)
			{
				if(((2.0081*j-251.0081)<0)||((2.0081*j-251.0081)>499)||((j+i-249)<0)||((j+i-249)>499))
					ImageTrans[i][j][k] = 0;
				else
				{
					x = 2.0081*j-251.0081;
					y = j+i-249;
					ImageTrans[i][j][k] = Imagedata[y][x][k];
				}
			}
//t2=[2.0081,-0.0000,-252.0161;-1.0000,1.0000,250.0000;0,0.0000,1.0000]
	for(int i=0; i<250; i++)
		for(int j=250; j<500-i; j++)
			for(int k=0; k<BytesPerPixel; k++)
			{
				if(((2.0081*j-252.0161)<0)||((2.0081*j-252.0161)>499)||((-j+i+250)<0)||((-j+i+250)>499))
					ImageTrans[i][j][k] = 0;
				else
				{
					x = 2.0081*j-252.0161;
					y = -j+i+250;
					ImageTrans[i][j][k] = Imagedata[y][x][k];
//					printf("%u,%u\n", x, y);
				}
			}
//t3=[1.0000,-1.0000,249.0000;0.0000,2.0081,-251.0081;0,0,1.0000]
	for(int i=0; i<250; i++)
		for(int j=499-i; j<500; j++)
			for(int k=0; k<BytesPerPixel; k++)
			{
				if(((j-i+249)<0)||((j-i+249)>499)||((2.0081*i-251.0081)<0)||((2.0081*i-251.0081)>499))
					ImageTrans[i][j][k] = 0;
				else
				{
					x = j-i+249;
					y = 2.0081*i-251.0081;
					ImageTrans[i][j][k] = Imagedata[y][x][k];
				}
			}			
//t4=[1.0000,1.0000,-250.0000;0.0000,2.0081,-252.0161;0.0000,0,1.0000]
	for(int i=250; i<500; i++)
		for(int j=500-i; j<500; j++)
			for(int k=0; k<BytesPerPixel; k++)
			{
				if(((j+i-250)<0)||((j+i-250)>499)||((2.0081*i-252.0161)<0)||((2.0081*i-252.0161)>499))
					ImageTrans[i][j][k] = 0;
				else
				{
					x = j+i-250;
					y = 2.0081*i-252.0161;
					ImageTrans[i][j][k] = Imagedata[y][x][k];
				}
			}	
//t5=[2.0081,0.0000,-252.0161;1.0000,1.0000,-250.0000;0,0.0000,1.0000]
	for(int i=250; i<500; i++)
		for(int j=250; j<i+1; j++)
			for(int k=0; k<BytesPerPixel; k++)
			{
				if(((2.0081*j-252.0161)<0)||((2.0081*j-252.0161)>499)||((j+i-250)<0)||((j+i-250)>499))
					ImageTrans[i][j][k] = 0;
				else
				{
					x = 2.0081*j-252.0161;
					y = j+i-250;
					ImageTrans[i][j][k] = Imagedata[y][x][k];
				}
			}	
//t6=[2.0081,-0.0000,-251.0081;-1.0000,1.0000,249.0000;-0.0000,0,1.0000]
	for(int i=250; i<500; i++)
		for(int j=499-i; j<250; j++)
			for(int k=0; k<BytesPerPixel; k++)
			{
				if(((2.0081*j-251.0081)<0)||((2.0081*j-251.0081)>499)||((-j+i+249)<0)||((-j+i+249)>499))
					ImageTrans[i][j][k] = 0;
				else
				{
					x = 2.0081*j-251.0081;
					y = -j+i+249;
					ImageTrans[i][j][k] = Imagedata[y][x][k];
				}
			}	
//t7=[1.0000,-1.0000,250.0000;-0.0000,2.0081,-252.0161;0.0000,0,1.0000]
	for(int i=250; i<500; i++)
		for(int j=0; j<500-i; j++)
			for(int k=0; k<BytesPerPixel; k++)
			{
				if(((j-i+250)<0)||((j-i+250)>499)||((2.0081*i-252.0161)<0)||((2.0081*i-252.0161)>499))
					ImageTrans[i][j][k] = 0;
				else
				{
					x = j-i+250;
					y = 2.0081*i-252.0161;
					ImageTrans[i][j][k] = Imagedata[y][x][k];
				}
			}	
//t8=[1.0000,1.0000,-249.0000;-0.0000,2.0081,-251.0081;0.0000,-0.0000,1.0000]
	for(int i=0; i<250; i++)
		for(int j=0; j<i+1; j++)
			for(int k=0; k<BytesPerPixel; k++)
			{
				if(((j+i-249)<0)||((j+i-249)>499)||((2.0081*i-251.0081)<0)||((2.0081*i-251.0081)>499))
					ImageTrans[i][j][k] = 0;
				else
				{
					x = j+i-249;
					y = 2.0081*i-251.0081;
					ImageTrans[i][j][k] = Imagedata[y][x][k];
				}
			}

/********************************************Merge Method*************************************************/
	unsigned char ImageTrans1[Width][Length][BytesPerPixel];

	for(int i=0; i<250; i++)
		for(int j=249-i; j<250; j++)
			for(int k=0; k<BytesPerPixel; k++)
				ImageTrans1[i][j][k] = Imagedata[i][249-250*(249-j)/(i+1)][k];

	for(int i=0; i<250; i++)
		for(int j=250; j<i+251; j++)
			for(int k=0; k<BytesPerPixel; k++)
				ImageTrans1[i][j][k] = Imagedata[i][250+250*(j-250)/(i+1)][k];

	for(int i=250; i<500; i++)
		for(int j=i-250; j<250; j++)
			for(int k=0; k<BytesPerPixel; k++)
				ImageTrans1[i][j][k] = Imagedata[i][249-250*(249-j)/(500-i)][k];

	for(int i=250; i<500; i++)
		for(int j=250; j<750-i; j++)
			for(int k=0; k<BytesPerPixel; k++)
				ImageTrans1[i][j][k] = Imagedata[i][250+250*(j-250)/(500-i)][k];


	if (!strcmp(argv[1],"cup1.raw"))
	{
		if (!(file=fopen("cup1_warping1.raw","wb"))) {
			cout << "Cannot open file: " << "cup1_warping1.raw" << endl;
			exit(1);
		}
		fwrite(ImageTrans, sizeof(unsigned char), Length*Width*BytesPerPixel, file);
		fclose(file);

		if (!(file=fopen("cup1_warping2.raw","wb"))) {
			cout << "Cannot open file: " << "cup1_warping2.raw" << endl;
			exit(1);
		}
		fwrite(ImageTrans1, sizeof(unsigned char), Length*Width*BytesPerPixel, file);
		fclose(file);
	}
	if (!strcmp(argv[1],"cup2.raw"))
	{
		if (!(file=fopen("cup2_warping1.raw","wb"))) {
			cout << "Cannot open file: " << "cup2_warping1.raw" << endl;
			exit(1);
		}
		fwrite(ImageTrans, sizeof(unsigned char), Length*Width*BytesPerPixel, file);
		fclose(file);

		if (!(file=fopen("cup2_warping2.raw","wb"))) {
			cout << "Cannot open file: " << "cup2_warping2.raw" << endl;
			exit(1);
		}
		fwrite(ImageTrans1, sizeof(unsigned char), Length*Width*BytesPerPixel, file);
		fclose(file);
	}

	return 0;
}
