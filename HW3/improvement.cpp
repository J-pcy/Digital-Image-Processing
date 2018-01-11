/*************************************************************************
 > EE569 Homework Assignment #3
 > Date:     March 24, 2017
 > Author:   Chenyu Peng
 > ID:       3498-8893-91
 > email:    chenyupe@usc.edu

 > Compiled on OS X with gcc
 > Input: g++ -o 

 ************************************************************************/

#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <cmath>

using namespace std;

int Length = 590;
int Width = 350;
int BytesPerPixel = 3;
	
unsigned char Imagedata[350][590][3];
unsigned char ImageTrans[350][590][3];
unsigned char ImageTrans_old[350][590][3];
unsigned char label[350][590] = {0};

int main(int argc, char *argv[])
{
	FILE *file;	

	if (!(file=fopen("texture_segmentation.raw","rb"))) {
		cout << "Cannot open file: " << "texture_segmentation.raw" <<endl;
		exit(1);
	}
	fread(Imagedata, sizeof(unsigned char), Length*Width*BytesPerPixel, file);
	fclose(file);


	for(int i=0; i<Width; i++)
		for(int j=0; j<Length; j++)
			for(int k=0; k<BytesPerPixel; k++)
				ImageTrans[i][j][k] = Imagedata[i][j][k];

	int start_x =420;
	int start_y =130;

	ImageTrans[start_y][start_x][0] = 255;
	ImageTrans[start_y][start_x][1] = 255;
	ImageTrans[start_y][start_x][2] = 255;

	if(((ImageTrans[start_y-1][start_x][0]!=255)||(ImageTrans[start_y-1][start_x][1]!=255)||(ImageTrans[start_y-1][start_x][2]!=255))&&((ImageTrans[start_y-1][start_x][0]!=255)||(ImageTrans[start_y-1][start_x][1]!=0)||(ImageTrans[start_y-1][start_x][2]!=0)))
	{
		ImageTrans[start_y-1][start_x][0] = 255;
		ImageTrans[start_y-1][start_x][1] = 255;
		ImageTrans[start_y-1][start_x][2] = 255;
		label[start_y-1][start_x] = 1;
	}
	if(((ImageTrans[start_y][start_x-1][0]!=255)||(ImageTrans[start_y][start_x-1][1]!=255)||(ImageTrans[start_y][start_x-1][2]!=255))&&((ImageTrans[start_y][start_x-1][0]!=255)||(ImageTrans[start_y][start_x-1][1]!=0)||(ImageTrans[start_y][start_x-1][2]!=0)))
	{
		ImageTrans[start_y][start_x-1][0] = 255;
		ImageTrans[start_y][start_x-1][1] = 255;
		ImageTrans[start_y][start_x-1][2] = 255;
		label[start_y][start_x-1] = 1;
	}
	if(((ImageTrans[start_y][start_x+1][0]!=255)||(ImageTrans[start_y][start_x+1][1]!=255)||(ImageTrans[start_y][start_x+1][2]!=255))&&((ImageTrans[start_y][start_x+1][0]!=255)||(ImageTrans[start_y][start_x+1][1]!=0)||(ImageTrans[start_y][start_x+1][2]!=0)))
	{
		ImageTrans[start_y][start_x+1][0] = 255;
		ImageTrans[start_y][start_x+1][1] = 255;
		ImageTrans[start_y][start_x+1][2] = 255;
		label[start_y][start_x+1] = 1;
	}
	if(((ImageTrans[start_y+1][start_x][0]!=255)||(ImageTrans[start_y+1][start_x][1]!=255)||(ImageTrans[start_y+1][start_x][2]!=255))&&((ImageTrans[start_y+1][start_x][0]!=255)||(ImageTrans[start_y+1][start_x][1]!=0)||(ImageTrans[start_y+1][start_x][2]!=0)))
	{
		ImageTrans[start_y+1][start_x][0] = 255;
		ImageTrans[start_y+1][start_x][1] = 255;
		ImageTrans[start_y+1][start_x][2] = 255;
		label[start_y+1][start_x] = 1;
	}

	bool break_flag_1 = false;
	while(!break_flag_1)
	{
		for(int i=0; i<Width; i++)
			for(int j=0; j<Length; j++)
				for(int k=0; k<BytesPerPixel; k++)
					ImageTrans_old[i][j][k] = ImageTrans[i][j][k];

		for(int i=0; i<Width; i++)
			for(int j=0; j<Length; j++)
			{
				if(label[i][j]==1)
				{
					if(/*((ImageTrans[i-1][j][0]!=255)||(ImageTrans[i-1][j][1]!=255)||(ImageTrans[i-1][j][2]!=255))&&*/((ImageTrans[i-1][j][0]!=255)||(ImageTrans[i-1][j][1]!=0)||(ImageTrans[i-1][j][2]!=0)))
					{
						ImageTrans[i-1][j][0] = 255;
						ImageTrans[i-1][j][1] = 255;
						ImageTrans[i-1][j][2] = 255;
						label[i-1][j] = 1;
					}
					if(/*((ImageTrans[i][j-1][0]!=255)||(ImageTrans[i][j-1][1]!=255)||(ImageTrans[i][j-1][2]!=255))&&*/((ImageTrans[i][j-1][0]!=255)||(ImageTrans[i][j-1][1]!=0)||(ImageTrans[i][j-1][2]!=0)))
					{
						ImageTrans[i][j-1][0] = 255;
						ImageTrans[i][j-1][1] = 255;
						ImageTrans[i][j-1][2] = 255;
						label[i][j-1] = 1;
					}
					if(/*((ImageTrans[i][j+1][0]!=255)||(ImageTrans[i][j+1][1]!=255)||(ImageTrans[i][j+1][2]!=255))&&*/((ImageTrans[i][j+1][0]!=255)||(ImageTrans[i][j+1][1]!=0)||(ImageTrans[i][j+1][2]!=0)))
					{
						ImageTrans[i][j+1][0] = 255;
						ImageTrans[i][j+1][1] = 255;
						ImageTrans[i][j+1][2] = 255;
						label[i][j+1] = 1;
					}
					if(/*((ImageTrans[i+1][j][0]!=255)||(ImageTrans[i+1][j][1]!=255)||(ImageTrans[i+1][j][2]!=255))&&*/((ImageTrans[i+1][j][0]!=255)||(ImageTrans[i+1][j][1]!=0)||(ImageTrans[i+1][j][2]!=0)))
					{
						ImageTrans[i+1][j][0] = 255;
						ImageTrans[i+1][j][1] = 255;
						ImageTrans[i+1][j][2] = 255;
						label[i+1][j] = 1;
					}
					label[i][j]=0;
				}
			}

		break_flag_1 = true;
		for(int i=0; i<Width&&break_flag_1; i++)
			for(int j=0; j<Length&&break_flag_1; j++)
				for(int k=0; k<BytesPerPixel&&break_flag_1; k++)
				{
					if(ImageTrans[i][j][k]!=ImageTrans_old[i][j][k])
						break_flag_1 = false;
				}
	}





	if (!(file=fopen("improvement.raw","wb"))) {
		cout << "Cannot open file: " << "improvement.raw" << endl;
		exit(1);
	}
	fwrite(ImageTrans, sizeof(unsigned char), 350*590*3, file);
	fclose(file);

	return 0;
}
