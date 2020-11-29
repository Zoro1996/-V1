#include "FastMatchForLineParam.h"


/*************************************************************
Function:       LSD
Description:    使用LSD检测图像直线
Input:          imageMat:待测图像
Return:         linePoints:直线点集
**************************************************************/
Mat LSD(Mat srcImage, bool ResizeFlag, float rate)
{
	if (ResizeFlag)
	{
		pyrDown(srcImage, srcImage, Size(srcImage.cols / 2, srcImage.rows / 2));
		//pyrDown(srcImage, srcImage, Size(srcImage.cols / 2, srcImage.rows / 2));
		//GaussianBlur(srcImage, srcImage, Size(3, 3), 0, 0);
		//resize(srcImage, srcImage, Size(srcImage.cols *rate, srcImage.rows*rate));
	}

	//Canny(srcImage, srcImage, 50, 200, 3);
	Ptr<LineSegmentDetector> ls = createLineSegmentDetector(LSD_REFINE_STD);
	vector<Vec4f> lines_std;

	// Detect the lines
	ls->detect(srcImage, lines_std);

	// Show found lines
	//Mat drawnLines(srcImage);
	Mat drawnLines = Mat::zeros(srcImage.size(), srcImage.type());

	ls->drawSegments(drawnLines, lines_std);
	//imshow("Standard refinement", drawnLines);

	//vector<Point2f> linePoints;
	return drawnLines;
}


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
	float delatX, float deltaY)
{
	Mat xgrad;  //x方向上的梯度
	Mat ygrad;  //y方向上的梯度
	vector<Gradient> gradientTable;

	Sobel(image, xgrad, CV_32F, 1, 0, 3);
	Sobel(image, ygrad, CV_32F, 0, 1, 3);

	Mat xygrad = Mat::zeros(image.size(), image.type());
	//cvtColor(xygrad, xygrad, CV_GRAY2BGR);

	Mat lineImage = LSD(image, 1, 0.5);//pyrDown->1/2

	vector<Point2f>linePoints;

	for (int x = 0; x < image.cols; x += 2)
	{
		for (int y = 0; y < image.rows; y += 2)
		{
			Point2f pt = Point2f(x, y);
			float xg = xgrad.at<float>(pt);
			float yg = ygrad.at<float>(pt);
			float gMargin = sqrt(pow(xg, 2) + pow(yg, 2));

			Point2f pt2 = Point2f(x * 0.5, y * 0.5);
			//float LSDValue0 = lineImage.at<Vec3b>(pt2)[0];
			//float LSDValue1 = lineImage.at<Vec3b>(pt2)[1];
			//float LSDValue2 = lineImage.at<Vec3b>(pt2)[2];
			//if (gMargin > thresholdEdges && LSDValue0 != 255
			//	&& LSDValue1 != 255 && LSDValue2 == 255)

			float LSDValue = lineImage.at<Vec3b>(pt2)[2];
			if (gMargin > thresholdEdges && LSDValue == 255)
			{
				xygrad.at<uchar>(pt) = 255;
				linePoints.push_back(Point2f(pt.x + delatX, pt.y + deltaY));
			}
		}
	}

	return linePoints;
}


/*计算某一变换对应的特征距离*/
GCBS SingleTransEvaluation(Mat lineRegionU, Mat lineRegionD,
	tuple<float, float>& curParam, float brectUX, float brectUY,
	float brectDX, float brectDY)
{
	GCBS curResult;

	int gray = get<0>(curParam);
	int gradient = get<1>(curParam);
	for (int ux = 0; ux < lineRegionU.cols; ux++)
	{
		for (int uy = 0; uy < lineRegionU.rows; uy++)
		{
			Point2f pt = Point2f(ux, uy);
			if (lineRegionU.at<uchar>(pt) < gray)
			{
				lineRegionU.at<uchar>(pt) = 0;
			}
		}
	}

	for (int dx = 0; dx < lineRegionD.cols; dx++)
	{
		for (int dy = 0; dy < lineRegionD.rows; dy++)
		{
			Point2f pt = Point2f(dx, dy);
			if (lineRegionD.at<uchar>(pt) < gray)
			{
				lineRegionD.at<uchar>(pt) = 0;
			}
		}
	}

	vector<Point2f>linePointX, linePointY;
	linePointX = GetLinePoints(lineRegionU, gradient, brectUX, brectUY);
	linePointY = GetLinePoints(lineRegionD, gradient, brectDX, brectDY);

	curResult.FLAG = (linePointX.size() < 20 || linePointY.size() < 20) ? false : true;

	if (curResult.FLAG == 1)
	{
		Vec4f fitLineX, fitLineY;
		fitLine(linePointX, fitLineX, CV_DIST_HUBER, 0, 0.01, 0.01);
		fitLine(linePointY, fitLineY, CV_DIST_HUBER, 0, 0.01, 0.01);

		float ka = (float)(fitLineX[1] / (fitLineX[0])); //求出LineA斜率
		float kb = (float)(fitLineY[1] / (fitLineY[0])); //求出LineB斜率
		float ma = fitLineX[3] - ka * fitLineX[2];
		float mb = fitLineY[3] - kb * fitLineY[2];

		float measure = abs(ka * kb + 1);

		curResult.ka = ka;
		curResult.kb = kb;
		curResult.ma = ma;
		curResult.mb = mb;
		curResult.measure = measure;
		curResult.gray = gray;
		curResult.gradient = gradient;
	}

	return curResult;
}


