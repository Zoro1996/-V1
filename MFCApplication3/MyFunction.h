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


struct GatherLineInput
{
	vector < cv::Point2f > edgePts;                   //������
	int indexROI;                             //ֱ�߱��
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
	/* ����΢�ּ���ķ��� */
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
	/*������ */
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
Description:    ʹ�ÿ���ƥ����״ƥ������ֻ��ǰ���ǵ�
Input:          srcImage:����ͼ�� maskImage:ģ��ͼ��
Return:         �ǰ���ǵ�
**************************************************************/
CrossPointInfo GetCrossBaseFastShapeL(Mat& srcImage, Mat& maskImage,RansacTest& ransacResult, char *a);


/*************************************************************
Function:       GetCrossBasedFastShapeR
Description:    ʹ�ÿ���ƥ����״ƥ������ֻ��ǰ��ҽǵ�
Input:          srcImage:����ͼ�� maskImage:ģ��ͼ��
Return:         �ǰ��ҽǵ�
**************************************************************/
CrossPointInfo GetCrossBaseFastShapeR(Mat& srcImage, Mat& maskImage, RansacTest& ransacResult, char *a);



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
int ransacLines(std::vector<cv::Point2f>& input, 
	/*std::vector<cv::Vec4d>& lines*/vector<Point2f>&lines,
	double distance, unsigned int ngon, unsigned int itmax);

//-------------------------------------------- Step2.1 gatherEdgePts---------------------------------//
//���ƣ���ȡ��Ե��
//���ܣ���ȡ��Ե��ģ���������ֱ��
//�����б�0-���� 1-���
//����ֵ��0-�ɹ� 1-ͼ��Ϊ�� 2-�ݶ���ֵ���ò�������Ҫ���� 3-��ͼû�б�Ե
int gatherEdgePts(const GatherEdgePtsInput &input, GatherEdgePtsOutput &output);

int collectPolygonEdgePointsGatherLineGray(Mat gray,
	int calMaxGrad, vector<Vec4f> seedEdgeGroups, int polar,
	float Tdist, int Tgrad, int step, int validPts,
	vector<Point2f>& edgePtsGroup, float& sharp);

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