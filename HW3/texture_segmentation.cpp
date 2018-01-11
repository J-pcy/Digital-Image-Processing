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


int Length = 590;
int Width = 350;
int BytesPerPixel = 3;
	
unsigned char Imagedata[350][590][3];

double feature_vector[25][350][590];
double kmean_center_old[25][5];
double kmean_center_new[25][5];

int ImageTrans3[350][590];
int ImageTrans1[350+4][590+4];
int ImageTrans2[25][350+20][590+20];

double energy_sum=0;
double pixel_sum=0;
int pixel_average=0;

double distance_center_1[350][590];
double distance_center_2[350][590];
double distance_center_3[350][590];

unsigned char label_rgb[350][590][3] = {0};

int main(int argc, char *argv[])
{
	FILE *file;	

	if (!(file=fopen("kitten.raw","rb"))) {
		cout << "Cannot open file: " << "kitten.raw" <<endl;
		exit(1);
	}
	fread(Imagedata, sizeof(unsigned char), Length*Width*BytesPerPixel, file);
	fclose(file);



	for(int i=0; i<Width; i++)
		for(int j=0; j<Length; j++)
			ImageTrans3[i][j] = 0.2989*Imagedata[i][j][0]+0.5870*Imagedata[i][j][1]+0.1140*Imagedata[i][j][2];


	for(int i=0; i<Width; i++)
		for(int j=0; j<Length; j++)
			pixel_sum = pixel_sum+ImageTrans3[i][j];
	pixel_average = pixel_sum/206500;

	for(int i=0; i<Width; i++)
		for(int j=0; j<Length; j++)
			ImageTrans1[i+2][j+2] = ImageTrans3[i][j];

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
				ImageTrans2[k][i+10][j+10] = filter_bank[k][0][0]*ImageTrans1[i][j]+filter_bank[k][0][1]*ImageTrans1[i][j+1]+filter_bank[k][0][2]*ImageTrans1[i][j+2]+filter_bank[k][0][3]*ImageTrans1[i][j+3]+filter_bank[k][0][4]*ImageTrans1[i][j+4] 
									+ filter_bank[k][1][0]*ImageTrans1[i+1][j]+filter_bank[k][1][1]*ImageTrans1[i+1][j+1]+filter_bank[k][1][2]*ImageTrans1[i+1][j+2]+filter_bank[k][1][3]*ImageTrans1[i+1][j+3]+filter_bank[k][1][4]*ImageTrans1[i+1][j+4]
									+ filter_bank[k][2][0]*ImageTrans1[i+2][j]+filter_bank[k][2][1]*ImageTrans1[i+2][j+1]+filter_bank[k][2][2]*ImageTrans1[i+2][j+2]+filter_bank[k][2][3]*ImageTrans1[i+2][j+3]+filter_bank[k][2][4]*ImageTrans1[i+2][j+4]
									+ filter_bank[k][3][0]*ImageTrans1[i+3][j]+filter_bank[k][3][1]*ImageTrans1[i+3][j+1]+filter_bank[k][3][2]*ImageTrans1[i+3][j+2]+filter_bank[k][3][3]*ImageTrans1[i+3][j+3]+filter_bank[k][3][4]*ImageTrans1[i+3][j+4]
									+ filter_bank[k][4][0]*ImageTrans1[i+4][j]+filter_bank[k][4][1]*ImageTrans1[i+4][j+1]+filter_bank[k][4][2]*ImageTrans1[i+4][j+2]+filter_bank[k][4][3]*ImageTrans1[i+4][j+3]+filter_bank[k][4][4]*ImageTrans1[i+4][j+4];
			}
		for(int i=0; i<10; i++)
			for(int j=10; j<Length+10; j++)
				ImageTrans2[k][i][j] = ImageTrans2[k][10][j];

		for(int i=Width+10; i<Width+20; i++)
			for(int j=10; j<Length+10; j++)
				ImageTrans2[k][i][j] = ImageTrans2[k][Width+9][j];

		for(int i=0; i<Width+20; i++)
			for(int j=0; j<10; j++)
				ImageTrans2[k][i][j] = ImageTrans2[k][i][10];

		for(int i=0; i<Width+20; i++)
			for(int j=Length+10; j<Length+20; j++)
				ImageTrans2[k][i][j] = ImageTrans2[k][i][Length+9];
	}

	for(int k=0; k<25; k++)
		for(int i=10; i<Width+10; i++)
			for(int j=10; j<Length+10; j++)
			{
				energy_sum = 0;
				for(int a=i-10; a<i+11; a++)
					for(int b=j-10; b<j+11; b++)
						energy_sum = energy_sum + ImageTrans2[k][a][b]*ImageTrans2[k][a][b];
				feature_vector[k][i-10][j-10] = energy_sum/441;
			}

	for(int k=1; k<25; k++)
		for(int i=0; i<Width; i++)
			for(int j=0; j<Length; j++)
				feature_vector[k][i][j] = feature_vector[k][i][j]/feature_vector[0][i][j];


	for(int i=0; i<Width; i++)
		for(int j=0; j<Length; j++)
			feature_vector[0][i][j] = feature_vector[0][i][j]/feature_vector[0][i][j];

