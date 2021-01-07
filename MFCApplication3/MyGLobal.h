#pragma once
#include <iostream>  
#include <fstream>
#include <string>
#include <vector>
#include <iterator>
#include "afxwin.h"

extern double CannyThreshold1;
extern double CannyThreshold2;
extern double HoughThreshold1;
extern double HoughThreshold2;
extern double HoughThreshold3;
extern double thresholdValue;
extern double ransacDistance;

extern Mat maskImageL;
extern Mat maskImageR;
extern Mat cosImage;
extern Mat sinImage;
extern Mat eWorldL;
extern Mat eWorldR;
//extern Mat ML;
//extern Mat MR;

/*九点标定*/
#define CalibrationMethod 1//1:直接求逆   2:单目标定

/*CrossMethod=1:GetCrossPoint 
CrossMethod=2:GetCrossBasedShape 
CrossMethod=3:GetCrossBaseFastShape*/
#define CrossMethod 3

/*CrossDetectionMode=1:Sobel提取边缘
CrossDetectionMode=2:Sobel提取边缘+ransac剔除不理想点+fitline（公司版本，后续换掉）
CrossDetectionMode=3:LSD提取直线，opencvv4.10不再可用*/
#define CrossDetectionMode 2

/*SubPixelMethod=1:灰度矩亚像素算法 
SubPixelMethod=2:Zernik矩亚像素算法*/
#define SubPixelMethod 1

/*形状匹配中图像金字塔缩放指数*/
#define factor 5

#define  roiOffset 100

/*标定时旋转角度*/
#define THETA -3 * PI / 180
//#define THETA 2 * PI / 180