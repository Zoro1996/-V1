#include "pch.h"
#include "MyFunction.h"
#include "MFCApplication3Dlg.h"


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


//float pointWorldSet[4][9] = {
//	0, 4, 8, 8,   4,   0,   0, 4, 8,
//	0, 0, 0, 4.5, 4.5, 4.5, 9, 9, 9,
//	0, 0, 0, 0,   0,   0,   0, 0, 0,
//	1, 1, 1, 1,   1,   1,   1, 1, 1
//};


Point2f TransToWorldAxis(Point2f point, Mat& invH)
{
	Point2f resultPoint;

	//invH:4*3
	resultPoint.x = invH.at<float>(0, 0)*point.x + invH.at<float>(0, 1)*point.y + invH.at<float>(0, 2);
	//cout << invH.at<float>(0, 0) << "," << invH.at<float>(0, 1) << "," << invH.at<float>(0, 2) << endl;
	resultPoint.y = invH.at<float>(1, 0)*point.x + invH.at<float>(1, 1)*point.y + invH.at<float>(1, 2);

	return resultPoint;
}


Point2f CrossInAlignmentSystem(Mat& srcImage, Mat& maskImage)
{
	float delta = 0.1;
	float epsilon = 1;
	float factor = 0.5;
	float resolution = 2 / srcImage.rows;

	clock_t t1 = clock();
	tuple<int, int, float> bestTrans = FastMatch(srcImage, maskImage, delta, epsilon, factor, resolution);

	int tx = 2 * get<0>(bestTrans);
	int ty = 2 * get<1>(bestTrans);
	float theta = get<2>(bestTrans);

	Rect maskRegion = Rect(tx, ty, maskImage.cols, maskImage.rows);
	Mat srcRegion;

	srcImage(maskRegion).copyTo(srcRegion);

	Point2f circleRegionPoint = GetCrossPoint(srcRegion);
	Point2f circlePoint = Point2f(tx + circleRegionPoint.x, ty + circleRegionPoint.y);

	return circlePoint;
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
	float A1, A2, B1, B2, C1, C2, temp;
	A1 = pt1.x - pt2.x;
	B1 = pt1.y - pt2.y;
	C1 = (pow(pt1.x, 2) - pow(pt2.x, 2) + pow(pt1.y, 2) - pow(pt2.y, 2)) / 2;
	A2 = pt3.x - pt2.x;
	B2 = pt3.y - pt2.y;
	C2 = (pow(pt3.x, 2) - pow(pt2.x, 2) + pow(pt3.y, 2) - pow(pt2.y, 2)) / 2;

	temp = A1 * B2 - A2 * B1;

	CircleData CD;

	if (temp == 0) {
		CD.center.x = pt1.x;
		CD.center.y = pt1.y;
	}
	else {
		CD.center.x = (C1*B2 - C2 * B1) / temp;
		CD.center.y = (A1*C2 - A2 * C1) / temp;
	}

	CD.radius = sqrtf((CD.center.x - pt1.x)*(CD.center.x - pt1.x) + (CD.center.y - pt1.y)*(CD.center.y - pt1.y));
	return CD;
}


