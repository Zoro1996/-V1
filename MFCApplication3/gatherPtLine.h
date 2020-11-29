#pragma once
#include "io.h"
#include "stdio.h"
#include "detectFilm.h"
using namespace std;
using namespace cv;
//获取轮廓点集
//名称：获取边缘点
//功能：获取边缘点模块用于拟合直线
//参数列表：0-输入 1-输出
//返回值：0-成功 1-图像为空 2-梯度阈值设置不合适需要调整 3-黑图没有边缘
ErrMsg gatherEdgePts(const GatherEdgePtsInput &input, GatherEdgePtsOutput &output);
//名称：拟合轮廓点获取直线
   //功能：通过拟合输入的轮廓点信息获取直线，可以支持像素级轮廓点或世界级轮廓点，若为图像，pixval采用默认值1.0，若为世界，pixval则为当前相机下的pixval
   //返回值 0- 正常 1- 轮廓点为空
ErrMsg  gatherLine(const GatherLineInput &input, GatherLineOutput &output);
//将待测点进行转换
cv::Point2f transFormPt(const cv::Point2f pt, TransformMatrix &transformM);
//返回值:0-正常 1- 输入的线异常
ErrMsg measureL2L(const MeasureL2LInuput &input, MeasureL2LOutput &output,int minFlag);
float point2line(cv::Point2f p, cv::Point2f p1, cv::Point2f p2);
int  GetRandom(int interval);
//-----------------------------获取轮廓点-----------------------//
//0-输入图像 1- 输入获取轮廓的ROI 2-参数 3- 返回轮廓点
//0-正常 1- 异常
int searchBoundaryForLine(cv::Mat &img, RectangleROI roiRect, AlgParamsGetLineConfig &algPara, int &calMaxGrad, cv::Rect &boundingRectangle, vector<cv::Point2f> &contours);
int computeCoarseLine(const cv::Mat& gray, int calMaxGrad, vector<cv::Vec4i> seedEdgeGroups, int polar, float Tdist, int Tgrad, int validPts, vector<cv::Vec4i> &seedEdgeGroupsOut);
int collectPolygonEdgePointsGatherLineGray(const cv::Mat& gray, int calMaxGrad, vector<cv::Vec4i> seedEdgeGroups, int polar, float Tdist, int Tgrad, int step, int validPts, vector < cv::Point > & edgePtsGroup, float& sharp);
int ransacLines(std::vector<cv::Point>& input, std::vector<cv::Vec4d>& lines, double distance, unsigned int ngon, unsigned int itmax);
int ransacLines(std::vector<cv::Point2f>& input, std::vector<cv::Vec4d>& lines, double distance, unsigned int ngon, unsigned int itmax);
int GetSubPixel(const cv::Mat &img, cv::Point2f &point);