/*计算当前ParamNet下的最佳变换*/
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
			}
		}
		else
		{
			bestResult.MeasureSet.push_back(-100);
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


ShapeMatchResult GetShapeTrans(Mat& maskImage, Mat& srcImage, float factor)
{
	/*gauss pyramid process image -> 1/32*/
	Mat maskImage1, maskImage2, maskImage3, maskImage4, maskImage5;
	//pyrDown(maskImage, maskImage1, Size(maskImage.cols / 2, maskImage.rows / 2));
	//pyrDown(maskImage1, maskImage2, Size(maskImage1.cols / 2, maskImage1.rows / 2));
	//pyrDown(maskImage2, maskImage3, Size(maskImage2.cols / 2, maskImage2.rows / 2));
	//pyrDown(maskImage3, maskImage4, Size(maskImage3.cols / 2, maskImage3.rows / 2));
	//pyrDown(maskImage4, maskImage5, Size(maskImage4.cols / 2, maskImage4.rows / 2));
	resize(maskImage, maskImage5, Size(maskImage.cols / pow(2, factor), maskImage.rows / pow(2, factor)));


	Mat srcImage1, srcImage2, srcImage3, srcImage4, srcImage5;
	//pyrDown(srcImage, srcImage1, Size(srcImage.cols / 2, srcImage.rows / 2));
	//pyrDown(srcImage1, srcImage2, Size(srcImage1.cols / 2, srcImage1.rows / 2));
	//pyrDown(srcImage2, srcImage3, Size(srcImage2.cols / 2, srcImage2.rows / 2));
	//pyrDown(srcImage3, srcImage4, Size(srcImage3.cols / 2, srcImage3.rows / 2));
	//pyrDown(srcImage4, srcImage5, Size(srcImage4.cols / 2, srcImage4.rows / 2));
	resize(srcImage, srcImage5, Size(srcImage.cols / pow(2, factor), srcImage.rows / pow(2, factor)));

	/*1/32*/
	vector<Gradient>maskGradientTable = GetGradientTable(maskImage5);


	Mat xgrad;  //x方向上的梯度
	Mat ygrad;  //y方向上的梯度
	vector<Gradient> gradientTable;

	Sobel(srcImage5, xgrad, CV_32F, 1, 0, 3);
	Sobel(srcImage5, ygrad, CV_32F, 0, 1, 3);

	float bestSimilarity = 0;
	float bestTheta;
	Point2f locate;

	for (int sx = 0; sx < srcImage5.cols; sx++)
	{
		for (int sy = 0; sy < srcImage5.rows; sy++)
		{
			for (float theta = -PI; theta < PI; theta += 1 / PI)
			{
				float similarity = 0;
				for (int i = 0; i < maskGradientTable.size(); i++)
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
					if (pt.x >= 0 && pt.x < srcImage5.cols - 1
						&& pt.y >= 0 && pt.y < srcImage5.rows - 1)
					{
						float xg = xgrad.at<float>(pt);
						float yg = ygrad.at<float>(pt);
						float gMargin = sqrt(pow(xg, 2) + pow(yg, 2));
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
					locate.x = sx;
					locate.y = sy;
					bestTheta = theta;
				}
			}
		}
	}

	ShapeMatchResult result;
	result.massCenter = locate;
	result.theta = bestTheta;
	return result;
}


vector<Gradient>GetGradientTable(Mat& image)
{
	Mat xgrad;  //x方向上的梯度
	Mat ygrad;  //y方向上的梯度
	Mat xygrad;
	vector<Gradient> gradientTable;

	Sobel(image, xgrad, CV_32F, 1, 0, 3);
	Sobel(image, ygrad, CV_32F, 0, 1, 3);

	int width = image.cols;
	int height = image.rows;
	for (int row = 0; row < height; row++) {
		for (int col = 0; col < width; col++) {
			float xg = xgrad.at<float>(row, col);

			float yg = ygrad.at<float>(row, col);
			float margin = sqrt(pow(xg, 2) + pow(yg, 2));

			if (margin > 200)
			{
				Gradient gradient;
				gradient.pt = Point2f(col - width / 2, row - height / 2);
				gradient.margin = sqrt(pow(xg, 2) + pow(yg, 2));
				gradient.theta = atan2(yg, xg);
				//gradient.direct1 = cos(atan2(yg, xg));
				//gradient.direct2 = sin(atan2(yg, xg));
				gradientTable.push_back(gradient);
			}
		}
	}

	return gradientTable;
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


/* I1 : mask; I2 : src*/
GCBS FastMatchForLineParam(
	Mat& imageU, Mat& imageD,
	float lowGray, float highGray,
	float lowGradient, float highGradient,
	float brectUX, float brectUY,
	float brectDX, float brectDY,
	float delta)
{
	/*Step 1 : Construct the N(δ) net */
	//cout << "Step 1:Construct the N(δ) net." << endl;
	float tx_step = delta * (highGray - lowGray);
	float ty_step = delta * (highGradient - lowGradient);

	vector<tuple<float, float>> ParamNet, GoodParamNet;

	ParamNet = ConstructNetForLineParam(lowGray, highGray,
		lowGradient, highGradient, delta);

	/*Step 2: Iterate, update and calculate the best translation.*/
	int index = 0;
	GCBS curBestResult, bestResult;
	bestResult.measure = 10;

	vector<float>bestMeasureSet;
	float L_Delta = 0.4;

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
		}

		bestMeasureSet.push_back(bestResult.measure);
		if (abs(bestMeasureSet[index - 1] - bestMeasureSet[index - 3]) < 0.1)
		{
			break;
		}

		/*计算和最佳变换相近的次优解集合GoodTransNet*/
		float alpha = 1, beta = 0;
		L_Delta = alpha * bestResult.measure + beta;

		vector<tuple<float, float>> tempParamNet;
		for (int i = 0; i < ParamNet.size(); i++)
		{
			float curMeasure = curBestResult.MeasureSet[i];
			if (curMeasure != -100 && abs(curMeasure - bestResult.measure) < L_Delta)
			{
				tuple<float, float> curParam = ParamNet[i];//获取当前变换
				tempParamNet.push_back(curParam);
			}
		}

		if (tempParamNet.size() == 0)
		{
			cout << "L_Delta isn't suitable,please adjust." << endl;
			break;
		}

		//清空GoodTransNet，存入当前的tempTransNet
		vector<tuple<float, float>>().swap(GoodParamNet);
		if (tempParamNet.size() > 10)
		{
			int deltaNum = tempParamNet.size() - 10;
			int offsetNum = rand() % deltaNum;
			vector<tuple<float, float>>::const_iterator first = tempParamNet.begin() + offsetNum;
			vector<tuple<float, float>>::const_iterator second = tempParamNet.begin() + offsetNum + 10;
			vector<tuple<float, float>>cutGoodParamNet(first, second);
			GoodParamNet = cutGoodParamNet;

			tuple<float, float>curBestParam{ bestResult.gray,bestResult.gradient };
			GoodParamNet.push_back(curBestParam);
		}
		else
		{
			GoodParamNet = tempParamNet;
		}


		cout << "the " << index << "th's GoodTransNet's size is :" << GoodParamNet.size() << endl;

		vector<tuple<float, float>>().swap(tempParamNet);

		/*更新L_Delta与δ*/
		//L_Delta /= 2;
		delta /= 2;

		/*根据新的δ和GoodTransNet更新变换网络TransNet*/
		vector<tuple<float, float>>().swap(ParamNet);//清空TransNet
		ParamNet = GetNextNet(GoodParamNet, tx_step, ty_step, delta);

		/*清空vector*/
		//vector<float>().swap(bestDistanceSet);
		vector<tuple<float, float>>().swap(GoodParamNet);

		if (ParamNet.size() > 500 || delta < 0.01 || abs(bestResult.measure) < 0.1)
		{
			break;
		}
	}

	cout << "Step 2:gray is: " << bestResult.gray << endl;
	cout << "Step 2:gradient is: " << bestResult.gradient << endl;
	cout << "Step 2:Step 2:Size of the N(δ) net is:" << ParamNet.size() << endl;
	cout << "Step 2:delta is :" << delta << "; bestMeasure is :" << bestResult.measure << endl;
	cout << "Step 2:Iterate, update and calculate the best translation has been finished !" << endl;

	return bestResult;
}