Point2f GetCrossPoint(Mat&srcImage)
{
	Mat edges;
	Mat dstImage = Mat::zeros(srcImage.size(), srcImage.type());
	// Find the edges in the image using canny detector
	Canny(srcImage, edges, 150, 200);
	// Create a vector to store lines of the image
	vector<Vec4f> lines;
	vector<Point>linePointX, linePointY;
	// Apply Hough Transform
	HoughLinesP(edges, lines, 1, CV_PI / 180, 100, 100, 250);

	// Draw lines on the image
	float epsilon = 0.001;
	for (size_t i = 0; i < lines.size(); i++) {
		Vec4f l = lines[i];
		line(dstImage, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(255), 3, LINE_AA);
		if (abs((l[3] - l[1]) / (l[2] - l[0] + epsilon)) > 5)
		{
			linePointY.push_back(Point(l[0], l[1]));
			linePointY.push_back(Point(l[2], l[3]));
		}
		else
		{
			linePointX.push_back(Point(l[0], l[1]));
			linePointX.push_back(Point(l[2], l[3]));
		}
	}

	Vec4f fitLineX, fitLineY;
	//拟合方法采用最小二乘法
	fitLine(linePointX, fitLineX, CV_DIST_HUBER, 0, 0.01, 0.01);
	fitLine(linePointY, fitLineY, CV_DIST_HUBER, 0, 0.01, 0.01);

	float ka, kb;
	ka = (float)(fitLineX[1] / (fitLineX[0] + 1e-6)); //求出LineA斜率
	kb = (float)(fitLineY[1] / (fitLineY[0] + 1e-6)); //求出LineB斜率

	float ma, mb;
	ma = fitLineX[3] - ka * fitLineX[2];
	mb = fitLineY[3] - kb * fitLineY[2];

	Point2f crossPoint;
	crossPoint.x = (mb - ma) / (ka - kb + 1e-6);
	crossPoint.y = (ma * kb - mb * ka) / (kb - ka + 1e-6);

	return crossPoint;
}


Point2f AfterTrans(tuple<int, int, float>&curTrans, Point2f curPoint, float centerX, float centerY)
{
	Point2f resultPoint;

	int transX = get<0>(curTrans);
	int transY = get<1>(curTrans);
	float theta = get<2>(curTrans);

	resultPoint.x = cos(theta) * (curPoint.x - centerX) - sin(theta)*(curPoint.y - centerY) + centerX + transX;
	resultPoint.y = sin(theta) * (curPoint.x - centerX) + cos(theta)*(curPoint.y - centerY) + centerY + transY;

	return resultPoint;
}


float GradientAtCurPoint(Mat&image, Point2f &pt, float kernel[][3])
{
	float gradient = 0;
	for (int x = -1; x < 2; x++)
	{
		for (int y = -1; y < 2; y++)
		{
			float curValue = (float)(image.at<uchar>(pt.y + y, pt.x + x));
			float curKernelValue = (float)(kernel[y + 1][x + 1]);
			gradient += curKernelValue * curValue;
		}
	}

	//返回归一化后的梯度值
	//float result = (gradient + 4 * 255) / (8 * 255);
	float result = gradient / 255;

	return result;
}


/*计算某一变换对应的特征距离*/
int SingleTransEvaluation(Mat &srcImage, Mat& maskImage, vector<Point2f> &subMaskPointSet,
	tuple<int, int, float>& curTrans, float epsilon)
{
	/*获取模板信息*/
	float centerX = floor(maskImage.cols / 2);
	float centerY = floor(maskImage.rows / 2);

	int num = 0;
	for (int i = 0; i < subMaskPointSet.size(); i++)
	{
		Point2f curPoint = subMaskPointSet[i];
		Point2f transPoint = AfterTrans(curTrans, curPoint, centerX, centerY);
		if (transPoint.x >= 0 && transPoint.x < srcImage.cols - 1 &&
			transPoint.y >= 0 && transPoint.y < srcImage.rows - 1)
		{
			float value1 = maskImage.at<float>(curPoint);
			float value2 = srcImage.at<float>(transPoint);

			if (abs(value1 - value2) < 0.2)
			{
				num++;
			}
		}
	}

	return num;
}


/*构建变换网络*/
vector<tuple<int, int, float>> ConstructNet(int row, int col, float delta)
{
	int lowX = 0;//-5472
	int highX = col;
	int lowY = 0;//-3648
	int highY = row;
	float lowR = -PI;
	float highR = PI;

	int tx_step = int(delta * col);
	int ty_step = int(delta * row);
	float theta_step = delta * 2 * PI;

	int tx, ty;
	float r;
	vector<tuple<int, int, float>> Trans;

	for (int tx_index = lowX; tx_index < highX; tx_index += tx_step)
	{
		tx = tx_index;
		for (int ty_index = lowY; ty_index < highY; ty_index += ty_step)
		{
			ty = ty_index;
			for (float r_index = lowR; r_index < highR; r_index += theta_step)
			{
				r = r_index;
				tuple<int, int, float>curTrans{ tx,ty,r };
				Trans.push_back(curTrans);
			}
		}
	}

	return Trans;
}


