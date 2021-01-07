	string csvPathL(".\\实验结果\\1-7-对位实验-直接求逆-左相机角点信息.csv");
	string csvPathR(".\\实验结果\\1-7-对位实验-直接求逆-右相机角点信息.csv");
	vector<CrossPointInfo> resultLVector,resultRVector;
	vector<Point2f>pixelAxisSetL, pixelAxisSetR;
	RestoreInfo(csvPathL, resultLVector, pixelAxisSetL);
	RestoreInfo(csvPathR, resultRVector, pixelAxisSetR);
	for (int i = 0; i < 33; i++)
	{
		Point2f resultPointL = pixelAxisSetL[i];
		Point2f resultPointR = pixelAxisSetR[i];

		//角点像素坐标变换至局部世界坐标系
#if	CalibrationMethod ==1
		Point2f crossPointWorldL = TransToWorldAxis(resultPointL, invHL);
		Point2f crossPointWorldR = TransToWorldAxis(resultPointR, invHR);
#elif CalibrationMethod ==2
		Point2f crossPointWorldL = CalWorldPoint(resultPointL, ML);
		Point2f crossPointWorldR = CalWorldPoint(resultPointR, MR);
#endif

		//角点世界坐标存储
		worldAxisSetL.push_back(crossPointWorldL);
		worldAxisSetR.push_back(crossPointWorldR);
	}


#include <sstream>	
void RestoreInfo(string csvPath, vector<CrossPointInfo> &resultVector, vector<Point2f>&pixelAxisSet)
{
	class innerFunc
	{
	public:
	//	innerFunc();
	//	~innerFunc();

		float stringToNum(const string& str)
		{
			istringstream iss(str);
			float num;
			iss >> num;
			return num;
		}
	private:
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


