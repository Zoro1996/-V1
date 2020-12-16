#include "pch.h"
#include "MyFunction.h"
#include "MFCApplication3Dlg.h"
#include "MyGLobal.h"
//#include "detectFilm.h"

//#define FLAG 4
#define ResizeFlag true

float kern0[3][3] = {
	-1,0,1,
	-2,0,2,
	-1,0,1
};

float kern90[3][3] = {
	-1, -2, -1,
	0, 0, 0,
	1, 2, 1
};

#if SubPixelMethod==1
double M00[5][5] = { { 0.0219, 0.1231, 0.1573, 0.1231, 0.0219 },
{ 0.1231, 0.1600, 0.1600, 0.1600, 0.1231 },
{ 0.1573, 0.1600, 0.1600, 0.1600, 0.1573 },
{ 0.1231, 0.1600, 0.1600, 0.1600, 0.1231 },
{ 0.0219, 0.1231, 0.1573, 0.1231, 0.0219 } };

double M10[5][5] = { { -0.0147, -0.0469, 0.0000, 0.0469, 0.0147 },
{ -0.0933, -0.0640, 0.0000, 0.0640, 0.0933 },
{ -0.1253, -0.0640, 0.0000, 0.0640, 0.1253 },
{ -0.0933, -0.0640, 0.0000, 0.0640, 0.0933 },
{ -0.0147, -0.0469, 0.0000, 0.0469, 0.0147 } };

double M20[5][5] = { { 0.0099, 0.0194, 0.0021, 0.0194, 0.0099 },
{ 0.0719, 0.0277, 0.0021, 0.0277, 0.0719 },
{ 0.1019, 0.0277, 0.0021, 0.0277, 0.1019 },
{ 0.0719, 0.0277, 0.0021, 0.0277, 0.0719 },
{ 0.0099, 0.0194, 0.0021, 0.0194, 0.0099 } };

double M11[5][5] = { { -0.0098, -0.0352, 0.0000, 0.0352, 0.0098 },
{ -0.0352, -0.0256, 0.0000, 0.0256, 0.0352 },
{ 0.0000, 0.0000, 0.0000, 0.0000, 0.0000 },
{ 0.0352, 0.0256, 0.0000, -0.0256, -0.0352 },
{ 0.0098, 0.0352, 0.0000, -0.0352, -0.0098 } };

double M01[5][5] = { { 0.0147, 0.0933, 0.1253, 0.0933, 0.0147 },
{ 0.0469, 0.0640, 0.0640, 0.0640, 0.0469 },
{ 0.0000, 0.0000, 0.0000, 0.0000, 0.0000 },
{ -0.0469, -0.0640, -0.0640, -0.0640, -0.0469 },
{ -0.0147, -0.0933, -0.1253, -0.0933, -0.0147 } };

double M02[5][5] = { { 0.0099, 0.0719, 0.1019, 0.0719, 0.0099 },
{ 0.0194, 0.0277, 0.0277, 0.0277, 0.0194 },
{ 0.0021, 0.0021, 0.0021, 0.0021, 0.0021 },
{ 0.0194, 0.0277, 0.0277, 0.0277, 0.0194 },
{ 0.0099, 0.0719, 0.1019, 0.0719, 0.0099 } };
#elif SubPixelMethod==2
/*Zernik��*/
const int g_N = 7;
const int h_N = 3;
Mat M00 = (Mat_<float>(7, 7) <<
	0, 0.0287, 0.0686, 0.0807, 0.0686, 0.0287, 0,
	0.0287, 0.0815, 0.0816, 0.0816, 0.0816, 0.0815, 0.0287,
	0.0686, 0.0816, 0.0816, 0.0816, 0.0816, 0.0816, 0.0686,
	0.0807, 0.0816, 0.0816, 0.0816, 0.0816, 0.0816, 0.0807,
	0.0686, 0.0816, 0.0816, 0.0816, 0.0816, 0.0816, 0.0686,
	0.0287, 0.0815, 0.0816, 0.0816, 0.0816, 0.0815, 0.0287,
	0, 0.0287, 0.0686, 0.0807, 0.0686, 0.0287, 0);

Mat M11R = (Mat_<float>(7, 7) <<
	0, -0.015, -0.019, 0, 0.019, 0.015, 0,
	-0.0224, -0.0466, -0.0233, 0, 0.0233, 0.0466, 0.0224,
	-0.0573, -0.0466, -0.0233, 0, 0.0233, 0.0466, 0.0573,
	-0.069, -0.0466, -0.0233, 0, 0.0233, 0.0466, 0.069,
	-0.0573, -0.0466, -0.0233, 0, 0.0233, 0.0466, 0.0573,
	-0.0224, -0.0466, -0.0233, 0, 0.0233, 0.0466, 0.0224,
	0, -0.015, -0.019, 0, 0.019, 0.015, 0);

Mat M11I = (Mat_<float>(7, 7) <<
	0, -0.0224, -0.0573, -0.069, -0.0573, -0.0224, 0,
	-0.015, -0.0466, -0.0466, -0.0466, -0.0466, -0.0466, -0.015,
	-0.019, -0.0233, -0.0233, -0.0233, -0.0233, -0.0233, -0.019,
	0, 0, 0, 0, 0, 0, 0,
	0.019, 0.0233, 0.0233, 0.0233, 0.0233, 0.0233, 0.019,
	0.015, 0.0466, 0.0466, 0.0466, 0.0466, 0.0466, 0.015,
	0, 0.0224, 0.0573, 0.069, 0.0573, 0.0224, 0);

Mat M20 = (Mat_<float>(7, 7) <<
	0, 0.0225, 0.0394, 0.0396, 0.0394, 0.0225, 0,
	0.0225, 0.0271, -0.0128, -0.0261, -0.0128, 0.0271, 0.0225,
	0.0394, -0.0128, -0.0528, -0.0661, -0.0528, -0.0128, 0.0394,
	0.0396, -0.0261, -0.0661, -0.0794, -0.0661, -0.0261, 0.0396,
	0.0394, -0.0128, -0.0528, -0.0661, -0.0528, -0.0128, 0.0394,
	0.0225, 0.0271, -0.0128, -0.0261, -0.0128, 0.0271, 0.0225,
	0, 0.0225, 0.0394, 0.0396, 0.0394, 0.0225, 0);

Mat M31R = (Mat_<float>(7, 7) <<
	0, -0.0103, -0.0073, 0, 0.0073, 0.0103, 0,
	-0.0153, -0.0018, 0.0162, 0, -0.0162, 0.0018, 0.0153,
	-0.0223, 0.0324, 0.0333, 0, -0.0333, -0.0324, 0.0223,
	-0.0190, 0.0438, 0.0390, 0, -0.0390, -0.0438, 0.0190,
	-0.0223, 0.0324, 0.0333, 0, -0.0333, -0.0324, 0.0223,
	-0.0153, -0.0018, 0.0162, 0, -0.0162, 0.0018, 0.0153,
	0, -0.0103, -0.0073, 0, 0.0073, 0.0103, 0);

Mat M31I = (Mat_<float>(7, 7) <<
	0, -0.0153, -0.0223, -0.019, -0.0223, -0.0153, 0,
	-0.0103, -0.0018, 0.0324, 0.0438, 0.0324, -0.0018, -0.0103,
	-0.0073, 0.0162, 0.0333, 0.039, 0.0333, 0.0162, -0.0073,
	0, 0, 0, 0, 0, 0, 0,
	0.0073, -0.0162, -0.0333, -0.039, -0.0333, -0.0162, 0.0073,
	0.0103, 0.0018, -0.0324, -0.0438, -0.0324, 0.0018, 0.0103,
	0, 0.0153, 0.0223, 0.0190, 0.0223, 0.0153, 0);

Mat M40 = (Mat_<float>(7, 7) <<
	0, 0.013, 0.0056, -0.0018, 0.0056, 0.013, 0,
	0.0130, -0.0186, -0.0323, -0.0239, -0.0323, -0.0186, 0.0130,
	0.0056, -0.0323, 0.0125, 0.0406, 0.0125, -0.0323, 0.0056,
	-0.0018, -0.0239, 0.0406, 0.0751, 0.0406, -0.0239, -0.0018,
	0.0056, -0.0323, 0.0125, 0.0406, 0.0125, -0.0323, 0.0056,
	0.0130, -0.0186, -0.0323, -0.0239, -0.0323, -0.0186, 0.0130,
	0, 0.013, 0.0056, -0.0018, 0.0056, 0.013, 0);
#endif


double CannyThreshold1 = 150;
double CannyThreshold2 = 200;
double HoughThreshold1 = 150;
double HoughThreshold2 = 150;
double HoughThreshold3 = 50;
double thresholdValue = 15;
double ransacDistance = 1.00;

Mat maskImageL;
Mat maskImageR;



Point2f TransToWorldAxis(Point2f point, Mat& invH)
{
	Point2f resultPoint;

	//invH:4*3
	resultPoint.x = invH.at<float>(0, 0)*point.x + invH.at<float>(0, 1)*point.y + invH.at<float>(0, 2);
	resultPoint.y = invH.at<float>(1, 0)*point.x + invH.at<float>(1, 1)*point.y + invH.at<float>(1, 2);

	return resultPoint;
}



Point2f findCircle1(Point2f pt1, Point2f pt2, float theta)
{
	float XMean = (pt1.x + pt2.x) / 2;
	float YMean = (pt1.y + pt2.y) / 2;

	float XAddition = sin(theta)*(pt1.y - pt2.y) / (2 * (1 - cos(theta)));
	float YAddition = sin(theta)*(pt2.x - pt1.x) / (2 * (1 - cos(theta)));

	Point2f pt = Point2f(XMean + XAddition, YMean + YAddition);
	return pt;
}



CircleData findCircle2(Point2f pt1, Point2f pt2, Point2f pt3)
{
	float a = pt1.x - pt2.x;
	float b = pt1.y - pt2.y;

	float c = pt1.x - pt3.x;
	float d = pt1.y - pt3.y;

	float e = (pt1.x*pt1.x + pt1.y*pt1.y - pt2.x*pt2.x - pt2.y*pt2.y) / 2;
	float f = (pt1.x*pt1.x + pt1.y*pt1.y - pt3.x*pt3.x - pt3.y*pt3.y) / 2;

	float x = (d * e - b * f) / (a*d - b * c);
	float y = (a * f - c * e) / (a*d - b * c);

	CircleData CD;
	CD.center = Point2f(x, y);

	return CD;
}



CircleData findCircle3(Point2f pt1, Point2f pt2, Point2f pt3)
{
	//*������ת���ģ������������궨���󣬲���ͼ����ת���ı任���������ꡣ
	//	u : = (row_ys[10] - row_ys[9]) / (col_xs[10] - col_xs[9])
	//	v : = (row_ys[11] - row_ys[10]) / (col_xs[11] - col_xs[10])
	//	w : = 0.5 * (row_ys[9] + row_ys[10]) + 0.5 * (col_xs[9] + col_xs[10]) / (u)
	//	k : = 0.5 * (row_ys[10] + row_ys[11]) + 0.5 * (col_xs[10] + col_xs[11]) / (v)
	//	cx : = (k - w) / (1 / v - 1 / u)
	//	cy : = (w - k) / u / (1 / v - 1 / u) + w
	//	r : = sqrt(pow((row_ys[9] - cy), 2) + pow((col_xs[9] - cx), 2))

	float u = (pt2.y - pt1.y) / (pt2.x - pt1.x);
	float v = (pt3.y - pt2.y) / (pt3.x - pt2.x);
	float w = 0.5*(pt1.y + pt2.y) + 0.5*(pt1.x + pt2.x) / u;
	float k = 0.5*(pt2.y + pt3.y) + 0.5*(pt2.x + pt3.x) / v;
	float x = (k - w) / (1 / v - 1 / u);
	float y = (w - k) / u / (1 / v - 1 / u) + w;

	CircleData CD;

	CD.center = Point2f(x, y);
	CD.radius = sqrt(pow((pt1.y - y), 2) + pow((pt1.x - x), 2));

	return CD;
}



Point2f GetCrossInCMask(Mat& srcImageL,
	double thresholdValue, int erodeSize,
	double circleRadiusMax, double deltaRadius,
	double CannyThreshold1, double CannyThreshold2,
	double HoughThreshold1, double HoughThreshold2, double HoughThreshold3)
{
	Point2f crossPoint;
	cout << "pause here." << endl;
	return crossPoint;
}



/*************************************************************
Function:       GetLinePointsBaseHoughLineP
Description:    ʹ�û���ֱ�߼���㷨���ROIֱ�߶�
Input:          image:����ͼ��,
				CannyThreshold1,CannyThreshold2:Canny���Ӳ���
				HoughThreshold1,HoughThreshold2,HoughThreshold3:����ֱ�߼�����Ӳ���
Return:         linePoints:ֱ�ߵ㼯
**************************************************************/
vector<Point2f> GetLinePointsBaseHoughLineP(Mat& srcImage,Mat& image,
	float deltaX, float deltaY,
	double CannyThreshold1, double CannyThreshold2,
	double HoughThreshold1, double HoughThreshold2, double HoughThreshold3)
{
	Mat edges,imageBGR;
	vector<Vec4f> lines;
	vector<Point2f>linPoints2,linePoints;
	cvtColor(image, imageBGR, CV_GRAY2BGR);
	Mat dstImage = Mat::zeros(image.size(), image.type());

	Canny(image, edges, CannyThreshold1, CannyThreshold2);
	HoughLinesP(edges, lines, 1, CV_PI / 360, HoughThreshold1, HoughThreshold2, HoughThreshold3);

	for (size_t i = 0; i < lines.size(); i++) {
		Vec4f l = lines[i];
		line(dstImage, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(255));
		//linPoints2.push_back(Point2f(l[0], l[1]));
		//linPoints2.push_back(Point2f(l[2], l[3]));
	}

	for (int row = 0; row < dstImage.rows; row++)
	{
		for (int col = 0; col < dstImage.cols; col++)
		{
			Point2f pt = Point2f(col, row);
			float value = dstImage.at<uchar>(pt);
			if (value != 0)linPoints2.push_back(pt);
		}
	}

	for (int i = 0; i < linPoints2.size(); i++)
	{
		Point2f pt = linPoints2[i] + Point2f(deltaX, deltaY);
		/*�����ش���*/
		GetSubPixel(srcImage, pt);

		/*���*/
		linePoints.push_back(pt);
	}

	return linePoints;
}


Point2f GetCrossPointL(Mat image,
	double thresholdValue, int erodeSize,
	double circleRadiusMax, double deltaRadius,
	double CannyThreshold1, double CannyThreshold2,
	double HoughThreshold1, double HoughThreshold2, double HoughThreshold3)
{
	Mat srcImage = image.clone();
	//threshold(srcImage, srcImage, thresholdValue, 255, CV_THRESH_BINARY);

	//GaussianBlur(srcImage, srcImage, Size(erodeSize, erodeSize), 0, 0);

	Mat element = getStructuringElement(MORPH_RECT, Size(erodeSize, erodeSize));
	//morphologyEx(srcImage, srcImage, MORPH_OPEN, element);		CannyThreshold1	150.00000000000000	double

	erode(srcImage, srcImage, element);

	vector<Vec3f> circles;
	//��һ��������InputArray���͵�image������ͼ�񣬼�Դͼ����Ϊ8λ�ĻҶȵ�ͨ��ͼ��
	//�ڶ���������InputArray���͵�circles����������HoughCircles������˲����洢�˼�⵽��Բ�����ʸ����ÿ��ʸ���ɰ�����3��Ԫ�صĸ���ʸ��(x, y, radius)��ʾ��
	//������������int���͵�method����ʹ�õļ�ⷽ����ĿǰOpenCV�оͻ����ݶȷ�һ�ֿ���ʹ�ã����ı�ʶ��ΪCV_HOUGH_GRADIENT���ڴ˲������������ʶ�����ɡ�
	//���ĸ�������double���͵�dp���������Բ�ĵ��ۼ���ͼ��ķֱ���������ͼ��֮�ȵĵ������Ҵ˲���������һ��������ͼ��ֱ��ʵ͵��ۼ������������ֲ������Ļ����������Ӱɡ����磬���dp= 1ʱ���ۼ���������ͼ�������ͬ�ķֱ��ʡ����dp=2���ۼ�����������ͼ��һ����ô��Ŀ�Ⱥ͸߶ȡ�
	//�����������double���͵�minDist��Ϊ����任��⵽��Բ��Բ��֮�����С���룬�������ǵ��㷨���������ֵ�������ͬԲ֮�����С���롣����������̫С�Ļ���������ڵ�Բ���ܱ�����ؼ�����һ���غϵ�Բ����֮�������������̫��Ļ���ĳЩԲ�Ͳ��ܱ��������ˡ�
	//������������double���͵�param1����Ĭ��ֵ100�����ǵ���������method���õļ�ⷽ���Ķ�Ӧ�Ĳ������Ե�ǰΨһ�ķ��������ݶȷ�CV_HOUGH_GRADIENT������ʾ���ݸ�canny��Ե������ӵĸ���ֵ��������ֵΪ����ֵ��һ�롣
	//���߸�������double���͵�param2��Ҳ��Ĭ��ֵ100�����ǵ���������method���õļ�ⷽ���Ķ�Ӧ�Ĳ������Ե�ǰΨһ�ķ��������ݶȷ�CV_HOUGH_GRADIENT������ʾ�ڼ��׶�Բ�ĵ��ۼ�����ֵ����ԽС�Ļ����Ϳ��Լ�⵽������������ڵ�Բ������Խ��Ļ�����ͨ������Բ�͸��ӽӽ�������Բ���ˡ�
	//�ڰ˸�������int���͵�minRadius,��Ĭ��ֵ0����ʾԲ�뾶����Сֵ��
	//�ھŸ�������int���͵�maxRadius,Ҳ��Ĭ��ֵ0����ʾԲ�뾶�����ֵ��
	//��Ҫע����ǣ�ʹ�ô˺������Ժ����׵ؼ���Բ��Բ�ģ������������Ҳ������ʵ�Բ�뾶
	HoughCircles(srcImage, circles, cv::HOUGH_GRADIENT, 2, 50, 150, 100, 0, circleRadiusMax);
	for (int i = 0; i < circles.size(); i++)
	{
		Vec3f cc = circles[i];
		circle(srcImage, Point(cc[0], cc[1]), cc[2] + deltaRadius, Scalar(0), -1, LINE_AA);
	}

	Mat edges;
	Mat srcImageRGB;
	cvtColor(srcImage, srcImageRGB, CV_GRAY2BGR);
	Mat dstImage = Mat::zeros(srcImage.size(), srcImage.type());
	Canny(srcImage, edges, CannyThreshold1, CannyThreshold2);

	vector<Vec4f> lines;
	vector<Point>linePointX, linePointY;
	// Apply Hough Transform
	HoughLinesP(edges, lines, 1, CV_PI / 540, HoughThreshold1, HoughThreshold2, HoughThreshold3);
	// Draw lines on the image
	//float epsilon = 0.001;
	for (size_t i = 0; i < lines.size(); i++) {
		Vec4f l = lines[i];
		//line(dstImage, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(255), 3, LINE_AA);
		if (abs((l[3] - l[1]) / (l[2] - l[0])) > 5)
		{
			line(dstImage, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(255));
			line(srcImageRGB, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(255, 0, 0));
			linePointY.push_back(Point(l[0], l[1]));
			linePointY.push_back(Point(l[2], l[3]));
		}
		else 
		{
			line(dstImage, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(255));				
			line(srcImageRGB, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(255, 0, 0));
			linePointX.push_back(Point(l[0], l[1]));
			linePointX.push_back(Point(l[2], l[3]));
		}
	}

	Vec4f fitLineX, fitLineY;
	//��Ϸ���������С���˷�
	fitLine(linePointX, fitLineX, CV_DIST_HUBER, 0, 0.01, 0.01);
	fitLine(linePointY, fitLineY, CV_DIST_HUBER, 0, 0.01, 0.01);
	float ka, kb;
	ka = (float)(fitLineX[1] / (fitLineX[0])); //���LineAб��
	kb = (float)(fitLineY[1] / (fitLineY[0])); //���LineBб��
	float ma, mb;
	ma = fitLineX[3] - ka * fitLineX[2];
	mb = fitLineY[3] - kb * fitLineY[2];
	Point2f crossPoint;
	crossPoint.x = (mb - ma) / (ka - kb);
	crossPoint.y = (ma * kb - mb * ka) / (kb - ka);

	Point2d pt1, pt2;
	pt1.x = fitLineX[2];
	pt1.y = fitLineX[3];
	pt2.x = fitLineY[2];
	pt2.y = fitLineY[3];

	line(srcImageRGB, pt1, crossPoint, Scalar(0, 0, 255));
	line(srcImageRGB, pt2, crossPoint, Scalar(0, 0, 255));

	MyCrossAndTheta crossPtResult;
	crossPtResult.pt = crossPoint;
	crossPtResult.theta = atan(ka);

	return crossPoint;
}


