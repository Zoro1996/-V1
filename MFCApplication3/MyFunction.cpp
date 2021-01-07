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
/*Zernik矩*/
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
double thresholdValue = 100;
double ransacDistance = 1.00;

Mat maskImageL;
Mat maskImageR;
//Mat ML;
//Mat MR;

Point2f TransToWorldAxis(Point2f point, Mat& invH)
{
	Point2f resultPoint;

	//invH:4*3
	resultPoint.x = invH.at<float>(0, 0)*point.x + invH.at<float>(0, 1)*point.y + invH.at<float>(0, 2);
	resultPoint.y = invH.at<float>(1, 0)*point.x + invH.at<float>(1, 1)*point.y + invH.at<float>(1, 2);

	return resultPoint;
}



Point2f CalCircleCenter(Point2f pt1, Point2f pt2, float theta)
{
	float XMean = (pt1.x + pt2.x) / 2;
	float YMean = (pt1.y + pt2.y) / 2;
	Point2f ptMean = (pt1 + pt2) / 2;

	float XAddition = sin(theta)*(pt1.y - pt2.y) / (2 * (1 - cos(theta)));
	float YAddition = sin(theta)*(pt2.x - pt1.x) / (2 * (1 - cos(theta)));
	Point2f ptAddition(XAddition, YAddition);

	Point2f pt = ptMean + ptAddition;
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
	//*计算旋转中心，并依据上述标定矩阵，并将图像旋转中心变换到世界坐标。
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
Description:    使用霍夫直线检测算法检测ROI直线段
Input:          image:待测图像,
				CannyThreshold1,CannyThreshold2:Canny算子参数
				HoughThreshold1,HoughThreshold2,HoughThreshold3:霍夫直线检测算子参数
Return:         linePoints:直线点集
**************************************************************/
vector<Point2f> GetLinePointsBaseHoughLineP(Mat& srcImage, Mat& image,
	float deltaX, float deltaY,
	double CannyThreshold1, double CannyThreshold2,
	double HoughThreshold1, double HoughThreshold2, double HoughThreshold3)
{
	Mat edges, imageBGR;
	vector<Vec4f> lines;
	vector<Point2f>linPoints2, linePoints;
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
		/*亚像素处理*/
		GetSubPixel(srcImage, pt);

		/*存点*/
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
	//第一个参数，InputArray类型的image，输入图像，即源图像，需为8位的灰度单通道图像。
	//第二个参数，InputArray类型的circles，经过调用HoughCircles函数后此参数存储了检测到的圆的输出矢量，每个矢量由包含了3个元素的浮点矢量(x, y, radius)表示。
	//第三个参数，int类型的method，即使用的检测方法，目前OpenCV中就霍夫梯度法一种可以使用，它的标识符为CV_HOUGH_GRADIENT，在此参数处填这个标识符即可。
	//第四个参数，double类型的dp，用来检测圆心的累加器图像的分辨率于输入图像之比的倒数，且此参数允许创建一个比输入图像分辨率低的累加器。上述文字不好理解的话，来看例子吧。例如，如果dp= 1时，累加器和输入图像具有相同的分辨率。如果dp=2，累加器便有输入图像一半那么大的宽度和高度。
	//第五个参数，double类型的minDist，为霍夫变换检测到的圆的圆心之间的最小距离，即让我们的算法能明显区分的两个不同圆之间的最小距离。这个参数如果太小的话，多个相邻的圆可能被错误地检测成了一个重合的圆。反之，这个参数设置太大的话，某些圆就不能被检测出来了。
	//第六个参数，double类型的param1，有默认值100。它是第三个参数method设置的检测方法的对应的参数。对当前唯一的方法霍夫梯度法CV_HOUGH_GRADIENT，它表示传递给canny边缘检测算子的高阈值，而低阈值为高阈值的一半。
	//第七个参数，double类型的param2，也有默认值100。它是第三个参数method设置的检测方法的对应的参数。对当前唯一的方法霍夫梯度法CV_HOUGH_GRADIENT，它表示在检测阶段圆心的累加器阈值。它越小的话，就可以检测到更多根本不存在的圆，而它越大的话，能通过检测的圆就更加接近完美的圆形了。
	//第八个参数，int类型的minRadius,有默认值0，表示圆半径的最小值。
	//第九个参数，int类型的maxRadius,也有默认值0，表示圆半径的最大值。
	//需要注意的是，使用此函数可以很容易地检测出圆的圆心，但是它可能找不到合适的圆半径
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
	//拟合方法采用最小二乘法
	fitLine(linePointX, fitLineX, CV_DIST_HUBER, 0, 0.01, 0.01);
	fitLine(linePointY, fitLineY, CV_DIST_HUBER, 0, 0.01, 0.01);
	float ka, kb;
	ka = (float)(fitLineX[1] / (fitLineX[0])); //求出LineA斜率
	kb = (float)(fitLineY[1] / (fitLineY[0])); //求出LineB斜率
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
Description:    使用全局算法检测盖板右图像中的直线和角点
Input:          srcImage:待测图像,
				CannyThreshold1,CannyThreshold2:Canny算子参数
				HoughThreshold1,HoughThreshold2,HoughThreshold3:霍夫直线检测算子参数
Return:         crossPoint:右角点
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
	//拟合方法采用最小二乘法
	fitLine(linePointX, fitLineX, CV_DIST_HUBER, 0, 0.01, 0.01);
	fitLine(linePointY, fitLineY, CV_DIST_HUBER, 0, 0.01, 0.01);

	float ka, kb;
	ka = (float)(fitLineX[1] / (fitLineX[0])); //求出LineA斜率
	kb = (float)(fitLineY[1] / (fitLineY[0])); //求出LineB斜率

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
Description:    计算梯度表
Input:          image:待测图像
Return:         gradientTable:图像梯度表
**************************************************************/
vector<Gradient>GetGradientTable(Mat& image, int modNum)
{
	Mat xgrad;  //x方向上的梯度
	Mat ygrad;  //y方向上的梯度
	Mat xygrad;
	vector<Gradient> gradientTable;

	Sobel(image, xgrad, CV_32F, 1, 0, 3);
	Sobel(image, ygrad, CV_32F, 0, 1, 3);

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
					//gradient.margin = abs(xg) + abs(yg);
					gradient.theta = atan2(yg, xg);
					gradientTable.push_back(gradient);
				}
			}
		}
	}

	return gradientTable;
}



