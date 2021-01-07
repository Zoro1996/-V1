#pragma once
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/calib3d/calib3d.hpp"
#include "opencv2/xfeatures2d/nonfree.hpp"
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
#include <sstream>	

using namespace std;
using namespace cv;
using namespace cv::xfeatures2d;

static constexpr const double PI = 3.141592636;
static constexpr const double circleRadiusMax = 200;
static constexpr const double deltaRadius = 350;


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

struct ShapeMatchLocation
{
	Point2f anchorPt;
	float theta;
	float similarity;
	int resizeFactor;
};

struct Gradient
{
	Point2f pt;
	float theta;
	float margin;
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


struct GatherLineInput
{
	vector < cv::Point2f > edgePts;                   //轮廓点
	int indexROI;                             //直线编号
};
struct GatherLineOutput
{
	LineStruct fitLine;
	Vec4f lineV4f;
};

struct SingleCameraAlignment
{
	Point2f crossPoint;
	Point2f theta;
};

struct CrossPointInfo
{
	Point2f crossPoint;
	Point2f ptU1;
	Point2f ptU2;
	Point2f ptD1;
	Point2f ptD2;

	float ka;
	float kb;
	float thetaU;
	float thetaD;
	float ransacDistance;

	int index;
	string imagePath;

	int status;
};


struct RansacTest
{
	Point2f crossPoint;
	float ka;
	float kb;
	float ma;
	float mb;
	float ransac;
};


struct DiffComponent
{
	/* 用于微分计算的分量 */
	float r11_bx;
	float r11_by;
	float r11_bz;

	float r12_bx;
	float r12_by;
	float r12_bz;

	float r13_bx;
	float r13_by;
	float r13_bz;

	float r21_bx;
	float r21_by;
	float r21_bz;

	float r22_bx;
	float r22_by;
	float r22_bz;

	float r23_bx;
	float r23_by;
	float r23_bz;

	float k;

	float r11;
	float r12;
	float r21;
	float r22;
	float r13;
	float r23;
	float px;
	float py;
};

struct Solution
{
	/*解向量 */
	float bx, by, bz, px, py;

	float k;

	Solution operator=(Solution &xTmp)
	{
		bx = xTmp.bx;
		by = xTmp.by;
		bz = xTmp.bz;
		px = xTmp.px;
		py = xTmp.py;
		k = xTmp.k;

		return *this;
	};
};


Point2f TransToWorldAxis(Point2f point, Mat& invH);


ControlInstruction GetInstruction(Position& bmPosition, Position& testPosition);


ShapeMatchLocation GetShapeTrans(Mat& maskImage, Mat& srcImage, int resizeFactor);

vector<Gradient>GetGradientTable(Mat& image, int modNum);


/*************************************************************
Function:       GetCrossBasedFastShapeL
Description:    使用快速匹配形状匹配计算手机盖板左角点
Input:          srcImage:待测图像 maskImage:模板图像
Return:         盖板左角点
**************************************************************/
CrossPointInfo GetCrossBaseFastShapeL(Mat& srcImage, Mat& maskImage,RansacTest& ransacResult, char *a);


/*************************************************************
Function:       GetCrossBasedFastShapeR
Description:    使用快速匹配形状匹配计算手机盖板右角点
Input:          srcImage:待测图像 maskImage:模板图像
Return:         盖板右角点
**************************************************************/
CrossPointInfo GetCrossBaseFastShapeR(Mat& srcImage, Mat& maskImage, RansacTest& ransacResult, char *a);



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
int ransacLines(std::vector<cv::Point2f>& input, 
	/*std::vector<cv::Vec4d>& lines*/vector<Point2f>&lines,
	double distance, unsigned int ngon, unsigned int itmax);

//-------------------------------------------- Step2.1 gatherEdgePts---------------------------------//
//名称：获取边缘点
//功能：获取边缘点模块用于拟合直线
//参数列表：0-输入 1-输出
//返回值：0-成功 1-图像为空 2-梯度阈值设置不合适需要调整 3-黑图没有边缘
int gatherEdgePts(const GatherEdgePtsInput &input, GatherEdgePtsOutput &output);

int collectPolygonEdgePointsGatherLineGray(Mat gray,
	int calMaxGrad, vector<Vec4f> seedEdgeGroups, int polar,
	float Tdist, int Tgrad, int step, int validPts,
	vector<Point2f>& edgePtsGroup, float& sharp);

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

void gatherLine(const GatherLineInput &input, GatherLineOutput &output);


vector<Point2f> GetLinePointsBaseSobel(Mat srcImage, Mat image, float deltaX, float deltaY, float imagePair, float direction);


float CalDistance(Point2f circlePt, Point2f pt1, Point2f pt2, Point2f pt3);


float CalSD(Point2f circlePt, Point2f pt1, Point2f pt2, Point2f pt3);


Point2f GetAccuracyCirclePoint(Point2f pointLW1, Point2f pointLW2, Point2f pointLW3, float theta);

void refinePointSet(vector<Point2f>& srcPointSet, vector<Point2f>& dstPointSet);

int GetFreemanCode(Point2f pt1, Point2f pt2);

vector<Point2f> GetLinePointsBaseHoughLineP(Mat& srcImage, Mat& image,
	float deltaX, float deltaY,
	double CannyThreshold1, double CannyThreshold2,
	double HoughThreshold1, double HoughThreshold2, double HoughThreshold3);

bool polynomial_curve_fit(std::vector<cv::Point2f>& key_point, int n, cv::Mat& A);

void SavePointSet(vector<Point2f>&Pts, CString &strPathName);

void SaveCrossInfo(vector<CrossPointInfo>&input, CString &strPathName);

void SaveValue(vector<tuple<float, float, int, int>>&input, CString &strPathName);

void saveSingleCameraTransError(
	vector<tuple<int, int, float, float, float, float, float, float>>&errorTranslationL,
	vector<tuple<int, int, float, float, float, float, float, float>>&errorTranslationR,
	CString& strPathName);

void saveAlignmentError(vector<tuple<float, float, int, int>>& errorInfo,
	vector<tuple<CrossPointInfo, CrossPointInfo, float, float>>&errorInfoL,
	vector<tuple<CrossPointInfo, CrossPointInfo, float, float>>	&errorInfoR,
	CString& strPathName);


void saveInstruction(vector<tuple<float, float, float, int, int>>& instruction,
	CString& strPathName);


Point2f CalWorldPoint(Point2f pt, Mat& M);


Position CalPosition(Mat& imageL, Mat& imageR, string strL, string strR);


void GetDiffComponent(DiffComponent &result, Solution x);


Mat GetJacobi(DiffComponent tempD, Mat matSetL, Mat matWorldSet);


Mat f(Solution xk, Mat matSet, Mat matWorldSet);


void LM(Solution x, float mu, vector<Solution> &historyX, Mat matSet, Mat matWorldSet);

void RestoreInfo(string csvPath, vector<CrossPointInfo> &resultVector, vector<Point2f>&pixelAxisSet);