//***************************************类名称：AlgFilmDetect（ver1.00.00）********************************************||
//***************************************编写者：王南南****************************************************************||
//***************************************编写时间：2020年10月11日****************************************************||
//***************************************类功能：实现AAhole缺陷检测********************************************************||

///20201011 1、贴膜检工位集成：贴膜识别、获取直线、偏位测量
#pragma once
//#include "AlgProcessDataDefine.h"
//#include "AlgProcessInterface.h"
#include "io.h"
#include "stdio.h"
using namespace std;

#ifndef _PROCESS_DLL_API  
#define _PROCESS_DLL_API _declspec(dllexport)  
#endif
//算子ID名称
enum ALGID
{
	RECOGNITION, //贴膜识别
	GETLINE,     //获取直线
	MEASURE,     //测量偏位
};
//0-贴膜识别算子参数
//struct AlgParamsRecognitionConfig
//{
//	union
//	{
//		struct
//		{
//			int shareMatch;
//			int matchStyle;
//			int rotateStart;
//			int rotateEnd;
//			int stepTheta;
//			int translateX;
//			int translateY;
//			int stepTranslate;
//			int cannyLow;
//			int cannyHigh;
//			int sobelSize;
//			int dis;
//			int detectContourArea;
//			int samplePt;
//			int metric;
//			
//		}block;
//		int data[PARAMS_MAXNUM];
//	}i_params;
//	union
//	{
//		struct
//		{
//			double ratio;
//			double score;
//			double disGrad;
//		}block;
//		double data[PARAMS_MAXNUM];
//	}d_params;
//};
//0-贴膜识别算子Msg参数
struct AlgMsgRecognitionConfig
{
	//初始化data大小
	//格式以$分开，空格不计
	//数据类型 Int  Double
	//控件类型 D_SpinBox I_Spinbox Combox CheckBox	
	//                 “算子类型 0-正常参数 1-界面勾选特征 $参数标识（只看不用）   $数据类型  $控件       $默认值  $参数名称               $参数意义  ￥下拉框的定义 $在界面显示顺序，不同算子的显示顺序是独立的 互补影响”
	vector<string> msgs;
	AlgMsgRecognitionConfig()
	{
		msgs.push_back("0 $shareMatch	     $Int       $CheckBox    $1       $是否共用同一个模板 $是否共用同一个模板$10");
		msgs.push_back("0 $matchStyle        $Int       $Combox      $0       $匹配方式        $选择合适的匹配方式 ￥轮廓匹配  $20");		
		msgs.push_back("0 $ratio     	     $Double    $D_Spinbox   $0.2     $图像降采样比例     $图像降采样比例，若原始图已经进行了降采样0.5，则此值为0.4         $30");
		msgs.push_back("0 $rotateStart	     $Int       $I_Spinbox   $-30	  $起始旋转角度   $起始旋转角度    $40");
		msgs.push_back("0 $rotateEnd	     $Int       $I_Spinbox   $30  	  $终止旋转角度  $终止旋转角度     $50");
		msgs.push_back("0 $stepTheta	     $Int       $I_Spinbox   $1  	  $旋转角度步长  $旋转角度步长     $60");
		msgs.push_back("0 $translateX	     $Int       $I_Spinbox   $200     $X方向平移量  $X方向平移量      $70");
		msgs.push_back("0 $translateY	     $Int       $I_Spinbox   $200     $Y方向平移量   $Y方向平移量     $80");
		msgs.push_back("0 $stepTranslate	 $Int       $I_Spinbox   $2  	  $平移步长    $平移步长       $90");
		msgs.push_back("0 $cannyLow	         $Int       $I_Spinbox   $100     $canny低阈值  $canny低阈值       $110");
		msgs.push_back("0 $cannyHigh         $Int       $I_Spinbox   $200  	  $canny高阈值  $canny高阈值       $120");
		msgs.push_back("0 $sobelSize         $Int       $I_Spinbox   $3  	  $canny边缘核   $canny边缘核      $130");
		msgs.push_back("0 $dis               $Int       $I_Spinbox   $2  	  $计算梯度的偏移 $计算梯度的偏移     $140");
		msgs.push_back("0 $detectContourArea $Int       $I_Spinbox   $50000  $剔除干扰点轮廓面积$剔除干扰点轮廓面积 $150");
		msgs.push_back("0 $samplePt          $Int       $I_Spinbox   $2  	  $匹配轮廓点抽样  $匹配轮廓点抽样   $160");
		msgs.push_back("0 $score             $Double    $D_Spinbox   $0.5     $匹配置信度     $匹配置信度     $170");
		msgs.push_back("0 $disGrad           $Double    $D_Spinbox   $20      $梯度阈值     $统计满足模板梯度均值-该阈值的梯度的轮廓点个数     $165");
		msgs.push_back("0 $metric            $Int       $Combox      $0       $评测指标        $选择合适的评测指标 ￥满足梯度阈值的轮廓点最多￥梯度最大￥梯度方向相似性     $25");

	}
};
//0-贴膜识别算子输出转换关系
struct TransformMatrix {
	float ptx;
	float pty;
	float theta;
	bool getTransForm = false;//是否正确获取了转换关系
};
//0-贴膜识别算子输入
//struct RecognitionInput
//{
//	cv::Mat srcImg;
//	SingleAlgInfo algPara;
//};
//0-贴膜识别算子输出
//struct RecognitionOutput
//{
//	bool    existFilmFlag;            //贴膜是否存在 true-存在 false-不存在  -输出给MeasureData
//	ResImg recogintionContour;        //模板轮廓转换后的结果
//	TransformMatrix transformMatrix;  //转换矩阵
//};
//1-获取直线算子
struct LineStruct
{
	cv::Point2f pt1;    //获取线段的两个点
	cv::Point2f pt2;
	bool   getFlag;   //该直线是否正确获取 true-获取 false-没有获取
	bool   baseFlag;//该直线是否基于定位
};
//1-获取直线算子输入
struct GetLineInput
{
	cv::Mat srcImg;
	//SingleAlgInfo algPara;
};
//1-获取直线算子输出
//struct GetLineOutput
//{
//	ResImg lineContour;
//	vector<LineStruct> lineOutput;
//};
//1-获取直线算子参数
//struct AlgParamsGetLineConfig
//{
//	union
//	{
//		struct
//		{
//			int   processStyle;           //图像预处理方式	
//			int   sobelsize;              //sobel预处理尺寸	
//			int   step;                   //获取轮廓点的步长	
//			int   Tgrad;                 //图像获取边缘的轮廓梯度
//			int    range;                //边缘粗定位后的搜素范围			
//			int   validPts;            //统计梯度有效点的个素数
//		}block;
//		int data[PARAMS_MAXNUM];
//	}i_params;
//	union
//	{
//		struct
//		{
//			double threshold;                       //二值化参数
//			double distance;						//用于排除异常轮廓点
//			
//		}block;
//		double data[PARAMS_MAXNUM];
//	}d_params;
//};
//1-获取直线算子Msg参数
struct AlgMsgGetLineConfig
{
	//初始化data大小
	//格式以$分开，空格不计
	//数据类型 Int  Double
	//控件类型 D_SpinBox I_Spinbox Combox CheckBox	
	//                 “算子类型 0-正常参数 1-界面勾选特征 $参数标识（只看不用）   $数据类型  $控件       $默认值  $参数名称               $参数意义  ￥下拉框的定义 $在界面显示顺序，不同算子的显示顺序是独立的 互补影响”
	vector<string> msgs;
	AlgMsgGetLineConfig()
	{
		msgs.push_back("0 $processStyle			$Int     $ Combox	    $ 1		$ 图像预处理方式 $对原图预处理方式 ￥无预处理 ￥sobel边缘增强 ￥二值化$10");
		msgs.push_back("0 $sobelsize				$ Int    $ I_SpinBox	$ 3 	$ sobel预处理尺寸			  $ 当采用sobel边缘增强时，调整该参数。$20");
		msgs.push_back("0 $step					$Int     $ I_SpinBox	$ 1 	$ 获取轮廓点的步长		      $ 获取轮廓点的步长，若时间比较长可以增大该值 $30");
		msgs.push_back("0 $Tgrad				    $ Int    $ I_SpinBox	$ 15 	$ 获取直线边缘的梯度		  $ 最终采用的获取边缘梯度阈值 $40");
		msgs.push_back("0 $range       			$ Int    $ I_SpinBox	$ 5 	$ 边缘粗定位后的搜索范围	  $ 边缘粗定位后的搜索范围$50");
		msgs.push_back("0 $validPts       			$ Int    $ I_SpinBox	$ 3 	$ 统计梯度有效像素点个数	  $ 统计梯度有效像素的个数$60");
		msgs.push_back("0 $threshold				$ Double $D_SpinBox		$120	$图像二值化阈值				  $ 选择二值化预处理 ");
		msgs.push_back("0 $distance				$ Double $D_SpinBox		$3	    $剔除边缘离群点阈值		      $ 拟合直线排除异常点距离参数");
	}
};
//2-测量偏位输入
//struct MeasureInput
//{
//	SingleAlgInfo algPara;
//};
//2-测量偏位输出
//struct MeasureOutput
//{
//	vector<MeasureData> measureRlt; //输出测量结果
//};
//2-测量偏位算子参数
//struct AlgParamsMeasureConfig
//{
//	union
//	{
//		struct
//		{
//			int flag;
//			int minDisflag;
//		}block;
//		int data[PARAMS_MAXNUM];
//	}i_params;
//	union
//	{
//		struct
//		{
//			double  basicHeightValue;                 //高度标准值
//			double  basicWidthValue;                 //宽度标准值
//			double  deviationHeight;                  //高度上下偏差
//			double  deviationWidth;                  //宽度上下偏差
//		}block;
//		double data[PARAMS_MAXNUM];
//	}d_params;
};
//2-测量偏位算子Msg参数
struct AlgMsgMeasureConfig
{
	//初始化data大小
	//格式以$分开，空格不计
	//数据类型 Int  Double
	//控件类型 D_SpinBox I_Spinbox Combox CheckBox	
	//                 “算子类型 0-正常参数 1-界面勾选特征 $参数标识（只看不用）   $数据类型  $控件       $默认值  $参数名称               $参数意义  ￥下拉框的定义 $在界面显示顺序，不同算子的显示顺序是独立的 互补影响”
	vector<string> msgs;
	AlgMsgMeasureConfig()
	{
		msgs.push_back("0 $flag         	$Int        $Combox     $0      $测量偏位类型     $选择测量的偏位类型  ￥高度和宽度￥高度 ￥宽度￥无 $10");
		msgs.push_back("0 $basicHeightValue	$Double     $D_Spinbox	$540   	$贴膜高度标准值   $贴膜的上边缘距离盖板底部的像素高度 $20");
		msgs.push_back("0 $basicWidthValue	$Double     $D_Spinbox	$1340   $贴膜宽度标准值   $贴膜的右边缘距离盖板左侧的像素宽度 $30");
		msgs.push_back("0 $deviationHeight  $Double     $D_Spinbox	$100   	$贴膜高度偏差     $当测量值在【标注值-偏差，标准值+偏差】为ok $40");
		msgs.push_back("0 $deviationWidth   $Double     $D_Spinbox	$100   	$贴膜宽度偏差     $当测量值在【标注值-偏差，标准值+偏差】为ok $50");
		msgs.push_back("0 $minDisflag       $Int        $Combox     $0      $测量偏位评测     $选择测量的偏位类型  ￥最近距离￥平均距离 $15");

	}
};
//class AlgFilmDetect : public AlgProcessInterface
//{
//public:
//	AlgFilmDetect() {}
//	//1、获取流程参数 
//	//输入/输出：参数信息
//	void getProcessAlgInfo(AlgProcessInfo *_processInfo);
//	//2、是否参数共享
//	void setSharedFlag(bool _share);
//	//2、初始化
//	ErrMsg setProcessParm(const vector<cv::Mat> *_vMats,//原图
//		vector<AlgProcessInfo> *_processInfo);
//	//3、创建模型
//	ErrMsg createAlgModel(const cv::Mat &_Mat, const SingleAlgInfo *_single);
//	//4、执行
//	ErrMsg goExe(const vector<cv::Mat> *_vMats,//输入原图:正常--16个
//		const SingleAlgInfo *_single,                 //输入控制指令--调试每次输入一个；
//		int  _imgIndex,//单个图像流程;正常--- -1；
//		bool  _debug,//是否调试 :正常---false；
//		vector<AlgOutInfo> *_outInfo);//流程输出结果信息
//	//5-获取工程路径
//	void setDataPath(const string &_path);
//	//6、获取版本
//	string getVision(int *_vision);
//	//7、贴膜识别算子
//	//0-输入参数 1-输出参数
//   //功能：根据模板图的轮廓信息进行匹配，输出待测图匹配后的轮廓信息以及转换矩阵
//	ErrMsg recognitionFilm(const RecognitionInput &input, RecognitionOutput &output);
//	//8、获取直线算子
//	//功能：获取贴膜工位的直线以及盖板边缘的直线
//	ErrMsg getLine(const GetLineInput &input, GetLineOutput &output);
//	//9、测量偏位算子
//	ErrMsg measureDeviation(const MeasureInput &input, MeasureOutput &output);
//
//private:
//	vector<cv::Mat> matchImg;                              //模板小图
//	vector<vector<vector<cv::Point2f>>> matchContours;     //模板小图轮廓信息相对于原始降采样的图
//	vector<vector<vector<float>>> grad;                            //存储每个轮廓点的梯度信息
//	vector<vector<vector<float>>> matchDir;                //模板小图轮廓的梯度信息
//	vector<cv::Point> matchLeftTop;                        //模板小图在原始大图的左上角点信息
//	vector<cv::Point2f> matchCenter;                       //模板小图的轮廓中心 相对于降采样后的图
//	vector<float> matchGrad;                               //模板轮廓的梯度数值，用于与待测相比
//	vector<float> meanGrad;                                //平均梯度值
//	string   projectPath;
//	//存储中间算子的输出结果，用于在调试阶段直接调用
//	vector<TransformMatrix> transformMatrix;               //贴膜识别算子输出的转换关系 作为获取直线的输入
//	vector<vector<LineStruct>> lineOutput;                 //拟合直线算子的输出结果
//	
//};
struct RectangleROI             //扫描矩形     
{
	int indexROI;                 // ROI编号
	cv::Point2f        pt1;
	cv::Point2f        pt2;
	float          offset;      //以pt1、pt2为轴线，向该轴线两侧法线方向的扩展偏移量
	int   direction;           //directionFlag 为正，表示沿着pt1 pt2的方向的顺时针方向扫描，为0则是逆时针方向扫描
};

