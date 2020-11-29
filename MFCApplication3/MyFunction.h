#pragma once
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/calib3d/calib3d.hpp"
//#include "opencv2/xfeatures2d/nonfree.hpp"
#include <opencv2/imgproc/imgproc.hpp>
#include<opencv2/opencv.hpp>
#include<opencv2/core.hpp>
#include <opencv2/highgui/highgui_c.h> 
#include <fstream>
#include <string>
#include <vector>
#include<iostream>
#include <iterator>
#include "MyFunction.h"

using namespace std;
using namespace cv;
//using namespace cv::xfeatures2d;

static constexpr const double PI = 3.141592636;
static constexpr const double circleRadiusMax = 200;
static constexpr const double deltaRadius = 350;
//static constexpr const double thresholdValue = 100;
//static constexpr const int erodeSize = 3;
//static constexpr const double CannyThreshold1 = 150;
//static constexpr const double CannyThreshold2 = 200;
//static constexpr const double HoughThreshold1 = 150;
//static constexpr const double HoughThreshold2 = 150;
//static constexpr const double HoughThreshold3 = 50;

//float uTCRotatePointLX;
//float uTCRotatePointLY;
//float uTCRotatePointRX;
//float uTCRotatePointRY;

//Point2f testRotatePoint;


struct CircleData
{
	Point2f center;
	float radius;
};

struct MyCrossAndTheta
{
	Point2f pt;
	float theta;
};

struct CenterPoint
{
	Point2f L;
	Point2f R;
};


struct ControlInstruction
{
	float commandX;
	float commandY;
	float commandTheta;
};


struct HomographyStruct
{
	Mat L;
	Mat R;
};

struct Position
{
	Point2f uniformCrossPointL;
	Point2f uniformCrossPointR;
	Point2f uniformCenterPoint;
	float theta;
};

struct ShapeMatchResult
{
	Point2f massCenter;
	float theta;
};

struct Gradient
{
	Point2f pt;
	float theta;
	float margin;
	//float direct1;
	//float direct2;
	//Mat image;
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
	Point2f pt1;
	Point2f pt2;

	vector<float>MeasureSet;
};

struct RectangleROI             //ɨ�����     
{
	int indexROI;                 // ROI���
	cv::Point2f        pt1;
	cv::Point2f        pt2;
	float          offset;      //��pt1��pt2Ϊ���ߣ�����������෨�߷������չƫ����
	int   direction;           //directionFlag Ϊ������ʾ����pt1 pt2�ķ����˳ʱ�뷽��ɨ�裬Ϊ0������ʱ�뷽��ɨ��
};
struct GatherEdgePtsInput
{
	cv::Mat img;                       //����ͼ��
	RectangleROI  rectangleROI;    //���ֱ�ߵ�ROI
	//AlgrithmParams algPara;        //�㷨����
};
struct GatherEdgePtsOutput
{
	Mat img;
	vector < cv::Point2f > imgPts;//��ȡ��������
};

struct LineStruct
{
	cv::Point2f pt1;    //��ȡ�߶ε�������
	cv::Point2f pt2;
	bool   getFlag;   //��ֱ���Ƿ���ȷ��ȡ true-��ȡ false-û�л�ȡ
	bool   baseFlag;//��ֱ���Ƿ���ڶ�λ
};



Point2f TransToWorldAxis(Point2f point, Mat& invH);

Point2f findCircle1(Point2f pt1, Point2f pt2, float theta);

CircleData findCircle2(Point2f pt1, Point2f pt2, Point2f pt3);

CircleData findCircle3(Point2f pt1, Point2f pt2, Point2f pt3);

Point2f GetCrossInCMask(Mat& srcImageL,
	double thresholdValue, int erodeSize,
	double circleRadiusMax, double deltaRadius,
	double CannyThreshold1, double CannyThreshold2,
	double HoughThreshold1, double HoughThreshold2, double HoughThreshold3);

Point2f GetCrossPointL(Mat srcImage,
	double thresholdValue, int erodeSize,
	double circleRadiusMax, double deltaRadius,
	double CannyThreshold1, double CannyThreshold2,
	double HoughThreshold1, double HoughThreshold2, double HoughThreshold3);

Point2f GetCrossPointR(Mat srcImage, double CannyThreshold1, double CannyThreshold2,
	double HoughThreshold1, double HoughThreshold2, double HoughThreshold3);

Point2f GetCrossPoint(Mat&srcImage, double CannyThreshold1, double CannyThreshold2,
	double HoughThreshold1, double HoughThreshold2, double HoughThreshold3);


Position CalPosition(Mat  imageL, Mat  imageR, 
	HomographyStruct invH,Point2f rotatePtW1,Point2f rotatePtW2);

ControlInstruction GetInstruction(Position& bmPosition, Position& testPosition, Point2f& rotatePoint);

//cv::Point2f RectifyRotateCenter(Position& testPosition, Position& bmPosition,
//	ControlInstruction& instruction, float deltaXeWorld, float deltaYeWorld);

Point2f GetCrossBasedShapeL(Mat& srcImage, Mat& maskImage);

Point2f GetCrossBasedShapeR(Mat& srcImage, Mat& maskImage);

ShapeMatchResult GetShapeTrans(Mat& maskImage, Mat& srcImage);

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
	float grayThreshold, float gradientThreshold, char *a);


