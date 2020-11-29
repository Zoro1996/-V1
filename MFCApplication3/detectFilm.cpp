//***************************************类名称：AlgFilmDetect（ver1.00.00）********************************************||
//***************************************编写者：王南南****************************************************************||
//***************************************编写时间：2020年10月11日****************************************************||
//***************************************类功能：实现贴膜检测********************************************************||

///20201011 1、贴膜检工位集成：贴膜识别、获取直线、偏位测量
//#include "AlgProcessInterface.h"
//#include "AlgProcessDataDefine.h"
#include"MyFunction.h"
#include "detectFilm.h"
#include "gatherPtLine.h"
#include<fstream>
#include<stdio.h>
#include <iostream>
using namespace std;
using namespace cv;
//float cosTable[360];
//float sinTable[360];
vector<Point> outOffset(8);  //8个象限的外坐标点
vector<Point> inOffset(8);   //8个象限的内坐标点
#define PI2Degree  CV_PI / 180
#define drawTemplatec 0   //参考模板轮信息
#define drawSampleC  0   //查看旋转后的待测轮廓信息
#define drawSeg 0          //绘制检测出的缺陷信息
static int drawNum;
//ofstream filetimecal("D:/新软件测试时间.txt", ios::app);
//接口：类名
//说明：一个算法流程类实例化一个
AlgProcessInterface *getAlgPlugin()
{
	return new AlgFilmDetect();//实际的类名
}
//4、获取版本
string AlgFilmDetect::getVision(int *_vision)
{
	*_vision = 0;
	return "FILM_00";
}
//5-获取工程路径
void  AlgFilmDetect::setDataPath(const string &_path)
{
	AlgFilmDetect::projectPath = _path;
	return;
}

