/*************************************************************************
 > EE569 Homework Assignment #1
 > Date:     February 4, 2017
 > Author:   Chenyu Peng
 > ID:       3498-8893-91
 > email:    chenyupe@usc.edu

 > Compiled on OS X with gcc
 > Input: ./his_enhanceA_mix tulip_mix.raw 400 366
 ************************************************************************/

#include <stdio.h>
#include <iostream>
#include <stdlib.h>

using namespace std;

int main(int argc, char *argv[])

{
	FILE *file;
	int BytesPerPixel = 1;
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
	
	unsigned char Imagedata[Width][Length];
	unsigned char Imagetrans[Width][Length];

	if (!(file=fopen(argv[1],"rb"))) {
		cout << "Cannot open file: " << argv[1] <<endl;
		exit(1);
	}
	fread(Imagedata, sizeof(unsigned char), Length*Width*BytesPerPixel, file);
	fclose(file);

	int histogram[256] = {0};
	for(int i=0; i<Width; i++)
		for(int j=0; j<Length; j++)
			histogram[Imagedata[i][j]]++;		

	if (!strcmp(argv[1],"tulip_mix.raw"))
	{
		for(int i=0; i<Width; i++)
			for(int j=0; j<Length; j++)
			{
				if(Imagedata[i][j]<=42)
				{
					Imagetrans[i][j] = (255/81)*Imagedata[i][j];
				}
				else if(Imagedata[i][j]>=217)
				{
					Imagetrans[i][j] = (255/81)*(Imagedata[i][j]-217+43);
				}
			}

		if (!(file=fopen("tulip_mix_newA.raw","wb"))) {
			cout << "Cannot open file: " << "tulip_mix_newA.raw" << endl;
			exit(1);
		}
		fwrite(Imagetrans, sizeof(unsigned char), Length*Width*BytesPerPixel, file);
		fclose(file);
	}

	return 0;
}
