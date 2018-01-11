/*************************************************************************
 > EE569 Homework Assignment #2
 > Date:     February 24, 2017
 > Author:   Chenyu Peng
 > ID:       3498-8893-91
 > email:    chenyupe@usc.edu

 > Compiled on OS X with gcc
 > Input: g++ -o puzzle_matching puzzle_matching.cpp
 		  ./puzzle_matching
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
	int Length1 = 500;  //piece.raw
	int Width1 = 500;
	int Length2 = 512;  //Hillary.raw
	int Width2 = 512;
	int Length3 = 512;  //Trump.raw
	int Width3 = 512;
	
	unsigned char Imagedata1[Width1][Length1][BytesPerPixel];       //piece.raw
	unsigned char Imagedata2[Width2][Length2][BytesPerPixel];       //Hillary.raw
	unsigned char Imagedata3[Width3][Length3][BytesPerPixel];       //Trump.raw

	if (!(file=fopen("piece.raw","rb"))) {
		cout << "Cannot open file: " << "piece.raw" <<endl;
		exit(1);
	}
	fread(Imagedata1, sizeof(unsigned char), Length1*Width1*BytesPerPixel, file);
	fclose(file);

	if (!(file=fopen("Hillary.raw","rb"))) {
		cout << "Cannot open file: " << "Hillary.raw" <<endl;
		exit(1);
	}
	fread(Imagedata2, sizeof(unsigned char), Length2*Width2*BytesPerPixel, file);
	fclose(file);

	if (!(file=fopen("Trump.raw","rb"))) {
		cout << "Cannot open file: " << "Trump.raw" <<endl;
		exit(1);
	}
	fread(Imagedata3, sizeof(unsigned char), Length3*Width3*BytesPerPixel, file);
	fclose(file);


	int x[16] = {0}, y[16] = {0};
/*********************************** coordinates of Hillary corners in piece image *************************/
	bool break_flag = true;
	for(int i=0; i<250&&break_flag; i++)
		for(int j=0; j<250&&break_flag; j++)
		{
			if((Imagedata1[i][j][0]!=255)||(Imagedata1[i][j][1]!=255)||(Imagedata1[i][j][2]!=255))
			{
				break_flag = false;
				x[0] = j;
				y[0] = i;
			}
		}

	break_flag = true;
	for(int j=249; j>=0&&break_flag; j--)
		for(int i=0; i<250&&break_flag; i++)
		{
			if((Imagedata1[i][j][0]!=255)||(Imagedata1[i][j][1]!=255)||(Imagedata1[i][j][2]!=255))
			{
				break_flag = false;
				x[1] = j;
				y[1] = i;
			}
		}

	break_flag = true;
	for(int i=249; i>=0&&break_flag; i--)
		for(int j=249; j>=0&&break_flag; j--)
		{
			if((Imagedata1[i][j][0]!=255)||(Imagedata1[i][j][1]!=255)||(Imagedata1[i][j][2]!=255))
			{
				break_flag = false;
				x[2] = j;
				y[2] = i;
			}
		}

	break_flag = true;
	for(int j=0; j<250&&break_flag; j++)
		for(int i=249; i>=0&&break_flag; i--)
		{
			if((Imagedata1[i][j][0]!=255)||(Imagedata1[i][j][1]!=255)||(Imagedata1[i][j][2]!=255))
			{
				break_flag = false;
				x[3] = j;
				y[3] = i;
			}
		}
/*********************************** coordinates of Trump corners in piece image *************************/
	break_flag = true;
	for(int i=250; i<500&&break_flag; i++)
		for(int j=499; j>249&&break_flag; j--)
		{
			if((Imagedata1[i][j][0]!=255)||(Imagedata1[i][j][1]!=255)||(Imagedata1[i][j][2]!=255))
			{
				break_flag = false;
				x[4] = j;
				y[4] = i;
			}
		}

	break_flag = true;
	for(int j=499; j>249&&break_flag; j--)
		for(int i=499; i>249&&break_flag; i--)
		{
			if((Imagedata1[i][j][0]!=255)||(Imagedata1[i][j][1]!=255)||(Imagedata1[i][j][2]!=255))
			{
				break_flag = false;
				x[5] = j;
				y[5] = i;
			}
		}

	break_flag = true;
	for(int i=499; i>249&&break_flag; i--)
		for(int j=250; j<500&&break_flag; j++)
		{
			if((Imagedata1[i][j][0]!=255)||(Imagedata1[i][j][1]!=255)||(Imagedata1[i][j][2]!=255))
			{
				break_flag = false;
				x[6] = j;
				y[6] = i;
			}
		}

	break_flag = true;
	for(int j=250; j<500&&break_flag; j++)
		for(int i=250; i<500&&break_flag; i++)
		{
			if((Imagedata1[i][j][0]!=255)||(Imagedata1[i][j][1]!=255)||(Imagedata1[i][j][2]!=255))
			{
				break_flag = false;
				x[7] = j;
				y[7] = i;
			}
		}
