/*************************************************************************
 > EE569 Homework Assignment #3
 > Date:     March 24, 2017
 > Author:   Chenyu Peng
 > ID:       3498-8893-91
 > email:    chenyupe@usc.edu

 > Compiled on OS X with gcc
 > Input: g++ -o texture_classification texture_classification.cpp
		  ./texture_classification
 ************************************************************************/

#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <cmath>

using namespace std;

char filter_bank[25][5][5] = {{{1,4,6,4,1},{4,16,24,16,4},{6,24,36,24,6},{4,16,24,16,4},{1,4,6,4,1}},
							{{-1,-4,-6,-4,-1},{-2,-8,-12,-8,-2},{0,0,0,0,0},{2,8,12,8,2},{1,4,6,4,1}},
							{{-1,-4,-6,-4,-1},{0,0,0,0,0},{2,8,12,8,2},{0,0,0,0,0},{-1,-4,-6,-4,-1}},
							{{-1,-4,-6,-4,-1},{2,8,12,8,2},{0,0,0,0,0},{-2,-8,-12,-8,-2},{1,4,6,4,1}},
							{{1,4,6,4,1},{-4,-16,-24,-16,-4},{6,24,36,24,6},{-4,-16,-24,-16,-4},{1,4,6,4,1}},

							{{-1,-2,0,2,1},{-4,-8,0,8,4},{-6,-12,0,12,6},{-4,-8,0,8,4},{-1,-2,0,2,1}},
							{{1,2,0,-2,-1},{2,4,0,-4,-2},{0,0,0,0,0},{-2,-4,0,4,2},{-1,-2,0,2,1}},
							{{1,2,0,-2,-1},{0,0,0,0,0},{-2,-4,0,4,2},{0,0,0,0,0},{1,2,0,-2,-1}},
							{{1,2,0,-2,-1},{-2,-4,0,4,2},{0,0,0,0,0},{2,4,0,-4,-2},{-1,-2,0,2,1}},
							{{-1,-2,0,2,1},{4,8,0,-8,-4},{-6,-12,0,12,6},{4,8,0,-8,-4},{-1,-2,0,2,1}},

							{{-1,0,2,0,-1},{-4,0,8,0,-4},{-6,0,12,0,-6},{-4,0,8,0,-4},{-1,0,2,0,-1}},
							{{1,0,-2,0,1},{2,0,-4,0,2},{0,0,0,0,0},{-2,0,4,0,-2},{-1,0,2,0,-1}},
							{{1,0,-2,0,1},{0,0,0,0,0},{-2,0,4,0,-2},{0,0,0,0,0},{1,0,-2,0,1}},
							{{1,0,-2,0,1},{-2,0,4,0,-2},{0,0,0,0,0},{2,0,-4,0,2},{-1,0,2,0,-1}},
							{{-1,0,2,0,-1},{4,0,-8,0,4},{-6,0,12,0,-6},{4,0,-8,0,4},{-1,0,2,0,-1}},

							{{-1,2,0,-2,1},{-4,8,0,-8,4},{-6,12,0,-12,6},{-4,8,0,-8,4},{-1,2,0,-2,1}},
							{{1,-2,0,2,-1},{2,-4,0,4,-2},{0,0,0,0,0},{-2,4,0,-4,2},{-1,2,0,-2,1}},
							{{1,-2,0,2,-1},{0,0,0,0,0},{-2,4,0,-4,2},{0,0,0,0,0},{1,-2,0,2,-1}},
							{{1,-2,0,2,-1},{-2,4,0,-4,2},{0,0,0,0,0},{2,-4,0,4,-2},{-1,2,0,-2,1}},
							{{-1,2,0,-2,1},{4,-8,0,8,-4},{-6,12,0,-12,6},{4,-8,0,8,-4},{-1,2,0,-2,1}},

							{{1,-4,6,-4,1},{4,-16,24,-16,4},{6,-24,36,-24,6},{4,-16,24,-16,4},{1,-4,6,-4,1}},
							{{-1,4,-6,4,-1},{-2,8,-12,8,-2},{0,0,0,0,0},{2,-8,12,-8,2},{1,-4,6,-4,1}},
							{{-1,4,-6,4,-1},{0,0,0,0,0},{2,-8,12,-8,2},{0,0,0,0,0},{-1,4,-6,4,-1}},
							{{-1,4,-6,4,-1},{2,-8,12,-8,2},{0,0,0,0,0},{-2,8,-12,8,-2},{1,-4,6,-4,1}},
							{{1,-4,6,-4,1},{-4,16,-24,16,-4},{6,-24,36,-24,6},{-4,16,-24,16,-4},{1,-4,6,-4,1}}};