//--------------------------------------以下为类成员的实现------------------------------//
//获取流程算子
//输入/输出：参数信息
void AlgFilmDetect::getProcessAlgInfo(AlgProcessInfo *_processInfo)
{

	AlgMsgRecognitionConfig msgRE;
	AlgMsgGetLineConfig msgGL;
	AlgMsgMeasureConfig msgME;
	_processInfo->projectDes = "FilmDetect";
	_processInfo->initialize = false;              //需要初始化
	SingleAlgInfo vAlgInfoRE, vAlgInfoGL, vAlgInfoME;

	vAlgInfoRE.algType = "贴膜识别";         //算子描述---0000
	vAlgInfoRE.algID = RECOGNITION;                 //算子ID  从0 开始----0000
	vAlgInfoRE.outInfoFlag = 1;            //输出中间结果控制：1--输出，0--不输出 将mask图以及轮廓进行输出用于界面显示
	vAlgInfoRE.algDes = msgRE.msgs;
	vAlgInfoRE.enableROI = true;
	vAlgInfoRE.initflag = true;
	vAlgInfoRE.execute = true;
	algModelInfo locateModel;
	locateModel.enable = true;
	locateModel.suffix = "SIX";
	vAlgInfoRE.model = locateModel;

	vAlgInfoGL.algType = "获取直线";  //算子描述---0000
	vAlgInfoGL.algID = GETLINE;       //算子ID  从0 开始----0000
	vAlgInfoGL.outInfoFlag = 1;       //输出中间结果控制：1--输出，0--不输出 将mask图以及轮廓进行输出用于界面显示
	vAlgInfoGL.enableROI = true;
	vAlgInfoGL.algDes = msgGL.msgs;
	vAlgInfoGL.initflag = false;
	vAlgInfoGL.execute = true;

	vAlgInfoME.algType = "测量偏位";  //算子描述---0000
	vAlgInfoME.algID = MEASURE;       //算子ID  从0 开始----0000
	vAlgInfoME.outInfoFlag = 0;       //输出中间结果控制：1--输出，0--不输出 将mask图以及轮廓进行输出用于界面显示
	vAlgInfoME.enableROI = false;
	vAlgInfoME.algDes = msgME.msgs;
	vAlgInfoME.initflag = false;
	vAlgInfoME.execute = true;

	_processInfo->vAlgInfo.push_back(vAlgInfoRE);
	_processInfo->vAlgInfo.push_back(vAlgInfoGL);
	_processInfo->vAlgInfo.push_back(vAlgInfoME);
	return;
}
//2、是否参数共享
void AlgFilmDetect::setSharedFlag(bool _share)
{
	AlgFilmDetect::m_shared = _share;
}
//2、初始化数据
//原图 - 流程信息 算法模型路径信息
ErrMsg AlgFilmDetect::setProcessParm(const vector<cv::Mat> *_vMats, vector<AlgProcessInfo> *_processInfo)
{
	//若参数共享，则模型路径都共享
	ErrMsg errorMsg;
	errorMsg.error = true;
	AlgFilmDetect::m_pProcessInfo = _processInfo;   //参数赋值
	vector<algModelInfo> model;
	algModelInfo segMentModel;
	//先分配好所需要的内存空间---begin
	/*vector<cv::Mat> matchImg;                              //模板小图
	vector<vector<vector<cv::Point2f>>> matchContours;     //模板小图轮廓信息相对于原始降采样的图
	vector<vector<vector<float>>> matchDir;                //模板小图轮廓的梯度信息
	vector<cv::Point> matchLeftTop;                        //模板小图在原始大图的左上角点信息
	vector<cv::Point2f> matchCenter;                       //模板小图的轮廓中心 相对于降采样后的图
	vector<float> matchGrad;                               //模板轮廓的梯度数值，用于与待测相比
	string   projectPath;
	//存储中间算子的输出结果，用于在调试阶段直接调用
	vector<TransformMatrix> transformMatrix;               //贴膜识别算子输出的转换关系 作为获取直线的输入
	vector<vector<LineSturct>> lineOutput;                 //拟合直线算子的输出结果*/
	if (AlgFilmDetect::matchImg.size() == 0) {
		for (int i = 0; i < _processInfo->size(); i++) {
			Mat matchimg;
			AlgFilmDetect::matchImg.push_back(matchimg);
		}
	}
	if (AlgFilmDetect::matchContours.size() == 0) {
		for (int i = 0; i < _processInfo->size(); i++) {
			vector<vector<cv::Point2f>> tempPts;
			AlgFilmDetect::matchContours.push_back(tempPts);
		}
	}
	if (AlgFilmDetect::matchDir.size() == 0) {
		for (int i = 0; i < _processInfo->size(); i++) {
			vector<vector<float>> tempDir;
			AlgFilmDetect::matchDir.push_back(tempDir);
		}
	}
	if (AlgFilmDetect::matchLeftTop.size() == 0) {
		for (int i = 0; i < _processInfo->size(); i++) {
			Point tempLeftTop;
			AlgFilmDetect::matchLeftTop.push_back(tempLeftTop);
		}
	}
	if (AlgFilmDetect::matchCenter.size() == 0) {
		for (int i = 0; i < _processInfo->size(); i++) {
			cv::Point2f tempCenter;
			AlgFilmDetect::matchCenter.push_back(tempCenter);
		}
	}
	if (AlgFilmDetect::matchGrad.size() == 0) {
		for (int i = 0; i < _processInfo->size(); i++) {
			float tempCenter;
			AlgFilmDetect::matchGrad.push_back(tempCenter);
		}
	}
	if (AlgFilmDetect::transformMatrix.size() == 0) {
		for (int i = 0; i < _processInfo->size(); i++) {
			TransformMatrix transForm;
			AlgFilmDetect::transformMatrix.push_back(transForm);
		}
	}
	if (AlgFilmDetect::lineOutput.size() == 0) {
		for (int i = 0; i < _processInfo->size(); i++) {
			vector<LineStruct> lineS;
			AlgFilmDetect::lineOutput.push_back(lineS);
		}
	}
	if (AlgFilmDetect::grad.size() == 0) {
		for (int i = 0; i < _processInfo->size(); i++) {
			vector<vector<float>> gradSub;
			AlgFilmDetect::grad.push_back(gradSub);
		}
	}
	if (AlgFilmDetect::meanGrad.size() == 0) {
		for (int i = 0; i < _processInfo->size(); i++) {
			float meanGradtemp;
			AlgFilmDetect::meanGrad.push_back(meanGradtemp);
		}
	}
	//分配好内存空间-end
	//贴膜识别算子初始化----------BEGIN
	AlgProcessInfo info = AlgFilmDetect::m_pProcessInfo->at(0);
	SingleAlgInfo singleInfoL = *(*_processInfo)[0].getAlgInfo(RECOGNITION);  //算子参数
	AlgParamsRecognitionConfig recogConfig = *(AlgParamsRecognitionConfig*)&singleInfoL.parms;
	int shareMatch = recogConfig.i_params.block.shareMatch;            //是否共享参数
	int matchStype = recogConfig.i_params.block.matchStyle;
	if (matchStype < 0)
		matchStype = 0;
	if (matchStype == 0) {
		int dis = recogConfig.i_params.block.dis;
		//-----------------灰度梯度区间查找表begin--------------------//

		vector<Point> tempPtdir;
		tempPtdir.clear();
		tempPtdir.push_back(Point(-dis, 0));
		tempPtdir.push_back(Point(-dis, -dis));
		tempPtdir.push_back(Point(0, -dis));
		tempPtdir.push_back(Point(dis, -dis));
		tempPtdir.push_back(Point(dis, 0));
		tempPtdir.push_back(Point(dis, dis));
		tempPtdir.push_back(Point(0, dis));
		tempPtdir.push_back(Point(-dis, dis));
		outOffset = tempPtdir;
		int c = 0;
		for (auto cc : tempPtdir) {
			inOffset[c] = -1 * cc;
			c++;
		}
		//Step0-存储模板图
		Mat globalMatchimg;
		for (size_t i = 0; i < _processInfo->size(); i++)
		{

			int index;
			if (shareMatch)
				index = 0;
			else
				index = i;
			SingleAlgInfo singleInfo = *(*_processInfo)[index].getAlgInfo(RECOGNITION);  //算子参数
			AlgParamsRecognitionConfig locateConfig = *(AlgParamsRecognitionConfig*)&singleInfo.parms;
			int matchStype = locateConfig.i_params.block.matchStyle;
			string algType = singleInfo.algType;
			Mat matchimg;
			string locatePath = AlgFilmDetect::projectPath + "//" + singleInfo.model.toName(index, algType, RECOGNITION) + ".png";  //图片名称
			ifstream fin(locatePath);
			/*if (!fin) {
				return 1;
			}*/
			//int fileExist = access(locatePath.data(), 0);
			if (fin && globalMatchimg.empty()) {
				if (shareMatch) {
					globalMatchimg = imread(locatePath, CV_8UC1);
				}
				else {
					matchimg = imread(locatePath, CV_8UC1);
				}
			}
			if (shareMatch) {
				AlgFilmDetect::matchImg[i] = globalMatchimg;
			}
			else {
				AlgFilmDetect::matchImg[i] = matchimg;
			}
		}

		//Step1-存储模板轮廓及统计信息
		/*当共享同一个模板时候，只计算一次模板信息*/
		Point lefttopGlobal;                  //左上角点
		vector<vector<float>> globaldir;     //轮廓匹配方向信息
		vector<vector<Point2f>> contoursGlobal; //模板轮廓信息
		float matchGradGlobal;
		Point2f centerfPtGlobal;
		float meanGradGlobal;     //模板梯度平均值
		vector<vector<float>> gradContourGlobal;  //模板梯度值
		for (size_t i = 0; i < _processInfo->size(); i++)
		{

			int index;
			if (shareMatch)
				index = 0;
			else
				index = i;
			SingleAlgInfo singleInfo = *(*_processInfo)[index].getAlgInfo(RECOGNITION);  //算子参数
			AlgParamsRecognitionConfig locateConfig = *(AlgParamsRecognitionConfig*)&singleInfo.parms;
			int matchStype = locateConfig.i_params.block.matchStyle;
			vector<Point> pt;
			vector<float> templateStatic;
			Point lefttop;
			float gradTemp;
			vector<vector<Point2f>> contours;
			vector<vector<float>> tempdir;
			vector<vector<float>> gradContourTemp;
			float meanGradTemp; //模板平均梯度
			Point2f centerfPt;
			vector<int> tempInfo;
			string algType = singleInfo.algType;
			string roiPath = AlgFilmDetect::projectPath + singleInfo.model.toName(index, algType, RECOGNITION) + ".txt";  //图片名称
			ifstream fin2(roiPath);
			//int fileROI = access(roiPath.data(), 0);
			if (fin2) {
				string featgurename;
				int count = 0;

				ifstream filename(roiPath, ifstream::in);  //从文件中读取信息
				while (getline(filename, featgurename)) {
					tempInfo.push_back(atoi(featgurename.c_str()));
				}
				if (shareMatch == 1)
					lefttopGlobal = Point(tempInfo[0], tempInfo[1]);
				else
					lefttop = Point(tempInfo[0], tempInfo[1]);
				filename.close();
			}
			if (shareMatch) {
				AlgFilmDetect::matchLeftTop[i] = lefttopGlobal;
			}
			else {
				AlgFilmDetect::matchLeftTop[i] = lefttop;
			}
			if (globaldir.size() == 0) {
				if (shareMatch) {
					if (matchStype == 0)
						getTemplateContour(AlgFilmDetect::matchImg[index], locateConfig, lefttopGlobal, contoursGlobal, globaldir, gradContourGlobal, meanGradGlobal, matchGradGlobal,centerfPtGlobal);
				}
				else {
					if (matchStype == 1)
						getTemplateContour(AlgFilmDetect::matchImg[index], locateConfig, lefttop, contours, tempdir, gradContourTemp, meanGradTemp, gradTemp, centerfPt);
				}
			}
			if (shareMatch) {
				AlgFilmDetect::matchContours[i] = contoursGlobal;
				AlgFilmDetect::matchCenter[i] = centerfPtGlobal;
				AlgFilmDetect::matchDir[i] = globaldir;
				AlgFilmDetect::matchGrad[i] = matchGradGlobal;
				AlgFilmDetect::meanGrad[i] = meanGradGlobal;
			}
			else {
				AlgFilmDetect::matchContours[i] = contours;
				AlgFilmDetect::matchCenter[i] = centerfPt;
				AlgFilmDetect::matchDir[i] = tempdir;
				AlgFilmDetect::matchGrad[i] = gradTemp;
				AlgFilmDetect::meanGrad[i] = meanGradTemp;
			}
		}
	}
	//计算一些中间结果信息*/
	errorMsg.error = false;
	return errorMsg;
}
//3-创建模型
ErrMsg AlgFilmDetect::createAlgModel(const cv::Mat &srcImg, const SingleAlgInfo *_single)
{
	int algID = _single->algID;
	int indexImg = _single->imgIndex;
	ErrMsg errorMsg;
	int imgSize = (*AlgFilmDetect::m_pProcessInfo).size();
	errorMsg.algID = algID;
	errorMsg.algType = _single->algType;
	errorMsg.error = true;
	SingleAlgInfo *singleInfoSEG = (*AlgFilmDetect::m_pProcessInfo)[indexImg].getAlgInfo(algID);
	switch (algID) {
	case RECOGNITION: {
		SingleAlgInfo algPara = *(*AlgFilmDetect::m_pProcessInfo)[indexImg].getAlgInfo(algID);
		AlgParamsRecognitionConfig algParaLocate = *(AlgParamsRecognitionConfig*)(&algPara.parms);
		//默认创建模板的时候 需要框ROI信息
		if (algPara.vROI.size() == 0) {
			errorMsg.algID = RECOGNITION;
			errorMsg.algType = algPara.algType;
			errorMsg.vmsg = "创建模型时没有框选ROI信息";
			return errorMsg;
		}
		int matchStyle = algParaLocate.i_params.block.matchStyle;  //0-轮廓匹配 1-无匹配
		int shareMatch = algParaLocate.i_params.block.shareMatch;
		Mat matchimg = AlgFilmDetect::matchImg[indexImg];
		double ratio = algParaLocate.d_params.block.ratio;
		if (ratio < 0)
			ratio = 0.2;
		Rect rectROI;
		Mat oriImg;
		if (srcImg.channels() > 2) {
			cv::cvtColor(srcImg, oriImg, COLOR_RGB2GRAY);
		}
		else
			oriImg = srcImg.clone();
		Point leftToppt;
		vector<vector<Point>> posROI(1);

		for (int i = 0; i < algPara.vROI.size(); i++) {
			ROIShapeData ROIshape = algPara.vROI[i];
			switch (algPara.vROI[i].roiType) {
			case DrawROIType::ROI_Rectangle1: {
				rectROI.x = algPara.vROI[i].points[0].x;
				rectROI.y = algPara.vROI[i].points[0].y;
				rectROI.width = algPara.vROI[i].points[1].x - rectROI.x;
				rectROI.height = algPara.vROI[i].points[1].y - rectROI.y;
				if (rectROI.x < 0) {
					rectROI.width += rectROI.x;
					rectROI.x = 0;
				}
				if (rectROI.y < 0) {
					rectROI.height += rectROI.y;
					rectROI.y = 0;
				}
				if (rectROI.y + rectROI.height > oriImg.rows)
					rectROI.height = oriImg.rows - rectROI.y;
				if (rectROI.x + rectROI.width > oriImg.cols)
					rectROI.width = oriImg.cols - rectROI.x;

				leftToppt.x = rectROI.x;
				leftToppt.y = rectROI.y;
			}break;
			case DrawROIType::ROI_Pts: {
				//相对于大图的轮廓信息
				for (int j = 0; j < algPara.vROI[i].points.size(); j++) {
					posROI[0].push_back(Point(algPara.vROI[i].points[j]));
				}
			}break;
			default:
				break;
			}
		}
		AlgFilmDetect::matchLeftTop[indexImg] = leftToppt;
		matchimg = oriImg(rectROI).clone();
		AlgFilmDetect::matchImg[indexImg] = matchimg.clone();
		string basicPath = AlgFilmDetect::projectPath + algPara.model.toName(indexImg, algPara.algType, algPara.algID);
		string locatePath = basicPath + ".png";  //图片名称
		cv::imwrite(locatePath, matchimg);
		string roiPath = basicPath + ".txt";    //图片名称
		//存储模板小图的左上角点以及ROI信息
		ofstream outfile;
		outfile.open(roiPath, ios::trunc);
		outfile << leftToppt.x << endl;
		outfile << leftToppt.y << endl;
		outfile.close();
		//获取模板轮廓
		vector<vector<Point2f>> matchContour;
		vector<float> matchStatic;
		vector<vector<float>> matchDir;
		vector<vector<float>> grad;
		float meanGrad;
		Point2f centerPt;
		float matchGrad;
		//if (matchStyle == 0)
		//	/*matchStatic = AlgFilmDetect::matchStatic[indexImg];
		//else*/
		//	matchDir = AlgFilmDetect::matchDir[indexImg];
		if (matchContour.size() == 0 && matchStyle == 0) {
			getTemplateContour(matchimg, algParaLocate, leftToppt, matchContour, matchDir, grad,meanGrad,matchGrad,centerPt);
#if drawTemplatec==1
			Mat color;
			Mat resizeimgT;
			resize(oriImg, resizeimgT, Size(0, 0), ratio, ratio);
			cv::cvtColor(resizeimgT, color, COLOR_GRAY2RGB);
			vector<vector<Point>> dc;
			for (auto pts : matchContour) {
				vector<Point> d;
				for (auto pt : pts) {
					d.push_back(Point(pt));
				}
				dc.push_back(d);
			}

			drawContours(color, dc, -1, Scalar(0, 0, 255), 1);
#endif
			
			AlgFilmDetect::matchDir[indexImg] = matchDir;
			AlgFilmDetect::matchContours[indexImg] = matchContour;
			AlgFilmDetect::matchCenter[indexImg] = centerPt;
			AlgFilmDetect::matchGrad[indexImg] = matchGrad;
			AlgFilmDetect::meanGrad[indexImg] = meanGrad;
			AlgFilmDetect::grad[indexImg] = grad;
		}
		//若模型需要共享，则对其他图也要相应的修改存图和txt文件
		if (shareMatch) {
			for (int i = 0; i < imgSize; i++) {
			
				AlgFilmDetect::matchCenter[i] = AlgFilmDetect::matchCenter[indexImg];
				AlgFilmDetect::matchDir[i] = AlgFilmDetect::matchDir[indexImg];
				AlgFilmDetect::matchImg[i] = AlgFilmDetect::matchImg[indexImg];
				AlgFilmDetect::matchLeftTop[i] = AlgFilmDetect::matchLeftTop[indexImg];
				AlgFilmDetect::matchGrad[i] = AlgFilmDetect::matchGrad[indexImg];
				AlgFilmDetect::matchContours[i] = AlgFilmDetect::matchContours[indexImg];
				AlgFilmDetect::meanGrad[i] = AlgFilmDetect::meanGrad[indexImg];
				AlgFilmDetect::grad[i] = AlgFilmDetect::grad[indexImg];
				//存储图和写txt文件
				basicPath = algPara.model.path + algPara.model.toName(i, algPara.algType, algPara.algID);
				locatePath = basicPath + ".png";  //图片名称
				cv::imwrite(locatePath, matchimg);
				roiPath = basicPath + ".txt";  //图片名称
				//只存储左上角点
				outfile.open(roiPath, ios::trunc);
				outfile << leftToppt.x << endl;
				outfile << leftToppt.y << endl;
				outfile.close();
			}
		}
	}break;
	default:
		break;
	}
	errorMsg.error = false;
	return errorMsg;
}
//3、执行
//在一键执行的时候，只显示输出的缺陷信息，和最后一个算子的输出结果图信息；
//如果想看中间某个算子的中间结果图或者轮廓信息只能是在单步调试该算子才能生效。
//0-输入原图 1-输入控制指令--调试每次输入一个 2-是否调试 3-流程输出结果信息
////输入原图:正常--16个 -输入控制指令--调试每次输入一个；单个图像流程;正-是否调试 :正常---false；
ErrMsg AlgFilmDetect::goExe(const vector<cv::Mat> *_vMats, const SingleAlgInfo *_single, int  _imgIndex, bool  _debug, vector<AlgOutInfo> *_outInfo)
{
	ErrMsg errorMsg;
	//单步调试阶段
	if (_single != NULL) {
		int imgIndex = _imgIndex;       //图像索引
		int algID = (*_single).algID;   //算子索引
		string algType = (*_single).algType;
		errorMsg.algID = algID;
		errorMsg.algType = algType;
		if ((*_vMats)[0].empty()) {
			errorMsg.error = true;
			errorMsg.vmsg = "测试当前算子输入图像为空";
			return errorMsg;
		}
		SingleAlgInfo siglePara = *_single;
		/*	ErrMsg recognitionFilm(const RecognitionInput &input, RecognitionOutput &output);
	//8、获取直线算子
	//功能：获取贴膜工位的直线以及盖板边缘的直线
	ErrMsg getLine(const GetLineInput &input, GetLineOutput &output);
	//9、测量偏位算子
	ErrMsg measureDeviation(const MeasureInput &input, MeasureOutput &output);
*/
		AlgOutInfo algOutRecong;
		switch (algID) {
		case RECOGNITION: {
			//0-输入原始图像 1-算法参数 2-输出中间结果信息	
			
			ResImg locateMaskImg;
			RecognitionInput recongInput;
			RecognitionOutput recongOutput;
			recongInput.algPara = siglePara;
			recongInput.srcImg = (*_vMats)[0];
			ErrMsg errorMsgRE = recognitionFilm(recongInput, recongOutput);
			if (errorMsgRE.error) {
				errorMsg.error = true;
				errorMsg.vmsg = errorMsgRE.vmsg;
				return errorMsg;
			}
				
			MeasureData measureRecong;
			measureRecong.exist = recongOutput.existFilmFlag;
			algOutRecong.measure.push_back(measureRecong);
			algOutRecong.imgIndex = _imgIndex;
			algOutRecong.outImg.contourPts = recongOutput.recogintionContour.contourPts;
			(*_outInfo).push_back(algOutRecong);
		}break;
		case GETLINE: {
			if (!AlgFilmDetect::transformMatrix[_imgIndex].getTransForm) {
				errorMsg.error = true;
				errorMsg.vmsg = "在获取直线时的前序算子贴膜检测失效";
				return errorMsg;
			}
			GetLineInput getLineInput;
			GetLineOutput getLineOutput;
			getLineInput.algPara = siglePara;
			getLineInput.srcImg = (*_vMats)[0];
			ErrMsg errorMsgGL = getLine(getLineInput, getLineOutput);
			if (errorMsgGL.error) {
				errorMsg.error = true;
				errorMsg.vmsg = errorMsgGL.vmsg;
				return errorMsg;
			}
				
			ResImg outImgGetline;
			outImgGetline = getLineOutput.lineContour;
			outImgGetline.algID = GETLINE;
			outImgGetline.imgIndex = imgIndex;	
			algOutRecong.outImg = outImgGetline;
			(*_outInfo).push_back(algOutRecong);
		}break;
		case MEASURE: {
			MeasureInput measureInput;
			MeasureOutput measureOutput;
			measureInput.algPara = siglePara;
			ErrMsg errorMsgME = measureDeviation(measureInput, measureOutput);
			if (errorMsgME.error) {
				errorMsg.error = true;
				errorMsg.vmsg = errorMsgME.vmsg;
				return errorMsg;
			}
			algOutRecong.imgIndex = _imgIndex;
			algOutRecong.measure = measureOutput.measureRlt;
			(*_outInfo).push_back(algOutRecong);
		}break;
		default:
			break;
		}
	}
	else {
		if (AlgFilmDetect::m_pProcessInfo->size() == 0) {
			errorMsg.algType = errorMsg.algType;
			errorMsg.error = true;
			errorMsg.vmsg = "在执行阶段流程参数为空";
			return errorMsg;
		}
		int startImg = 0;
		int processNum = (int)(*_vMats).size();
		if (_debug) {   //调试模式对应图像调试整个流程 调试模式只有一个图
			startImg = _imgIndex;
			processNum = _imgIndex + 1;
		}
		for (int i = startImg; i < processNum; i++) {
			AlgOutInfo algOutInfo;
			AlgProcessInfo *sinfo = nullptr;
			if (AlgFilmDetect::m_shared) {
				sinfo = &AlgFilmDetect::m_pProcessInfo->at(0);  //共享参数时，只有0流程才有参数，其他的都没有参数
			}

			else {
				sinfo = &AlgFilmDetect::m_pProcessInfo->at(i);  //共享参数时，只有0流程才有参数，其他的都没有参数	
			}

			SingleAlgInfo *singleRE = sinfo->getAlgInfo(RECOGNITION);
			SingleAlgInfo *singleGL = sinfo->getAlgInfo(GETLINE);
			SingleAlgInfo *singleME = sinfo->getAlgInfo(MEASURE);
			Mat srcImg;
			if (_debug)
				srcImg = (*_vMats)[0];
			else
				srcImg = (*_vMats)[i];
			if (srcImg.empty()) {
				errorMsg.algType = errorMsg.algType;
				errorMsg.error = true;
				errorMsg.vmsg = "贴膜" + to_string(i + 1) + "图像未加载";
				return errorMsg;
			}
			if (singleRE->execute) {
				errorMsg.algID = singleRE->algID;
				errorMsg.algType = singleRE->algType;
				RecognitionInput recongInput;
				RecognitionOutput recongOutput;
				recongInput.algPara = *singleRE;
				recongInput.srcImg = srcImg;
				errorMsg = recognitionFilm(recongInput, recongOutput);
				
				MeasureData measureRecong;
				measureRecong.exist = recongOutput.existFilmFlag;
				if (!measureRecong.exist) {
					errorMsg.error = false;
					algOutInfo.imgIndex = i;
					measureRecong.description = "未检测到贴膜";
					measureRecong.L2LangleBias = 0;
					measureRecong.L2Ldistance = 0;
					measureRecong.detectRlt = false;
					algOutInfo.measure.push_back(measureRecong);	
					(*_outInfo).push_back(algOutInfo);
					errorMsg.vmsg = "未检测到贴膜！";
					return errorMsg;
				}
				if (errorMsg.error)
					return errorMsg;
				AlgFilmDetect::transformMatrix[i] = recongOutput.transformMatrix;
			}
			if (singleGL->execute) {
				if (!AlgFilmDetect::transformMatrix[i].getTransForm) {
					errorMsg.algID = GETLINE;
					errorMsg.error = true;
					errorMsg.vmsg = "在获取直线时的前序算子贴膜检测失效";
					return errorMsg;
				}
				GetLineInput getLineInput;
				GetLineOutput getLineOutput;
				getLineInput.algPara = *singleGL;
				getLineInput.srcImg = srcImg;
				errorMsg = getLine(getLineInput, getLineOutput);
				if (errorMsg.error)
					return errorMsg;
				algOutInfo.outImg.contourPts.clear();
				algOutInfo.outImg.contourPts = getLineOutput.lineContour.contourPts;
				AlgFilmDetect::lineOutput[i] = getLineOutput.lineOutput;
			}
			if (singleME->execute) {
				MeasureInput measureInput;
				MeasureOutput measureOutput;
				measureInput.algPara = *singleME;
				errorMsg = measureDeviation(measureInput, measureOutput);
				if (errorMsg.error) {
					errorMsg.algID = MEASURE; 
					return errorMsg;
				}
				algOutInfo.imgIndex = i;
				algOutInfo.measure = measureOutput.measureRlt;

				(*_outInfo).push_back(algOutInfo);
			}
		}
	}
	return errorMsg;
}