/*************************************************************
Function:       GetCrossPointR
Description:    ʹ��ȫ���㷨���ǰ���ͼ���е�ֱ�ߺͽǵ�
Input:          srcImage:����ͼ��,
				CannyThreshold1,CannyThreshold2:Canny���Ӳ���
				HoughThreshold1,HoughThreshold2,HoughThreshold3:����ֱ�߼�����Ӳ���
Return:         crossPoint:�ҽǵ�
**************************************************************/
Point2f GetCrossPointR(Mat srcImage, double CannyThreshold1, double CannyThreshold2,
	double HoughThreshold1, double HoughThreshold2, double HoughThreshold3)
{
	Mat edges;
	Mat srcImageRGB;
	cvtColor(srcImage, srcImageRGB, CV_GRAY2BGR);
	Mat dstImage = Mat::zeros(srcImage.size(), srcImage.type());

	// Find the edges in the image using canny detector
	Canny(srcImage, edges, CannyThreshold1, CannyThreshold2);
	// Create a vector to store lines of the image
	vector<Vec4f> lines;
	vector<Point>linePointX, linePointY;
	// Apply Hough Transform
	HoughLinesP(edges, lines, 1, CV_PI / 180, HoughThreshold1,
		HoughThreshold2, HoughThreshold3);

	// Draw lines on the image
	float epsilon = 0;
	for (size_t i = 0; i < lines.size(); i++) {
		Vec4f l = lines[i];
		//line(dstImage, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(255), 3, LINE_AA);
		if (abs((l[3] - l[1]) / (l[2] - l[0] + epsilon)) > 5)
		{
			line(dstImage, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(255));
			line(srcImageRGB, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0, 0, 255));

			linePointY.push_back(Point(l[0], l[1]));
			linePointY.push_back(Point(l[2], l[3]));
		}
		else 
		{
			line(dstImage, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(255));
			line(srcImageRGB, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0, 0, 255));

			linePointX.push_back(Point(l[0], l[1]));
			linePointX.push_back(Point(l[2], l[3]));
		}

	}

	Vec4f fitLineX, fitLineY;
	//��Ϸ���������С���˷�
	fitLine(linePointX, fitLineX, CV_DIST_HUBER, 0, 0.01, 0.01);
	fitLine(linePointY, fitLineY, CV_DIST_HUBER, 0, 0.01, 0.01);

	float ka, kb;
	ka = (float)(fitLineX[1] / (fitLineX[0])); //���LineAб��
	kb = (float)(fitLineY[1] / (fitLineY[0])); //���LineBб��

	float ma, mb;
	ma = fitLineX[3] - ka * fitLineX[2];
	mb = fitLineY[3] - kb * fitLineY[2];

	Point2f crossPoint;
	crossPoint.x = (mb - ma) / (ka - kb + 1e-16);
	crossPoint.y = (ma * kb - mb * ka) / (kb - ka + 1e-16);

	Point2d pt1, pt2;
	pt1.x = fitLineX[2];
	pt1.y = fitLineX[3];
	pt2.x = fitLineY[2];
	pt2.y = fitLineY[3];

	line(srcImageRGB, pt1, crossPoint, Scalar(0, 0, 255));
	line(srcImageRGB, pt2, crossPoint, Scalar(0, 0, 255));

	MyCrossAndTheta crossPtResult;
	crossPtResult.pt = crossPoint;
	crossPtResult.theta = atan(ka);

	return crossPoint;
}





/*************************************************************
Function:       GetGradientTable
Description:    �����ݶȱ�
Input:          image:����ͼ��
Return:         gradientTable:ͼ���ݶȱ�
**************************************************************/
vector<Gradient>GetGradientTable(Mat& image,int modNum)
{
	Mat xgrad;  //x�����ϵ��ݶ�
	Mat ygrad;  //y�����ϵ��ݶ�
	Mat xygrad;
	vector<Gradient> gradientTable;

	Sobel(image, xgrad, CV_32F, 1, 0, 3);
	Sobel(image, ygrad, CV_32F, 0, 1, 3);
	//convertScaleAbs(xgrad, xgrad);
	//convertScaleAbs(ygrad, ygrad);

	int width = image.cols;
	int height = image.rows;

	int index = 0;
	for (int row = 0; row < height; row++) {
		for (int col = 0; col < width; col++) {
			float xg = xgrad.at<float>(row, col);

			float yg = ygrad.at<float>(row, col);
			float margin = sqrt(pow(xg, 2) + pow(yg, 2));

			if (margin > 200)
			{
				index++;
				if (index % modNum == 0)
				{
					Gradient gradient;
					gradient.pt = Point2f(col - width / 2, row - height / 2);
					//gradient.margin = sqrt(pow(xg, 2) + pow(yg, 2));
					gradient.margin = abs(xg) + abs(yg);
					gradient.theta = atan2(yg, xg);
					gradientTable.push_back(gradient);
				}
			}
		}
	}

	return gradientTable;
}



/*������߲�������𲽳��������*/
vector<ShapeMatchLocation> GetCoarseTrans(Mat& maskImage, Mat& srcImage, int resizeFactor)
{
	//resize maskImage and srcImage
	Mat resizeMaskImage, resizeSrcImage;
	resize(maskImage, resizeMaskImage,
		Size(maskImage.cols / pow(2, resizeFactor), maskImage.rows / pow(2, resizeFactor)));
	resize(srcImage, resizeSrcImage,
		Size(srcImage.cols / pow(2, resizeFactor), srcImage.rows / pow(2, resizeFactor)));

	Mat xgrad;  //x�����ϵ��ݶ�
	Mat ygrad;  //y�����ϵ��ݶ�
	Sobel(resizeSrcImage, xgrad, CV_32F, 1, 0, 3);
	Sobel(resizeSrcImage, ygrad, CV_32F, 0, 1, 3);

	vector<Gradient>maskGradientTable = GetGradientTable(resizeMaskImage,1);
	vector<ShapeMatchLocation> coarseLocation;
	ShapeMatchLocation tempLocation;

	float bestTheta;
	//float ratio = 0.8;
	//float bestSimilarity = ratio * maskGradientTable.size();
	float bestSimilarity = 0;

	Point2f locate;
	for (float sx = 0; sx < resizeSrcImage.cols; sx += 1)
	{
		for (float sy = 0; sy < resizeSrcImage.rows; sy += 1)
		{
			for (float theta = -10 * PI / 180; theta < 10 * PI / 180; theta += PI / 180)
			{
				float similarity = 0;
				for (double i = 0; i < maskGradientTable.size(); i += 1)
				{
					Gradient curMaskGradient = maskGradientTable[i];

					/*ģ��ͼ������������������ĵ�����*/
					float deltaPtX = curMaskGradient.pt.x;
					float deltaPtY = curMaskGradient.pt.y;

					/*������ת����������*/
					float rotateX = cos(theta)*deltaPtX - sin(theta)*deltaPtY;
					float rotateY = sin(theta)*deltaPtX + cos(theta)*deltaPtY;

					/*����ͼ��ǰ��(sx,sy)��Ϊ���ģ���������+��ת����pt�����ڼ���ƥ���*/
					Point2f pt = Point2f(rotateX + sx, rotateY + sy);

					/*����ͼ��߽�����*/
					if (pt.x >= 0 && pt.x < resizeSrcImage.cols - 1
						&& pt.y >= 0 && pt.y < resizeSrcImage.rows - 1)
					{
						float xg = xgrad.at<float>(pt);
						float yg = ygrad.at<float>(pt);
						float gMargin = abs(xg) + abs(yg);
						float gTheta = atan2(yg, xg);

						/*��maskGradientTable�ĵ�i��Ԫ�����꣬�����任
						֮�����Ĵ���ͼ���ϵĶ�Ӧ����ݶ���Ϣ*/
						float gDirection1 = cos(gTheta);
						float gDirection2 = sin(gTheta);

						/*����ƥ�����ƶ�*/
						similarity += gDirection1 * cos(curMaskGradient.theta + theta)
							+ gDirection2 * sin(curMaskGradient.theta + theta);

						/*��ͣ����*/
						if (similarity < bestSimilarity - 1 + i / maskGradientTable.size())
						{
							continue;
						}
					}
				}

				if (similarity > bestSimilarity)
				{
					//if (coarseLocation.size()==0)
					//{
					//	ShapeMatchLocation tempLocation;
					//	tempLocation.anchorPt = Point2f(sx, sy);
					//	tempLocation.theta = theta;
					//	tempLocation.resizeFactor = resizeFactor;
					//	tempLocation.similarity = similarity;
					//	coarseLocation.push_back(tempLocation);
					//}
					//else
					//{
					//	int flag = 1;
					//	for (int i = 0; i < coarseLocation.size(); i++)
					//	{
					//		if (abs(sx - coarseLocation[i].anchorPt.x < 5)
					//			&& abs(sy - coarseLocation[i].anchorPt.y) < 5)
					//		{
					//			flag=0;
					//			break;
					//		}
					//	}
					//	if (flag==1)
					//	{
					//		ShapeMatchLocation tempLocation;
					//		tempLocation.anchorPt = Point2f(sx, sy);
					//		tempLocation.theta = theta;
					//		tempLocation.resizeFactor = resizeFactor;
					//		tempLocation.similarity = similarity;
					//		coarseLocation.push_back(tempLocation);
					//	}
					//}

					bestSimilarity = similarity;
					tempLocation.anchorPt = Point2f(sx, sy);
					tempLocation.theta = theta;
					tempLocation.resizeFactor = resizeFactor;
					tempLocation.similarity = similarity;
				}
			}
		}
	}

	coarseLocation.push_back(tempLocation);

	//ShapeMatchLocation bestLocation = coarseLocation.back();
	//Mat dstImage(resizeSrcImage);
	//cvtColor(dstImage, dstImage, CV_GRAY2BGR);
	//for (int i = 0; i < maskGradientTable.size(); i++)
	//{
	//	Gradient curMaskGradient = maskGradientTable[i];
	//	/*ģ��ͼ������������������ĵ�����*/
	//	float deltaPtX = curMaskGradient.pt.x;
	//	float deltaPtY = curMaskGradient.pt.y;
	//	/*������ת����������*/
	//	float rotateX = cos(bestLocation.theta)*deltaPtX - sin(bestLocation.theta)*deltaPtY;
	//	float rotateY = sin(bestLocation.theta)*deltaPtX + cos(bestLocation.theta)*deltaPtY;
	//	/*����ͼ��ǰ��(sx,sy)��Ϊ���ģ���������+��ת����pt�����ڼ���ƥ���*/
	//	Point2f pt = Point2f(rotateX + bestLocation.anchorPt.x, rotateY + bestLocation.anchorPt.y);
	//	if (pt.x >= 0 && pt.x < srcImage.cols - 1
	//		&& pt.y >= 0 && pt.y < srcImage.rows - 1)
	//	{
	//		dstImage.at<Vec3b>(pt)[0] = 0;
	//		dstImage.at<Vec3b>(pt)[1] = 0;
	//		dstImage.at<Vec3b>(pt)[2] = 255;
	//	}
	//}
	return coarseLocation;
}


/*��->��*/
vector<ShapeMatchLocation> GetRefinedTrans(Mat& maskImage, Mat& srcImage,
	int resizeFactor, vector<ShapeMatchLocation> coarseLocation)
{
	//resize maskImage and srcImage
	Mat resizeMaskImage, resizeSrcImage;
	resize(maskImage, resizeMaskImage,
		Size(maskImage.cols / pow(2, resizeFactor), maskImage.rows / pow(2, resizeFactor)));
	resize(srcImage, resizeSrcImage,
		Size(srcImage.cols / pow(2, resizeFactor), srcImage.rows / pow(2, resizeFactor)));

	/*�������ź����ģͼ����ݶȱ�*/
	vector<Gradient>maskGradientTable = GetGradientTable(resizeMaskImage, 2);

	vector<ShapeMatchLocation> refineLocation;
	ShapeMatchLocation tempLocation;

	/*����ͼ���ݶ�ͼ*/
	Mat xgrad, ygrad;
	Sobel(resizeSrcImage, xgrad, CV_32F, 1, 0, 3);
	Sobel(resizeSrcImage, ygrad, CV_32F, 0, 1, 3);

	float ratio = 0.7;
	int regionX = 5, regionY = 5;
	int factorIndex = coarseLocation[0].resizeFactor - resizeFactor;//��������������֮�����������
	int scaleFactor = pow(2, factorIndex);
	//float bestSimilarity = ratio * maskGradientTable.size();
	float bestSimilarity = 0;
	//float stepTheta = (float)(PI / (180 * pow(2, factor - resizeFactor-1)));
	float stepTheta = (float)(0.2*PI / 180);

	for (int i = 0; i < coarseLocation.size(); i++)
	{
		ShapeMatchLocation curLocation = coarseLocation[i];
		for (float sx = scaleFactor * curLocation.anchorPt.x - regionX; 
			sx < scaleFactor * curLocation.anchorPt.x + regionX; sx += 1)
		{
			for (float sy = scaleFactor * curLocation.anchorPt.y - regionY;
				sy < scaleFactor * curLocation.anchorPt.y + regionY; sy += 1)
			{
				for (float theta = curLocation.theta - stepTheta *10;
					theta < curLocation.theta + stepTheta * 10; theta += stepTheta)
				{
					float similarity = 0;
					for (int j = 0; j < maskGradientTable.size(); j += 1)
					{
						Gradient curMaskGradient = maskGradientTable[j];

						/*ģ��ͼ������������������ĵ�����*/
						float deltaPtX = curMaskGradient.pt.x;
						float deltaPtY = curMaskGradient.pt.y;

						/*������ת����������*/
						float rotateX = cos(theta)*deltaPtX - sin(theta)*deltaPtY;
						float rotateY = sin(theta)*deltaPtX + cos(theta)*deltaPtY;

						/*����ͼ��ǰ��(sx,sy)��Ϊ���ģ���������+��ת����pt*/
						Point2f pt = Point2f(rotateX + sx, rotateY + sy);

						/*����ͼ��߽�����*/
						if (pt.x >= 0 && pt.x < resizeSrcImage.cols - 1
							&& pt.y >= 0 && pt.y < resizeSrcImage.rows - 1)
						{
							float xg = xgrad.at<float>(pt);
							float yg = ygrad.at<float>(pt);
							float gMargin = abs(xg) + abs(yg);
							float gTheta = atan2(yg, xg);//[-Pi,Pi]

							/*��maskGradientTable�ĵ�i��Ԫ�����꣬�����任
							֮�����Ĵ���ͼ���ϵĶ�Ӧ����ݶ���Ϣ*/
							float gDirection1 = cos(gTheta);
							float gDirection2 = sin(gTheta);

							/*����ƥ�����ƶ�*/
							//similarity += abs(gDirection1 * cos(curMaskGradient.theta + theta)
							//	+ gDirection2 * sin(curMaskGradient.theta + theta));
							similarity += gDirection1 * cos(curMaskGradient.theta + theta)
								+ gDirection2 * sin(curMaskGradient.theta + theta);

							/*��ͣ����*/
							if (similarity < bestSimilarity - 1 + i / maskGradientTable.size())
							{
								continue;
							}
						}
					}
					if (similarity > bestSimilarity)
					{
						//if (refineLocation.size() == 0)
						//{
						//	ShapeMatchLocation tempLocation;
						//	tempLocation.anchorPt = Point2f(sx, sy);
						//	tempLocation.theta = theta;
						//	tempLocation.resizeFactor = resizeFactor;
						//	tempLocation.similarity = similarity;
						//	refineLocation.push_back(tempLocation);
						//}
						//else
						//{
						//	int flag = 1;
						//	for (int i = 0; i < refineLocation.size(); i++)
						//	{
						//		if (abs(sx - refineLocation[i].anchorPt.x < regionX)
						//			&& abs(sy - refineLocation[i].anchorPt.y) < regionY)
						//		{
						//			flag = 0;
						//		}
						//	}
						//	if (flag == 1)
						//	{
						//		ShapeMatchLocation tempLocation;
						//		tempLocation.anchorPt = Point2f(sx, sy);
						//		tempLocation.theta = theta;
						//		tempLocation.resizeFactor = resizeFactor;
						//		tempLocation.similarity = similarity;
						//		refineLocation.push_back(tempLocation);
						//	}
						//}

						bestSimilarity = similarity;
						tempLocation.anchorPt = Point2f(sx, sy);
						tempLocation.theta = theta;
						tempLocation.resizeFactor = resizeFactor;
						tempLocation.similarity = similarity;
					}

				}
			}
		}
	}

	refineLocation.push_back(tempLocation);

	//ShapeMatchLocation bestLocation = refineLocation.back();
	//Mat dstImage(resizeSrcImage);
	//cvtColor(dstImage, dstImage, CV_GRAY2BGR);
	//for (int i = 0; i < maskGradientTable.size(); i++)
	//{
	//	Gradient curMaskGradient = maskGradientTable[i];
	//	/*ģ��ͼ������������������ĵ�����*/
	//	float deltaPtX = curMaskGradient.pt.x;
	//	float deltaPtY = curMaskGradient.pt.y;
	//	/*������ת����������*/
	//	float rotateX = cos(bestLocation.theta)*deltaPtX - sin(bestLocation.theta)*deltaPtY;
	//	float rotateY = sin(bestLocation.theta)*deltaPtX + cos(bestLocation.theta)*deltaPtY;
	//	/*����ͼ��ǰ��(sx,sy)��Ϊ���ģ���������+��ת����pt�����ڼ���ƥ���*/
	//	Point2f pt = Point2f(rotateX + bestLocation.anchorPt.x, rotateY + bestLocation.anchorPt.y);
	//	if (pt.x >= 0 && pt.x < srcImage.cols - 1
	//		&& pt.y >= 0 && pt.y < srcImage.rows - 1)
	//	{
	//		dstImage.at<Vec3b>(pt)[0] = 0;
	//		dstImage.at<Vec3b>(pt)[1] = 0;
	//		dstImage.at<Vec3b>(pt)[2] = 255;
	//	}
	//}
	return refineLocation;
}


/*��ײ������������bestTrans*/
ShapeMatchLocation GetBestTrans(Mat& maskImage, Mat& srcImage, vector<ShapeMatchLocation>refinedLocation)
{
	/*�������ź����ģͼ����ݶȱ�*/
	vector<Gradient>maskGradientTable = GetGradientTable(maskImage,4);
	ShapeMatchLocation bestLocation;

	/*����ͼ���ݶ�ͼ*/
	Mat xgrad, ygrad;
	Sobel(srcImage, xgrad, CV_32F, 1, 0, 3);
	Sobel(srcImage, ygrad, CV_32F, 0, 1, 3);

	int regionX = 10, regionY = 10;
	int factorIndex = refinedLocation[0].resizeFactor;
	int scaleFactor = pow(2, factorIndex);
	float bestSimilarity = 0;
	float stepTheta = 0.1 * PI / 180;

	for (int i = 0; i < refinedLocation.size(); i++)
	{
		ShapeMatchLocation curLocation = refinedLocation[i];
		for (float sx = scaleFactor * curLocation.anchorPt.x - regionX;
			sx < scaleFactor * curLocation.anchorPt.x + regionX; sx += 1)
		{
			for (float sy = scaleFactor * curLocation.anchorPt.y - regionY;
				sy < scaleFactor * curLocation.anchorPt.y + regionY; sy += 1)
			{
				for (float theta = curLocation.theta - stepTheta * 10;
					theta < curLocation.theta + stepTheta * 10; theta += stepTheta)
				{
					float similarity = 0;
					for (int j = 0; j < maskGradientTable.size(); j += 1)
					{
						Gradient curMaskGradient = maskGradientTable[j];

						/*ģ��ͼ������������������ĵ�����*/
						float deltaPtX = curMaskGradient.pt.x;
						float deltaPtY = curMaskGradient.pt.y;

						/*������ת����������*/
						float rotateX = cos(theta)*deltaPtX - sin(theta)*deltaPtY;
						float rotateY = sin(theta)*deltaPtX + cos(theta)*deltaPtY;

						/*����ͼ��ǰ��(sx,sy)��Ϊ���ģ���������+��ת����pt*/
						Point2f pt = Point2f(rotateX + sx, rotateY + sy);

						/*����ͼ��߽�����*/
						if (pt.x >= 0 && pt.x < srcImage.cols - 1
							&& pt.y >= 0 && pt.y < srcImage.rows - 1)
						{
							float xg = xgrad.at<float>(pt);
							float yg = ygrad.at<float>(pt);
							float gMargin = abs(xg) + abs(yg);
							float gTheta = atan2(yg, xg);//[-Pi,Pi]

							/*��maskGradientTable�ĵ�i��Ԫ�����꣬�����任
							֮�����Ĵ���ͼ���ϵĶ�Ӧ����ݶ���Ϣ*/
							float gDirection1 = cos(gTheta);
							float gDirection2 = sin(gTheta);

							/*����ƥ�����ƶ�*/
							similarity += gDirection1 * cos(curMaskGradient.theta + theta)
								+ gDirection2 * sin(curMaskGradient.theta + theta);
						}
					}
					if (similarity > bestSimilarity)
					{
						bestSimilarity = similarity;
						bestLocation.anchorPt = Point2f(sx, sy);
						bestLocation.theta = theta;
						bestLocation.similarity = similarity;
					}

				}
			}
		}
	}

	//Mat dstImage(srcImage);
	//cvtColor(dstImage, dstImage, CV_GRAY2BGR);
	//for (int i = 0; i < maskGradientTable.size(); i++)
	//{
	//	Gradient curMaskGradient = maskGradientTable[i];
	//	/*ģ��ͼ������������������ĵ�����*/
	//	float deltaPtX = curMaskGradient.pt.x;
	//	float deltaPtY = curMaskGradient.pt.y;
	//	/*����ͼ��ǰ��(sx,sy)��Ϊ���ģ���������+��ת����pt�����ڼ���ƥ���*/
	//	Point2f pt = Point2f(deltaPtX + refinedLocation[0].anchorPt.x*scaleFactor,
	//		deltaPtY + refinedLocation[0].anchorPt.y*scaleFactor);
	//	if (pt.x >= 0 && pt.x < srcImage.cols - 1
	//		&& pt.y >= 0 && pt.y < srcImage.rows - 1)
	//	{
	//		dstImage.at<Vec3b>(pt)[0] = 255;
	//		dstImage.at<Vec3b>(pt)[1] = 0;
	//		dstImage.at<Vec3b>(pt)[2] = 0;
	//	}
	//}
	//for (int i = 0; i < maskGradientTable.size(); i++)
	//{
	//	Gradient curMaskGradient = maskGradientTable[i];
	//	/*ģ��ͼ������������������ĵ�����*/
	//	float deltaPtX = curMaskGradient.pt.x;
	//	float deltaPtY = curMaskGradient.pt.y;
	//	/*������ת����������*/
	//	float rotateX = cos(bestLocation.theta)*deltaPtX - sin(bestLocation.theta)*deltaPtY;
	//	float rotateY = sin(bestLocation.theta)*deltaPtX + cos(bestLocation.theta)*deltaPtY;
	//	/*����ͼ��ǰ��(sx,sy)��Ϊ���ģ���������+��ת����pt�����ڼ���ƥ���*/
	//	Point2f pt = Point2f(rotateX + bestLocation.anchorPt.x, rotateY + bestLocation.anchorPt.y);
	//	if (pt.x >= 0 && pt.x < srcImage.cols - 1
	//		&& pt.y >= 0 && pt.y < srcImage.rows - 1)
	//	{
	//		dstImage.at<Vec3b>(pt)[0] = 0;
	//		dstImage.at<Vec3b>(pt)[1] = 0;
	//		dstImage.at<Vec3b>(pt)[2] = 255;
	//	}
	//}

	return bestLocation;
}



