/*************************************************************************
 > EE569 Homework Assignment #1
 > Date:     February 4, 2017
 > Author:   Chenyu Peng
 > ID:       3498-8893-91
 > email:    chenyupe@usc.edu

 > Compiled on OS X with gcc
 > Input: ./sepia_filter beach.raw 1914 808
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

	if (!(file=fopen(argv[1],"rb"))) {
		cout << "Cannot open file: " << argv[1] <<endl;
		exit(1);
	}
	fread(Imagedata, sizeof(unsigned char), Length*Width*BytesPerPixel, file);
	fclose(file);

	unsigned char GrayImage[Width][Length];
	unsigned char ImageTrans_sepia[Width][Length][BytesPerPixel];
	
	for(int i=0; i<Width; i++)
	{
		for(int j=0; j<Length; j++)
		{
			if((0.21*Imagedata[i][j][0] + 0.72*Imagedata[i][j][1] + 0.07*Imagedata[i][j][2])<=255)
				GrayImage[i][j] = 0.21*Imagedata[i][j][0] + 0.72*Imagedata[i][j][1] + 0.07*Imagedata[i][j][2];
			else
				GrayImage[i][j] = 255;

			if((0.393*GrayImage[i][j] + 0.769*GrayImage[i][j] + 0.189*GrayImage[i][j])<=255)
				ImageTrans_sepia[i][j][0] = 0.393*GrayImage[i][j] + 0.769*GrayImage[i][j] + 0.189*GrayImage[i][j];
			else
				ImageTrans_sepia[i][j][0] = 255;

			if((0.349*GrayImage[i][j] + 0.686*GrayImage[i][j] + 0.168*GrayImage[i][j])<=255)
				ImageTrans_sepia[i][j][1] = 0.349*GrayImage[i][j] + 0.686*GrayImage[i][j] + 0.168*GrayImage[i][j];
			else
				ImageTrans_sepia[i][j][1] = 255;

			if((0.272*GrayImage[i][j] + 0.534*GrayImage[i][j] + 0.131*GrayImage[i][j])<=255)
				ImageTrans_sepia[i][j][2] = 0.272*GrayImage[i][j] + 0.534*GrayImage[i][j] + 0.131*GrayImage[i][j];
			else
				ImageTrans_sepia[i][j][2] = 255;

//			printf("%u ", C);
		}
//		printf("\n");
	}

	if (!(file=fopen("beach_gray.raw","wb"))) {
		cout << "Cannot open file: " << "beach_gray.raw" << endl;
		exit(1);
	}
	fwrite(GrayImage, sizeof(unsigned char), Length*Width, file);
	fclose(file);

	if (!(file=fopen("beach_sepia.raw","wb"))) {
		cout << "Cannot open file: " << "beach_sepia.raw" << endl;
		exit(1);
	}
	fwrite(ImageTrans_sepia, sizeof(unsigned char), Length*Width*BytesPerPixel, file);
	fclose(file);

	return 0;
}