/*********************************** coordinates of holes in Hillary image *******************************/
	break_flag = true;
	for(int i=0; i<512&&break_flag; i++)
		for(int j=0; j<512&&break_flag; j++)
		{
			if((Imagedata2[i][j][0]==255)&&(Imagedata2[i][j][1]==255)&&(Imagedata2[i][j][2]==255))
			{
				break_flag = false;
				x[8] = j;
				y[8] = i;
			}
		}

	break_flag = true;
	for(int j=511; j>=0&&break_flag; j--)
		for(int i=0; i<512&&break_flag; i++)
		{
			if((Imagedata2[i][j][0]==255)&&(Imagedata2[i][j][1]==255)&&(Imagedata2[i][j][2]==255))
			{
				break_flag = false;
				x[9] = j;
				y[9] = i;
			}
		}

	break_flag = true;
	for(int i=511; i>=0&&break_flag; i--)
		for(int j=511; j>=0&&break_flag; j--)
		{
			if((Imagedata2[i][j][0]==255)&&(Imagedata2[i][j][1]==255)&&(Imagedata2[i][j][2]==255))
			{
				break_flag = false;
				x[10] = j;
				y[10] = i;
			}
		}

	break_flag = true;
	for(int j=0; j<512&&break_flag; j++)
		for(int i=511; i>=0&&break_flag; i--)
		{
			if((Imagedata2[i][j][0]==255)&&(Imagedata2[i][j][1]==255)&&(Imagedata2[i][j][2]==255))
			{
				break_flag = false;
				x[11] = j;
				y[11] = i;
			}
		}
/*********************************** coordinates of holes in Hillary image *******************************/
	break_flag = true;
	for(int i=0; i<512&&break_flag; i++)
		for(int j=0; j<512&&break_flag; j++)
		{
			if((Imagedata3[i][j][0]==255)&&(Imagedata3[i][j][1]==255)&&(Imagedata3[i][j][2]==255))
			{
				break_flag = false;
				x[12] = j;
				y[12] = i;
			}
		}

	break_flag = true;
	for(int j=511; j>=0&&break_flag; j--)
		for(int i=0; i<512&&break_flag; i++)
		{
			if((Imagedata3[i][j][0]==255)&&(Imagedata3[i][j][1]==255)&&(Imagedata3[i][j][2]==255))
			{
				break_flag = false;
				x[13] = j;
				y[13] = i;
			}
		}

	break_flag = true;
	for(int i=511; i>=0&&break_flag; i--)
		for(int j=511; j>=0&&break_flag; j--)
		{
			if((Imagedata3[i][j][0]==255)&&(Imagedata3[i][j][1]==255)&&(Imagedata3[i][j][2]==255))
			{
				break_flag = false;
				x[14] = j;
				y[14] = i;
			}
		}

	break_flag = true;
	for(int j=0; j<512&&break_flag; j++)
		for(int i=511; i>=0&&break_flag; i--)
		{
			if((Imagedata3[i][j][0]==255)&&(Imagedata3[i][j][1]==255)&&(Imagedata3[i][j][2]==255))
			{
				break_flag = false;
				x[15] = j;
				y[15] = i;
			}
		}

	for(int i=0; i<16; i++)
		cout << x[i] << "," << y[i] <<endl;


	int warping_x=0, warping_y=0;

//t1=[1.4646,-0.3939,-104.2020;0.3939,1.4545,-207.5152;0.0000,0.0000,1.0000]
	for(int i=135; i<235; i++)
		for(int j=i+38; j<273; j++)
			for(int k=0; k<BytesPerPixel; k++)
			{
					warping_x = 1.4646*j-0.3939*i-104.2020;
					warping_y = 0.3939*j+1.4545*i-207.5152;
					Imagedata2[i][j][k] = Imagedata1[warping_y][warping_x][k];
			}