/*************************************************************
Function:       GetShapeTrans
Description:    ��״ƥ��
Input:          maskImage:ģ��ͼ�� srcImage:��ƥ��ͼ��
Return:         result:��״ƥ����
**************************************************************/
ShapeMatchLocation GetShapeTrans(Mat& maskImage, Mat& srcImage, int resizeFactor)
{
	int layers = resizeFactor;//the number of layers of the pyramid
	ShapeMatchLocation bestLocation;//best location
	vector<ShapeMatchLocation> coarseLocation, refinedLocation;//coarse location and refined location

	while (resizeFactor + 1)//resizeFactor��ʼ��Ϊ5
	{
		if (resizeFactor != 0)
		{
			if (resizeFactor == layers)//�ֶ�λ
			{
				coarseLocation = GetCoarseTrans(maskImage, srcImage, resizeFactor);
			}
			else if (resizeFactor == layers - 1)
			{
				refinedLocation = GetRefinedTrans(maskImage, srcImage, resizeFactor, coarseLocation);
			}
			//else //�����
			//{
			//	refinedLocation = GetRefinedTrans(maskImage, srcImage, resizeFactor, refinedLocation);
			//}
			else if (resizeFactor == layers - 2)
			{
				refinedLocation = GetRefinedTrans(maskImage, srcImage, resizeFactor, refinedLocation);
			}
		}

		else if (resizeFactor == 0)//��ײ�����Ž�
		{
			//������Ϊ���ӵ�ͼ���ڽ�������߲����ּ�����ѡλ�ã��������󾫲���
			bestLocation = GetBestTrans(maskImage, srcImage, refinedLocation);

			//�ֻ��ǰ�ͼ�������򵥣���������߲����һ����ѡλ�ã����ֱ�ӷ�����ײ����bestTrans
			//bestLocation = GetBestTrans(maskImage, srcImage, coarseLocation);
		}

		resizeFactor--;
	}

	cout << "����" << layers << "�������" << endl;
	cout << "��λ�����[" << bestLocation.anchorPt.x << "," << bestLocation.anchorPt.y
		<< "," << bestLocation.theta << "]" << endl;

	return bestLocation;
}


/*************************************************************
Function:       Hough
Description:    ʹ��Hough���ͼ��ֱ��
Input:          imageMat:����ͼ��
Return:         dstImage:����ֱ�ߵ���ģͼ��
/**************************************************************/
Mat Hough(Mat srcImage)
{
	Mat edges;
	Mat dstImage = Mat::zeros(srcImage.size(), srcImage.type());

	Canny(srcImage, edges, CannyThreshold1, CannyThreshold2);

	vector<Vec4f> lines;
	HoughLinesP(edges, lines, 1, CV_PI / 360, HoughThreshold1, HoughThreshold2, HoughThreshold3);

	for (size_t i = 0; i < lines.size(); i++) {
		Vec4f l = lines[i];
		line(dstImage, Point2f(l[0], l[1]), Point2f(l[2], l[3]), Scalar(255));
	}

	return dstImage;
}


/*************************************************************
Function:       LSD
Description:    ʹ��LSD���ͼ��ֱ��
Input:          imageMat:����ͼ��
Return:         drawnLines:����ֱ�ߵ���ģͼ��
**************************************************************/
Mat LSD(Mat srcImage)
{
	/*����LSDֱ�߼����*/
	Ptr<LineSegmentDetector> ls = createLineSegmentDetector(LSD_REFINE_STD);
	vector<Vec4f> lines_std;
	ls->detect(srcImage, lines_std);

	/*��ֱ��*/
	Mat drawnLines = Mat::zeros(srcImage.size(), srcImage.type());
	Mat drawnLines2(srcImage);
	ls->drawSegments(drawnLines, lines_std);
	ls->drawSegments(drawnLines2, lines_std);

	return drawnLines;
}



/*************************************************************
Function:       GetLinePointsBaseLsd
Description:    ʹ��Sobel��ȡͼ��Ǳ��ֱ����ϵ�+LSD���ֱ��
Input:          image:����ͼ��
				thresholdEdges:�ݶ���ֵ
				deltaX:����ͼ���ڹ���ͼ����X�������λ��
				deltaY:����ͼ���ڹ���ͼ����Y�������λ��
Return:         linePoints:ֱ����ϵ㼯
**************************************************************/
vector<Point2f> GetLinePointsBaseLsd(Mat image,
	float grayThreshold, float gradientThreshold,
	float delatX, float deltaY)
{
	Mat imgBGR;
	cvtColor(image, imgBGR, CV_GRAY2BGR);

	Mat xygrad = Mat::zeros(image.size(), image.type());
	Mat xgrad;  //x�����ϵ��ݶ�
	Mat ygrad;  //y�����ϵ��ݶ�
	Sobel(image, xgrad, CV_32F, 1, 0, 3);
	Sobel(image, ygrad, CV_32F, 0, 1, 3);

	/*LSD�㷨���ֱ�ߣ��������ֱ�߶ε���ģͼ��lingImage*/
	Mat lineImage = LSD(image);

	/*��Ե�㼯linePoints*/
	vector<Point2f>linePoints;
	for (int x = 0; x < image.cols; x += 1)
	{
		for (int y = 0; y < image.rows; y += 1)
		{
			Point2f pt = Point2f(x, y);
			float xg = xgrad.at<float>(pt);
			float yg = ygrad.at<float>(pt);

			/*��ǰ����ݶ�ģ��*/
			float gMargin = sqrt(pow(xg, 2) + pow(yg, 2));

			/*ֱ����ģͼ��ǰ���Ƿ���ֱ�߶��ϵĵ㣬255/0*/
			float lineValue = lineImage.at<Vec3b>(pt)[2];

			if (gMargin > gradientThreshold && lineValue != 0)
			{
				/*��ʾ*/
				xygrad.at<uchar>(pt) = 255;
				imgBGR.at<Vec3b>(pt)[0] = 255;
				imgBGR.at<Vec3b>(pt)[1] = 0;
				imgBGR.at<Vec3b>(pt)[2] = 0;

				/*�����ش���*/
				GetSubPixel(image, pt);

				/*���*/
				linePoints.push_back(Point2f(pt.x + delatX, pt.y + deltaY));
			}
		}
	}

	return linePoints;
}



/*************************************************************
Function:       GetLinePoints2
Description:    ʹ��houghline��ȡͼ��Ǳ��ֱ����ϵ�
Input:          image:����ͼ��
				thresholdEdges:�ݶ���ֵ
				deltaX:����ͼ���ڹ���ͼ����X�������λ��
				deltaY:����ͼ���ڹ���ͼ����Y�������λ��
Return:         linePoints:ֱ����ϵ㼯
**************************************************************/
vector<Point2f> GetLinePoints2(Mat& image, float delatX, float deltaY)
{
	vector<Point2f>linePoints;

	Mat edges, imageRGB;
	cvtColor(image, imageRGB, CV_GRAY2BGR);

	Mat dstImage = Mat::zeros(image.size(), image.type());

	Canny(image, edges, CannyThreshold1, CannyThreshold2);

	vector<Vec4f> lines;
	HoughLinesP(edges, lines, 1, CV_PI / 360, HoughThreshold1, HoughThreshold2, HoughThreshold3);

	for (size_t i = 0; i < lines.size(); i++) {
		Vec4f l = lines[i];

		line(dstImage, Point2f(l[0], l[1]), Point2f(l[2], l[3]), Scalar(255), 1, LINE_AA);
		line(imageRGB, Point2f(l[0], l[1]), Point2f(l[2], l[3]), Scalar(0, 0, 255), 1, LINE_AA);
	}

	for (int row = 0; row < dstImage.rows; row++)
	{
		for (int col = 0; col < dstImage.cols; col++)
		{
			Point2f pt = Point2f(col, row);
			if (dstImage.at<uchar>(pt) != 0)
			{
				Point2f pt2 = Point2f(pt.x + delatX, pt.y + deltaY);
				linePoints.push_back(pt2);
			}
		}
	}

	return linePoints;
}



vector<Point2f> GetLinePointsBaseSobel(Mat srcImage, Mat image, float deltaX, float deltaY, float imagePair, float direction)
{
	vector<Point2f>linePoints,tempLinePoints;

	Mat edges;
	Mat xgrad, xgradabs;  //x�����ϵ��ݶ�
	Mat ygrad, ygradabs;  //y�����ϵ��ݶ�
	vector<Gradient> gradientTable;

	Mat imageBGR(image);
	cvtColor(imageBGR, imageBGR, CV_GRAY2BGR);

	if (direction == 1)//U
	{
		Sobel(image, ygrad, CV_32F, 0, 1, 3);
		convertScaleAbs(ygrad, ygradabs);

		for (int col = 0; col < ygradabs.cols; col++)
		{
			for (int row = 2; row < ygradabs.rows - 1; row++)
			{
				Point2f pt = Point2f(col, row);
				Point2f pt1 = Point2f(col, row - 1);
				Point2f pt2 = Point2f(col, row + 1);
				float deltaGray = abs(ygradabs.at<uchar>(pt1) - ygradabs.at<uchar>(pt2));
				if (deltaGray >= thresholdValue)
				{
					imageBGR.at<Vec3b>(pt)[0] = 0;
					imageBGR.at<Vec3b>(pt)[1] = 0;
					imageBGR.at<Vec3b>(pt)[2] = 255;

					tempLinePoints.push_back(pt);
					break;
				}
			}
		}
	}

	if (direction == 2)//D
	{
		Sobel(image, xgrad, CV_32F, 1, 0, 3);
		convertScaleAbs(xgrad, xgradabs);

		if (imagePair == 0)
		{
			for (int row = 0; row < xgradabs.rows; row++)
			{
				for (int col = 2; col < xgradabs.cols - 2; col++)
				{
					Point2f pt = Point2f(col, row);
					Point2f pt1 = Point2f(col - 1, row);
					Point2f pt2 = Point2f(col + 1, row);
					float deltaGray = abs(xgradabs.at<uchar>(pt1) - xgradabs.at<uchar>(pt2));
					if (deltaGray >= thresholdValue)
					{
						imageBGR.at<Vec3b>(pt)[0] = 0;
						imageBGR.at<Vec3b>(pt)[1] = 0;
						imageBGR.at<Vec3b>(pt)[2] = 255;

						tempLinePoints.push_back(pt);
						break;
					}
				}
			}
		}
		else
		{
			for (int row = 0; row < xgradabs.rows; row++)
			{
				for (int col = xgradabs.cols - 2; col > 1; col--)
				{
					Point2f pt = Point2f(col, row);
					Point2f pt1 = Point2f(col + 1, row);
					Point2f pt2 = Point2f(col - 1, row);
					float deltaGray = abs(xgradabs.at<uchar>(pt1) - xgradabs.at<uchar>(pt2));
					if (deltaGray >= thresholdValue)
					{
						imageBGR.at<Vec3b>(pt)[0] = 0;
						imageBGR.at<Vec3b>(pt)[1] = 0;
						imageBGR.at<Vec3b>(pt)[2] = 255;

						tempLinePoints.push_back(pt);
						break;
					}
				}
			}
		}
	}


	vector<Point2f>linPoints2;
	refinePointSet(tempLinePoints, linPoints2);
	for (int i = 0; i < linPoints2.size(); i++)
	{
		Point2f pt = linPoints2[i];
		if (imageBGR.at<Vec3b>(pt)[0] == 0 &&
			imageBGR.at<Vec3b>(pt)[1] == 0 &&
			imageBGR.at<Vec3b>(pt)[2] == 255)
		{
			imageBGR.at<Vec3b>(pt)[0] = 255;
			imageBGR.at<Vec3b>(pt)[1] = 0;
			imageBGR.at<Vec3b>(pt)[2] = 0;
		}
		else
		{
			imageBGR.at<Vec3b>(pt)[0] = 255;
			imageBGR.at<Vec3b>(pt)[1] = 0;
			imageBGR.at<Vec3b>(pt)[2] = 255;
		}
	}

	for (int i = 0; i < linPoints2.size(); i++)
	{
		Point2f pt = linPoints2[i] + Point2f(deltaX, deltaY);
		/*�����ش���*/
		//GetSubPixel(srcImage, pt);

		/*���*/
		linePoints.push_back(pt);
	}

	return linePoints;
}


/*************************************************************
Function:       GetCrossBasedShape
Description:    ʹ����״ƥ������ֻ��ǰ���ǵ�
Input:          srcImage:����ͼ�� maskImage:ģ��ͼ��
Return:         �ǰ���ǵ�
**************************************************************/
Point2f GetCrossBasedShapeL(Mat& srcImage, Mat& maskImage)
{
	/*step1:��״ƥ�䣬ROI*/
	ShapeMatchLocation arcShapeMatchLocation = GetShapeTrans(maskImage, srcImage,factor);

	Point2f locate = arcShapeMatchLocation.anchorPt;
	float bestTheta = arcShapeMatchLocation.theta;

	Rect maskArcRegion = Rect(1674, 350, 2666 - 1674, 1141 - 350);
	Rect maskLineRegion1 = Rect(2946, 350, 4500 - 2946, 700 - 350);
	Rect maskLineRegion2 = Rect(1304, 1660, 2364 - 1304, 2372 - 1660);

	float centerX = (1674 + 2666) / 2;
	float centerY = (350 + 1141) / 2;
	float deltaCol = locate.x ;
	float deltaRow = locate.y ;

	float xUA1 = 2946 - centerX, yUA1 = 350 - centerY;
	float xUA2 = 4000 - centerX, yUA2 = 350 - centerY;
	float xUB1 = 2946 - centerX, yUB1 = 700 - centerY;
	float xUB2 = 4000 - centerX, yUB2 = 700 - centerY;

	float xDA1 = 1304 - centerX, yDA1 = 1660 - centerY;
	float xDA2 = 2364 - centerX, yDA2 = 1660 - centerY;
	float xDB1 = 1304 - centerX, yDB1 = 2372 - centerY;
	float xDB2 = 2364 - centerX, yDB2 = 2372 - centerY;

	float trxUA1 = cos(bestTheta)*xUA1 - sin(bestTheta)*yUA1 + deltaCol;
	float tryUA1 = sin(bestTheta)*xUA1 + cos(bestTheta)*yUA1 + deltaRow;
	float trxUA2 = cos(bestTheta)*xUA2 - sin(bestTheta)*yUA2 + deltaCol;
	float tryUA2 = sin(bestTheta)*xUA2 + cos(bestTheta)*yUA2 + deltaRow;
	float trxUB1 = cos(bestTheta)*xUB1 - sin(bestTheta)*yUB1 + deltaCol;
	float tryUB1 = sin(bestTheta)*xUB1 + cos(bestTheta)*yUB1 + deltaRow;
	float trxUB2 = cos(bestTheta)*xUB2 - sin(bestTheta)*yUB2 + deltaCol;
	float tryUB2 = sin(bestTheta)*xUB2 + cos(bestTheta)*yUB2 + deltaRow;

	float trxDA1 = cos(bestTheta)*xDA1 - sin(bestTheta)*yDA1 + deltaCol;
	float tryDA1 = sin(bestTheta)*xDA1 + cos(bestTheta)*yDA1 + deltaRow;
	float trxDA2 = cos(bestTheta)*xDA2 - sin(bestTheta)*yDA2 + deltaCol;
	float tryDA2 = sin(bestTheta)*xDA2 + cos(bestTheta)*yDA2 + deltaRow;
	float trxDB1 = cos(bestTheta)*xDB1 - sin(bestTheta)*yDB1 + deltaCol;
	float tryDB1 = sin(bestTheta)*xDB1 + cos(bestTheta)*yDB1 + deltaRow;
	float trxDB2 = cos(bestTheta)*xDB2 - sin(bestTheta)*yDB2 + deltaCol;
	float tryDB2 = sin(bestTheta)*xDB2 + cos(bestTheta)*yDB2 + deltaRow;


	vector<Point2f> contourU, contourD;
	Point2f pU1(trxUA1 + 300, tryUA1 - 150), pU2(trxUA2 + 500, tryUA2 - 150), pU3(trxUB1 + 300, tryUB1 - 150), pU4(trxUB2 + 500, tryUB2 - 150);
	Point2f pD1(trxDA1 + 200, tryDA1 - 100), pD2(trxDA2 - 200, tryDA2 - 100), pD3(trxDB1 + 200, tryDB1 - 250), pD4(trxDB2 - 200, tryDB2 - 250);

	contourU.push_back(pU1);
	contourU.push_back(pU2);
	contourU.push_back(pU3);
	contourU.push_back(pU4);
	RotatedRect rectU = minAreaRect(contourU);//��Ӿ���
	Point2f verticesU[4];
	rectU.points(verticesU);//��Ӿ��ε�4������
	Rect brectU = rectU.boundingRect();

	contourD.push_back(pD1);
	contourD.push_back(pD2);
	contourD.push_back(pD3);
	contourD.push_back(pD4);
	RotatedRect rectD = minAreaRect(contourD);//��Ӿ���
	Point2f verticesD[4];
	rectD.points(verticesD);//��Ӿ��ε�4������
	Rect brectD = rectD.boundingRect();


	if (brectU.x < 0)
	{
		brectU.width -= abs(brectU.x);
		brectU.x = 0;
	}
	if (brectU.y < 0)
	{
		brectU.height -= abs(brectU.y);
		brectU.y = 0;
	}
	if (brectD.x < 0)
	{
		brectD.width -= abs(brectD.x);
		brectD.x = 0;
	}
	if (brectD.y < 0)
	{
		brectD.height -= abs(brectD.y);
		brectD.y = 0;
	}

	if (brectU.x + brectU.width > srcImage.cols)brectU.width = srcImage.cols - brectU.x;
	if (brectU.y + brectU.height > srcImage.rows)brectU.height = srcImage.rows - brectU.y;
	if (brectD.x + brectD.width > srcImage.cols)brectD.width = srcImage.cols - brectD.x;
	if (brectD.y + brectD.height > srcImage.rows)brectD.height = srcImage.rows - brectD.y;

	if (brectU.x % 2 != 0)brectU.x += 1;
	if (brectU.y % 2 != 0)brectU.y += 1;
	if (brectU.width % 2 != 0)brectU.width -= 1;
	if (brectU.height % 2 != 0)brectU.height -= 1;
	if (brectD.x % 2 != 0)brectD.x += 1;
	if (brectD.y % 2 != 0)brectD.y += 1;
	if (brectD.width % 2 != 0)brectD.width -= 1;
	if (brectD.height % 2 != 0)brectD.height -= 1;

	Mat srcImageBGR, BGR1, BGR2;
	cvtColor(srcImage, srcImageBGR, CV_GRAY2BGR);
	cvtColor(srcImage, BGR1, CV_GRAY2BGR);
	cvtColor(srcImage, BGR2, CV_GRAY2BGR);

	for (int i = 0; i < 4; i++)//������
	{
		line(srcImageBGR, verticesU[i], verticesU[(i + 1) % 4], Scalar(0, 0, 255));
		line(srcImageBGR, verticesD[i], verticesD[(i + 1) % 4], Scalar(0, 0, 255));
	}

	/*��ROI*/
	rectangle(srcImageBGR, brectD, Scalar(255, 0, 0));
	rectangle(srcImageBGR, brectU, Scalar(255, 0, 0));


	Mat lineRegionU, lineRegionD;
	srcImage(brectU).copyTo(lineRegionU);
	srcImage(brectD).copyTo(lineRegionD);

	double start = double(getTickCount());

	vector<Point2f>linePointU, linePointD;

	vector<Vec4f> LU, LD;
	LU = LSD(lineRegionU);
	LD = LSD(lineRegionD);

	for (int i = 0; i < LU.size(); i++)
	{
		linePointU.push_back(Point2f(LU[i][0] + brectU.x, LU[i][1] + brectU.y));
		linePointU.push_back(Point2f(LU[i][2] + brectU.x, LU[i][3] + brectU.y));
	}
	for (int i = 0; i < LD.size(); i++)
	{
		linePointD.push_back(Point2f(LD[i][0] + brectD.x, LD[i][1] + brectD.y));
		linePointD.push_back(Point2f(LD[i][2] + brectD.x, LD[i][3] + brectD.y));
	}

	/*����ԭʼ��Ե�㼯*/
	for (int i = 0; i < linePointU.size(); i++)
	{
		BGR1.at<Vec3b>(linePointU[i])[0] = 0;
		BGR1.at<Vec3b>(linePointU[i])[1] = 0;
		BGR1.at<Vec3b>(linePointU[i])[2] = 255;
	}
	for (int i = 0; i < linePointD.size(); i++)
	{
		BGR1.at<Vec3b>(linePointD[i])[0] = 0;
		BGR1.at<Vec3b>(linePointD[i])[1] = 0;
		BGR1.at<Vec3b>(linePointD[i])[2] = 255;
	}

	cout << "before ransac refine: linePointU's size is: " << linePointU.size() << endl;
	cout << "before ransac refine: linePointD's size is: " << linePointD.size() << endl;

	////vector<Vec4d> linesU, linesD;
	//vector<Point2f>linesU, linesD;
	//ransacLines(linePointU, linesU, ransacDistance, 10, 2000);
	//ransacLines(linePointD, linesD, ransacDistance, 10, 2000);
	//cout << "after ransac refine: linePointU's size is: " << linePointU.size() << endl;
	//cout << "after ransac refine: linePointD's size is: " << linePointD.size() << endl;

	/*����ransacɸѡ��ĵ㼯*/
	for (int i = 0; i < linePointU.size(); i++)
	{
		BGR2.at<Vec3b>(linePointU[i])[0] = 0;
		BGR2.at<Vec3b>(linePointU[i])[1] = 0;
		BGR2.at<Vec3b>(linePointU[i])[2] = 255;
	}
	for (int i = 0; i < linePointD.size(); i++)
	{
		BGR2.at<Vec3b>(linePointD[i])[0] = 0;
		BGR2.at<Vec3b>(linePointD[i])[1] = 0;
		BGR2.at<Vec3b>(linePointD[i])[2] = 255;
	}

	GatherLineInput inputLU;
	GatherLineInput inputLD;
	inputLU.edgePts = linePointU;
	inputLD.edgePts = linePointD;
	//inputLU.edgePts = linesU;
	//inputLD.edgePts = linesD;

	GatherLineOutput outputLU, outputLD;
	gatherLine(inputLU, outputLU);
	gatherLine(inputLD, outputLD);

	Point2f ptU1 = outputLU.fitLine.pt1;
	Point2f ptU2 = outputLU.fitLine.pt2;
	Point2f ptD1 = outputLD.fitLine.pt1;
	Point2f ptD2 = outputLD.fitLine.pt2;

	float ka = (float)((ptU2.y - ptU1.y) / (ptU2.x - ptU1.x));
	float kb = (float)((ptD2.y - ptD1.y) / (ptD2.x - ptD1.x));

	float ma = ptU1.y - ka * ptU1.x;
	float mb = ptD1.y - kb * ptD1.x;

	Point2f crossPoint;
	crossPoint.x = (mb - ma) / (ka - kb);
	crossPoint.y = (ma * kb - mb * ka) / (kb - ka);

	line(srcImageBGR, ptU2, crossPoint, Scalar(0, 0, 255), 1);
	line(srcImageBGR, ptD2, crossPoint, Scalar(0, 0, 255), 1);

	double duration_ms = (double(getTickCount()) - start) * 1000 / getTickFrequency();


	for (int i = 0; i < linePointU.size(); i++)
	{
		Point pt = linePointU[i];
		if (srcImageBGR.at<Vec3b>(pt)[0] == 0 &&
			srcImageBGR.at<Vec3b>(pt)[1] == 0 &&
			srcImageBGR.at<Vec3b>(pt)[2] == 255)
		{
			srcImageBGR.at<Vec3b>(pt)[0] = 255;
			srcImageBGR.at<Vec3b>(pt)[1] = 0;
			srcImageBGR.at<Vec3b>(pt)[2] = 0;
		}
		else
		{
			srcImageBGR.at<Vec3b>(pt)[0] = 255;
			srcImageBGR.at<Vec3b>(pt)[1] = 0;
			srcImageBGR.at<Vec3b>(pt)[2] = 255;

		}
	}
	for (int i = 0; i < linePointD.size(); i++)
	{
		Point pt = linePointD[i];
		if (srcImageBGR.at<Vec3b>(pt)[0] == 0 &&
			srcImageBGR.at<Vec3b>(pt)[1] == 0 &&
			srcImageBGR.at<Vec3b>(pt)[2] == 255)
		{
			srcImageBGR.at<Vec3b>(pt)[0] = 255;
			srcImageBGR.at<Vec3b>(pt)[1] = 0;
			srcImageBGR.at<Vec3b>(pt)[2] = 0;
		}
		else
		{
			srcImageBGR.at<Vec3b>(linePointD[i])[0] = 255;
			srcImageBGR.at<Vec3b>(linePointD[i])[1] = 0;
			srcImageBGR.at<Vec3b>(linePointD[i])[2] = 255;

		}
	}

	float ans = abs(ka*kb + 1);

	cout << "ka is: " << ka << endl;
	cout << "kb is: " << kb << endl;
	cout << "Best measurement is: " << ans << " \n";
	cout << "Best crossPoint is: " << crossPoint << " \n";
	std::cout << "It took " << duration_ms << " ms." << "\n" << std::endl;

	return crossPoint;
}



