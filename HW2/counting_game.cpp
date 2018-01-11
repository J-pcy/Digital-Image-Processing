/*************************************************************************
 > EE569 Homework Assignment #2
 > Date:     February 24, 2017
 > Author:   Chenyu Peng
 > ID:       3498-8893-91
 > email:    chenyupe@usc.edu

 > Compiled on OS X with gcc
 > Input: g++ -o counting_game counting_game.cpp
 		  ./counting_game board.raw 480 480
 ************************************************************************/

#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <cmath>

#define pi 3.141592653

using namespace std;

unsigned char shrinking[58][8] = {{0,0,255,0,0,0,0,0},{255,0,0,0,0,0,0,0},{0,0,0,0,0,255,0,0},{0,0,0,0,0,0,0,255},                                                 //s_bond1
								{0,0,0,0,255,0,0,0},{0,255,0,0,0,0,0,0},{0,0,0,255,0,0,0,0},{0,0,0,0,0,0,255,0},                                                   //s_bond2
								{0,0,255,0,255,0,0,0},{0,255,255,0,0,0,0,0},{255,255,0,0,0,0,0,0},{255,0,0,255,0,0,0,0},                                           //s_bond3
								{0,0,0,255,0,255,0,0},{0,0,0,0,0,255,255,0},{0,0,0,0,0,0,255,255},{0,0,0,0,255,0,0,255},
								{0,0,255,0,255,0,0,255},{255,255,255,0,0,0,0,0},{255,0,0,255,0,255,0,0},{0,0,0,0,0,255,255,255},                                   //stk_bond4
								{255,255,0,0,255,0,0,0},{0,255,0,0,255,0,0,255},{0,255,255,255,0,0,0,0},{0,0,255,0,255,0,255,0},                                   //st_bond5
								{0,255,255,0,255,0,0,0},{255,255,0,255,0,0,0,0},{0,0,0,255,0,255,255,0},{0,0,0,0,255,0,255,255},                                   //st_bond5
								{255,255,0,0,255,0,0,255},{0,255,255,255,0,255,0,0},                                                                               //st_bond6
								{255,255,255,0,255,0,0,0},{0,255,255,0,255,0,0,255},{255,255,255,255,0,0,0,0},{255,255,0,255,0,255,0,0},                           //stk_bond6
								{255,0,0,255,0,255,255,0},{0,0,0,255,0,255,255,255},{0,0,0,0,255,255,255,255},{0,0,255,0,255,0,255,255},
								{255,255,255,0,255,0,0,255},{255,255,255,255,0,255,0,0},{255,0,0,255,0,255,255,255},{0,0,255,0,255,255,255,255},                   //stk_bond7
								{0,255,255,0,255,0,255,255},{255,255,255,255,255,0,0,0},{255,255,0,255,0,255,255,0},{0,0,0,255,255,255,255,255},                   //stk_bond8
								{255,255,255,0,255,0,255,255},{0,255,255,0,255,255,255,255},{255,255,255,255,255,255,0,0},{255,255,255,255,255,0,0,255},           //stk_bond9
								{255,255,255,255,0,255,255,0},{255,255,0,255,0,255,255,255},{255,0,0,255,255,255,255,255},{0,0,255,255,255,255,255,255},
								{255,255,255,0,255,255,255,255},{255,255,255,255,255,255,0,255},{255,255,255,255,0,255,255,255},{255,0,255,255,255,255,255,255}};  //stk_bond10