/*返回最高层金字塔逐步长搜索结果*/
vector<ShapeMatchLocation> GetCoarseTrans(Mat& maskImage, Mat& srcImage, int resizeFactor)
{
	//resize maskImage and srcImage
	Mat resizeMaskImage, resizeSrcImage;
	resize(maskImage, resizeMaskImage,
		Size(maskImage.cols / pow(2, resizeFactor), maskImage.rows / pow(2, resizeFactor)));
	resize(srcImage, resizeSrcImage,
		Size(srcImage.cols / pow(2, resizeFactor), srcImage.rows / pow(2, resizeFactor)));

	Mat xgrad;  //x方向上的梯度
	Mat ygrad;  //y方向上的梯度
	Sobel(resizeSrcImage, xgrad, CV_32F, 1, 0, 3);
	Sobel(resizeSrcImage, ygrad, CV_32F, 0, 1, 3);

	vector<Gradient>maskGradientTable = GetGradientTable(resizeMaskImage, 1);
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
			for (float theta = -5 * PI / 180; theta < 5 * PI / 180; theta += 0.5 * PI / 180)
			{
				float similarity = 0;
				for (double i = 0; i < maskGradientTable.size(); i += 1)
				{
					Gradient curMaskGradient = maskGradientTable[i];

					/*模板图像计算的轮廓相对于质心的坐标*/
					float deltaPtX = curMaskGradient.pt.x;
					float deltaPtY = curMaskGradient.pt.y;

					/*计算旋转后的相对坐标*/
					float rotateX = cos(theta)*deltaPtX - sin(theta)*deltaPtY;
					float rotateY = sin(theta)*deltaPtX + cos(theta)*deltaPtY;

					/*待测图像当前点(sx,sy)作为质心，计算质心+旋转坐标pt，用于计算匹配度*/
					Point2f pt = Point2f(rotateX + sx, rotateY + sy);

					/*待测图像边界限制*/
					if (pt.x >= 0 && pt.x < resizeSrcImage.cols - 1
						&& pt.y >= 0 && pt.y < resizeSrcImage.rows - 1)
					{
						float xg = xgrad.at<float>(pt);
						float yg = ygrad.at<float>(pt);
						float gMargin = abs(xg) + abs(yg);
						float gTheta = atan2(yg, xg);

						/*由maskGradientTable的第i个元素坐标，经过变换
						之后计算的待测图向上的对应点的梯度信息*/
						float gDirection1 = cos(gTheta);
						float gDirection2 = sin(gTheta);

						/*计算匹配相似度*/
						similarity += gDirection1 * cos(curMaskGradient.theta + theta)
							+ gDirection2 * sin(curMaskGradient.theta + theta);

						/*早停策略*/
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
	//	/*模板图像计算的轮廓相对于质心的坐标*/
	//	float deltaPtX = curMaskGradient.pt.x;
	//	float deltaPtY = curMaskGradient.pt.y;
	//	/*计算旋转后的相对坐标*/
	//	float rotateX = cos(bestLocation.theta)*deltaPtX - sin(bestLocation.theta)*deltaPtY;
	//	float rotateY = sin(bestLocation.theta)*deltaPtX + cos(bestLocation.theta)*deltaPtY;
	//	/*待测图像当前点(sx,sy)作为质心，计算质心+旋转坐标pt，用于计算匹配度*/
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


/*粗->精*/
vector<ShapeMatchLocation> GetRefinedTrans(Mat& maskImage, Mat& srcImage,
	int resizeFactor, vector<ShapeMatchLocation> coarseLocation)
{
	Mat resizeMaskImage, resizeSrcImage;
	resize(maskImage, resizeMaskImage,
		Size(maskImage.cols / pow(2, resizeFactor), maskImage.rows / pow(2, resizeFactor)));
	resize(srcImage, resizeSrcImage,
		Size(srcImage.cols / pow(2, resizeFactor), srcImage.rows / pow(2, resizeFactor)));

	/*计算缩放后的掩模图像的梯度表*/
	vector<Gradient>maskGradientTable = GetGradientTable(resizeMaskImage, 5);

	vector<ShapeMatchLocation> refineLocation;
	ShapeMatchLocation tempLocation;

	/*待测图像梯度图*/
	Mat xgrad, ygrad;
	Sobel(resizeSrcImage, xgrad, CV_32F, 1, 0, 3);
	Sobel(resizeSrcImage, ygrad, CV_32F, 0, 1, 3);

	int regionX = 5, regionY = 5;
	int factorIndex = coarseLocation[0].resizeFactor - resizeFactor;//相邻搜索金字塔之间的缩放因子
	int scaleFactor = pow(2, factorIndex);
	//float ratio = 0.7;
	//float bestSimilarity = ratio * maskGradientTable.size();
	float bestSimilarity = 0;

	//float stepTheta = (float)(PI / (180 * pow(2, factor - resizeFactor-1)));
	float stepTheta = (float)(0.2 * PI / 180);

	for (int i = 0; i < coarseLocation.size(); i++)
	{
		ShapeMatchLocation curLocation = coarseLocation[i];
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

						/*模板图像计算的轮廓相对于质心的坐标*/
						float deltaPtX = curMaskGradient.pt.x;
						float deltaPtY = curMaskGradient.pt.y;

						/*计算旋转后的相对坐标*/
						float rotateX = cos(theta)*deltaPtX - sin(theta)*deltaPtY;
						float rotateY = sin(theta)*deltaPtX + cos(theta)*deltaPtY;

						/*待测图像当前点(sx,sy)作为质心，计算质心+旋转坐标pt*/
						Point2f pt = Point2f(rotateX + sx, rotateY + sy);

						/*待测图像边界限制*/
						if (pt.x >= 0 && pt.x < resizeSrcImage.cols - 1
							&& pt.y >= 0 && pt.y < resizeSrcImage.rows - 1)
						{
							float xg = xgrad.at<float>(pt);
							float yg = ygrad.at<float>(pt);
							float gMargin = abs(xg) + abs(yg);
							float gTheta = atan2(yg, xg);//[-Pi,Pi]

							/*由maskGradientTable的第i个元素坐标，经过变换
							之后计算的待测图向上的对应点的梯度信息*/
							float gDirection1 = cos(gTheta);
							float gDirection2 = sin(gTheta);

							/*计算匹配相似度*/
							//similarity += abs(gDirection1 * cos(curMaskGradient.theta + theta)
							//	+ gDirection2 * sin(curMaskGradient.theta + theta));
							similarity += gDirection1 * cos(curMaskGradient.theta + theta)
								+ gDirection2 * sin(curMaskGradient.theta + theta);

							/*早停策略*/
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
	//	/*模板图像计算的轮廓相对于质心的坐标*/
	//	float deltaPtX = curMaskGradient.pt.x;
	//	float deltaPtY = curMaskGradient.pt.y;
	//	/*计算旋转后的相对坐标*/
	//	float rotateX = cos(bestLocation.theta)*deltaPtX - sin(bestLocation.theta)*deltaPtY;
	//	float rotateY = sin(bestLocation.theta)*deltaPtX + cos(bestLocation.theta)*deltaPtY;
	//	/*待测图像当前点(sx,sy)作为质心，计算质心+旋转坐标pt，用于计算匹配度*/
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


/*最底层金字塔，计算bestTrans*/
ShapeMatchLocation GetBestTrans(Mat& maskImage, Mat& srcImage, vector<ShapeMatchLocation>refinedLocation)
{
	/*计算缩放后的掩模图像的梯度表*/
	vector<Gradient>maskGradientTable = GetGradientTable(maskImage, 10);
	ShapeMatchLocation bestLocation;

	/*待测图像梯度图*/
	Mat xgrad, ygrad;
	Sobel(srcImage, xgrad, CV_32F, 1, 0, 3);
	Sobel(srcImage, ygrad, CV_32F, 0, 1, 3);

	int regionX = 20, regionY = 20;
	int factorIndex = refinedLocation[0].resizeFactor;
	int scaleFactor = pow(2, factorIndex);
	float bestSimilarity = 0;
	float stepTheta = 0.05 * PI / 180;

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

						/*模板图像计算的轮廓相对于质心的坐标*/
						float deltaPtX = curMaskGradient.pt.x;
						float deltaPtY = curMaskGradient.pt.y;

						/*计算旋转后的相对坐标*/
						float rotateX = cos(theta)*deltaPtX - sin(theta)*deltaPtY;
						float rotateY = sin(theta)*deltaPtX + cos(theta)*deltaPtY;

						/*待测图像当前点(sx,sy)作为质心，计算质心+旋转坐标pt*/
						Point2f pt = Point2f(rotateX + sx, rotateY + sy);

						/*待测图像边界限制*/
						if (pt.x >= 0 && pt.x < srcImage.cols - 1
							&& pt.y >= 0 && pt.y < srcImage.rows - 1)
						{
							float xg = xgrad.at<float>(pt);
							float yg = ygrad.at<float>(pt);
							float gMargin = abs(xg) + abs(yg);
							float gTheta = atan2(yg, xg);//[-Pi,Pi]

							/*由maskGradientTable的第i个元素坐标，经过变换
							之后计算的待测图向上的对应点的梯度信息*/
							float gDirection1 = cos(gTheta);
							float gDirection2 = sin(gTheta);

							/*计算匹配相似度*/
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

	Mat dstImage(srcImage);
	cvtColor(dstImage, dstImage, CV_GRAY2BGR);
	for (int i = 0; i < maskGradientTable.size(); i++)
	{
		Gradient curMaskGradient = maskGradientTable[i];
		/*模板图像计算的轮廓相对于质心的坐标*/
		float deltaPtX = curMaskGradient.pt.x;
		float deltaPtY = curMaskGradient.pt.y;
		/*计算旋转后的相对坐标*/
		float rotateX = cos(bestLocation.theta)*deltaPtX - sin(bestLocation.theta)*deltaPtY;
		float rotateY = sin(bestLocation.theta)*deltaPtX + cos(bestLocation.theta)*deltaPtY;
		/*待测图像当前点(sx,sy)作为质心，计算质心+旋转坐标pt，用于计算匹配度*/
		Point2f pt = Point2f(rotateX + bestLocation.anchorPt.x, rotateY + bestLocation.anchorPt.y);
		if (pt.x >= 0 && pt.x < srcImage.cols - 1
			&& pt.y >= 0 && pt.y < srcImage.rows - 1)
		{
			dstImage.at<Vec3b>(pt)[0] = 0;
			dstImage.at<Vec3b>(pt)[1] = 0;
			dstImage.at<Vec3b>(pt)[2] = 255;
		}
	}

	return bestLocation;
}



/*************************************************************
Function:       GetShapeTrans
Description:    形状匹配
Input:          maskImage:模板图像 srcImage:待匹配图像
Return:         result:形状匹配结果
**************************************************************/
ShapeMatchLocation GetShapeTrans(Mat& maskImage, Mat& srcImage, int resizeFactor)
{
	int layers = resizeFactor;//the number of layers of the pyramid
	ShapeMatchLocation bestLocation;//best location
	vector<ShapeMatchLocation> coarseLocation, refinedLocation;//coarse location and refined location

	while (resizeFactor + 1)//resizeFactor初始化为5
	{
		if (resizeFactor != 0)
		{
			if (resizeFactor == layers)//粗定位
			{
				coarseLocation = GetCoarseTrans(maskImage, srcImage, resizeFactor);
			}
			else if (resizeFactor == layers - 1)
			{
				refinedLocation = GetRefinedTrans(maskImage, srcImage, resizeFactor, coarseLocation);
			}
			//else //逐层求精
			//{
			//	refinedLocation = GetRefinedTrans(maskImage, srcImage, resizeFactor, refinedLocation);
			//}
			//else if (resizeFactor == layers - 2)
			//{
			//	refinedLocation = GetRefinedTrans(maskImage, srcImage, resizeFactor, refinedLocation);
			//}
		}

		else if (resizeFactor == 0)//最底层的最优解
		{
			//轮廓较为复杂的图像，在金字塔最高层会出现几个候选位置，采用逐级求精策略
			bestLocation = GetBestTrans(maskImage, srcImage, refinedLocation);

			//手机盖板图像轮廓简单，金字塔最高层仅有一个候选位置，因此直接返回最底层计算bestTrans
			//bestLocation = GetBestTrans(maskImage, srcImage, coarseLocation);
		}

		resizeFactor--;
	}

	//cout << "共计" << layers << "层金字塔" << endl;
	//cout << "定位结果：[" << bestLocation.anchorPt.x << "," << bestLocation.anchorPt.y
	//	<< "," << bestLocation.theta << "]" << endl;

	return bestLocation;
}



vector<Point2f> GetLinePointsBaseSobel(Mat srcImage, Mat image, float deltaX, float deltaY, float imagePair, float direction)
{
	vector<Point2f>linePoints, tempLinePoints;

	Mat edges;
	Mat xgrad, xgradabs;  //x方向上的梯度
	Mat ygrad, ygradabs;  //y方向上的梯度
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
					imageBGR.at<Vec3b>(pt2)[0] = 0;
					imageBGR.at<Vec3b>(pt2)[1] = 0;
					imageBGR.at<Vec3b>(pt2)[2] = 255;

					tempLinePoints.push_back(pt2);
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
						imageBGR.at<Vec3b>(pt2)[0] = 0;
						imageBGR.at<Vec3b>(pt2)[1] = 0;
						imageBGR.at<Vec3b>(pt2)[2] = 255;

						tempLinePoints.push_back(pt2);
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
						imageBGR.at<Vec3b>(pt2)[0] = 0;
						imageBGR.at<Vec3b>(pt2)[1] = 0;
						imageBGR.at<Vec3b>(pt2)[2] = 255;

						tempLinePoints.push_back(pt2);
						break;
					}
				}
			}
		}
	}


	vector<Point2f>linPoints2;
	//refinePointSet(tempLinePoints, linPoints2);
	linPoints2 = tempLinePoints;
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
		/*亚像素处理*/
		//GetSubPixel(srcImage, pt);

		/*存点*/
		linePoints.push_back(pt);
	}

	return linePoints;
}


Position CalPosition(Mat& imageL, Mat& imageR, string strL, string strR)
{
	maskImageL = imread(".\\L-12-8.bmp", 0);
	maskImageR = imread(".\\R-12-8.bmp", 0);
	//maskImageL = imread("E:\\数据集\\3号台直角盖板图像\\maskImageL.bmp", 0);
	//maskImageR = imread("E:\\数据集\\3号台直角盖板图像\\maskImageR.bmp", 0);


	FileStorage fs(".\\标定结果.xml", FileStorage::READ);
	//FileStorage fs(".\\直角边工件标定结果.xml", FileStorage::READ);
	Mat invHL, invHR;
	Mat ML, MR;
	Point2f rotatePoint1, rotatePoint2;
	fs["invHL"] >> invHL;
	fs["invHR"] >> invHR;
	fs["ML"] >> ML;
	fs["MR"] >> MR;
	fs["rotatePoint1"] >> rotatePoint1;
	fs["rotatePoint2"] >> rotatePoint2;

	/*计算角点的像素坐标*/
	RansacTest rl, rr;//后续实验调用，暂无用处
	CrossPointInfo resultL, resultR;
	Point2f crossPointL, crossPointR;
	crossPointL = GetCrossBaseFastShapeL(imageL, maskImageL, rl, &strL[0]).crossPoint;
	crossPointR = GetCrossBaseFastShapeR(imageR, maskImageR, rr, &strR[0]).crossPoint;
	//crossPointL = resultL.crossPoint;
	//crossPointR = resultR.crossPoint;

	//角点像素坐标变换至局部世界坐标系
#if	CalibrationMethod ==1
	Point2f crossPointWorldL = TransToWorldAxis(crossPointL, invHL);
	Point2f crossPointWorldR = TransToWorldAxis(crossPointR, invHR);
#elif CalibrationMethod ==2
	Point2f crossPointWorldL = CalWorldPoint(crossPointL, ML);
	Point2f crossPointWorldR = CalWorldPoint(crossPointR, MR);
#endif	

	/*分别减去各自的旋转中心坐标，变换至以旋转中心为原点的统一世界坐标系*/
	Point2f uniformCrossPointL = crossPointWorldL - rotatePoint1;//左角点-左局部世界坐标系旋转中心坐标
	Point2f uniformCrossPointR = crossPointWorldR - rotatePoint2;//右角点-右局部世界坐标系旋转中心坐标

	//计算角点的中心点的统一世界坐标
	Point2f uniformCenterPoint = (uniformCrossPointL + uniformCrossPointR) / 2;

	//在统一世界坐标系下计算盖板边缘的倾斜角度theta
	float theta = atan((uniformCrossPointR.y - uniformCrossPointL.y)
		/ (uniformCrossPointR.x - uniformCrossPointL.x));

	Position position;
	position.uniformCrossPointL = uniformCrossPointL;
	position.uniformCrossPointR = uniformCrossPointR;
	position.uniformCenterPoint = uniformCenterPoint;
	position.theta = theta;

	return position;
}



ControlInstruction GetInstruction(Position& bmPosition, Position& testPosition)
{
	/*计算待测工件移动至基准位置需要移动的偏移量和旋转量*/
	ControlInstruction instruction;

	//计算旋转量alpha
	float theta = -bmPosition.theta + testPosition.theta;

	Point2f bmL = bmPosition.uniformCrossPointL;
	Point2f bmR = bmPosition.uniformCrossPointR;
	Point2f bmC = bmPosition.uniformCenterPoint;
	Point2f testL = testPosition.uniformCrossPointL;
	Point2f testR = testPosition.uniformCrossPointR;
	Point2f testC = testPosition.uniformCenterPoint;

	float rotateBmLX = cos(theta)*bmL.x - sin(theta)*bmL.y;
	float rotateBmLY = sin(theta)*bmL.x + cos(theta)*bmL.y;

	float rotateBmRX = cos(theta)*bmR.x - sin(theta)*bmR.y;
	float rotateBmRY = sin(theta)*bmR.x + cos(theta)*bmR.y;

	float rotateBmCX = cos(theta)*bmC.x - sin(theta)*bmC.y;
	float rotateBmCY = sin(theta)*bmC.x + cos(theta)*bmC.y;

	Point2f rbmL(rotateBmLX, rotateBmLY);
	Point2f rbmR(rotateBmRX, rotateBmRY);
	Point2f rbmC(rotateBmCX, rotateBmCY);

	Point2f commandL = rbmL - testL;
	Point2f commandR = rbmR - testR;
	Point2f commandC = rbmC - testC;


	float errorLX = commandL.x - round(commandL.x);
	float errorLY = commandL.y - round(commandL.y);
	float errorRX = commandR.x - round(commandR.x);
	float errorRY = commandR.y - round(commandR.y);
	float errorCX = commandC.x - round(commandC.x);
	float errorCY = commandC.y - round(commandC.y);


	float commandX, commandY;
	commandX = -commandC.x;
	commandY = -commandC.y;

	instruction.commandTheta = -theta;
	instruction.commandX = commandX;
	instruction.commandY = commandY;

	cout << "左角点X误差: " << errorLX << endl;
	cout << "左角点Y误差: " << errorLY << endl;
	cout << "右角点X误差: " << errorRX << endl;
	cout << "右角点Y误差: " << errorRY << endl;
	cout << "中点X误差: " << errorCX << endl;
	cout << "中点Y误差: " << errorCY << "\n" << endl;

	return instruction;
}



float select(vector<float> s, int left, int right, int k)
{ // 在s[ left .. right ]中选择第k 小的元素
	if (left >= right)
		return abs(s[left]);
	int i = left; // 从左至右的标志
	int j = right + 1; // 从右到左的标志
	float pivot = abs(s[left]); // 将最左面的元素作为分界数据
	while (true)
	{
		do
		{ // 在左侧寻找>= pivot 的元素
			i = i + 1;
		} while (abs(s[i]) < pivot);
		do
		{ // 在右侧寻找<= pivot 的元素
			j = j - 1;
		} while (abs(s[j]) > pivot);
		if (i >= j) // 未发现交换对象
			break;
		float temp = abs(s[i]);
		s[i] = abs(s[j]);
		s[j] = temp;
	}
	if (j - left + 1 == k)
		return pivot;
	s[left] = abs(s[j]); // 设置pivot
	s[j] = pivot;
	if (j - left + 1 < k) // 对一个段递归
		return select(s, j + 1, right, k - j - 1 + left);
	else
		return select(s, left, j - 1, k);
}

float findKth(vector<float>s, int n, int K)
{ // 返回 s[0 .. n - 1]中第K 小的元素
	if (K < 1 || K > n)
		throw "error";
	return select(s, 0, n - 1, K);
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
		if (deltaFreemanCode[i] != 0)//追踪当前点
		{
			/*追踪当前点的左半端*/
			int leftChaseIndex = 1;
			while (deltaFreemanCode[i - leftChaseIndex] == 0)
			{
				leftChaseIndex++;
				if (i - leftChaseIndex == 0)break;
				if (i - leftChaseIndex == srcPointSet.size() - 1)break;
			}

			/*追踪当前点的右半端*/
			int rightChaseIndex = 1;
			while (deltaFreemanCode[i + rightChaseIndex] == 0)
			{
				rightChaseIndex++;
				if (i + rightChaseIndex == 0)break;
				if (i + rightChaseIndex == srcPointSet.size() - 1)break;
			}

			/*在5邻域内变化两次，认为当前点属于异常点*/
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
Description:    使用形状匹配计算手机盖板左角点
Input:          srcImage:待测图像 maskImage:模板图像
Return:         盖板左角点
**************************************************************/
CrossPointInfo GetCrossBaseFastShapeL(Mat& srcImage, Mat& maskImage, RansacTest& ransacResult, char *a)
{
	/*step1:形状匹配，获取局部ROI*/
	ShapeMatchLocation arcShapeMatchLocation = GetShapeTrans(maskImage, srcImage, factor);

	Point2f locate = arcShapeMatchLocation.anchorPt;
	float bestTheta = arcShapeMatchLocation.theta;

	/*3号机模板*/
	//best backup
	//Rect maskArcRegion = Rect(1500, 900, 1370, 1300);
	//Rect maskLineRegion1 = Rect(2988, 850, 600, 400);
	//Rect maskLineRegion2 = Rect(1350, 2100, 400, 400);
	//实际
	Rect maskArcRegion = Rect(1500, 900, 1370, 1300);
	Rect maskLineRegion1 = Rect(2988 - 200, 850, 600, 400);
	Rect maskLineRegion2 = Rect(1350, 2100, 400, 400);

	/*直角边模板*/
	//Rect maskArcRegion = Rect(1640, 620, 2280 - 1640, 1250 - 620);
	//Rect maskLineRegion1 = Rect(2340, 600 - 100, 1000, 400);
	//Rect maskLineRegion2 = Rect(1600 - 100, 1270, 400, 600);

	float centerX = maskArcRegion.width / 2 + maskArcRegion.x;
	float centerY = maskArcRegion.height / 2 + maskArcRegion.y;
	float deltaCol = locate.x;
	float deltaRow = locate.y;

	float xUA1 = maskLineRegion1.x - centerX, yUA1 = maskLineRegion1.y - centerY;
	float xUA2 = maskLineRegion1.x + maskLineRegion1.width - centerX, yUA2 = maskLineRegion1.y - centerY;
	float xUB1 = maskLineRegion1.x - centerX, yUB1 = maskLineRegion1.y + maskLineRegion1.height - centerY;
	float xUB2 = maskLineRegion1.x + maskLineRegion1.width - centerX, yUB2 = maskLineRegion1.y + maskLineRegion1.height - centerY;

	float xDA1 = maskLineRegion2.x - centerX, yDA1 = maskLineRegion2.y - centerY;
	float xDA2 = maskLineRegion2.x + maskLineRegion2.width - centerX, yDA2 = maskLineRegion2.y - centerY;
	float xDB1 = maskLineRegion2.x - centerX, yDB1 = maskLineRegion2.y + maskLineRegion2.height - centerY;
	float xDB2 = maskLineRegion2.x + maskLineRegion2.width - centerX, yDB2 = maskLineRegion2.y + maskLineRegion2.height - centerY;

	//U左上角点
	float trxUA1 = cos(bestTheta)*xUA1 - sin(bestTheta)*yUA1 + deltaCol;
	float tryUA1 = sin(bestTheta)*xUA1 + cos(bestTheta)*yUA1 + deltaRow;
	//U右上角点
	float trxUA2 = cos(bestTheta)*xUA2 - sin(bestTheta)*yUA2 + deltaCol;
	float tryUA2 = sin(bestTheta)*xUA2 + cos(bestTheta)*yUA2 + deltaRow;
	//U左下角点
	float trxUB1 = cos(bestTheta)*xUB1 - sin(bestTheta)*yUB1 + deltaCol;
	float tryUB1 = sin(bestTheta)*xUB1 + cos(bestTheta)*yUB1 + deltaRow;
	//U右下角点
	float trxUB2 = cos(bestTheta)*xUB2 - sin(bestTheta)*yUB2 + deltaCol;
	float tryUB2 = sin(bestTheta)*xUB2 + cos(bestTheta)*yUB2 + deltaRow;
	//D左上角点
	float trxDA1 = cos(bestTheta)*xDA1 - sin(bestTheta)*yDA1 + deltaCol;
	float tryDA1 = sin(bestTheta)*xDA1 + cos(bestTheta)*yDA1 + deltaRow;
	//D右上角点
	float trxDA2 = cos(bestTheta)*xDA2 - sin(bestTheta)*yDA2 + deltaCol;
	float tryDA2 = sin(bestTheta)*xDA2 + cos(bestTheta)*yDA2 + deltaRow;
	//D左下角点
	float trxDB1 = cos(bestTheta)*xDB1 - sin(bestTheta)*yDB1 + deltaCol;
	float tryDB1 = sin(bestTheta)*xDB1 + cos(bestTheta)*yDB1 + deltaRow;
	//D右下角点
	float trxDB2 = cos(bestTheta)*xDB2 - sin(bestTheta)*yDB2 + deltaCol;
	float tryDB2 = sin(bestTheta)*xDB2 + cos(bestTheta)*yDB2 + deltaRow;

	/*获取仿射变换之后的ROI四个角点*/
	vector<Point2f> contourU, contourD;
	Point2f pU1(trxUA1, tryUA1), pU2(trxUA2, tryUA2), pU3(trxUB1, tryUB1), pU4(trxUB2, tryUB2);
	Point2f pD1(trxDA1, tryDA1), pD2(trxDA2, tryDA2), pD3(trxDB1, tryDB1), pD4(trxDB2, tryDB2);

	/*计算ROI的最小外接矩形，作为待测图像的ROI：brectU,brectD*/
	contourU.push_back(pU1);
	contourU.push_back(pU2);
	contourU.push_back(pU3);
	contourU.push_back(pU4);
	RotatedRect rectU = minAreaRect(contourU);//外接矩形
	Point2f verticesU[4];
	rectU.points(verticesU);//外接矩形的4个顶点
	Rect brectU = rectU.boundingRect();

	contourD.push_back(pD1);
	contourD.push_back(pD2);
	contourD.push_back(pD3);
	contourD.push_back(pD4);
	RotatedRect rectD = minAreaRect(contourD);//外接矩形
	Point2f verticesD[4];
	rectD.points(verticesD);//外接矩形的4个顶点
	Rect brectD = rectD.boundingRect();

	/*ROI边界限制*/
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

	/*在待测图向上画出ROI*/
	for (int i = 0; i < 4; i++)//画矩形
	{
		line(srcImageBGR, verticesU[i], verticesU[(i + 1) % 4], Scalar(0, 0, 255));
		line(srcImageBGR, verticesD[i], verticesD[(i + 1) % 4], Scalar(0, 0, 255));
	}
	//rectangle(srcImageBGR, brectD, Scalar(255, 0, 0));
	//rectangle(srcImageBGR, brectU, Scalar(255, 0, 0));

	/*获取ROI局部图像:lineRegionU,lineRegionD。用于直线检测*/
	Mat lineRegionU, lineRegionD;
	srcImage(brectU).copyTo(lineRegionU);
	srcImage(brectD).copyTo(lineRegionD);

	/*计算时间*/
	double start = double(getTickCount());

	vector<Point2f>linePointU, linePointD;

#if CrossDetectionMode==1
	linePointU = GetLinePointsBaseSobel(srcImage, lineRegionU, brectU.x, brectU.y, 0, 1);
	linePointD = GetLinePointsBaseSobel(srcImage, lineRegionD, brectD.x, brectD.y, 0, 2);

#elif CrossDetectionMode==2 //Sobel提取边缘+ransac剔除不理想点+fitline
	GatherEdgePtsInput inputU, inputD;
	GatherEdgePtsOutput outputU, outputD;

	inputU.img = srcImage;
	//inputU.rectangleROI.pt1 = Point2f(brectU.x, brectU.y + brectU.height / 2);
	//inputU.rectangleROI.pt2 = Point2f(brectU.x + brectU.width, brectU.y + brectU.height / 2);
	inputU.rectangleROI.pt1 = (pU1 + pU3) / 2;
	inputU.rectangleROI.pt2 = (pU2 + pU4) / 2;
	inputU.rectangleROI.offset = brectU.height / 2;
	inputU.rectangleROI.direction = 1;//顺时针扫描，从左到右

	inputD.img = srcImage;
	//inputD.rectangleROI.pt1 = Point2f(brectD.x + brectD.width / 2, brectD.y);
	//inputD.rectangleROI.pt2 = Point2f(brectD.x + brectD.width / 2, brectD.y + brectD.height);
	inputD.rectangleROI.pt1 = (pD1 + pD2) / 2;
	inputD.rectangleROI.pt2 = (pD3 + pD4) / 2;
	inputD.rectangleROI.offset = brectD.width / 2;
	inputD.rectangleROI.direction = 0;//逆时针扫描，从上到下

	/*获取边缘点集linePointU,linePointD*/
	gatherEdgePts(inputU, outputU);
	gatherEdgePts(inputD, outputD);

	//refinePointSet(outputU.imgPts, linePointU);
	//refinePointSet(outputD.imgPts, linePointD);

	linePointU = outputU.imgPts;
	linePointD = outputD.imgPts;

#elif CrossDetectionMode==3//LSD算法检测直线,opencv4.10版本不再可用
	linePointU = GetLinePointsBaseLsd(lineRegionU, 0, 200, brectU.x, brectU.y);//direction=1:U  direction=2:D
	linePointD = GetLinePointsBaseLsd(lineRegionD, 0, 200, brectD.x, brectD.y);
#elif CrossDetectionMode==4//局部霍夫线检测
	linePointU = GetLinePointsBaseHoughLineP(srcImage, lineRegionU, brectU.x, brectU.y,
		CannyThreshold1, CannyThreshold2,
		HoughThreshold1, HoughThreshold2, HoughThreshold3);
	linePointD = GetLinePointsBaseHoughLineP(srcImage, lineRegionD, brectD.x, brectD.y,
		CannyThreshold1, CannyThreshold2,
		HoughThreshold1, HoughThreshold2, HoughThreshold3);
#endif

	/*绘制原始边缘点集*/
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

	vector<Point2f>linesU, linesD;
	ransacLines(linePointU, linesU, ransacDistance, 10, 2000);
	ransacLines(linePointD, linesD, ransacDistance, 10, 2000);

	/*绘制ransac筛选后的点集*/
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

	CrossPointInfo result;
	result.crossPoint = crossPoint;
	result.ptU1 = ptU1;
	result.ptD1 = ptD1;
	result.ptU2 = ptU2;
	result.ptD2 = ptD2;
	result.ka = ka;
	result.kb = kb;
	result.thetaU = atan(ka) * 180 / PI;
	result.thetaD = atan(kb) * 180 / PI;
	result.ransacDistance = ransacDistance;
	result.imagePath = string(a);
	result.status = 0;

	cout << "the distance between crossPt and UPt is: " << inputU.rectangleROI.pt1.x - crossPoint.x << endl;
	cout << "the distance between crossPt and DPt is: " << inputD.rectangleROI.pt1.y - crossPoint.y << endl;
	cout << "thetaU is: " << result.thetaU << endl;
	cout << "thetaD is: " << result.thetaD << endl;
	cout << "Best crossPoint is: " << crossPoint << " for the " << a << " image" << "\n" << endl;

	return result;
}


/*************************************************************
Function:       GetCrossBasedFastShapeR
Description:    使用形状匹配计算手机盖板右角点
Input:          srcImage:待测图像 maskImage:模板图像
Return:         盖板右角点
**************************************************************/
CrossPointInfo GetCrossBaseFastShapeR(Mat& srcImage, Mat& maskImage, RansacTest& ransacResult, char *a)
{
	/*step1:形状匹配，ROI*/
	ShapeMatchLocation arcShapeMatchLocation = GetShapeTrans(maskImage, srcImage, factor);

	Point2f locate = arcShapeMatchLocation.anchorPt;
	float bestTheta = arcShapeMatchLocation.theta;

	/*2号机模板*/
	//best backup
	//Rect maskArcRegion = Rect(310, 710, 2000, 2000);
	//Rect maskLineRegion1 = Rect(600 - 600 + 400, 950, 600, 400);
	//Rect maskLineRegion2 = Rect(1760, 2320 - 200, 400, 400);
	//实际
	Rect maskArcRegion = Rect(310, 710, 2000, 2000);
	Rect maskLineRegion1 = Rect(600 - 600 + 400, 950, 600, 400);
	Rect maskLineRegion2 = Rect(1760, 2320 - 200, 400, 400);

	/*直角边模板*/
	//Rect maskArcRegion = Rect(1260, 660, 2090 - 1260, 1500 - 660);
	//Rect maskLineRegion1 = Rect(770, 650-100, 600, 400);
	//Rect maskLineRegion2 = Rect(1870-100, 1120, 400, 600);

	float centerX = maskArcRegion.width / 2 + maskArcRegion.x;
	float centerY = maskArcRegion.height / 2 + maskArcRegion.y;
	float deltaCol = locate.x;
	float deltaRow = locate.y;

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
	RotatedRect rectU = minAreaRect(contourU);//外接矩形
	Point2f verticesU[4];
	rectU.points(verticesU);//外接矩形的4个顶点
	Rect brectU = rectU.boundingRect();

	contourD.push_back(pD1);
	contourD.push_back(pD2);
	contourD.push_back(pD3);
	contourD.push_back(pD4);
	RotatedRect rectD = minAreaRect(contourD);//外接矩形
	Point2f verticesD[4];
	rectD.points(verticesD);//外接矩形的4个顶点
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

	for (int i = 0; i < 4; i++)//画矩形
	{
		line(srcImageBGR, verticesU[i], verticesU[(i + 1) % 4], Scalar(0, 0, 255));
		line(srcImageBGR, verticesD[i], verticesD[(i + 1) % 4], Scalar(0, 0, 255));
	}

	Mat lineRegionU, lineRegionD;
	srcImage(brectU).copyTo(lineRegionU);
	srcImage(brectD).copyTo(lineRegionD);


	/*使用FastMatch搜索最优参数：gray,gradient*/
	double start = double(getTickCount());
	vector<Point2f>linePointU, linePointD;
#if CrossDetectionMode==1
	//direction=1:U  direction=2:D
	linePointU = GetLinePointsBaseSobel(srcImage, lineRegionU, brectU.x, brectU.y, 1, 1);
	linePointD = GetLinePointsBaseSobel(srcImage, lineRegionD, brectD.x, brectD.y, 1, 2);
#elif CrossDetectionMode==2
	GatherEdgePtsInput inputU, inputD;
	GatherEdgePtsOutput outputU, outputD;

	inputU.img = srcImage;
	inputU.rectangleROI.pt1 = (pU1 + pU3) / 2;
	inputU.rectangleROI.pt2 = (pU2 + pU4) / 2;
	inputU.rectangleROI.offset = brectU.height / 2;
	inputU.rectangleROI.direction = 1;//顺时针扫描，从左到右

	inputD.img = srcImage;
	inputD.rectangleROI.pt1 = (pD1 + pD2) / 2;
	inputD.rectangleROI.pt2 = (pD3 + pD4) / 2;
	inputD.rectangleROI.offset = brectD.width / 2;
	inputD.rectangleROI.direction = 1;//顺时针扫描，从上到下

	gatherEdgePts(inputU, outputU);
	gatherEdgePts(inputD, outputD);


	linePointU = outputU.imgPts;
	linePointD = outputD.imgPts;

#elif CrossDetectionMode==3//LSD算法检测直线
	linePointU = GetLinePointsBaseLsd(lineRegionU, 0, 200, brectU.x, brectU.y);//direction=1:U  direction=2:D
	linePointD = GetLinePointsBaseLsd(lineRegionD, 0, 200, brectD.x, brectD.y);
#elif CrossDetectionMode==4//局部霍夫线检测
	linePointU = GetLinePointsBaseHoughLineP(srcImage, lineRegionU, brectU.x, brectU.y,
		CannyThreshold1, CannyThreshold2,
		HoughThreshold1, HoughThreshold2, HoughThreshold3);
	linePointD = GetLinePointsBaseHoughLineP(srcImage, lineRegionD, brectD.x, brectD.y,
		CannyThreshold1, CannyThreshold2,
		HoughThreshold1, HoughThreshold2, HoughThreshold3);
#endif

	/*绘制原始边缘点集*/
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

	//vector<Vec4d> linesU, linesD;
	vector<Point2f>linesU, linesD;
	ransacLines(linePointU, linesU, ransacDistance, 10, 2000);
	ransacLines(linePointD, linesD, ransacDistance, 10, 2000);

	/*绘制ransac筛选后的点集*/
	for (int i = 0; i < linePointU.size(); i++)
	{
		BGR2.at<Vec3b>(linePointU[i])[0] = 255;
		BGR2.at<Vec3b>(linePointU[i])[1] = 0;
		BGR2.at<Vec3b>(linePointU[i])[2] = 255;
	}
	for (int i = 0; i < linePointD.size(); i++)
	{
		BGR2.at<Vec3b>(linePointD[i])[0] = 255;
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

	float ka = (float)((ptU2.y - ptU1.y) / (ptU2.x - ptU1.x));
	float ma = ptU1.y - ka * ptU1.x;
	float kb = (float)((ptD2.y - ptD1.y) / (ptD2.x - ptD1.x));
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

	float ans = abs(ka*kb + 1);

	CrossPointInfo result;
	result.crossPoint = crossPoint;
	result.ptU1 = ptU1;
	result.ptD1 = ptD1;
	result.ptU2 = ptU2;
	result.ptD2 = ptD2;
	result.ka = ka;
	result.kb = kb;
	result.thetaU = atan(ka) * 180 / PI;
	result.thetaD = atan(kb) * 180 / PI;
	result.ransacDistance = ransacDistance;
	result.imagePath = string(a);
	result.status = 0;

	cout << "the distance between crossPt and UPt is: " << inputU.rectangleROI.pt1.x - crossPoint.x << endl;
	cout << "the distance between crossPt and DPt is: " << inputD.rectangleROI.pt1.y - crossPoint.y << endl;
	cout << "thetaU is: " << result.thetaU << endl;
	cout << "thetaD is: " << result.thetaD << endl;
	cout << "Best crossPoint is: " << crossPoint << " for the " << a << " image" << "\n" << endl;

	return result;
}


//-----------------------------------------------GetRandom-----------------------------------------//
//实现：取随机数
//int interval                输入：生成某个区间内的随机数,区间: [0-interval]
//返回值:	                   [0-interval] 的一随机数
//------------------------------------------------------------------------------------------------//
int  GetRandom(int interval)
{
	//  生成某个区间内的随机数,区间: [0-interval]

	int n = 10;   // 递推迭代次数
	int a = 29;  // 1-计算机字长之间的任意数
	int b = 5;
	int m = 1000000;  // 足够大的数
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


int ransacLines(std::vector<cv::Point2f>& input,
	/*std::vector<cv::Vec4d>& lines*/vector<Point2f>& lines,
	double distance, unsigned int ngon, unsigned int itmax)
{
	unsigned int Mmax = 0;
	cv::Point2f imax;
	cv::Point2f jmax;
	cv::Vec4d line;
	size_t t1, t2;

	/*ransac 随机选取种子点*/
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

	/*每次搜索整个点集，找到最优的直线端点，排除ransac随机种子点的影响*/
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

	//cout << "current Mmax is:" << Mmax << endl;
	//cout << "current imax is:" << imax << endl;
	//cout << "current jmax is:" << jmax << endl;

	auto iter = input.begin();
	while (iter != input.end())
	{
		float dis = point2line(*iter, imax, jmax);
		if (dis > distance)
			iter = input.erase(iter);
		else ++iter;
	}

	//cout << "current input's size is: " << input.size() << endl;

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


//-------------------------------------------- Step2.1 gatherEdgePts---------------------------------//
//名称：获取边缘点
//功能：获取边缘点模块用于拟合直线
//参数列表：0-输入 1-输出
//返回值：0-成功 1-图像为空 2-梯度阈值设置不合适需要调整 3-黑图没有边缘
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

	if (rectROI.direction)//顺时针为1 逆时针为0
	{
		scanvx = -vy;
		scanvy = vx;
	}
	else {
		scanvx = vy;
		scanvy = -vx;
	}

	//用于后续求直线与矩形ROI的交点
	vertex.push_back(Point2f((float)(rectROI.pt1.x - scanvx * rectROI.offset), (float)(rectROI.pt1.y - scanvy * rectROI.offset)));
	vertex.push_back(Point2f((float)(rectROI.pt2.x - scanvx * rectROI.offset), (float)(rectROI.pt2.y - scanvy * rectROI.offset)));
	vertex.push_back(Point2f((float)(rectROI.pt2.x + scanvx * rectROI.offset), (float)(rectROI.pt2.y + scanvy * rectROI.offset)));
	vertex.push_back(Point2f((float)(rectROI.pt1.x + scanvx * rectROI.offset), (float)(rectROI.pt1.y + scanvy * rectROI.offset)));

	//判断图像是否含有边缘
	double theta = abs(atan2(rectROI.pt2.y - rectROI.pt1.y, rectROI.pt2.x - rectROI.pt1.x));

	int flagDark = 0;
	int edgeProc = 1;
	//当获取左右边线的时候
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
	//Mat imageBGR(input.img);
	//cvtColor(imageBGR, imageBGR, CV_GRAY2BGR);
	//rectangle(imageBGR, boundingRectangle, Scalar(0, 0, 255), 1);
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
		Sobel(subimg, edgeSobel, CV_16S, 0, 1, sobelsize, 1, 0, BORDER_DEFAULT);  //找水平的边线 垂直方向sobel
	}
	else {
		Sobel(subimg, edgeSobel, CV_16S, 1, 0, sobelsize, 1, 0, BORDER_DEFAULT);  //找垂直的边线 垂直方向sobel
	}

	Mat subimg2;
	convertScaleAbs(edgeSobel, subimg2);
	int boundPtserror = searchBoundaryForLine(subimg, subimg2, rectROI, flagRight, boundingRectangle, output);

	return 0;
}


int collectPolygonEdgePointsGatherLineGray(Mat gray,
	int calMaxGrad, vector<Vec4f> seedEdgeGroups, int polar,
	float Tdist, int Tgrad, int step, int validPts,
	vector<Point2f>& edgePtsGroup, float& sharp)
{
	int H = gray.rows;
	int W = gray.cols;
	Vec4f seedEdge;
	int xs, ys, xe, ye, xl, yl, x, y, x1, y1, x2, y2, tempMaxgrad, tempabsgrad, grad;
	float len, curlen, nlen, nlen0;
	Vec2f vl, vn;
	//对于每一组
	int maxGrad = 0;
	sharp = 0;
	int cnt = 0;

	//int step = 1;
	//int step = 2;
	int tempgrad;
	int flag = 0;
	int signflag = 1;

	/*边缘平滑*/
	//Point2f pt1, pt2, pt3, pt4, pt5, pt6, pt7, pt8, pt9;
	//for (int m = 0; m < seedEdgeGroups.size(); m++) {
	//	seedEdge = seedEdgeGroups[m];
	//	xs = seedEdge[0]; ys = seedEdge[1]; xe = seedEdge[2]; ye = seedEdge[3];
	//	len = sqrt((float)((xs - xe)*(xs - xe) + (ys - ye)*(ys - ye)));
	//	if (len <= 0)continue;
	//	vl[0] = (xe - xs) / len;
	//	vl[1] = (ye - ys) / len;
	//	if (polar) {
	//		vn[0] = -vl[1];                             //沿着顺时针的法线方向
	//		vn[1] = vl[0];
	//	}
	//	else {
	//		vn[0] = vl[1];
	//		vn[1] = -vl[0];
	//	}
	//	//沿线段采样
	//	curlen = 1;
	//	xl = xs;
	//	yl = ys;
	//	while (curlen <= len-1) {
	//		flag = 0;
	//		signflag = 0;
	//		xl = int(xs + vl[0] * curlen);             //当前的连接线上的基准点
	//		yl = int(ys + vl[1] * curlen);
	//		if (xl < 0 || xl >= W || yl < 0 || yl >= H) {
	//			curlen += step;
	//			continue;
	//		}
	//		for (nlen = float(-Tdist)+1; nlen <= float(Tdist)-1; nlen++)
	//		{
	//			int pts = 1;
	//			//采样点
	//			x = xl + nlen * vn[0];
	//			y = yl + nlen * vn[1];
	//			pt5 = Point2f(x, y);
	//			pt1 = pt5 + Point2f(vn[0] - vl[0], vn[1] - vl[1]);
	//			pt2 = pt5 + Point2f(vn[0], vn[1]);
	//			pt3 = pt5 + Point2f(vn[0] + vl[0], vn[1] + vl[1]);
	//			pt4 = pt5 + Point2f(-vl[0], -vl[1]);
	//			pt6 = pt5 + Point2f(vl[0], vl[1]);
	//			pt7 = pt5 + Point2f(-vn[0] - vl[0], -vn[1] - vl[1]);
	//			pt8 = pt5 + Point2f(-vn[0], -vn[1]);
	//			pt9 = pt5 + Point2f(-vn[0] + vl[0], -vn[1] + vl[1]);
	//			if (pt1.x >= 0 && pt1.x < W && pt1.y >= 0 && pt1.y < H
	//				&&pt2.x >= 0 && pt2.x < W && pt2.y >= 0 && pt2.y < H
	//				&&pt3.x >= 0 && pt3.x < W && pt3.y >= 0 && pt3.y < H
	//				&&pt4.x >= 0 && pt4.x < W && pt4.y >= 0 && pt4.y < H
	//				&&pt5.x >= 0 && pt5.x < W && pt5.y >= 0 && pt5.y < H
	//				&&pt6.x >= 0 && pt6.x < W && pt6.y >= 0 && pt6.y < H
	//				&&pt7.x >= 0 && pt7.x < W && pt7.y >= 0 && pt7.y < H
	//				&&pt8.x >= 0 && pt8.x < W && pt8.y >= 0 && pt8.y < H
	//				&&pt9.x >= 0 && pt9.x < W && pt9.y >= 0 && pt9.y < H)
	//			{
	//				//gray.at<uchar>(pt5) = (gray.at<uchar>(pt1) + gray.at<uchar>(pt2) +
	//				//	gray.at<uchar>(pt3) + gray.at<uchar>(pt4) + gray.at<uchar>(pt5) +
	//				//	gray.at<uchar>(pt6) + gray.at<uchar>(pt7) + gray.at<uchar>(pt8) +
	//				//	gray.at<uchar>(pt9)) / 9;
	//				gray.at<uchar>(pt5) = (gray.at<uchar>(pt4) + gray.at<uchar>(pt5) +
	//					gray.at<uchar>(pt6)) / 3;
	//			}
	//		}
	//		curlen += step;
	//	}
	//}

	/*获取边缘点*/
	uchar* data = gray.data;
	for (int m = 0; m < seedEdgeGroups.size(); m++) {
		seedEdge = seedEdgeGroups[m];
		xs = seedEdge[0]; ys = seedEdge[1]; xe = seedEdge[2]; ye = seedEdge[3];
		len = sqrt((float)((xs - xe)*(xs - xe) + (ys - ye)*(ys - ye)));
		if (len <= 0)continue;
		vl[0] = (xe - xs) / len;
		vl[1] = (ye - ys) / len;
		if (polar) {
			vn[0] = -vl[1];                             //沿着顺时针的法线方向
			vn[1] = vl[0];
		}
		else {
			vn[0] = vl[1];
			vn[1] = -vl[0];
		}
		//沿线段采样
		curlen = 0;
		xl = xs;
		yl = ys;
		while (curlen <= len) {
			flag = 0;
			signflag = 0;
			xl = int(xs + vl[0] * curlen);             //当前的连接线上的基准点
			yl = int(ys + vl[1] * curlen);
			if (xl < 0 || xl >= W || yl < 0 || yl >= H) {
				curlen += step;
				continue;
			}
			//沿法向收集
			maxGrad = 0;
			tempMaxgrad = 0;
			tempabsgrad = 0;
			grad = 0;
			for (nlen = float(-Tdist); nlen <= float(Tdist); nlen++)
			{
				int pts = 1;
				//采样点
				x = int(xl + nlen * vn[0]);
				y = int(yl + nlen * vn[1]);
				tempMaxgrad = 0;
				tempgrad = 0;
				while (pts <= validPts)
				{
					x1 = int(xl + (nlen + pts)*vn[0]);
					y1 = int(yl + (nlen + pts)*vn[1]);
					//内采样点
					x2 = int(xl + (nlen - pts)*vn[0]);
					y2 = int(yl + (nlen - pts)*vn[1]);
					if (x < 0 || x >= W || y < 0 || y >= H ||
						x1 < 0 || x1 >= W || y1 < 0 || y1 >= H || x2 < 0 || x2 >= W || y2 < 0 || y2 >= H)
					{
						pts++;
						continue;
					}
					//int grayPix = int(data[x1 + y1 * W] - data[x2 + y2 * W]);
					//int grayPix = int(data[x1 + y1 * W] - data[x + y * W]);
					int grayPix = int(data[x + y * W]);

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
//名称：拟合轮廓点获取直线
//功能：通过拟合输入的轮廓点信息获取直线，可以支持像素级轮廓点或世界级轮廓点，若为图像，pixval采用默认值1.0，若为世界，pixval则为当前相机下的pixval
//返回值 0-正常 1-轮廓点为空
void gatherLine(const GatherLineInput &input, GatherLineOutput &output)
{
	vector<Point2f> edgePtsFloat = input.edgePts;
	vector<Vec4d> lineV4;

	//double distace = 3;

	int numpts = int(edgePtsFloat.size());
	Vec4f lineV4f;
	Vec4f temp;                  //拟合的轮廓线
	vector<Point2f> vertex;      //ROI的四个顶点
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
	else if (abs(asin(lineV4f[1])) > CV_PI / 4) {        //所处理的线是竖直线 首点在上 末点在下
		k = (float)(lineV4f[1] / lineV4f[0]);
		temp[0] = (float)(lineV4f[2] - (len / 2.0) / k);
		temp[1] = (float)(lineV4f[3] - len / 2.0);
		temp[2] = (float)(lineV4f[2] + (len / 2.0) / k);
		temp[3] = (float)(lineV4f[3] + len / 2.0);
	}
	else {                                              //所处理的线是水平 首点在上 末点在下
		k = (float)(lineV4f[1] / lineV4f[0]);
		temp[0] = (float)(lineV4f[2] - len / 2.0);
		temp[1] = (float)(lineV4f[3] - len / 2.0 * k);
		temp[2] = (float)(lineV4f[2] + len / 2.0);
		temp[3] = (float)(lineV4f[3] + len / 2.0 * k);
	}
	output.fitLine.pt1 = Point2f(temp[0], temp[1]);
	output.fitLine.pt2 = Point2f(temp[2], temp[3]);
	output.lineV4f = lineV4f;
}


//灰度矩方法亚像素检测，模板定义
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

	point.y = float(point.y - 5 * L*sin_theta / 2);           //行数
	point.x = float(point.x + 5 * L*cos_theta / 2);           //列数
	if ((abs(point.y - tempPts.y) > 2) || (abs(point.x - tempPts.x) > 2)) {
		point.y = tempPts.y;
		point.x = tempPts.x;
	}

	return 0;
}


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
	//对于每一组
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
			vn[0] = -vl[1];                             //沿着顺时针的法线方向
			vn[1] = vl[0];
		}
		else {
			vn[0] = vl[1];
			vn[1] = -vl[0];
		}
		//沿线段采样
		curlen = 0;
		xl = xs; yl = ys;
		int flagstep = 0;
		while (curlen <= len) {
			flag = 0;
			signflag = 0;
			xl = int(xs + vl[0] * curlen);             //当前的连接线上的基准点
			yl = int(ys + vl[1] * curlen);
			if (xl < 0 || xl >= W || yl < 0 || yl >= H) {
				curlen += step;
				continue;
			}
			//沿法向收集
			maxGrad = 0;
			//vector<float> everylinegrad;
			//vector<int> everylineX;
			//vector<int> everylineY;
			//gradcpie << "image" << endl;

			tempabsgrad = 0;
			grad = 0;
			for (nlen = float(-Tdist); nlen <= float(Tdist); nlen++) {
				int pts = 1;
				////采样点
				x = int(xl + nlen * vn[0]);
				y = int(yl + nlen * vn[1]);
				tempMaxgrad = 0;
				tempgrad = 0;
				while (pts <= validPts) {
					x1 = int(xl + (nlen + pts)*vn[0]);
					y1 = int(yl + (nlen + pts)*vn[1]);
					//内采样点
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
	float distance = 6;                                                              //用于ranscan的阈值判断
	//vector<Vec4d> lineV4;
	vector<Point2f>lineV4;
	Vec4f lineV4f;                           //获取的拟合直线
	if (ransacLines(edgePtsGroup, lineV4, distance, 1, 500))
		return 3;
	if (edgePtsGroup.size() < 2) {
		return 2;
	}
	int ptsCount = int(edgePtsGroup.size() - 1);
	seedEdgeGroupsOut.push_back(Vec4i(edgePtsGroup[0].x, edgePtsGroup[0].y, edgePtsGroup[ptsCount].x, edgePtsGroup[ptsCount].y));
	return 0;
}


//-----------------------------获取轮廓点-----------------------//
//0-输入图像 1- 输入获取轮廓的ROI 2-参数 3- 返回轮廓点
//0-正常 1- 异常
int searchBoundaryForLine(Mat srcImage, cv::Mat &img, RectangleROI roiRect, int &calMaxGrad, cv::Rect &boundingRectangle, GatherEdgePtsOutput& output)
{
	float len = (float)sqrt(pow(roiRect.pt2.x - roiRect.pt1.x, 2) + pow(roiRect.pt2.y - roiRect.pt1.y, 2));

	vector<Point2f> vertex;
	int step = 1;
	vector<Vec4f> seedEdgeGroups;
	vector<Point2f> edgePtsGroup;
	vector<Point2f> edgePtsWhitegroup;
	int Tgrad = thresholdValue;                                                                 //将之前的10变为了20 排除杂点的干扰
	float sharp;
	LineStruct lineContour;//拟合的轮廓线
	LineStruct lineP1;//ROI的p1点所在的直线
	LineStruct lineP2;//ROI的p2点所在的直线
	Vec4f temp;
	seedEdgeGroups.push_back(Vec4f(int(roiRect.pt1.x), int(roiRect.pt1.y), int(roiRect.pt2.x), int(roiRect.pt2.y)));
	int rangeFinal = 400;
	//进行加速处理
	int validPts = 1;

	collectPolygonEdgePointsGatherLineGray(img, calMaxGrad, seedEdgeGroups, roiRect.direction, roiRect.offset, Tgrad, step, validPts, edgePtsGroup, sharp);                 //如果是多段的ROI也可以多次调用此函数

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


Point2f GetAccuracyCirclePoint(Point2f pointW1, Point2f pointW2, Point2f pointW3, float theta)
{
	Point2f circlePoint1 = CalCircleCenter(pointW1, pointW2, theta);
	float SD1 = CalSD(circlePoint1, pointW1, pointW2, pointW3);
	cout << "circlePt1 is: " << circlePoint1 << endl;
	cout << "SD1 is: " << SD1 << endl;

	Point2f circlePoint2 = CalCircleCenter(pointW2, pointW3, theta);
	float SD2 = CalSD(circlePoint2, pointW1, pointW2, pointW3);
	cout << "circlePt2 is: " << circlePoint2 << endl;
	cout << "SD2 is: " << SD2 << endl;

	Point2f circlePoint3 = CalCircleCenter(pointW1, pointW3, 2 * theta);
	float SD3 = CalSD(circlePoint3, pointW1, pointW2, pointW3);
	cout << "circlePt3 is: " << circlePoint3 << endl;
	cout << "SD3 is: " << SD3 << "\n" << endl;

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


bool polynomial_curve_fit(std::vector<cv::Point2f>& key_point, int n, cv::Mat& A)
{
	//Number of key points
	int N = key_point.size();

	//构造矩阵X
	cv::Mat X = cv::Mat::zeros(n + 1, n + 1, CV_32FC1);
	for (int i = 0; i < n + 1; i++)
	{
		for (int j = 0; j < n + 1; j++)
		{
			for (int k = 0; k < N; k++)
			{
				X.at<float>(i, j) = X.at<float>(i, j) +
					std::pow(key_point[k].x, i + j);
			}
		}
	}

	//构造矩阵Y
	cv::Mat Y = cv::Mat::zeros(n + 1, 1, CV_32FC1);
	for (int i = 0; i < n + 1; i++)
	{
		for (int k = 0; k < N; k++)
		{
			Y.at<float>(i, 0) = Y.at<float>(i, 0) +
				std::pow(key_point[k].x, i) * key_point[k].y;
		}
	}

	A = cv::Mat::zeros(n + 1, 1, CV_32FC1);
	//求解矩阵A
	cv::solve(X, Y, A, cv::DECOMP_LU);
	return true;
}


void SaveCrossInfo(vector<CrossPointInfo>&input, CString &strPathName)
{
	ofstream outfile;

	outfile.open(strPathName, ios::out);
	outfile << "index" << "," << "crossPt.x" << "," << "crossPt.y" << "," 
		<< "ptU2.x" << "," << "ptU2.y" << ","
		<< "thetaU"<< "," << "thetaD" << "," 
		<< "image" << endl;

	tuple<int, float, float, float> curResult2;
	for (int i = 0; i < input.size(); i++)
	{
		outfile << i << ","
			<< input[i].crossPoint.x << ","
			<< input[i].crossPoint.y << ","
			<< input[i].ptU2.x << ","
			<< input[i].ptU2.y << ","
			<< input[i].thetaU << ","
			<< input[i].thetaD << ","
			<< input[i].imagePath << endl;
	}
	outfile.close();//关闭文件，保存文件
}

void SaveValue(vector<tuple<float, float, int, int>>&input, CString &strPathName)
{
	ofstream outfile;
	outfile.open(strPathName, ios::out);

	outfile << "index" << "," << "errorX" << "," << "errorY" << ","
		<< "基准图像" << "," << "待测图像" << endl;

	for (int i = 0; i < input.size(); i++)
	{
		tuple<float, float, int, int> temp = input[i];
		outfile << i + 1 << ","
			<< get<0>(temp) << "," << get<1>(temp) << ","
			<< "第" << get<2>(temp) + 1 << "张图" << ","
			<< "第" << get<3>(temp) + 1 << "张图" << endl;
	}
	outfile.close();//关闭文件，保存文件
}

void SavePointSet(vector<Point2f>&Pts, CString &strPathName)
{
	ofstream outfile;
	outfile.open(strPathName, ios::out);
	outfile << "index" << "," << "X" << "," << "Y" << endl;

	tuple<int, float, float, float> curResult2;
	for (int i = 0; i < Pts.size(); i++)
	{
		outfile << i + 1 << ","
			<< Pts[i].x << ","
			<< Pts[i].y << endl;
	}
	outfile.close();
}

void saveSingleCameraTransError(
	vector<tuple<int, int, float, float, float, float, float, float>>&errorTranslationL,
	vector<tuple<int, int, float, float, float, float, float, float>>&errorTranslationR,
	CString& strPathName)
{
	ofstream outfile;
	outfile.open(strPathName, ios::out);
	outfile << "index" << "," << "" << ',' << "图像1" << ',' << "图像2" << ","
		<< "世界坐标差值X" << ',' << "世界坐标差值Y" << ','
		<< "像素坐标差X" << "," << "像素坐标差Y" << "," << "△thetaD"
		<< endl;

	for (int i = 0; i < errorTranslationL.size(); i++)
	{
		tuple<int, int, float, float, float, float, float, float> tempErrorTranslationL = errorTranslationL[i];
		tuple<int, int, float, float, float, float, float, float> tempErrorTranslationR = errorTranslationR[i];

		float errorXL = get<2>(tempErrorTranslationL);
		float errorYL = get<3>(tempErrorTranslationL);
		float errorXLP = get<4>(tempErrorTranslationL);
		float errorYLP = get<5>(tempErrorTranslationL);
		float thetaUL1 = get<6>(tempErrorTranslationL);
		float thetaUL2 = get<7>(tempErrorTranslationL);

		float errorXR = get<2>(tempErrorTranslationR);
		float errorYR = get<3>(tempErrorTranslationR);
		float errorXRP = get<4>(tempErrorTranslationR);
		float errorYRP = get<5>(tempErrorTranslationR);
		float thetaUR1 = get<6>(tempErrorTranslationR);
		float thetaUR2 = get<7>(tempErrorTranslationR);

		outfile << i << "," << "左相机" << ","
			<< "第" << get<1>(tempErrorTranslationL) << "张图" << ","
			<< "第" << get<0>(tempErrorTranslationL) << "张图" << ","
			<< errorXL << "," << errorYL << ","
			<< errorXLP << "," << errorYLP << ","
			<< thetaUL1 - thetaUL2 << ",\n"

			<< i << "," << "右相机" << ","
			<< "第" << get<1>(tempErrorTranslationR) << "张图" << ","
			<< "第" << get<0>(tempErrorTranslationR) << "张图" << ","
			<< errorXR << "," << errorYR << ","
			<< errorXRP << "," << errorYRP << ","
			<< thetaUR1 - thetaUR2 << ",\n"

			<< "两角点坐标平移差值（左-右）" << "," << "" << "," << "" << "," << "" << ","
			<< errorXL - errorXR << "," << errorYL - errorYR << ","
			<< errorXLP - errorXRP << "," << errorYLP - errorYRP

			<< "\n" << endl;
	}
	outfile.close();//关闭文件，保存文件
}

/*存储对位误差*/
void saveAlignmentError(vector<tuple<float, float, int, int>>& errorInfo,
	vector<tuple<CrossPointInfo, CrossPointInfo, float, float>>&errorInfoL,
	vector<tuple<CrossPointInfo, CrossPointInfo, float, float>>	&errorInfoR,
	CString& strPathName)
{
	ofstream outfile;
	outfile.open(strPathName, ios::out);
	outfile << "index" << ',' << "双相机X" << ',' << "双相机Y" << ","
		<< "左相机X" << ',' << "左相机Y" << ','
		<< "右相机X" << "," << "右相机Y" << ","
		<< "基准图像" << "," << "待测图像" << endl;

	for (int i = 0; i < errorInfo.size(); i++)
	{
		tuple<float, float, int, int>tempErrorInfo = errorInfo[i];
		tuple<CrossPointInfo, CrossPointInfo, float, float> tempErrorInfoL = errorInfoL[i];
		tuple<CrossPointInfo, CrossPointInfo, float, float> tempErrorInfoR = errorInfoR[i];

		outfile << i << "," << get<0>(tempErrorInfo) << "," << get<1>(tempErrorInfo) << ","
			<< get<2>(tempErrorInfoL) << "," << get<3>(tempErrorInfoL) << ","
			<< get<2>(tempErrorInfoR) << "," << get<3>(tempErrorInfoR) << ","
			<< "第" << get<2>(tempErrorInfo) << "张图" << ","
			<< "第" << get<3>(tempErrorInfo) << "张图" << endl;

	}
	outfile.close();//关闭文件，保存文件
}



/*存储对位误差*/
void saveInstruction(
	vector<tuple<float, float, float, int, int>>& instruction,
	CString& strPathName)
{
	ofstream outfile;
	outfile.open(strPathName, ios::out);
	outfile << "index" << ',' << "X" << ',' << "Y" << "," << "Theta" << ","
		<< "基准图像" << "," << "待测图像" << endl;

	for (int i = 0; i < instruction.size(); i++)
	{
		tuple<float, float, float, int, int>tempInstruction = instruction[i];

		outfile << i << "," << get<0>(tempInstruction) << ","
			<< get<1>(tempInstruction) << ","
			<< get<2>(tempInstruction) << ","
			<< "第" << get<3>(tempInstruction) << "张图" << ","
			<< "第" << get<4>(tempInstruction) << "张图" << endl;

	}
	outfile.close();//关闭文件，保存文件
}


Point2f CalWorldPoint(Point2f pt, Mat& M)
{
	float u = pt.x;
	float v = pt.y;
	float A = M.at<float>(0, 0) - u * M.at<float>(6, 0);
	float B = M.at<float>(1, 0) - u * M.at<float>(7, 0);
	float C = u - M.at<float>(2, 0);
	float D = M.at<float>(3, 0) - v * M.at<float>(6, 0);
	float E = M.at<float>(4, 0) - v * M.at<float>(7, 0);
	float F = v - M.at<float>(5, 0);

	float Xw = (C * E - B * F) / (A * E - B * D);
	float Yw = (A * F - C * D) / (A * E - B * D);

	return Point2f(Xw, Yw);
}


void GetDiffComponent(DiffComponent &result, Solution x)
{
	float bx = x.bx;
	float by = x.by;
	float bz = x.bz;
	float px = x.px;
	float py = x.py;
	float k = x.k;

	/*r11 = cosβz cosβy ,r12 = cosβz sinβy sinβx − sinβz cosβx 
	r21 = sinβz cosβy ,r22 = sinβz sinβy sinβx + cosβz cosβx 
	r13 = cosβz sinβy cosβx + sinβz sinβx r23 = sinβz sinβy cosβx − cosβz sinβx*/
	result.r11 = cos(bz) * cos(by);
	result.r12 = cos(bz) * sin(by) * sin(bx) - sin(bz) * cos(bx);
	result.r21 = sin(bz) * cos(by);
	result.r22 = sin(bz) * sin(by) * sin(bx) + cos(bz) * cos(bx);
	result.r13 = cos(bz) * sin(by) * cos(bx) + sin(bz) * sin(bx);
	result.r23 = sin(bz) * sin(by) * cos(bx) - cos(bz) * sin(bx);
	result.px = px;
	result.py = py;
	result.k = k;

	result.r11_bx = 0;
	result.r11_by = - cos(bz) * sin(by);
	result.r11_bz = - sin(bz) * cos(by);

	result.r12_bx = cos(bz) * sin(by) * cos(bx) + sin(bz) * sin(bx);
	result.r12_by = cos(bz) * cos(by) * sin(bx);
	result.r12_bz = - sin(bz) * sin(by) * sin(bx) - cos(bz) * cos(bx);

	result.r13_bx = - cos(bz) * sin(by) * sin(bx) + sin(bz) * cos(bx);
	result.r13_by = cos(bz) * cos(by) * cos(bx);
	result.r13_bz = - sin(bz) * sin(by) * cos(bx) + cos(bz) * sin(bx);

	result.r21_bx = 0;
	result.r21_by = - sin(bz) * sin(by);
	result.r21_bz = cos(bz) * cos(by);

	result.r22_bx = sin(bz) * sin(by) * cos(bx) - cos(bz) * sin(bx);
	result.r22_by = sin(bz) * cos(by) * sin(bx);
	result.r22_bz = cos(bz) * sin(by) * sin(bx) - sin(bz) * cos(bx);

	result.r23_bx = - sin(bz) * sin(by) * sin(bx) - cos(bz) * cos(bx);
	result.r23_by = sin(bz) * cos(by) * cos(bx);
	result.r23_bz = cos(bz) * sin(by) * cos(bx) + sin(bz) * sin(bx);
}


Mat GetJacobi(DiffComponent tempD, Mat matSetL, Mat matWorldSet)
{
	int m = matSetL.cols;         //9 points,18 equations
	Mat Jacobi(18, 6, CV_32FC1); //declar Jacobin matrix: 18 * 6

	for (int i = 0; i < m; i++)
	{
		float xW = matWorldSet.at<float>(0, i);
		float yW = matWorldSet.at<float>(1, i);

		float f1_bx = -tempD.k * (tempD.r11_bx * xW + tempD.r12_bx * yW);
		float f1_by = -tempD.k * (tempD.r11_by * xW + tempD.r12_by * yW);
		float f1_bz = -tempD.k * (tempD.r11_bz * xW + tempD.r12_bz * yW);
		float f1_px = -tempD.k;
		float f1_py = 0;

		float f2_bx = -tempD.k * (tempD.r21_bx * xW + tempD.r22_bx * yW);
		float f2_by = -tempD.k * (tempD.r21_by * xW + tempD.r22_by * yW);
		float f2_bz = -tempD.k * (tempD.r21_bz * xW + tempD.r22_bz * yW);
		float f2_px = 0;
		float f2_py = -tempD.k;

		//consider zW=0, we only get the first two components for calculation
		float f1_k = -(tempD.r11 * xW + tempD.r12 * yW + tempD.px);
		float f2_k = -(tempD.r21 * xW + tempD.r22 * yW + tempD.py);


		Jacobi.at<float>(i, 0) = f1_bx;
		Jacobi.at<float>(i, 1) = f1_by;
		Jacobi.at<float>(i, 2) = f1_bz;
		Jacobi.at<float>(i, 3) = f1_px;
		Jacobi.at<float>(i, 4) = f1_py;
		Jacobi.at<float>(i, 5) = f1_k;

		Jacobi.at<float>(i + m, 0) = f2_bx;
		Jacobi.at<float>(i + m, 1) = f2_by;
		Jacobi.at<float>(i + m, 2) = f2_bz;
		Jacobi.at<float>(i + m, 3) = f2_px;
		Jacobi.at<float>(i + m, 4) = f2_py;
		Jacobi.at<float>(i + m, 5) = f2_k;
	}

	return Jacobi;
}


Mat f(Solution xk, Mat matSet, Mat matWorldSet)
{
	/*r11 = cosβz cosβy ,r12 = cosβz sinβy sinβx − sinβz cosβx
	r21 = sinβz cosβy ,r22 = sinβz sinβy sinβx + cosβz cosβx
	r13 = cosβz sinβy cosβx + sinβz sinβx
	r23 = sinβz sinβy cosβx − cosβz sinβx
	fi = ui−k(r11xwi + r12 ywi + r13 zwi + px ),
	f2i = vi−k(r21xwi + r22 ywi + r23 zwi + py ),i = 1,...,m*/

	float r11 = cos(xk.bz) * cos(xk.by);
	float r12 = cos(xk.bz) * sin(xk.by) * sin(xk.bx) - sin(xk.bz) * cos(xk.bx);
	float r21 = sin(xk.bz) * cos(xk.by);
	float r22 = sin(xk.bz) * sin(xk.by) * sin(xk.bx) + cos(xk.bz) * cos(xk.bx);
	float r13 = cos(xk.bz) * sin(xk.by) * cos(xk.bx) + sin(xk.bz) * sin(xk.bx);
	float r23 = sin(xk.bz) * sin(xk.by) * cos(xk.bx) - cos(xk.bz) * sin(xk.bx);

	Mat result(18, 1, CV_32FC1);
	int m = matSet.cols;         //9 points,18 equations
	for (int i = 0; i < m; i++)
	{
		float u = matSet.at<float>(0, i);
		float v = matSet.at<float>(1, i);
		float xW = matWorldSet.at<float>(0, i);
		float yW = matWorldSet.at<float>(1, i);

		result.at<float>(i, 0) = u - xk.k * (r11 * xW + r12 * yW + xk.px);
		result.at<float>(i + m, 0) = v - xk.k * (r21 * xW + r22 * yW + xk.py);
	}


	return result;
}


float GetDiagMaxMatrix(Mat &src)
{
	float result = 0;
	for (int row = 0; row < src.rows; row++)
	{
		float tempValue = src.at<float>(row, row);
		if (result < tempValue)
		{
			result = tempValue;
		}
	}

	return result;
}

float GetMatNorm(Mat &src)
{
	return sqrt(pow(src.at<float>(0, 0), 2) + pow(src.at<float>(1, 0), 2) +
		pow(src.at<float>(2, 0), 2) + pow(src.at<float>(3, 0), 2) +
		pow(src.at<float>(4, 0), 2) + pow(src.at<float>(5, 0), 2) +
		pow(src.at<float>(6, 0), 2) + pow(src.at<float>(7, 0), 2));
}

void LM(Solution x, float mu, vector<Solution> &historyX, Mat matSet, Mat matWorldSet)
{
	Solution xk, xkk;
	xk = x;

	Mat gradientF(6, 1, CV_32FC1,Scalar(5));
	float gradientNorm = GetMatNorm(gradientF);//计算梯度幅值

	float error = 1e6;
	float tau = 1e-2;
	int iter = 0,iterNum = 5*1e3;
	while (gradientNorm > 1e-2 && error > 1e-2 && iter < iterNum)
	{
		iter++;

		historyX.push_back(xk);

		Mat xkMat(6, 1, CV_32FC1);
		Mat xkkMat(6, 1, CV_32FC1, Scalar(0));
		Mat deltaXk(6, 1, CV_32FC1);

		xkMat.at<float>(0, 0) = xk.bx;
		xkMat.at<float>(1, 0) = xk.by;
		xkMat.at<float>(2, 0) = xk.bz;
		xkMat.at<float>(3, 0) = xk.px;
		xkMat.at<float>(4, 0) = xk.py;
		xkMat.at<float>(5, 0) = xk.k;

		//Get Difference component for calculation.
		DiffComponent tempDiffComponent;
		GetDiffComponent(tempDiffComponent, xk);

		//Get Jacobi matrix
		Mat Jacobi = GetJacobi(tempDiffComponent, matSet, matWorldSet);

		Mat G(6, 6, CV_32FC1);
		G = Jacobi.t() * Jacobi;

		Mat diagJ(6, 6, CV_32FC1, Scalar(0));
		diagJ.at<float>(0, 0) = G.at<float>(0, 0);
		diagJ.at<float>(1, 1) = G.at<float>(1, 1);
		diagJ.at<float>(2, 2) = G.at<float>(2, 2);
		diagJ.at<float>(3, 3) = G.at<float>(3, 3);
		diagJ.at<float>(4, 4) = G.at<float>(4, 4);
		diagJ.at<float>(5, 5) = G.at<float>(5, 5);
		//diagJ.at<float>(0, 0) = 1;
		//diagJ.at<float>(1, 1) = 1;
		//diagJ.at<float>(2, 2) = 1;
		//diagJ.at<float>(3, 3) = 1;
		//diagJ.at<float>(4, 4) = 1;
		//diagJ.at<float>(5, 5) = 1;

		//if (iter==1)
		//{
		//	mu = tau * GetDiagMaxMatrix(G);
		//}
		//else
		//{

		//}

		Mat GU =G.clone() + mu * diagJ.clone();
		Mat invGU = GU.inv();
		deltaXk = -invGU * Jacobi.t() * f(xk, matSet, matWorldSet);
		xkkMat = xkMat + deltaXk;

		//计算当前解xk对应的梯度
		gradientF = Jacobi.t() * f(xk, matSet, matWorldSet);
		gradientNorm = GetMatNorm(gradientF);//计算梯度幅值

		xkk.bx = xkkMat.at<float>(0, 0);
		xkk.by = xkkMat.at<float>(1, 0);
		xkk.bz = xkkMat.at<float>(2, 0);
		xkk.px = xkkMat.at<float>(3, 0);
		xkk.py = xkkMat.at<float>(4, 0);
		xkk.k = xkkMat.at<float>(5, 0);

		//update xk
		error = sqrt(pow(xk.bx - xkk.bx, 2) + pow(xk.by - xkk.by, 2) + pow(xk.bz - xkk.bz, 2) +
			pow(xk.px - xkk.px, 2) + pow(xk.py - xkk.py, 2) + pow(xk.k - xkk.k, 2));
		xk = xkk;

		//release all matrix, prepare for next iteration.
		xkMat.release();
		xkkMat.release();
		deltaXk.release();
		G.release();
		invGU.release();
		diagJ.release();
		GU.release();
		Jacobi.release();

		cout << "iter: [" << iter << "\/" << iterNum << "], error is: " << error << endl;
	}

	x = xk;
	cout << "Iteration: " << iter << ", error is: " << error <<
		", [bx, by, bz, px, py, k] is: [" << xk.bx << "," << xk.by <<
		"," << xk.bz << "," << xk.px << "," << xk.py << "," << xk.k << "]" << "\n" << endl;

	cout << "LM calibration finished." << "\n" << endl;
}


void RestoreInfo(string csvPath, vector<CrossPointInfo> &resultVector, vector<Point2f>&pixelAxisSet)
{
	class innerFunc
	{
	public:

		float stringToNum(const string& str)
		{
			istringstream iss(str);
			float num;
			iss >> num;
			return num;
		}
	};

	ifstream inFile(csvPath, ios::in);
	string lineStr;
	vector<vector<string>> strArray;
	while (getline(inFile, lineStr))
	{
		// 存成二维表结构
		stringstream ss(lineStr);
		string str;
		vector<string> lineArray;
		// 按照逗号分隔
		while (getline(ss, str, ','))
			lineArray.push_back(str);
		strArray.push_back(lineArray);
	}

	innerFunc m_innerFunc;
	for (int i = 0; i < strArray.size(); i++)
	{
		if (i == 0)continue;
		int index = (int)(m_innerFunc.stringToNum(strArray[i][0]));
		float crossPtX = m_innerFunc.stringToNum(strArray[i][1]);
		float crossPtY = m_innerFunc.stringToNum(strArray[i][2]);
		float ptU2X = m_innerFunc.stringToNum(strArray[i][3]);
		float ptU2Y = m_innerFunc.stringToNum(strArray[i][4]);
		float thetaU = m_innerFunc.stringToNum(strArray[i][5]);
		float thetaD = m_innerFunc.stringToNum(strArray[i][6]);
		string imagePath = strArray[i][7];

		Point2f crossPoint(crossPtX, crossPtY);
		Point2f ptU2(ptU2X, ptU2Y);

		CrossPointInfo tempLVector;
		tempLVector.index = index;
		tempLVector.crossPoint = crossPoint;
		tempLVector.ptU2 = ptU2;
		tempLVector.thetaU = thetaU;
		tempLVector.thetaD = thetaD;
		tempLVector.imagePath = imagePath;

		pixelAxisSet.push_back(crossPoint);
		resultVector.push_back(tempLVector);
	}
}