/*************************************************************
Function:       GetCrossBasedShapeR
Description:    ʹ����״ƥ������ֻ��ǰ��ҽǵ�
Input:          srcImage:����ͼ�� maskImage:ģ��ͼ��
Return:         �ǰ��ҽǵ�
**************************************************************/
Point2f GetCrossBasedShapeR(Mat& srcImage, Mat& maskImage)
{
	/*step1:��״ƥ�䣬ROI*/
	ShapeMatchLocation arcShapeMatchLocation = GetShapeTrans(maskImage, srcImage,factor);

	Point2f locate = arcShapeMatchLocation.anchorPt;
	float bestTheta = arcShapeMatchLocation.theta;

	Rect maskArcRegion = Rect(1204, 418, 2330 - 1204, 1384 - 418);
	Rect maskLineRegion1 = Rect(0, 360, 1327 - 0, 750 - 360);
	Rect maskLineRegion2 = Rect(1916, 1474, 2338 - 1916, 3000 - 1474);

	float centerX = (1204 + 2330) / 2;
	float centerY = (1384 + 418) / 2;
	float deltaCol = locate.x;
	float deltaRow = locate.y;

	float xUA1 = 0 - centerX, yUA1 = 360 - centerY;
	float xUA2 = 1327 - centerX, yUA2 = 360 - centerY;
	float xUB1 = 0 - centerX, yUB1 = 750 - centerY;
	float xUB2 = 1327 - centerX, yUB2 = 750 - centerY;

	float xDA1 = 1916 - centerX, yDA1 = 1474 - centerY;
	float xDA2 = 2338 - centerX, yDA2 = 1474 - centerY;
	float xDB1 = 1916 - centerX, yDB1 = 3000 - centerY;
	float xDB2 = 2338 - centerX, yDB2 = 3000 - centerY;

	float trxUA1 = cos(bestTheta)*xUA1 - sin(bestTheta)*yUA1 + deltaCol;
	float tryUA1 = sin(bestTheta)*xUA1 + cos(bestTheta)*yUA1 + deltaRow;
	float trxUA2 = cos(bestTheta)*xUA2 - sin(bestTheta)*yUA2 + deltaCol;
	float tryUA2 = sin(bestTheta)*xUA2 + cos(bestTheta)*yUA2 + deltaRow;
	float trxUB1 = cos(bestTheta)*xUB1 - sin(bestTheta)*yUB1 + deltaCol;
	float tryUB1 = sin(bestTheta)*xUB1 + cos(bestTheta)*yUB1 + deltaRow;
	float trxUB2 = cos(bestTheta)*xUB2 - sin(bestTheta)*yUB2 + deltaCol;
	float tryUB2 = sin(bestTheta)*xUB2 + cos(bestTheta)*yUB2 + deltaRow;
	float trxDA1 = cos(bestTheta)*xDA1 - sin(bestTheta)*yDA1 + deltaCol;
	float tryDA1 = sin(bestTheta)*xDA1 + cos(bestTheta)*yDA1 + deltaRow;
	float trxDA2 = cos(bestTheta)*xDA2 - sin(bestTheta)*yDA2 + deltaCol;
	float tryDA2 = sin(bestTheta)*xDA2 + cos(bestTheta)*yDA2 + deltaRow;
	float trxDB1 = cos(bestTheta)*xDB1 - sin(bestTheta)*yDB1 + deltaCol;
	float tryDB1 = sin(bestTheta)*xDB1 + cos(bestTheta)*yDB1 + deltaRow;
	float trxDB2 = cos(bestTheta)*xDB2 - sin(bestTheta)*yDB2 + deltaCol;
	float tryDB2 = sin(bestTheta)*xDB2 + cos(bestTheta)*yDB2 + deltaRow;


	vector<Point2f> contourU, contourD;
	Point2f pU1(trxUA1, tryUA1), pU2(trxUA2 - 300, tryUA2), pU3(trxUB1, tryUB1), pU4(trxUB2 - 300, tryUB2);
	Point2f pD1(trxDA1, tryDA1 + 40), pD2(trxDA2, tryDA2 + 40), pD3(trxDB1, tryDB1 - 1000), pD4(trxDB2, tryDB2 - 1000);

	contourU.push_back(pU1);
	contourU.push_back(pU2);
	contourU.push_back(pU3);
	contourU.push_back(pU4);
	RotatedRect rectU = minAreaRect(contourU);//��Ӿ���
	Point2f verticesU[4];
	rectU.points(verticesU);//��Ӿ��ε�4������
	Rect brectU = rectU.boundingRect();

	contourD.push_back(pD1);
	contourD.push_back(pD2);
	contourD.push_back(pD3);
	contourD.push_back(pD4);
	RotatedRect rectD = minAreaRect(contourD);//��Ӿ���
	Point2f verticesD[4];
	rectD.points(verticesD);//��Ӿ��ε�4������
	Rect brectD = rectD.boundingRect();

	if (brectU.x % 2 != 0)brectU.x += 1;
	if (brectU.y % 2 != 0)brectU.y += 1;
	if (brectU.width % 2 != 0)brectU.width -= 1;
	if (brectU.height % 2 != 0)brectU.height -= 1;
	if (brectD.x % 2 != 0)brectD.x += 1;
	if (brectD.y % 2 != 0)brectD.y += 1;
	if (brectD.width % 2 != 0)brectD.width -= 1;
	if (brectD.height % 2 != 0)brectD.height -= 1;

	if (brectU.x < 0)
	{
		brectU.width -= abs(brectU.x);
		brectU.x = 0;
	}
	if (brectU.y < 0)
	{
		brectU.height -= abs(brectU.y);
		brectU.y = 0;
	}
	if (brectD.x < 0)
	{
		brectD.width -= abs(brectD.x);
		brectD.x = 0;
	}
	if (brectD.y < 0)
	{
		brectD.height -= abs(brectD.y);
		brectD.y = 0;
	}

	if (brectU.x + brectU.width > srcImage.cols)brectU.width = srcImage.cols - brectU.x;
	if (brectU.y + brectU.height > srcImage.rows)brectU.height = srcImage.rows - brectU.y;
	if (brectD.x + brectD.width > srcImage.cols)brectD.width = srcImage.cols - brectD.x;
	if (brectD.y + brectD.height > srcImage.rows)brectD.height = srcImage.rows - brectD.y;

	Mat srcImageBGR, BGR1, BGR2;
	cvtColor(srcImage, srcImageBGR, CV_GRAY2BGR);
	cvtColor(srcImage, BGR1, CV_GRAY2BGR);
	cvtColor(srcImage, BGR2, CV_GRAY2BGR);

	for (int i = 0; i < 4; i++)//������
	{
		line(srcImageBGR, verticesU[i], verticesU[(i + 1) % 4], Scalar(0, 0, 255));
		line(srcImageBGR, verticesD[i], verticesD[(i + 1) % 4], Scalar(0, 0, 255));
	}

	rectangle(srcImageBGR, brectD, Scalar(255, 0, 0));
	rectangle(srcImageBGR, brectU, Scalar(255, 0, 0));


	Mat lineRegionU, lineRegionD;
	srcImage(brectU).copyTo(lineRegionU);
	srcImage(brectD).copyTo(lineRegionD);


	double start = double(getTickCount());

	vector<Point2f>linePointU, linePointD;

	vector<Vec4f> LU, LD;
	LU = LSD(lineRegionU);
	LD = LSD(lineRegionD);

	for (int i = 0; i < LU.size(); i++)
	{
		linePointU.push_back(Point2f(LU[i][0] + brectU.x, LU[i][1] + brectU.y));
		linePointU.push_back(Point2f(LU[i][2] + brectU.x, LU[i][3] + brectU.y));
	}
	for (int i = 0; i < LD.size(); i++)
	{
		linePointD.push_back(Point2f(LD[i][0] + brectD.x, LD[i][1] + brectD.y));
		linePointD.push_back(Point2f(LD[i][2] + brectD.x, LD[i][3] + brectD.y));
	}

	/*����ԭʼ��Ե�㼯*/
	for (int i = 0; i < linePointU.size(); i++)
	{
		BGR1.at<Vec3b>(linePointU[i])[0] = 0;
		BGR1.at<Vec3b>(linePointU[i])[1] = 0;
		BGR1.at<Vec3b>(linePointU[i])[2] = 255;
	}
	for (int i = 0; i < linePointD.size(); i++)
	{
		BGR1.at<Vec3b>(linePointD[i])[0] = 0;
		BGR1.at<Vec3b>(linePointD[i])[1] = 0;
		BGR1.at<Vec3b>(linePointD[i])[2] = 255;
	}

	cout << "before ransac refine: linePointU's size is: " << linePointU.size() << endl;
	cout << "before ransac refine: linePointD's size is: " << linePointD.size() << endl;

	////vector<Vec4d> linesU, linesD;
	//vector<Point2f>linesU, linesD;
	//ransacLines(linePointU, linesU, ransacDistance, 10, 2000);
	//ransacLines(linePointD, linesD, ransacDistance, 10, 2000);
	//cout << "after ransac refine: linePointU's size is: " << linePointU.size() << endl;
	//cout << "after ransac refine: linePointD's size is: " << linePointD.size() << endl;

	/*����ransacɸѡ��ĵ㼯*/
	for (int i = 0; i < linePointU.size(); i++)
	{
		BGR2.at<Vec3b>(linePointU[i])[0] = 0;
		BGR2.at<Vec3b>(linePointU[i])[1] = 0;
		BGR2.at<Vec3b>(linePointU[i])[2] = 255;
	}
	for (int i = 0; i < linePointD.size(); i++)
	{
		BGR2.at<Vec3b>(linePointD[i])[0] = 0;
		BGR2.at<Vec3b>(linePointD[i])[1] = 0;
		BGR2.at<Vec3b>(linePointD[i])[2] = 255;
	}

	GatherLineInput inputLU;
	GatherLineInput inputLD;
	inputLU.edgePts = linePointU;
	inputLD.edgePts = linePointD;
	//inputLU.edgePts = linesU;
	//inputLD.edgePts = linesD;

	GatherLineOutput outputLU, outputLD;
	gatherLine(inputLU, outputLU);
	gatherLine(inputLD, outputLD);

	Point2f ptU1 = outputLU.fitLine.pt1;
	Point2f ptU2 = outputLU.fitLine.pt2;
	Point2f ptD1 = outputLD.fitLine.pt1;
	Point2f ptD2 = outputLD.fitLine.pt2;

	float ka = (float)((ptU2.y - ptU1.y) / (ptU2.x - ptU1.x));
	float kb = (float)((ptD2.y - ptD1.y) / (ptD2.x - ptD1.x));

	float ma = ptU1.y - ka * ptU1.x;
	float mb = ptD1.y - kb * ptD1.x;

	Point2f crossPoint;
	crossPoint.x = (mb - ma) / (ka - kb);
	crossPoint.y = (ma * kb - mb * ka) / (kb - ka);

	line(srcImageBGR, ptU2, crossPoint, Scalar(0, 0, 255), 1);
	line(srcImageBGR, ptD2, crossPoint, Scalar(0, 0, 255), 1);

	double duration_ms = (double(getTickCount()) - start) * 1000 / getTickFrequency();


	for (int i = 0; i < linePointU.size(); i++)
	{
		Point pt = linePointU[i];
		if (srcImageBGR.at<Vec3b>(pt)[0] == 0 &&
			srcImageBGR.at<Vec3b>(pt)[1] == 0 &&
			srcImageBGR.at<Vec3b>(pt)[2] == 255)
		{
			srcImageBGR.at<Vec3b>(pt)[0] = 255;
			srcImageBGR.at<Vec3b>(pt)[1] = 0;
			srcImageBGR.at<Vec3b>(pt)[2] = 0;
		}
		else
		{
			srcImageBGR.at<Vec3b>(pt)[0] = 255;
			srcImageBGR.at<Vec3b>(pt)[1] = 0;
			srcImageBGR.at<Vec3b>(pt)[2] = 255;

		}
	}
	for (int i = 0; i < linePointD.size(); i++)
	{
		Point pt = linePointD[i];
		if (srcImageBGR.at<Vec3b>(pt)[0] == 0 &&
			srcImageBGR.at<Vec3b>(pt)[1] == 0 &&
			srcImageBGR.at<Vec3b>(pt)[2] == 255)
		{
			srcImageBGR.at<Vec3b>(pt)[0] = 255;
			srcImageBGR.at<Vec3b>(pt)[1] = 0;
			srcImageBGR.at<Vec3b>(pt)[2] = 0;
		}
		else
		{
			srcImageBGR.at<Vec3b>(linePointD[i])[0] = 255;
			srcImageBGR.at<Vec3b>(linePointD[i])[1] = 0;
			srcImageBGR.at<Vec3b>(linePointD[i])[2] = 255;

		}
	}

	float ans = abs(ka*kb + 1);

	cout << "ka is: " << ka << endl;
	cout << "kb is: " << kb << endl;
	cout << "Best measurement is: " << ans << " \n";
	cout << "Best crossPoint is: " << crossPoint << " \n";
	std::cout << "It took " << duration_ms << " ms." << "\n" << std::endl;

	return crossPoint;
}



Point2f GetCrossPoint(Mat&srcImage, double CannyThreshold1, double CannyThreshold2,
	double HoughThreshold1, double HoughThreshold2, double HoughThreshold3)
{
	Mat edges;
	Mat dstImage = Mat::zeros(srcImage.size(), srcImage.type());
	// Find the edges in the image using canny detector
	Canny(srcImage, edges, CannyThreshold1, CannyThreshold2);
	// Create a vector to store lines of the image
	vector<Vec4f> lines;
	vector<Point>linePointX, linePointY;
	// Apply Hough Transform
	HoughLinesP(edges, lines, 1, CV_PI / 180, HoughThreshold1,
		HoughThreshold2, HoughThreshold3);

	// Draw lines on the image
	float epsilon = 0.001;
	for (size_t i = 0; i < lines.size(); i++) {
		Vec4f l = lines[i];
		//line(dstImage, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(255), 3, LINE_AA);
		if (abs((l[3] - l[1]) / (l[2] - l[0] + epsilon)) > 5)
		{
			linePointY.push_back(Point(l[0], l[1]));
			linePointY.push_back(Point(l[2], l[3]));
		}
		else if (abs((l[3] - l[1]) / (l[2] - l[0] + epsilon)) < 0.1)
		{
			linePointX.push_back(Point(l[0], l[1]));
			linePointX.push_back(Point(l[2], l[3]));
		}

	}

	Vec4f fitLineX, fitLineY;
	//��Ϸ���������С���˷�
	fitLine(linePointX, fitLineX, CV_DIST_HUBER, 0, 0.01, 0.01);
	fitLine(linePointY, fitLineY, CV_DIST_HUBER, 0, 0.01, 0.01);

	float ka, kb;
	ka = (float)(fitLineX[1] / (fitLineX[0] + 1e-6)); //���LineAб��
	kb = (float)(fitLineY[1] / (fitLineY[0] + 1e-6)); //���LineBб��

	float ma, mb;
	ma = fitLineX[3] - ka * fitLineX[2];
	mb = fitLineY[3] - kb * fitLineY[2];

	Point2f crossPoint;
	crossPoint.x = (mb - ma) / (ka - kb + 1e-6);
	crossPoint.y = (ma * kb - mb * ka) / (kb - ka + 1e-6);

	return crossPoint;
}



float CalThetaL(Mat srcImage,
	float thresholdValue, int erodeSize,
	float circleRadiusMax, float deltaRadius,
	float CannyThreshold1, double CannyThreshold2,
	float HoughThreshold1, double HoughThreshold2, double HoughThreshold3)
{
	threshold(srcImage, srcImage, thresholdValue, 255, CV_THRESH_BINARY);
	//Mat element = getStructuringElement(MORPH_RECT, Size(erodeSize, erodeSize));
	//morphologyEx(srcImage, srcImage, MORPH_OPEN, element);
	//erode(srcImage, srcImage, element);
	vector<Vec3f> circles;
	//��һ��������InputArray���͵�image������ͼ�񣬼�Դͼ����Ϊ8λ�ĻҶȵ�ͨ��ͼ��
	//�ڶ���������InputArray���͵�circles����������HoughCircles������˲����洢�˼�⵽��Բ�����ʸ����ÿ��ʸ���ɰ�����3��Ԫ�صĸ���ʸ��(x, y, radius)��ʾ��
	//������������int���͵�method����ʹ�õļ�ⷽ����ĿǰOpenCV�оͻ����ݶȷ�һ�ֿ���ʹ�ã����ı�ʶ��ΪCV_HOUGH_GRADIENT���ڴ˲������������ʶ�����ɡ�
	//���ĸ�������double���͵�dp���������Բ�ĵ��ۼ���ͼ��ķֱ���������ͼ��֮�ȵĵ������Ҵ˲���������һ��������ͼ��ֱ��ʵ͵��ۼ������������ֲ������Ļ����������Ӱɡ����磬���dp= 1ʱ���ۼ���������ͼ�������ͬ�ķֱ��ʡ����dp=2���ۼ�����������ͼ��һ����ô��Ŀ�Ⱥ͸߶ȡ�
	//�����������double���͵�minDist��Ϊ����任��⵽��Բ��Բ��֮�����С���룬�������ǵ��㷨���������ֵ�������ͬԲ֮�����С���롣����������̫С�Ļ���������ڵ�Բ���ܱ�����ؼ�����һ���غϵ�Բ����֮�������������̫��Ļ���ĳЩԲ�Ͳ��ܱ��������ˡ�
	//������������double���͵�param1����Ĭ��ֵ100�����ǵ���������method���õļ�ⷽ���Ķ�Ӧ�Ĳ������Ե�ǰΨһ�ķ��������ݶȷ�CV_HOUGH_GRADIENT������ʾ���ݸ�canny��Ե������ӵĸ���ֵ��������ֵΪ����ֵ��һ�롣
	//���߸�������double���͵�param2��Ҳ��Ĭ��ֵ100�����ǵ���������method���õļ�ⷽ���Ķ�Ӧ�Ĳ������Ե�ǰΨһ�ķ��������ݶȷ�CV_HOUGH_GRADIENT������ʾ�ڼ��׶�Բ�ĵ��ۼ�����ֵ����ԽС�Ļ����Ϳ��Լ�⵽������������ڵ�Բ������Խ��Ļ�����ͨ������Բ�͸��ӽӽ�������Բ���ˡ�
	//�ڰ˸�������int���͵�minRadius,��Ĭ��ֵ0����ʾԲ�뾶����Сֵ��
	//�ھŸ�������int���͵�maxRadius,Ҳ��Ĭ��ֵ0����ʾԲ�뾶�����ֵ��
	//��Ҫע����ǣ�ʹ�ô˺������Ժ����׵ؼ���Բ��Բ�ģ������������Ҳ������ʵ�Բ�뾶
	HoughCircles(srcImage, circles, cv::HOUGH_GRADIENT, 2, 50, 150, 100, 0, circleRadiusMax);
	for (int i = 0; i < circles.size(); i++)
	{
		Vec3f cc = circles[i];
		circle(srcImage, Point(cc[0], cc[1]), cc[2] + deltaRadius, Scalar(0), -1, LINE_AA);
	}

	Mat edges;
	Mat srcImageRGB;
	cvtColor(srcImage, srcImageRGB, CV_GRAY2BGR);
	Mat dstImage = Mat::zeros(srcImage.size(), srcImage.type());
	Canny(srcImage, edges, CannyThreshold1, CannyThreshold2);

	vector<Vec4f> lines;
	vector<Point>linePointX, linePointY;
	// Apply Hough Transform
	HoughLinesP(edges, lines, 1, CV_PI / 540, HoughThreshold1, HoughThreshold2, HoughThreshold3);
	// Draw lines on the image
	//float epsilon = 0.001;
	for (size_t i = 0; i < lines.size(); i++) {
		Vec4f l = lines[i];
		//line(dstImage, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(255), 3, LINE_AA);
		if (abs((l[3] - l[1]) / (l[2] - l[0] /*+ epsilon*/)) > 5)
		{
			//line(dstImage, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(255), 3, LINE_AA);
			//line(srcImageRGB, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0, 0, 255), 3, LINE_AA);
			linePointY.push_back(Point(l[0], l[1]));
			linePointY.push_back(Point(l[2], l[3]));
		}
		else if (abs((l[3] - l[1]) / (l[2] - l[0] /*+ epsilon*/)) < 0.1)
		{
			//line(dstImage, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(255), 3, LINE_AA);				line(srcImageRGB, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0, 0, 255), 3, LINE_AA);
			//line(srcImageRGB, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0, 0, 255), 3, LINE_AA);
			linePointX.push_back(Point(l[0], l[1]));
			linePointX.push_back(Point(l[2], l[3]));
		}
	}

	Vec4f fitLineX, fitLineY;
	//��Ϸ���������С���˷�
	fitLine(linePointX, fitLineX, CV_DIST_HUBER, 0, 0.01, 0.01);
	fitLine(linePointY, fitLineY, CV_DIST_HUBER, 0, 0.01, 0.01);
	float ka, kb;
	ka = (float)(fitLineX[1] / (fitLineX[0])); //���LineAб��
	float theta = atan(ka);

	return theta;
}