unsigned char shrinking_uncond[200][8] = {{0,0,255,0,0,0,0,0},{255,0,0,0,0,0,0,0},                                                                                 //1
										{0,0,0,0,0,0,255,0},{0,0,0,0,255,0,0,0},                                                                                   //2
										{0,0,255,0,255,0,0,0},{0,255,255,0,0,0,0,0},{255,255,0,0,0,0,0,0},{255,0,0,255,0,0,0,0},                                   //3
										{0,0,0,255,0,255,0,0},{0,0,0,0,0,255,255,0},{0,0,0,0,0,0,255,255},{0,0,0,0,255,0,0,255},
										{0,255,255,255,0,0,0,0},{255,255,0,0,255,0,0,0},{0,255,0,0,255,0,0,255},{0,0,255,0,255,0,255,0},                           //4
										{0,0,255,0,255,255,0,0},{255,0,0,255,0,0,0,255},{0,0,255,0,0,255,255,0},{255,0,0,0,0,0,255,255},                           //5
										{0,255,255,0,0,255,0,0},{255,255,0,0,0,0,0,255},{0,0,255,255,0,255,0,0},{255,0,0,0,255,0,0,255},
										{255,255,0,255,0,0,0,0},{255,255,0,255,0,0,0,255},{255,255,0,255,0,0,255,0},{255,255,0,255,0,0,255,255},                   //6
										{255,255,0,255,0,255,0,0},{255,255,0,255,0,255,0,255},{255,255,0,255,0,255,255,0},{255,255,0,255,0,255,255,255},
										{255,255,0,255,255,0,0,0},{255,255,0,255,255,0,0,255},{255,255,0,255,255,0,255,0},{255,255,0,255,255,0,255,255},
										{255,255,0,255,255,255,0,0},{255,255,0,255,255,255,0,255},{255,255,0,255,255,255,255,0},{255,255,0,255,255,255,255,255},
										{255,255,255,255,0,0,0,0},{255,255,255,255,0,0,0,255},{255,255,255,255,0,0,255,0},{255,255,255,255,0,0,255,255},
										{255,255,255,255,0,255,0,0},{255,255,255,255,0,255,0,255},{255,255,255,255,0,255,255,0},{255,255,255,255,0,255,255,255},
										{255,255,255,255,255,0,0,0},{255,255,255,255,255,0,0,255},{255,255,255,255,255,0,255,0},{255,255,255,255,255,0,255,255},
										{255,255,255,255,255,255,0,0},{255,255,255,255,255,255,0,255},{255,255,255,255,255,255,255,0},{255,255,255,255,255,255,255,255},
										{0,255,0,255,255,0,0,0},{0,255,0,255,255,0,0,0},{0,0,0,255,255,0,255,0},{0,0,0,255,255,0,255,0},                          //7
										{0,255,0,255,255,255,0,0},{0,255,0,255,255,0,0,255},{0,0,0,255,255,0,255,255},{0,0,0,255,255,255,255,0},
										{255,255,0,255,255,0,0,0},{0,255,255,255,255,0,0,0},{0,0,255,255,255,0,255,0},{255,0,0,255,255,0,255,0},
										{255,255,0,255,255,255,0,0},{0,255,255,255,255,0,0,255},{0,0,255,255,255,0,255,255},{255,0,0,255,255,255,255,0},
										{0,255,0,255,0,0,255,0},{0,255,0,255,0,0,255,0},{0,255,0,0,255,0,255,0},{0,255,0,0,255,0,255,0},
										{0,255,255,255,0,0,255,0},{0,255,0,255,0,0,255,255},{0,255,0,0,255,0,255,255},{0,255,255,0,255,0,255,0},
										{255,255,0,255,0,0,255,0},{0,255,0,255,0,255,255,0},{0,255,0,0,255,255,255,0},{255,255,0,0,255,0,255,0},
										{255,255,255,255,0,0,255,0},{0,255,0,255,0,255,255,255},{0,255,0,0,255,255,255,255},{255,255,255,0,255,0,255,0},
										{255,0,255,0,0,0,0,255},{255,0,0,0,0,255,0,255},{0,0,255,0,0,255,0,255},{0,0,255,0,0,255,0,255},                          //8
										{255,0,255,0,0,0,255,0},{255,0,0,0,255,255,0,0},{0,255,0,0,0,255,0,255},{0,0,255,255,0,0,0,255},
										{255,0,255,0,0,255,0,0},{255,0,255,0,0,255,0,0},{255,0,0,0,0,255,0,255},{255,0,255,0,0,0,0,255},
										{255,0,255,0,255,0,0,255},{255,0,0,0,0,255,255,255},{0,0,255,0,0,255,255,255},{0,0,255,0,0,255,255,255},
										{255,0,255,0,255,0,255,0},{255,0,0,0,255,255,255,0},{0,255,0,0,0,255,255,255},{0,0,255,255,0,0,255,255},
										{255,0,255,0,255,255,0,0},{255,0,255,0,0,255,255,0},{255,0,0,0,0,255,255,255},{255,0,255,0,0,0,255,255},
										{255,0,255,255,0,0,0,255},{255,0,0,255,0,255,0,255},{0,0,255,0,255,255,0,255},{0,0,255,0,255,255,0,255},
										{255,0,255,255,0,0,255,0},{255,0,0,255,255,255,0,0},{0,255,0,0,255,255,0,255},{0,0,255,255,255,0,0,255},
										{255,0,255,255,0,255,0,0},{255,0,255,255,0,255,0,0},{255,0,0,0,255,255,0,255},{255,0,255,0,255,0,0,255},
										{255,0,255,255,255,0,0,255},{255,0,0,255,0,255,255,255},{0,0,255,0,255,255,255,255},{0,0,255,0,255,255,255,255},
										{255,0,255,255,255,0,255,0},{255,0,0,255,255,255,255,0},{0,255,0,0,255,255,255,255},{0,0,255,255,255,0,255,255},
										{255,0,255,255,255,255,0,0},{255,0,255,255,0,255,255,0},{255,0,0,0,255,255,255,255},{255,0,255,0,255,0,255,255},
										{255,255,255,0,0,0,0,255},{255,255,0,0,0,255,0,255},{0,0,255,255,0,255,0,255},{0,255,255,0,0,255,0,255},
										{255,255,255,0,0,0,255,0},{255,255,0,0,255,255,0,0},{0,255,0,255,0,255,0,255},{0,255,255,255,0,0,0,255},
										{255,255,255,0,0,255,0,0},{255,255,255,0,0,255,0,0},{255,0,0,255,0,255,0,255},{255,255,255,0,0,0,0,255},
										{255,255,255,0,255,0,0,255},{255,255,0,0,0,255,255,255},{0,0,255,255,0,255,255,255},{0,255,255,0,0,255,255,255},
										{255,255,255,0,255,0,255,0},{255,255,0,0,255,255,255,0},{0,255,0,255,0,255,255,255},{0,255,255,255,0,0,255,255},
										{255,255,255,0,255,255,0,0},{255,255,255,0,0,255,255,0},{255,0,0,255,0,255,255,255},{255,255,255,0,0,0,255,255},
										{255,255,255,255,0,0,0,255},{255,255,0,255,0,255,0,255},{0,0,255,255,255,255,0,255},{0,255,255,0,255,255,0,255},
										{255,255,255,255,0,0,255,0},{255,255,0,255,255,255,0,0},{0,255,0,255,255,255,0,255},{0,255,255,255,255,0,0,255},
										{255,255,255,255,0,255,0,0},{255,255,255,255,0,255,0,0},{255,0,0,255,255,255,0,255},{255,255,255,0,255,0,0,255},
										{255,255,255,255,255,0,0,255},{255,255,0,255,0,255,255,255},{0,0,255,255,255,255,255,255},{0,255,255,0,255,255,255,255},
										{255,255,255,255,255,0,255,0},{255,255,0,255,255,255,255,0},{0,255,0,255,255,255,255,255},{0,255,255,255,255,0,255,255},
										{255,255,255,255,255,255,0,0},{255,255,255,255,0,255,255,0},{255,0,0,255,255,255,255,255},{255,255,255,0,255,0,255,255},
										{0,255,0,0,255,255,0,0},{0,255,0,255,0,0,0,255},{0,0,255,255,0,0,255,0},{255,0,0,0,255,0,255,0},                          //9
										{0,255,0,0,255,255,0,255},{0,255,0,255,0,255,0,255},{0,0,255,255,0,0,255,255},{255,0,0,0,255,255,255,0},
										{255,255,0,0,255,255,0,0},{0,255,255,255,0,0,0,255},{255,0,255,255,0,0,255,0},{255,0,255,0,255,0,255,0},
										{255,255,0,0,255,255,0,255},{0,255,255,255,0,255,0,255},{255,0,255,255,0,0,255,255},{255,0,255,0,255,255,255,0}};

