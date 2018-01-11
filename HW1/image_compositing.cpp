/*************************************************************************
 > EE569 Homework Assignment #1
 > Date:     February 4, 2017
 > Author:   Chenyu Peng
 > ID:       3498-8893-91
 > email:    chenyupe@usc.edu

 > Compiled on OS X with gcc
 > Input: ./image_compositing dog_mirroring.raw 300 300 beach.raw 1914 808 1100 400
 ************************************************************************/

#include <stdio.h>
#include <iostream>
#include <stdlib.h>

using namespace std;

int main(int argc, char *argv[])

{
	FILE *file;
	int BytesPerPixel = 3;
	int Length_input = 0;
	int Width_input = 0;
	int Length_backg = 0;
	int Width_backg = 0;
	int X_axis = 0;
	int Y_axis = 0;

	if (argc < 7)
	{
		cout << "Syntax Error - Incorrect Parameter Usage:" << endl;
		cout << "program_name input_image.raw Length_input Width_input background_image.raw Length_backg Width_backg [X_axis=0] [Y_axis=Width_backg]" << endl;
		return 0;
	}	
	else
	{
		if(argc <9)
		{
			Length_input = atoi(argv[2]);
			Width_input = atoi(argv[3]);
			Length_backg = atoi(argv[5]);
			Width_backg = atoi(argv[6]);
			if((Length_input>Length_backg)||(Width_input>Width_backg))
				cout << "Input Error - The Size of input_image should smaller than background_image." << endl;
			X_axis = 0;
			Y_axis = Width_backg;
		}
		else
		{
			Length_input = atoi(argv[2]);
			Width_input = atoi(argv[3]);
			Length_backg = atoi(argv[5]);
			Width_backg = atoi(argv[6]);
			if((Length_input>Length_backg)||(Width_input>Width_backg))
			{
				cout << "Input Error - The Size of input_image should be no bigger than background_image." << endl;
				return 0;
			}		
			X_axis = atoi(argv[7]);
			Y_axis = atoi(argv[8]);
			if(((X_axis+Length_input)>Length_backg)||(Y_axis<Width_input)||(Y_axis>Width_backg))
			{
				cout << "Input Error - The Position of input_image should be inside the background_image." << endl;
				return 0;
			}
		}
	}
	
	unsigned char Imagedata_input[Width_input][Length_input][BytesPerPixel];
	unsigned char Imagedata_backg[Width_backg][Length_backg][BytesPerPixel];

	if (!(file=fopen(argv[1],"rb"))) {
		cout << "Cannot open file: " << argv[1] <<endl;
		exit(1);
	}
	fread(Imagedata_input, sizeof(unsigned char), Length_input*Width_input*BytesPerPixel, file);
	fclose(file);

	if (!(file=fopen(argv[4],"rb"))) {
		cout << "Cannot open file: " << argv[4] <<endl;
		exit(1);
	}
	fread(Imagedata_backg, sizeof(unsigned char), Length_backg*Width_backg*BytesPerPixel, file);
	fclose(file);

	for(int i=Width_backg-Y_axis; i<Width_backg-Y_axis+Width_input; i++)
	{
		for(int j=X_axis; j<X_axis+Length_input; j++)
		{
			if((Imagedata_input[i+Y_axis-Width_backg][j-X_axis][0]>1)||(Imagedata_input[i+Y_axis-Width_backg][j-X_axis][1]>1)||(Imagedata_input[i+Y_axis-Width_backg][j-X_axis][2]<254))
			{
				Imagedata_backg[i][j][0] = Imagedata_input[i+Y_axis-Width_backg][j-X_axis][0];
				Imagedata_backg[i][j][1] = Imagedata_input[i+Y_axis-Width_backg][j-X_axis][1];
				Imagedata_backg[i][j][2] = Imagedata_input[i+Y_axis-Width_backg][j-X_axis][2];
//				printf("%u ", Imagedata_input[i+Y_axis-Width_backg][j-X_axis][0]);
			}
		}
//		printf("\n");
	}

	if (!(file=fopen("image_compositing.raw","wb"))) {
		cout << "Cannot open file: " << "image_compositing.raw" << endl;
		exit(1);
	}
	fwrite(Imagedata_backg, sizeof(unsigned char), Length_backg*Width_backg*BytesPerPixel, file);
	fclose(file);

	return 0;
}