Position CalPosition(Mat imageL, Mat imageR,
	HomographyStruct invH, Point2f rotatePtW1, Point2f rotatePtW2)
{
	Point2f crossPointL, crossPointR;

	/*����ǵ����������*/
#if CrossMethod == 1
	crossPointL = GetCrossPointL(imageL, thresholdValue, 3,
		circleRadiusMax, deltaRadius, CannyThreshold1, CannyThreshold2,
		HoughThreshold1, HoughThreshold2, HoughThreshold3);
	crossPointR = GetCrossPointR(imageR, CannyThreshold1, CannyThreshold2,
		HoughThreshold1, HoughThreshold2, HoughThreshold3);
#elif CrossMethod == 2
	crossPointL = GetCrossBasedShapeL(imageL, maskImageL);
	crossPointR = GetCrossBasedShapeR(imageR, maskImageR);
#elif CrossMethod == 3
	string strL = "����ͼ����";
	string strR = "����ͼ����";
	RansacTest rl, rr;
	crossPointL = GetCrossBaseFastShapeL(imageL, maskImageL, rl, &strL[0]);
	crossPointR = GetCrossBaseFastShapeR(imageR, maskImageR, rr, &strR[0]);

#endif 

	//�ǵ���������任���ֲ���������ϵ
	Point2f crossPointWorldL = TransToWorldAxis(crossPointL, invH.L);
	Point2f crossPointWorldR = TransToWorldAxis(crossPointR, invH.R);

	/*�ֱ��ȥ���Ե���ת�������꣬�任������ת����Ϊԭ���ͳһ��������ϵ*/
	Point2f uniformCrossPointL = Point2f(crossPointWorldL.x - rotatePtW1.x,
		crossPointWorldL.y - rotatePtW1.y);//��ǵ�-��ֲ���������ϵ��ת��������
	Point2f uniformCrossPointR = Point2f(crossPointWorldR.x - rotatePtW2.x,
		crossPointWorldR.y - rotatePtW2.y);//�ҽǵ�-�Ҿֲ���������ϵ��ת��������

	//����ǵ�����ĵ��ͳһ��������
	float pointX = (uniformCrossPointL.x + uniformCrossPointR.x) / 2;
	float pointY = (uniformCrossPointL.y + uniformCrossPointR.y) / 2;
	Point2f uniformCenterPoint = Point2f(pointX, pointY);

	//��ͳһ��������ϵ�¼���ǰ��Ե����б�Ƕ�theta
	float theta = atan((uniformCrossPointR.y - uniformCrossPointL.y)
		/ (uniformCrossPointR.x - uniformCrossPointL.x));

	Position position;
	position.uniformCrossPointL = uniformCrossPointL;
	position.uniformCrossPointR = uniformCrossPointR;
	position.uniformCenterPoint = uniformCenterPoint;
	position.theta = theta;

	return position;
}



ControlInstruction GetInstruction(Position& bmPosition, Position& testPosition, Point2f& rotatePoint)
{
	/*������⹤���ƶ�����׼λ����Ҫ�ƶ���ƫ��������ת��*/
	ControlInstruction instruction;

	//������ת��alpha
	instruction.commandTheta = bmPosition.theta - testPosition.theta;

	//����ƫ����
	Point2f uniformBmCrossPointL = bmPosition.uniformCrossPointL;
	Point2f uniformBmCrossPointR = bmPosition.uniformCrossPointR;
	Point2f uniformBmCenterPoint = bmPosition.uniformCenterPoint;

	Point2f uniformTestCrossPointL = testPosition.uniformCrossPointL;
	Point2f uniformTestCrossPointR = testPosition.uniformCrossPointR;
	Point2f uniformTestCenterPoint = testPosition.uniformCenterPoint;

	float uTCRotatePointLX = cos(instruction.commandTheta)*(uniformTestCrossPointL.x) -
		sin(instruction.commandTheta)*(uniformTestCrossPointL.y);
	float uTCRotatePointLY = sin(instruction.commandTheta)*(uniformTestCrossPointL.x) +
		cos(instruction.commandTheta)*(uniformTestCrossPointL.y);

	float uTCRotatePointRX = cos(instruction.commandTheta)*(uniformTestCrossPointR.x) -
		sin(instruction.commandTheta)*(uniformTestCrossPointR.y);
	float uTCRotatePointRY = sin(instruction.commandTheta)*(uniformTestCrossPointR.x) +
		cos(instruction.commandTheta)*(uniformTestCrossPointR.y);

	float uTCRotatePointCenterX = cos(instruction.commandTheta)*(uniformTestCenterPoint.x) -
		sin(instruction.commandTheta)*(uniformTestCenterPoint.y);
	float uTCRotatePointCenterY = sin(instruction.commandTheta)*(uniformTestCenterPoint.x) +
		cos(instruction.commandTheta)*(uniformTestCenterPoint.y);

	//��תУ��֮������ĵ�����
	Point2f testRotatePoint = Point2f(uTCRotatePointCenterX, uTCRotatePointCenterY);

	float commandX1, commandX2, commandX3;
	float commandY1, commandY2, commandY3;

	commandX1 = -uTCRotatePointLX + uniformBmCrossPointL.x;
	commandY1 = -uTCRotatePointLY + uniformBmCrossPointL.y;

	commandX2 = -uTCRotatePointRX + uniformBmCrossPointR.x;
	commandY2 = -uTCRotatePointRY + uniformBmCrossPointR.y;

	commandX3 = -uTCRotatePointCenterX + uniformBmCenterPoint.x;
	commandY3 = -uTCRotatePointCenterY + uniformBmCenterPoint.y;

	//instruction.commandX = (commandX1 + commandX2 + commandX3) / 3;
	//instruction.commandY = (commandY1 + commandY2 + commandY3) / 3;
	instruction.commandX = commandX3;
	instruction.commandY = commandY3;

	return instruction;
}


/*����ĳһ�任��Ӧ����������*/
GCBS SingleTransEvaluation(Mat& lineRegionU, Mat& lineRegionD,
	tuple<float, float>& curParam, float brectUX, float brectUY,
	float brectDX, float brectDY)
{
	GCBS curResult;

	int gray = get<0>(curParam);
	int gradient = get<1>(curParam);

	vector<Point2f>linePointX, linePointY;
	linePointX = GetLinePointsBaseLsd(lineRegionU, gray, gradient, brectUX, brectUY);
	linePointY = GetLinePointsBaseLsd(lineRegionD, gray, gradient, brectDX, brectDY);

	curResult.FLAG = (linePointX.size() < 20 || linePointY.size() < 20) ? false : true;

	if (curResult.FLAG == 1)
	{
		Vec4f fitLineX, fitLineY;
		fitLine(linePointX, fitLineX, CV_DIST_HUBER, 0, 0.01, 0.01);
		fitLine(linePointY, fitLineY, CV_DIST_HUBER, 0, 0.01, 0.01);

		float ka = (float)(fitLineX[1] / (fitLineX[0])); //���LineAб��
		float kb = (float)(fitLineY[1] / (fitLineY[0])); //���LineBб��
		float ma = fitLineX[3] - ka * fitLineX[2];
		float mb = fitLineY[3] - kb * fitLineY[2];

		Point2f crossPoint;
		crossPoint.x = (mb - ma) / (ka - kb);
		crossPoint.y = (ma * kb - mb * ka) / (kb - ka);

		Point2f pt1, pt2;
		pt1.x = fitLineX[2];
		pt1.y = fitLineX[3];
		pt2.x = fitLineY[2];
		pt2.y = fitLineY[3];

		//Mat srcImageRGB;
		//cvtColor(srcImage, srcImageRGB, CV_GRAY2BGR);
		//line(srcImageRGB, pt1, crossPoint, Scalar(0, 0, 255), 1, LINE_AA);
		//line(srcImageRGB, pt2, crossPoint, Scalar(0, 0, 255), 1, LINE_AA);
		////circle(srcImageRGB, crossPoint, 8, Scalar(0, 0, 255), -1);

		float measure = abs(ka * kb + 1);

		curResult.ka = ka;
		curResult.kb = kb;
		curResult.ma = ma;
		curResult.mb = mb;
		curResult.measure = measure;
		curResult.gray = gray;
		curResult.gradient = gradient;

		curResult.crossPoint = crossPoint;
		curResult.pt1 = pt1;
		curResult.pt2 = pt2;
	}

	return curResult;
}


/*���㵱ǰParamNet�µ���ѱ任*/
GCBS GetBestMeasure(Mat& imageU, Mat& imageD,
	vector <tuple<float, float>> ParamNet,
	float brectUX, float brectUY,
	float brectDX, float brectDY,
	float delta)
{
	tuple<float, float> bestParam;
	GCBS curResult, bestResult;
	bestResult.measure = 1;

	for (int i = 0; i < ParamNet.size(); i++)
	{
		tuple<float, float> curParam = ParamNet[i];
		curResult = SingleTransEvaluation(imageU, imageD,
			curParam, brectUX, brectUY, brectDX, brectDY);

		if (curResult.FLAG == 1)
		{
			bestResult.MeasureSet.push_back(curResult.measure);

			if (curResult.measure < bestResult.measure)
			{
				bestResult.ka = curResult.ka;
				bestResult.kb = curResult.kb;
				bestResult.ma = curResult.ma;
				bestResult.mb = bestResult.mb;
				bestResult.measure = curResult.measure;
				bestResult.gradient = curResult.gradient;
				bestResult.gray = curResult.gray;

				bestResult.crossPoint = curResult.crossPoint;
				bestResult.pt1 = curResult.pt1;
				bestResult.pt2 = curResult.pt2;
			}
		}
		else
		{
			bestResult.MeasureSet.push_back(1000);
		}
	}

	return bestResult;
}



vector <tuple<float, float>> GetNextNet(vector<tuple<float, float>> &GoodParamNet,
	float txStep, float tyStep, float delta)
{
	txStep *= delta;
	tyStep *= delta;

	vector<tuple<float, float>> nextParamNet;
	tuple<float, float> extendedParam;
	for (int i = 0; i < GoodParamNet.size(); i++)
	{
		nextParamNet.push_back(GoodParamNet[i]);
		for (float outerX = -txStep; outerX <= txStep; outerX += txStep)
		{
			for (float outerY = -tyStep; outerY <= tyStep; outerY += tyStep)
			{
				if (outerX == 0 && outerY == 0)
				{
					continue;
				}
				get<0>(extendedParam) = get<0>(GoodParamNet[i]) + outerX;
				get<1>(extendedParam) = get<1>(GoodParamNet[i]) + outerY;
				nextParamNet.push_back(extendedParam);
			}
		}
	}

	return nextParamNet;
}


vector<tuple<float, float>> ConstructNetForLineParam(
	float lowGray, float highGray,
	float lowGradient, float highGradient, float delta)
{

	float tx_step = float(delta * (highGray - lowGray));
	float ty_step = float(delta * (highGradient - lowGradient));

	float tx, ty;
	vector<tuple<float, float>> Params;

	for (float tx_index = lowGray; tx_index <= highGray; tx_index += tx_step)
	{
		tx = tx_index;
		for (float ty_index = lowGradient; ty_index <= highGradient; ty_index += ty_step)
		{
			ty = ty_index;
			tuple<float, float>curParam{ tx,ty };
			Params.push_back(curParam);
		}
	}

	return Params;
}


float select(vector<float> s, int left, int right, int k)
{ // ��s[ left .. right ]��ѡ���k С��Ԫ��
	if (left >= right)
		return abs(s[left]);
	int i = left; // �������ҵı�־
	int j = right + 1; // ���ҵ���ı�־
	float pivot = abs(s[left]); // ���������Ԫ����Ϊ�ֽ�����
	while (true)
	{
		do
		{ // �����Ѱ��>= pivot ��Ԫ��
			i = i + 1;
		} while (abs(s[i]) < pivot);
		do
		{ // ���Ҳ�Ѱ��<= pivot ��Ԫ��
			j = j - 1;
		} while (abs(s[j]) > pivot);
		if (i >= j) // δ���ֽ�������
			break;
		float temp = abs(s[i]);
		s[i] = abs(s[j]);
		s[j] = temp;
	}
	if (j - left + 1 == k)
		return pivot;
	s[left] = abs(s[j]); // ����pivot
	s[j] = pivot;
	if (j - left + 1 < k) // ��һ���εݹ�
		return select(s, j + 1, right, k - j - 1 + left);
	else
		return select(s, left, j - 1, k);
}

float findKth(vector<float>s, int n, int K)
{ // ���� s[0 .. n - 1]�е�K С��Ԫ��
	if (K < 1 || K > n)
		throw "error";
	return select(s, 0, n - 1, K);
}

/* I1 : mask; I2 : src*/
GCBS FastMatchForLineParam(Mat& imageU, Mat& imageD,
	float lowGray, float highGray, float lowGradient, float highGradient,
	float brectUX, float brectUY, float brectDX, float brectDY, float delta)
{
	//for (int ux = 0; ux < imageU.cols; ux++)
	//{
	//	for (int uy = 0; uy < imageU.rows; uy++)
	//	{
	//		Point2f pt = Point2f(ux, uy);
	//		if (imageU.at<uchar>(pt) >220)
	//		{
	//			imageU.at<uchar>(pt) = 255;
	//		}
	//	}
	//}

	//for (int dx = 0; dx < imageD.cols; dx++)
	//{
	//	for (int dy = 0; dy < imageD.rows; dy++)
	//	{
	//		Point2f pt = Point2f(dx, dy);
	//		if (imageD.at<uchar>(pt) > 220)
	//		{
	//			imageD.at<uchar>(pt) = 255;
	//		}
	//	}
	//}

	/*Step 1 : Construct the N(��) net */
	float tx_step = delta * (highGray - lowGray);
	float ty_step = delta * (highGradient - lowGradient);

	/*vector<tuple<gray,gradient>>*/
	vector<tuple<float, float>> ParamNet, GoodParamNet;

	ParamNet = ConstructNetForLineParam(lowGray, highGray,
		lowGradient, highGradient, delta);

	/*Step 2: Iterate, update and calculate the best translation.*/
	int index = 0;
	GCBS curBestResult, bestResult;
	bestResult.measure = 10;

	vector<float>bestMeasureSet;
	//float L_Delta = 0.4;
	float L_Delta;

	while (true)
	{
		index++;
		cout << "Current TransNet's size is: " << ParamNet.size() << endl;

		curBestResult = GetBestMeasure(imageU, imageD, ParamNet,
			brectUX, brectUY, brectDX, brectDY, delta);

		if (curBestResult.measure < bestResult.measure)
		{
			bestResult.measure = curBestResult.measure;
			bestResult.ka = curBestResult.ka;
			bestResult.kb = curBestResult.kb;
			bestResult.ma = curBestResult.ma;
			bestResult.mb = curBestResult.mb;
			bestResult.gray = curBestResult.gray;
			bestResult.gradient = curBestResult.gradient;
			bestResult.crossPoint = curBestResult.crossPoint;
			bestResult.pt1 = curBestResult.pt1;
			bestResult.pt2 = curBestResult.pt2;
		}

		bestMeasureSet.push_back(bestResult.measure);
		if (abs(bestMeasureSet[index - 1] - bestMeasureSet[index - 3]) < 0.1)
		{
			break;
		}

		/*�������ѱ任����Ĵ��Ž⼯��GoodTransNet*/
		float alpha = 0.5, beta = 0;
		L_Delta = alpha * bestResult.measure + beta;

		float kThMin = select(curBestResult.MeasureSet, 0, curBestResult.MeasureSet.size(), 10);

		//vector<tuple<float, float>> tempParamNet;
		vector<tuple<float, float>>().swap(GoodParamNet);
		for (int i = 0; i < ParamNet.size(); i++)
		{
			float curMeasure = curBestResult.MeasureSet[i];
			if (curMeasure != 1000 && abs(curMeasure - bestResult.measure) < L_Delta && curMeasure <= kThMin)
			{
				tuple<float, float> curParam = ParamNet[i];//��ȡ��ǰ�任
				GoodParamNet.push_back(curParam);
			}
		}

		if (GoodParamNet.size() == 0)
		{
			cout << "L_Delta isn't suitable,please adjust." << endl;
			break;
		}

		//���GoodTransNet�����뵱ǰ��tempTransNet
		//vector<tuple<float, float>>().swap(GoodParamNet);
		//if (tempParamNet.size() > 10)
		//{
		//	int deltaNum = tempParamNet.size() - 10;
		//	int offsetNum = rand() % deltaNum;
		//	vector<tuple<float, float>>::const_iterator first = tempParamNet.begin() + offsetNum;
		//	vector<tuple<float, float>>::const_iterator second = tempParamNet.begin() + offsetNum + 10;
		//	vector<tuple<float, float>>cutGoodParamNet(first, second);
		//	GoodParamNet = cutGoodParamNet;
		//	tuple<float, float>curBestParam{ bestResult.gray,bestResult.gradient };
		//	GoodParamNet.push_back(curBestParam);
		//}
		//else
		//{
		//	GoodParamNet = tempParamNet;
		//}


		cout << "the " << index << "th's GoodTransNet's size is :" << GoodParamNet.size() << endl;

		//vector<tuple<float, float>>().swap(tempParamNet);

		/*����L_Delta���*/
		//L_Delta /= 2;
		delta /= 2;

		/*�����µĦĺ�GoodTransNet���±任����TransNet*/
		vector<tuple<float, float>>().swap(ParamNet);//���TransNet
		ParamNet = GetNextNet(GoodParamNet, tx_step, ty_step, delta);

		/*���vector*/
		//vector<float>().swap(bestDistanceSet);
		//vector<tuple<float, float>>().swap(GoodParamNet);

		if (ParamNet.size() > 1000 || delta < 0.005 || abs(bestResult.measure) < 0.05)
		{
			break;
		}
	}

	cout << "Step 2:gray is: " << bestResult.gray << endl;
	cout << "Step 2:gradient is: " << bestResult.gradient << endl;
	cout << "Step 2:Step 2:Size of the N(��) net is:" << ParamNet.size() << endl;
	cout << "Step 2:delta is :" << delta << "; bestMeasure is :" << bestResult.measure << endl;
	cout << "Step 2:Iterate, update and calculate the best translation has been finished !" << endl;

	return bestResult;
}


void refinePointSet(vector<Point2f>& srcPointSet, vector<Point2f>& dstPointSet)
{
	vector<int>deltaFreemanCode;
	for (int i = 1; i < srcPointSet.size() - 1; i++)
	{
		int code1 = GetFreemanCode(srcPointSet[i - 1], srcPointSet[i]);
		int code2 = GetFreemanCode(srcPointSet[i], srcPointSet[i + 1]);
		deltaFreemanCode.push_back(code2 - code1);
	}

	for (int i = 0; i < deltaFreemanCode.size(); i++)
	{
		Point2f pt = srcPointSet[i + 1];
		if (deltaFreemanCode[i] != 0)//׷�ٵ�ǰ��
		{
			/*׷�ٵ�ǰ�������*/
			int leftChaseIndex = 1;
			while (deltaFreemanCode[i - leftChaseIndex] == 0)
			{
				leftChaseIndex++;
				if (i - leftChaseIndex == 0)break;
				if (i - leftChaseIndex == srcPointSet.size() - 1)break;
			}

			/*׷�ٵ�ǰ����Ұ��*/
			int rightChaseIndex = 1;
			while (deltaFreemanCode[i + rightChaseIndex] == 0)
			{
				rightChaseIndex++;
				if (i + rightChaseIndex == 0)break;
				if (i + rightChaseIndex == srcPointSet.size() - 1)break;
			}

			/*��5�����ڱ仯���Σ���Ϊ��ǰ�������쳣��*/
			if (leftChaseIndex <= 5 && rightChaseIndex <= 5)
			{
				//cout << "[" << pt.x << "," << pt.y << "] is a line-point." << endl;
			}
			else
			{
				dstPointSet.push_back(pt);
			}
		}
		else
		{
			dstPointSet.push_back(pt);
		}
	}
}