/*计算当前TransNet下的最佳变换*/
CurrentBestReusult GetBestTrans(Mat& srcImage, Mat& maskImage, vector<Point2f>& subMaskPointSet,
	vector<tuple<int, int, float>>& TransNet, float delta, float epsilon)
{
	CurrentBestReusult bestResult;
	tuple<int, int, float> bestTrans;

	int bestNum = 0;
	for (int i = 0; i < TransNet.size(); i++)
	{
		tuple<int, int, float> curTrans = TransNet[i];
		int curNum = SingleTransEvaluation(srcImage, maskImage, subMaskPointSet, curTrans, epsilon);

		bestResult.TransNum.push_back(curNum);

		if (bestNum < curNum)
		{
			bestTrans = curTrans;
			bestNum = curNum;
		}
	}

	bestResult.transX = get<0>(bestTrans);
	bestResult.transY = get<1>(bestTrans);
	bestResult.theta = get<2>(bestTrans);
	bestResult.bestNum = bestNum;

	return bestResult;
}


vector <tuple<int, int, float >> GetNextNet(Mat&srcImage, vector<tuple<int, int, float >> &GoodTransNet,
	vector<Point2f>&subMaskPointSet, float centerX, float centerY, float delta)
{
	int lowX = -1;
	int highX = 1;
	int lowY = -1;
	int highY = 1;
	float lowR = -1;
	float highR = 1;

	vector<tuple<int, int, float>> nextTransNet;
	tuple<int, int, float> extendedTrans;
	for (int i = 0; i < GoodTransNet.size(); i++)
	{
		nextTransNet.push_back(GoodTransNet[i]);
		for (int outerX = lowX; outerX <= highX; outerX++)
		{
			for (int outerY = lowY; outerY <= highY; outerY++)
			{
				for (float outerTheta = lowR; outerTheta <= highR; outerTheta++)
				{
					if (outerX == 0 && outerY == 0 && outerTheta == 0)
					{
						continue;
					}
					get<0>(extendedTrans) = get<0>(GoodTransNet[i]) + outerX * delta * srcImage.cols;
					get<1>(extendedTrans) = get<1>(GoodTransNet[i]) + outerY * delta * srcImage.rows;
					get<2>(extendedTrans) = get<2>(GoodTransNet[i]) + outerTheta * delta * 2 * PI;
					nextTransNet.push_back(extendedTrans);
				}
			}
		}
	}

	return nextTransNet;
}