/*************************************************************
Function:       GetCrossBasedFastShapeR
Description:    ʹ�ÿ���ƥ����״ƥ������ֻ��ǰ��ҽǵ�
Input:          srcImage:����ͼ�� maskImage:ģ��ͼ��
Return:         �ǰ��ҽǵ�
**************************************************************/
Point2f GetCrossBasedFastShapeR(Mat& srcImage, Mat& maskImage,
	float grayThreshold, float gradientThreshold, char *a);

/*************************************************************
Function:       GetLinePoints
Description:    ʹ��Sobel��ȡͼ��Ǳ��ֱ����ϵ�
Input:          image:����ͼ��
				thresholdEdges:�ݶ���ֵ
				deltaX:����ͼ���ڹ���ͼ����X�������λ��
				deltaY:����ͼ���ڹ���ͼ����Y�������λ��
Return:         linePoints:ֱ����ϵ㼯
**************************************************************/
vector<Point2f> GetLinePoints(Mat image,
	float grayThreshold, float gradientThreshold,
	float delatX, float deltaY);


/*����ĳһ�任��Ӧ����������*/
GCBS SingleTransEvaluation(Mat& lineRegionU, Mat& lineRegionD,
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

Mat LSD(Mat srcImage);


//int ransacLines(std::vector<cv::Point2f>& input, std::vector<cv::Vec4d>& lines, double distance, unsigned int ngon, unsigned int itmax);


//-----------------------------------------------GetRandom-----------------------------------------//
//ʵ�֣�ȡ�����
//int interval                ���룺����ĳ�������ڵ������,����: [0-interval]
//����ֵ:	                   [0-interval] ��һ�����
//------------------------------------------------------------------------------------------------//
int  GetRandom(int interval);

float point2line(Point2f p, Point2f p1, Point2f p2);

//--------------------ransacLines-----------------------//
//ʵ�֣�ѡȡ���Ǿ��� ���ѡ������������С��distance�������ĵ㼯��Ȼ�� ȥ����Щ���볬��distance�ĵ㼯
//std::vector<cv::Point>& input                                ���룺�ҵı�Ե�㼯
//std::vector<cv::Vec4d>& lines                                ���룺��Ե���е������㣬���������γɵ�
//float distance                                               ���룺С�ڵ���С����
//unsigned int ngon                                            ���룺��������
//unsigned int itmax                                           ���룺��Ѱ�ĵ�Ĵ���
//----------------------------------------------------------------------------------------------------//
int ransacLines(std::vector<cv::Point2f> input, std::vector<cv::Vec4d>& lines, double distance, unsigned int ngon, unsigned int itmax);

//-------------------------------------------- Step2.1 gatherEdgePts---------------------------------//
//���ƣ���ȡ��Ե��
//���ܣ���ȡ��Ե��ģ���������ֱ��
//�����б�0-���� 1-���
//����ֵ��0-�ɹ� 1-ͼ��Ϊ�� 2-�ݶ���ֵ���ò�������Ҫ���� 3-��ͼû�б�Ե
int gatherEdgePts(const GatherEdgePtsInput &input, GatherEdgePtsOutput &output);

int collectPolygonEdgePointsGatherLineGray(const Mat& gray,
	int calMaxGrad, vector<Vec4i> seedEdgeGroups, int polar,
	float Tdist, int Tgrad, int step, int validPts,
	vector<Point>& edgePtsGroup, float& sharp);

//�ҶȾط��������ؼ�⣬ģ�嶨��
int GetSubPixel(const Mat &img, Point2f &point);

//--------------------collectPolygonEdgePointsertherLine-----------------------//
//ʵ�֣�������Ե�Ĵ���λ�ã��Ѽ���Ե��	
//const cv::Mat& gray					                ���룺�����Ե��ֵ��֮���ͼ��
////vector<cv::Vec4i> seedEdgeGroups                      ���룺ÿ��ROI�������˵�<���x�����y���յ�x���յ�y>��Ӧͬһ��ֱ�ߣ�
////bool polar                                            ���룺����p1-p2��˳ʱ�뻹����ʱ�뷽��
////int Tdist                                             ���룺���뷶Χ
////int Tgrad                                             ���룺�ݶ�����
////std::vector<std::vector<cv::Point>>& edgePtsGroup		������㼯groups��ÿ��group����һ���㼯����Ӧһ��ֱ�ߡ�//���ǵ��ɶ���߶ι��ɵĲ�����ֱ��					
////float& sharp					                        ������������
////����ֵ                                                0���ҵ����ʵı�Ե��
////                                                      2: δ�ҵ����ʵı�Ե��
////------------------------------------------------------------------//
int computeCoarseLine(const Mat& gray, int calMaxGrad,
	vector<Vec4i> seedEdgeGroups, int polar, float Tdist,
	int Tgrad, int validPts, vector<Vec4i> &seedEdgeGroupsOut);


//-----------------------------��ȡ������-----------------------//
//0-����ͼ�� 1- �����ȡ������ROI 2-���� 3- ����������
//0-���� 1- �쳣
int searchBoundaryForLine(Mat srcImage, cv::Mat &img, RectangleROI roiRect, int &calMaxGrad,
	cv::Rect &boundingRectangle, GatherEdgePtsOutput& output);
