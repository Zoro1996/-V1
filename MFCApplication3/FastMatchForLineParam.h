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
	/*��������*/
	int centerX;
	int centerY;

	/*�㼯*/
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
Description:    ʹ��Sobel��ȡͼ��Ǳ��ֱ����ϵ�
Input:          image:����ͼ��
				thresholdEdges:�ݶ���ֵ
				deltaX:����ͼ���ڹ���ͼ����X�������λ��
				deltaY:����ͼ���ڹ���ͼ����Y�������λ��
Return:         linePoints:ֱ����ϵ㼯
**************************************************************/
vector<Point2f> GetLinePoints(Mat& image, float thresholdEdges,
	float delatX, float deltaY);


/*����ĳһ�任��Ӧ����������*/
GCBS SingleTransEvaluation(Mat lineRegionU, Mat lineRegionD,
	tuple<float, float>& curParam, float brectUX, float brectUY,
	float brectDX, float brectDY);


/*���㵱ǰParamNet�µ���ѱ任*/
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
Description:    ʹ�ÿ���ƥ����״ƥ������ֻ��ǰ���ǵ�
Input:          srcImage:����ͼ�� maskImage:ģ��ͼ��
Return:         �ǰ���ǵ�
**************************************************************/
Point2f GetCrossBasedFastShapeL(Mat& srcImage, Mat& maskImage,
	float factor, float grayThreshold, float gradientThreshold, char *a);


/*************************************************************
Function:       GetCrossBasedFastShapeR
Description:    ʹ�ÿ���ƥ����״ƥ������ֻ��ǰ��ҽǵ�
Input:          srcImage:����ͼ�� maskImage:ģ��ͼ��
Return:         �ǰ��ҽǵ�
**************************************************************/
Point2f GetCrossBasedFastShapeR(Mat& srcImage, Mat& maskImage,
	float factor, float grayThreshold, float gradientThreshold, char *a);