/*************************************************************
Function:       GetCrossBasedFastShapeL
Description:    使用形状匹配计算手机盖板左角点
Input:          srcImage:待测图像 maskImage:模板图像
Return:         盖板左角点
**************************************************************/
Point2f GetCrossBasedFastShapeL(Mat& srcImage, Mat& maskImage,
	float factor, float grayThreshold, float gradientThreshold, char *a)
{
	ShapeMatchResult arcShapeMatchResult = GetShapeTrans(maskImage, srcImage, factor);

	Point2f locate = arcShapeMatchResult.massCenter;
	float bestTheta = arcShapeMatchResult.theta;

	Rect maskArcRegion = Rect(1674, 350, 2666 - 1674, 1141 - 350);
	Rect maskLineRegion1 = Rect(2946, 394, 3562 - 2946, 600 - 394);
	Rect maskLineRegion2 = Rect(1704, 1660, 2064 - 1704, 2372 - 1660);

	float centerX = (1674 + 2666) / 2;
	float centerY = (350 + 1141) / 2;
	float deltaCol = locate.x * pow(2, factor);
	float deltaRow = locate.y * pow(2, factor);

	float xUA1 = 2946 - centerX, yUA1 = 300 - centerY;
	float xUA2 = 3562 - centerX, yUA2 = 300 - centerY;
	float xUB1 = 2946 - centerX, yUB1 = 700 - centerY;
	float xUB2 = 3562 - centerX, yUB2 = 700 - centerY;

	float xDA1 = 1704 - centerX, yDA1 = 1660 - centerY;
	float xDA2 = 2064 - centerX, yDA2 = 1660 - centerY;
	float xDB1 = 1704 - centerX, yDB1 = 2372 - centerY;
	float xDB2 = 2064 - centerX, yDB2 = 2372 - centerY;

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

	if (brectU.x % 2 != 0)brectU.x += 1;
	if (brectU.y % 2 != 0)brectU.y += 1;
	if (brectU.width % 2 != 0)brectU.width -= 1;
	if (brectU.height % 2 != 0)brectU.height -= 1;

	contourD.push_back(pD1);
	contourD.push_back(pD2);
	contourD.push_back(pD3);
	contourD.push_back(pD4);
	RotatedRect rectD = minAreaRect(contourD);//外接矩形
	Point2f verticesD[4];
	rectD.points(verticesD);//外接矩形的4个顶点
	Rect brectD = rectD.boundingRect();

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


	//Mat dstImage4;
	//cvtColor(srcImage, dstImage4, CV_GRAY2BGR);
	//for (int i = 0; i < 4; i++)//画矩形
	//{
	//	line(dstImage4, verticesU[i], verticesU[(i + 1) % 4], Scalar(0, 0, 255));
	//	line(dstImage4, verticesD[i], verticesD[(i + 1) % 4], Scalar(0, 0, 255));
	//}
	//rectangle(dstImage4, brectD, Scalar(255, 0, 0));
	//rectangle(dstImage4, brectU, Scalar(255, 0, 0));

	Mat lineRegionU, lineRegionD;
	srcImage(brectU).copyTo(lineRegionU);
	srcImage(brectD).copyTo(lineRegionD);

	double start = double(getTickCount());

	GCBS bestResult = FastMatchForLineParam(
		lineRegionU, lineRegionD,
		0, grayThreshold,
		150, gradientThreshold,
		brectU.x, brectU.y,
		brectD.x, brectD.y,
		0.1);

	double duration_ms = (double(getTickCount()) - start) * 1000 / getTickFrequency();

	Point2f crossPoint;
	crossPoint.x = (bestResult.mb - bestResult.ma) / (bestResult.ka - bestResult.kb);
	crossPoint.y = (bestResult.ma * bestResult.kb - bestResult.mb * bestResult.ka) / (bestResult.kb - bestResult.ka);

	cout << "Best grayThreshold is: " << bestResult.gray << " for the " << a << "th image\n";
	cout << "Best gradientThreshold is: " << bestResult.gradient << " for the " << a << "th image\n";
	cout << "Best measurement is: " << bestResult.measure << " for the " << a << "th image\n";
	cout << "Best crossPoint is: " << crossPoint << " for the " << a << " image\n";
	std::cout << "It took " << duration_ms << " ms." << "\n" << std::endl;

	return crossPoint;
}