/* I1 : mask; I2 : src*/
tuple<int, int, float> FastMatch(Mat srcImage, Mat maskImage,
	float delta, float epsilon, float factor, float resolution)
{
	/*Step 0 :Sample the subMaskPointSet, Normalize*/
	//cout << "Step 0:Prepare work : Sample subMaskPointSet from the whole maskImage's PointSet." << endl;
	//clock_t t1 = clock();

	resize(srcImage, srcImage, Size(srcImage.cols / 2, srcImage.rows / 2));
	resize(maskImage, maskImage, Size(maskImage.cols / 2, maskImage.rows / 2));

	srcImage.convertTo(srcImage, CV_32FC1);
	maskImage.convertTo(maskImage, CV_32FC1);
	maskImage /= 255;
	srcImage /= 255;

	float row = maskImage.rows;
	float col = maskImage.cols;
	float centerX = floor(col / 2);
	float centerY = floor(row / 2);

	//点集均匀采样
	vector<Point2f>subMaskPointSet;
	float sampleRate = 0.1;
	for (float x = 0; x < col; x += col * sampleRate)
	{
		for (float y = 0; y < row; y += row * sampleRate)
		{
			subMaskPointSet.push_back(Point2f(x, y));
		}
	}

	clock_t t2 = clock();
	//cout << "Step 0: subMaskPointSet's size is :" << subMaskPointSet.size() << endl;
	//cout << "Step0: Prepare work has been finished !" << endl;
	//cout << "Time is :" << (t2 - t1) * 1.0 / CLOCKS_PER_SEC << "s\n" << endl;


	/*Step 1 : Construct the N(δ) net */
	//T: [translationX, translationY, Rtate] 
	//cout << "Step 1:Construct the N(δ) net." << endl;
	clock_t t3 = clock();
	vector<tuple<int, int, float>> TransNet, GoodTransNet;

	//建立初始网络
	TransNet = ConstructNet(srcImage.rows, srcImage.cols, delta);

	clock_t t4 = clock();
	//cout << "Step 1:δis:" << delta << endl;
	//cout << "Step 1:Size of the N(δ) net is:" << TransNet.size() << endl;
	//cout << "Step 1:Construct the N(δ) net has been finished !" << endl;
	//cout << "Time is :" << (t4 - t3)* 1.0 / CLOCKS_PER_SEC << "s\n" << endl;


	/*Step 2: Iterate, update and calculate the best translation.*/
	//cout << "Step 2:Iterate, update and calculate the best translation." << endl;
	float distance = 0;
	float L_Delta;
	int N_Delta;

	int index = 0;

	float bestDistance = FLT_MAX;
	float curDistance = 0;
	float temp_distance;
	vector<float>bestDistanceSet;

	int bestNum = 0;
	float curNum = 0;
	vector<int>bestNumSet;

	vector<tuple<int, int, float>> tempTransNet;
	tuple<int, int, float>  bestTrans;
	int bestTransX, bestTransY;
	float bestTheta;
	CurrentBestReusult bestResult;

	while (true)
	{
		index++;
		//cout << "Current TransNet's size is: " << TransNet.size() << endl;

		/*计算当前变换网络下的bestTrans + bestDistance*/
		clock_t ta = clock();
		bestResult = GetBestTrans(srcImage, maskImage, subMaskPointSet, TransNet, delta, epsilon);		clock_t tb = clock();
		//cout << "GetBestTrans's time is: " << (tb - ta)* 1.0 / CLOCKS_PER_SEC << "s" << endl;

		//if (bestDistance > bestResult.BestDistance)
		//{
		//	bestDistance = bestResult.BestDistance;
		//	get<0>(bestTrans) = bestResult.transX;
		//	get<1>(bestTrans) = bestResult.transY;
		//	get<2>(bestTrans) = bestResult.theta;
		//}

		if (bestNum < bestResult.bestNum)
		{
			bestNum = bestResult.bestNum;
			get<0>(bestTrans) = bestResult.transX;
			get<1>(bestTrans) = bestResult.transY;
			get<2>(bestTrans) = bestResult.theta;
		}

		//cout << "bestDistance is :" << bestDistance << endl;
		//cout << "bestNum is :" << bestNum << endl;

		bestDistanceSet.push_back(bestDistance);
		bestNumSet.push_back(bestNum);

		//if (bestDistanceSet.size() >= 3 && abs(bestDistanceSet[index - 1] - bestDistanceSet[index - 3]) < 0.1)
		//{
		//	break;
		//}

		if (bestNumSet.size() >= 3 && abs(bestNumSet[index - 1] - bestNumSet[index - 3]) < 0.1)
		{
			break;
		}


		/*计算和最佳变换相近的次优解集合GoodTransNet*/
		float curDistance = 0;

		//L_Delta = alpha * bestDistance + beta;
		float alpha = 0.2, beta = 0.01;

		//N_Delta = (int)(alpha * N_Delta);
		N_Delta = (int)((1 - sampleRate * sampleRate*bestNum) / (sampleRate*sampleRate));

		for (int i = 0; i < TransNet.size(); i++)
		{
			tuple<int, int, float> curTrans = TransNet[i];//获取当前变换

			//curDistance = bestResult.TransDistance[i];
			curNum = bestResult.TransNum[i];

			if (abs(curNum - bestNum) < N_Delta)
			{
				tempTransNet.push_back(curTrans);
			}
		}

		//清空GoodTransNet，存入当前的tempTransNet
		vector<tuple<int, int, float>>().swap(GoodTransNet);
		GoodTransNet = tempTransNet;

		//清空tempTransNet
		vector<tuple<int, int, float>>().swap(tempTransNet);

		/*更新L_Delta与δ*/
		N_Delta /= 2;
		delta = delta * factor;

		/*根据新的δ和GoodTransNet更新变换网络TransNet*/
		vector<tuple<int, int, float>>().swap(TransNet);//清空TransNet
		TransNet = GetNextNet(srcImage, GoodTransNet, subMaskPointSet, centerX, centerY, delta);

		//cout << "the " << index << "th's GoodTransNet's size is :" << GoodTransNet.size() << endl;
		//cout << "Next TransNet's size is: " << TransNet.size() << endl;
		//cout << "		bestTransX is: " << get<0>(bestTrans) << endl;
		//cout << "		bestTransY is: " << get<1>(bestTrans) << endl;
		//cout << "		bestTransTheta is: " << get<2>(bestTrans) << "\n" << endl;


		/*清空vector*/
		vector<float>().swap(bestDistanceSet);
		vector<tuple<int, int, float>>().swap(GoodTransNet);

		if (TransNet.size() > 5000 || delta < resolution)
		{
			break;
		}
	}

	//cout << "Step 2:Size of the next_N(δ) net is:" << TransNet.size() << endl;
	//cout << "Step 2:delta is :" << delta << "; bestDistance is :" << bestDistance << endl;
	//cout << "Step 2:delta is :" << delta << "; bestNum is :" << bestNum << endl;
	//cout << "Step 2:Iterate, update and calculate the best translation has been finished !" << endl;
	cout << "		bestTransX is: " << get<0>(bestTrans) << endl;
	cout << "		bestTransY is: " << get<1>(bestTrans) << endl;
	cout << "		bestTransTheta is: " << get<2>(bestTrans) << "\n" << endl;
	return bestTrans;
}