/*************************************************************
Function:       GetCrossBasedFastShapeL
Description:    ʹ����״ƥ������ֻ��ǰ���ǵ�
Input:          srcImage:����ͼ�� maskImage:ģ��ͼ��
Return:         �ǰ���ǵ�
**************************************************************/
Point2f GetCrossBaseFastShapeL(Mat& srcImage, Mat& maskImage, RansacTest& ransacResult, char *a)
{
	//GaussianBlur(srcImage, srcImage, Size(3, 3), 0, 0);

	/*step1:��״ƥ�䣬��ȡ�ֲ�ROI*/
	ShapeMatchLocation arcShapeMatchLocation = GetShapeTrans(maskImage, srcImage,factor);

	Point2f locate = arcShapeMatchLocation.anchorPt;
	float bestTheta = arcShapeMatchLocation.theta;

	//Rect maskArcRegion = Rect(1300, 708, 2580 - 1300, 1828 - 708);
	//Rect maskLineRegion1 = Rect(2410 , 551, 600 + roiOffset, 400);
	//Rect maskLineRegion2 = Rect(1044, 1707, 500, 400);

	//Rect maskArcRegion = Rect(1500, 900, 1370, 1300);
	//Rect maskLineRegion1 = Rect(2538, 850, 600, 400);
	//Rect maskLineRegion2 = Rect(1350, 1970+200, 400, 400);
	//Rect maskLineRegion2 = Rect(1350, 1930 + 210 , 400, 400);

	Rect maskArcRegion = Rect(1500, 900, 1370, 1300);
	Rect maskLineRegion1 = Rect(2988, 850, 600, 400);
	Rect maskLineRegion2 = Rect(1350, 2100, 400, 400);

	float centerX = maskArcRegion.width / 2 + maskArcRegion.x;
	float centerY = maskArcRegion.height / 2 + maskArcRegion.y;
	float deltaCol = locate.x ;
	float deltaRow = locate.y ;

	float xUA1 = maskLineRegion1.x - centerX, yUA1 = maskLineRegion1.y - centerY;
	float xUA2 = maskLineRegion1.x + maskLineRegion1.width - centerX, yUA2 = maskLineRegion1.y - centerY;
	float xUB1 = maskLineRegion1.x - centerX, yUB1 = maskLineRegion1.y + maskLineRegion1.height - centerY;
	float xUB2 = maskLineRegion1.x + maskLineRegion1.width - centerX, yUB2 = maskLineRegion1.y + maskLineRegion1.height - centerY;

	float xDA1 = maskLineRegion2.x - centerX, yDA1 = maskLineRegion2.y - centerY;
	float xDA2 = maskLineRegion2.x + maskLineRegion2.width - centerX, yDA2 = maskLineRegion2.y - centerY;
	float xDB1 = maskLineRegion2.x - centerX, yDB1 = maskLineRegion2.y + maskLineRegion2.height - centerY;
	float xDB2 = maskLineRegion2.x + maskLineRegion2.width - centerX, yDB2 = maskLineRegion2.y + maskLineRegion2.height - centerY;

	//U���Ͻǵ�
	float trxUA1 = cos(bestTheta)*xUA1 - sin(bestTheta)*yUA1 + deltaCol;
	float tryUA1 = sin(bestTheta)*xUA1 + cos(bestTheta)*yUA1 + deltaRow;
	//U���Ͻǵ�
	float trxUA2 = cos(bestTheta)*xUA2 - sin(bestTheta)*yUA2 + deltaCol;
	float tryUA2 = sin(bestTheta)*xUA2 + cos(bestTheta)*yUA2 + deltaRow;
	//U���½ǵ�
	float trxUB1 = cos(bestTheta)*xUB1 - sin(bestTheta)*yUB1 + deltaCol;
	float tryUB1 = sin(bestTheta)*xUB1 + cos(bestTheta)*yUB1 + deltaRow;
	//U���½ǵ�
	float trxUB2 = cos(bestTheta)*xUB2 - sin(bestTheta)*yUB2 + deltaCol;
	float tryUB2 = sin(bestTheta)*xUB2 + cos(bestTheta)*yUB2 + deltaRow;
	//D���Ͻǵ�
	float trxDA1 = cos(bestTheta)*xDA1 - sin(bestTheta)*yDA1 + deltaCol;
	float tryDA1 = sin(bestTheta)*xDA1 + cos(bestTheta)*yDA1 + deltaRow;
	//D���Ͻǵ�
	float trxDA2 = cos(bestTheta)*xDA2 - sin(bestTheta)*yDA2 + deltaCol;
	float tryDA2 = sin(bestTheta)*xDA2 + cos(bestTheta)*yDA2 + deltaRow;
	//D���½ǵ�
	float trxDB1 = cos(bestTheta)*xDB1 - sin(bestTheta)*yDB1 + deltaCol;
	float tryDB1 = sin(bestTheta)*xDB1 + cos(bestTheta)*yDB1 + deltaRow;
	//D���½ǵ�
	float trxDB2 = cos(bestTheta)*xDB2 - sin(bestTheta)*yDB2 + deltaCol;
	float tryDB2 = sin(bestTheta)*xDB2 + cos(bestTheta)*yDB2 + deltaRow;

	/*��ȡ����任֮���ROI�ĸ��ǵ�*/
	vector<Point2f> contourU, contourD;
	Point2f pU1(trxUA1, tryUA1), pU2(trxUA2, tryUA2), pU3(trxUB1, tryUB1), pU4(trxUB2, tryUB2);
	Point2f pD1(trxDA1, tryDA1), pD2(trxDA2, tryDA2), pD3(trxDB1, tryDB1), pD4(trxDB2, tryDB2);

	/*����ROI����С��Ӿ��Σ���Ϊ����ͼ���ROI��brectU,brectD*/
	contourU.push_back(pU1);
	contourU.push_back(pU2);
	contourU.push_back(pU3);
	contourU.push_back(pU4);
	RotatedRect rectU = minAreaRect(contourU);//��Ӿ���
	Point2f verticesU[4];
	rectU.points(verticesU);//��Ӿ��ε�4������
	Rect brectU = rectU.boundingRect();

	contourD.push_back(pD1);
	contourD.push_back(pD2);
	contourD.push_back(pD3);
	contourD.push_back(pD4);
	RotatedRect rectD = minAreaRect(contourD);//��Ӿ���
	Point2f verticesD[4];
	rectD.points(verticesD);//��Ӿ��ε�4������
	Rect brectD = rectD.boundingRect();

	/*ROI�߽�����*/
	if (brectU.x < 0)
	{
		brectU.width -= abs(brectU.x);
		brectU.x = 0;
	}
	if (brectU.y < 0)
	{
		brectU.height -= abs(brectU.y);
		brectU.y = 0;
	}
	if (brectD.x < 0)
	{
		brectD.width -= abs(brectD.x);
		brectD.x = 0;
	}
	if (brectD.y < 0)
	{
		brectD.height -= abs(brectD.y);
		brectD.y = 0;
	}

	if (brectU.x + brectU.width > srcImage.cols)brectU.width = srcImage.cols - brectU.x;
	if (brectU.y + brectU.height > srcImage.rows)brectU.height = srcImage.rows - brectU.y;
	if (brectD.x + brectD.width > srcImage.cols)brectD.width = srcImage.cols - brectD.x;
	if (brectD.y + brectD.height > srcImage.rows)brectD.height = srcImage.rows - brectD.y;

	if (brectU.x % 2 != 0)brectU.x += 1;
	if (brectU.y % 2 != 0)brectU.y += 1;
	if (brectU.width % 2 != 0)brectU.width -= 1;
	if (brectU.height % 2 != 0)brectU.height -= 1;
	if (brectD.x % 2 != 0)brectD.x += 1;
	if (brectD.y % 2 != 0)brectD.y += 1;
	if (brectD.width % 2 != 0)brectD.width -= 1;
	if (brectD.height % 2 != 0)brectD.height -= 1;

	Mat srcImageBGR, BGR1, BGR2;
	cvtColor(srcImage, srcImageBGR, CV_GRAY2BGR);
	cvtColor(srcImage, BGR1, CV_GRAY2BGR);
	cvtColor(srcImage, BGR2, CV_GRAY2BGR);

	/*�ڴ���ͼ���ϻ���ROI*/
	for (int i = 0; i < 4; i++)//������
	{
		line(srcImageBGR, verticesU[i], verticesU[(i + 1) % 4], Scalar(0, 0, 255));
		line(srcImageBGR, verticesD[i], verticesD[(i + 1) % 4], Scalar(0, 0, 255));
	}
	//rectangle(srcImageBGR, brectD, Scalar(255, 0, 0));
	//rectangle(srcImageBGR, brectU, Scalar(255, 0, 0));

	/*��ȡROI�ֲ�ͼ��:lineRegionU,lineRegionD������ֱ�߼��*/
	Mat lineRegionU, lineRegionD;
	srcImage(brectU).copyTo(lineRegionU);
	srcImage(brectD).copyTo(lineRegionD);

	/*����ʱ��*/
	double start = double(getTickCount());

	vector<Point2f>linePointU, linePointD;

#if CrossDetectionMode==1
	linePointU = GetLinePointsBaseSobel(srcImage,lineRegionU, brectU.x, brectU.y, 0, 1);
	linePointD = GetLinePointsBaseSobel(srcImage,lineRegionD, brectD.x, brectD.y, 0, 2);

#elif CrossDetectionMode==2 //Sobel��ȡ��Ե+ransac�޳��������+fitline
	GatherEdgePtsInput inputU, inputD;
	GatherEdgePtsOutput outputU, outputD;

	inputU.img = srcImage;
	//inputU.rectangleROI.pt1 = Point2f(brectU.x, brectU.y + brectU.height / 2);
	//inputU.rectangleROI.pt2 = Point2f(brectU.x + brectU.width, brectU.y + brectU.height / 2);
	inputU.rectangleROI.pt1 = (pU1 + pU3) / 2;
	inputU.rectangleROI.pt2 = (pU2 + pU4) / 2;
	inputU.rectangleROI.offset = brectU.height / 2;
	inputU.rectangleROI.direction = 1;//˳ʱ��ɨ�裬������

	inputD.img = srcImage;
	//inputD.rectangleROI.pt1 = Point2f(brectD.x + brectD.width / 2, brectD.y);
	//inputD.rectangleROI.pt2 = Point2f(brectD.x + brectD.width / 2, brectD.y + brectD.height);
	inputD.rectangleROI.pt1 = (pD1 + pD2) / 2;
	inputD.rectangleROI.pt2 = (pD3 + pD4) / 2;
	inputD.rectangleROI.offset = brectD.width / 2;
	inputD.rectangleROI.direction = 0;//��ʱ��ɨ�裬���ϵ���

	/*��ȡ��Ե�㼯linePointU,linePointD*/
	gatherEdgePts(inputU, outputU);
	gatherEdgePts(inputD, outputD);
	linePointU = outputU.imgPts;
	linePointD = outputD.imgPts;

#elif CrossDetectionMode==3//LSD�㷨���ֱ��,opencv4.10�汾���ٿ���
	linePointU = GetLinePointsBaseLsd(lineRegionU, 0, 200, brectU.x, brectU.y);//direction=1:U  direction=2:D
	linePointD = GetLinePointsBaseLsd(lineRegionD, 0, 200, brectD.x, brectD.y);
#elif CrossDetectionMode==4//�ֲ������߼��
	linePointU = GetLinePointsBaseHoughLineP(srcImage, lineRegionU, brectU.x, brectU.y,
		CannyThreshold1, CannyThreshold2,
		HoughThreshold1, HoughThreshold2, HoughThreshold3);
	linePointD = GetLinePointsBaseHoughLineP(srcImage, lineRegionD, brectD.x, brectD.y,
		CannyThreshold1, CannyThreshold2,
		HoughThreshold1, HoughThreshold2, HoughThreshold3);
#endif

	/*����ԭʼ��Ե�㼯*/
	for (int i = 0; i < linePointU.size(); i++)
	{
		BGR1.at<Vec3b>(linePointU[i])[0] = 0;
		BGR1.at<Vec3b>(linePointU[i])[1] = 0;
		BGR1.at<Vec3b>(linePointU[i])[2] = 255;
	}
	for (int i = 0; i < linePointD.size(); i++)
	{
		BGR1.at<Vec3b>(linePointD[i])[0] = 0;
		BGR1.at<Vec3b>(linePointD[i])[1] = 0;
		BGR1.at<Vec3b>(linePointD[i])[2] = 255;
	}

	cout << "before ransac refine: linePointU's size is: " << linePointU.size() << endl;
	cout << "before ransac refine: linePointD's size is: " << linePointD.size() << endl;

	//vector<Vec4d> linesU, linesD;
	vector<Point2f>linesU, linesD;
	ransacLines(linePointU, linesU, ransacDistance, 10, 2000);
	ransacLines(linePointD, linesD, ransacDistance, 10, 2000);
	cout << "after ransac refine: linePointU's size is: " << linePointU.size() << endl;
	cout << "after ransac refine: linePointD's size is: " << linePointD.size() << endl;

	/*����ransacɸѡ��ĵ㼯*/
	for (int i = 0; i < linePointU.size(); i++)
	{
		BGR2.at<Vec3b>(linePointU[i])[0] = 0;
		BGR2.at<Vec3b>(linePointU[i])[1] = 0;
		BGR2.at<Vec3b>(linePointU[i])[2] = 255;
	}
	for (int i = 0; i < linePointD.size(); i++)
	{
		BGR2.at<Vec3b>(linePointD[i])[0] = 0;
		BGR2.at<Vec3b>(linePointD[i])[1] = 0;
		BGR2.at<Vec3b>(linePointD[i])[2] = 255;
	}

	GatherLineInput inputLU;
	GatherLineInput inputLD;
	inputLU.edgePts = linePointU;
	inputLD.edgePts = linePointD;
	//inputLU.edgePts = linesU;
	//inputLD.edgePts = linesD;

	GatherLineOutput outputLU, outputLD;
	gatherLine(inputLU, outputLU);
	gatherLine(inputLD, outputLD);

	Point2f ptU1 = outputLU.fitLine.pt1;
	Point2f ptU2 = outputLU.fitLine.pt2;
	Point2f ptD1 = outputLD.fitLine.pt1;
	Point2f ptD2 = outputLD.fitLine.pt2;

	float ka = (float)((ptU2.y - ptU1.y) / (ptU2.x - ptU1.x + 1e-16));
	float kb = (float)((ptD2.y - ptD1.y) / (ptD2.x - ptD1.x + 1e-16));

	float ma = ptU1.y - ka * ptU1.x;
	float mb = ptD1.y - kb * ptD1.x;

	Point2f crossPoint;
	crossPoint.x = (mb - ma) / (ka - kb);
	crossPoint.y = (ma * kb - mb * ka) / (kb - ka);

	line(srcImageBGR, ptU2, crossPoint, Scalar(0, 0, 255), 1);
	line(srcImageBGR, ptD2, crossPoint, Scalar(0, 0, 255), 1);

	double duration_ms = (double(getTickCount()) - start) * 1000 / getTickFrequency();


	for (int i = 0; i < linePointU.size(); i++)
	{
		Point pt = linePointU[i];
		if (srcImageBGR.at<Vec3b>(pt)[0] == 0 &&
			srcImageBGR.at<Vec3b>(pt)[1] == 0 &&
			srcImageBGR.at<Vec3b>(pt)[2] == 255)
		{
			srcImageBGR.at<Vec3b>(pt)[0] = 255;
			srcImageBGR.at<Vec3b>(pt)[1] = 0;
			srcImageBGR.at<Vec3b>(pt)[2] = 0;
		}
		else
		{
			srcImageBGR.at<Vec3b>(pt)[0] = 255;
			srcImageBGR.at<Vec3b>(pt)[1] = 0;
			srcImageBGR.at<Vec3b>(pt)[2] = 255;

		}
	}
	for (int i = 0; i < linePointD.size(); i++)
	{
		Point pt = linePointD[i];
		if (srcImageBGR.at<Vec3b>(pt)[0] == 0 &&
			srcImageBGR.at<Vec3b>(pt)[1] == 0 &&
			srcImageBGR.at<Vec3b>(pt)[2] == 255)
		{
			srcImageBGR.at<Vec3b>(pt)[0] = 255;
			srcImageBGR.at<Vec3b>(pt)[1] = 0;
			srcImageBGR.at<Vec3b>(pt)[2] = 0;
		}
		else
		{
			srcImageBGR.at<Vec3b>(linePointD[i])[0] = 255;
			srcImageBGR.at<Vec3b>(linePointD[i])[1] = 0;
			srcImageBGR.at<Vec3b>(linePointD[i])[2] = 255;

		}
	}

	float ans = abs(ka*kb + 1);

	//SinglePicInfo result;
	//result.crossPoint = crossPoint;
	//result.ptU = ptU2;
	//result.ptD = ptD2;
	//result.thetaU = atan(ka);
	//result.thetaD = atan(kb);

	ransacResult.crossPoint = crossPoint;
	ransacResult.ka = ka;
	ransacResult.ma = ma;
	ransacResult.kb = kb;
	ransacResult.mb = mb;
	ransacResult.ransac = ransacDistance;

	cout << "the distance between crossPt and UPt is: " << inputU.rectangleROI.pt1.x - crossPoint.x << endl;
	cout << "the distance between crossPt and DPt is: " << inputD.rectangleROI.pt1.y - crossPoint.y << endl;
	cout << "current ransacDis is: " << ransacDistance << endl;
	cout << "ka is: " << ka << endl;
	cout << "kb is: " << kb << endl;
	cout << "ma is:" << ma << endl;
	cout << "mb is:" << mb << endl;
	//cout << "Best measurement is: " << ans << " for the " << ans << " \n";
	cout << "Best crossPoint is: " << crossPoint << " for the " << a << " image\n";
	std::cout << "It took " << duration_ms << " ms." << "\n" << endl;

	return crossPoint;
}