struct GatherEdgePtsOutput
{
	vector < cv:: Point2f > imgPts;//获取的轮廓点
};
struct GatherLineInput
{
	vector < cv:: Point2f > edgePts;                   //轮廓点
	int indexROI;                             //直线编号
	//AlgrithmParams algPara;                    //算法参数
};
struct GatherLineOutput
{
	LineStruct fitLine;
};
struct MeasureL2LInuput
{
	LineStruct line1;
	LineStruct line2;
};
struct MeasureL2LOutput
{
	float distance;
};
//------------------------step0 贴膜识别-----------------------//
//0-模板小图 1-算子参数 2-模板小图相对于左上角点 3-模板轮廓 4-模板轮廓对应的梯度方向 5-轮廓点梯度值 6-梯度和 7-中心点
//ErrMsg getTemplateContour(const cv::Mat &templateImg, const AlgParamsRecognitionConfig &alg, cv::Point leftTop, vector<vector<cv::Point2f>> &templateContour, vector<vector<float>> &templateDir,vector<vector<float>> &grad, float &meanGrad,float &matchGrad, cv::Point2f &centerPt);//返回轮廓点集的梯度数值
//0-待测图 1-模板梯度均值 2-梯度阈值 3-当前点 4-外轮廓点 5-内轮廓点 6-满足条件的轮廓点个数  返回值待测的梯度总和
//float getGradSumofEdgeEle(const cv::Mat &srcImg, const float &meanGrad, const float &disGrad,const cv::Point2f &current,vector<cv::Point2f> &edgesOut, vector<cv::Point2f> &edgesIn,int &countNum);
//轮廓匹配
//0-模板轮廓 1-模板轮廓中心点 1- 参数 2-待测图 3-偏移量 4-旋转角 5-梯度 6-模板轮廓中心
//void matchContourGrad(const vector<vector<cv::Point2f>> &matchContour, const cv::Point2f &centerPt, const vector<vector<float>> &matchDir, const float meanGrad,const AlgParamsRecognitionConfig &alg, const cv::Mat &sampleimg, vector<cv::Point2f> &translate, vector<float> &rotatetheta, vector<float> &gradAllPts,vector<int> &countNumGrad);
//0-模板轮廓 1-模板轮廓中心点 2-模板图的方向 3-置信度值 4-偏移量 5-转换角度 6-相似度
//void matchContourGrad(const vector<vector<cv::Point2f>> &matchContour, const cv::Point2f &centerPt, const vector<vector<float>> &matchDir, const AlgParamsRecognitionConfig &alg, const cv::Mat &sampleimg, vector<cv::Point2f> &translate, vector<float> &rotatetheta, vector <float> &countNumGrad);
//求模板梯度方向和待测的相似度
//0-待测图的梯度方向图像 1-平移量 2-模板轮廓点 3-模板梯度方向 4-相似性
//void getGradSumofEdgeEle(const cv::Mat &srcImg, const cv::Point2f &current, vector<cv::Point2f> &edgesOut, vector<float> &matchDir, float &correctVal);

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
