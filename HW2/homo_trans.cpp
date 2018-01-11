/*************************************************************************
 > EE569 Homework Assignment #2
 > Date:     February 24, 2017
 > Author:   Chenyu Peng
 > ID:       3498-8893-91
 > email:    chenyupe@usc.edu

 > Compiled on OS X with gcc
 > Input: g++ -o homo_trans homo_trans.cpp
 		  ./homo_trans
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
	int Length1 = 972;  //field.raw
	int Width1 = 648;
	int Length2 = 350;  //tartans.raw
	int Width2 = 146;
	int Length3 = 350;  //trojans.raw
	int Width3 = 197;
	
	unsigned char Imagedata1[Width1][Length1][BytesPerPixel];       //field.raw
	unsigned char Imagedata2[Width2][Length2][BytesPerPixel];       //tartans.raw
	unsigned char Imagedata3[Width3][Length3][BytesPerPixel];       //trojans.raw

	if (!(file=fopen("field.raw","rb"))) {
		cout << "Cannot open file: " << "field.raw" <<endl;
		exit(1);
	}
	fread(Imagedata1, sizeof(unsigned char), Length1*Width1*BytesPerPixel, file);
	fclose(file);

	if (!(file=fopen("tartans.raw","rb"))) {
		cout << "Cannot open file: " << "tartans.raw" <<endl;
		exit(1);
	}
	fread(Imagedata2, sizeof(unsigned char), Length2*Width2*BytesPerPixel, file);
	fclose(file);

	if (!(file=fopen("trojans.raw","rb"))) {
		cout << "Cannot open file: " << "trojans.raw" <<endl;
		exit(1);
	}
	fread(Imagedata3, sizeof(unsigned char), Length3*Width3*BytesPerPixel, file);
	fclose(file);

	unsigned char Imagetrans1[Width1][Length1][BytesPerPixel];
	unsigned char Imagetrans2[Width1][Length1][BytesPerPixel];
	int warping_x=0, warping_y=0;
	double warping_w=0.0;

//h1=[-0.0856,1.1927,-685.9194;-0.8258,-1.0896,915.0333;-0.0001,-0.0037,1]
//w1=[-1.2233,-0.6322,-0.6529,-1.3030]
	for(int i=0; i<Width1; i++)
		for(int j=0; j<Length1; j++)
			for(int k=0; k<BytesPerPixel; k++)
			{
					warping_w = -0.0001*j-0.0037*i+1;
					warping_x = (-0.0856*j+1.1927*i-685.9194)/warping_w;
					warping_y = (-0.8258*j-1.0896*i+915.0333)/warping_w;
					if((warping_x>=0)&&(warping_x<Length2)&&(warping_y>=0)&&(warping_y<Width2))
						Imagetrans1[i][j][k] = Imagedata2[warping_y][warping_x][k];
					else
						Imagetrans1[i][j][k] = 0;
			}
	for(int i=0; i<Width1; i++)
		for(int j=0; j<Length1; j++)
		{
			if((Imagetrans1[i][j][0]==0)&&(Imagetrans1[i][j][1]==0)&&(Imagetrans1[i][j][2]==0))
			{
				Imagetrans1[i][j][0] = Imagedata1[i][j][0];
				Imagetrans1[i][j][1] = Imagedata1[i][j][1];
				Imagetrans1[i][j][2] = Imagedata1[i][j][2];
			}
		}

//h2=[-0.0855,1.1926,-685.9194;-1.1162,-1.4729,1236.8726;-0.0001,-0.0037,1]
//w2=[-1.2233,-0.6322,-0.6528,-1.3030]
	for(int i=0; i<Width3; i++)
		for(int j=0; j<Length3; j++)
		{
			if((Imagedata3[i][j][0]<=255)&&(Imagedata3[i][j][0]>=200)&&(Imagedata3[i][j][1]<=255)&&(Imagedata3[i][j][1]>=200)&&(Imagedata3[i][j][2]<=255)&&(Imagedata3[i][j][2]>=200))
			{
				Imagedata3[i][j][0] = 0;
				Imagedata3[i][j][1] = 0;
				Imagedata3[i][j][2] = 0;
			}
		}
	for(int i=0; i<Width1; i++)
		for(int j=0; j<Length1; j++)
			for(int k=0; k<BytesPerPixel; k++)
			{
					warping_w = -0.0001*j-0.0037*i+1;
					warping_x = (-0.0855*j+1.1926*i-685.9194)/warping_w;
					warping_y = (-1.1162*j-1.4729*i+1236.8726)/warping_w;
					if((warping_x>=0)&&(warping_x<Length3)&&(warping_y>=0)&&(warping_y<Width3))
						Imagetrans2[i][j][k] = Imagedata3[warping_y][warping_x][k];
					else
						Imagetrans2[i][j][k] = 0;
			}
	for(int i=0; i<Width1; i++)
		for(int j=0; j<Length1; j++)
		{
			if((Imagetrans2[i][j][0]==0)&&(Imagetrans2[i][j][1]==0)&&(Imagetrans2[i][j][2]==0))
			{
				Imagetrans2[i][j][0] = Imagedata1[i][j][0];
				Imagetrans2[i][j][1] = Imagedata1[i][j][1];
				Imagetrans2[i][j][2] = Imagedata1[i][j][2];
			}
		}

	if (!(file=fopen("field_tartans.raw","wb"))) {
		cout << "Cannot open file: " << "field_tartans.raw" << endl;
		exit(1);
	}
	fwrite(Imagetrans1, sizeof(unsigned char), Length1*Width1*BytesPerPixel, file);
	fclose(file);

	if (!(file=fopen("field_trojans.raw","wb"))) {
		cout << "Cannot open file: " << "field_trojans.raw" << endl;
		exit(1);
	}
	fwrite(Imagetrans2, sizeof(unsigned char), Length1*Width1*BytesPerPixel, file);
	fclose(file);

	return 0;
}