/*
	for(int i=0; i<12; i++)
	{
		for(int j=0; j<25; j++)
			cout << feature_vector[i][j] << ",";
		cout << endl;
	}*/
	for(int k=0; k<25; k++)
	{
		kmean_center_new[k][0] = feature_vector[k][1][1];
		kmean_center_new[k][1] = feature_vector[k][80][140];
		kmean_center_new[k][2] = feature_vector[k][140][460];
		kmean_center_new[k][3] = feature_vector[k][270][280];
		kmean_center_new[k][4] = feature_vector[k][110][160];
	}


/************************************************k-mean**************************************************/
	int K_clusters = 5;
	bool break_flag_1 = false;
	unsigned char label[350][590] = {0};
	
//	while(!break_flag_1)
//	{
	for(int x=0; x<5; x++)
	{
		double distance[K_clusters];
		memset(distance,0.0,sizeof(distance));
		for(int i=0; i<Width; i++)
			for(int j=0; j<Length; j++)
			{
				for(int k=0; k<25; k++)
				{
					distance[0] = distance[0] + (feature_vector[k][i][j]-kmean_center_new[k][0])*(feature_vector[k][i][j]-kmean_center_new[k][0]);
					distance[1] = distance[1] + (feature_vector[k][i][j]-kmean_center_new[k][1])*(feature_vector[k][i][j]-kmean_center_new[k][1]);
					distance[2] = distance[2] + (feature_vector[k][i][j]-kmean_center_new[k][2])*(feature_vector[k][i][j]-kmean_center_new[k][2]);
					distance[3] = distance[3] + (feature_vector[k][i][j]-kmean_center_new[k][3])*(feature_vector[k][i][j]-kmean_center_new[k][3]);
					distance[4] = distance[4] + (feature_vector[k][i][j]-kmean_center_new[k][4])*(feature_vector[k][i][j]-kmean_center_new[k][4]);
				}
	//			cout << distance[0] <<","<<distance[1] <<","<<distance[2] <<","<<distance[3] << endl;
				if((distance[0]<=distance[1])&&(distance[0]<=distance[2])&&(distance[0]<=distance[3])&&(distance[0]<=distance[4]))
					label[i][j] = 0;
				else if((distance[1]<=distance[0])&&(distance[1]<=distance[2])&&(distance[1]<=distance[3])&&(distance[1]<=distance[4]))
					label[i][j] = 64;
				else if((distance[2]<=distance[0])&&(distance[2]<=distance[1])&&(distance[2]<=distance[3])&&(distance[2]<=distance[4]))
					label[i][j] = 128;
				else if((distance[3]<=distance[0])&&(distance[3]<=distance[1])&&(distance[3]<=distance[2])&&(distance[3]<=distance[4]))
					label[i][j] = 192;
				else if((distance[4]<=distance[0])&&(distance[4]<=distance[1])&&(distance[4]<=distance[2])&&(distance[4]<=distance[3]))
					label[i][j] = 255;

	//			printf("%u\n",label[i]);
				memset(distance,0.0,sizeof(distance));
			}

		int flag[K_clusters];
		memset(flag,0,sizeof(flag));
		double center_sum[25][K_clusters];
		memset(center_sum,0.0,sizeof(center_sum));
		for(int i=0; i<Width; i++)
			for(int j=0; j<Length; j++)
			{
				if(label[i][j]==0)
				{
					flag[0]++;
					for(int k=0; k<25; k++)
						center_sum[k][0] = center_sum[k][0]+feature_vector[k][i][j];
				}
				else if(label[i][j]==64)
				{
					flag[1]++;
					for(int k=0; k<25; k++)
						center_sum[k][1] = center_sum[k][1]+feature_vector[k][i][j];
				}
				else if(label[i][j]==128)
				{
					flag[2]++;
					for(int k=0; k<25; k++)
						center_sum[k][2] = center_sum[k][2]+feature_vector[k][i][j];
				}
				else if(label[i][j]==192)
				{
					flag[3]++;
					for(int k=0; k<25; k++)
						center_sum[k][3] = center_sum[k][3]+feature_vector[k][i][j];
				}
				else if(label[i][j]==255)
				{
					flag[4]++;
					for(int k=0; k<25; k++)
						center_sum[k][4] = center_sum[k][4]+feature_vector[k][i][j];
				}
			}
/*
		for(int i=0; i<K_clusters; i++)
			cout << flag[i] << ",";
		cout << endl;*/
		for(int i=0; i<K_clusters; i++)
		{
			for(int k=0; k<25; k++)
			{
//				cout << center_sum[k][i] <<",";
				kmean_center_old[k][i] = kmean_center_new[k][i];
				kmean_center_new[k][i] = center_sum[k][i]/flag[i];
//				cout << kmean_center_new[k][i] <<",";
			}
//			cout << endl;
		}

		
		break_flag_1 = true;
		for(int i=0; i<K_clusters&&break_flag_1; i++)
		{
			for(int k=0; k<25&&break_flag_1; k++)
			{
				if(kmean_center_new[k][i]!=kmean_center_old[k][i])
					break_flag_1 = false;
			}
		}	
	}