//t2=[1.4646,-0.3939,-104.2020;0.3838,1.4646,-207.1313;0,-0.0000,1.0000]
	for(int i=135; i<235; i++)
		for(int j=173; j<i+39; j++)
			for(int k=0; k<BytesPerPixel; k++)
			{
					warping_x = 1.4646*j-0.3939*i-104.2020;
					warping_y = 0.3838*j+1.4646*i-207.1313;
					Imagedata2[i][j][k] = Imagedata1[warping_y][warping_x][k];
			}
//t3=[-0.0606,0.7576,139.0909;-0.7576,-0.0606,508.7879;0.0000,0,1.0000]
	for(int i=236; i<336; i++)
		for(int j=i-73; j<263; j++)
			for(int k=0; k<BytesPerPixel; k++)
			{
					warping_x = -0.0606*j+0.7576*i+139.0909;
					warping_y = -0.7576*j-0.0606*i+508.7879;
					Imagedata3[i][j][k] = Imagedata1[warping_y][warping_x][k];
			}			
//t4=[-0.0606,0.7576,139.0909;-0.7475,-0.0707,509.5253;-0.0000,0.0000,1.0000]
	for(int i=236; i<336; i++)
		for(int j=163; j<i-72; j++)
			for(int k=0; k<BytesPerPixel; k++)
			{
					warping_x = -0.0606*j+0.7576*i+139.0909;
					warping_y = -0.7475*j-0.0707*i+509.5253;
					Imagedata3[i][j][k] = Imagedata1[warping_y][warping_x][k];
			}

	for(int i=135; i<235; i++)
		for(int j=173; j<273; j++)
		{
			if(Imagedata2[i][j][0]>180&&Imagedata2[i][j][1]>180&&Imagedata2[i][j][2]>180)
			{
//				Imagedata2[i][j][0] = (1/9)*(Imagedata2[i-1][j-1][0]+Imagedata2[i-1][j][0]+Imagedata2[i-1][j+1][0]+Imagedata2[i][j-1][0]+Imagedata2[i][j][0]+Imagedata2[i][j+1][0]+Imagedata2[i+1][j-1][0]+Imagedata2[i+1][j][0]+Imagedata2[i+1][j+1][0]);
//				Imagedata2[i][j][1] = (1/9)*(Imagedata2[i-1][j-1][1]+Imagedata2[i-1][j][1]+Imagedata2[i-1][j+1][1]+Imagedata2[i][j-1][1]+Imagedata2[i][j][1]+Imagedata2[i][j+1][1]+Imagedata2[i+1][j-1][1]+Imagedata2[i+1][j][1]+Imagedata2[i+1][j+1][1]);
//				Imagedata2[i][j][2] = (1/9)*(Imagedata2[i-1][j-1][2]+Imagedata2[i-1][j][2]+Imagedata2[i-1][j+1][2]+Imagedata2[i][j-1][2]+Imagedata2[i][j][2]+Imagedata2[i][j+1][2]+Imagedata2[i+1][j-1][2]+Imagedata2[i+1][j][2]+Imagedata2[i+1][j+1][2]);
				Imagedata2[i][j][0] = Imagedata2[i-1][j-1][0];
				Imagedata2[i][j][1] = Imagedata2[i-1][j-1][1];
				Imagedata2[i][j][2] = Imagedata2[i-1][j-1][2];
			}
		}

	for(int i=236; i<336; i++)
		for(int j=163; j<263; j++)
		{
			if(Imagedata3[i][j][0]>180&&Imagedata3[i][j][1]>150&&Imagedata3[i][j][2]>130)
			{
				Imagedata3[i][j][0] = Imagedata3[i-1][j-1][0];
				Imagedata3[i][j][1] = Imagedata3[i-1][j-1][1];
				Imagedata3[i][j][2] = Imagedata3[i-1][j-1][2];
			}
		}



	if (!(file=fopen("Hillary_warping.raw","wb"))) {
		cout << "Cannot open file: " << "Hillary_warping.raw" << endl;
		exit(1);
	}
	fwrite(Imagedata2, sizeof(unsigned char), Length2*Width2*BytesPerPixel, file);
	fclose(file);

	if (!(file=fopen("Trump_warping.raw","wb"))) {
		cout << "Cannot open file: " << "Trump_warping.raw" << endl;
		exit(1);
	}
	fwrite(Imagedata3, sizeof(unsigned char), Length3*Width3*BytesPerPixel, file);
	fclose(file);

	return 0;
}