Position CalPosition(Mat& imageL, Mat& imageR, Mat &maskL, Mat& maskR,
	HomographyStruct invH, float deltaX, float deltaY)
{
	//当前图像角点的图像像素坐标
	//Point2d crossPointL = CrossInAlignmentSystem(imageL,maskL);
	//Point2d crossPointR = CrossInAlignmentSystem(imageR,maskR);
	Point2d crossPointL = GetCrossPoint(imageL);
	Point2d crossPointR = GetCrossPoint(imageR);

	//变换至局部世界坐标系
	Point2f crossPointWorldL = TransToWorldAxis(crossPointL, invH.L);
	Point2f crossPointWorldR = TransToWorldAxis(crossPointR, invH.R);

	//统一变换至左相机下视场
	Point2f uniformCrossPointL = crossPointWorldL;
	Point2f uniformCrossPointR = Point2f(crossPointWorldR.x - deltaX, crossPointWorldR.y - deltaY);

	//计算角点的中心点坐标
	float pointX = (uniformCrossPointL.x + uniformCrossPointR.x) / 2;
	float pointY = (uniformCrossPointL.y + uniformCrossPointR.y) / 2;
	Point2f uniformCenterPoint = Point2f(pointX, pointY);

	//根据旋转中心计算边缘倾斜角度theta1
	float theta1 = atan((uniformCrossPointR.y - uniformCrossPointL.y)
		/ (uniformCrossPointR.x - uniformCrossPointL.x)) ;
	Position position;
	position.uniformCrossPointL = uniformCrossPointL;
	position.uniformCrossPointR = uniformCrossPointR;
	position.uniformCenterPoint = uniformCenterPoint;
	position.theta = theta1;

	return position;
}

