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

struct RectangleROI             //扫描矩形     
{
	int indexROI;                 // ROI编号
	cv::Point2f        pt1;
	cv::Point2f        pt2;
	float          offset;      //以pt1、pt2为轴线，向该轴线两侧法线方向的扩展偏移量
	int   direction;           //directionFlag 为正，表示沿着pt1 pt2的方向的顺时针方向扫描，为0则是逆时针方向扫描
};
struct GatherEdgePtsInput
{
	cv::Mat img;                       //输入图像
	RectangleROI  rectangleROI;    //拟合直线的ROI
	//AlgrithmParams algPara;        //算法参数
};
struct GatherEdgePtsOutput
{
	Mat img;
	vector < cv::Point2f > imgPts;//获取的轮廓点
};

struct LineStruct
{
	cv::Point2f pt1;    //获取线段的两个点
	cv::Point2f pt2;
	bool   getFlag;   //该直线是否正确获取 true-获取 false-没有获取
	bool   baseFlag;//该直线是否基于定位
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
Description:    使用快速匹配形状匹配计算手机盖板左角点
Input:          srcImage:待测图像 maskImage:模板图像
Return:         盖板左角点
**************************************************************/
Point2f GetCrossBasedFastShapeL(Mat& srcImage, Mat& maskImage,
	float grayThreshold, float gradientThreshold, char *a);


/*************************************************************
Function:       GetCrossBasedFastShapeR
Description:    使用快速匹配形状匹配计算手机盖板右角点
Input:          srcImage:待测图像 maskImage:模板图像
Return:         盖板右角点
**************************************************************/
Point2f GetCrossBasedFastShapeR(Mat& srcImage, Mat& maskImage,
	float grayThreshold, float gradientThreshold, char *a);

/*************************************************************
Function:       GetLinePoints
Description:    使用Sobel提取图像潜在直线拟合点
Input:          image:待测图像
				thresholdEdges:梯度阈值
				deltaX:待测图像在工件图像中X方向相对位置
				deltaY:待测图像在工件图像中Y方向相对位置
Return:         linePoints:直线拟合点集
**************************************************************/
vector<Point2f> GetLinePoints(Mat image,
	float grayThreshold, float gradientThreshold,
	float delatX, float deltaY);


/*计算某一变换对应的特征距离*/
GCBS SingleTransEvaluation(Mat& lineRegionU, Mat& lineRegionD,
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

Mat LSD(Mat srcImage);


//int ransacLines(std::vector<cv::Point2f>& input, std::vector<cv::Vec4d>& lines, double distance, unsigned int ngon, unsigned int itmax);


//-----------------------------------------------GetRandom-----------------------------------------//
//实现：取随机数
//int interval                输入：生成某个区间内的随机数,区间: [0-interval]
//返回值:	                   [0-interval] 的一随机数
//------------------------------------------------------------------------------------------------//
int  GetRandom(int interval);

float point2line(Point2f p, Point2f p1, Point2f p2);

//--------------------ransacLines-----------------------//
//实现：选取的是距离 随机选择的两个点距离小于distance点数最多的点集。然后 去掉那些距离超过distance的点集
//std::vector<cv::Point>& input                                输入：找的边缘点集
//std::vector<cv::Vec4d>& lines                                输入：边缘点中的两个点，到此两点形成的
//float distance                                               输入：小于的最小距离
//unsigned int ngon                                            输入：迭代次数
//unsigned int itmax                                           输入：找寻的点的次数
//----------------------------------------------------------------------------------------------------//
int ransacLines(std::vector<cv::Point2f> input, std::vector<cv::Vec4d>& lines, double distance, unsigned int ngon, unsigned int itmax);

//-------------------------------------------- Step2.1 gatherEdgePts---------------------------------//
//名称：获取边缘点
//功能：获取边缘点模块用于拟合直线
//参数列表：0-输入 1-输出
//返回值：0-成功 1-图像为空 2-梯度阈值设置不合适需要调整 3-黑图没有边缘
int gatherEdgePts(const GatherEdgePtsInput &input, GatherEdgePtsOutput &output);

int collectPolygonEdgePointsGatherLineGray(const Mat& gray,
	int calMaxGrad, vector<Vec4i> seedEdgeGroups, int polar,
	float Tdist, int Tgrad, int step, int validPts,
	vector<Point>& edgePtsGroup, float& sharp);

//灰度矩方法亚像素检测，模板定义
int GetSubPixel(const Mat &img, Point2f &point);

//--------------------collectPolygonEdgePointsertherLine-----------------------//
//实现：给定边缘的大致位置，搜集边缘点	
//const cv::Mat& gray					                输入：输入边缘二值化之后的图像
////vector<cv::Vec4i> seedEdgeGroups                      输入：每个ROI的两个端点<起点x，起点y，终点x，终点y>对应同一条直线；
////bool polar                                            输入：沿着p1-p2的顺时针还是逆时针方向
////int Tdist                                             输入：距离范围
////int Tgrad                                             输入：梯度下限
////std::vector<std::vector<cv::Point>>& edgePtsGroup		输出：点集groups，每个group包含一个点集并对应一条直线。//考虑到由多个线段构成的不连续直线					
////float& sharp					                        输出：锐度评价
////返回值                                                0：找到合适的边缘点
////                                                      2: 未找到合适的边缘点
////------------------------------------------------------------------//
int computeCoarseLine(const Mat& gray, int calMaxGrad,
	vector<Vec4i> seedEdgeGroups, int polar, float Tdist,
	int Tgrad, int validPts, vector<Vec4i> &seedEdgeGroupsOut);


//-----------------------------获取轮廓点-----------------------//
//0-输入图像 1- 输入获取轮廓的ROI 2-参数 3- 返回轮廓点
//0-正常 1- 异常
int searchBoundaryForLine(Mat srcImage, cv::Mat &img, RectangleROI roiRect, int &calMaxGrad,
	cv::Rect &boundingRectangle, GatherEdgePtsOutput& output);
