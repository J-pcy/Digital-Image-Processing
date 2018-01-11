/*************************************************************************
 > EE569 Homework Assignment #1
 > Date:     February 4, 2017
 > Author:   Chenyu Peng
 > ID:       3498-8893-91
 > email:    chenyupe@usc.edu

 > Compiled on OS X with gcc
 > Input: ./dog_resizing dog_mirroring.raw 300 300
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

	unsigned char ImageTrans1[200][200][BytesPerPixel];
	unsigned char ImageTrans2[400][400][BytesPerPixel];
	unsigned char ImageTrans3[600][600][BytesPerPixel];

	unsigned char *** ImageTrans;
	ImageTrans = new unsigned char**[1201];
	for(int i=0; i<1201; i++)
	{
		ImageTrans[i] = new unsigned char*[1201];
		for(int j=0; j<1201; j++)
		{
			ImageTrans[i][j] = new unsigned char[3];
		}
	}

	for(int i=0; i<Width; i++)
		for(int j=0; j<Length; j++)
			for(int k=0; k<3; k++)
				ImageTrans[4*i][4*j][k]=Imagedata[i][j][k];

	for(int i=0; i<Width; i++)
	{
		ImageTrans[4*i][1200][0]=ImageTrans[4*i][1196][0];
		ImageTrans[4*i][1200][1]=ImageTrans[4*i][1196][1];
		ImageTrans[4*i][1200][2]=ImageTrans[4*i][1196][2];
	}
	for(int j=0; j<Length+1; j++)
	{
		ImageTrans[1200][4*j][0]=ImageTrans[1196][4*j][0];
		ImageTrans[1200][4*j][1]=ImageTrans[1196][4*j][1];
		ImageTrans[1200][4*j][2]=ImageTrans[1196][4*j][2];
	}

	
	for(int i=0; i<Width; i++)
		for(int j=0; j<Length; j++)
		{
			ImageTrans[4*i][4*j+1][0]=0.75*ImageTrans[4*i][4*j][0]+0.25*ImageTrans[4*i][4*j+4][0];
			ImageTrans[4*i][4*j+1][1]=0.75*ImageTrans[4*i][4*j][1]+0.25*ImageTrans[4*i][4*j+4][1];
			ImageTrans[4*i][4*j+1][2]=0.75*ImageTrans[4*i][4*j][2]+0.25*ImageTrans[4*i][4*j+4][2];

			ImageTrans[4*i][4*j+2][0]=0.5*ImageTrans[4*i][4*j][0]+0.5*ImageTrans[4*i][4*j+4][0];
			ImageTrans[4*i][4*j+2][1]=0.5*ImageTrans[4*i][4*j][1]+0.5*ImageTrans[4*i][4*j+4][1];
			ImageTrans[4*i][4*j+2][2]=0.5*ImageTrans[4*i][4*j][2]+0.5*ImageTrans[4*i][4*j+4][2];

			ImageTrans[4*i][4*j+3][0]=0.25*ImageTrans[4*i][4*j][0]+0.75*ImageTrans[4*i][4*j+4][0];
			ImageTrans[4*i][4*j+3][1]=0.25*ImageTrans[4*i][4*j][1]+0.75*ImageTrans[4*i][4*j+4][1];
			ImageTrans[4*i][4*j+3][2]=0.25*ImageTrans[4*i][4*j][2]+0.75*ImageTrans[4*i][4*j+4][2];

			ImageTrans[4*i+1][4*j][0]=0.75*ImageTrans[4*i][4*j][0]+0.25*ImageTrans[4*i+4][4*j][0];
			ImageTrans[4*i+1][4*j][1]=0.75*ImageTrans[4*i][4*j][1]+0.25*ImageTrans[4*i+4][4*j][1];
			ImageTrans[4*i+1][4*j][2]=0.75*ImageTrans[4*i][4*j][2]+0.25*ImageTrans[4*i+4][4*j][2];

			ImageTrans[4*i+2][4*j][0]=0.5*ImageTrans[4*i][4*j][0]+0.5*ImageTrans[4*i+4][4*j][0];
			ImageTrans[4*i+2][4*j][1]=0.5*ImageTrans[4*i][4*j][1]+0.5*ImageTrans[4*i+4][4*j][1];
			ImageTrans[4*i+2][4*j][2]=0.5*ImageTrans[4*i][4*j][2]+0.5*ImageTrans[4*i+4][4*j][2];

			ImageTrans[4*i+3][4*j][0]=0.25*ImageTrans[4*i][4*j][0]+0.75*ImageTrans[4*i+4][4*j][0];
			ImageTrans[4*i+3][4*j][1]=0.25*ImageTrans[4*i][4*j][1]+0.75*ImageTrans[4*i+4][4*j][1];
			ImageTrans[4*i+3][4*j][2]=0.25*ImageTrans[4*i][4*j][2]+0.75*ImageTrans[4*i+4][4*j][2];

			ImageTrans[4*i+1][4*j+1][0]=0.5625*ImageTrans[4*i][4*j][0]+0.1875*ImageTrans[4*i][4*j+4][0]+0.1875*ImageTrans[4*i+4][4*j][0]+0.0625*ImageTrans[4*i+4][4*j+4][0];
			ImageTrans[4*i+1][4*j+1][1]=0.5625*ImageTrans[4*i][4*j][1]+0.1875*ImageTrans[4*i][4*j+4][1]+0.1875*ImageTrans[4*i+4][4*j][1]+0.0625*ImageTrans[4*i+4][4*j+4][1];
			ImageTrans[4*i+1][4*j+1][2]=0.5625*ImageTrans[4*i][4*j][2]+0.1875*ImageTrans[4*i][4*j+4][2]+0.1875*ImageTrans[4*i+4][4*j][2]+0.0625*ImageTrans[4*i+4][4*j+4][2];

			ImageTrans[4*i+1][4*j+2][0]=0.375*ImageTrans[4*i][4*j][0]+0.375*ImageTrans[4*i][4*j+4][0]+0.125*ImageTrans[4*i+4][4*j][0]+0.125*ImageTrans[4*i+4][4*j+4][0];
			ImageTrans[4*i+1][4*j+2][1]=0.375*ImageTrans[4*i][4*j][1]+0.375*ImageTrans[4*i][4*j+4][1]+0.125*ImageTrans[4*i+4][4*j][1]+0.125*ImageTrans[4*i+4][4*j+4][1];
			ImageTrans[4*i+1][4*j+2][2]=0.375*ImageTrans[4*i][4*j][2]+0.375*ImageTrans[4*i][4*j+4][2]+0.125*ImageTrans[4*i+4][4*j][2]+0.125*ImageTrans[4*i+4][4*j+4][2];

			ImageTrans[4*i+1][4*j+3][0]=0.1875*ImageTrans[4*i][4*j][0]+0.5625*ImageTrans[4*i][4*j+4][0]+0.0625*ImageTrans[4*i+4][4*j][0]+0.1875*ImageTrans[4*i+4][4*j+4][0];
			ImageTrans[4*i+1][4*j+3][1]=0.1875*ImageTrans[4*i][4*j][1]+0.5625*ImageTrans[4*i][4*j+4][1]+0.0625*ImageTrans[4*i+4][4*j][1]+0.1875*ImageTrans[4*i+4][4*j+4][1];
			ImageTrans[4*i+1][4*j+3][2]=0.1875*ImageTrans[4*i][4*j][2]+0.5625*ImageTrans[4*i][4*j+4][2]+0.0625*ImageTrans[4*i+4][4*j][2]+0.1875*ImageTrans[4*i+4][4*j+4][2];

			ImageTrans[4*i+2][4*j+1][0]=0.375*ImageTrans[4*i][4*j][0]+0.125*ImageTrans[4*i][4*j+4][0]+0.375*ImageTrans[4*i+4][4*j][0]+0.125*ImageTrans[4*i+4][4*j+4][0];
			ImageTrans[4*i+2][4*j+1][1]=0.375*ImageTrans[4*i][4*j][1]+0.125*ImageTrans[4*i][4*j+4][1]+0.375*ImageTrans[4*i+4][4*j][1]+0.125*ImageTrans[4*i+4][4*j+4][1];
			ImageTrans[4*i+2][4*j+1][2]=0.375*ImageTrans[4*i][4*j][2]+0.125*ImageTrans[4*i][4*j+4][2]+0.375*ImageTrans[4*i+4][4*j][2]+0.125*ImageTrans[4*i+4][4*j+4][2];

			ImageTrans[4*i+2][4*j+2][0]=0.25*ImageTrans[4*i][4*j][0]+0.25*ImageTrans[4*i][4*j+4][0]+0.25*ImageTrans[4*i+4][4*j][0]+0.25*ImageTrans[4*i+4][4*j+4][0];
			ImageTrans[4*i+2][4*j+2][1]=0.25*ImageTrans[4*i][4*j][1]+0.25*ImageTrans[4*i][4*j+4][1]+0.25*ImageTrans[4*i+4][4*j][1]+0.25*ImageTrans[4*i+4][4*j+4][1];
			ImageTrans[4*i+2][4*j+2][2]=0.25*ImageTrans[4*i][4*j][2]+0.25*ImageTrans[4*i][4*j+4][2]+0.25*ImageTrans[4*i+4][4*j][2]+0.25*ImageTrans[4*i+4][4*j+4][2];

			ImageTrans[4*i+2][4*j+3][0]=0.125*ImageTrans[4*i][4*j][0]+0.375*ImageTrans[4*i][4*j+4][0]+0.125*ImageTrans[4*i+4][4*j][0]+0.375*ImageTrans[4*i+4][4*j+4][0];
			ImageTrans[4*i+2][4*j+3][1]=0.125*ImageTrans[4*i][4*j][1]+0.375*ImageTrans[4*i][4*j+4][1]+0.125*ImageTrans[4*i+4][4*j][1]+0.375*ImageTrans[4*i+4][4*j+4][1];
			ImageTrans[4*i+2][4*j+3][2]=0.125*ImageTrans[4*i][4*j][2]+0.375*ImageTrans[4*i][4*j+4][2]+0.125*ImageTrans[4*i+4][4*j][2]+0.375*ImageTrans[4*i+4][4*j+4][2];

			ImageTrans[4*i+3][4*j+1][0]=0.1875*ImageTrans[4*i][4*j][0]+0.0625*ImageTrans[4*i][4*j+4][0]+0.5625*ImageTrans[4*i+4][4*j][0]+0.1875*ImageTrans[4*i+4][4*j+4][0];
			ImageTrans[4*i+3][4*j+1][1]=0.1875*ImageTrans[4*i][4*j][1]+0.0625*ImageTrans[4*i][4*j+4][1]+0.5625*ImageTrans[4*i+4][4*j][1]+0.1875*ImageTrans[4*i+4][4*j+4][1];
			ImageTrans[4*i+3][4*j+1][2]=0.1875*ImageTrans[4*i][4*j][2]+0.0625*ImageTrans[4*i][4*j+4][2]+0.5625*ImageTrans[4*i+4][4*j][2]+0.1875*ImageTrans[4*i+4][4*j+4][2];

			ImageTrans[4*i+3][4*j+2][0]=0.125*ImageTrans[4*i][4*j][0]+0.125*ImageTrans[4*i][4*j+4][0]+0.375*ImageTrans[4*i+4][4*j][0]+0.375*ImageTrans[4*i+4][4*j+4][0];
			ImageTrans[4*i+3][4*j+2][1]=0.125*ImageTrans[4*i][4*j][1]+0.125*ImageTrans[4*i][4*j+4][1]+0.375*ImageTrans[4*i+4][4*j][1]+0.375*ImageTrans[4*i+4][4*j+4][1];
			ImageTrans[4*i+3][4*j+2][2]=0.125*ImageTrans[4*i][4*j][2]+0.125*ImageTrans[4*i][4*j+4][2]+0.375*ImageTrans[4*i+4][4*j][2]+0.375*ImageTrans[4*i+4][4*j+4][2];

			ImageTrans[4*i+3][4*j+3][0]=0.0625*ImageTrans[4*i][4*j][0]+0.1875*ImageTrans[4*i][4*j+4][0]+0.1875*ImageTrans[4*i+4][4*j][0]+0.5625*ImageTrans[4*i+4][4*j+4][0];
			ImageTrans[4*i+3][4*j+3][1]=0.0625*ImageTrans[4*i][4*j][1]+0.1875*ImageTrans[4*i][4*j+4][1]+0.1875*ImageTrans[4*i+4][4*j][1]+0.5625*ImageTrans[4*i+4][4*j+4][1];
			ImageTrans[4*i+3][4*j+3][2]=0.0625*ImageTrans[4*i][4*j][2]+0.1875*ImageTrans[4*i][4*j+4][2]+0.1875*ImageTrans[4*i+4][4*j][2]+0.5625*ImageTrans[4*i+4][4*j+4][2];
		}
	
	for(int i=0; i<200; i++)
		for(int j=0; j<200; j++)
			for(int k=0; k<3; k++)
				ImageTrans1[i][j][k]= ImageTrans[6*i][6*j][k];

	for(int i=0; i<400; i++)
		for(int j=0; j<400; j++)
			for(int k=0; k<3; k++)
				ImageTrans2[i][j][k]= ImageTrans[3*i][3*j][k];

	for(int i=0; i<600; i++)
		for(int j=0; j<600; j++)
			for(int k=0; k<3; k++)
				ImageTrans3[i][j][k]= ImageTrans[2*i][2*j][k];

	if (!(file=fopen("dog_resizing1.raw","wb"))) {
		cout << "Cannot open file: " << "dog_resizing1.raw" << endl;
		exit(1);
	}
	fwrite(ImageTrans1, sizeof(unsigned char), 200*200*BytesPerPixel, file);
	fclose(file);

	if (!(file=fopen("dog_resizing2.raw","wb"))) {
		cout << "Cannot open file: " << "dog_resizing2.raw" << endl;
		exit(1);
	}
	fwrite(ImageTrans2, sizeof(unsigned char), 400*400*BytesPerPixel, file);
	fclose(file);

	if (!(file=fopen("dog_resizing3.raw","wb"))) {
		cout << "Cannot open file: " << "dog_resizing3.raw" << endl;
		exit(1);
	}
	fwrite(ImageTrans3, sizeof(unsigned char), 600*600*BytesPerPixel, file);
	fclose(file);

	return 0;
}
