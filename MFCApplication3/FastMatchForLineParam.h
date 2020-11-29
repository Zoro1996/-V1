#pragma once
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/calib3d/calib3d.hpp"
#include <opencv2/imgproc/imgproc.hpp>
#include<opencv2/opencv.hpp>
#include<opencv2/core.hpp>
#include <opencv2/opencv_modules.hpp>
#include <opencv2/highgui/highgui_c.h> 
#include <fstream>
#include <string>
#include <vector>
#include<iostream>
#include <iterator>
#include <opencv2/core/utility.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/features2d.hpp>
#include <opencv2/highgui.hpp>
#include "algorithm"

using namespace std;
using namespace cv;

static constexpr const float PI = 3.1415926;

struct Gradient
{
	Point2f pt;
	float theta;
	float margin;
};

struct ShapeMatchResult
{
	Point2f massCenter;
	float theta;
};


struct Contours
{
	/*质心坐标*/
	int centerX;
	int centerY;

	/*点集*/
	vector<Point2f> pointSet;
};


struct GCBS
{
	float ka;
	float kb;
	float ma;
	float mb;
	float measure;
	float gray;
	float gradient;

	bool FLAG;

	Point2f crossPoint;

	vector<float>MeasureSet;
};


Mat LSD(Mat srcImage, bool ResizeFlag, float rate);


/*************************************************************
Function:       GetLinePoints
Description:    使用Sobel提取图像潜在直线拟合点
Input:          image:待测图像
				thresholdEdges:梯度阈值
				deltaX:待测图像在工件图像中X方向相对位置
				deltaY:待测图像在工件图像中Y方向相对位置
Return:         linePoints:直线拟合点集
**************************************************************/
vector<Point2f> GetLinePoints(Mat& image, float thresholdEdges,
	float delatX, float deltaY);


/*计算某一变换对应的特征距离*/
GCBS SingleTransEvaluation(Mat lineRegionU, Mat lineRegionD,
	tuple<float, float>& curParam, float brectUX, float brectUY,
	float brectDX, float brectDY);


/*计算当前ParamNet下的最佳变换*/
GCBS GetBestMeasure(Mat& imageU, Mat& imageD,
	vector <tuple<float, float>> ParamNet,
	float brectUX, float brectUY,
	float brectDX, float brectDY,
	float delta);


vector <tuple<float, float>> GetNextNet(
	vector<tuple<float, float>> &GoodParamNet,
	float txStep, float tyStep, float delta);


ShapeMatchResult GetShapeTrans(Mat& maskImage, Mat& srcImage, float factor);


vector<Gradient>GetGradientTable(Mat& image);


vector<tuple<float, float>> ConstructNetForLineParam(
	float lowGray, float highGray,
	float lowGradient, float highGradient, float delta);


GCBS FastMatchForLineParam(
	Mat& imageU, Mat& imageD,
	float lowGray, float highGray,
	float lowGradient, float highGradient,
	float brectUX, float brectUY,
	float brectDX, float brectDY,
	float delta);


/*************************************************************
Function:       GetCrossBasedFastShapeL
Description:    使用快速匹配形状匹配计算手机盖板左角点
Input:          srcImage:待测图像 maskImage:模板图像
Return:         盖板左角点
**************************************************************/
Point2f GetCrossBasedFastShapeL(Mat& srcImage, Mat& maskImage,
	float factor, float grayThreshold, float gradientThreshold, char *a);


/*************************************************************
Function:       GetCrossBasedFastShapeR
Description:    使用快速匹配形状匹配计算手机盖板右角点
Input:          srcImage:待测图像 maskImage:模板图像
Return:         盖板右角点
**************************************************************/
Point2f GetCrossBasedFastShapeR(Mat& srcImage, Mat& maskImage,
	float factor, float grayThreshold, float gradientThreshold, char *a);
