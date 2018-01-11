/*************************************************************************
 > EE569 Homework Assignment #1
 > Date:     February 4, 2017
 > Author:   Chenyu Peng
 > ID:       3498-8893-91
 > email:    chenyupe@usc.edu

 > Compiled on OS X with gcc
 > Input: ./his_enhanceA tulip_dark.raw 400 366
          ./his_enhanceA tulip_bright.raw 400 366
          ./his_enhanceA tulip_mix.raw 400 366
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

	int sum = 0;
	int lowerlimit=0, upperlimit=0;

	for(int i=0; i<256; i++)
	{
		sum = sum + histogram[i];
		if(((sum-histogram[i])<(0.05*Length*Width))&&(sum>=(0.05*Length*Width)))
		{
			lowerlimit = i;
		}		
		if(((sum-histogram[i])<(0.95*Length*Width))&&(sum>=(0.95*Length*Width)))
		{
			upperlimit = i;
		}	
	}
	for(int i=0; i<Width; i++)
		for(int j=0; j<Length; j++)
		{
			if(Imagedata[i][j]<lowerlimit)
			{
				Imagetrans[i][j] = 0;
			}
			else if(Imagedata[i][j]>upperlimit)
			{
				Imagetrans[i][j] = 255;
			}
			else
			{
				Imagetrans[i][j] = (255/(upperlimit-lowerlimit))*(Imagedata[i][j]-lowerlimit);
			}
		}
			
	if (!strcmp(argv[1],"tulip_bright.raw"))
	{
		if (!(file=fopen("tulip_bright_A.raw","wb"))) {
			cout << "Cannot open file: " << "tulip_bright_A.raw" << endl;
			exit(1);
		}
		fwrite(Imagetrans, sizeof(unsigned char), Length*Width*BytesPerPixel, file);
		fclose(file);
	}

	if (!strcmp(argv[1],"tulip_dark.raw"))
	{
		if (!(file=fopen("tulip_dark_A.raw","wb"))) {
			cout << "Cannot open file: " << "tulip_dark_A.raw" << endl;
			exit(1);
		}
		fwrite(Imagetrans, sizeof(unsigned char), Length*Width*BytesPerPixel, file);
		fclose(file);
	}

	if (!strcmp(argv[1],"tulip_mix.raw"))
	{
		if (!(file=fopen("tulip_mix_A.raw","wb"))) {
			cout << "Cannot open file: " << "tulip_mix_A.raw" << endl;
			exit(1);
		}
		fwrite(Imagetrans, sizeof(unsigned char), Length*Width*BytesPerPixel, file);
		fclose(file);
	}

	return 0;
}