//	}

	for(int i=0; i<Width; i++)
		for(int j=0; j<Length; j++)
		{
			if(label[i][j]==0)
			{
				label_rgb[i][j][0] = 0;
				label_rgb[i][j][1] = 0;
				label_rgb[i][j][2] = 0;
			}
			else if(label[i][j]==64)
			{
				label_rgb[i][j][0] = 255;
				label_rgb[i][j][1] = 0;
				label_rgb[i][j][2] = 0;
			}
			else if(label[i][j]==128)
			{
				label_rgb[i][j][0] = 0;
				label_rgb[i][j][1] = 255;
				label_rgb[i][j][2] = 0;
			}
			else if(label[i][j]==192)
			{
				label_rgb[i][j][0] = 0;
				label_rgb[i][j][1] = 0;
				label_rgb[i][j][2] = 255;
			}
			else if(label[i][j]==255)
			{
				label_rgb[i][j][0] = 255;
				label_rgb[i][j][1] = 255;
				label_rgb[i][j][2] = 255;
			}		
		}


	if (!(file=fopen("texture_segmentation.raw","wb"))) {
		cout << "Cannot open file: " << "texture_segmentation.raw" << endl;
		exit(1);
	}
	fwrite(label_rgb, sizeof(unsigned char), 350*590*3, file);
	fclose(file);
/*
	if (!(file=fopen("Trump_warping.raw","wb"))) {
		cout << "Cannot open file: " << "Trump_warping.raw" << endl;
		exit(1);
	}
	fwrite(Imagedata3, sizeof(unsigned char), Length3*Width3, file);
	fclose(file);
*/
	return 0;
}