//7、贴膜识别算子
//0-输入参数 1-输出参数
//功能：根据模板图的轮廓信息进行匹配，输出待测图匹配后的轮廓信息以及转换矩阵
ErrMsg AlgFilmDetect::recognitionFilm(const RecognitionInput &input, RecognitionOutput &output)
{
	ErrMsg errorMsg;	
	int imgindex = input.algPara.imgIndex;
	int algID = input.algPara.algID;
	errorMsg.algID = algID;
	errorMsg.algType = input.algPara.algType;
	errorMsg.error = true;
	Mat oriImg;
	//	ErrMsg errorMsg;
	if (input.srcImg.channels() > 2) {
		cv::cvtColor(input.srcImg, oriImg, COLOR_RGB2GRAY);
	}
	else
		oriImg = input.srcImg.clone();
	AlgParamsRecognitionConfig alg = *(AlgParamsRecognitionConfig*)&input.algPara.parms;
	int matchStyle = alg.i_params.block.matchStyle;
	double ratio = alg.d_params.block.ratio;
	double score = alg.d_params.block.score;
	int samplePt = alg.i_params.block.samplePt;
	int metric = alg.i_params.block.metric;
	if (metric < 0)
		metric = 0;  //统计个数最多
	if (samplePt < 0)
		samplePt = 2;
	if (score < 0)
		score = 0.4;
	if (ratio < 0)
		ratio = 0.2;
	Mat sampleImg;
	resize(oriImg, sampleImg, Size(0, 0), ratio, ratio);
	//通过滤波操作得梯度方向

	Mat matchimg = AlgFilmDetect::matchImg[imgindex];
	if (matchimg.empty()) {
		errorMsg.vmsg = "没有初始化，无法执行；请先框选ROI并执行模型重置";
		return errorMsg;
	}
	Point leftToppt = AlgFilmDetect::matchLeftTop[imgindex];
	Rect rectROI;
	float matchGrad = AlgFilmDetect::matchGrad[imgindex];
	vector<vector<Point2f>> matchContour = AlgFilmDetect::matchContours[imgindex];
	vector<float> matchStatic;
	vector<vector<float>> matchDir;
	Point2f centerPt = AlgFilmDetect::matchCenter[imgindex];
	matchDir = AlgFilmDetect::matchDir[imgindex];
	float meanGrad = AlgFilmDetect::meanGrad[imgindex];
	if (matchDir.size() == 0) {
		errorMsg.vmsg = "没有进行轮廓匹配初始化，无法执行；请先框选ROI并执行模型重置";
		return errorMsg;
	}

	//进行匹配求偏移量和旋转角
	//step0-进行旋转，求旋转后每个点对应的内外点 
	centerPt = AlgFilmDetect::matchCenter[imgindex];

	vector<Point2f> translate;
	vector<float> rotatetheta;
	vector<float> gradAllPts;
	vector<int> numGrad;
	vector<float> correnctVal;
	Point2f translateBest;
	int maxIndex = 0;
	float rotateBest = 0;
	float maxGradSum = 0;
	int numGradTemp = 0;
	//0-模板轮廓 1- 参数 2-待测图 3-偏移量 4-旋转角 5-梯度 6-模板轮廓中心
	if (matchStyle == 0 && metric < 2) {   //采用求梯度最大或者满足梯度阈值最多的轮廓点进行评测
		matchContourGrad(matchContour, centerPt, matchDir, meanGrad, alg, sampleImg, translate, rotatetheta, gradAllPts, numGrad);
		//找出梯度最大值
		
		
		
		if (metric == 1) {
			for (int i = 0; i < (int)gradAllPts.size(); i++) {
				if (gradAllPts[i] > maxGradSum) {
					maxGradSum = gradAllPts[i];
					maxIndex = i;
				}
			}
		}
		else {
			for (int i = 0; i < (int)gradAllPts.size(); i++) {
				if (numGrad[i] > numGradTemp) {
					numGradTemp = numGrad[i];
					maxIndex = i;
				}
			}
			maxGradSum = gradAllPts[maxIndex];
		}
		if (gradAllPts.size() == 0) {
			errorMsg.vmsg = "未检测到贴膜";
			return errorMsg;
		}

		if (maxGradSum < score*matchGrad / samplePt || maxGradSum > matchGrad + 100) {
			errorMsg.vmsg = "未检测到贴膜";
			return errorMsg;
		}
	}
	if (metric == 2) {              //采用梯度方向相似性
		Mat sampleFilterX, sampleFilterY, sampleGrad;
		Mat kernelX = (Mat_<int>(1, 3) << -1, 0, 1);
		Mat kernelY = (Mat_<int>(3, 1) << -1, 0, 1);
		filter2D(sampleImg, sampleFilterX, CV_32FC1, kernelX);
		filter2D(sampleImg, sampleFilterY, CV_32FC1, kernelY);
		sampleGrad = sampleFilterX.clone();
#pragma omp parallel for
		for (int m = 0; m < sampleFilterY.rows; m++)
		{
			for (int n = 0; n < sampleFilterY.cols; n++) {
				sampleGrad.at<float>(m, n) = atan2(sampleFilterY.at<float>(m, n), sampleFilterX.at<float>(m, n));//-PI/2 PI/2
			}
		}
		matchContourGrad(matchContour, centerPt, matchDir, alg, sampleGrad, translate, rotatetheta, correnctVal);
		for (int i = 0; i < (int)correnctVal.size(); i++) {
			if (correnctVal[i] > maxGradSum) {
				maxGradSum = correnctVal[i];
				maxIndex = i;
			}
		}
		if (maxGradSum < score) {
			errorMsg.vmsg = "未检测到贴膜";
			return errorMsg;
		}
	}
	translateBest = translate[maxIndex] / ratio;  //上采样后 为原始轮廓的转换关系
	rotateBest = rotatetheta[maxIndex];
	centerPt.x = centerPt.x / ratio;
	centerPt.y = centerPt.y / ratio;

	//根据转换关系 计算检测区域转换后的结果，并绘制mask图
	vector<Point> afterTrans;
	vector<Point2f> afterTransF;
	TransformMatrix transformM;
	transformM.getTransForm = true;
	transformM.theta = rotateBest * PI2Degree;
	transformM.ptx = centerPt.x + translateBest.x - centerPt.x*cos(transformM.theta) + centerPt.y*sin(transformM.theta);
	transformM.pty = centerPt.y + translateBest.y - centerPt.x*sin(transformM.theta) - centerPt.y*cos(transformM.theta);
	//将模板轮廓进行转换到待测图显示
	output.existFilmFlag = true;
	output.recogintionContour.contourPts= matchContour;
#pragma omp parallel for
	for (int i = 0; i < matchContour.size(); i++) {
		for (int j = 0; j < matchContour[i].size(); j++) {
			Point2f tranPt = transFormPt(Point2f(matchContour[i][j].x / ratio, matchContour[i][j].y / ratio), transformM);
			output.recogintionContour.contourPts[i][j] = tranPt;
		}
	}
	output.transformMatrix = transformM;
	errorMsg.error = false;
	return errorMsg;
}