ControlInstruction GetInstruction(Position& bmPosition, Position& testPosition, Point2f& rotatePoint)
{
	/*计算待测工件移动至基准位置需要移动的偏移量和旋转量*/
	ControlInstruction instruction;

	//计算旋转量alpha
	Point2f uniformCrossPointL = bmPosition.uniformCrossPointL;
	Point2f uniformCrossPointR = bmPosition.uniformCrossPointR;
	Point2f benchMarkPoint = bmPosition.uniformCenterPoint;

	Point2f uniformTestCrossPointL = testPosition.uniformCrossPointL;
	Point2f uniformTestCrossPointR = testPosition.uniformCrossPointR;
	Point2f uniformTestCenterPoint = testPosition.uniformCenterPoint;

	float A = uniformTestCrossPointR.x - uniformTestCrossPointL.x;
	float B = uniformTestCrossPointR.y - uniformTestCrossPointL.y;
	float k = tan((uniformCrossPointR.y - uniformCrossPointL.y) / (uniformCrossPointR.x - uniformCrossPointL.x));
	instruction.commandTheta = -atan((k*A - B) / (A + k * B));

	//计算偏移量
	float uTCRotatePointLX = cos(instruction.commandTheta)*(uniformTestCrossPointL.x - rotatePoint.x) -
		sin(instruction.commandTheta)*(uniformTestCrossPointL.y - rotatePoint.y) + rotatePoint.x;
	float uTCRotatePointLY = sin(instruction.commandTheta)*(uniformTestCrossPointL.x - rotatePoint.x) +
		cos(instruction.commandTheta)*(uniformTestCrossPointL.y - rotatePoint.y) + rotatePoint.y;
	float uTCRotatePointRX = cos(instruction.commandTheta)*(uniformTestCrossPointR.x - rotatePoint.x) -
		sin(instruction.commandTheta)*(uniformTestCrossPointR.y - rotatePoint.y) + rotatePoint.x;
	float uTCRotatePointRY = sin(instruction.commandTheta)*(uniformTestCrossPointR.x - rotatePoint.x) +
		cos(instruction.commandTheta)*(uniformTestCrossPointR.y - rotatePoint.y) + rotatePoint.y;

	//旋转校正之后的中心点坐标
	Point2f testRotatePoint = Point2f((uTCRotatePointLX + uTCRotatePointRX) / 2, (uTCRotatePointLY + uTCRotatePointRY) / 2);

	instruction.commandX = -testRotatePoint.x + benchMarkPoint.x;
	instruction.commandY = testRotatePoint.y - benchMarkPoint.y;

	float testRotateTheta = atan2(uTCRotatePointRY - uTCRotatePointLY,
		uTCRotatePointRX - uTCRotatePointLX) * 180 / PI;

	cout << "After Rotation 's Δθ is: " << testRotateTheta - bmPosition.theta << "°" << "\n" << endl;

	return instruction;
}



Point2f RectifyRotateCenter(Position& testPosition, Position& bmPosition,
	ControlInstruction& instruction, float deltaXeWorld, float deltaYeWorld)
{
	float Xwc0 = bmPosition.uniformCenterPoint.x;
	float Ywc0 = bmPosition.uniformCenterPoint.y;

	float Xwc1 = testPosition.uniformCenterPoint.x;
	float Ywc1 = testPosition.uniformCenterPoint.y;

	float Xwc2 = Xwc0 - deltaXeWorld - instruction.commandX;
	float Ywc2 = Ywc0 - deltaYeWorld - instruction.commandY;

	float theta = instruction.commandTheta;

	float Xwo = (Xwc1 + Xwc2) / 2 + sin(theta)*(Ywc1 - Ywc2) / (2 * (1 - cos(theta)));
	float Ywo = (Ywc1 + Ywc2) / 2 + sin(theta)*(Xwc2 - Xwc1) / (2 * (1 - cos(theta)));

	Point2f RectifiedRC = Point2f(Xwo, Ywo);
	return RectifiedRC;
}
