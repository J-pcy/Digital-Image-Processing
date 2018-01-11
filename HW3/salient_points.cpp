/*************************************************************************
 > EE569 Homework Assignment #3
 > Date:     March 24, 2017
 > Author:   Chenyu Peng
 > ID:       3498-8893-91
 > email:    chenyupe@usc.edu
 
 > Compiled on OS X with Xcode
 
 ************************************************************************/

#include<opencv2/opencv.hpp>
#include"opencv2/core/core.hpp"
#include"opencv2/features2d/features2d.hpp"
#include"opencv2/nonfree/features2d.hpp"
#include"opencv2/highgui/highgui.hpp"
#include"opencv2/nonfree/nonfree.hpp"
#include<iostream>
#include<cstdio>
#include<time.h>

using namespace std;
using namespace cv;

int extract_surffeatures(const Mat& image,vector<KeyPoint>& keypoint,Mat& descriptor)
{
 double minHessian=400;
 SurfFeatureDetector detector(minHessian);
 detector.detect(image,keypoint);
 
 if(keypoint.size()<=10)
	 return -1;

 SurfDescriptorExtractor extractor;
 extractor.compute(image,keypoint,descriptor);
 return keypoint.size();
}

int extract_siftfeatures(const Mat& image,vector<KeyPoint>& keypoint,Mat& descriptor)
{
 double minHessian=400;
 SiftFeatureDetector detector(minHessian);
 detector.detect(image,keypoint);
 if(keypoint.size()<=10)
	 return -1;

 SiftDescriptorExtractor extractor;
 extractor.compute(image,keypoint,descriptor);
 return keypoint.size();
}

int match_knnfeatures(const Mat& descriptor_src, const Mat& descriptor_temp, vector<DMatch>& good_matches)
{
 const float minratio = 8.f/9.f;

 //ptr<DescriptorMatch> matcher=DescriptorMatcher::create("BruteForce-Hamming");
 BFMatcher matcher(NORM_L2);
 vector<vector<DMatch>> knnMatches;
 matcher.knnMatch(descriptor_src,descriptor_temp,knnMatches,2);
 for(int i=0;i<knnMatches.size();i++)
 {
  const DMatch& bestMatch=knnMatches[i][0];
  const DMatch& betterMatch=knnMatches[i][1];
  float distanceRatio=bestMatch.distance/betterMatch.distance;
  if(distanceRatio<minratio)
	  good_matches.push_back(bestMatch);
 }
 return good_matches.size();
}

FILE *image;
int row = 500;
int col = 300;

int main(int argc,char** argv)
{
 clock_t start,end_read,end_getfeat,end_match;
 start=clock();
 Mat image_src,image_temp;
    uchar *raw_1 = new uchar[500 *300 * 3];
    uchar *raw_2 = new uchar[500 *300 * 3];
 //image_src=imread("convertible_1.raw");
    if (!(image = fopen("suv.raw", "rb"))) {
        cout << "Cannot open file: " << "suv.raw" << endl;
        exit(1);
    }
    fread(raw_1, sizeof(unsigned char), row*col*3, image);
    fclose(image);
    
    image_src=cv::Mat(Size(row,col), CV_8UC3, raw_1);

// image_temp=imread("suv.raw");
    if (!(image = fopen("truck.raw", "rb"))) {
        cout << "Cannot open file: " << "truck.raw" << endl;
        exit(1);
    }
    fread(raw_2, sizeof(unsigned char), row*col*3, image);
    fclose(image);
    
    image_temp=cv::Mat(Size(row,col), CV_8UC3, raw_2);
    
  if(!image_src.data||!image_temp.data)
 {
  cout<<"can not read image."<<endl;
  return -1;
 }
  end_read=clock();
 //imshow("src",image_src);
 //imshow("temp",image_temp);
  ////////////////////////////////
  vector<KeyPoint> keypoint_src,keypoint_temp;
  Mat descriptor_src,descriptor_temp;
  int num_src,num_temp;
  num_src=extract_surffeatures(image_src,keypoint_src,descriptor_src);
  num_temp=extract_surffeatures(image_temp,keypoint_temp,descriptor_temp);
//  num_src=extract_siftfeatures(image_src,keypoint_src,descriptor_src);
//  num_temp=extract_siftfeatures(image_temp,keypoint_temp,descriptor_temp);

  end_getfeat=clock();
  Mat img_keypoint1,img_keypoint2;
  drawKeypoints(image_src,keypoint_src,img_keypoint1,Scalar::all(-1),DrawMatchesFlags::DEFAULT);
  drawKeypoints(image_temp,keypoint_temp,img_keypoint2,Scalar::all(-1),DrawMatchesFlags::DEFAULT);
//  imshow("SUV_SIFT",img_keypoint1);
    imshow("SUV_SURF",img_keypoint1);
  //imwrite("SUV_SURF.jpg",img_keypoint1);
//  imshow("Truck_SIFT",img_keypoint2);
    imshow("Truck_SURF",img_keypoint2);
  //imwrite("Truck_SURF.jpg",img_keypoint2);
  waitKey(30);

    waitKey(0);
 return 0;
}