//8、获取直线算子
//功能：获取贴膜工位的直线以及盖板边缘的直线
ErrMsg AlgFilmDetect::getLine(const GetLineInput &input, GetLineOutput &output)
{
	ErrMsg errorMsg;
	int imgindex = input.algPara.imgIndex;
	int algID = input.algPara.algID;
	errorMsg.algID = algID;
	errorMsg.algType = input.algPara.algType;
	errorMsg.error = true;
	vector<ROIShapeData> vROI = input.algPara.vROI;
	TransformMatrix transformM = AlgFilmDetect::transformMatrix[imgindex];
	if (!transformM.getTransForm) {
		errorMsg.vmsg = "没有获取到合适的转换矩阵";
		return errorMsg;
	}
	for (int i = 0; i < vROI.size(); i++) {
		LineStruct lineT;
		output.lineOutput.push_back(lineT);
	}
#pragma omp parallel for
	for (int i = 0; i < vROI.size(); i++) {
		//获取轮廓点集
		RectangleROI ROI;
		if (vROI[i].roiType != DrawROIType::ROI_Rectangle2 || vROI[i].points.size()!=3) {
			errorMsg.vmsg = "没有框选合适的旋转矩形ROI，请重新框选";
			return errorMsg;
		}
		ROI.pt1 = vROI[i].points[0];
		ROI.pt2 = vROI[i].points[1];
		ROI.direction = vROI[i].direction;
		ROI.offset = abs(vROI[i].offset1);
		ROI.indexROI = i;
		if (input.algPara.vROI[i].baseFlag) {
			ROI.pt1 = transFormPt(ROI.pt1, transformM);
			ROI.pt2 = transFormPt(ROI.pt2, transformM);
		}
		GatherEdgePtsInput inputGP;
		GatherEdgePtsOutput outputGP;
		inputGP.algPara = input.algPara.parms;
		inputGP.img = input.srcImg;
		inputGP.rectangleROI = ROI;

		ErrMsg errorMsgP = gatherEdgePts(inputGP, outputGP);
		if (errorMsgP.error) {
			errorMsg.vmsg = errorMsgP.vmsg;
			return errorMsg;
		}
			
		//拟合直线
		GatherLineInput inputGL;
		GatherLineOutput outputGL;
		inputGL.algPara = input.algPara.parms;
		inputGL.edgePts = outputGP.imgPts;
		inputGL.indexROI = i;
		ErrMsg errorMsgL =  gatherLine(inputGL, outputGL);
		if (errorMsgL.error) {
			errorMsg.vmsg = errorMsgL.vmsg;
			return errorMsg;
		}
		outputGL.fitLine.baseFlag = input.algPara.vROI[i].baseFlag;
		outputGL.fitLine.getFlag = true;
		output.lineOutput[i] = outputGL.fitLine;
	}
	//将直线转换为点用于在界面上显示
	vector<vector<cv::Point2f>> contourPts;//轮廓点--界面显示
	for (int i = 0; i < output.lineOutput.size(); i++) {
		vector<cv::Point2f > contourPt;
		contourPt.push_back(output.lineOutput[i].pt2);
		contourPt.push_back(output.lineOutput[i].pt1);
		contourPts.push_back(contourPt);
	}
	output.lineContour.contourPts = contourPts;
	errorMsg.error = false;
	return errorMsg;
}
//9、测量偏位算子
ErrMsg AlgFilmDetect::measureDeviation(const MeasureInput &input, MeasureOutput &output)
{
	AlgParamsMeasureConfig alg = *(AlgParamsMeasureConfig*)&(input.algPara.parms);
	double basicHeight = alg.d_params.block.basicHeightValue;
	double basicWidth = alg.d_params.block.basicWidthValue;
	double heightDis = alg.d_params.block.deviationHeight;
	double widthDis = alg.d_params.block.deviationWidth;
	ErrMsg errorMsg;
	int imgindex = input.algPara.imgIndex;
	int algID = input.algPara.algID;
	errorMsg.algID = algID;
	errorMsg.algType = input.algPara.algType;
	errorMsg.error = true;
	/*￥高度和宽度￥高度 ￥宽度￥无*/
	int flag = alg.i_params.block.flag;
	if (flag == 3) {
		errorMsg.error = false;
		return errorMsg;
	}
	//开始计算贴膜的高度和宽度，根据拟合直线的角度进行配对；
	LineStruct lineFilmH, lineFilmW, lineGlassH, lineGlassW;  //用于测量贴膜的高度和宽度的直线
	vector<LineStruct> lines= AlgFilmDetect::lineOutput[imgindex];
	if (lines.size() != 4) {
		errorMsg.error = true;
		errorMsg.vmsg = "获取的直线不等于4条";
		return errorMsg;
	}
	int direction = 0;//0-H 1-W
	for (int i = 0; i < lines.size(); i++) {
		if (!lines[i].getFlag) {
			errorMsg.error = true;
			errorMsg.vmsg = "没有正常获取第"+to_string(i)+"条直线";
			return errorMsg;
		}
		float theta = abs(atan2(lines[i].pt2.y - lines[i].pt1.y, lines[i].pt2.x - lines[i].pt1.x));
		if (abs(theta - 0) < abs(theta - CV_PI / 2) || abs(theta - CV_PI) < abs(theta - CV_PI / 2))
			direction = 0;
		else
			direction = 1;
		if (lines[i].baseFlag&&direction == 0)
			lineFilmH = lines[i];
		if (lines[i].baseFlag&&direction == 1)
			lineFilmW = lines[i];
		if ((!lines[i].baseFlag) && direction == 0)
			lineGlassH = lines[i];
		if ((!lines[i].baseFlag) && direction == 1)
			lineGlassW = lines[i];
	}
	int minDisflag = alg.i_params.block.minDisflag;   //距离类型
	if (minDisflag < 0) 
		minDisflag = 0;
	MeasureL2LInuput inputH, inputW;
	MeasureL2LOutput outputH, outputW;
	inputH.line1 = lineFilmH;
	inputH.line2 = lineGlassH;
	inputW.line1 = lineFilmW;
	inputW.line2 = lineGlassW;
	ErrMsg errorMsgH = measureL2L(inputH, outputH, minDisflag);
	ErrMsg errorMsgW = measureL2L(inputW, outputW, minDisflag);
	MeasureData measureH, measureW;
	measureH.description = "贴膜距离盖板底边缘距离";
	measureH.L2Ldistance = outputH.distance;
	if (abs(measureH.L2Ldistance - basicHeight) < heightDis)
		measureH.detectRlt = true;
	else
		measureH.detectRlt = false;
	measureH.exist = true;
	measureW.description = "贴膜距离盖板右边缘距离";
	measureW.L2Ldistance = outputW.distance;
	if (abs(measureW.L2Ldistance - basicWidth) < widthDis)
		measureW.detectRlt = true;
	else
		measureW.detectRlt = false;
	measureW.exist = true;
	if (flag == 0) {
		output.measureRlt.push_back(measureH);
		output.measureRlt.push_back(measureW);
	}
	else if(flag ==1)
		output.measureRlt.push_back(measureH);
	else if(flag ==2)
		output.measureRlt.push_back(measureW);
	errorMsg.error = false;
	return errorMsg;
}
//0-模板轮廓 1-模板轮廓中心点 2-模板图的方向 3-置信度值 4-偏移量 5-转换角度 6-相似度
void matchContourGrad(const vector<vector<cv::Point2f>> &matchContour, const cv::Point2f &centerPt, const vector<vector<float>> &matchDir, const AlgParamsRecognitionConfig &alg, const cv::Mat &sampleimg, vector<cv::Point2f> &translate, vector<float> &rotatetheta, vector < float > &countNumGrad)
{
	//float gradSum = 21;
	int startTheta = alg.i_params.block.rotateStart;
	int endTheta = alg.i_params.block.rotateEnd;
	int stepTheta = alg.i_params.block.stepTheta;
	double ratio = alg.d_params.block.ratio;
	double disGrad = alg.d_params.block.disGrad;
	double score = alg.d_params.block.score;
	if (disGrad < 0)
		disGrad = 20;
	if (ratio < 0)
		ratio = 0.2;
	int samplePt = alg.i_params.block.samplePt;
	if (samplePt < 0)
		samplePt = 2;
	int translateX = int(alg.i_params.block.translateX * ratio + 0.5);
	int translateY = int(alg.i_params.block.translateY * ratio + 0.5);
	int stepTranslarte = alg.i_params.block.stepTranslate;
	int stepC = 1, stepC2 = 1;
	if (matchContour.size() > 10)
		stepC = matchContour.size() / 5;
	float tempGrad = 0;
	Point2f centerBest;
	float bestTheta = 0;
	//求模板轮廓的梯度值 以及均值和归一化的值
#pragma omp parallel for
	for (int theta = startTheta; theta < endTheta; theta = theta + stepTheta) {
		vector<Point2f> ptTrans;
		vector<float> thetaTrans;
#pragma omp parallel for	
		//step0-求模板轮廓旋转后的点	
		for (int i = 0; i < matchContour.size(); i = i + 1) {
			/*int stepC2 = 200;
			if (matchContour[i].size() > 1000)
			stepC2 = matchContour[i].size() / 200;*/
			for (int j = 0; j < matchContour[i].size(); j = j + samplePt) {
				float x1 = (matchContour[i][j].x - centerPt.x)*cos(theta*PI2Degree) - (matchContour[i][j].y - centerPt.y)*sin(theta*PI2Degree) + centerPt.x;
				float y1 = (matchContour[i][j].x - centerPt.x)*sin(theta*PI2Degree) + (matchContour[i][j].y - centerPt.y)*cos(theta*PI2Degree) + centerPt.y;
				Point2f rotatec = Point2f(x1, y1);//旋转后的点
				float thetaT = matchDir[i][j] + theta;

#pragma omp critical
				{
					thetaTrans.push_back(thetaT*PI2Degree);   //存储旋转后的点
					ptTrans.push_back(rotatec);
				}

			}
		}
#if drawSampleC
		Mat color;
		cvtColor(sampleimg, color, COLOR_GRAY2RGB);
		for (auto t : outerPt) {
			Point c = Point(t);
			if (c.x < 0 || c.x >= sampleimg.cols || c.y < 0 || c.y >= sampleimg.rows)
				continue;
			color.at<Vec3b>(c) = Vec3b(0, 0, 255);
		}
		for (auto f : innerPt) {
			Point d = Point(f);
			if (d.x < 0 || d.x >= sampleimg.cols || d.y < 0 || d.y >= sampleimg.rows)
				continue;
			color.at<Vec3b>(Point(d)) = Vec3b(0, 255, 0);
		}
		int cccc = 0;
#endif
		//计算旋转后的轮廓点集的梯度信息
#pragma omp parallel for

		//step 3: 遍历移动范围
		for (int u = -(translateX); u <= translateX; u = u + stepTranslarte) {
			for (int v = -translateY; v <= translateY; v = v + stepTranslarte) {
				Point2f currentCentre = Point2f(u, v);
				float correctVal = 0;
				getGradSumofEdgeEle(sampleimg, currentCentre, ptTrans, thetaTrans, correctVal);
#pragma omp critical
				{
					if (correctVal > score) {
						translate.push_back(currentCentre);
						rotatetheta.push_back(theta);
						countNumGrad.push_back(correctVal);
					}
				}
			}
		}
	}
	return;
}
//轮廓匹配
//0-模板轮廓 1-模板轮廓中心点 1- 参数 2-待测图 3-偏移量 4-旋转角 5-梯度 6-模板轮廓中心
void matchContourGrad(const vector<vector<cv::Point2f>> &matchContour, const Point2f &centerPt, const vector<vector<float>> &matchDir, const float meanGrad, const AlgParamsRecognitionConfig &alg, const cv::Mat &sampleimg, vector<cv::Point2f> &translate, vector<float> &rotatetheta, vector<float> &gradAllPts, vector<int> &countNumGrad)
{
	//float gradSum = 21;
	int startTheta = alg.i_params.block.rotateStart;
	int endTheta = alg.i_params.block.rotateEnd;
	int stepTheta = alg.i_params.block.stepTheta;
	double ratio = alg.d_params.block.ratio;
	double disGrad = alg.d_params.block.disGrad;
	if (disGrad < 0)
		disGrad = 20;
	if (ratio < 0)
		ratio = 0.2;
	int samplePt = alg.i_params.block.samplePt;
	if (samplePt < 0)
		samplePt = 2;
	int translateX = int(alg.i_params.block.translateX * ratio + 0.5);
	int translateY = int(alg.i_params.block.translateY * ratio + 0.5);
	int stepTranslarte = alg.i_params.block.stepTranslate;
	int stepC = 1, stepC2 = 1;
	if (matchContour.size() > 10)
		stepC = matchContour.size() / 5;
	float tempGrad = 0;
	Point2f centerBest;
	float bestTheta = 0;
	//求模板轮廓的梯度值 以及均值和归一化的值
#pragma omp parallel for
	for (int theta = startTheta; theta < endTheta; theta = theta + stepTheta) {
		vector<Point2f> outerPt;
		vector<Point2f> innerPt;
#pragma omp parallel for	
		//step0-求模板轮廓旋转后的点	
		for (int i = 0; i < matchContour.size(); i = i + 1) {
			/*int stepC2 = 200;
			if (matchContour[i].size() > 1000)
				stepC2 = matchContour[i].size() / 200;*/
			for (int j = 0; j < matchContour[i].size(); j = j + samplePt) {
				float x1 = (matchContour[i][j].x - centerPt.x)*cos(theta*PI2Degree) - (matchContour[i][j].y - centerPt.y)*sin(theta*PI2Degree) + centerPt.x;
				float y1 = (matchContour[i][j].x - centerPt.x)*sin(theta*PI2Degree) + (matchContour[i][j].y - centerPt.y)*cos(theta*PI2Degree) + centerPt.y;
				Point2f rotatec = Point2f(x1, y1);//旋转后的点
				float thetaT = matchDir[i][j] + theta + 22.5 + 180;
				if (thetaT < 0)
					thetaT += 360;
				int thetatemp = int(thetaT / 45) % 8;
				Point2f rotateOuter = rotatec + Point2f(outOffset[thetatemp]);  //旋转后的外点
				Point2f rotateInner = rotatec + Point2f(inOffset[thetatemp]);  //旋转后的内点
#pragma omp critical
				{
					outerPt.push_back(rotateOuter);   //存储旋转后的点
					innerPt.push_back(rotateInner);
				}

			}
		}
#if drawSampleC
		Mat color;
		cvtColor(sampleimg, color, COLOR_GRAY2RGB);
		for (auto t : outerPt) {
			Point c = Point(t);
			if (c.x < 0 || c.x >= sampleimg.cols || c.y < 0 || c.y >= sampleimg.rows)
				continue;
			color.at<Vec3b>(c) = Vec3b(0, 0, 255);
		}
		for (auto f : innerPt) {
			Point d = Point(f);
			if (d.x < 0 || d.x >= sampleimg.cols || d.y < 0 || d.y >= sampleimg.rows)
				continue;
			color.at<Vec3b>(Point(d)) = Vec3b(0, 255, 0);
		}
		int cccc = 0;
#endif
		//计算旋转后的轮廓点集的梯度信息
#pragma omp parallel for

		//step 3: 遍历移动范围
		for (int u = -(translateX); u <= translateX; u = u + stepTranslarte) {
			for (int v = -translateY; v <= translateY; v = v + stepTranslarte) {
				Point2f currentCentre = Point2f(u, v);
				int countNum = 0;
				float gradSum = getGradSumofEdgeEle(sampleimg, meanGrad, disGrad,currentCentre, outerPt, innerPt, countNum);
				//if (gradSum > tempGrad) {
				//	tempGrad = gradSum;
				//	centerBest = currentCentre;
				//	bestTheta = theta;
				//}
#pragma omp critical
				{
					if (gradSum > 100) {
						translate.push_back(currentCentre);
						rotatetheta.push_back(theta);
						gradAllPts.push_back(gradSum);
						countNumGrad.push_back(countNum);
					}
				}
			}
		}
	}
	return;

}
//求模板梯度方向和待测的相似度
//0-待测图的梯度方向图像 1-平移量 2-模板轮廓点 3-模板梯度方向 4-相似性
void getGradSumofEdgeEle(const cv::Mat &srcImg, const cv::Point2f &current, vector<cv::Point2f> &matchPts, vector<float> &matchDir, float &correctVal)
{
	correctVal = 0;
	int count = 0;
	for (int i = 0; i < matchPts.size(); i++) {
		Point edgePt = Point(matchPts[i] + current);
		if (edgePt.x < srcImg.cols&&edgePt.x>0 && edgePt.y > 0 && edgePt.y < srcImg.rows) {
			float tempGrad = srcImg.at<float>(edgePt);
			correctVal += (cos(matchDir[i])*cos(tempGrad) + sin(matchDir[i] * sin(tempGrad)));
			count++;
		}
	}
	correctVal /= count;
	return;
}
//求轮廓点集的梯度信息
//0-待测图 1-模板梯度均值 2-梯度阈值 3-当前点 4-外轮廓点 5-内轮廓点 6-满足条件的轮廓点个数  返回值待测的梯度总和
float getGradSumofEdgeEle(const cv::Mat &srcImg, const float &meanGrad, const float &disGrad, const cv::Point2f &current, vector<cv::Point2f> &edgesOut, vector<cv::Point2f> &edgesIn, int &countNum)
{
	float currentGradSum = 0;
	int count = 0;
	countNum = 0;
	for (int i = 0; i < (int)(edgesOut.size()); i++) {
		Point edgeOut = Point(current + edgesOut[i]);
		Point edgeIn = Point(current + edgesIn[i]);
		if (edgeOut.x < srcImg.cols&&edgeOut.x>0 && edgeOut.y > 0 && edgeOut.y < srcImg.rows&&edgeIn.x < srcImg.cols&&edgeIn.x>0 && edgeIn.y > 0 && edgeIn.y < srcImg.rows) {
			float tempGrad = abs(srcImg.at<uchar>(edgeOut) - srcImg.at<uchar>(edgeIn));
			currentGradSum = currentGradSum + tempGrad;
			count++;;
			if (tempGrad > meanGrad - disGrad)   //待测梯度大于模板梯度
				countNum++;
		}
	}
	if (countNum < count * 5 / 6.0)
		currentGradSum = 0;
	if (count == 0)
		return 0;
	else 
		return currentGradSum;
}
//0-模板小图 1-算子参数 2-模板小图相对于左上角点 3-模板轮廓 4-模板轮廓对应的梯度方向 5-模板梯度均值 6-模板梯度和 7-轮廓中心点
ErrMsg getTemplateContour(const cv::Mat &templateImg, const AlgParamsRecognitionConfig &alg, cv::Point leftTop, vector<vector<cv::Point2f>> &templateContour, vector<vector<float>> &templateDir, vector<vector<float>> &grad, float &meanGrad,float &matchGrad, cv::Point2f &centerPt)
{
	float rad2Angle = 180 / 3.1415926;
	ErrMsg error;
	if (templateImg.empty()) {
		error.vmsg = "模板图不存在";
		error.error = true;
		return error;
	}
	double ratio = alg.d_params.block.ratio;
	if (ratio < 0)
		ratio = 0.2;
	double detectArea = (alg.i_params.block.detectContourArea*ratio*ratio);
	int cannylow = alg.i_params.block.cannyLow;
	int cannyhigh = alg.i_params.block.cannyHigh;
	int sobelsize = alg.i_params.block.sobelSize;
	Mat sampleImg, resizeimg;
	resize(templateImg, sampleImg, Size(0, 0), ratio, ratio);

	//cv::threshold(resizeimg, resizeimg, thersholdT, 255, THRESH_BINARY);
	blur(sampleImg, resizeimg, Size(3, 3));
	Canny(resizeimg, resizeimg, cannylow, cannyhigh, sobelsize);//边缘检测
	vector<Vec4i> hierarchy11;
	vector<vector<Point>> contours;
	findContours(resizeimg.clone(), contours, hierarchy11, RETR_EXTERNAL, CHAIN_APPROX_NONE);
	Mat maskImg = Mat::zeros(resizeimg.size(), CV_8UC1);
	drawContours(maskImg, contours, -1, Scalar(255), 1);
	if (contours.size() < 1) {
		error.vmsg = "没有找到模板轮廓";
		error.error = true;
		return error;
	}
	//剔除干扰轮廓信息
#pragma omp parallel for
	for (int i = 0; i < contours.size(); ++i)
	{
		RotatedRect	boundRectRotate;
		boundRectRotate = minAreaRect(contours[i]);
		int width = boundRectRotate.size.width;
		if (width > boundRectRotate.size.height)
			width = boundRectRotate.size.height;
		if (boundRectRotate.size.area() < detectArea)   //0609进行了调整，之前是宽度或高度<200就进行剔除
		{
			vector<vector<Point>> drawSub;
			drawSub.push_back(contours[i]);
#pragma omp critical
			{
				drawContours(resizeimg, drawSub, -1, Scalar(0), FILLED);
			}
			/*vector<vector<Point>> contour(1);
			Point2f pts[4];
			boundRectRotate.points(pts);
			for (int m = 0; m < 4; m++)
				contour[0].push_back(Point(pts[m]));
#pragma omp critical
			{
			drawContours(maskImg, contour, 0, Scalar(0), FILLED);
			}*/
		}
	}
	contours.clear();
	findContours(resizeimg, contours, hierarchy11, RETR_EXTERNAL, CHAIN_APPROX_NONE);
	//求模板轮廓点的梯度方向
	/*Mat color;
	cvtColor(sampleImg, color, COLOR_GRAY2RGB);*/
	for (int i = 0; i < (int)contours.size(); i++) {
		vector<float > gradofContourEle((int)contours[i].size());
		for (int j = 0; j < (int)contours[i].size(); j++) {
			Point x1 = contours[i][j] + Point(1, 0);
			if (x1.x >= sampleImg.cols)
				x1 = contours[i][j];
			Point x_1 = contours[i][j] + Point(-1, 0);
			if (x_1.x < 0)
				x_1 = contours[i][j];

			Point y1 = contours[i][j] + Point(0, 1);
			if (y1.y >= sampleImg.rows)
				y1 = contours[i][j];
			Point y_1 = contours[i][j] + Point(0, -1);
			if (y_1.y < 0)
				y_1 = contours[i][j];

			float xGradOrig = (float)(sampleImg.at<uchar>(x1) - sampleImg.at<uchar>(x_1));
			float yGradOrig = (float)(sampleImg.at<uchar>(y1) - sampleImg.at<uchar>(y_1));
			/*color.at<Vec3b>(Point(x1)) = Vec3b(0, 0, 255);
			color.at<Vec3b>(Point(x_1)) = Vec3b(0, 255,0);
			color.at<Vec3b>(Point(y1)) = Vec3b(255, 0, 0);
			color.at<Vec3b>(Point(y_1)) = Vec3b(255, 255, 0);*/
			float dir = rad2Angle * atan2(yGradOrig, xGradOrig);   //通过横向和纵向滤波核求梯度方向
			gradofContourEle[j] = dir;
		}
		templateDir.push_back(gradofContourEle);
	}
	//计算模板轮廓的灰度梯度
	matchGrad = 0;
	int count = 0;
	for (int i = 0; i < templateDir.size(); i++) {
		vector<float> tempGrad;
		for (int j = 0; j < templateDir[i].size(); j++) {
			float thetaT = templateDir[i][j] + 22.5 + 180;
			if (thetaT < 0)
				thetaT += 360;
			int thetatemp = int(thetaT / 45) % 8;
			Point rotateOuter = contours[i][j] + Point(outOffset[thetatemp]);  //旋转后的外点
			Point rotateInner = contours[i][j] + Point(inOffset[thetatemp]);  //旋转后的内点
			if (rotateOuter.x < sampleImg.cols&&rotateOuter.x>0 && rotateOuter.y > 0 && rotateOuter.y < sampleImg.rows&&rotateInner.x < sampleImg.cols&&rotateInner.x>0 && rotateInner.y > 0 && rotateInner.y < sampleImg.rows) {
				float temp = sampleImg.at<uchar>(rotateOuter) - sampleImg.at<uchar>(rotateInner);
				matchGrad += abs(temp);
				tempGrad.push_back(temp);
				count++;
			}
			else
				tempGrad.push_back(-999999);
		}
	}
	meanGrad = matchGrad / count;  //梯度平均值
	//得到模板轮廓点相对于降采样后的原始图
	for (int i = 0; i < contours.size(); i++) {
		vector<Point2f> temp;
		for (int j = 0; j < contours[i].size(); j++) {
			temp.push_back(Point2f(contours[i][j]) + Point2f(leftTop.x*ratio, leftTop.y*ratio));
		}
		templateContour.push_back(temp);
	}
	//求轮廓中心点
	centerPt = Point2f(0, 0);
	int numofPoints = 0;
	for (int i = 0; i < (int)(templateContour.size()); i++) {
		numofPoints = numofPoints + (double)(templateContour[i].size());
		for (int j = 0; j < (int)(templateContour[i].size()); j++) {
			centerPt.x = centerPt.x + templateContour[i][j].x;
			centerPt.y = centerPt.y + templateContour[i][j].y;
		}
	}
	centerPt.x = centerPt.x / numofPoints;
	centerPt.y = centerPt.y / numofPoints;
	
	return error;
}
/*拟合直线*/
//将待测点进行转换
cv::Point2f transFormPt(const cv::Point2f pt, TransformMatrix &transformM)
{
	float x1 = pt.x * cos(transformM.theta) - pt.y * sin(transformM.theta) + transformM.ptx;
	float y1 = pt.x  * sin(transformM.theta) + pt.y  * cos(transformM.theta) + transformM.pty;
	Point2f tranPt = Point2f(x1, y1);//旋转后的点
	return tranPt;
}
//-------------------------------------------- Step2.3 gatherLine------------------------------------------//
//名称：拟合轮廓点获取直线
//功能：通过拟合输入的轮廓点信息获取直线，可以支持像素级轮廓点或世界级轮廓点，若为图像，pixval采用默认值1.0，若为世界，pixval则为当前相机下的pixval
//返回值 0-正常 1-轮廓点为空
ErrMsg gatherLine(const GatherLineInput &input, GatherLineOutput &output)
{
	ErrMsg errorMsg;
	if (input.edgePts.size() == 0) {
		errorMsg.error = true;
		errorMsg.vmsg = "轮廓点集为空";
		return errorMsg;
	}
	vector<Point2f> edgePtsFloat = input.edgePts;
	vector<Vec4d> lineV4;
	AlgParamsGetLineConfig * algPara = (AlgParamsGetLineConfig *)&input.algPara;
	double distace = algPara->d_params.block.distance;
	/*if (num20dis > 0)
		distace = algPara->d_params.block.distance;*/
	if (ransacLines(edgePtsFloat, lineV4, distace, 1, 500)) {
		errorMsg.error = true;
		errorMsg.vmsg = "第" + to_string(input.indexROI) + "条直线ransac失效";
		return errorMsg;
	}
	int numpts = int(edgePtsFloat.size());
	Vec4f lineV4f;
	Vec4f temp;                                              //拟合的轮廓线
	vector<Point2f> vertex;                                                        //ROI的四个顶点
	float k;
	float len;

#if drawline==1
	for (int c = 0; c < input.edgePts.size(); c++) {
		globalcolor.at<Vec3b>(Point(input.edgePts[c].x + 500, input.edgePts[c].y + 500)) = Vec3b(0, 0, 255);
	}
	imwrite("K:/zkhy_boardMeasure/Bin/测试/draw_PTSS.bmp", globalcolor);
#endif
	//float len = (float)sqrt(pow(edgePtsFloat[0].x - edgePtsFloat[numpts-1].x, 2) + pow(edgePtsFloat[0].y - edgePtsFloat[numpts - 1].y, 2));
	cv::fitLine(edgePtsFloat, lineV4f, DIST_L2, 0, 0.01, 0.01);
	RotatedRect rect = minAreaRect(edgePtsFloat);
	len = rect.size.height;
	if (rect.size.height < rect.size.width)
		len = rect.size.width;
	int flagK = 0;
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
	//filetimecal << "点 "<<output.fitLine.pt1 << " " << output.fitLine.pt2 << endl;
//#if drawline==1
//	line(globalcolor, Point(output.fitLine.pt1.x+500, output.fitLine.pt1.y+500), Point(output.fitLine.pt2.x + 500, output.fitLine.pt2.y + 500), Scalar(255, 0, 0), 1);	
//	char namew1[300];
//	sprintf_s(namew1, "%s%d%s", "K:/zkhy_boardMeasure/Bin/测试/world_line", numBlock, ".bmp");
//	imwrite(namew1, globalcolor);
//	
//#endif
	/*t2 = (getTickCount() - t1) * 1000 / getTickFrequency();
	filetimecal << "获取直线" << t2 << endl;*/
	errorMsg.error = false;
	return errorMsg;
}