/*************************************************************
Function:       GetCrossBasedFastShapeR
Description:    使用形状匹配计算手机盖板右角点
Input:          srcImage:待测图像 maskImage:模板图像
Return:         盖板右角点
**************************************************************/
Point2f GetCrossBasedFastShapeR(Mat& srcImage, Mat& maskImage,
	float factor, float grayThreshold, float gradientThreshold, char *a)
{
	ShapeMatchResult arcShapeMatchResult = GetShapeTrans(maskImage, srcImage, factor);

	Point2f locate = arcShapeMatchResult.massCenter;
	float bestTheta = arcShapeMatchResult.theta;

	Rect maskArcRegion = Rect(1204, 418, 2330 - 1204, 1384 - 418);
	Rect maskLineRegion1 = Rect(550, 360, 1327 - 550, 750 - 360);
	Rect maskLineRegion2 = Rect(1916, 1474, 2338 - 1916, 2215 - 1474);

	float centerX = (1204 + 2330) / 2;
	float centerY = (1384 + 418) / 2;
	float deltaCol = locate.x * pow(2, factor);
	float deltaRow = locate.y * pow(2, factor);

	float xUA1 = 550 - centerX, yUA1 = 360 - centerY;
	float xUA2 = 1327 - centerX, yUA2 = 360 - centerY;
	float xUB1 = 550 - centerX, yUB1 = 750 - centerY;
	float xUB2 = 1327 - centerX, yUB2 = 750 - centerY;

	float xDA1 = 1916 - centerX, yDA1 = 1474 - centerY;
	float xDA2 = 2338 - centerX, yDA2 = 1474 - centerY;
	float xDB1 = 1916 - centerX, yDB1 = 2215 - centerY;
	float xDB2 = 2338 - centerX, yDB2 = 2215 - centerY;

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
	Point2f pU1(trxUA1, tryUA1), pU2(trxUA2 - 200, tryUA2), pU3(trxUB1, tryUB1), pU4(trxUB2 - 200, tryUB2);
	Point2f pD1(trxDA1, tryDA1 + 200), pD2(trxDA2, tryDA2 + 200), pD3(trxDB1, tryDB1), pD4(trxDB2, tryDB2);

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

	//Mat dstImage4;
	//cvtColor(srcImage, dstImage4, CV_GRAY2BGR);
	//for (int i = 0; i < 4; i++)//画矩形
	//{
	//	line(dstImage4, verticesU[i], verticesU[(i + 1) % 4], Scalar(0, 0, 255));
	//	line(dstImage4, verticesD[i], verticesD[(i + 1) % 4], Scalar(0, 0, 255));
	//}
	//rectangle(dstImage4, brectD, Scalar(255, 0, 0));
	//rectangle(dstImage4, brectU, Scalar(255, 0, 0));


	Mat lineRegionU, lineRegionD;
	srcImage(brectU).copyTo(lineRegionU);
	srcImage(brectD).copyTo(lineRegionD);

	//Mat edgesU, edgesD;
	////Mat dstImageU = Mat::zeros(lineRegionU.size(), lineRegionU.type());
	////Mat dstImageD = Mat::zeros(lineRegionD.size(), lineRegionD.type());
	//vector<Vec4f> linesU, linesD;
	//vector<Point2f>linePointX, linePointY;
	//float measurement;
	//GCBS curResult, bestResult;
	//bestResult.measurement = 0;
	//float bestGrayThreshold;
	//float bestGradientThreshold;
	//float ka, kb;
	//float ma, mb;

	double start = double(getTickCount());

	GCBS bestResult = FastMatchForLineParam(
		lineRegionU, lineRegionD,
		0, grayThreshold,
		150, gradientThreshold,
		brectU.x, brectU.y,
		brectD.x, brectD.y,
		0.1);

	double duration_ms = (double(getTickCount()) - start) * 1000 / getTickFrequency();

	Point2f crossPoint;
	crossPoint.x = (bestResult.mb - bestResult.ma) / (bestResult.ka - bestResult.kb);
	crossPoint.y = (bestResult.ma * bestResult.kb - bestResult.mb * bestResult.ka) / (bestResult.kb - bestResult.ka);

	cout << "Best grayThreshold is: " << bestResult.gray << " for the " << a << "th image\n";
	cout << "Best gradientThreshold is: " << bestResult.gradient << " for the " << a << "th image\n";
	cout << "Best measurement is: " << bestResult.measure << " for the " << a << "th image\n";
	cout << "Best crossPoint is: " << crossPoint << " for the " << a << " image\n";
	std::cout << "It took " << duration_ms << " ms." << "\n" << std::endl;

	//bestResult.crossPoint = crossPoint;
	return crossPoint;
}