/*************************************************************
Function:       GetCrossBasedFastShapeR
Description:    ʹ����״ƥ������ֻ��ǰ��ҽǵ�
Input:          srcImage:����ͼ�� maskImage:ģ��ͼ��
Return:         �ǰ��ҽǵ�
**************************************************************/
Point2f GetCrossBaseFastShapeR(Mat& srcImage, Mat& maskImage, RansacTest& ransacResult, char *a)
{
	/*step1:��״ƥ�䣬ROI*/
	ShapeMatchLocation arcShapeMatchLocation = GetShapeTrans(maskImage, srcImage, factor);

	Point2f locate = arcShapeMatchLocation.anchorPt;
	float bestTheta = arcShapeMatchLocation.theta;

	//Rect maskArcRegion = Rect(310, 710, 2000, 2000);
	//Rect maskLineRegion1 = Rect(410 , 950, 600, 400);
	//Rect maskLineRegion2 = Rect(1760, 2138+100, 400, 400);
	//Rect maskLineRegion2 = Rect(1760, 2120+200, 400, 400);

	Rect maskArcRegion = Rect(310, 710, 2000, 2000);
	Rect maskLineRegion1 = Rect(600 - 600+400, 950, 600, 400);
	Rect maskLineRegion2 = Rect(1760, 2320, 400, 400);

	float centerX = maskArcRegion.width / 2 + maskArcRegion.x;
	float centerY = maskArcRegion.height / 2 + maskArcRegion.y;
	float deltaCol = locate.x ;
	float deltaRow = locate.y ;

	float xUA1 = maskLineRegion1.x - centerX, yUA1 = maskLineRegion1.y - centerY;
	float xUA2 = maskLineRegion1.x + maskLineRegion1.width - centerX, yUA2 = maskLineRegion1.y - centerY;
	float xUB1 = maskLineRegion1.x - centerX, yUB1 = maskLineRegion1.y + maskLineRegion1.height - centerY;
	float xUB2 = maskLineRegion1.x + maskLineRegion1.width - centerX, yUB2 = maskLineRegion1.y + maskLineRegion1.height - centerY;

	float xDA1 = maskLineRegion2.x - centerX, yDA1 = maskLineRegion2.y - centerY;
	float xDA2 = maskLineRegion2.x + maskLineRegion2.width - centerX, yDA2 = maskLineRegion2.y - centerY;
	float xDB1 = maskLineRegion2.x - centerX, yDB1 = maskLineRegion2.y + maskLineRegion2.height - centerY;
	float xDB2 = maskLineRegion2.x + maskLineRegion2.width - centerX, yDB2 = maskLineRegion2.y + maskLineRegion2.height - centerY;


	float trxUA1 = cos(bestTheta)*xUA1 - sin(bestTheta)*yUA1 + deltaCol;
	float tryUA1 = sin(bestTheta)*xUA1 + cos(bestTheta)*yUA1 + deltaRow;
	float trxUA2 = cos(bestTheta)*xUA2 - sin(bestTheta)*yUA2 + deltaCol;
	float tryUA2 = sin(bestTheta)*xUA2 + cos(bestTheta)*yUA2 + deltaRow;
	float trxUB1 = cos(bestTheta)*xUB1 - sin(bestTheta)*yUB1 + deltaCol;
	float tryUB1 = sin(bestTheta)*xUB1 + cos(bestTheta)*yUB1 + deltaRow;
	float trxUB2 = cos(bestTheta)*xUB2 - sin(bestTheta)*yUB2 + deltaCol;
	float tryUB2 = sin(bestTheta)*xUB2 + cos(bestTheta)*yUB2 + deltaRow;
	float trxDA1 = cos(bestTheta)*xDA1 - sin(bestTheta)*yDA1 + deltaCol;
	float tryDA1 = sin(bestTheta)*xDA1 + cos(bestTheta)*yDA1 + deltaRow;
	float trxDA2 = cos(bestTheta)*xDA2 - sin(bestTheta)*yDA2 + deltaCol;
	float tryDA2 = sin(bestTheta)*xDA2 + cos(bestTheta)*yDA2 + deltaRow;
	float trxDB1 = cos(bestTheta)*xDB1 - sin(bestTheta)*yDB1 + deltaCol;
	float tryDB1 = sin(bestTheta)*xDB1 + cos(bestTheta)*yDB1 + deltaRow;
	float trxDB2 = cos(bestTheta)*xDB2 - sin(bestTheta)*yDB2 + deltaCol;
	float tryDB2 = sin(bestTheta)*xDB2 + cos(bestTheta)*yDB2 + deltaRow;


	vector<Point2f> contourU, contourD;
	Point2f pU1(trxUA1, tryUA1), pU2(trxUA2, tryUA2), pU3(trxUB1, tryUB1), pU4(trxUB2, tryUB2);
	Point2f pD1(trxDA1, tryDA1), pD2(trxDA2, tryDA2), pD3(trxDB1, tryDB1), pD4(trxDB2, tryDB2);

	contourU.push_back(pU1);
	contourU.push_back(pU2);
	contourU.push_back(pU3);
	contourU.push_back(pU4);
	RotatedRect rectU = minAreaRect(contourU);//��Ӿ���
	Point2f verticesU[4];
	rectU.points(verticesU);//��Ӿ��ε�4������
	Rect brectU = rectU.boundingRect();

	contourD.push_back(pD1);
	contourD.push_back(pD2);
	contourD.push_back(pD3);
	contourD.push_back(pD4);
	RotatedRect rectD = minAreaRect(contourD);//��Ӿ���
	Point2f verticesD[4];
	rectD.points(verticesD);//��Ӿ��ε�4������
	Rect brectD = rectD.boundingRect();

	if (brectU.x % 2 != 0)brectU.x += 1;
	if (brectU.y % 2 != 0)brectU.y += 1;
	if (brectU.width % 2 != 0)brectU.width -= 1;
	if (brectU.height % 2 != 0)brectU.height -= 1;
	if (brectD.x % 2 != 0)brectD.x += 1;
	if (brectD.y % 2 != 0)brectD.y += 1;
	if (brectD.width % 2 != 0)brectD.width -= 1;
	if (brectD.height % 2 != 0)brectD.height -= 1;

	if (brectU.x < 0)
	{
		brectU.width -= abs(brectU.x);
		brectU.x = 0;
	}
	if (brectU.y < 0)
	{
		brectU.height -= abs(brectU.y);
		brectU.y = 0;
	}
	if (brectD.x < 0)
	{
		brectD.width -= abs(brectD.x);
		brectD.x = 0;
	}
	if (brectD.y < 0)
	{
		brectD.height -= abs(brectD.y);
		brectD.y = 0;
	}

	if (brectU.x + brectU.width > srcImage.cols)brectU.width = srcImage.cols - brectU.x;
	if (brectU.y + brectU.height > srcImage.rows)brectU.height = srcImage.rows - brectU.y;
	if (brectD.x + brectD.width > srcImage.cols)brectD.width = srcImage.cols - brectD.x;
	if (brectD.y + brectD.height > srcImage.rows)brectD.height = srcImage.rows - brectD.y;

	Mat srcImageBGR, BGR1, BGR2;
	cvtColor(srcImage, srcImageBGR, CV_GRAY2BGR);
	cvtColor(srcImage, BGR1, CV_GRAY2BGR);
	cvtColor(srcImage, BGR2, CV_GRAY2BGR);

	for (int i = 0; i < 4; i++)//������
	{
		line(srcImageBGR, verticesU[i], verticesU[(i + 1) % 4], Scalar(0, 0, 255));
		line(srcImageBGR, verticesD[i], verticesD[(i + 1) % 4], Scalar(0, 0, 255));
	}
	//rectangle(srcImageBGR, brectD, Scalar(255, 0, 0));
	//rectangle(srcImageBGR, brectU, Scalar(255, 0, 0));


	Mat lineRegionU, lineRegionD;
	srcImage(brectU).copyTo(lineRegionU);
	srcImage(brectD).copyTo(lineRegionD);


	/*ʹ��FastMatch�������Ų�����gray,gradient*/
	double start = double(getTickCount());
	vector<Point2f>linePointU, linePointD;
#if CrossDetectionMode==1
	linePointU = GetLinePointsBaseSobel(srcImage,lineRegionU, brectU.x, brectU.y, 1, 1);//direction=1:U  direction=2:D
	linePointD = GetLinePointsBaseSobel(srcImage,lineRegionD, brectD.x, brectD.y, 1, 2);
#elif CrossDetectionMode==2
	GatherEdgePtsInput inputU, inputD;
	GatherEdgePtsOutput outputU, outputD;

	inputU.img = srcImage;
	//inputU.rectangleROI.pt1 = Point2f(brectU.x, brectU.y + brectU.height / 2);
	//inputU.rectangleROI.pt2 = Point2f(brectU.x + brectU.width, brectU.y + brectU.height / 2);
	//inputU.rectangleROI.offset = brectU.height / 2;
	//inputU.rectangleROI.direction = 1;//˳ʱ��ɨ�裬������

	//inputD.img = srcImage;
	//inputD.rectangleROI.pt1 = Point2f(brectD.x + brectD.width / 2, brectD.y);
	//inputD.rectangleROI.pt2 = Point2f(brectD.x + brectD.width / 2, brectD.y + brectD.height);
	//inputD.rectangleROI.offset = brectD.width / 2;
	//inputD.rectangleROI.direction = 1;//��ʱ��ɨ�裬���ϵ���

	inputU.rectangleROI.pt1 = (pU1 + pU3) / 2;
	inputU.rectangleROI.pt2 = (pU2 + pU4) / 2;
	inputU.rectangleROI.offset = brectU.height / 2;
	inputU.rectangleROI.direction = 1;//˳ʱ��ɨ�裬������

	inputD.img = srcImage;
	//inputD.rectangleROI.pt1 = Point2f(brectD.x + brectD.width / 2, brectD.y);
	//inputD.rectangleROI.pt2 = Point2f(brectD.x + brectD.width / 2, brectD.y + brectD.height);
	inputD.rectangleROI.pt1 = (pD1 + pD2) / 2;
	inputD.rectangleROI.pt2 = (pD3 + pD4) / 2;
	inputD.rectangleROI.offset = brectD.width / 2;
	inputD.rectangleROI.direction = 1;//˳ʱ��ɨ�裬���ϵ���

	gatherEdgePts(inputU, outputU);
	gatherEdgePts(inputD, outputD);
	//getherEdgePtsLsd(lineRegionU, linePointU, brectU.x, brectU.y);
	//getherEdgePtsLsd(lineRegionD, linePointD, brectD.x, brectD.y);

	linePointU = outputU.imgPts;
	linePointD = outputD.imgPts;

#elif CrossDetectionMode==3//LSD�㷨���ֱ��
	linePointU = GetLinePointsBaseLsd(lineRegionU, 0, 200, brectU.x, brectU.y);//direction=1:U  direction=2:D
	linePointD = GetLinePointsBaseLsd(lineRegionD, 0, 200, brectD.x, brectD.y);
#elif CrossDetectionMode==4//�ֲ������߼��
	linePointU = GetLinePointsBaseHoughLineP(srcImage, lineRegionU, brectU.x, brectU.y,
		CannyThreshold1, CannyThreshold2,
		HoughThreshold1, HoughThreshold2, HoughThreshold3);
	linePointD = GetLinePointsBaseHoughLineP(srcImage, lineRegionD, brectD.x, brectD.y,
		CannyThreshold1, CannyThreshold2,
		HoughThreshold1, HoughThreshold2, HoughThreshold3);
#endif

	/*����ԭʼ��Ե�㼯*/
	for (int i = 0; i < linePointU.size(); i++)
	{
		BGR1.at<Vec3b>(linePointU[i])[0] = 0;
		BGR1.at<Vec3b>(linePointU[i])[1] = 0;
		BGR1.at<Vec3b>(linePointU[i])[2] = 255;
	}
	for (int i = 0; i < linePointD.size(); i++)
	{
		BGR1.at<Vec3b>(linePointD[i])[0] = 0;
		BGR1.at<Vec3b>(linePointD[i])[1] = 0;
		BGR1.at<Vec3b>(linePointD[i])[2] = 255;
	}

	cout << "before ransac refine: linePointU's size is: " << linePointU.size() << endl;
	cout << "before ransac refine: linePointD's size is: " << linePointD.size() << endl;

	//vector<Vec4d> linesU, linesD;
	vector<Point2f>linesU, linesD;
	ransacLines(linePointU, linesU, ransacDistance, 10, 2000);
	ransacLines(linePointD, linesD, ransacDistance, 10, 2000);
	cout << "after ransac refine: linePointU's size is: " << linePointU.size() << endl;
	cout << "after ransac refine: linePointD's size is: " << linePointD.size() << endl;

	/*����ransacɸѡ��ĵ㼯*/
	for (int i = 0; i < linePointU.size(); i++)
	{
		BGR2.at<Vec3b>(linePointU[i])[0] = 0;
		BGR2.at<Vec3b>(linePointU[i])[1] = 0;
		BGR2.at<Vec3b>(linePointU[i])[2] = 255;
	}
	for (int i = 0; i < linePointD.size(); i++)
	{
		BGR2.at<Vec3b>(linePointD[i])[0] = 0;
		BGR2.at<Vec3b>(linePointD[i])[1] = 0;
		BGR2.at<Vec3b>(linePointD[i])[2] = 255;
	}

	GatherLineInput inputLU;
	GatherLineInput inputLD;
	inputLU.edgePts = linePointU;
	inputLD.edgePts = linePointD;

	GatherLineOutput outputLU, outputLD;
	gatherLine(inputLU, outputLU);
	gatherLine(inputLD, outputLD);

	Point2f ptU1 = outputLU.fitLine.pt1;
	Point2f ptU2 = outputLU.fitLine.pt2;
	Point2f ptD1 = outputLD.fitLine.pt1;
	Point2f ptD2 = outputLD.fitLine.pt2;


	float ka = (float)((ptU2.y - ptU1.y) / (ptU2.x - ptU1.x + 1e-16));
	float kb = (float)((ptD2.y - ptD1.y) / (ptD2.x - ptD1.x + 1e-16));

	float ma = ptU1.y - ka * ptU1.x;
	float mb = ptD1.y - kb * ptD1.x;

	Point2f crossPoint;
	crossPoint.x = (mb - ma) / (ka - kb);
	crossPoint.y = (ma * kb - mb * ka) / (kb - ka);

	line(srcImageBGR, ptU1, crossPoint, Scalar(0, 0, 255), 1);
	line(srcImageBGR, ptD2, crossPoint, Scalar(0, 0, 255), 1);

	double duration_ms = (double(getTickCount()) - start) * 1000 / getTickFrequency();


	for (int i = 0; i < linePointU.size(); i++)
	{
		Point pt = linePointU[i];
		if (srcImageBGR.at<Vec3b>(pt)[0] == 0 &&
			srcImageBGR.at<Vec3b>(pt)[1] == 0 &&
			srcImageBGR.at<Vec3b>(pt)[2] == 255)
		{
			srcImageBGR.at<Vec3b>(pt)[0] = 255;
			srcImageBGR.at<Vec3b>(pt)[1] = 0;
			srcImageBGR.at<Vec3b>(pt)[2] = 0;
		}
		else
		{
			srcImageBGR.at<Vec3b>(pt)[0] = 255;
			srcImageBGR.at<Vec3b>(pt)[1] = 0;
			srcImageBGR.at<Vec3b>(pt)[2] = 255;

		}
	}
	for (int i = 0; i < linePointD.size(); i++)
	{
		Point pt = linePointD[i];
		if (srcImageBGR.at<Vec3b>(pt)[0] == 0 &&
			srcImageBGR.at<Vec3b>(pt)[1] == 0 &&
			srcImageBGR.at<Vec3b>(pt)[2] == 255)
		{
			srcImageBGR.at<Vec3b>(pt)[0] = 255;
			srcImageBGR.at<Vec3b>(pt)[1] = 0;
			srcImageBGR.at<Vec3b>(pt)[2] = 0;
		}
		else
		{
			srcImageBGR.at<Vec3b>(linePointD[i])[0] = 255;
			srcImageBGR.at<Vec3b>(linePointD[i])[1] = 0;
			srcImageBGR.at<Vec3b>(linePointD[i])[2] = 255;

		}
	}

	SinglePicInfo result;
	result.crossPoint = crossPoint;
	result.ptU = ptU2;
	result.ptD = ptD2;
	result.thetaU = atan(ka);
	result.thetaD = atan(kb);

	ransacResult.crossPoint = crossPoint;
	ransacResult.ka = ka;
	ransacResult.ma = ma;
	ransacResult.kb = kb;
	ransacResult.mb = mb;
	ransacResult.ransac = ransacDistance;

	float ans = ka * kb;
	cout << "the distance between crossPt and UPt is: " << crossPoint.x - inputU.rectangleROI.pt2.x << endl;
	cout << "the distance between crossPt and DPt is: " << inputD.rectangleROI.pt1.y - crossPoint.y << endl;	cout << "current ransacDis is: " << ransacDistance << endl;
	cout << "ka is: " << ka << endl;
	cout << "kb is: " << kb << endl;
	cout << "ma is:" << ma << endl;
	cout << "mb is:" << mb << endl;
	cout << "Best crossPoint is: " << crossPoint << " for the " << a << " image\n";
	std::cout << "It took " << duration_ms << " ms." << "\n" << std::endl;

 	return crossPoint;
}


//-----------------------------------------------GetRandom-----------------------------------------//
//ʵ�֣�ȡ�����
//int interval                ���룺����ĳ�������ڵ������,����: [0-interval]
//����ֵ:	                   [0-interval] ��һ�����
//------------------------------------------------------------------------------------------------//
int  GetRandom(int interval)
{
	//  ����ĳ�������ڵ������,����: [0-interval]

	int n = 10;   // ���Ƶ�������
	int a = 29;  // 1-������ֳ�֮���������
	int b = 5;
	int m = 1000000;  // �㹻�����
	int i;
	int res;
	static  int	RandomSeed = 100;

	for (i = 1; i <= n; i++)
		RandomSeed = (a * RandomSeed + b) % m;

	res = (int)((float)RandomSeed * interval / m);
	return res;
}


float point2line(Point2f p, Point2f p1, Point2f p2)
{
	float a, b, c, dis;
	a = p2.y - p1.y;
	b = p1.x - p2.x;
	c = p2.x * p1.y - p1.x * p2.y;
	dis = float(1.0*abs(a * p.x + b * p.y + c) / sqrt(a * a + b * b));
	return dis;
}


int refinrPointSet(vector<Point2f>& input,
	/*std::vector<cv::Vec4d>& lines*/vector<Point2f>& lines,
	double distance, unsigned int ngon, unsigned int itmax)
{
}

int ransacLines(std::vector<cv::Point2f>& input,
	/*std::vector<cv::Vec4d>& lines*/vector<Point2f>& lines,
	double distance, unsigned int ngon, unsigned int itmax)
{
	unsigned int Mmax = 0;
	cv::Point2f imax;
	cv::Point2f jmax;
	cv::Vec4d line;
	size_t t1, t2;

	/*ransac ���ѡȡ���ӵ�*/
	for (int i = 0; i <int(ngon); ++i) {
		int inter = int(input.size());
		unsigned int it = itmax;
		while (--it)
		{
			t1 = GetRandom(inter);
			t2 = GetRandom(inter);
			int count = 0;
			while (t1 == t2)
			{
				t2 = GetRandom(inter);
				count++;
				if (count > 500)
				{
					return 1;
				}
			}
			unsigned int M = 0;
			Point2f i = input[t1];
			Point2f j = input[t2];
			for (int p = 0; p < input.size(); p++)
			{
				Point2f a = input[p];
				float dis = point2line(a, i, j);
				if (dis < distance)
					++M;
			}
			if (M > Mmax) {
				Mmax = M;
				imax = i;
				jmax = j;
			}
		}
	}

	/*ÿ�����������㼯���ҵ����ŵ�ֱ�߶˵㣬�ų�ransac������ӵ��Ӱ��*/
	/*for (int t1 =0; t1 <input.size(); t1++)
	{
		for (int t2 = t1 +1; t2 < input.size(); t2++)
		{
			Point2f i = input[t1];
			Point2f j = input[t2];

			unsigned int M = 0;
			for (int p = 0; p < input.size(); p++)
			{
				Point2f a = input[p];
				float dis = point2line(a, i, j);
				if (dis < distance)
					++M;
			}
			if (M > Mmax) {
				Mmax = M;
				imax = i;
				jmax = j;
			}
		}
	}*/

	cout << "current Mmax is:" << Mmax << endl;
	cout << "current imax is:" << imax << endl;
	cout << "current jmax is:" << jmax << endl;

	auto iter = input.begin();
	while (iter != input.end())
	{
		float dis = point2line(*iter, imax, jmax);
		if (dis > distance)
			iter = input.erase(iter);
		else ++iter;
	}

	cout << "current input's size is: " << input.size() << endl;

	return 0;
}


int GetFreemanCode(Point2f pt1, Point2f pt2)
{
	float deltaX = pt2.x - pt1.x;
	float deltaY = pt2.y - pt1.y;
	int direction = 20;
	if (deltaX > 0.8 && abs(deltaY) < 0.2)	direction = 0;
	if (deltaX > 0.8 && deltaY < -0.8)		direction = 1;
	if (abs(deltaX) < 0.2 && deltaY < -0.8)	direction = 2;
	if (deltaX < -0.8 && deltaY < -0.8)		direction = 3;
	if (deltaX < -0.8 && abs(deltaY) < 0.2)	direction = 4;
	if (deltaX < -0.8 && deltaY > 0.8)	    direction = 5;
	if (abs(deltaX) < 0.2 && deltaY > 0.8)	direction = 6;
	if (deltaX > 0.8 && deltaY > 0.8)   	direction = 7;
	return direction;
}


/*************************************************************
Function:       EdgesPtsRefine
Description:    ֱ�߱�Ե�㼯�޲�
Input:          srcImage:����ͼ�� maskImage:ģ��ͼ��
Return:         �ǰ��ҽǵ�
**************************************************************/
void EdgesPtsRefine(Mat img, vector<Point2f>& edgePts, float flag)
{

	/*if (flag == 1)
	{
		vector<int> FreemanCodeSetL, FreemanCodeSetR;
		for (int index = 2; index < edgePts.size()-2; index++)
		{
			Point2f pt = edgePts[index];
			for (int indexL = 0; indexL <= 3; indexL++)
			{
				Point2f pt1 = edgePts[index - indexL];
				Point2f pt2 = edgePts[index - indexL - 1];
				int code = GetFreemanCode(pt1, pt2);

			}
		}
	}
	else if (flag==2)
	{

	}
	else cout << "direction error" << endl;*/
}


void getherEdgePtsLsd(Mat img, vector<Point2f>&edgePts, float deltaX, float deltaY)
{
	edgePts = GetLinePointsBaseLsd(img, 0, 200, deltaX, deltaY);
}


//-------------------------------------------- Step2.1 gatherEdgePts---------------------------------//
//���ƣ���ȡ��Ե��
//���ܣ���ȡ��Ե��ģ���������ֱ��
//�����б�0-���� 1-���
//����ֵ��0-�ɹ� 1-ͼ��Ϊ�� 2-�ݶ���ֵ���ò�������Ҫ���� 3-��ͼû�б�Ե
int gatherEdgePts(const GatherEdgePtsInput &input, GatherEdgePtsOutput &output)
{
	Mat img = input.img.clone();

	//Mat element = getStructuringElement(MORPH_RECT, Size(3, 3));
	//erode(img, img, element);
	//dilate(img, img, element);

	int rows = img.cols;
	int cols = img.rows;
	RectangleROI rectROI = input.rectangleROI;

	float scanvx, scanvy;
	vector<Point2f> vertex;

	float len = (float)sqrt(pow(rectROI.pt2.x - rectROI.pt1.x, 2) + pow(rectROI.pt2.y - rectROI.pt1.y, 2));
	float vx = (float)(rectROI.pt2.x - rectROI.pt1.x) / len;//cos
	float vy = (float)(rectROI.pt2.y - rectROI.pt1.y) / len;//sin

	if (rectROI.direction)//˳ʱ��Ϊ1 ��ʱ��Ϊ0
	{
		scanvx = -vy;
		scanvy = vx;
	}
	else {
		scanvx = vy;
		scanvy = -vx;
	}

	//���ں�����ֱ�������ROI�Ľ���
	vertex.push_back(Point2f((float)(rectROI.pt1.x - scanvx * rectROI.offset), (float)(rectROI.pt1.y - scanvy * rectROI.offset)));
	vertex.push_back(Point2f((float)(rectROI.pt2.x - scanvx * rectROI.offset), (float)(rectROI.pt2.y - scanvy * rectROI.offset)));
	vertex.push_back(Point2f((float)(rectROI.pt2.x + scanvx * rectROI.offset), (float)(rectROI.pt2.y + scanvy * rectROI.offset)));
	vertex.push_back(Point2f((float)(rectROI.pt1.x + scanvx * rectROI.offset), (float)(rectROI.pt1.y + scanvy * rectROI.offset)));

	//�ж�ͼ���Ƿ��б�Ե
	double theta = abs(atan2(rectROI.pt2.y - rectROI.pt1.y, rectROI.pt2.x - rectROI.pt1.x));

	int flagDark = 0;
	int edgeProc = 1;
	//����ȡ���ұ��ߵ�ʱ��
	int flagRight = 0;
	Rect boundingRectangle = boundingRect(vertex);

	int expandDis = 0;
	boundingRectangle.x -= expandDis;
	boundingRectangle.y -= expandDis;
	boundingRectangle.height = boundingRectangle.height + 2 * expandDis;
	boundingRectangle.width = boundingRectangle.width + 2 * expandDis;

	if (boundingRectangle.x < 0) {
		boundingRectangle.width += boundingRectangle.x;
		boundingRectangle.x = 0;
	}
	if (boundingRectangle.y < 0) {
		boundingRectangle.height += boundingRectangle.y;
		boundingRectangle.y = 0;
	}
	if (boundingRectangle.y + boundingRectangle.height > img.rows)
		boundingRectangle.height = img.rows - boundingRectangle.y;
	if (boundingRectangle.x + boundingRectangle.width > img.cols)
		boundingRectangle.width = img.cols - boundingRectangle.x;

	Mat subimg = img(boundingRectangle).clone();
	rectROI.pt1 -= Point2f(boundingRectangle.x, boundingRectangle.y);
	rectROI.pt2 -= Point2f(boundingRectangle.x, boundingRectangle.y);

	/*check point1:check if the roi is correct*/
	Mat imageBGR(input.img);
	cvtColor(imageBGR, imageBGR, CV_GRAY2BGR);
	rectangle(imageBGR, boundingRectangle, Scalar(0, 0, 255), 1);
	//cout << "check point1, please insert a breakpoint here." << endl;

	Mat subimgX, subimgY, subimgXY;
	int sobelsize = 3;

	Mat edgeSobel, edgeSobelX, edgeSobelY;
	//Sobel(subimg, edgeSobelX, CV_32F, 0, 1, sobelsize, 1, 0, BORDER_DEFAULT);
	//Sobel(subimg, edgeSobelY, CV_32F, 1, 0, sobelsize, 1, 0, BORDER_DEFAULT);
	//convertScaleAbs(edgeSobelX, subimgX);
	//convertScaleAbs(edgeSobelY, subimgY);
	//subimgXY = Mat::zeros(subimgX.size(), CV_8UC1);

	//addWeighted(subimgX, 0.5, subimgY, 0.5, 0, subimgXY);

	for (int scol = 0; scol < subimgXY.cols; scol++)
	{
		for (int srow = 0; srow < subimgXY.rows; srow++)
		{
			Point2f pt = Point2f(scol, srow);
			int value1 = subimgX.at<uchar>(pt);
			int value2 = subimgY.at<uchar>(pt);
			subimgXY.at<uchar>(pt) = (int)(sqrt(pow(value1, 2) + pow(value2, 2)));
		}
	}
	convertScaleAbs(subimgXY, subimgXY);

	if ((abs(theta - CV_PI) < abs(theta - CV_PI / 2)) || (abs(theta) < abs(theta - CV_PI / 2))) {
		Sobel(subimg, edgeSobel, CV_16S, 0, 1, sobelsize, 1, 0, BORDER_DEFAULT);  //��ˮƽ�ı��� ��ֱ����sobel
	}
	else {
		Sobel(subimg, edgeSobel, CV_16S, 1, 0, sobelsize, 1, 0, BORDER_DEFAULT);  //�Ҵ�ֱ�ı��� ��ֱ����sobel
	}

	Mat subimg2;
	convertScaleAbs(edgeSobel, subimg2);
	int boundPtserror = searchBoundaryForLine(subimg, subimg2, rectROI, flagRight, boundingRectangle, output);

	return 0;
}