int main(int argc, char *argv[])
{
	FILE *file;
	int Length = 128;
	int Width = 128;
	
	unsigned char Imagedata1[Width][Length];
	unsigned char Imagedata2[Width][Length];
	unsigned char Imagedata3[Width][Length];
	unsigned char Imagedata4[Width][Length];
	unsigned char Imagedata5[Width][Length];
	unsigned char Imagedata6[Width][Length];
	unsigned char Imagedata7[Width][Length];
	unsigned char Imagedata8[Width][Length];
	unsigned char Imagedata9[Width][Length];
	unsigned char Imagedata10[Width][Length];
	unsigned char Imagedata11[Width][Length];
	unsigned char Imagedata12[Width][Length];

	unsigned char ImagedataA[Width][Length];
	unsigned char ImagedataB[Width][Length];
	unsigned char ImagedataC[Width][Length];
	unsigned char ImagedataD[Width][Length];
	unsigned char ImagedataE[Width][Length];
	unsigned char ImagedataF[Width][Length];

	if (!(file=fopen("Texture1.raw","rb"))) {
		cout << "Cannot open file: " << "Texture1.raw" <<endl;
		exit(1);
	}
	fread(Imagedata1, sizeof(unsigned char), Length*Width, file);
	fclose(file);

	if (!(file=fopen("Texture2.raw","rb"))) {
		cout << "Cannot open file: " << "Texture2.raw" <<endl;
		exit(1);
	}
	fread(Imagedata2, sizeof(unsigned char), Length*Width, file);
	fclose(file);

	if (!(file=fopen("Texture3.raw","rb"))) {
		cout << "Cannot open file: " << "Texture3.raw" <<endl;
		exit(1);
	}
	fread(Imagedata3, sizeof(unsigned char), Length*Width, file);
	fclose(file);

	if (!(file=fopen("Texture4.raw","rb"))) {
		cout << "Cannot open file: " << "Texture4.raw" <<endl;
		exit(1);
	}
	fread(Imagedata4, sizeof(unsigned char), Length*Width, file);
	fclose(file);

	if (!(file=fopen("Texture5.raw","rb"))) {
		cout << "Cannot open file: " << "Texture5.raw" <<endl;
		exit(1);
	}
	fread(Imagedata5, sizeof(unsigned char), Length*Width, file);
	fclose(file);

	if (!(file=fopen("Texture6.raw","rb"))) {
		cout << "Cannot open file: " << "Texture6.raw" <<endl;
		exit(1);
	}
	fread(Imagedata6, sizeof(unsigned char), Length*Width, file);
	fclose(file);

	if (!(file=fopen("Texture7.raw","rb"))) {
		cout << "Cannot open file: " << "Texture7.raw" <<endl;
		exit(1);
	}
	fread(Imagedata7, sizeof(unsigned char), Length*Width, file);
	fclose(file);

	if (!(file=fopen("Texture8.raw","rb"))) {
		cout << "Cannot open file: " << "Texture8.raw" <<endl;
		exit(1);
	}
	fread(Imagedata8, sizeof(unsigned char), Length*Width, file);
	fclose(file);

	if (!(file=fopen("Texture9.raw","rb"))) {
		cout << "Cannot open file: " << "Texture9.raw" <<endl;
		exit(1);
	}
	fread(Imagedata9, sizeof(unsigned char), Length*Width, file);
	fclose(file);

	if (!(file=fopen("Texture10.raw","rb"))) {
		cout << "Cannot open file: " << "Texture10.raw" <<endl;
		exit(1);
	}
	fread(Imagedata10, sizeof(unsigned char), Length*Width, file);
	fclose(file);

	if (!(file=fopen("Texture11.raw","rb"))) {
		cout << "Cannot open file: " << "Texture11.raw" <<endl;
		exit(1);
	}
	fread(Imagedata11, sizeof(unsigned char), Length*Width, file);
	fclose(file);

	if (!(file=fopen("Texture12.raw","rb"))) {
		cout << "Cannot open file: " << "Texture12.raw" <<endl;
		exit(1);
	}
	fread(Imagedata12, sizeof(unsigned char), Length*Width, file);
	fclose(file);


	if (!(file=fopen("TextureA.raw","rb"))) {
		cout << "Cannot open file: " << "TextureA.raw" <<endl;
		exit(1);
	}
	fread(ImagedataA, sizeof(unsigned char), Length*Width, file);
	fclose(file);

	if (!(file=fopen("TextureB.raw","rb"))) {
		cout << "Cannot open file: " << "TextureB.raw" <<endl;
		exit(1);
	}
	fread(ImagedataB, sizeof(unsigned char), Length*Width, file);
	fclose(file);

	if (!(file=fopen("TextureC.raw","rb"))) {
		cout << "Cannot open file: " << "TextureC.raw" <<endl;
		exit(1);
	}
	fread(ImagedataC, sizeof(unsigned char), Length*Width, file);
	fclose(file);

	if (!(file=fopen("TextureD.raw","rb"))) {
		cout << "Cannot open file: " << "TextureD.raw" <<endl;
		exit(1);
	}
	fread(ImagedataD, sizeof(unsigned char), Length*Width, file);
	fclose(file);

	if (!(file=fopen("TextureE.raw","rb"))) {
		cout << "Cannot open file: " << "TextureE.raw" <<endl;
		exit(1);
	}
	fread(ImagedataE, sizeof(unsigned char), Length*Width, file);
	fclose(file);

	if (!(file=fopen("TextureF.raw","rb"))) {
		cout << "Cannot open file: " << "TextureF.raw" <<endl;
		exit(1);
	}
	fread(ImagedataF, sizeof(unsigned char), Length*Width, file);
	fclose(file);


	double feature_vector[12][25]={0.0};
	double feature_vector_6[6][25]={0.0};
	double kmean_center_old[4][25]={0.0};
	double kmean_center_new[4][25]={0.0};

	double feature_vector3d[12][3]={{3.6739,0.0096,-0.0744},{2.1889,0.1305,-0.0493},{-0.8910,0.0961,-0.0247},
									{-5.5780,0.0307,0.0327},{-5.4875,0.0396,0.0309},{-5.0620,0.0236,0.0387},
									{8.0285,-0.0666,-0.0382},{8.0473,-0.0295,0.0482},{6.9885,0.0106,0.0887},
									{-3.9062,-0.0844,-0.0171},{-4.1417,-0.0782,-0.0113},{-3.8605,-0.0822,-0.0242}};
	double kmean_center_old3d[4][3]={0.0};
	double kmean_center_new3d[4][3]={0.0};

	int ImageTrans1[Width+4][Length+4];
	int ImageTrans2[Width][Length];
	double energy_sum=0;
	double pixel_sum=0;
	int pixel_average=0;

	for(int i=0; i<Width; i++)
		for(int j=0; j<Length; j++)
			pixel_sum = pixel_sum+Imagedata1[i][j];
	pixel_average = pixel_sum/16384;
	pixel_sum = 0;

	for(int i=0; i<Width; i++)
		for(int j=0; j<Length; j++)
			ImageTrans1[i+2][j+2] = Imagedata1[i][j];

	for(int i=0; i<2; i++)
		for(int j=2; j<Length+2; j++)
			ImageTrans1[i][j] = ImageTrans1[2][j];

	for(int i=Width+2; i<Width+4; i++)
		for(int j=2; j<Length+2; j++)
			ImageTrans1[i][j] = ImageTrans1[Width+1][j];

	for(int i=0; i<Width+4; i++)
		for(int j=0; j<2; j++)
			ImageTrans1[i][j] = ImageTrans1[i][2];

	for(int i=0; i<Width+4; i++)
		for(int j=Length+2; j<Length+4; j++)
			ImageTrans1[i][j] = ImageTrans1[i][Length+1];

	for(int i=0; i<Width+4; i++)
		for(int j=0; j<Length+4; j++)
			ImageTrans1[i][j] = ImageTrans1[i][j]-pixel_average;

	for(int k=0; k<25; k++)
	{
		for(int i=0; i<Width; i++)
			for(int j=0; j<Length; j++)
			{
				ImageTrans2[i][j] = filter_bank[k][0][0]*ImageTrans1[i][j]+filter_bank[k][0][1]*ImageTrans1[i][j+1]+filter_bank[k][0][2]*ImageTrans1[i][j+2]+filter_bank[k][0][3]*ImageTrans1[i][j+3]+filter_bank[k][0][4]*ImageTrans1[i][j+4] 
									+ filter_bank[k][1][0]*ImageTrans1[i+1][j]+filter_bank[k][1][1]*ImageTrans1[i+1][j+1]+filter_bank[k][1][2]*ImageTrans1[i+1][j+2]+filter_bank[k][1][3]*ImageTrans1[i+1][j+3]+filter_bank[k][1][4]*ImageTrans1[i+1][j+4]
									+ filter_bank[k][2][0]*ImageTrans1[i+2][j]+filter_bank[k][2][1]*ImageTrans1[i+2][j+1]+filter_bank[k][2][2]*ImageTrans1[i+2][j+2]+filter_bank[k][2][3]*ImageTrans1[i+2][j+3]+filter_bank[k][2][4]*ImageTrans1[i+2][j+4]
									+ filter_bank[k][3][0]*ImageTrans1[i+3][j]+filter_bank[k][3][1]*ImageTrans1[i+3][j+1]+filter_bank[k][3][2]*ImageTrans1[i+3][j+2]+filter_bank[k][3][3]*ImageTrans1[i+3][j+3]+filter_bank[k][3][4]*ImageTrans1[i+3][j+4]
									+ filter_bank[k][4][0]*ImageTrans1[i+4][j]+filter_bank[k][4][1]*ImageTrans1[i+4][j+1]+filter_bank[k][4][2]*ImageTrans1[i+4][j+2]+filter_bank[k][4][3]*ImageTrans1[i+4][j+3]+filter_bank[k][4][4]*ImageTrans1[i+4][j+4];
				energy_sum = energy_sum + ImageTrans2[i][j]*ImageTrans2[i][j];
			}
//		cout << energy_sum << endl;
		feature_vector[0][k] = energy_sum/16384;
		energy_sum = 0;
//		cout << feature_vector[0][k] << endl;
	}
//	printf("%u\n",filter_bank[0][0][0]);
//	cout << feature_vector[0][0] << endl;


	for(int i=0; i<Width; i++)
		for(int j=0; j<Length; j++)
			pixel_sum = pixel_sum+Imagedata2[i][j];
	pixel_average = pixel_sum/16384;
	pixel_sum = 0;

	for(int i=0; i<Width; i++)
		for(int j=0; j<Length; j++)
			ImageTrans1[i+2][j+2] = Imagedata2[i][j];

	for(int i=0; i<2; i++)
		for(int j=2; j<Length+2; j++)
			ImageTrans1[i][j] = ImageTrans1[2][j];

	for(int i=Width+2; i<Width+4; i++)
		for(int j=2; j<Length+2; j++)
			ImageTrans1[i][j] = ImageTrans1[Width+1][j];

	for(int i=0; i<Width+4; i++)
		for(int j=0; j<2; j++)
			ImageTrans1[i][j] = ImageTrans1[i][2];

	for(int i=0; i<Width+4; i++)
		for(int j=Length+2; j<Length+4; j++)
			ImageTrans1[i][j] = ImageTrans1[i][Length+1];

	for(int i=0; i<Width+4; i++)
		for(int j=0; j<Length+4; j++)
			ImageTrans1[i][j] = ImageTrans1[i][j]-pixel_average;

	for(int k=0; k<25; k++)
	{
		for(int i=0; i<Width; i++)
			for(int j=0; j<Length; j++)
			{
				ImageTrans2[i][j] = filter_bank[k][0][0]*ImageTrans1[i][j]+filter_bank[k][0][1]*ImageTrans1[i][j+1]+filter_bank[k][0][2]*ImageTrans1[i][j+2]+filter_bank[k][0][3]*ImageTrans1[i][j+3]+filter_bank[k][0][4]*ImageTrans1[i][j+4] 
									+ filter_bank[k][1][0]*ImageTrans1[i+1][j]+filter_bank[k][1][1]*ImageTrans1[i+1][j+1]+filter_bank[k][1][2]*ImageTrans1[i+1][j+2]+filter_bank[k][1][3]*ImageTrans1[i+1][j+3]+filter_bank[k][1][4]*ImageTrans1[i+1][j+4]
									+ filter_bank[k][2][0]*ImageTrans1[i+2][j]+filter_bank[k][2][1]*ImageTrans1[i+2][j+1]+filter_bank[k][2][2]*ImageTrans1[i+2][j+2]+filter_bank[k][2][3]*ImageTrans1[i+2][j+3]+filter_bank[k][2][4]*ImageTrans1[i+2][j+4]
									+ filter_bank[k][3][0]*ImageTrans1[i+3][j]+filter_bank[k][3][1]*ImageTrans1[i+3][j+1]+filter_bank[k][3][2]*ImageTrans1[i+3][j+2]+filter_bank[k][3][3]*ImageTrans1[i+3][j+3]+filter_bank[k][3][4]*ImageTrans1[i+3][j+4]
									+ filter_bank[k][4][0]*ImageTrans1[i+4][j]+filter_bank[k][4][1]*ImageTrans1[i+4][j+1]+filter_bank[k][4][2]*ImageTrans1[i+4][j+2]+filter_bank[k][4][3]*ImageTrans1[i+4][j+3]+filter_bank[k][4][4]*ImageTrans1[i+4][j+4];
				energy_sum = energy_sum + ImageTrans2[i][j]*ImageTrans2[i][j];
			}
		feature_vector[1][k] = energy_sum/16384;
		energy_sum = 0;
//		cout << feature_vector[1][k] << endl;
	}

	
	for(int i=0; i<Width; i++)
		for(int j=0; j<Length; j++)
			pixel_sum = pixel_sum+Imagedata3[i][j];
	pixel_average = pixel_sum/16384;
	pixel_sum = 0;

	for(int i=0; i<Width; i++)
		for(int j=0; j<Length; j++)
			ImageTrans1[i+2][j+2] = Imagedata3[i][j];

	for(int i=0; i<2; i++)
		for(int j=2; j<Length+2; j++)
			ImageTrans1[i][j] = ImageTrans1[2][j];

	for(int i=Width+2; i<Width+4; i++)
		for(int j=2; j<Length+2; j++)
			ImageTrans1[i][j] = ImageTrans1[Width+1][j];

	for(int i=0; i<Width+4; i++)
		for(int j=0; j<2; j++)
			ImageTrans1[i][j] = ImageTrans1[i][2];

	for(int i=0; i<Width+4; i++)
		for(int j=Length+2; j<Length+4; j++)
			ImageTrans1[i][j] = ImageTrans1[i][Length+1];

	for(int i=0; i<Width+4; i++)
		for(int j=0; j<Length+4; j++)
			ImageTrans1[i][j] = ImageTrans1[i][j]-pixel_average;

	for(int k=0; k<25; k++)
	{
		for(int i=0; i<Width; i++)
			for(int j=0; j<Length; j++)
			{
				ImageTrans2[i][j] = filter_bank[k][0][0]*ImageTrans1[i][j]+filter_bank[k][0][1]*ImageTrans1[i][j+1]+filter_bank[k][0][2]*ImageTrans1[i][j+2]+filter_bank[k][0][3]*ImageTrans1[i][j+3]+filter_bank[k][0][4]*ImageTrans1[i][j+4] 
									+ filter_bank[k][1][0]*ImageTrans1[i+1][j]+filter_bank[k][1][1]*ImageTrans1[i+1][j+1]+filter_bank[k][1][2]*ImageTrans1[i+1][j+2]+filter_bank[k][1][3]*ImageTrans1[i+1][j+3]+filter_bank[k][1][4]*ImageTrans1[i+1][j+4]
									+ filter_bank[k][2][0]*ImageTrans1[i+2][j]+filter_bank[k][2][1]*ImageTrans1[i+2][j+1]+filter_bank[k][2][2]*ImageTrans1[i+2][j+2]+filter_bank[k][2][3]*ImageTrans1[i+2][j+3]+filter_bank[k][2][4]*ImageTrans1[i+2][j+4]
									+ filter_bank[k][3][0]*ImageTrans1[i+3][j]+filter_bank[k][3][1]*ImageTrans1[i+3][j+1]+filter_bank[k][3][2]*ImageTrans1[i+3][j+2]+filter_bank[k][3][3]*ImageTrans1[i+3][j+3]+filter_bank[k][3][4]*ImageTrans1[i+3][j+4]
									+ filter_bank[k][4][0]*ImageTrans1[i+4][j]+filter_bank[k][4][1]*ImageTrans1[i+4][j+1]+filter_bank[k][4][2]*ImageTrans1[i+4][j+2]+filter_bank[k][4][3]*ImageTrans1[i+4][j+3]+filter_bank[k][4][4]*ImageTrans1[i+4][j+4];
				energy_sum = energy_sum + ImageTrans2[i][j]*ImageTrans2[i][j];
			}
		feature_vector[2][k] = energy_sum/16384;
		energy_sum = 0;
//		cout << feature_vector[2][k] << endl;
	}


	for(int i=0; i<Width; i++)
		for(int j=0; j<Length; j++)
			pixel_sum = pixel_sum+Imagedata4[i][j];
	pixel_average = pixel_sum/16384;
	pixel_sum = 0;

	for(int i=0; i<Width; i++)
		for(int j=0; j<Length; j++)
			ImageTrans1[i+2][j+2] = Imagedata4[i][j];

	for(int i=0; i<2; i++)
		for(int j=2; j<Length+2; j++)
			ImageTrans1[i][j] = ImageTrans1[2][j];

	for(int i=Width+2; i<Width+4; i++)
		for(int j=2; j<Length+2; j++)
			ImageTrans1[i][j] = ImageTrans1[Width+1][j];

	for(int i=0; i<Width+4; i++)
		for(int j=0; j<2; j++)
			ImageTrans1[i][j] = ImageTrans1[i][2];

	for(int i=0; i<Width+4; i++)
		for(int j=Length+2; j<Length+4; j++)
			ImageTrans1[i][j] = ImageTrans1[i][Length+1];

	for(int i=0; i<Width+4; i++)
		for(int j=0; j<Length+4; j++)
			ImageTrans1[i][j] = ImageTrans1[i][j]-pixel_average;

	for(int k=0; k<25; k++)
	{
		for(int i=0; i<Width; i++)
			for(int j=0; j<Length; j++)
			{
				ImageTrans2[i][j] = filter_bank[k][0][0]*ImageTrans1[i][j]+filter_bank[k][0][1]*ImageTrans1[i][j+1]+filter_bank[k][0][2]*ImageTrans1[i][j+2]+filter_bank[k][0][3]*ImageTrans1[i][j+3]+filter_bank[k][0][4]*ImageTrans1[i][j+4] 
									+ filter_bank[k][1][0]*ImageTrans1[i+1][j]+filter_bank[k][1][1]*ImageTrans1[i+1][j+1]+filter_bank[k][1][2]*ImageTrans1[i+1][j+2]+filter_bank[k][1][3]*ImageTrans1[i+1][j+3]+filter_bank[k][1][4]*ImageTrans1[i+1][j+4]
									+ filter_bank[k][2][0]*ImageTrans1[i+2][j]+filter_bank[k][2][1]*ImageTrans1[i+2][j+1]+filter_bank[k][2][2]*ImageTrans1[i+2][j+2]+filter_bank[k][2][3]*ImageTrans1[i+2][j+3]+filter_bank[k][2][4]*ImageTrans1[i+2][j+4]
									+ filter_bank[k][3][0]*ImageTrans1[i+3][j]+filter_bank[k][3][1]*ImageTrans1[i+3][j+1]+filter_bank[k][3][2]*ImageTrans1[i+3][j+2]+filter_bank[k][3][3]*ImageTrans1[i+3][j+3]+filter_bank[k][3][4]*ImageTrans1[i+3][j+4]
									+ filter_bank[k][4][0]*ImageTrans1[i+4][j]+filter_bank[k][4][1]*ImageTrans1[i+4][j+1]+filter_bank[k][4][2]*ImageTrans1[i+4][j+2]+filter_bank[k][4][3]*ImageTrans1[i+4][j+3]+filter_bank[k][4][4]*ImageTrans1[i+4][j+4];
				energy_sum = energy_sum + ImageTrans2[i][j]*ImageTrans2[i][j];
			}
		feature_vector[3][k] = energy_sum/16384;
		energy_sum = 0;
//		cout << feature_vector[3][k] << endl;
	}


	for(int i=0; i<Width; i++)
		for(int j=0; j<Length; j++)
			pixel_sum = pixel_sum+Imagedata5[i][j];
	pixel_average = pixel_sum/16384;
	pixel_sum = 0;

	for(int i=0; i<Width; i++)
		for(int j=0; j<Length; j++)
			ImageTrans1[i+2][j+2] = Imagedata5[i][j];

	for(int i=0; i<2; i++)
		for(int j=2; j<Length+2; j++)
			ImageTrans1[i][j] = ImageTrans1[2][j];

	for(int i=Width+2; i<Width+4; i++)
		for(int j=2; j<Length+2; j++)
			ImageTrans1[i][j] = ImageTrans1[Width+1][j];

	for(int i=0; i<Width+4; i++)
		for(int j=0; j<2; j++)
			ImageTrans1[i][j] = ImageTrans1[i][2];

	for(int i=0; i<Width+4; i++)
		for(int j=Length+2; j<Length+4; j++)
			ImageTrans1[i][j] = ImageTrans1[i][Length+1];

	for(int i=0; i<Width+4; i++)
		for(int j=0; j<Length+4; j++)
			ImageTrans1[i][j] = ImageTrans1[i][j]-pixel_average;

	for(int k=0; k<25; k++)
	{
		for(int i=0; i<Width; i++)
			for(int j=0; j<Length; j++)
			{
				ImageTrans2[i][j] = filter_bank[k][0][0]*ImageTrans1[i][j]+filter_bank[k][0][1]*ImageTrans1[i][j+1]+filter_bank[k][0][2]*ImageTrans1[i][j+2]+filter_bank[k][0][3]*ImageTrans1[i][j+3]+filter_bank[k][0][4]*ImageTrans1[i][j+4] 
									+ filter_bank[k][1][0]*ImageTrans1[i+1][j]+filter_bank[k][1][1]*ImageTrans1[i+1][j+1]+filter_bank[k][1][2]*ImageTrans1[i+1][j+2]+filter_bank[k][1][3]*ImageTrans1[i+1][j+3]+filter_bank[k][1][4]*ImageTrans1[i+1][j+4]
									+ filter_bank[k][2][0]*ImageTrans1[i+2][j]+filter_bank[k][2][1]*ImageTrans1[i+2][j+1]+filter_bank[k][2][2]*ImageTrans1[i+2][j+2]+filter_bank[k][2][3]*ImageTrans1[i+2][j+3]+filter_bank[k][2][4]*ImageTrans1[i+2][j+4]
									+ filter_bank[k][3][0]*ImageTrans1[i+3][j]+filter_bank[k][3][1]*ImageTrans1[i+3][j+1]+filter_bank[k][3][2]*ImageTrans1[i+3][j+2]+filter_bank[k][3][3]*ImageTrans1[i+3][j+3]+filter_bank[k][3][4]*ImageTrans1[i+3][j+4]
									+ filter_bank[k][4][0]*ImageTrans1[i+4][j]+filter_bank[k][4][1]*ImageTrans1[i+4][j+1]+filter_bank[k][4][2]*ImageTrans1[i+4][j+2]+filter_bank[k][4][3]*ImageTrans1[i+4][j+3]+filter_bank[k][4][4]*ImageTrans1[i+4][j+4];
				energy_sum = energy_sum + ImageTrans2[i][j]*ImageTrans2[i][j];
			}
		feature_vector[4][k] = energy_sum/16384;
		energy_sum = 0;
//		cout << feature_vector[4][k] << endl;
	}


	for(int i=0; i<Width; i++)
		for(int j=0; j<Length; j++)
			pixel_sum = pixel_sum+Imagedata6[i][j];
	pixel_average = pixel_sum/16384;
	pixel_sum = 0;

	for(int i=0; i<Width; i++)
		for(int j=0; j<Length; j++)
			ImageTrans1[i+2][j+2] = Imagedata6[i][j];

	for(int i=0; i<2; i++)
		for(int j=2; j<Length+2; j++)
			ImageTrans1[i][j] = ImageTrans1[2][j];

	for(int i=Width+2; i<Width+4; i++)
		for(int j=2; j<Length+2; j++)
			ImageTrans1[i][j] = ImageTrans1[Width+1][j];

	for(int i=0; i<Width+4; i++)
		for(int j=0; j<2; j++)
			ImageTrans1[i][j] = ImageTrans1[i][2];

	for(int i=0; i<Width+4; i++)
		for(int j=Length+2; j<Length+4; j++)
			ImageTrans1[i][j] = ImageTrans1[i][Length+1];

	for(int i=0; i<Width+4; i++)
		for(int j=0; j<Length+4; j++)
			ImageTrans1[i][j] = ImageTrans1[i][j]-pixel_average;

	for(int k=0; k<25; k++)
	{
		for(int i=0; i<Width; i++)
			for(int j=0; j<Length; j++)
			{
				ImageTrans2[i][j] = filter_bank[k][0][0]*ImageTrans1[i][j]+filter_bank[k][0][1]*ImageTrans1[i][j+1]+filter_bank[k][0][2]*ImageTrans1[i][j+2]+filter_bank[k][0][3]*ImageTrans1[i][j+3]+filter_bank[k][0][4]*ImageTrans1[i][j+4] 
									+ filter_bank[k][1][0]*ImageTrans1[i+1][j]+filter_bank[k][1][1]*ImageTrans1[i+1][j+1]+filter_bank[k][1][2]*ImageTrans1[i+1][j+2]+filter_bank[k][1][3]*ImageTrans1[i+1][j+3]+filter_bank[k][1][4]*ImageTrans1[i+1][j+4]
									+ filter_bank[k][2][0]*ImageTrans1[i+2][j]+filter_bank[k][2][1]*ImageTrans1[i+2][j+1]+filter_bank[k][2][2]*ImageTrans1[i+2][j+2]+filter_bank[k][2][3]*ImageTrans1[i+2][j+3]+filter_bank[k][2][4]*ImageTrans1[i+2][j+4]
									+ filter_bank[k][3][0]*ImageTrans1[i+3][j]+filter_bank[k][3][1]*ImageTrans1[i+3][j+1]+filter_bank[k][3][2]*ImageTrans1[i+3][j+2]+filter_bank[k][3][3]*ImageTrans1[i+3][j+3]+filter_bank[k][3][4]*ImageTrans1[i+3][j+4]
									+ filter_bank[k][4][0]*ImageTrans1[i+4][j]+filter_bank[k][4][1]*ImageTrans1[i+4][j+1]+filter_bank[k][4][2]*ImageTrans1[i+4][j+2]+filter_bank[k][4][3]*ImageTrans1[i+4][j+3]+filter_bank[k][4][4]*ImageTrans1[i+4][j+4];
				energy_sum = energy_sum + ImageTrans2[i][j]*ImageTrans2[i][j];
			}
		feature_vector[5][k] = energy_sum/16384;
		energy_sum = 0;
//		cout << feature_vector[5][k] << endl;
	}


	for(int i=0; i<Width; i++)
		for(int j=0; j<Length; j++)
			pixel_sum = pixel_sum+Imagedata7[i][j];
	pixel_average = pixel_sum/16384;
	pixel_sum = 0;

	for(int i=0; i<Width; i++)
		for(int j=0; j<Length; j++)
			ImageTrans1[i+2][j+2] = Imagedata7[i][j];

	for(int i=0; i<2; i++)
		for(int j=2; j<Length+2; j++)
			ImageTrans1[i][j] = ImageTrans1[2][j];

	for(int i=Width+2; i<Width+4; i++)
		for(int j=2; j<Length+2; j++)
			ImageTrans1[i][j] = ImageTrans1[Width+1][j];

	for(int i=0; i<Width+4; i++)
		for(int j=0; j<2; j++)
			ImageTrans1[i][j] = ImageTrans1[i][2];

	for(int i=0; i<Width+4; i++)
		for(int j=Length+2; j<Length+4; j++)
			ImageTrans1[i][j] = ImageTrans1[i][Length+1];

	for(int i=0; i<Width+4; i++)
		for(int j=0; j<Length+4; j++)
			ImageTrans1[i][j] = ImageTrans1[i][j]-pixel_average;

	for(int k=0; k<25; k++)
	{
		for(int i=0; i<Width; i++)
			for(int j=0; j<Length; j++)
			{
				ImageTrans2[i][j] = filter_bank[k][0][0]*ImageTrans1[i][j]+filter_bank[k][0][1]*ImageTrans1[i][j+1]+filter_bank[k][0][2]*ImageTrans1[i][j+2]+filter_bank[k][0][3]*ImageTrans1[i][j+3]+filter_bank[k][0][4]*ImageTrans1[i][j+4] 
									+ filter_bank[k][1][0]*ImageTrans1[i+1][j]+filter_bank[k][1][1]*ImageTrans1[i+1][j+1]+filter_bank[k][1][2]*ImageTrans1[i+1][j+2]+filter_bank[k][1][3]*ImageTrans1[i+1][j+3]+filter_bank[k][1][4]*ImageTrans1[i+1][j+4]
									+ filter_bank[k][2][0]*ImageTrans1[i+2][j]+filter_bank[k][2][1]*ImageTrans1[i+2][j+1]+filter_bank[k][2][2]*ImageTrans1[i+2][j+2]+filter_bank[k][2][3]*ImageTrans1[i+2][j+3]+filter_bank[k][2][4]*ImageTrans1[i+2][j+4]
									+ filter_bank[k][3][0]*ImageTrans1[i+3][j]+filter_bank[k][3][1]*ImageTrans1[i+3][j+1]+filter_bank[k][3][2]*ImageTrans1[i+3][j+2]+filter_bank[k][3][3]*ImageTrans1[i+3][j+3]+filter_bank[k][3][4]*ImageTrans1[i+3][j+4]
									+ filter_bank[k][4][0]*ImageTrans1[i+4][j]+filter_bank[k][4][1]*ImageTrans1[i+4][j+1]+filter_bank[k][4][2]*ImageTrans1[i+4][j+2]+filter_bank[k][4][3]*ImageTrans1[i+4][j+3]+filter_bank[k][4][4]*ImageTrans1[i+4][j+4];
				energy_sum = energy_sum + ImageTrans2[i][j]*ImageTrans2[i][j];
			}
		feature_vector[6][k] = energy_sum/16384;
		energy_sum = 0;
//		cout << feature_vector[6][k] << endl;
	}


	for(int i=0; i<Width; i++)
		for(int j=0; j<Length; j++)
			pixel_sum = pixel_sum+Imagedata8[i][j];
	pixel_average = pixel_sum/16384;
	pixel_sum = 0;

	for(int i=0; i<Width; i++)
		for(int j=0; j<Length; j++)
			ImageTrans1[i+2][j+2] = Imagedata8[i][j];

	for(int i=0; i<2; i++)
		for(int j=2; j<Length+2; j++)
			ImageTrans1[i][j] = ImageTrans1[2][j];

	for(int i=Width+2; i<Width+4; i++)
		for(int j=2; j<Length+2; j++)
			ImageTrans1[i][j] = ImageTrans1[Width+1][j];

	for(int i=0; i<Width+4; i++)
		for(int j=0; j<2; j++)
			ImageTrans1[i][j] = ImageTrans1[i][2];

	for(int i=0; i<Width+4; i++)
		for(int j=Length+2; j<Length+4; j++)
			ImageTrans1[i][j] = ImageTrans1[i][Length+1];

	for(int i=0; i<Width+4; i++)
		for(int j=0; j<Length+4; j++)
			ImageTrans1[i][j] = ImageTrans1[i][j]-pixel_average;

	for(int k=0; k<25; k++)
	{
		for(int i=0; i<Width; i++)
			for(int j=0; j<Length; j++)
			{
				ImageTrans2[i][j] = filter_bank[k][0][0]*ImageTrans1[i][j]+filter_bank[k][0][1]*ImageTrans1[i][j+1]+filter_bank[k][0][2]*ImageTrans1[i][j+2]+filter_bank[k][0][3]*ImageTrans1[i][j+3]+filter_bank[k][0][4]*ImageTrans1[i][j+4] 
									+ filter_bank[k][1][0]*ImageTrans1[i+1][j]+filter_bank[k][1][1]*ImageTrans1[i+1][j+1]+filter_bank[k][1][2]*ImageTrans1[i+1][j+2]+filter_bank[k][1][3]*ImageTrans1[i+1][j+3]+filter_bank[k][1][4]*ImageTrans1[i+1][j+4]
									+ filter_bank[k][2][0]*ImageTrans1[i+2][j]+filter_bank[k][2][1]*ImageTrans1[i+2][j+1]+filter_bank[k][2][2]*ImageTrans1[i+2][j+2]+filter_bank[k][2][3]*ImageTrans1[i+2][j+3]+filter_bank[k][2][4]*ImageTrans1[i+2][j+4]
									+ filter_bank[k][3][0]*ImageTrans1[i+3][j]+filter_bank[k][3][1]*ImageTrans1[i+3][j+1]+filter_bank[k][3][2]*ImageTrans1[i+3][j+2]+filter_bank[k][3][3]*ImageTrans1[i+3][j+3]+filter_bank[k][3][4]*ImageTrans1[i+3][j+4]
									+ filter_bank[k][4][0]*ImageTrans1[i+4][j]+filter_bank[k][4][1]*ImageTrans1[i+4][j+1]+filter_bank[k][4][2]*ImageTrans1[i+4][j+2]+filter_bank[k][4][3]*ImageTrans1[i+4][j+3]+filter_bank[k][4][4]*ImageTrans1[i+4][j+4];
				energy_sum = energy_sum + ImageTrans2[i][j]*ImageTrans2[i][j];
			}
		feature_vector[7][k] = energy_sum/16384;
		energy_sum = 0;
//		cout << feature_vector[7][k] << endl;
	}


	for(int i=0; i<Width; i++)
		for(int j=0; j<Length; j++)
			pixel_sum = pixel_sum+Imagedata9[i][j];
	pixel_average = pixel_sum/16384;
	pixel_sum = 0;

	for(int i=0; i<Width; i++)
		for(int j=0; j<Length; j++)
			ImageTrans1[i+2][j+2] = Imagedata9[i][j];

	for(int i=0; i<2; i++)
		for(int j=2; j<Length+2; j++)
			ImageTrans1[i][j] = ImageTrans1[2][j];

	for(int i=Width+2; i<Width+4; i++)
		for(int j=2; j<Length+2; j++)
			ImageTrans1[i][j] = ImageTrans1[Width+1][j];

	for(int i=0; i<Width+4; i++)
		for(int j=0; j<2; j++)
			ImageTrans1[i][j] = ImageTrans1[i][2];

	for(int i=0; i<Width+4; i++)
		for(int j=Length+2; j<Length+4; j++)
			ImageTrans1[i][j] = ImageTrans1[i][Length+1];

	for(int i=0; i<Width+4; i++)
		for(int j=0; j<Length+4; j++)
			ImageTrans1[i][j] = ImageTrans1[i][j]-pixel_average;

	for(int k=0; k<25; k++)
	{
		for(int i=0; i<Width; i++)
			for(int j=0; j<Length; j++)
			{
				ImageTrans2[i][j] = filter_bank[k][0][0]*ImageTrans1[i][j]+filter_bank[k][0][1]*ImageTrans1[i][j+1]+filter_bank[k][0][2]*ImageTrans1[i][j+2]+filter_bank[k][0][3]*ImageTrans1[i][j+3]+filter_bank[k][0][4]*ImageTrans1[i][j+4] 
									+ filter_bank[k][1][0]*ImageTrans1[i+1][j]+filter_bank[k][1][1]*ImageTrans1[i+1][j+1]+filter_bank[k][1][2]*ImageTrans1[i+1][j+2]+filter_bank[k][1][3]*ImageTrans1[i+1][j+3]+filter_bank[k][1][4]*ImageTrans1[i+1][j+4]
									+ filter_bank[k][2][0]*ImageTrans1[i+2][j]+filter_bank[k][2][1]*ImageTrans1[i+2][j+1]+filter_bank[k][2][2]*ImageTrans1[i+2][j+2]+filter_bank[k][2][3]*ImageTrans1[i+2][j+3]+filter_bank[k][2][4]*ImageTrans1[i+2][j+4]
									+ filter_bank[k][3][0]*ImageTrans1[i+3][j]+filter_bank[k][3][1]*ImageTrans1[i+3][j+1]+filter_bank[k][3][2]*ImageTrans1[i+3][j+2]+filter_bank[k][3][3]*ImageTrans1[i+3][j+3]+filter_bank[k][3][4]*ImageTrans1[i+3][j+4]
									+ filter_bank[k][4][0]*ImageTrans1[i+4][j]+filter_bank[k][4][1]*ImageTrans1[i+4][j+1]+filter_bank[k][4][2]*ImageTrans1[i+4][j+2]+filter_bank[k][4][3]*ImageTrans1[i+4][j+3]+filter_bank[k][4][4]*ImageTrans1[i+4][j+4];
				energy_sum = energy_sum + ImageTrans2[i][j]*ImageTrans2[i][j];
			}
		feature_vector[8][k] = energy_sum/16384;
		energy_sum = 0;
//		cout << feature_vector[8][k] << endl;
	}


	for(int i=0; i<Width; i++)
		for(int j=0; j<Length; j++)
			pixel_sum = pixel_sum+Imagedata10[i][j];
	pixel_average = pixel_sum/16384;
	pixel_sum = 0;

	for(int i=0; i<Width; i++)
		for(int j=0; j<Length; j++)
			ImageTrans1[i+2][j+2] = Imagedata10[i][j];

	for(int i=0; i<2; i++)
		for(int j=2; j<Length+2; j++)
			ImageTrans1[i][j] = ImageTrans1[2][j];

	for(int i=Width+2; i<Width+4; i++)
		for(int j=2; j<Length+2; j++)
			ImageTrans1[i][j] = ImageTrans1[Width+1][j];

	for(int i=0; i<Width+4; i++)
		for(int j=0; j<2; j++)
			ImageTrans1[i][j] = ImageTrans1[i][2];

	for(int i=0; i<Width+4; i++)
		for(int j=Length+2; j<Length+4; j++)
			ImageTrans1[i][j] = ImageTrans1[i][Length+1];

	for(int i=0; i<Width+4; i++)
		for(int j=0; j<Length+4; j++)
			ImageTrans1[i][j] = ImageTrans1[i][j]-pixel_average;

	for(int k=0; k<25; k++)
	{
		for(int i=0; i<Width; i++)
			for(int j=0; j<Length; j++)
			{
				ImageTrans2[i][j] = filter_bank[k][0][0]*ImageTrans1[i][j]+filter_bank[k][0][1]*ImageTrans1[i][j+1]+filter_bank[k][0][2]*ImageTrans1[i][j+2]+filter_bank[k][0][3]*ImageTrans1[i][j+3]+filter_bank[k][0][4]*ImageTrans1[i][j+4] 
									+ filter_bank[k][1][0]*ImageTrans1[i+1][j]+filter_bank[k][1][1]*ImageTrans1[i+1][j+1]+filter_bank[k][1][2]*ImageTrans1[i+1][j+2]+filter_bank[k][1][3]*ImageTrans1[i+1][j+3]+filter_bank[k][1][4]*ImageTrans1[i+1][j+4]
									+ filter_bank[k][2][0]*ImageTrans1[i+2][j]+filter_bank[k][2][1]*ImageTrans1[i+2][j+1]+filter_bank[k][2][2]*ImageTrans1[i+2][j+2]+filter_bank[k][2][3]*ImageTrans1[i+2][j+3]+filter_bank[k][2][4]*ImageTrans1[i+2][j+4]
									+ filter_bank[k][3][0]*ImageTrans1[i+3][j]+filter_bank[k][3][1]*ImageTrans1[i+3][j+1]+filter_bank[k][3][2]*ImageTrans1[i+3][j+2]+filter_bank[k][3][3]*ImageTrans1[i+3][j+3]+filter_bank[k][3][4]*ImageTrans1[i+3][j+4]
									+ filter_bank[k][4][0]*ImageTrans1[i+4][j]+filter_bank[k][4][1]*ImageTrans1[i+4][j+1]+filter_bank[k][4][2]*ImageTrans1[i+4][j+2]+filter_bank[k][4][3]*ImageTrans1[i+4][j+3]+filter_bank[k][4][4]*ImageTrans1[i+4][j+4];
				energy_sum = energy_sum + ImageTrans2[i][j]*ImageTrans2[i][j];
			}
		feature_vector[9][k] = energy_sum/16384;
		energy_sum = 0;
//		cout << feature_vector[9][k] << endl;
	}


	for(int i=0; i<Width; i++)
		for(int j=0; j<Length; j++)
			pixel_sum = pixel_sum+Imagedata11[i][j];
	pixel_average = pixel_sum/16384;
	pixel_sum = 0;

	for(int i=0; i<Width; i++)
		for(int j=0; j<Length; j++)
			ImageTrans1[i+2][j+2] = Imagedata11[i][j];

	for(int i=0; i<2; i++)
		for(int j=2; j<Length+2; j++)
			ImageTrans1[i][j] = ImageTrans1[2][j];

	for(int i=Width+2; i<Width+4; i++)
		for(int j=2; j<Length+2; j++)
			ImageTrans1[i][j] = ImageTrans1[Width+1][j];

	for(int i=0; i<Width+4; i++)
		for(int j=0; j<2; j++)
			ImageTrans1[i][j] = ImageTrans1[i][2];

	for(int i=0; i<Width+4; i++)
		for(int j=Length+2; j<Length+4; j++)
			ImageTrans1[i][j] = ImageTrans1[i][Length+1];

	for(int i=0; i<Width+4; i++)
		for(int j=0; j<Length+4; j++)
			ImageTrans1[i][j] = ImageTrans1[i][j]-pixel_average;

	for(int k=0; k<25; k++)
	{
		for(int i=0; i<Width; i++)
			for(int j=0; j<Length; j++)
			{
				ImageTrans2[i][j] = filter_bank[k][0][0]*ImageTrans1[i][j]+filter_bank[k][0][1]*ImageTrans1[i][j+1]+filter_bank[k][0][2]*ImageTrans1[i][j+2]+filter_bank[k][0][3]*ImageTrans1[i][j+3]+filter_bank[k][0][4]*ImageTrans1[i][j+4] 
									+ filter_bank[k][1][0]*ImageTrans1[i+1][j]+filter_bank[k][1][1]*ImageTrans1[i+1][j+1]+filter_bank[k][1][2]*ImageTrans1[i+1][j+2]+filter_bank[k][1][3]*ImageTrans1[i+1][j+3]+filter_bank[k][1][4]*ImageTrans1[i+1][j+4]
									+ filter_bank[k][2][0]*ImageTrans1[i+2][j]+filter_bank[k][2][1]*ImageTrans1[i+2][j+1]+filter_bank[k][2][2]*ImageTrans1[i+2][j+2]+filter_bank[k][2][3]*ImageTrans1[i+2][j+3]+filter_bank[k][2][4]*ImageTrans1[i+2][j+4]
									+ filter_bank[k][3][0]*ImageTrans1[i+3][j]+filter_bank[k][3][1]*ImageTrans1[i+3][j+1]+filter_bank[k][3][2]*ImageTrans1[i+3][j+2]+filter_bank[k][3][3]*ImageTrans1[i+3][j+3]+filter_bank[k][3][4]*ImageTrans1[i+3][j+4]
									+ filter_bank[k][4][0]*ImageTrans1[i+4][j]+filter_bank[k][4][1]*ImageTrans1[i+4][j+1]+filter_bank[k][4][2]*ImageTrans1[i+4][j+2]+filter_bank[k][4][3]*ImageTrans1[i+4][j+3]+filter_bank[k][4][4]*ImageTrans1[i+4][j+4];
				energy_sum = energy_sum + ImageTrans2[i][j]*ImageTrans2[i][j];
			}
		feature_vector[10][k] = energy_sum/16384;
		energy_sum = 0;
//		cout << feature_vector[10][k] << endl;
	}


	for(int i=0; i<Width; i++)
		for(int j=0; j<Length; j++)
			pixel_sum = pixel_sum+Imagedata12[i][j];
	pixel_average = pixel_sum/16384;
	pixel_sum = 0;

	for(int i=0; i<Width; i++)
		for(int j=0; j<Length; j++)
			ImageTrans1[i+2][j+2] = Imagedata12[i][j];

	for(int i=0; i<2; i++)
		for(int j=2; j<Length+2; j++)
			ImageTrans1[i][j] = ImageTrans1[2][j];

	for(int i=Width+2; i<Width+4; i++)
		for(int j=2; j<Length+2; j++)
			ImageTrans1[i][j] = ImageTrans1[Width+1][j];

	for(int i=0; i<Width+4; i++)
		for(int j=0; j<2; j++)
			ImageTrans1[i][j] = ImageTrans1[i][2];

	for(int i=0; i<Width+4; i++)
		for(int j=Length+2; j<Length+4; j++)
			ImageTrans1[i][j] = ImageTrans1[i][Length+1];

	for(int i=0; i<Width+4; i++)
		for(int j=0; j<Length+4; j++)
			ImageTrans1[i][j] = ImageTrans1[i][j]-pixel_average;

	for(int k=0; k<25; k++)
	{
		for(int i=0; i<Width; i++)
			for(int j=0; j<Length; j++)
			{
				ImageTrans2[i][j] = filter_bank[k][0][0]*ImageTrans1[i][j]+filter_bank[k][0][1]*ImageTrans1[i][j+1]+filter_bank[k][0][2]*ImageTrans1[i][j+2]+filter_bank[k][0][3]*ImageTrans1[i][j+3]+filter_bank[k][0][4]*ImageTrans1[i][j+4] 
									+ filter_bank[k][1][0]*ImageTrans1[i+1][j]+filter_bank[k][1][1]*ImageTrans1[i+1][j+1]+filter_bank[k][1][2]*ImageTrans1[i+1][j+2]+filter_bank[k][1][3]*ImageTrans1[i+1][j+3]+filter_bank[k][1][4]*ImageTrans1[i+1][j+4]
									+ filter_bank[k][2][0]*ImageTrans1[i+2][j]+filter_bank[k][2][1]*ImageTrans1[i+2][j+1]+filter_bank[k][2][2]*ImageTrans1[i+2][j+2]+filter_bank[k][2][3]*ImageTrans1[i+2][j+3]+filter_bank[k][2][4]*ImageTrans1[i+2][j+4]
									+ filter_bank[k][3][0]*ImageTrans1[i+3][j]+filter_bank[k][3][1]*ImageTrans1[i+3][j+1]+filter_bank[k][3][2]*ImageTrans1[i+3][j+2]+filter_bank[k][3][3]*ImageTrans1[i+3][j+3]+filter_bank[k][3][4]*ImageTrans1[i+3][j+4]
									+ filter_bank[k][4][0]*ImageTrans1[i+4][j]+filter_bank[k][4][1]*ImageTrans1[i+4][j+1]+filter_bank[k][4][2]*ImageTrans1[i+4][j+2]+filter_bank[k][4][3]*ImageTrans1[i+4][j+3]+filter_bank[k][4][4]*ImageTrans1[i+4][j+4];
				energy_sum = energy_sum + ImageTrans2[i][j]*ImageTrans2[i][j];
			}
		feature_vector[11][k] = energy_sum/16384;
		energy_sum = 0;
//		cout << feature_vector[11][k] << endl;
	}


	for(int i=0; i<12; i++)
	{
		for(int j=0; j<25; j++)
			cout << feature_vector[i][j] << endl;
		cout << endl;
	}

/****************************************normal feature vector******************************************/
	double feature_vector_max[25] = {0};
	for(int j=0; j<25; j++)
	{
		feature_vector_max[j] = feature_vector[0][j];
		for(int i=1; i<12; i++)
		{
			if(feature_vector_max[j]<feature_vector[i][j])
				feature_vector_max[j] = feature_vector[i][j];
		}
	}

	for(int i=0; i<12; i++)
	{
		for(int j=0; j<25; j++)
			feature_vector[i][j] = feature_vector[i][j]/feature_vector_max[j];
	}

/*
	for(int i=0; i<12; i++)
	{
		for(int j=0; j<25; j++)
			cout << feature_vector[i][j] << ",";
		cout << endl;
	}
	cout << endl;*/


/****************************************maximum mean algorthim******************************************/
/*	for(int i=0; i<4; i++)
		for(int j=0; j<25; j++)
			kmean_center_new[i][j] = feature_vector[3*i][j];*/

	double distance_center_1[12] = {0.0};
	double distance_center_2[12] = {0.0};
	double distance_center_3[12] = {0.0};
//first center
/*	for(int j=0; j<25; j++)
	{
		for(int i=0; i<12; i++)
		{
			kmean_center_new[0][j] = kmean_center_new[0][j]+feature_vector[i][j];
		}
		kmean_center_new[0][j] = kmean_center_new[0][j]/12.0;
//		cout << kmean_center_new[0][j] <<",";
	}
//	cout << endl;*/
	for(int j=0; j<25; j++)
		kmean_center_new[0][j] = feature_vector[1][j];

//second center
	memset(distance_center_1,0.0,sizeof(distance_center_1));
	for(int i=0; i<12; i++)
		for(int j=0; j<25; j++)
		{
			distance_center_1[i] = distance_center_1[i] + (feature_vector[i][j]-kmean_center_new[0][j])*(feature_vector[i][j]-kmean_center_new[0][j]);
		}

	int max = 0;
	for(int i=0; i<12; i++)
	{
		if((distance_center_1[i]>distance_center_1[max])&&(distance_center_1[i]!=0))
			max = i;
	}
//	cout << max << endl;
	for(int j=0; j<25; j++)
	{
		kmean_center_new[1][j] = feature_vector[max][j];
//		cout << kmean_center_new[1][j] <<",";
	}
//	cout << endl;

//third center
	memset(distance_center_1,0.0,sizeof(distance_center_1));
	memset(distance_center_2,0.0,sizeof(distance_center_2));
	for(int i=0; i<12; i++)
		for(int j=0; j<25; j++)
		{
			distance_center_1[i] = distance_center_1[i] + (feature_vector[i][j]-kmean_center_new[0][j])*(feature_vector[i][j]-kmean_center_new[0][j]);
			distance_center_2[i] = distance_center_2[i] + (feature_vector[i][j]-kmean_center_new[1][j])*(feature_vector[i][j]-kmean_center_new[1][j]);		
		}

	max = 0;
	for(int i=0; i<12; i++)
	{
		if(((distance_center_1[i]+distance_center_2[i])>(distance_center_1[max]+distance_center_2[max]))&&(distance_center_1[i]!=0)&&(distance_center_2[i]!=0))
			max = i;
	}
//	cout << max << endl;
	for(int j=0; j<25; j++)
	{
		kmean_center_new[2][j] = feature_vector[max][j];
//		cout << kmean_center_new[2][j] <<",";
	}
//	cout << endl;


//fourth center
	memset(distance_center_1,0.0,sizeof(distance_center_1));
	memset(distance_center_2,0.0,sizeof(distance_center_2));
	memset(distance_center_3,0.0,sizeof(distance_center_3));
	for(int i=0; i<12; i++)
		for(int j=0; j<25; j++)
		{
			distance_center_1[i] = distance_center_1[i] + (feature_vector[i][j]-kmean_center_new[0][j])*(feature_vector[i][j]-kmean_center_new[0][j]);
			distance_center_2[i] = distance_center_2[i] + (feature_vector[i][j]-kmean_center_new[1][j])*(feature_vector[i][j]-kmean_center_new[1][j]);		
			distance_center_3[i] = distance_center_3[i] + (feature_vector[i][j]-kmean_center_new[2][j])*(feature_vector[i][j]-kmean_center_new[2][j]);				
		}

	max = 0;
	for(int i=0; i<12; i++)
	{
		if(((distance_center_1[i]+distance_center_2[i]+distance_center_3[i])>(distance_center_1[max]+distance_center_2[max]+distance_center_3[max]))&&(distance_center_1[i]!=0)&&(distance_center_2[i]!=0)&&(distance_center_3[i]!=0))
			max = i;
	}
//	cout << max << endl;
	for(int j=0; j<25; j++)
	{
		kmean_center_new[3][j] = feature_vector[max][j];
//		cout << kmean_center_new[3][j] <<",";
	}
//	cout << endl;


/************************************************k-mean**************************************************/
	bool break_flag_1 = false;
	char label[12] = {0};
	
	while(!break_flag_1)
	{
		double distance[4]={0.0};
		for(int i=0; i<12; i++)
		{
			for(int j=0; j<25; j++)
			{
				distance[0] = distance[0] + (feature_vector[i][j]-kmean_center_new[0][j])*(feature_vector[i][j]-kmean_center_new[0][j]);
				distance[1] = distance[1] + (feature_vector[i][j]-kmean_center_new[1][j])*(feature_vector[i][j]-kmean_center_new[1][j]);
				distance[2] = distance[2] + (feature_vector[i][j]-kmean_center_new[2][j])*(feature_vector[i][j]-kmean_center_new[2][j]);
				distance[3] = distance[3] + (feature_vector[i][j]-kmean_center_new[3][j])*(feature_vector[i][j]-kmean_center_new[3][j]);
			}
//			cout << distance[0] <<","<<distance[1] <<","<<distance[2] <<","<<distance[3] << endl;
			if((distance[0]<=distance[1])&&(distance[0]<=distance[2])&&(distance[0]<=distance[3]))
				label[i] = 1;
			else if((distance[1]<=distance[0])&&(distance[1]<=distance[2])&&(distance[1]<=distance[3]))
				label[i] = 2;
			else if((distance[2]<=distance[0])&&(distance[2]<=distance[1])&&(distance[2]<=distance[3]))
				label[i] = 3;
			else if((distance[3]<=distance[0])&&(distance[3]<=distance[1])&&(distance[3]<=distance[2]))
				label[i] = 4;
//			printf("%u\n",label[i]);
			memset(distance,0,sizeof(distance));
		}

		int flag[4] ={0};
		memset(flag,0,sizeof(flag));
		double center_sum[4][25] ={0.0};
		memset(center_sum,0.0,sizeof(center_sum));
		for(int i=0; i<12; i++)
		{
			if(label[i]==1)
			{
				flag[0]++;
				for(int j=0; j<25; j++)
					center_sum[0][j] = center_sum[0][j]+feature_vector[i][j];
			}
			else if(label[i]==2)
			{
				flag[1]++;
				for(int j=0; j<25; j++)
					center_sum[1][j] = center_sum[1][j]+feature_vector[i][j];
			}
			else if(label[i]==3)
			{
				flag[2]++;
				for(int j=0; j<25; j++)
					center_sum[2][j] = center_sum[2][j]+feature_vector[i][j];
			}
			else if(label[i]==4)
			{
				flag[3]++;
				for(int j=0; j<25; j++)
					center_sum[3][j] = center_sum[3][j]+feature_vector[i][j];
			}
		}

/*		for(int i=0; i<4; i++)
			cout << flag[i] << ",";
		cout << endl;*/
		for(int i=0; i<4; i++)
		{
			for(int j=0; j<25; j++)
			{
				kmean_center_old[i][j] = kmean_center_new[i][j];
				kmean_center_new[i][j] = center_sum[i][j]/flag[i];
//				cout <<kmean_center_new[i][j] <<",";
			}
//			cout << endl;
		}
		
		break_flag_1 = true;
		for(int i=0; i<4&&break_flag_1; i++)
		{
			for(int j=0; j<25&&break_flag_1; j++)
			{
				if(kmean_center_new[i][j]!=kmean_center_old[i][j])
					break_flag_1 = false;
			}
		}	
	}

	cout << "25-D: " << endl;
	for(int i=0; i<12; i++)
		printf("%u,",label[i]);
	cout << endl;

/****************************************maximum mean algorthim******************************************/
//first center
	for(int j=0; j<3; j++)
		kmean_center_new3d[0][j] = feature_vector3d[0][j];

//second center
	memset(distance_center_1,0.0,sizeof(distance_center_1));
	for(int i=0; i<12; i++)
		for(int j=0; j<3; j++)
		{
			distance_center_1[i] = distance_center_1[i] + (feature_vector3d[i][j]-kmean_center_new3d[0][j])*(feature_vector3d[i][j]-kmean_center_new3d[0][j]);
		}

	max = 0;
	for(int i=0; i<12; i++)
	{
		if((distance_center_1[i]>distance_center_1[max])&&(distance_center_1[i]!=0))
			max = i;
	}
//	cout << max << endl;
	for(int j=0; j<3; j++)
	{
		kmean_center_new3d[1][j] = feature_vector3d[max][j];
//		cout << kmean_center_new[1][j] <<",";
	}
//	cout << endl;

//third center
	memset(distance_center_1,0.0,sizeof(distance_center_1));
	memset(distance_center_2,0.0,sizeof(distance_center_2));
	for(int i=0; i<12; i++)
		for(int j=0; j<3; j++)
		{
			distance_center_1[i] = distance_center_1[i] + (feature_vector3d[i][j]-kmean_center_new3d[0][j])*(feature_vector3d[i][j]-kmean_center_new3d[0][j]);
			distance_center_2[i] = distance_center_2[i] + (feature_vector3d[i][j]-kmean_center_new3d[1][j])*(feature_vector3d[i][j]-kmean_center_new3d[1][j]);		
		}

	max = 0;
	for(int i=0; i<12; i++)
	{
		if(((distance_center_1[i]+distance_center_2[i])>(distance_center_1[max]+distance_center_2[max]))&&(distance_center_1[i]!=0)&&(distance_center_2[i]!=0))
			max = i;
	}
//	cout << max << endl;
	for(int j=0; j<3; j++)
	{
		kmean_center_new3d[2][j] = feature_vector3d[max][j];
//		cout << kmean_center_new[2][j] <<",";
	}
//	cout << endl;


//fourth center
	memset(distance_center_1,0.0,sizeof(distance_center_1));
	memset(distance_center_2,0.0,sizeof(distance_center_2));
	memset(distance_center_3,0.0,sizeof(distance_center_3));
	for(int i=0; i<12; i++)
		for(int j=0; j<3; j++)
		{
			distance_center_1[i] = distance_center_1[i] + (feature_vector3d[i][j]-kmean_center_new3d[0][j])*(feature_vector3d[i][j]-kmean_center_new3d[0][j]);
			distance_center_2[i] = distance_center_2[i] + (feature_vector3d[i][j]-kmean_center_new3d[1][j])*(feature_vector3d[i][j]-kmean_center_new3d[1][j]);		
			distance_center_3[i] = distance_center_3[i] + (feature_vector3d[i][j]-kmean_center_new3d[2][j])*(feature_vector3d[i][j]-kmean_center_new3d[2][j]);				
		}

	max = 0;
	for(int i=0; i<12; i++)
	{
		if(((distance_center_1[i]+distance_center_2[i]+distance_center_3[i])>(distance_center_1[max]+distance_center_2[max]+distance_center_3[max]))&&(distance_center_1[i]!=0)&&(distance_center_2[i]!=0)&&(distance_center_3[i]!=0))
			max = i;
	}
//	cout << max << endl;
	for(int j=0; j<3; j++)
	{
		kmean_center_new3d[3][j] = feature_vector3d[max][j];
//		cout << kmean_center_new[3][j] <<",";
	}
//	cout << endl;


/************************************************k-mean**************************************************/
	break_flag_1 = false;
	char label3d[12] = {0};
	
	while(!break_flag_1)
	{
		double distance3d[4]={0.0};
		for(int i=0; i<12; i++)
		{
			for(int j=0; j<3; j++)
			{
				distance3d[0] = distance3d[0] + (feature_vector3d[i][j]-kmean_center_new3d[0][j])*(feature_vector3d[i][j]-kmean_center_new3d[0][j]);
				distance3d[1] = distance3d[1] + (feature_vector3d[i][j]-kmean_center_new3d[1][j])*(feature_vector3d[i][j]-kmean_center_new3d[1][j]);
				distance3d[2] = distance3d[2] + (feature_vector3d[i][j]-kmean_center_new3d[2][j])*(feature_vector3d[i][j]-kmean_center_new3d[2][j]);
				distance3d[3] = distance3d[3] + (feature_vector3d[i][j]-kmean_center_new3d[3][j])*(feature_vector3d[i][j]-kmean_center_new3d[3][j]);
			}
//			cout << distance3d[0] <<","<<distance3d[1] <<","<<distance3d[2] <<","<<distance3d[3] << endl;
			if((distance3d[0]<=distance3d[1])&&(distance3d[0]<=distance3d[2])&&(distance3d[0]<=distance3d[3]))
				label3d[i] = 1;
			else if((distance3d[1]<=distance3d[0])&&(distance3d[1]<=distance3d[2])&&(distance3d[1]<=distance3d[3]))
				label3d[i] = 2;
			else if((distance3d[2]<=distance3d[0])&&(distance3d[2]<=distance3d[1])&&(distance3d[2]<=distance3d[3]))
				label3d[i] = 3;
			else if((distance3d[3]<=distance3d[0])&&(distance3d[3]<=distance3d[1])&&(distance3d[3]<=distance3d[2]))
				label3d[i] = 4;
//			printf("%u\n",label3d[i]);
			memset(distance3d,0,sizeof(distance3d));
		}

		int flag3d[4] ={0};
		memset(flag3d,0,sizeof(flag3d));
		double center_sum3d[4][4] ={0.0};
		memset(center_sum3d,0.0,sizeof(center_sum3d));
		for(int i=0; i<12; i++)
		{
			if(label3d[i]==1)
			{
				flag3d[0]++;
				for(int j=0; j<3; j++)
					center_sum3d[0][j] = center_sum3d[0][j]+feature_vector3d[i][j];
			}
			else if(label3d[i]==2)
			{
				flag3d[1]++;
				for(int j=0; j<3; j++)
					center_sum3d[1][j] = center_sum3d[1][j]+feature_vector3d[i][j];
			}
			else if(label3d[i]==3)
			{
				flag3d[2]++;
				for(int j=0; j<3; j++)
					center_sum3d[2][j] = center_sum3d[2][j]+feature_vector3d[i][j];
			}
			else if(label3d[i]==4)
			{
				flag3d[3]++;
				for(int j=0; j<3; j++)
					center_sum3d[3][j] = center_sum3d[3][j]+feature_vector3d[i][j];
			}
		}

/*		for(int i=0; i<4; i++)
			cout << flag3d[i] << ",";
		cout << endl;*/
		for(int i=0; i<4; i++)
			for(int j=0; j<3; j++)
			{
				kmean_center_old3d[i][j] = kmean_center_new3d[i][j];
				kmean_center_new3d[i][j] = center_sum3d[i][j]/flag3d[i];
			}
		
		break_flag_1 = true;
		for(int i=0; i<4&&break_flag_1; i++)
		{
			for(int j=0; j<3&&break_flag_1; j++)
			{
				if(kmean_center_new3d[i][j]!=kmean_center_old3d[i][j])
					break_flag_1 = false;
			}
		}	
	}

	cout << "3-D: " << endl;
	for(int i=0; i<12; i++)
		printf("%u,",label3d[i]);
	cout << endl;


	for(int i=0; i<Width; i++)
		for(int j=0; j<Length; j++)
			pixel_sum = pixel_sum+ImagedataA[i][j];
	pixel_average = pixel_sum/16384;
	pixel_sum = 0;

	for(int i=0; i<Width; i++)
		for(int j=0; j<Length; j++)
			ImageTrans1[i+2][j+2] = ImagedataA[i][j];

	for(int i=0; i<2; i++)
		for(int j=2; j<Length+2; j++)
			ImageTrans1[i][j] = ImageTrans1[2][j];

	for(int i=Width+2; i<Width+4; i++)
		for(int j=2; j<Length+2; j++)
			ImageTrans1[i][j] = ImageTrans1[Width+1][j];

	for(int i=0; i<Width+4; i++)
		for(int j=0; j<2; j++)
			ImageTrans1[i][j] = ImageTrans1[i][2];

	for(int i=0; i<Width+4; i++)
		for(int j=Length+2; j<Length+4; j++)
			ImageTrans1[i][j] = ImageTrans1[i][Length+1];

	for(int i=0; i<Width+4; i++)
		for(int j=0; j<Length+4; j++)
			ImageTrans1[i][j] = ImageTrans1[i][j]-pixel_average;

	for(int k=0; k<25; k++)
	{
		for(int i=0; i<Width; i++)
			for(int j=0; j<Length; j++)
			{
				ImageTrans2[i][j] = filter_bank[k][0][0]*ImageTrans1[i][j]+filter_bank[k][0][1]*ImageTrans1[i][j+1]+filter_bank[k][0][2]*ImageTrans1[i][j+2]+filter_bank[k][0][3]*ImageTrans1[i][j+3]+filter_bank[k][0][4]*ImageTrans1[i][j+4] 
									+ filter_bank[k][1][0]*ImageTrans1[i+1][j]+filter_bank[k][1][1]*ImageTrans1[i+1][j+1]+filter_bank[k][1][2]*ImageTrans1[i+1][j+2]+filter_bank[k][1][3]*ImageTrans1[i+1][j+3]+filter_bank[k][1][4]*ImageTrans1[i+1][j+4]
									+ filter_bank[k][2][0]*ImageTrans1[i+2][j]+filter_bank[k][2][1]*ImageTrans1[i+2][j+1]+filter_bank[k][2][2]*ImageTrans1[i+2][j+2]+filter_bank[k][2][3]*ImageTrans1[i+2][j+3]+filter_bank[k][2][4]*ImageTrans1[i+2][j+4]
									+ filter_bank[k][3][0]*ImageTrans1[i+3][j]+filter_bank[k][3][1]*ImageTrans1[i+3][j+1]+filter_bank[k][3][2]*ImageTrans1[i+3][j+2]+filter_bank[k][3][3]*ImageTrans1[i+3][j+3]+filter_bank[k][3][4]*ImageTrans1[i+3][j+4]
									+ filter_bank[k][4][0]*ImageTrans1[i+4][j]+filter_bank[k][4][1]*ImageTrans1[i+4][j+1]+filter_bank[k][4][2]*ImageTrans1[i+4][j+2]+filter_bank[k][4][3]*ImageTrans1[i+4][j+3]+filter_bank[k][4][4]*ImageTrans1[i+4][j+4];
				energy_sum = energy_sum + ImageTrans2[i][j]*ImageTrans2[i][j];
			}
		feature_vector_6[0][k] = energy_sum/16384;
		energy_sum = 0;
//		cout << feature_vector_6[0][k] << endl;
	}

	for(int i=0; i<Width; i++)
		for(int j=0; j<Length; j++)
			pixel_sum = pixel_sum+ImagedataB[i][j];
	pixel_average = pixel_sum/16384;
	pixel_sum = 0;

	for(int i=0; i<Width; i++)
		for(int j=0; j<Length; j++)
			ImageTrans1[i+2][j+2] = ImagedataB[i][j];

	for(int i=0; i<2; i++)
		for(int j=2; j<Length+2; j++)
			ImageTrans1[i][j] = ImageTrans1[2][j];

	for(int i=Width+2; i<Width+4; i++)
		for(int j=2; j<Length+2; j++)
			ImageTrans1[i][j] = ImageTrans1[Width+1][j];

	for(int i=0; i<Width+4; i++)
		for(int j=0; j<2; j++)
			ImageTrans1[i][j] = ImageTrans1[i][2];

	for(int i=0; i<Width+4; i++)
		for(int j=Length+2; j<Length+4; j++)
			ImageTrans1[i][j] = ImageTrans1[i][Length+1];

	for(int i=0; i<Width+4; i++)
		for(int j=0; j<Length+4; j++)
			ImageTrans1[i][j] = ImageTrans1[i][j]-pixel_average;

	for(int k=0; k<25; k++)
	{
		for(int i=0; i<Width; i++)
			for(int j=0; j<Length; j++)
			{
				ImageTrans2[i][j] = filter_bank[k][0][0]*ImageTrans1[i][j]+filter_bank[k][0][1]*ImageTrans1[i][j+1]+filter_bank[k][0][2]*ImageTrans1[i][j+2]+filter_bank[k][0][3]*ImageTrans1[i][j+3]+filter_bank[k][0][4]*ImageTrans1[i][j+4] 
									+ filter_bank[k][1][0]*ImageTrans1[i+1][j]+filter_bank[k][1][1]*ImageTrans1[i+1][j+1]+filter_bank[k][1][2]*ImageTrans1[i+1][j+2]+filter_bank[k][1][3]*ImageTrans1[i+1][j+3]+filter_bank[k][1][4]*ImageTrans1[i+1][j+4]
									+ filter_bank[k][2][0]*ImageTrans1[i+2][j]+filter_bank[k][2][1]*ImageTrans1[i+2][j+1]+filter_bank[k][2][2]*ImageTrans1[i+2][j+2]+filter_bank[k][2][3]*ImageTrans1[i+2][j+3]+filter_bank[k][2][4]*ImageTrans1[i+2][j+4]
									+ filter_bank[k][3][0]*ImageTrans1[i+3][j]+filter_bank[k][3][1]*ImageTrans1[i+3][j+1]+filter_bank[k][3][2]*ImageTrans1[i+3][j+2]+filter_bank[k][3][3]*ImageTrans1[i+3][j+3]+filter_bank[k][3][4]*ImageTrans1[i+3][j+4]
									+ filter_bank[k][4][0]*ImageTrans1[i+4][j]+filter_bank[k][4][1]*ImageTrans1[i+4][j+1]+filter_bank[k][4][2]*ImageTrans1[i+4][j+2]+filter_bank[k][4][3]*ImageTrans1[i+4][j+3]+filter_bank[k][4][4]*ImageTrans1[i+4][j+4];
				energy_sum = energy_sum + ImageTrans2[i][j]*ImageTrans2[i][j];
			}
		feature_vector_6[1][k] = energy_sum/16384;
		energy_sum = 0;
//		cout << feature_vector_6[1][k] << endl;
	}

	for(int i=0; i<Width; i++)
		for(int j=0; j<Length; j++)
			pixel_sum = pixel_sum+ImagedataC[i][j];
	pixel_average = pixel_sum/16384;
	pixel_sum = 0;

	for(int i=0; i<Width; i++)
		for(int j=0; j<Length; j++)
			ImageTrans1[i+2][j+2] = ImagedataC[i][j];

	for(int i=0; i<2; i++)
		for(int j=2; j<Length+2; j++)
			ImageTrans1[i][j] = ImageTrans1[2][j];

	for(int i=Width+2; i<Width+4; i++)
		for(int j=2; j<Length+2; j++)
			ImageTrans1[i][j] = ImageTrans1[Width+1][j];

	for(int i=0; i<Width+4; i++)
		for(int j=0; j<2; j++)
			ImageTrans1[i][j] = ImageTrans1[i][2];

	for(int i=0; i<Width+4; i++)
		for(int j=Length+2; j<Length+4; j++)
			ImageTrans1[i][j] = ImageTrans1[i][Length+1];

	for(int i=0; i<Width+4; i++)
		for(int j=0; j<Length+4; j++)
			ImageTrans1[i][j] = ImageTrans1[i][j]-pixel_average;

	for(int k=0; k<25; k++)
	{
		for(int i=0; i<Width; i++)
			for(int j=0; j<Length; j++)
			{
				ImageTrans2[i][j] = filter_bank[k][0][0]*ImageTrans1[i][j]+filter_bank[k][0][1]*ImageTrans1[i][j+1]+filter_bank[k][0][2]*ImageTrans1[i][j+2]+filter_bank[k][0][3]*ImageTrans1[i][j+3]+filter_bank[k][0][4]*ImageTrans1[i][j+4] 
									+ filter_bank[k][1][0]*ImageTrans1[i+1][j]+filter_bank[k][1][1]*ImageTrans1[i+1][j+1]+filter_bank[k][1][2]*ImageTrans1[i+1][j+2]+filter_bank[k][1][3]*ImageTrans1[i+1][j+3]+filter_bank[k][1][4]*ImageTrans1[i+1][j+4]
									+ filter_bank[k][2][0]*ImageTrans1[i+2][j]+filter_bank[k][2][1]*ImageTrans1[i+2][j+1]+filter_bank[k][2][2]*ImageTrans1[i+2][j+2]+filter_bank[k][2][3]*ImageTrans1[i+2][j+3]+filter_bank[k][2][4]*ImageTrans1[i+2][j+4]
									+ filter_bank[k][3][0]*ImageTrans1[i+3][j]+filter_bank[k][3][1]*ImageTrans1[i+3][j+1]+filter_bank[k][3][2]*ImageTrans1[i+3][j+2]+filter_bank[k][3][3]*ImageTrans1[i+3][j+3]+filter_bank[k][3][4]*ImageTrans1[i+3][j+4]
									+ filter_bank[k][4][0]*ImageTrans1[i+4][j]+filter_bank[k][4][1]*ImageTrans1[i+4][j+1]+filter_bank[k][4][2]*ImageTrans1[i+4][j+2]+filter_bank[k][4][3]*ImageTrans1[i+4][j+3]+filter_bank[k][4][4]*ImageTrans1[i+4][j+4];
				energy_sum = energy_sum + ImageTrans2[i][j]*ImageTrans2[i][j];
			}
		feature_vector_6[2][k] = energy_sum/16384;
		energy_sum = 0;
//		cout << feature_vector_6[2][k] << endl;
	}

	for(int i=0; i<Width; i++)
		for(int j=0; j<Length; j++)
			pixel_sum = pixel_sum+ImagedataD[i][j];
	pixel_average = pixel_sum/16384;
	pixel_sum = 0;

	for(int i=0; i<Width; i++)
		for(int j=0; j<Length; j++)
			ImageTrans1[i+2][j+2] = ImagedataD[i][j];

	for(int i=0; i<2; i++)
		for(int j=2; j<Length+2; j++)
			ImageTrans1[i][j] = ImageTrans1[2][j];

	for(int i=Width+2; i<Width+4; i++)
		for(int j=2; j<Length+2; j++)
			ImageTrans1[i][j] = ImageTrans1[Width+1][j];

	for(int i=0; i<Width+4; i++)
		for(int j=0; j<2; j++)
			ImageTrans1[i][j] = ImageTrans1[i][2];

	for(int i=0; i<Width+4; i++)
		for(int j=Length+2; j<Length+4; j++)
			ImageTrans1[i][j] = ImageTrans1[i][Length+1];

	for(int i=0; i<Width+4; i++)
		for(int j=0; j<Length+4; j++)
			ImageTrans1[i][j] = ImageTrans1[i][j]-pixel_average;

	for(int k=0; k<25; k++)
	{
		for(int i=0; i<Width; i++)
			for(int j=0; j<Length; j++)
			{
				ImageTrans2[i][j] = filter_bank[k][0][0]*ImageTrans1[i][j]+filter_bank[k][0][1]*ImageTrans1[i][j+1]+filter_bank[k][0][2]*ImageTrans1[i][j+2]+filter_bank[k][0][3]*ImageTrans1[i][j+3]+filter_bank[k][0][4]*ImageTrans1[i][j+4] 
									+ filter_bank[k][1][0]*ImageTrans1[i+1][j]+filter_bank[k][1][1]*ImageTrans1[i+1][j+1]+filter_bank[k][1][2]*ImageTrans1[i+1][j+2]+filter_bank[k][1][3]*ImageTrans1[i+1][j+3]+filter_bank[k][1][4]*ImageTrans1[i+1][j+4]
									+ filter_bank[k][2][0]*ImageTrans1[i+2][j]+filter_bank[k][2][1]*ImageTrans1[i+2][j+1]+filter_bank[k][2][2]*ImageTrans1[i+2][j+2]+filter_bank[k][2][3]*ImageTrans1[i+2][j+3]+filter_bank[k][2][4]*ImageTrans1[i+2][j+4]
									+ filter_bank[k][3][0]*ImageTrans1[i+3][j]+filter_bank[k][3][1]*ImageTrans1[i+3][j+1]+filter_bank[k][3][2]*ImageTrans1[i+3][j+2]+filter_bank[k][3][3]*ImageTrans1[i+3][j+3]+filter_bank[k][3][4]*ImageTrans1[i+3][j+4]
									+ filter_bank[k][4][0]*ImageTrans1[i+4][j]+filter_bank[k][4][1]*ImageTrans1[i+4][j+1]+filter_bank[k][4][2]*ImageTrans1[i+4][j+2]+filter_bank[k][4][3]*ImageTrans1[i+4][j+3]+filter_bank[k][4][4]*ImageTrans1[i+4][j+4];
				energy_sum = energy_sum + ImageTrans2[i][j]*ImageTrans2[i][j];
			}
		feature_vector_6[3][k] = energy_sum/16384;
		energy_sum = 0;
//		cout << feature_vector_6[0][k] << endl;
	}

	for(int i=0; i<Width; i++)
		for(int j=0; j<Length; j++)
			pixel_sum = pixel_sum+ImagedataE[i][j];
	pixel_average = pixel_sum/16384;
	pixel_sum = 0;

	for(int i=0; i<Width; i++)
		for(int j=0; j<Length; j++)
			ImageTrans1[i+2][j+2] = ImagedataE[i][j];

	for(int i=0; i<2; i++)
		for(int j=2; j<Length+2; j++)
			ImageTrans1[i][j] = ImageTrans1[2][j];

	for(int i=Width+2; i<Width+4; i++)
		for(int j=2; j<Length+2; j++)
			ImageTrans1[i][j] = ImageTrans1[Width+1][j];

	for(int i=0; i<Width+4; i++)
		for(int j=0; j<2; j++)
			ImageTrans1[i][j] = ImageTrans1[i][2];

	for(int i=0; i<Width+4; i++)
		for(int j=Length+2; j<Length+4; j++)
			ImageTrans1[i][j] = ImageTrans1[i][Length+1];

	for(int i=0; i<Width+4; i++)
		for(int j=0; j<Length+4; j++)
			ImageTrans1[i][j] = ImageTrans1[i][j]-pixel_average;

	for(int k=0; k<25; k++)
	{
		for(int i=0; i<Width; i++)
			for(int j=0; j<Length; j++)
			{
				ImageTrans2[i][j] = filter_bank[k][0][0]*ImageTrans1[i][j]+filter_bank[k][0][1]*ImageTrans1[i][j+1]+filter_bank[k][0][2]*ImageTrans1[i][j+2]+filter_bank[k][0][3]*ImageTrans1[i][j+3]+filter_bank[k][0][4]*ImageTrans1[i][j+4] 
									+ filter_bank[k][1][0]*ImageTrans1[i+1][j]+filter_bank[k][1][1]*ImageTrans1[i+1][j+1]+filter_bank[k][1][2]*ImageTrans1[i+1][j+2]+filter_bank[k][1][3]*ImageTrans1[i+1][j+3]+filter_bank[k][1][4]*ImageTrans1[i+1][j+4]
									+ filter_bank[k][2][0]*ImageTrans1[i+2][j]+filter_bank[k][2][1]*ImageTrans1[i+2][j+1]+filter_bank[k][2][2]*ImageTrans1[i+2][j+2]+filter_bank[k][2][3]*ImageTrans1[i+2][j+3]+filter_bank[k][2][4]*ImageTrans1[i+2][j+4]
									+ filter_bank[k][3][0]*ImageTrans1[i+3][j]+filter_bank[k][3][1]*ImageTrans1[i+3][j+1]+filter_bank[k][3][2]*ImageTrans1[i+3][j+2]+filter_bank[k][3][3]*ImageTrans1[i+3][j+3]+filter_bank[k][3][4]*ImageTrans1[i+3][j+4]
									+ filter_bank[k][4][0]*ImageTrans1[i+4][j]+filter_bank[k][4][1]*ImageTrans1[i+4][j+1]+filter_bank[k][4][2]*ImageTrans1[i+4][j+2]+filter_bank[k][4][3]*ImageTrans1[i+4][j+3]+filter_bank[k][4][4]*ImageTrans1[i+4][j+4];
				energy_sum = energy_sum + ImageTrans2[i][j]*ImageTrans2[i][j];
			}
		feature_vector_6[4][k] = energy_sum/16384;
		energy_sum = 0;
//		cout << feature_vector_6[0][k] << endl;
	}

	for(int i=0; i<Width; i++)
		for(int j=0; j<Length; j++)
			pixel_sum = pixel_sum+ImagedataF[i][j];
	pixel_average = pixel_sum/16384;
	pixel_sum = 0;

	for(int i=0; i<Width; i++)
		for(int j=0; j<Length; j++)
			ImageTrans1[i+2][j+2] = ImagedataF[i][j];

	for(int i=0; i<2; i++)
		for(int j=2; j<Length+2; j++)
			ImageTrans1[i][j] = ImageTrans1[2][j];

	for(int i=Width+2; i<Width+4; i++)
		for(int j=2; j<Length+2; j++)
			ImageTrans1[i][j] = ImageTrans1[Width+1][j];

	for(int i=0; i<Width+4; i++)
		for(int j=0; j<2; j++)
			ImageTrans1[i][j] = ImageTrans1[i][2];

	for(int i=0; i<Width+4; i++)
		for(int j=Length+2; j<Length+4; j++)
			ImageTrans1[i][j] = ImageTrans1[i][Length+1];

	for(int i=0; i<Width+4; i++)
		for(int j=0; j<Length+4; j++)
			ImageTrans1[i][j] = ImageTrans1[i][j]-pixel_average;

	for(int k=0; k<25; k++)
	{
		for(int i=0; i<Width; i++)
			for(int j=0; j<Length; j++)
			{
				ImageTrans2[i][j] = filter_bank[k][0][0]*ImageTrans1[i][j]+filter_bank[k][0][1]*ImageTrans1[i][j+1]+filter_bank[k][0][2]*ImageTrans1[i][j+2]+filter_bank[k][0][3]*ImageTrans1[i][j+3]+filter_bank[k][0][4]*ImageTrans1[i][j+4] 
									+ filter_bank[k][1][0]*ImageTrans1[i+1][j]+filter_bank[k][1][1]*ImageTrans1[i+1][j+1]+filter_bank[k][1][2]*ImageTrans1[i+1][j+2]+filter_bank[k][1][3]*ImageTrans1[i+1][j+3]+filter_bank[k][1][4]*ImageTrans1[i+1][j+4]
									+ filter_bank[k][2][0]*ImageTrans1[i+2][j]+filter_bank[k][2][1]*ImageTrans1[i+2][j+1]+filter_bank[k][2][2]*ImageTrans1[i+2][j+2]+filter_bank[k][2][3]*ImageTrans1[i+2][j+3]+filter_bank[k][2][4]*ImageTrans1[i+2][j+4]
									+ filter_bank[k][3][0]*ImageTrans1[i+3][j]+filter_bank[k][3][1]*ImageTrans1[i+3][j+1]+filter_bank[k][3][2]*ImageTrans1[i+3][j+2]+filter_bank[k][3][3]*ImageTrans1[i+3][j+3]+filter_bank[k][3][4]*ImageTrans1[i+3][j+4]
									+ filter_bank[k][4][0]*ImageTrans1[i+4][j]+filter_bank[k][4][1]*ImageTrans1[i+4][j+1]+filter_bank[k][4][2]*ImageTrans1[i+4][j+2]+filter_bank[k][4][3]*ImageTrans1[i+4][j+3]+filter_bank[k][4][4]*ImageTrans1[i+4][j+4];
				energy_sum = energy_sum + ImageTrans2[i][j]*ImageTrans2[i][j];
			}
		feature_vector_6[5][k] = energy_sum/16384;
		energy_sum = 0;
//		cout << feature_vector_6[0][k] << endl;
	}
/*
	for(int i=0; i<1; i++)
	{
		for(int j=0; j<25; j++)
		{
				cout <<kmean_center_new[i][j] <<",";
		}
			cout << endl;
	}*/

/****************************************normal feature vector******************************************/
/*	double feature_vector_max_6[25] = {0};
	for(int j=0; j<25; j++)
	{
		feature_vector_max_6[j] = feature_vector_6[0][j];
		for(int i=1; i<6; i++)
		{
			if(feature_vector_max_6[j]<feature_vector_6[i][j])
				feature_vector_max_6[j] = feature_vector_6[i][j];
		}
	}*/

	for(int i=0; i<6; i++)
	{
		for(int j=0; j<25; j++)
			feature_vector_6[i][j] = feature_vector_6[i][j]/feature_vector_max[j];
	}
/*
	for(int i=0; i<4; i++)
	{
		for(int j=0; j<25; j++)
		{
				cout <<kmean_center_new[i][j] <<",";
		}
			cout << endl;
	}
	cout << endl;*/

	char label_6[6] = {0};
	double distance_6[4]={0.0};
	for(int i=0; i<6; i++)
	{
		for(int j=0; j<25; j++)
		{
//			cout <<feature_vector_6[i][j] <<",";
			distance_6[0] = distance_6[0] + (feature_vector_6[i][j]-kmean_center_new[0][j])*(feature_vector_6[i][j]-kmean_center_new[0][j]);
			distance_6[1] = distance_6[1] + (feature_vector_6[i][j]-kmean_center_new[1][j])*(feature_vector_6[i][j]-kmean_center_new[1][j]);
			distance_6[2] = distance_6[2] + (feature_vector_6[i][j]-kmean_center_new[2][j])*(feature_vector_6[i][j]-kmean_center_new[2][j]);
			distance_6[3] = distance_6[3] + (feature_vector_6[i][j]-kmean_center_new[3][j])*(feature_vector_6[i][j]-kmean_center_new[3][j]);
		}
//		cout << endl;
//		cout << endl;
//		cout << distance_6[0] <<","<<distance_6[1] <<","<<distance_6[2] <<","<<distance_6[3] << endl;
		if((distance_6[0]<=distance_6[1])&&(distance_6[0]<=distance_6[2])&&(distance_6[0]<=distance_6[3]))
			label_6[i] = 1;
		else if((distance_6[1]<=distance_6[0])&&(distance_6[1]<=distance_6[2])&&(distance_6[1]<=distance_6[3]))
			label_6[i] = 2;
		else if((distance_6[2]<=distance_6[0])&&(distance_6[2]<=distance_6[1])&&(distance_6[2]<=distance_6[3]))
			label_6[i] = 3;
		else if((distance_6[3]<=distance_6[0])&&(distance_6[3]<=distance_6[1])&&(distance_6[3]<=distance_6[2]))
			label_6[i] = 4;
		memset(distance_6,0,sizeof(distance_6));
	}

	cout << "A-F: " << endl;
	for(int i=0; i<6; i++)
		printf("%u,",label_6[i]);
	cout << endl;

	return 0;
}
