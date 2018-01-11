/*************************************************************************
 > EE569 Homework Assignment #1
 > Date:     February 4, 2017
 > Author:   Chenyu Peng
 > ID:       3498-8893-91
 > email:    chenyupe@usc.edu

 > Compiled on OS X with gcc
 > Input: ./cmy_colorspace parrot.raw 512 384
          ./cmy_colorspace building.raw 789 600
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

	unsigned char ImageTrans[Width][Length][BytesPerPixel];
	for(int i=0; i<Width; i++)
		for(int j=0; j<Length; j++)
			for(int k=0; k<BytesPerPixel; k++)
			{
				if(Imagedata[i][j][k]<0)
					Imagedata[i][j][k] = 0;
				if(Imagedata[i][j][k]>255)
					Imagedata[i][j][k] = 255;
				ImageTrans[i][j][k] = 255 - Imagedata[i][j][k];
			}

	unsigned char ImageTrans_c[Width][Length];
	unsigned char ImageTrans_m[Width][Length];
	unsigned char ImageTrans_y[Width][Length];
	for(int i=0; i<Width; i++)
	{
		for(int j=0; j<Length; j++)
		{
			ImageTrans_c[i][j] = ImageTrans[i][j][0];
			ImageTrans_m[i][j] = ImageTrans[i][j][1];
			ImageTrans_y[i][j] = ImageTrans[i][j][2];
//			printf("%u ", Imagedata[i][j][1]);
		}
//		printf("\n");
	}

	if (!strcmp(argv[1],"parrot.raw"))
	{
		if (!(file=fopen("parrot_cmy.raw","wb"))) {
			cout << "Cannot open file: " << "parrot_cmy.raw" << endl;
			exit(1);
		}
		fwrite(ImageTrans, sizeof(unsigned char), Length*Width*BytesPerPixel, file);
		fclose(file);

		if (!(file=fopen("parrot_c.raw","wb"))) {
			cout << "Cannot open file: " << "parrot_c.raw" << endl;
			exit(1);
		}
		fwrite(ImageTrans_c, sizeof(unsigned char), Length*Width, file);
		fclose(file);

		if (!(file=fopen("parrot_m.raw","wb"))) {
			cout << "Cannot open file: " << "parrot_m.raw" << endl;
			exit(1);
		}
		fwrite(ImageTrans_m, sizeof(unsigned char), Length*Width, file);
		fclose(file);

		if (!(file=fopen("parrot_y.raw","wb"))) {
			cout << "Cannot open file: " << "parrot_y.raw" << endl;
			exit(1);
		}
		fwrite(ImageTrans_y, sizeof(unsigned char), Length*Width, file);
		fclose(file);
	}

	if (!strcmp(argv[1],"building.raw"))
	{
		if (!(file=fopen("building_cmy.raw","wb"))) {
			cout << "Cannot open file: " << "building_cmy.raw" << endl;
			exit(1);
		}
		fwrite(ImageTrans, sizeof(unsigned char), Length*Width*BytesPerPixel, file);
		fclose(file);

		if (!(file=fopen("building_c.raw","wb"))) {
			cout << "Cannot open file: " << "building_c.raw" << endl;
			exit(1);
		}
		fwrite(ImageTrans_c, sizeof(unsigned char), Length*Width, file);
		fclose(file);

		if (!(file=fopen("building_m.raw","wb"))) {
			cout << "Cannot open file: " << "building_m.raw" << endl;
			exit(1);
		}
		fwrite(ImageTrans_m, sizeof(unsigned char), Length*Width, file);
		fclose(file);

		if (!(file=fopen("building_y.raw","wb"))) {
			cout << "Cannot open file: " << "building_y.raw" << endl;
			exit(1);
		}
		fwrite(ImageTrans_y, sizeof(unsigned char), Length*Width, file);
		fclose(file);
	}

	return 0;
}