//----------------------------------------measureL2L--------------------------------------------//
//返回值:0-正常 1- 输入的线异常
ErrMsg measureL2L(const MeasureL2LInuput &input, MeasureL2LOutput &output, int minFlag)
{
	ErrMsg errorMsg;
	float len1 = sqrtf(powf(input.line1.pt1.x - input.line1.pt2.x, 2) + powf(input.line1.pt1.y - input.line1.pt2.y, 2));
	float len2 = sqrtf(powf(input.line2.pt1.x - input.line2.pt2.x, 2) + powf(input.line2.pt1.y - input.line2.pt2.y, 2));
	if (len1 < 0.0001 || len2 < 0.0001) {
		errorMsg.error = true;
		errorMsg.vmsg = "送入的直线有问题";
	}
	float pt1Line1ToLine2 = point2line(input.line1.pt1, input.line2.pt1, input.line2.pt2);
	float pt2Line1ToLine2 = point2line(input.line1.pt2, input.line2.pt1, input.line2.pt2);

	float pt1Line2ToLine1 = point2line(input.line2.pt1, input.line1.pt1, input.line1.pt2);
	float pt2Line2ToLine1 = point2line(input.line2.pt2, input.line1.pt1, input.line1.pt2);
	float minDis = 10000000000000;
	if (minFlag == 0) {
		if (len1 > (len2 * 2))
			output.distance = min(pt1Line2ToLine1 , pt2Line2ToLine1);
		else if ((len1 * 2) < len2)
			output.distance = min(pt1Line1ToLine2 , pt2Line1ToLine2);
		else {
			vector<float> dis;
			dis.push_back(pt1Line1ToLine2);
			dis.push_back(pt2Line1ToLine2);
			dis.push_back(pt1Line2ToLine1);
			dis.push_back(pt2Line2ToLine1);
			for (int i = 0; i < dis.size(); i++) {
				if (dis[i] < minDis)
					minDis = dis[i];
			}
			output.distance = minDis;
		}
		errorMsg.error = false;
		return errorMsg;
	}

	/*filetimecal << "坐标 " << input.line1.pt1.x << " " << input.line1.pt1.y << " " << input.line2.pt1.x << " " << input.line2.pt1.y << endl;
	filetimecal << "测量距离 " << pt1Line1ToLine2 << " " << pt2Line1ToLine2 << " " << pt1Line2ToLine1 << " " << pt2Line2ToLine1 << endl;*/
	else {
      if (len1 > (len2 * 2))
		  output.distance = float((pt1Line2ToLine1 + pt2Line2ToLine1) / 2);
	  else if ((len1 * 2) < len2)
		  output.distance = float((pt1Line1ToLine2 + pt2Line1ToLine2) / 2);
	  else
		output.distance = float((pt1Line1ToLine2 + pt2Line1ToLine2 + pt1Line2ToLine1 + pt2Line2ToLine1) / 4);
	errorMsg.error = false;
	return errorMsg;
	}
	
}
float point2line(Point2f p, Point2f p1, Point2f p2)
{
	float a, b, c, dis;
	// 化简两点式为一般式
	// 两点式公式为(y - y1)/(x - x1) = (y2 - y1)/ (x2 - x1)
	// 化简为一般式为(y2 - y1)x + (x1 - x2)y + (x2y1 - x1y2) = 0
	// A = y2 - y1
	// B = x1 - x2
	// C = x2y1 - x1y2
	a = p2.y - p1.y;
	b = p1.x - p2.x;
	c = p2.x * p1.y - p1.x * p2.y;
	// 距离公式为d = |A*x0 + B*y0 + C|/√(A^2 + B^2)
	dis = float(1.0*abs(a * p.x + b * p.y + c) / sqrt(a * a + b * b));
	return dis;
}
//-------------------------------------------- Step2.1 gatherEdgePts---------------------------------//
//名称：获取边缘点
//功能：获取边缘点模块用于拟合直线
//参数列表：0-输入 1-输出
//返回值：0-成功 1-图像为空 2-梯度阈值设置不合适需要调整 3-黑图没有边缘
ErrMsg gatherEdgePts(const GatherEdgePtsInput &input, GatherEdgePtsOutput &output)
{
	ErrMsg errorMsg;
	Mat img = input.img.clone();
	int rows = img.cols;
	int cols = img.rows;

	RectangleROI rectROI = input.rectangleROI;
	if (img.empty()) {
		errorMsg.error = true;
		errorMsg.vmsg = "输入图像为空";
		return errorMsg;
	}
	if (img.channels() == 3)
		cvtColor(img, img, COLOR_RGB2GRAY);

	float scanvx, scanvy;
	vector<Point2f> vertex;

	float len = (float)sqrt(pow(rectROI.pt2.x - rectROI.pt1.x, 2) + pow(rectROI.pt2.y - rectROI.pt1.y, 2));
	float vx = (float)(rectROI.pt2.x - rectROI.pt1.x) / len;
	float vy = (float)(rectROI.pt2.y - rectROI.pt1.y) / len;

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


	AlgParamsGetLineConfig gatherEdgePara = *(AlgParamsGetLineConfig*)&input.algPara;
	int processStyle;
	int oriGrad = gatherEdgePara.i_params.block.Tgrad;
	double thresholdT = gatherEdgePara.d_params.block.threshold;
	processStyle = gatherEdgePara.i_params.block.processStyle;  //0-不增强 1-增强 2-二值化
	//判断图像是否含有边缘
	double theta = abs(atan2(rectROI.pt2.y - rectROI.pt1.y, rectROI.pt2.x - rectROI.pt1.x));
	Mat edgeSobel;
	int flagDark = 0;
	int edgeProc = 1;
	int validPts = gatherEdgePara.i_params.block.validPts;  //获取上下边缘 以及基准相机的边缘的时候validPts=1；除此以为validPts为界面设置阈值
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

	if (processStyle == 1) {   //对于不单独处理右侧边缘 或者处理右侧边缘 但是当前的矩形不是非基准的矩形时 还是需要增强处理。
		int sobelsize = gatherEdgePara.i_params.block.sobelsize;
		if ((abs(theta - CV_PI) < abs(theta - CV_PI / 2)) || (abs(theta) < abs(theta - CV_PI / 2))) {
			Sobel(subimg, edgeSobel, CV_16S, 0, 1, sobelsize, 1, 0, BORDER_DEFAULT);  //找水平的边线 垂直方向sobel
		}
		else {
			Sobel(subimg, edgeSobel, CV_16S, 1, 0, sobelsize, 1, 0, BORDER_DEFAULT);  //找垂直的边线 垂直方向sobel
		}
		convertScaleAbs(edgeSobel, subimg);
	}
	else if (processStyle == 2) {
		threshold(subimg, subimg, thresholdT, 255, THRESH_BINARY);
	}
	gatherEdgePara.i_params.block.validPts = validPts;
	int boundPtserror = searchBoundaryForLine(subimg, rectROI, gatherEdgePara, flagRight, boundingRectangle, output.imgPts);
#if drawpts==1
#pragma omp critical
	{
		Mat colorimg;
		cvtColor(img, colorimg, COLOR_GRAY2RGB);

		for (int c = 0; c < vertex.size(); c++) {
			line(colorimg, vertex[c], vertex[(c + 1) % 4], Scalar(0, 255, 0), 1);
		}
		char namew1[100];
		for (int i = 0; i < output.imgPts.size(); i++) {

			colorimg.at<Vec3b>(output.imgPts[i]) = Vec3b(0, 0, 255);
		}
		sprintf_s(namew1, "%s%d%s", "D:/板材尺寸测量中间结果图暂存/edgePts_", numPtsdraw, ".png");

		imwrite(namew1, colorimg);

		numPtsdraw++;
	}
#endif
	if (output.imgPts.size() == 0) {
		errorMsg.error = true;
		errorMsg.vmsg = "ROI" + to_string(rectROI.indexROI) + "获取轮廓点集为空";
		return errorMsg;
	}
	errorMsg.error = false;
	return errorMsg;
}
//-----------------------------获取轮廓点-----------------------//
//0-输入图像 1- 输入获取轮廓的ROI 2-参数 3- 返回轮廓点
//0-正常 1- 异常
int searchBoundaryForLine(cv::Mat &img, RectangleROI roiRect, AlgParamsGetLineConfig &algPara, int &calMaxGrad, cv::Rect &boundingRectangle, vector<cv::Point2f> &contours)
{
	float range = (float)1000;//以前是50
	float len = (float)sqrt(pow(roiRect.pt2.x - roiRect.pt1.x, 2) + pow(roiRect.pt2.y - roiRect.pt1.y, 2));
	if (abs(len) <= 1e-5 || roiRect.offset <= 1e-5)
		return 2;
	vector<Point2f> vertex;
	int step = algPara.i_params.block.step;
	vector<Vec4i> seedEdgeGroups;
	vector<Point> edgePtsGroup;
	vector<Point> edgePtsWhitegroup;
	int Tgrad = algPara.i_params.block.Tgrad;                                                                 //将之前的10变为了20 排除杂点的干扰
	float sharp;
	LineStruct lineContour;                                                         //拟合的轮廓线
	LineStruct lineP1;                                                              //ROI的p1点所在的直线
	LineStruct lineP2;                                                              //ROI的p2点所在的直线
	Vec4f temp;
	seedEdgeGroups.push_back(Vec4i(int(roiRect.pt1.x), int(roiRect.pt1.y), int(roiRect.pt2.x), int(roiRect.pt2.y)));
	int rangeFinal = algPara.i_params.block.range;
	//进行加速处理
	int validPts = algPara.i_params.block.validPts;
	if (calMaxGrad == 1) {
		collectPolygonEdgePointsGatherLineGray(img, calMaxGrad, seedEdgeGroups, roiRect.direction, rangeFinal, Tgrad, step, validPts, edgePtsGroup, sharp); //如果是多段的ROI也可以多次调用此函数
	}
	else {
		if (roiRect.offset > range) {
			vector<Vec4i> seedEdgeGroupsOut;
			computeCoarseLine(img, calMaxGrad, seedEdgeGroups, roiRect.direction, roiRect.offset, Tgrad, validPts, seedEdgeGroupsOut);
			//if(flagEdge==0)
			collectPolygonEdgePointsGatherLineGray(img, calMaxGrad, seedEdgeGroupsOut, roiRect.direction, rangeFinal, Tgrad, step, validPts, edgePtsGroup, sharp); //如果是多段的ROI也可以多次调用此函数
																																								   //else
																																								   //	collectPolygonEdgePointsGatherLineFirstMaxSecondGradFast(img, seedEdgeGroupsOut, roiRect.direction,5, Tgrad, step, edgePtsGroup, sharp); //如果是多段的ROI也可以多次调用此函数
			seedEdgeGroupsOut.clear();
		}
		else {
			//if(flagEdge ==0)
			collectPolygonEdgePointsGatherLineGray(img, calMaxGrad, seedEdgeGroups, roiRect.direction, roiRect.offset, Tgrad, step, validPts, edgePtsGroup, sharp);                 //如果是多段的ROI也可以多次调用此函数
																																													/*	else
																																													collectPolygonEdgePointsGatherLineFirstMaxSecondGradFast(img, seedEdgeGroups, roiRect.direction, roiRect.offset, Tgrad, step, edgePtsGroup, sharp);	*/
		}
	}

	for (int i = 0; i < edgePtsGroup.size(); i++) {
		Point2f tempblack = Point2f(float(edgePtsGroup[i].x), float(edgePtsGroup[i].y));
		GetSubPixel(img, tempblack);
		tempblack += Point2f(boundingRectangle.x, boundingRectangle.y);
		contours.push_back(tempblack);
	}
	if (contours.size() < 2)
		return 3;
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
int computeCoarseLine(const Mat& gray, int calMaxGrad, vector<Vec4i> seedEdgeGroups, int polar, float Tdist, int Tgrad, int validPts, vector<Vec4i> &seedEdgeGroupsOut)
{
	vector<Point> edgePtsGroup;
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
	vector<Vec4d> lineV4;
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
// --------------------ransacLines---------------------- -//
//实现：选取的是距离 随机选择的两个点距离小于distance点数最多的点集。然后 去掉那些距离超过distance的点集
//std::vector<cv::Point>& input                                输入：找的边缘点集
//std::vector<cv::Vec4d>& lines                                输入：边缘点中的两个点，到此两点形成的
//float distance                                               输入：小于的最小距离
//unsigned int ngon                                            输入：迭代次数
//unsigned int itmax                                           输入：找寻的点的次数
//----------------------------------------------------------------------------------------------------//
int ransacLines(std::vector<cv::Point>& input, std::vector<cv::Vec4d>& lines, double distance, unsigned int ngon, unsigned int itmax)
{
	for (int i = 0; i < int(ngon); ++i) {
		unsigned int Mmax = 0;
		cv::Point imax;
		cv::Point jmax;
		cv::Vec4d line;
		size_t t1, t2;
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

			Point i = input[t1];
			Point j = input[t2];
			for (int p = 0; p < input.size(); p++)
			{
				Point a = input[p];
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
		line[0] = imax.x;
		line[1] = imax.y;
		line[2] = jmax.x;
		line[3] = jmax.y;


		lines.push_back(line);
		auto iter = input.begin();
		while (iter != input.end())
		{
			float dis = point2line(*iter, imax, jmax);
			if (dis > distance)
				iter = input.erase(iter);  //erase the dis within , then point to
			//   the next element
			else ++iter;
		}
	}
	return 0;
}
//--------------------ransacLines-----------------------//
//实现：选取的是距离 随机选择的两个点距离小于distance点数最多的点集。然后 去掉那些距离超过distance的点集
//std::vector<cv::Point>& input                                输入：找的边缘点集
//std::vector<cv::Vec4d>& lines                                输入：边缘点中的两个点，到此两点形成的
//float distance                                               输入：小于的最小距离
//unsigned int ngon                                            输入：迭代次数
//unsigned int itmax                                           输入：找寻的点的次数
//----------------------------------------------------------------------------------------------------//
int ransacLines(std::vector<cv::Point2f>& input, std::vector<cv::Vec4d>& lines, double distance, unsigned int ngon, unsigned int itmax)
{
	for (int i = 0; i <int(ngon); ++i) {
		unsigned int Mmax = 0;
		cv::Point2f imax;
		cv::Point2f jmax;
		cv::Vec4d line;
		size_t t1, t2;
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
		line[0] = imax.x;
		line[1] = imax.y;
		line[2] = jmax.x;
		line[3] = jmax.y;


		lines.push_back(line);
		auto iter = input.begin();
		while (iter != input.end())
		{
			float dis = point2line(*iter, imax, jmax);
			if (dis > distance)
				iter = input.erase(iter);  //erase the dis within , then point to
			//   the next element
			else ++iter;
		}
	}
	return 0;
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
int collectPolygonEdgePointsGatherLineGray(const Mat& gray, int calMaxGrad, vector<Vec4i> seedEdgeGroups, int polar, float Tdist, int Tgrad, int step, int validPts, vector<Point>& edgePtsGroup, float& sharp)
{
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
	if (calMaxGrad == 1)
		Tgrad = 4;
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
				/*everylinegrad.push_back(grad);
				gradcpie << grad << endl;
				everylineX.push_back(x);
				everylineY.push_back(y);*/
			}
			/*gradcpie << "image" << endl;
			for (int count = 0; count<everylinegrad.size()-1; count++){
			if (everylinegrad[count + 1]>(10 * everylinegrad[count]) && everylinegrad[count + 1] > Tgrad){
			edgePtsGroup.push_back(Point(everylineX[count+1], everylineY[count+1]));
			sharp += everylinegrad[count + 1]; cnt++;
			}
			}*/
			if (maxGrad > Tgrad) {
				x = int(xl + nlen0 * vn[0]);
				y = int(yl + nlen0 * vn[1]);
				edgePtsGroup.push_back(Point(x, y));
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