unsigned char count_holes[8] = {0,0,0,0,0,0,0,0};

int main(int argc, char *argv[])
{
	FILE *file;
	int BytesPerPixel = 1;
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


	unsigned char ImageTrans1[Width+2][Length+2][BytesPerPixel];
	unsigned char ImageTrans2[Width][Length][BytesPerPixel];
	unsigned char ImageTrans3[Width+2][Length+2][BytesPerPixel];
	unsigned char ImageTrans4[Width][Length][BytesPerPixel];
	unsigned char ImageTrans5[Width][Length][BytesPerPixel];
	unsigned char ImageTrans6[Width][Length][BytesPerPixel];
	unsigned char ImageTrans7[Width][Length][BytesPerPixel];
	unsigned char ImageTrans8[Width][Length][BytesPerPixel];
	unsigned char ImageTrans9[Width][Length][BytesPerPixel];

	memset(ImageTrans1,255,sizeof(ImageTrans1));
	
	for(int i=0; i<Width; i++)
		for(int j=0; j<Length; j++)
			for(int k=0; k<BytesPerPixel; k++)
			{
				if(Imagedata[i][j][k]==0)
				{
					ImageTrans1[i+1][j+1][k] = 255;
					ImageTrans6[i][j][k] = 255;
				}
				else if(Imagedata[i][j][k]==255)
				{
					ImageTrans1[i+1][j+1][k] = 0;
					ImageTrans6[i][j][k] = 0;
				}
			}

	unsigned char array_temp[8];
	bool break_flag_1 = true;
	bool break_flag_2 = true;
	bool break_flag_3 = false;
	bool break_flag_4 = true;
	bool break_flag_5 = true;
	bool break_flag_6 = true;

/********************************************number of holes***********************************************/
//	while(!break_flag_3)
//	{
	for(int p=0; p<15; p++)
	{
		memset(ImageTrans2,0,sizeof(ImageTrans2));
		for(int i=0; i<Width; i++)
			for(int j=0; j<Length; j++)
				for(int k=0; k<BytesPerPixel; k++)
				{
					if(ImageTrans1[i+1][j+1][k]==255)
					{
						break_flag_2 = true;
						array_temp[0] = ImageTrans1[i][j][k];
						array_temp[1] = ImageTrans1[i][j+1][k];
						array_temp[2] = ImageTrans1[i][j+2][k];
						array_temp[3] = ImageTrans1[i+1][j][k];
						array_temp[4] = ImageTrans1[i+1][j+2][k];
						array_temp[5] = ImageTrans1[i+2][j][k];
						array_temp[6] = ImageTrans1[i+2][j+1][k];
						array_temp[7] = ImageTrans1[i+2][j+2][k];
						for(int a=0; a<58&&break_flag_2; a++)
						{
							break_flag_1 = true;
							for(int b=0; b<8&&break_flag_1; b++)
							{
								if(array_temp[b]!=shrinking[a][b])
									break_flag_1 = false;
							}
							if(break_flag_1)
							{
								ImageTrans2[i][j][k] = 255;
								break_flag_2 = false;
							}
							else
								ImageTrans2[i][j][k] = 0;
						}
					}
				}

	for(int i=0; i<Width; i++)
		for(int j=0; j<Length; j++)
			for(int k=0; k<BytesPerPixel; k++)
				ImageTrans3[i+1][j+1][k] = ImageTrans2[i][j][k];

		for(int i=0; i<Width; i++)
			for(int j=0; j<Length; j++)
				for(int k=0; k<BytesPerPixel; k++)
				{
					if(ImageTrans3[i+1][j+1][k]==255)
					{
						break_flag_5 = true;
						array_temp[0] = ImageTrans3[i][j][k];
						array_temp[1] = ImageTrans3[i][j+1][k];
						array_temp[2] = ImageTrans3[i][j+2][k];
						array_temp[3] = ImageTrans3[i+1][j][k];
						array_temp[4] = ImageTrans3[i+1][j+2][k];
						array_temp[5] = ImageTrans3[i+2][j][k];
						array_temp[6] = ImageTrans3[i+2][j+1][k];
						array_temp[7] = ImageTrans3[i+2][j+2][k];
						for(int a=0; a<200&&break_flag_5; a++)
						{
							break_flag_4 = true;
							for(int b=0; b<8&&break_flag_4; b++)
							{
								if(array_temp[b]!=shrinking_uncond[a][b])
									break_flag_4 = false;
							}
							if(break_flag_4)
							{
								ImageTrans1[i+1][j+1][k] = 255;
								break_flag_5 = false;
							}
							else
							{
								ImageTrans1[i+1][j+1][k] = 0;
							}
						}
					}
				}
	}

	int holes_num = 0;
	for(int i=0; i<Width; i++)
		for(int j=0; j<Length; j++)
			for(int k=0; k<BytesPerPixel; k++)
			{
				ImageTrans4[i][j][k] = ImageTrans1[i+1][j+1][k];
				if(ImageTrans1[i+1][j+1][k]==255)
				{
					break_flag_3 = true;
					array_temp[0] = ImageTrans1[i][j][k];
					array_temp[1] = ImageTrans1[i][j+1][k];
					array_temp[2] = ImageTrans1[i][j+2][k];
					array_temp[3] = ImageTrans1[i+1][j][k];
					array_temp[4] = ImageTrans1[i+1][j+2][k];
					array_temp[5] = ImageTrans1[i+2][j][k];
					array_temp[6] = ImageTrans1[i+2][j+1][k];
					array_temp[7] = ImageTrans1[i+2][j+2][k];
					for(int a=0; a<8&&break_flag_3; a++)
					{
						if(array_temp[a]!=count_holes[a])
							break_flag_3 = false;
					}
					if(break_flag_3)
					{
						holes_num++;
						ImageTrans5[i][j][k] = ImageTrans1[i+1][j+1][k];
					}
				}
			}

/********************************************hole-filling algorithm***********************************************/
	for(int p=0; p<15; p++)
	{
		for(int i=0; i<Width; i++)
			for(int j=0; j<Length; j++)
				for(int k=0; k<BytesPerPixel; k++)
				{
					if(ImageTrans5[i][j][k]==255)
					{
						ImageTrans9[i-1][j-1][k] = 255;
						ImageTrans9[i-1][j][k] = 255;
						ImageTrans9[i-1][j+1][k] = 255;
						ImageTrans9[i][j-1][k] = 255;
						ImageTrans9[i][j][k] = 255;
						ImageTrans9[i][j+1][k] = 255;
						ImageTrans9[i+1][j-1][k] = 255;
						ImageTrans9[i+1][j][k] = 255;
						ImageTrans9[i+1][j+1][k] = 255;
					}
				}

		for(int i=0; i<Width; i++)
			for(int j=0; j<Length; j++)
				for(int k=0; k<BytesPerPixel; k++)
					ImageTrans5[i][j][k] = ImageTrans9[i][j][k];

		for(int i=0; i<Width; i++)
			for(int j=0; j<Length; j++)
				for(int k=0; k<BytesPerPixel; k++)
				{
					if(ImageTrans5[i][j][k]&&ImageTrans6[i][j][k])
						ImageTrans7[i][j][k] = 255;
				}

		break_flag_6 = true;
		for(int i=0; i<Width&&break_flag_6; i++)
			for(int j=0; j<Length&&break_flag_6; j++)
				for(int k=0; k<BytesPerPixel; k++)
				{
					if(ImageTrans5[i][j][k]!=ImageTrans7[i][j][k])
						break_flag_6 = false;
				}
	}

	for(int i=0; i<Width; i++)
		for(int j=0; j<Length; j++)
			for(int k=0; k<BytesPerPixel; k++)
			{
				if(ImageTrans5[i][j][k]||Imagedata[i][j][k])
					ImageTrans8[i][j][k] = 255;
				else
					ImageTrans8[i][j][k] = 0;
			}

/*****************************************number of white objects*******************************************/
	unsigned char ImageTrans11[Width+2][Length+2][BytesPerPixel];
	unsigned char ImageTrans12[Width][Length][BytesPerPixel];
	unsigned char ImageTrans13[Width+2][Length+2][BytesPerPixel];
	unsigned char ImageTrans14[Width][Length][BytesPerPixel];

	for(int i=0; i<Width; i++)
		for(int j=0; j<Length; j++)
			for(int k=0; k<BytesPerPixel; k++)
				ImageTrans11[i+1][j+1][k] = ImageTrans8[i][j][k];

	unsigned char array_temp1[8];
	bool break_flag_11 = true;
	bool break_flag_12 = true;
	bool break_flag_13 = false;
	bool break_flag_14 = true;
	bool break_flag_15 = true;

	while(!break_flag_13)
	{
		memset(ImageTrans12,0,sizeof(ImageTrans12));
		for(int i=0; i<Width; i++)
			for(int j=0; j<Length; j++)
				for(int k=0; k<BytesPerPixel; k++)
				{
					if(ImageTrans11[i+1][j+1][k]==255)
					{
						break_flag_12 = true;
						array_temp1[0] = ImageTrans11[i][j][k];
						array_temp1[1] = ImageTrans11[i][j+1][k];
						array_temp1[2] = ImageTrans11[i][j+2][k];
						array_temp1[3] = ImageTrans11[i+1][j][k];
						array_temp1[4] = ImageTrans11[i+1][j+2][k];
						array_temp1[5] = ImageTrans11[i+2][j][k];
						array_temp1[6] = ImageTrans11[i+2][j+1][k];
						array_temp1[7] = ImageTrans11[i+2][j+2][k];
						for(int a=0; a<58&&break_flag_12; a++)
						{
							break_flag_11 = true;
							for(int b=0; b<8&&break_flag_11; b++)
							{
								if(array_temp1[b]!=shrinking[a][b])
									break_flag_11 = false;
							}
							if(break_flag_11)
							{
								ImageTrans12[i][j][k] = 255;
								break_flag_12 = false;
							}
							else
								ImageTrans12[i][j][k] = 0;
						}
					}
				}

	for(int i=0; i<Width; i++)
		for(int j=0; j<Length; j++)
			for(int k=0; k<BytesPerPixel; k++)
				ImageTrans13[i+1][j+1][k] = ImageTrans12[i][j][k];

		for(int i=0; i<Width; i++)
			for(int j=0; j<Length; j++)
				for(int k=0; k<BytesPerPixel; k++)
				{
					if(ImageTrans13[i+1][j+1][k]==255)
					{
						break_flag_15 = true;
						array_temp1[0] = ImageTrans13[i][j][k];
						array_temp1[1] = ImageTrans13[i][j+1][k];
						array_temp1[2] = ImageTrans13[i][j+2][k];
						array_temp1[3] = ImageTrans13[i+1][j][k];
						array_temp1[4] = ImageTrans13[i+1][j+2][k];
						array_temp1[5] = ImageTrans13[i+2][j][k];
						array_temp1[6] = ImageTrans13[i+2][j+1][k];
						array_temp1[7] = ImageTrans13[i+2][j+2][k];
						for(int a=0; a<200&&break_flag_15; a++)
						{
							break_flag_14 = true;
							for(int b=0; b<8&&break_flag_14; b++)
							{
								if(array_temp1[b]!=shrinking_uncond[a][b])
									break_flag_14 = false;
							}
							if(break_flag_14)
							{
								ImageTrans11[i+1][j+1][k] = 255;
								break_flag_15 = false;
							}
							else
							{
								ImageTrans11[i+1][j+1][k] = 0;
							}
						}
					}
				}

		break_flag_13 = true;
		for(int i=0; i<Width&&break_flag_13; i++)
			for(int j=0; j<Length&&break_flag_13; j++)
				for(int k=0; k<BytesPerPixel; k++)
				{
					if(ImageTrans12[i][j][k]==255)
						break_flag_13 = false;
				}
	}

	int objects_num = 0;
	for(int i=0; i<Width; i++)
		for(int j=0; j<Length; j++)
			for(int k=0; k<BytesPerPixel; k++)
			{
				ImageTrans14[i][j][k] = ImageTrans11[i+1][j+1][k];
				if(ImageTrans11[i+1][j+1][k]==255)
					objects_num++;
			}

/********************************************number of white squares and circles*************************************/
	unsigned char ImageTrans21[Width+2][Length+2][BytesPerPixel];
	unsigned char ImageTrans22[Width][Length][BytesPerPixel];

	for(int i=0; i<Width; i++)
		for(int j=0; j<Length; j++)
			for(int k=0; k<BytesPerPixel; k++)
				ImageTrans21[i+1][j+1][k] = ImageTrans8[i][j][k];

	unsigned char array_temp_2[8];
	bool break_flag_21 = true;
	bool break_flag_22 = true;

	for(int i=0; i<Width; i++)
		for(int j=0; j<Length; j++)
			for(int k=0; k<BytesPerPixel; k++)
			{
				if(ImageTrans21[i+1][j+1][k]==255)
				{
					break_flag_22 = true;
					array_temp_2[0] = ImageTrans21[i][j][k];
					array_temp_2[1] = ImageTrans21[i][j+1][k];
					array_temp_2[2] = ImageTrans21[i][j+2][k];
					array_temp_2[3] = ImageTrans21[i+1][j][k];
					array_temp_2[4] = ImageTrans21[i+1][j+2][k];
					array_temp_2[5] = ImageTrans21[i+2][j][k];
					array_temp_2[6] = ImageTrans21[i+2][j+1][k];
					array_temp_2[7] = ImageTrans21[i+2][j+2][k];
					for(int a=0; a<58&&break_flag_22; a++)
					{
						break_flag_21 = true;
						for(int b=0; b<8&&break_flag_21; b++)
						{
							if(array_temp_2[b]!=shrinking[a][b])
								break_flag_21 = false;
						}
						if(break_flag_21)
						{
							ImageTrans22[i][j][k] = 255;
							break_flag_22 = false;
						}
						else
							ImageTrans22[i][j][k] = 0;
					}
				}
			}

	int distance[1000]={0};
	int flag_1 = 0, pixel_num=0;
	int squares_num=0, circles_num=0;
	for(int i=0; i<Width; i++)
		for(int j=0; j<Length; j++)
			for(int k=0; k<BytesPerPixel; k++)
			{

				if(ImageTrans14[i][j][k]==255)
				{
					int start_i=0,end_i=0, start_j=0, end_j=0;
					if(i-80<0)
						start_i=0;
					else
						start_i=i-80;
					if(j-80<0)
						start_j=0;
					else
						start_j=j-80;
					if(i+80>480)
						end_i=480;
					else
						end_i=i+80;
					if(j+80>480)
						end_j=480;
					else
						end_j=j+80;

					flag_1=0;
					for(int a=start_i; a<end_i; a++)
						for(int b=start_j; b<end_j; b++)
							for(int c=0; c<BytesPerPixel; c++)
							{
								if(ImageTrans22[a][b][c]==255)
								{
									distance[flag_1]=(a-i)*(a-i)+(b-j)*(b-j);
//									cout << a <<"," << b << "," << distance[flag_1] << endl;
									flag_1++;
								}
							}

					int min=distance[0];
					for(int a=0; a<1000; a++)
					{
						if(distance[a]<min&&distance[a])
							min = distance[a];
					}

					pixel_num=0;
					for(int a=0; a<1000; a++)
					{
						if((distance[a]<=2*min||distance[a]<=min+200)&&distance[a])
							pixel_num++;
					}
//					cout << pixel_num*pixel_num/min << endl;
					if(pixel_num*pixel_num/min<75&&pixel_num*pixel_num/min>55)
						squares_num++;
				}
			}
	circles_num=objects_num-squares_num;

/********************************************Hough Transform**********************************************/
/*
	int radius = 1;
	double radian = 0.0;
	int x=0, y=0;
	int circle[Width][Length];
	for(radius=10; radius<80; radius++)
	{
		memset(circle,0,sizeof(circle));
		for(int i=0; i<Width; i++)
			for(int j=0; j<Length; j++)
				for(int k=0; k<BytesPerPixel; k++)
				{
					if(ImageTrans22[i][j][k]==255)
					{
						for(int theta=0; theta<360; theta++)
						{
							radian = (theta*pi)/180.0;
							x = i-radius*cos(radian);
							y = j-radius*sin(radian);
							if(x>=0&&x<Width&&y>=0&&y<Length)
								circle[x][y]++;
						}
					}
				}
		int max = 0;
		for(int i=0; i<Width; i++)
			for(int j=0; j<Length; j++)
				if(circle[i][j]>max)
					max = circle[i][j];
		cout << radius << ":" << max << endl;

	}

//	for(int i=0; i<Width; i++)
//	{
//		for(int j=0; j<Length; j++)
//			cout << circle[i][j];
//		cout << endl;
//	}

	for(radius=12; radius<13; radius++)
	{
		memset(circle,0,sizeof(circle));
		for(int i=0; i<Width; i++)
			for(int j=0; j<Length; j++)
				for(int k=0; k<BytesPerPixel; k++)
				{
					if(ImageTrans22[i][j][k]==255)
					{
						for(int theta=0; theta<360; theta++)
						{
							radian = (theta*pi)/180.0;
							x = i-radius*cos(radian);
							y = j-radius*sin(radian);
							if(x>=0&&x<Width&&y>=0&&y<Length)
								circle[x][y]++;
						}
					}
				}
	}
	int max = 0;
	for(int i=0; i<Width; i++)
		for(int j=0; j<Length; j++)
			if(circle[i][j]>max)
				max = circle[i][j];
	cout << max << endl;

	unsigned char ImageTrans31[Width][Length];
	for(int i=0; i<Width; i++)
		for(int j=0; j<Length; j++)
			ImageTrans31[i][j] = 255*circle[i][j]/max;
*/
	cout << "Total number of white obiects: " << objects_num << endl;
	cout << "Total number of holes: " << holes_num << endl;
	cout << "Total number of white square obiects: " << squares_num << endl;
	cout << "Total number of white circle obiects: " << circles_num << endl;

	if (!(file=fopen("board_counting1_1.raw","wb"))) {
		cout << "Cannot open file: " << "board_counting1_1.raw" << endl;
		exit(1);
	}
	fwrite(ImageTrans8, sizeof(unsigned char), Length*Width*BytesPerPixel, file);
	fclose(file);

	if (!(file=fopen("board_counting1_2.raw","wb"))) {
		cout << "Cannot open file: " << "board_counting1_2.raw" << endl;
		exit(1);
	}
	fwrite(ImageTrans14, sizeof(unsigned char), Length*Width*BytesPerPixel, file);
	fclose(file);

	if (!(file=fopen("board_counting2.raw","wb"))) {
		cout << "Cannot open file: " << "board_counting2.raw" << endl;
		exit(1);
	}
	fwrite(ImageTrans4, sizeof(unsigned char), Length*Width*BytesPerPixel, file);
	fclose(file);

	if (!(file=fopen("board_counting3_1.raw","wb"))) {
		cout << "Cannot open file: " << "board_counting3_1.raw" << endl;
		exit(1);
	}
	fwrite(ImageTrans22, sizeof(unsigned char), Length*Width*BytesPerPixel, file);
	fclose(file);

	return 0;
}