int collectPolygonEdgePointsGatherLineGray(const Mat& gray,
	int calMaxGrad, vector<Vec4f> seedEdgeGroups, int polar,
	float Tdist, int Tgrad, int step, int validPts,
	vector<Point2f>& edgePtsGroup, float& sharp)
{
	int H = gray.rows;
	int W = gray.cols;
	uchar* data = gray.data;
	Vec4f seedEdge;
	int xs, ys, xe, ye, xl, yl, x, y, x1, y1, x2, y2, tempMaxgrad, tempabsgrad, grad;
	float len, curlen, nlen, nlen0;
	Vec2f vl, vn;
	//����ÿһ��
	int maxGrad = 0;
	sharp = 0;
	int cnt = 0;

	//int step = 1;
	//int step = 2;
	int tempgrad;
	int flag = 0;
	int signflag = 1;

	for (int m = 0; m < seedEdgeGroups.size(); m++) {
		seedEdge = seedEdgeGroups[m];
		xs = seedEdge[0]; ys = seedEdge[1]; xe = seedEdge[2]; ye = seedEdge[3];
		len = sqrt((float)((xs - xe)*(xs - xe) + (ys - ye)*(ys - ye)));
		if (len <= 0)continue;
		vl[0] = (xe - xs) / len;
		vl[1] = (ye - ys) / len;
		if (polar) {
			vn[0] = -vl[1];                             //����˳ʱ��ķ��߷���
			vn[1] = vl[0];
		}
		else {
			vn[0] = vl[1];
			vn[1] = -vl[0];
		}
		//���߶β���
		curlen = 0;
		xl = xs;
		yl = ys;
		while (curlen <= len) {
			flag = 0;
			signflag = 0;
			xl = int(xs + vl[0] * curlen);             //��ǰ���������ϵĻ�׼��
			yl = int(ys + vl[1] * curlen);
			if (xl < 0 || xl >= W || yl < 0 || yl >= H) {
				curlen += step;
				continue;
			}
			//�ط����ռ�
			maxGrad = 0;
			tempMaxgrad = 0;
			tempabsgrad = 0;
			grad = 0;
			for (nlen = float(-Tdist); nlen <= float(Tdist); nlen++) {
				int pts = 1;
				//������
				x = int(xl + nlen * vn[0]);
				y = int(yl + nlen * vn[1]);
				tempMaxgrad = 0;
				tempgrad = 0;
				while (pts <= validPts) {
					x1 = int(xl + (nlen + pts)*vn[0]);
					y1 = int(yl + (nlen + pts)*vn[1]);
					//�ڲ�����
					x2 = int(xl + (nlen - pts)*vn[0]);
					y2 = int(yl + (nlen - pts)*vn[1]);
					if (x < 0 || x >= W || y < 0 || y >= H ||
						x1 < 0 || x1 >= W || y1 < 0 || y1 >= H || x2 < 0 || x2 >= W || y2 < 0 || y2 >= H)
					{
						pts++;
						continue;
					}
					int grayPix = int(data[x1 + y1 * W] - data[x2 + y2 * W]);
					//int grayPix = int(data[x1 + y1 * W] - data[x + y * W]);
					tempabsgrad = abs(grayPix) / 2;
					if (tempabsgrad > tempMaxgrad) {
						tempMaxgrad = tempabsgrad;
						grad = tempabsgrad;
						tempgrad = grayPix;
						tempgrad /= 2;
					}
					pts++;
				}
				if (calMaxGrad == 0) {
					if (tempgrad<0 && grad > Tgrad && flag == 0) {
						flag = 1;
						signflag = -1;
					}
					if (tempgrad > 0 && grad > Tgrad && flag == 0) {
						flag = 1;
						signflag = 1;
					}
					if (flag == 1 && signflag == -1 && tempgrad > 0 && grad > Tgrad)
						break;
					if (flag == 1 && signflag == 1 && tempgrad < 0 && grad > Tgrad)
						break;
					if (grad > Tgrad && grad > maxGrad && (tempgrad*signflag > 0)) {
						maxGrad = grad;
						nlen0 = nlen;
					}
				}
				else {
					if (grad > Tgrad && grad > maxGrad) {
						maxGrad = grad;
						nlen0 = nlen;
					}
				}
			}

			if (maxGrad > Tgrad) {
				x = int(xl + (nlen0)* vn[0]);
				y = int(yl + (nlen0)* vn[1]);
				edgePtsGroup.push_back(Point2f(x, y));
				sharp += maxGrad; cnt++;
			}
			curlen += step;
		}
	}
	if (edgePtsGroup.size() < 2) {
		return 2;
	}
	if (cnt > 0)sharp /= cnt;
	return 0;
}


//-------------------------------------------- Step2.3 gatherLine------------------------------------------//
//���ƣ�����������ȡֱ��
//���ܣ�ͨ������������������Ϣ��ȡֱ�ߣ�����֧�����ؼ�����������缶�����㣬��Ϊͼ��pixval����Ĭ��ֵ1.0����Ϊ���磬pixval��Ϊ��ǰ����µ�pixval
//����ֵ 0-���� 1-������Ϊ��
void gatherLine(const GatherLineInput &input, GatherLineOutput &output)
{
	vector<Point2f> edgePtsFloat = input.edgePts;
	vector<Vec4d> lineV4;

	//double distace = 3;

	int numpts = int(edgePtsFloat.size());
	Vec4f lineV4f;
	Vec4f temp;                                              //��ϵ�������
	vector<Point2f> vertex;                                  //ROI���ĸ�����
	float k;
	float len;

	RotatedRect rect = minAreaRect(edgePtsFloat);
	len = rect.size.height;
	if (rect.size.height < rect.size.width)
		len = rect.size.width;

	int flagK = 0;

	cv::fitLine(edgePtsFloat, lineV4f, DIST_L2, 0, 0.01, 0.01);
	if (abs(lineV4f[0]) < 1e-6) {
		temp[0] = lineV4f[2];
		temp[1] = (float)(lineV4f[3] - len / 2.0);
		temp[2] = lineV4f[2];
		temp[3] = (float)(lineV4f[3] + len / 2.0);
		flagK = 1;
	}
	else if (abs(asin(lineV4f[1])) > CV_PI / 4) {        //�������������ֱ�� �׵����� ĩ������
		k = (float)(lineV4f[1] / lineV4f[0]);
		temp[0] = (float)(lineV4f[2] - (len / 2.0) / k);
		temp[1] = (float)(lineV4f[3] - len / 2.0);
		temp[2] = (float)(lineV4f[2] + (len / 2.0) / k);
		temp[3] = (float)(lineV4f[3] + len / 2.0);
	}
	else {                                              //�����������ˮƽ �׵����� ĩ������
		k = (float)(lineV4f[1] / lineV4f[0]);
		temp[0] = (float)(lineV4f[2] - len / 2.0);
		temp[1] = (float)(lineV4f[3] - len / 2.0 * k);
		temp[2] = (float)(lineV4f[2] + len / 2.0);
		temp[3] = (float)(lineV4f[3] + len / 2.0 * k);
	}
	output.fitLine.pt1 = Point2f(temp[0], temp[1]);
	output.fitLine.pt2 = Point2f(temp[2], temp[3]);
}


//�ҶȾط��������ؼ�⣬ģ�嶨��
int GetSubPixel(const Mat &img, Point2f &point)
{

	Point2f tempPts = point;
	double data[5][5];
	int rows = img.rows;
	int cols = img.cols;
	if (point.y<2 || point.y>rows - 3 || point.x<2 || point.x>cols - 3) {
		return 0;
	}
	for (int n = (int)point.y - 2; n <= (int)point.y + 2; n++)
	{
		const uchar *idata = img.ptr<uchar>(n);
		for (int m = (int)point.x - 2; m <= (int)point.x + 2; m++)
			data[n - int(point.y) + 2][m - int(point.x) + 2] = (double)idata[m];
	}

	double m00, m10, m20, m11, m01, m02;
	m00 = 0;
	m10 = 0;
	m20 = 0;
	m11 = 0;
	m01 = 0;
	m02 = 0;

	for (int j = 0; j < 5; j++)
	{
		for (int i = 0; i < 5; i++)
		{
			m00 = m00 + data[j][i] * M00[j][i];
			m10 = m10 + data[j][i] * M10[j][i];
			m20 = m20 + data[j][i] * M20[j][i];
			m11 = m11 + data[j][i] * M11[j][i];
			m01 = m01 + data[j][i] * M01[j][i];
			m02 = m02 + data[j][i] * M02[j][i];
		}
	}


	double cos_theta, sin_theta;
	if (sqrt(m01*m01 + m10 * m10) == 0)
	{
		return 1;
	}
	else
	{
		cos_theta = m10 / (sqrt(m01*m01 + m10 * m10));
		sin_theta = m01 / (sqrt(m01*m01 + m10 * m10));
	}


	double m_00, m_10, m_20;
	m_00 = m00;

	m_20 = cos_theta * cos_theta*m20 + 2 * cos_theta*sin_theta*m11 + sin_theta * sin_theta*m02;

	m_10 = sin_theta * m01 + cos_theta * m10;


	double L;
	if (abs(m_10) > 1e-3)
	{
		L = (4 * m_20 - m_00) / (3 * m_10);
	}
	else
	{
		return 0;
	}

	point.y = float(point.y - 5 * L*sin_theta / 2);           //����
	point.x = float(point.x + 5 * L*cos_theta / 2);           //����
	if ((abs(point.y - tempPts.y) > 2) || (abs(point.x - tempPts.x) > 2)) {
		point.y = tempPts.y;
		point.x = tempPts.x;
	}

	return 0;
}


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
	int Tgrad, int validPts, vector<Vec4i> &seedEdgeGroupsOut)
{
	vector<Point2f> edgePtsGroup;
	float sharp;
	//vector<Point> edgePts;
	int H = gray.rows;
	int W = gray.cols;
	uchar* data = gray.data;
	Vec4i seedEdge;
	int xs, ys, xe, ye, xl, yl, x, y, x1, y1, x2, y2, tempMaxgrad, tempabsgrad, grad;
	float len, curlen, nlen, nlen0;
	Vec2f vl, vn;
	//����ÿһ��
	int maxGrad = 0;
	sharp = 0;
	int cnt = 0;
	int tempgrad;
	int flag = 0;
	int signflag = 1;
	int flagstep = 0;
	if (calMaxGrad == 1)
		Tgrad = 2;
	for (int m = 0; m < seedEdgeGroups.size(); m++) {
		seedEdge = seedEdgeGroups[m];
		xs = seedEdge[0]; ys = seedEdge[1]; xe = seedEdge[2]; ye = seedEdge[3];
		len = sqrt((float)((xs - xe)*(xs - xe) + (ys - ye)*(ys - ye)));
		//int step = int(len / 20);
		int step = 18;
		if (step >= len)
			step = 1;
		//int step = 1;
		if (len <= 0)continue;
		vl[0] = (xe - xs) / len;
		vl[1] = (ye - ys) / len;
		if (polar) {
			vn[0] = -vl[1];                             //����˳ʱ��ķ��߷���
			vn[1] = vl[0];
		}
		else {
			vn[0] = vl[1];
			vn[1] = -vl[0];
		}
		//���߶β���
		curlen = 0;
		xl = xs; yl = ys;
		int flagstep = 0;
		while (curlen <= len) {
			flag = 0;
			signflag = 0;
			xl = int(xs + vl[0] * curlen);             //��ǰ���������ϵĻ�׼��
			yl = int(ys + vl[1] * curlen);
			if (xl < 0 || xl >= W || yl < 0 || yl >= H) {
				curlen += step;
				continue;
			}
			//�ط����ռ�
			maxGrad = 0;
			//vector<float> everylinegrad;
			//vector<int> everylineX;
			//vector<int> everylineY;
			//gradcpie << "image" << endl;

			tempabsgrad = 0;
			grad = 0;
			for (nlen = float(-Tdist); nlen <= float(Tdist); nlen++) {
				int pts = 1;
				////������
				x = int(xl + nlen * vn[0]);
				y = int(yl + nlen * vn[1]);
				tempMaxgrad = 0;
				tempgrad = 0;
				while (pts <= validPts) {
					x1 = int(xl + (nlen + pts)*vn[0]);
					y1 = int(yl + (nlen + pts)*vn[1]);
					//�ڲ�����
					x2 = int(xl + (nlen - pts)*vn[0]);
					y2 = int(yl + (nlen - pts)*vn[1]);
					if (x < 0 || x >= W || y < 0 || y >= H ||
						x1 < 0 || x1 >= W || y1 < 0 || y1 >= H ||
						x2 < 0 || x2 >= W || y2 < 0 || y2 >= H) {
						pts++;
						continue;
					}
					int grayPix = int(data[x1 + y1 * W] - data[x2 + y2 * W]);
					tempabsgrad = abs(grayPix) / 2;
					if (tempabsgrad > tempMaxgrad) {
						tempMaxgrad = tempabsgrad;
						grad = tempabsgrad;
						tempgrad = grayPix;
						tempgrad /= 2;
					}
					pts++;
				}
				if (calMaxGrad == 0) {
					if (tempgrad<0 && grad > Tgrad && flag == 0) {
						flag = 1;
						signflag = -1;
					}
					if (tempgrad > 0 && grad > Tgrad && flag == 0) {
						flag = 1;
						signflag = 1;
					}
					if (flag == 1 && signflag == -1 && tempgrad > 0 && grad > Tgrad)
						break;
					if (flag == 1 && signflag == 1 && tempgrad < 0 && grad > Tgrad)
						break;
					if (grad > Tgrad && grad > maxGrad && (tempgrad*signflag > 0)) {
						maxGrad = grad;
						nlen0 = nlen;
					}
				}
				else {
					if (grad > Tgrad && grad > maxGrad) {
						maxGrad = grad;
						nlen0 = nlen;
					}
				}

			}
			if (maxGrad > Tgrad) {
				x = int(xl + nlen0 * vn[0]);
				y = int(yl + nlen0 * vn[1]);
				edgePtsGroup.push_back(Point(x, y));
				sharp += maxGrad; cnt++;
			}
			curlen += step;

			if (curlen > len && (curlen - step) < len &&flagstep == 0) {
				curlen = len;
				flagstep = 1;
			}
		}
	}
	if (edgePtsGroup.size() < 2) {
		return 2;
	}
	if (cnt > 0)
		sharp /= cnt;
	float distance = 6;                                                              //����ranscan����ֵ�ж�
	//vector<Vec4d> lineV4;
	vector<Point2f>lineV4;
	Vec4f lineV4f;                           //��ȡ�����ֱ��
	if (ransacLines(edgePtsGroup, lineV4, distance, 1, 500))
		return 3;
	if (edgePtsGroup.size() < 2) {
		return 2;
	}
	int ptsCount = int(edgePtsGroup.size() - 1);
	seedEdgeGroupsOut.push_back(Vec4i(edgePtsGroup[0].x, edgePtsGroup[0].y, edgePtsGroup[ptsCount].x, edgePtsGroup[ptsCount].y));
	return 0;
}


//-----------------------------��ȡ������-----------------------//
//0-����ͼ�� 1- �����ȡ������ROI 2-���� 3- ����������
//0-���� 1- �쳣
int searchBoundaryForLine(Mat srcImage, cv::Mat &img, RectangleROI roiRect, int &calMaxGrad, cv::Rect &boundingRectangle, GatherEdgePtsOutput& output)
{
	float len = (float)sqrt(pow(roiRect.pt2.x - roiRect.pt1.x, 2) + pow(roiRect.pt2.y - roiRect.pt1.y, 2));

	vector<Point2f> vertex;
	int step = 1;
	vector<Vec4f> seedEdgeGroups;
	vector<Point2f> edgePtsGroup;
	vector<Point2f> edgePtsWhitegroup;
	int Tgrad = thresholdValue;                                                                 //��֮ǰ��10��Ϊ��20 �ų��ӵ�ĸ���
	float sharp;
	LineStruct lineContour;//��ϵ�������
	LineStruct lineP1;//ROI��p1�����ڵ�ֱ��
	LineStruct lineP2;//ROI��p2�����ڵ�ֱ��
	Vec4f temp;
	seedEdgeGroups.push_back(Vec4f(int(roiRect.pt1.x), int(roiRect.pt1.y), int(roiRect.pt2.x), int(roiRect.pt2.y)));
	int rangeFinal = 400;
	//���м��ٴ���
	int validPts = 1;

	collectPolygonEdgePointsGatherLineGray(img, calMaxGrad, seedEdgeGroups, roiRect.direction, roiRect.offset, Tgrad, step, validPts, edgePtsGroup, sharp);                 //����Ƕ�ε�ROIҲ���Զ�ε��ô˺���

	Mat imgBGR;
	cvtColor(srcImage, imgBGR, CV_GRAY2BGR);
	//cvtColor(srcImage, srcImage, CV_GRAY2BGR);
	output.img = Mat::zeros(img.size(), CV_8UC1);
	for (int i = 0; i < edgePtsGroup.size(); i++) {
		Point2f tempblack = Point2f(float(edgePtsGroup[i].x), float(edgePtsGroup[i].y));

		tempblack += Point2f(boundingRectangle.x, boundingRectangle.y);
		//GetSubPixel(srcImage, tempblack);
		output.imgPts.push_back(tempblack);

		//imgBGR.at<Vec3b>(tempblack)[0] = 0;
		//imgBGR.at<Vec3b>(tempblack)[1] = 0;
		//imgBGR.at<Vec3b>(tempblack)[2] = 255;
		//output.img.at<uchar>(tempblack) = 255;
	}

	if (output.imgPts.size() < 2)
		return 3;
	return 0;
}


float CalDistance(Point2f circlePt, Point2f pt1, Point2f pt2, Point2f pt3)
{
	float d1 = sqrt(pow(circlePt.x - pt1.x, 2) + pow(circlePt.y - pt1.y, 2));
	float d2 = sqrt(pow(circlePt.x - pt2.x, 2) + pow(circlePt.y - pt2.y, 2));
	float d3 = sqrt(pow(circlePt.x - pt3.x, 2) + pow(circlePt.y - pt3.y, 2));

	return (d1 + d2 + d3) / 3;
}


float CalSD(Point2f circlePt, Point2f pt1, Point2f pt2, Point2f pt3)
{
	float d1 = sqrt(pow(circlePt.x - pt1.x, 2) + pow(circlePt.y - pt1.y, 2));
	float d2 = sqrt(pow(circlePt.x - pt2.x, 2) + pow(circlePt.y - pt2.y, 2));
	float d3 = sqrt(pow(circlePt.x - pt3.x, 2) + pow(circlePt.y - pt3.y, 2));
	float meanD = (d1 + d2 + d3) / 3;
	float SD = sqrt(pow(d1 - meanD, 2) + pow(d2 - meanD, 2) + pow(d3 - meanD, 2)) / 3;
	return SD;
}


Point2f GetAccuracyCirclePoint(Point2f pointLW1, Point2f pointLW2, Point2f pointLW3, float theta)
{
	Point2f circlePoint1 = findCircle1(pointLW1, pointLW2, THETA);
	float SD1 = CalSD(circlePoint1, pointLW1, pointLW2, pointLW3);

	Point2f circlePoint2 = findCircle1(pointLW2, pointLW3, THETA);
	float SD2 = CalSD(circlePoint2, pointLW1, pointLW2, pointLW3);

	Point2f circlePoint3 = findCircle1(pointLW1, pointLW3, 2 * THETA);
	float SD3 = CalSD(circlePoint3, pointLW1, pointLW2, pointLW3);

	Point2f resultPoint;
	if (SD1 > SD2)
	{
		if (SD3 > SD2)resultPoint = circlePoint2;
		else resultPoint = circlePoint3;
	}
	else
	{
		if (SD3 < SD1) resultPoint = circlePoint3;
		else resultPoint = circlePoint1;
	}
	return resultPoint;
}