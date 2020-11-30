
// MFCApplication3Dlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "MFCApplication3.h"
#include "MFCApplication3Dlg.h"
#include "afxdialogex.h"
#include "MyFunction.h"
//#include "FastMatchForLineParam.h"
#include "resource.h"
#include<stdio.h>
#include <fstream>
#include <cstdlib>
#include "MyGLobal.h"
#include <string>


using namespace std;


//int factor = 5;


float pointWorldSet[4][9] = {
	  -3,   0,   3,   3,   0,   -3,   -3,   0,   3,
	   3,   3,   3,   0,   0,    0,  -3,  -3,  -3,
	   0,   0,   0,   0,   0,    0,   0,   0,   0,
	   1,   1,   1,   1,   1,    1,   1,   1,   1
};


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMFCApplication3Dlg 对话框



CMFCApplication3Dlg::CMFCApplication3Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCAPPLICATION3_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCApplication3Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, InstructionCommandList);
	//DDX_Control(pDX, IDC_LIST3, ErrorList);
	DDX_Control(pDX, IDC_LIST2, RectifyInstructionCommand);
	//  DDX_Control(pDX, IDC_LIST4, RectifyErrorList);
	//DDX_Control(pDX, IDC_LIST4, RectifyErrorList);
	DDX_Control(pDX, IDC_LIST3, RotatePointList1);
	DDX_Control(pDX, IDC_LIST4, RotatePointList2);
	DDX_Control(pDX, IDC_Threshold, m_threshold);
	DDX_Control(pDX, IDC_erodeSize, m_erodeSize);
	DDX_Control(pDX, IDC_Canny1, m_cannt1);
	DDX_Control(pDX, IDC_Canny2, m_canny2);
	DDX_Control(pDX, IDC_Hough1, m_hough1);
	DDX_Control(pDX, IDC_Hough2, m_hough2);
	DDX_Control(pDX, IDC_Hough3, m_hough3);
}

BEGIN_MESSAGE_MAP(CMFCApplication3Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CMFCApplication3Dlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON3, &CMFCApplication3Dlg::OnBnClickedButton3)
	ON_STN_CLICKED(PictureViewer2, &CMFCApplication3Dlg::OnStnClickedPictureviewer2)
	ON_BN_CLICKED(IDC_BUTTON4, &CMFCApplication3Dlg::OnBnClickedButton4)
	ON_BN_CLICKED(ID_testImageL, &CMFCApplication3Dlg::OnBnClickedtestimagel)
	ON_BN_CLICKED(ID_testImageR, &CMFCApplication3Dlg::OnBnClickedtestimager)
	ON_BN_CLICKED(ID_bmImageL, &CMFCApplication3Dlg::OnBnClickedbmimagel)
	ON_BN_CLICKED(ID_bmImageR, &CMFCApplication3Dlg::OnBnClickedbmimager)
	ON_BN_CLICKED(ID_ALignment_WO, &CMFCApplication3Dlg::OnBnClickedAlignmentWo)
	ON_BN_CLICKED(CameraCalibation, &CMFCApplication3Dlg::OnBnClickedCameracalibation)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST3, &CMFCApplication3Dlg::OnLvnItemchangedList3)
	//ON_BN_CLICKED(ID_RectifyRotateCenter, &CMFCApplication3Dlg::OnBnClickedRectifyrotatecenter)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST1, &CMFCApplication3Dlg::OnLvnItemchangedList1)
	//ON_BN_CLICKED(IDC_RectifyImageL, &CMFCApplication3Dlg::OnBnClickedRectifyimagel)
	//ON_BN_CLICKED(IDC_RectifyImageR, &CMFCApplication3Dlg::OnBnClickedRectifyimager)
	ON_BN_CLICKED(IDC_BUTTON6, &CMFCApplication3Dlg::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON1, &CMFCApplication3Dlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON5, &CMFCApplication3Dlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON7, &CMFCApplication3Dlg::OnBnClickedButton7)
	//ON_STN_CLICKED(RectifyImageViewR, &CMFCApplication3Dlg::OnStnClickedRectifyimageviewr)
	ON_BN_CLICKED(IDC_BUTTON8, &CMFCApplication3Dlg::OnBnClickedButton8)
	ON_BN_CLICKED(IDC_BUTTON9, &CMFCApplication3Dlg::OnBnClickedButton9)
	ON_BN_CLICKED(IDC_BUTTON10, &CMFCApplication3Dlg::OnBnClickedButton10)
	ON_BN_CLICKED(IDC_ResultImageL, &CMFCApplication3Dlg::OnBnClickedResultimagel)
	ON_BN_CLICKED(IDC_ResultImageR, &CMFCApplication3Dlg::OnBnClickedResultimager)
	ON_BN_CLICKED(IDC_BUTTON11, &CMFCApplication3Dlg::OnBnClickedButton11)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST4, &CMFCApplication3Dlg::OnLvnItemchangedList4)
	ON_EN_CHANGE(IDC_Canny1, &CMFCApplication3Dlg::OnEnChangeCanny1)
	ON_EN_CHANGE(IDC_Hough1, &CMFCApplication3Dlg::OnEnChangeHough1)
	ON_EN_CHANGE(IDC_Threshold, &CMFCApplication3Dlg::OnEnChangeThreshold)
	ON_EN_CHANGE(IDC_erodeSize, &CMFCApplication3Dlg::OnEnChangeerodesize)
	ON_EN_CHANGE(IDC_Hough3, &CMFCApplication3Dlg::OnEnChangeHough3)
	ON_EN_CHANGE(IDC_Hough2, &CMFCApplication3Dlg::OnEnChangeHough2)
	ON_EN_CHANGE(IDC_HoughCircle, &CMFCApplication3Dlg::OnEnChangeHoughcircle)
END_MESSAGE_MAP()


// CMFCApplication3Dlg 消息处理程序

BOOL CMFCApplication3Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	//namedWindow("view1", WINDOW_AUTOSIZE);
	//HWND hWnd = (HWND)cvGetWindowHandle("view1");
	//HWND hParent = ::GetParent(hWnd);
	//::SetParent(hWnd, GetDlgItem(PictureViewer1)->m_hWnd);
	//::ShowWindow(hParent, SW_HIDE);

	//namedWindow("view2", WINDOW_AUTOSIZE);
	//HWND hWnd2 = (HWND)cvGetWindowHandle("view2");
	//HWND hParent2 = ::GetParent(hWnd2);
	//::SetParent(hWnd2, GetDlgItem(PictureViewer2)->m_hWnd);
	//::ShowWindow(hParent2, SW_HIDE);

	namedWindow("view3", WINDOW_AUTOSIZE);
	HWND hWnd3 = (HWND)cvGetWindowHandle("view3");
	HWND hParent3 = ::GetParent(hWnd3);
	::SetParent(hWnd3, GetDlgItem(testImageViewL)->m_hWnd);
	::ShowWindow(hParent3, SW_HIDE);

	namedWindow("view4", WINDOW_AUTOSIZE);
	HWND hWnd4 = (HWND)cvGetWindowHandle("view4");
	HWND hParent4 = ::GetParent(hWnd4);
	::SetParent(hWnd4, GetDlgItem(testImageViewR)->m_hWnd);
	::ShowWindow(hParent4, SW_HIDE);

	namedWindow("view5", WINDOW_AUTOSIZE);
	HWND hWnd5 = (HWND)cvGetWindowHandle("view5");
	HWND hParent5 = ::GetParent(hWnd5);
	::SetParent(hWnd5, GetDlgItem(bmImageViewL)->m_hWnd);
	::ShowWindow(hParent5, SW_HIDE);

	namedWindow("view6", WINDOW_AUTOSIZE);
	HWND hWnd6 = (HWND)cvGetWindowHandle("view6");
	HWND hParent6 = ::GetParent(hWnd6);
	::SetParent(hWnd6, GetDlgItem(bmImageViewR)->m_hWnd);
	::ShowWindow(hParent6, SW_HIDE);

	//namedWindow("view7", WINDOW_AUTOSIZE);
	//HWND hWnd7 = (HWND)cvGetWindowHandle("view7");
	//HWND hParent7 = ::GetParent(hWnd7);
	//::SetParent(hWnd7, GetDlgItem(ResultImageViewL)->m_hWnd);
	//::ShowWindow(hParent7, SW_HIDE);
	//namedWindow("view8", WINDOW_AUTOSIZE);
	//HWND hWnd8 = (HWND)cvGetWindowHandle("view8");
	//HWND hParent8 = ::GetParent(hWnd8);
	//::SetParent(hWnd8, GetDlgItem(ResultImageViewR)->m_hWnd);
	//::ShowWindow(hParent8, SW_HIDE);
	//namedWindow("view9", WINDOW_AUTOSIZE);
	//HWND hWnd9 = (HWND)cvGetWindowHandle("view9");
	//HWND hParent9 = ::GetParent(hWnd9);
	//::SetParent(hWnd9, GetDlgItem(secTestViewL)->m_hWnd);
	//::ShowWindow(hParent9, SW_HIDE);
	//namedWindow("view10", WINDOW_AUTOSIZE);
	//HWND hWnd10 = (HWND)cvGetWindowHandle("view10");
	//HWND hParent10 = ::GetParent(hWnd10);
	//::SetParent(hWnd10, GetDlgItem(secTestViewR)->m_hWnd);
	//::ShowWindow(hParent10, SW_HIDE);
	//namedWindow("view11", WINDOW_AUTOSIZE);
	//HWND hWnd11 = (HWND)cvGetWindowHandle("view11");
	//HWND hParent11 = ::GetParent(hWnd11);
	//::SetParent(hWnd11, GetDlgItem(secResultViewL)->m_hWnd);
	//::ShowWindow(hParent11, SW_HIDE);
	//namedWindow("view12", WINDOW_AUTOSIZE);
	//HWND hWnd12 = (HWND)cvGetWindowHandle("view12");
	//HWND hParent12 = ::GetParent(hWnd12);
	//::SetParent(hWnd12, GetDlgItem(secResultViewR)->m_hWnd);
	//::ShowWindow(hParent12, SW_HIDE);

	CString str1[] = { TEXT("RotateX"),TEXT("RotateY"),TEXT("X"),TEXT("Y"),TEXT("Theta") };
	CString str2[] = {TEXT("X(mm)"),TEXT("Y(mm)"),TEXT("Theta(°)") };
	InstructionCommandList.InsertColumn(0, TEXT("序号"), LVCFMT_CENTER, 60);
	RectifyInstructionCommand.InsertColumn(0, TEXT("序号"), LVCFMT_CENTER, 60);
	for (int i = 1; i < 4; i++)
	{
		InstructionCommandList.InsertColumn(i, str2[i-1], LVCFMT_CENTER, 80);
		RectifyInstructionCommand.InsertColumn(i, str2[i-1], LVCFMT_CENTER, 80);
	}

	for (int i = 0; i < 100; i++)
	{
		CString iToText;
		iToText.Format(TEXT("%d"), 100 - i);
		InstructionCommandList.InsertItem(0, iToText);
		RectifyInstructionCommand.InsertItem(0, iToText);
	}

	RotatePointList1.InsertColumn(0, TEXT("RotateY"), LVCFMT_CENTER, 80);
	RotatePointList1.InsertColumn(0, TEXT("RotateX"), LVCFMT_CENTER, 80);
	RotatePointList2.InsertColumn(0, TEXT("RotateY"), LVCFMT_CENTER, 80);
	RotatePointList2.InsertColumn(0, TEXT("RotateX"), LVCFMT_CENTER, 80);

	CString strThreshold, strErodeSize, strCanny1, strCanny2,
		strHough1, strHough2, strHough3, strHoughCircleRadius;
	GetDlgItemText(IDC_Threshold, strThreshold);
	GetDlgItemText(IDC_erodeSize, strErodeSize);
	GetDlgItemText(IDC_Canny1, strCanny1);
	GetDlgItemText(IDC_Canny2, strCanny2);
	GetDlgItemText(IDC_Hough1, strHough1);
	GetDlgItemText(IDC_Hough2, strHough2);
	GetDlgItemText(IDC_Hough3, strHough3);
	GetDlgItemText(IDC_HoughCircle, strHoughCircleRadius);

	m_threshold.SetWindowTextW(TEXT("15"));
	m_erodeSize.SetWindowTextW(TEXT("3"));
	m_cannt1.SetWindowTextW(TEXT("150"));
	m_canny2.SetWindowTextW(TEXT("200"));
	m_hough1.SetWindowTextW(TEXT("150"));
	m_hough2.SetWindowTextW(TEXT("150"));
	m_hough3.SetWindowTextW(TEXT("50"));

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMFCApplication3Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMFCApplication3Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMFCApplication3Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCApplication3Dlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnOK();
}


void CMFCApplication3Dlg::ShowPic_MaskL(Mat input_1)
{
	Mat imagedst;
	CRect rect1;
	GetDlgItem(PictureViewer1)->GetClientRect(&rect1);
	Rect dst1(rect1.left, rect1.top, rect1.right, rect1.bottom);
	resize(input_1, imagedst, cv::Size(rect1.Width(), rect1.Height()));
	imshow("view1", imagedst);
}

void CMFCApplication3Dlg::ShowPic_MaskR(Mat input_2)
{
	Mat imagedst;
	CRect rect2;
	GetDlgItem(PictureViewer2)->GetClientRect(&rect2);
	Rect dst2(rect2.left, rect2.top, rect2.right, rect2.bottom);
	resize(input_2, imagedst, cv::Size(rect2.Width(), rect2.Height()));
	imshow("view2", imagedst);
}

void CMFCApplication3Dlg::ShowPic_testImageL(Mat input)
{
	Mat imagedst;
	CRect rect2;
	GetDlgItem(testImageViewL)->GetClientRect(&rect2);
	Rect dst2(rect2.left, rect2.top, rect2.right, rect2.bottom);
	resize(input, imagedst, cv::Size(rect2.Width(), rect2.Height()));
	imshow("view3", imagedst);
}
void CMFCApplication3Dlg::ShowPic_testImageR(Mat input)
{
	Mat imagedst;
	CRect rect2;
	GetDlgItem(testImageViewR)->GetClientRect(&rect2);
	Rect dst2(rect2.left, rect2.top, rect2.right, rect2.bottom);
	resize(input, imagedst, cv::Size(rect2.Width(), rect2.Height()));
	imshow("view4", imagedst);
}

void CMFCApplication3Dlg::ShowPic_bmImageViweL(Mat input)
{
	Mat imagedst;
	CRect rect2;
	GetDlgItem(bmImageViewL)->GetClientRect(&rect2);
	Rect dst2(rect2.left, rect2.top, rect2.right, rect2.bottom);
	resize(input, imagedst, cv::Size(rect2.Width(), rect2.Height()));
	imshow("view5", imagedst);
}

void CMFCApplication3Dlg::ShowPic_bmImageViweR(Mat input)
{
	Mat imagedst;
	CRect rect2;
	GetDlgItem(bmImageViewL)->GetClientRect(&rect2);
	Rect dst2(rect2.left, rect2.top, rect2.right, rect2.bottom);
	resize(input, imagedst, cv::Size(rect2.Width(), rect2.Height()));
	imshow("view6", imagedst);
}

//void CMFCApplication3Dlg::ShowPic_RectifyImageViewL(Mat input)
//{
//	Mat imagedst;
//	CRect rect2;
//	GetDlgItem(RectifyImageViewL)->GetClientRect(&rect2);
//	Rect dst2(rect2.left, rect2.top, rect2.right, rect2.bottom);
//	resize(input, imagedst, cv::Size(rect2.Width(), rect2.Height()));
//	imshow("view7", imagedst);
//}


void CMFCApplication3Dlg::ShowPic_resultImageViweL(Mat input)
{
	Mat imagedst;
	CRect rect2;
	GetDlgItem(ResultImageViewL)->GetClientRect(&rect2);
	Rect dst2(rect2.left, rect2.top, rect2.right, rect2.bottom);
	resize(input, imagedst, cv::Size(rect2.Width(), rect2.Height()));
	imshow("view7", imagedst);
}
//void CMFCApplication3Dlg::ShowPic_RectifyImageViewR(Mat input)
//{
//	Mat imagedst;
//	CRect rect2;
//	GetDlgItem(RectifyImageViewR)->GetClientRect(&rect2);
//	Rect dst2(rect2.left, rect2.top, rect2.right, rect2.bottom);
//	resize(input, imagedst, cv::Size(rect2.Width(), rect2.Height()));
//	imshow("view8", imagedst);
//}

void CMFCApplication3Dlg::ShowPic_resultImageViweR(Mat input)
{
	Mat imagedst;
	CRect rect2;
	GetDlgItem(ResultImageViewR)->GetClientRect(&rect2);
	Rect dst2(rect2.left, rect2.top, rect2.right, rect2.bottom);
	resize(input, imagedst, cv::Size(rect2.Width(), rect2.Height()));
	imshow("view8", imagedst);
}

void CMFCApplication3Dlg::ShowPic_secTestViewL(Mat input) {
	Mat imagedst;
	CRect rect2;
	GetDlgItem(secTestViewL)->GetClientRect(&rect2);
	Rect dst2(rect2.left, rect2.top, rect2.right, rect2.bottom);
	resize(input, imagedst, cv::Size(rect2.Width(), rect2.Height()));
	imshow("view9", imagedst);
}

void CMFCApplication3Dlg::ShowPic_secTestViewR(Mat input) {
	Mat imagedst;
	CRect rect2;
	GetDlgItem(secTestViewR)->GetClientRect(&rect2);
	Rect dst2(rect2.left, rect2.top, rect2.right, rect2.bottom);
	resize(input, imagedst, cv::Size(rect2.Width(), rect2.Height()));
	imshow("view10", imagedst);
}


void CMFCApplication3Dlg::ShowPic_secResultViewL(Mat input) {
	Mat imagedst;
	CRect rect2;
	GetDlgItem(secResultViewL)->GetClientRect(&rect2);
	Rect dst2(rect2.left, rect2.top, rect2.right, rect2.bottom);
	resize(input, imagedst, cv::Size(rect2.Width(), rect2.Height()));
	imshow("view11", imagedst);
}


void CMFCApplication3Dlg::ShowPic_secResultViewR(Mat input) {
	Mat imagedst;
	CRect rect2;
	GetDlgItem(secResultViewR)->GetClientRect(&rect2);
	Rect dst2(rect2.left, rect2.top, rect2.right, rect2.bottom);
	resize(input, imagedst, cv::Size(rect2.Width(), rect2.Height()));
	imshow("view12", imagedst);
}


void CMFCApplication3Dlg::OnBnClickedButton3()
{
	CString strThreshold, strErodeSize, strCanny1, strCanny2,
		strHough1, strHough2, strHough3, strHoughCircleRadius;

	GetDlgItemText(IDC_Threshold, strThreshold);
	GetDlgItemText(IDC_erodeSize, strErodeSize);
	GetDlgItemText(IDC_Canny1, strCanny1);
	GetDlgItemText(IDC_Canny2, strCanny2);
	GetDlgItemText(IDC_Hough1, strHough1);
	GetDlgItemText(IDC_Hough2, strHough2);
	GetDlgItemText(IDC_Hough3, strHough3);
	GetDlgItemText(IDC_HoughCircle, strHoughCircleRadius);

	vector<CString>parameters;
	parameters.push_back(strCanny1);
	parameters.push_back(strCanny2);
	parameters.push_back(strHough1);
	parameters.push_back(strHough2);
	parameters.push_back(strHough3);
	parameters.push_back(strThreshold);
	parameters.push_back(strErodeSize);
	parameters.push_back(strHoughCircleRadius);

	vector<double>parametersValue;

	for (int i = 0; i < parameters.size(); i++)
	{
		const size_t strsize = (parameters[i].GetLength() + 1) * 2; // 宽字符的长度;
		char * pstr = new char[strsize]; //分配空间;
		size_t sz = 0;
		wcstombs_s(&sz, pstr, strsize, parameters[i], _TRUNCATE);
		double ans = atof((const char*)pstr); // 字符串已经由原来的CString 转换成了 const char*
		parametersValue.push_back(ans);
	}

	CannyThreshold1 = parametersValue[0];
	CannyThreshold2 = parametersValue[1];
	HoughThreshold1 = parametersValue[2];
	HoughThreshold2 = parametersValue[3];
	HoughThreshold3 = parametersValue[4];
	thresholdValue = parametersValue[5];
	erodeSize = (int)(parametersValue[6]);

	//double d = atof(str);
	cout << "pause here" << endl;
}


void CMFCApplication3Dlg::OnStnClickedPictureviewer1()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CMFCApplication3Dlg::OnStnClickedPictureviewer2()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CMFCApplication3Dlg::OnBnClickedButton4()
{
	//Mat maskImage = imread("F:\\数据集\\对位\\3号台圆弧盖板图像\\对位2\\F01-20201114223512-1.jpeg", 0);
	//Mat srcImage = imread("F:\\数据集\\对位\\3号台圆弧盖板图像\\对位2\\F01-20201114223512-1.jpeg", 0);

	/*计算单相机的平移标定角点的图像像素坐标*/
	maskImageL = imread("F:\\数据集\\对位\\3号台圆弧盖板图像\\maskImageL.bmp", 0);
	maskImageR = imread("F:\\数据集\\对位\\3号台圆弧盖板图像\\maskImageR.bmp", 0);

	char srcImagePathL[500], srcImagePathR[500];
	CString srcPathL, srcPathR;
	Mat srcImageRectL, srcImageRectR;
	Rect rectL, rectR;
	float pointTransSetL[3][9], pointTransSetR[3][9];//角点图像像素坐标
	for (int index = 3; index < 10; index++)
	{
		sprintf_s(srcImagePathL, "E:\\数据集\\后盖标定采图\\L\\T-L-%d.bmp", index);
		sprintf_s(srcImagePathR, "E:\\数据集\\后盖标定采图\\R\\T-R-%d.bmp", index);


		//Mat srcImageL = imread(srcImagePathL, 0);
		Mat srcImageR = imread(srcImagePathR, 0);

#if CrossMethod==1
		Point2f resultPointL = GetCrossPointL(srcImageL, thresholdValue, erodeSize,
			circleRadiusMax, deltaRadius, CannyThreshold1, CannyThreshold2,
			HoughThreshold1, HoughThreshold2, HoughThreshold3);
		Point2f resultPointR = GetCrossPointR(srcImageR, CannyThreshold1, CannyThreshold2,
			HoughThreshold1, HoughThreshold2, HoughThreshold3);
#elif CrossMethod == 2
		Point2f resultPointL = GetCrossBasedShapeL(srcImageL, maskImageL);
		Point2f resultPointR = GetCrossBasedShapeR(srcImageR, maskImageR);
#elif CrossMethod == 3
		//Point2f resultPointL = GetCrossBasedFastShapeL(srcImageL, maskImageL, 255, 1500, srcImagePathL);
		Point2f resultPointR = GetCrossBasedFastShapeR(srcImageR, maskImageR, 255, 1500, srcImagePathR);
#endif
	}

	cout << "pause here." << endl;
}


void CMFCApplication3Dlg::OnBnClickedtestimagel()
{
	//打开文件 定义四种格式的文件bmp gif jpg tiff
	CString m_strFilePath = _T("");

	//打开图像文件，获取文件路径名
	LPCTSTR szFilter = _T("ALLSUPORTFILE(*.*)|*.*|JPG(*.jpg)|*.jpg|BMP(*.bmp)|*.bmp||");
	CFileDialog dlgFileOpenImg(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter, NULL);
	
	//打开图像
	if (dlgFileOpenImg.DoModal() == IDOK)
	{
		//读取图像文件名
		m_strFilePath = dlgFileOpenImg.GetPathName();
	}
	else
	{
		return;
	}

	USES_CONVERSION;
	string str(W2A(m_strFilePath));
	testImageL = imread(str, 0);
	ShowPic_testImageL(testImageL);

}


void CMFCApplication3Dlg::OnBnClickedtestimager()
{
	//打开文件 定义四种格式的文件bmp gif jpg tiff
	CString m_strFilePath = _T("");

	//打开图像文件，获取文件路径名
	LPCTSTR szFilter = _T("ALLSUPORTFILE(*.*)|*.*|JPG(*.jpg)|*.jpg|BMP(*.bmp)|*.bmp||");
	CFileDialog dlgFileOpenImg(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter, NULL);
	//打开图像
	if (dlgFileOpenImg.DoModal() == IDOK)
	{
		//读取图像文件名
		m_strFilePath = dlgFileOpenImg.GetPathName();
	}
	else
	{
		return;
	}

	USES_CONVERSION;
	string str(W2A(m_strFilePath));
	testImageR = imread(str, 0);
	ShowPic_testImageR(testImageR);
}


void CMFCApplication3Dlg::OnBnClickedbmimagel()
{
	// TODO: 在此添加控件通知处理程序代码
		//打开文件 定义四种格式的文件bmp gif jpg tiff
	CString m_strFilePath = _T("");

	//打开图像文件，获取文件路径名
	LPCTSTR szFilter = _T("ALLSUPORTFILE(*.*)|*.*|JPG(*.jpg)|*.jpg|BMP(*.bmp)|*.bmp||");
	CFileDialog dlgFileOpenImg(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter, NULL);
	//打开图像
	if (dlgFileOpenImg.DoModal() == IDOK)
	{
		//读取图像文件名
		m_strFilePath = dlgFileOpenImg.GetPathName();
	}
	else
	{
		return;
	}

	USES_CONVERSION;
	string str(W2A(m_strFilePath));
	bmImageL = imread(str, 0);

	//Rect maskLRegion1 = Rect(2650, 1284,  3791- 2650, 1563 - 1284);
	//Mat maskLResult1;
	//bmImageL(maskLRegion1).copyTo(maskLResult1);
	//imwrite("F:\\数据集\\标定\\标定B\\maskL1.bmp", maskLResult1);

	//Rect maskLRegion2 = Rect(1600, 2280, 2060 - 1600, 2683 - 2280);
	//Mat maskLResult2;
	//bmImageL(maskLRegion2).copyTo(maskLResult2);
	//imwrite("F:\\数据集\\标定\\标定B\\maskL2.bmp", maskLResult2);

	ShowPic_bmImageViweL(bmImageL);
}


void CMFCApplication3Dlg::OnBnClickedbmimager()
{
	// TODO: 在此添加控件通知处理程序代码
		//打开文件 定义四种格式的文件bmp gif jpg tiff
	CString m_strFilePath = _T("");

	//打开图像文件，获取文件路径名
	LPCTSTR szFilter = _T("ALLSUPORTFILE(*.*)|*.*|JPG(*.jpg)|*.jpg|BMP(*.bmp)|*.bmp||");
	CFileDialog dlgFileOpenImg(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter, NULL);
	//打开图像
	if (dlgFileOpenImg.DoModal() == IDOK)
	{
		//读取图像文件名
		m_strFilePath = dlgFileOpenImg.GetPathName();
	}
	else
	{
		return;
	}

	USES_CONVERSION;
	string str(W2A(m_strFilePath));
	bmImageR = imread(str, 0);

	//Rect maskLRegion1 = Rect(77, 1081, 1771 - 77, 1564 - 1081);
	//Mat maskResult1;
	//bmImageR(maskLRegion1).copyTo(maskResult1);
	//imwrite("F:\\数据集\\标定\\标定B\\maskR1.bmp", maskResult1);

	//Rect maskLRegion2 = Rect(2234, 2207, 2633 - 2234, 2701 - 2207);
	//Mat maskResult2;
	//bmImageR(maskLRegion2).copyTo(maskResult2);
	//imwrite("F:\\数据集\\标定\\标定B\\maskR2.bmp", maskResult2);

	ShowPic_bmImageViweR(bmImageR);
}



float CalThetaR(Mat&srcImage, double CannyThreshold1, double CannyThreshold2,
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
	float epsilon = 0.001;
	for (size_t i = 0; i < lines.size(); i++) {
		Vec4f l = lines[i];
		//line(dstImage, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(255), 3, LINE_AA);
		if (abs((l[3] - l[1]) / (l[2] - l[0] + epsilon)) > 5)
		{
			line(dstImage, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(255), 3, LINE_AA);				line(srcImageRGB, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0, 0, 255), 3, LINE_AA);
			line(srcImageRGB, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0, 0, 255), 3, LINE_AA);

			linePointY.push_back(Point(l[0], l[1]));
			linePointY.push_back(Point(l[2], l[3]));
		}
		else if (abs((l[3] - l[1]) / (l[2] - l[0] + epsilon)) < 0.1)
		{
			line(dstImage, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(255), 3, LINE_AA);				line(srcImageRGB, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0, 0, 255), 3, LINE_AA);
			line(srcImageRGB, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0, 0, 255), 3, LINE_AA);

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

	float theta = atan(ka);

	return theta;
}


ControlInstruction GetInstruction2(Mat& bmImageL,Mat& testImageL,
	Position& bmPosition, Position& testPosition, Point2f& rotatePoint)
{
	/*计算待测工件移动至基准位置需要移动的偏移量和旋转量*/
	ControlInstruction instruction;

	//计算旋转量alpha
	Point2f uniformCrossPointL = bmPosition.uniformCrossPointL;
	Point2f uniformCrossPointR = bmPosition.uniformCrossPointR;
	Point2f uniformCenterPoint = bmPosition.uniformCenterPoint;

	Point2f uniformTestCrossPointL = testPosition.uniformCrossPointL;
	Point2f uniformTestCrossPointR = testPosition.uniformCrossPointR;
	Point2f uniformTestCenterPoint = testPosition.uniformCenterPoint;

	//float thetaL1 = CalThetaL(bmImageL, 100, 3, 200, 350,
	//	100, 200, 100, 100, 50);
	//float thetaL2 = CalThetaL(testImageL, 100, 3, 200, 350,
	//	100, 200, 100, 100, 50);
	//float ansThetaL = thetaL1 - thetaL2;
	//instruction.commandTheta = ansThetaL;
	instruction.commandTheta = bmPosition.theta - testPosition.theta;

	//计算偏移量
	//float uTCRotatePointLX = cos(instruction.commandTheta)*(uniformTestCrossPointL.x - rotatePoint.x) -
	//	sin(instruction.commandTheta)*(uniformTestCrossPointL.y - rotatePoint.y) + rotatePoint.x;
	//float uTCRotatePointLY = sin(instruction.commandTheta)*(uniformTestCrossPointL.x - rotatePoint.x) +
	//	cos(instruction.commandTheta)*(uniformTestCrossPointL.y - rotatePoint.y) + rotatePoint.y;
	//float uTCRotatePointRX = cos(instruction.commandTheta)*(uniformTestCrossPointR.x - rotatePoint.x) -
	//	sin(instruction.commandTheta)*(uniformTestCrossPointR.y - rotatePoint.y) + rotatePoint.x;
	//float uTCRotatePointRY = sin(instruction.commandTheta)*(uniformTestCrossPointR.x - rotatePoint.x) +
	//	cos(instruction.commandTheta)*(uniformTestCrossPointR.y - rotatePoint.y) + rotatePoint.y;
	//float uTCRotatePointCenterX = cos(instruction.commandTheta)*(uniformTestCenterPoint.x - rotatePoint.x) -
	//	sin(instruction.commandTheta)*(uniformTestCenterPoint.y - rotatePoint.y) + rotatePoint.x;
	//float uTCRotatePointCenterY = sin(instruction.commandTheta)*(uniformTestCenterPoint.x - rotatePoint.x) +
	//	cos(instruction.commandTheta)*(uniformTestCenterPoint.y - rotatePoint.y) + rotatePoint.y;

	float uTCRotatePointLX = cos(instruction.commandTheta)*(uniformTestCrossPointL.x ) -
		sin(instruction.commandTheta)*(uniformTestCrossPointL.y );
	float uTCRotatePointLY = sin(instruction.commandTheta)*(uniformTestCrossPointL.x ) +
		cos(instruction.commandTheta)*(uniformTestCrossPointL.y) ;

	float uTCRotatePointRX = cos(instruction.commandTheta)*(uniformTestCrossPointR.x) -
		sin(instruction.commandTheta)*(uniformTestCrossPointR.y);
	float uTCRotatePointRY = sin(instruction.commandTheta)*(uniformTestCrossPointR.x) +
		cos(instruction.commandTheta)*(uniformTestCrossPointR.y);

	float uTCRotatePointCenterX = cos(instruction.commandTheta)*(uniformTestCenterPoint.x) -
		sin(instruction.commandTheta)*(uniformTestCenterPoint.y);
	float uTCRotatePointCenterY = sin(instruction.commandTheta)*(uniformTestCenterPoint.x) +
		cos(instruction.commandTheta)*(uniformTestCenterPoint.y);

	//旋转校正之后的中心点坐标
	Point2f testRotatePoint = Point2f(uTCRotatePointCenterX, uTCRotatePointCenterY);

	float commandX1, commandX2, commandX3;
	float commandY1, commandY2, commandY3;

	commandX1 = -uTCRotatePointLX + uniformCrossPointL.x;
	commandY1 = -uTCRotatePointLY + uniformCrossPointL.y;

	commandX2 = -uTCRotatePointCenterX + uniformCenterPoint.x;
	commandY2 = -uTCRotatePointCenterY + uniformCenterPoint.y;

	commandX3 = -uTCRotatePointRX + uniformCrossPointR.x;;
	commandY3 = -uTCRotatePointRY + uniformCrossPointR.y;

	instruction.commandX = (commandX1 + commandX2 + commandX3) / 3;
	instruction.commandY = (commandY1 + commandY2 + commandY3) / 3;
	//instruction.commandX = commandX1;
	//instruction.commandY = commandY1;

	return instruction;
}


void CMFCApplication3Dlg::OnBnClickedAlignmentWo()
{
	index++;

	/*对位开始*/
	/*计算基准位姿*/
	Position bmPosition;
	bmPosition = CalPosition(bmImageL, bmImageR, invH1,
		centerWorldL1.center,centerWorldR1.center);

	/*计算待测工件位姿*/
	Position testPosition = CalPosition(testImageL, testImageR, invH1, 
		centerWorldL1.center, centerWorldR1.center);

	/*运动指令*/
	instruction1 = GetInstruction2(bmImageL, testImageL, bmPosition, testPosition, rotatePoint1);

	CString  indexToText,X, Y, Theta;

	indexToText.Format(TEXT("%d"), index);
	X.Format(TEXT("%0.5f"), instruction1.commandX);
	Y.Format(TEXT("%0.5f"), instruction1.commandY);
	Theta.Format(TEXT("%f"),instruction1.commandTheta * 180 / PI);

	//InstructionCommandList.SetItemText(index - 1, 0, indexToText);
	InstructionCommandList.SetItemText(index - 1, 1, X);
	InstructionCommandList.SetItemText(index - 1, 2, Y);
	InstructionCommandList.SetItemText(index - 1, 3, Theta);
	
	tuple<int, float, float, float> res1;
	get<0>(res1) = index;
	get<1>(res1) = instruction1.commandX;
	get<2>(res1) = instruction1.commandY;
	get<3>(res1) = instruction1.commandTheta * 180 / PI;

	resultText1.push_back(res1);
}


/*************************************************************
Function:       RotateImage
Description:    旋转图片
Input:          src:需要旋转的图片路径 angle:旋转角度
Return:         旋转后的图片
**************************************************************/
cv::Mat RotateImage(cv::Mat src, double angle)
{
	cv::Mat dst;
	try
	{
		//float scale = 200.0/ src.rows;//缩放因子    
		//cv::resize(src, src, cv::Size(), scale, scale, cv::INTER_LINEAR);    	    	
		//输出图像的尺寸与原图一样    
		cv::Size dst_sz(src.cols, src.rows);

		//指定旋转中心      
		cv::Point2f center(static_cast<float>(src.cols / 2.), static_cast<float>(src.rows / 2.));

		//获取旋转矩阵（2x3矩阵）      
		cv::Mat rot_mat = cv::getRotationMatrix2D(center, angle, 1.0);
		//设置选择背景边界颜色   
		/*cv::Scalar borderColor = Scalar(0, 238, 0);*/
		/*cv::warpAffine(src, dst, rot_mat, src.size(), INTER_LINEAR, BORDER_CONSTANT, borderColor);*/
		//复制边缘填充
		cv::warpAffine(src, dst, rot_mat, dst_sz, cv::INTER_LINEAR, cv::BORDER_REPLICATE);
	}
	catch (cv::Exception e)
	{
	}

	return dst;
}


void CMFCApplication3Dlg::OnBnClickedCameracalibation()
{
	CString m_strFileOut = _T("");  //初始化适应Unicode
	TCHAR szSelected[MAX_PATH];//用来存放文件夹路径  
	BROWSEINFO bi;
	LPITEMIDLIST pidl;
	bi.hwndOwner = this->m_hWnd;
	bi.pidlRoot = NULL;
	bi.pszDisplayName = szSelected;
	bi.lpszTitle = _T("选择标定文件路径");
	bi.ulFlags = BIF_RETURNONLYFSDIRS;
	bi.lpfn = NULL;
	bi.lParam = NULL;
	bi.iImage = NULL;
	if ((pidl = SHBrowseForFolder(&bi)) != NULL)
	{
		if (SUCCEEDED(SHGetPathFromIDList(pidl, szSelected))) //得到文件夹的全路径，不要的话，只得本文件夹名  
		{
			m_strFileOut = szSelected;  	//获得文件夹的全路径
		}
	}

	USES_CONVERSION;

	/*计算单相机的平移标定角点的图像像素坐标*/
	maskImageL = imread("F:\\数据集\\对位\\3号台圆弧盖板图像\\maskImageL.bmp", 0);
	maskImageR = imread("F:\\数据集\\对位\\3号台圆弧盖板图像\\maskImageR.bmp", 0);

	CString srcImagePathL, srcImagePathR;
	CString srcPathL, srcPathR;
	Mat srcImageRectL, srcImageRectR;
	Rect rectL, rectR;
	float pointTransSetL[3][9], pointTransSetR[3][9];//角点图像像素坐标
	for (int index = 1; index < 10; index++)
	{
		srcPathL.Format(_T("\\L\\T-L-%d.bmp"),index);
		srcPathR.Format(_T("\\R\\T-R-%d.bmp"), index);

		srcImagePathL = m_strFileOut + srcPathL;
		srcImagePathR = m_strFileOut + srcPathR;
		
		string strL(W2A(srcImagePathL));
		string strR(W2A(srcImagePathR));

		Mat srcImageL = imread(strL, 0);
		Mat srcImageR = imread(strR, 0);

#if CrossMethod==1
		Point2f resultPointL = GetCrossPointL(srcImageL, thresholdValue, erodeSize,
			circleRadiusMax, deltaRadius, CannyThreshold1, CannyThreshold2,
			HoughThreshold1, HoughThreshold2, HoughThreshold3);
		Point2f resultPointR = GetCrossPointR(srcImageR, CannyThreshold1, CannyThreshold2,
			HoughThreshold1, HoughThreshold2, HoughThreshold3);
#elif CrossMethod == 2
		Point2f resultPointL = GetCrossBasedShapeL(srcImageL, maskImageL);
		Point2f resultPointR = GetCrossBasedShapeR(srcImageR, maskImageR);
#elif CrossMethod == 3
		Point2f resultPointL = GetCrossBasedFastShapeL(srcImageL, maskImageL, 255, 1500, &strL[0]);
		Point2f resultPointR = GetCrossBasedFastShapeR(srcImageR, maskImageR, 255, 1500, &strR[0]);
#endif 

		pointTransSetL[0][index - 1] = resultPointL.x;
		pointTransSetL[1][index - 1] = resultPointL.y;
		pointTransSetL[2][index - 1] = 1;

		pointTransSetR[0][index - 1] = resultPointR.x;
		pointTransSetR[1][index - 1] = resultPointR.y;
		pointTransSetR[2][index - 1] = 1;

		//cvtColor(srcImageL, srcImageL, COLOR_GRAY2BGR);
		//cvtColor(srcImageR, srcImageR, COLOR_GRAY2BGR);
		//circle(srcImageL, resultPointL, 8, Scalar(0, 0, 255), 8);
		//circle(srcImageR, resultPointR, 8, Scalar(0, 0, 255), 8);
		//namedWindow(srcImagePathR, 0);
		//imshow(srcImagePathR, srcImageR);
		//namedWindow(srcImagePathL, 0);
		//imshow(srcImagePathL, srcImageL);
	}

	/*单相机标定，计算单应性矩阵H*/
	//图像像素坐标以Mat形式存储
	Mat matSetL(3, 9, CV_32FC1);
	Mat matSetR(3, 9, CV_32FC1);

	for (int y = 0; y < 3; ++y) {
		for (int x = 0; x < 9; ++x) {
			matSetL.at<float>(y, x) = pointTransSetL[y][x];
			matSetR.at<float>(y, x) = pointTransSetR[y][x];
		}
	}

	//计算图像像素坐标矩阵的伪逆
	Mat imatSetL(9, 3, CV_32FC1);
	Mat imatSetR(9, 3, CV_32FC1);

	invert(matSetL, imatSetL, DECOMP_SVD);
	invert(matSetR, imatSetR, DECOMP_SVD);

	//标定点的物理坐标以Mat形式存储
	Mat matTransWorldSet(4, 9, CV_32FC1);
	//cvtColor(matTransWorldSet, matTransWorldSet, CV_BGR2GRAY);
	for (int y = 0; y < 4; ++y) {
		for (int x = 0; x < 9; ++x) {
			matTransWorldSet.at<float>(y, x) = pointWorldSet[y][x];
		}
	}

	/*计算单应性矩阵*/
	invH1.L.convertTo(invH1.L, CV_32FC1);
	invH1.R.convertTo(invH1.R, CV_32FC1);

	invH1.L = matTransWorldSet * imatSetL;
	invH1.R = matTransWorldSet * imatSetR;


	float pointRotateSetL[3][3], pointRotateSetR[3][3];
	for (int index = 1; index < 4; index++)
	{
		srcPathL.Format(_T("\\L\\rotate-L-%d.bmp"), index);
		srcPathR.Format(_T("\\R\\rotate-R-%d.bmp"), index);

		srcImagePathL = m_strFileOut + srcPathL;
		srcImagePathR = m_strFileOut + srcPathR;

		string strL(W2A(srcImagePathL));
		string strR(W2A(srcImagePathR));

		Mat srcImageL = imread(strL, 0);
		Mat srcImageR = imread(strR, 0);


#if CrossMethod==1
		Point2f resultPointL = GetCrossPointL(srcImageL, thresholdValue, erodeSize,
			circleRadiusMax, deltaRadius, CannyThreshold1, CannyThreshold2,
			HoughThreshold1, HoughThreshold2, HoughThreshold3);
		Point2f resultPointR = GetCrossPointR(srcImageR, CannyThreshold1, CannyThreshold2,
			HoughThreshold1, HoughThreshold2, HoughThreshold3);
#elif CrossMethod == 2
		Point2f resultPointL = GetCrossBasedShapeL(srcImageL, maskImageL);
		Point2f resultPointR = GetCrossBasedShapeR(srcImageR, maskImageR);
#elif CrossMethod == 3
		Point2f resultPointL = GetCrossBasedFastShapeL(srcImageL, maskImageL, 255, 1500, &strL[0]);
		Point2f resultPointR = GetCrossBasedFastShapeR(srcImageR, maskImageR, 255, 1500, &strR[0]);
#endif 

		pointRotateSetL[0][index - 1] = resultPointL.x;
		pointRotateSetL[1][index - 1] = resultPointL.y;
		pointRotateSetL[2][index - 1] = 1;

		pointRotateSetR[0][index - 1] = resultPointR.x;
		pointRotateSetR[1][index - 1] = resultPointR.y;
		pointRotateSetR[2][index - 1] = 1;

		//cvtColor(srcImageL, srcImageL, COLOR_GRAY2BGR);
		//cvtColor(srcImageR, srcImageR, COLOR_GRAY2BGR);
		//circle(srcImageL, resultPointL, 8, Scalar(0, 0, 255), 8);
		//circle(srcImageR, resultPointR, 8, Scalar(0, 0, 255), 8);
		//namedWindow(srcImagePathR, 0);
		//imshow(srcImagePathR, srcImageR);
		//namedWindow(srcImagePathL, 0);
		//imshow(srcImagePathL, srcImageL);
	}

	Point2f pointL1 = Point2f(pointRotateSetL[0][0], pointRotateSetL[1][0]);
	Point2f pointL2 = Point2f(pointRotateSetL[0][1], pointRotateSetL[1][1]);
	Point2f pointL3 = Point2f(pointRotateSetL[0][2], pointRotateSetL[1][2]);

	Point2f pointR1 = Point2f(pointRotateSetR[0][0], pointRotateSetR[1][0]);
	Point2f pointR2 = Point2f(pointRotateSetR[0][1], pointRotateSetR[1][1]);
	Point2f pointR3 = Point2f(pointRotateSetR[0][2], pointRotateSetR[1][2]);

	/*拟合点变换至世界坐标系*/
	Point2f pointLW1 = TransToWorldAxis(pointL1, invH1.L);
	Point2f pointLW2 = TransToWorldAxis(pointL2, invH1.L);
	Point2f pointLW3 = TransToWorldAxis(pointL3, invH1.L);

	Point2f pointRW1 = TransToWorldAxis(pointR1, invH1.R);
	Point2f pointRW2 = TransToWorldAxis(pointR2, invH1.R);
	Point2f pointRW3 = TransToWorldAxis(pointR3, invH1.R);

	/*根据最小二乘法计算旋转中心centerL,centerR*/
	//CircleData centerL = findCircle2(pointL2, pointL3, pointL1);
	//CircleData centerR = findCircle2(pointR2, pointR3, pointR1);
	//CircleData centerL = findCircle3(pointL1, pointL2, pointL3);
	//CircleData centerR = findCircle3(pointR1, pointR2, pointR3);

	CircleData centerLW = findCircle2(pointLW1, pointLW2, pointLW3);
	CircleData centerRW = findCircle2(pointRW1, pointRW2, pointRW3);

	//float distanceL1 = sqrt((centerLW.center.x - pointLW1.x)*(centerLW.center.x - pointLW1.x) +
	//	(centerLW.center.y - pointLW1.y)*(centerLW.center.y - pointLW1.y));
	//float distanceL2 = sqrt((centerLW.center.x - pointLW2.x)*(centerLW.center.x - pointLW2.x) +
	//	(centerLW.center.y - pointLW2.y)*(centerLW.center.y - pointLW2.y));
	//float distanceL3 = sqrt((centerLW.center.x - pointLW3.x)*(centerLW.center.x - pointLW3.x) +
	//	(centerLW.center.y - pointLW3.y)*(centerLW.center.y - pointLW3.y));
	//float distanceR1 = sqrt((centerRW.center.x - pointRW1.x)*(centerRW.center.x - pointRW1.x) +
	//	(centerRW.center.y - pointRW1.y)*(centerRW.center.y - pointRW1.y));
	//float distanceR2 = sqrt((centerRW.center.x - pointRW2.x)*(centerRW.center.x - pointRW2.x) +
	//	(centerRW.center.y - pointRW2.y)*(centerRW.center.y - pointRW2.y));
	//float distanceR3 = sqrt((centerRW.center.x - pointRW3.x)*(centerRW.center.x - pointRW3.x) +
	//	(centerRW.center.y - pointRW3.y)*(centerRW.center.y - pointRW3.y));

	centerWorldL1.center = centerLW.center;
	centerWorldR1.center = centerRW.center;

	//deltaX1 = centerWorldR1.center.x - centerWorldL1.center.x;
	//deltaY1 = centerWorldR1.center.y - centerWorldL1.center.y;

	rotatePoint1 = centerWorldL1.center;
	RotateX1.Format(TEXT("%0.5f"), rotatePoint1.x);
	RotateY1.Format(TEXT("%0.5f"), rotatePoint1.y);

	RotatePointList1.InsertItem(0, RotateX1);
	RotatePointList1.SetItemText(0, 1, RotateY1);
}


void CMFCApplication3Dlg::OnLvnItemchangedList3(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}


//void CMFCApplication3Dlg::OnBnClickedRectifyrotatecenter()
//{
//	// TODO: 在此添加控件通知处理程序代码
//	Position resultPosition = CalPosition(resultImageL, resultImageR, maskL, maskR,
//		invH, deltaX, deltaY);
//
//	deltaXeWorld = bmPosition.uniformCenterPoint.x - resultPosition.uniformCenterPoint.x;
//	deltaYeWorld = bmPosition.uniformCenterPoint.y - resultPosition.uniformCenterPoint.y;
//
//	/*这里计算的是统一世界坐标系下的旋转中心坐标，
//	但是它在左右相机局部世界坐标系下的表示仍未知，
//	因此新的deltaX与deltaY仍然未知*/
//	Point2f RectifiedRCenter = RectifyRotateCenter(testPosition, bmPosition, instruction1, deltaXeWorld, deltaYeWorld);
//
//	/*重新计算右相机局部世界坐标系统一所需的参数*/
//	deltaX = circlePointWorldR.center.x - RectifiedRCenter.x;
//	deltaY = circlePointWorldR.center.y - RectifiedRCenter.y;
//
//	/*重新计算参考位姿*/
//	bmPosition = CalPosition(bmImageL, bmImageR,maskL,maskR, invH, deltaX, deltaY);
//
//	Mat resultImageL2, resultImageR2;
//	//resultImageL2 = imread(, 0);
//	//resultImageR2 = imread(, 0);
//	Position resultPosition2 = CalPosition(resultImageL2, resultImageR2, maskL, maskR, invH, deltaX, deltaY);
//
//	/*重新控制指令，纠偏*/
//	instruction1 = GetInstruction(bmPosition, resultPosition2, RectifiedRCenter);
//	cout << "Error rectify's control instruction in X-axis is: " << instruction1.commandX << endl;
//	cout << "Error rectify's control instruction in Y-axis is: " << instruction1.commandY << "\n" << endl;
//	cout << "Error rectify's control instruction in Theta-axis is: " << instruction1.commandTheta << endl;
//
//}


void CMFCApplication3Dlg::OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}


void CMFCApplication3Dlg::OnBnClickedButton6()
{
	index = 0;
	vector<tuple<int, float, float, float>>().swap(resultText1);
	CString str2[] = { TEXT("X(mm)"),TEXT("Y(mm)"),TEXT("Theta(°)") };
	InstructionCommandList.InsertColumn(0, TEXT("序号"), LVCFMT_CENTER, 60);
	for (int i = 1; i < 4; i++)
	{
		InstructionCommandList.InsertColumn(i, str2[i - 1], LVCFMT_CENTER, 80);
	}

	for (int i = 0; i < 100; i++)
	{
		CString iToText;
		iToText.Format(TEXT("%d"), 100 - i);
		InstructionCommandList.InsertItem(0, iToText);
	}
}


void CMFCApplication3Dlg::OnBnClickedButton1()
{
	/*对位开始*/
	/*计算基准位姿*/
	Position bmPosition = CalPosition(bmImageL, bmImageR, invH2,
		centerWorldL2.center, centerWorldR2.center);

	/*计算待测工件位姿*/
	Position testPosition = CalPosition(testImageL, testImageR, invH2, 
		centerWorldL2.center, centerWorldR2.center);

	/*运动指令*/
	//instruction2 = GetInstruction(bmPosition, testPosition, rotatePoint2);
	instruction2 = GetInstruction2(bmImageL, testImageL, bmPosition, testPosition, rotatePoint1);

	CString  indexToText, X, Y, Theta;

	//indexToText.Format(TEXT("%d"), index-1);
	X.Format(TEXT("%0.5f"), instruction2.commandX);
	Y.Format(TEXT("%0.5f"), instruction2.commandY);
	Theta.Format(TEXT("%f"), instruction2.commandTheta * 180 / PI);

	//RectifyInstructionCommand.InsertItem(0, indexToText);
	RectifyInstructionCommand.SetItemText(index - 1, 1, X);
	RectifyInstructionCommand.SetItemText(index - 1, 2, Y);
	RectifyInstructionCommand.SetItemText(index - 1, 3, Theta);

	tuple<int, float, float, float> res2;
	get<0>(res2) = index;
	get<1>(res2) = instruction2.commandX;
	get<2>(res2) = instruction2.commandY;
	get<3>(res2) = instruction2.commandTheta * 180 / PI;

	resultText2.push_back(res2);
}


void CMFCApplication3Dlg::OnBnClickedButton5()
{
	CFileDialog dlg(TRUE, NULL,
		NULL,
		OFN_FILEMUSTEXIST | OFN_SHAREAWARE | OFN_PATHMUSTEXIST,
		TEXT("所有文件(*.*)|*.*|"),
		NULL);
	CString strPathName;
	if (dlg.DoModal() == IDOK)
	{
		strPathName = dlg.GetPathName();
	}

	ofstream outfile1;
	outfile1.open(strPathName, ios::trunc);

	tuple<int, float, float, float> curResult1;
	for (int i = 0; i < resultText1.size(); i++)
	{
		outfile1 << "index:" << get<0>(resultText1[i]) <<
			"  " << "X: " << get<1>(resultText1[i]) <<
			"  " << "Y: " << get<2>(resultText1[i]) <<
			"  " << "Theta: " << get<3>(resultText1[i]) <<"\n";
	}
	outfile1.close();//关闭文件，保存文件
}


void CMFCApplication3Dlg::OnBnClickedButton7()
{
	CFileDialog dlg(TRUE, NULL,
		NULL,
		OFN_FILEMUSTEXIST | OFN_SHAREAWARE | OFN_PATHMUSTEXIST,
		TEXT("所有文件(*.*)|*.*|"),
		NULL);
	CString strPathName;
	if (dlg.DoModal() == IDOK)
	{
		strPathName = dlg.GetPathName();
	}

	ofstream outfile2;

	outfile2.open(strPathName, ios::trunc);

	tuple<int, float, float, float> curResult2;
	for (int i = 0; i < resultText2.size(); i++)
	{
		outfile2 << "index:" << get<0>(resultText2[i]) <<
			"  " << "X: " << get<1>(resultText2[i]) <<
			"  " << "Y: " << get<2>(resultText2[i]) <<
			"  " << "Theta: " << get<3>(resultText2[i]) << "\n";
	}
	outfile2.close();//关闭文件，保存文件
}


void CMFCApplication3Dlg::OnBnClickedButton9()
{
	// TODO: 在此添加控件通知处理程序代码
		// TODO: 在此添加控件通知处理程序代码
	//打开文件 定义四种格式的文件bmp gif jpg tiff
	CString m_strFilePath = _T("");

	//打开图像文件，获取文件路径名
	LPCTSTR szFilter = _T("ALLSUPORTFILE(*.*)|*.*|JPG(*.jpg)|*.jpg|BMP(*.bmp)|*.bmp||");
	CFileDialog dlgFileOpenImg(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter, NULL);
	//打开图像
	if (dlgFileOpenImg.DoModal() == IDOK)
	{
		//读取图像文件名
		m_strFilePath = dlgFileOpenImg.GetPathName();
	}
	else
	{
		return;
	}

	USES_CONVERSION;
	string str(W2A(m_strFilePath));
	secImageResultL = imread(str, 0);
	ShowPic_secResultViewL(secImageResultL);
}


void CMFCApplication3Dlg::OnBnClickedButton10()
{
	// TODO: 在此添加控件通知处理程序代码
		// TODO: 在此添加控件通知处理程序代码
	//打开文件 定义四种格式的文件bmp gif jpg tiff
	CString m_strFilePath = _T("");

	//打开图像文件，获取文件路径名
	LPCTSTR szFilter = _T("ALLSUPORTFILE(*.*)|*.*|JPG(*.jpg)|*.jpg|BMP(*.bmp)|*.bmp||");
	CFileDialog dlgFileOpenImg(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter, NULL);
	//打开图像
	if (dlgFileOpenImg.DoModal() == IDOK)
	{
		//读取图像文件名
		m_strFilePath = dlgFileOpenImg.GetPathName();
	}
	else
	{
		return;
	}

	USES_CONVERSION;
	string str(W2A(m_strFilePath));
	secImageResultR = imread(str, 0);
	ShowPic_secResultViewR(secImageResultR);
}



void CMFCApplication3Dlg::OnStnClickedRectifyimageviewr()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CMFCApplication3Dlg::OnBnClickedButton8()
{
	index = 0;
	vector<tuple<int, float, float, float>>().swap(resultText2);
	CString str2[] = { TEXT("X(mm)"),TEXT("Y(mm)"),TEXT("Theta(°)") };
	RectifyInstructionCommand.InsertColumn(0, TEXT("序号"), LVCFMT_CENTER, 60);
	for (int i = 1; i < 4; i++)
	{
		RectifyInstructionCommand.InsertColumn(i, str2[i - 1], LVCFMT_CENTER, 80);
	}

	for (int i = 0; i < 100; i++)
	{
		CString iToText;
		iToText.Format(TEXT("%d"), 100 - i);
		RectifyInstructionCommand.InsertItem(0, iToText);
	}
}


void CMFCApplication3Dlg::OnBnClickedResultimagel()
{
	// TODO: 在此添加控件通知处理程序代码
		// TODO: 在此添加控件通知处理程序代码
	//打开文件 定义四种格式的文件bmp gif jpg tiff
	CString m_strFilePath = _T("");

	//打开图像文件，获取文件路径名
	LPCTSTR szFilter = _T("ALLSUPORTFILE(*.*)|*.*|JPG(*.jpg)|*.jpg|BMP(*.bmp)|*.bmp||");
	CFileDialog dlgFileOpenImg(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter, NULL);
	//打开图像
	if (dlgFileOpenImg.DoModal() == IDOK)
	{
		//读取图像文件名
		m_strFilePath = dlgFileOpenImg.GetPathName();
	}
	else
	{
		return;
	}

	USES_CONVERSION;
	string str(W2A(m_strFilePath));
	resultImageL = imread(str, 0);
	ShowPic_resultImageViweL(resultImageL);
}


void CMFCApplication3Dlg::OnBnClickedResultimager()
{
	// TODO: 在此添加控件通知处理程序代码
		// TODO: 在此添加控件通知处理程序代码
	//打开文件 定义四种格式的文件bmp gif jpg tiff
	CString m_strFilePath = _T("");

	//打开图像文件，获取文件路径名
	LPCTSTR szFilter = _T("ALLSUPORTFILE(*.*)|*.*|JPG(*.jpg)|*.jpg|BMP(*.bmp)|*.bmp||");
	CFileDialog dlgFileOpenImg(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter, NULL);
	//打开图像
	if (dlgFileOpenImg.DoModal() == IDOK)
	{
		//读取图像文件名
		m_strFilePath = dlgFileOpenImg.GetPathName();
	}
	else
	{
		return;
	}

	USES_CONVERSION;
	string str(W2A(m_strFilePath));
	resultImageR = imread(str, 0);
	ShowPic_resultImageViweR(resultImageR);
}


void CMFCApplication3Dlg::OnBnClickedButton11()
{
	CString m_strFileOut = _T("");  //初始化适应Unicode
	TCHAR szSelected[MAX_PATH];//用来存放文件夹路径  
	BROWSEINFO bi;
	LPITEMIDLIST pidl;
	bi.hwndOwner = this->m_hWnd;
	bi.pidlRoot = NULL;
	bi.pszDisplayName = szSelected;
	bi.lpszTitle = _T("选择标定文件路径");
	bi.ulFlags = BIF_RETURNONLYFSDIRS;
	bi.lpfn = NULL;
	bi.lParam = NULL;
	bi.iImage = NULL;
	if ((pidl = SHBrowseForFolder(&bi)) != NULL)
	{
		if (SUCCEEDED(SHGetPathFromIDList(pidl, szSelected))) //得到文件夹的全路径，不要的话，只得本文件夹名  
		{
			m_strFileOut = szSelected;  	//获得文件夹的全路径
		}
	}

	CString srcImagePathL, srcImagePathR;
	CString srcPathL, srcPathR;

	/*计算单相机的平移标定角点的图像像素坐标*/
	Mat srcImageRectL, srcImageRectR;
	Rect rectL, rectR;
	float pointTransSetL[3][9], pointTransSetR[3][9];//角点图像像素坐标
	USES_CONVERSION;
	for (int index = 1; index < 10; index++)
	{
		srcPathL.Format(_T("\\L\\T-L-%d.bmp"), index);
		srcPathR.Format(_T("\\R\\T-R-%d.bmp"), index);

		srcImagePathL = m_strFileOut + srcPathL;
		srcImagePathR = m_strFileOut + srcPathR;

		string strL(W2A(srcImagePathL));
		string strR(W2A(srcImagePathL));

		Mat srcImageL = imread(strL, 0);
		Mat srcImageR = imread(strR, 0);

		Point2f resultPointL = GetCrossPointL(srcImageL, thresholdValue, erodeSize,
			circleRadiusMax, deltaRadius, CannyThreshold1, CannyThreshold2,
			HoughThreshold1, HoughThreshold2, HoughThreshold3);
		Point2f resultPointR = GetCrossPointR(srcImageR, CannyThreshold1, CannyThreshold2,
			HoughThreshold1, HoughThreshold2, HoughThreshold3);

		pointTransSetL[0][index - 1] = resultPointL.x;
		pointTransSetL[1][index - 1] = resultPointL.y;
		pointTransSetL[2][index - 1] = 1;
		pointTransSetR[0][index - 1] = resultPointR.x;
		pointTransSetR[1][index - 1] = resultPointR.y;
		pointTransSetR[2][index - 1] = 1;

		//cvtColor(srcImageL, srcImageL, COLOR_GRAY2BGR);
		//cvtColor(srcImageR, srcImageR, COLOR_GRAY2BGR);
		//circle(srcImageL, resultPointL, 8, Scalar(0, 0, 255), 8);
		//circle(srcImageR, resultPointR, 8, Scalar(0, 0, 255), 8);
		//namedWindow(srcImagePathR, 0);
		//imshow(srcImagePathR, srcImageR);
		//namedWindow(srcImagePathL, 0);
		//imshow(srcImagePathL, srcImageL);
	}

	/*单相机标定，计算单应性矩阵H*/
	//图像像素坐标以Mat形式存储
	Mat matSetL(3, 9, CV_32FC1);
	Mat matSetR(3, 9, CV_32FC1);

	for (int y = 0; y < 3; ++y) {
		for (int x = 0; x < 9; ++x) {
			matSetL.at<float>(y, x) = pointTransSetL[y][x];
			matSetR.at<float>(y, x) = pointTransSetR[y][x];
		}
	}

	//计算图像像素坐标矩阵的伪逆
	Mat imatSetL, imatSetR;
	invert(matSetL, imatSetL, DECOMP_SVD);
	invert(matSetR, imatSetR, DECOMP_SVD);

	//标定点的物理坐标以Mat形式存储
	Mat matTransWorldSet(4, 9, CV_32FC1);
	for (int y = 0; y < 4; ++y) {
		for (int x = 0; x < 9; ++x) {
			matTransWorldSet.at<float>(y, x) = pointWorldSet[y][x];
		}
	}

	/*计算单应性矩阵*/
	invH2.L = matTransWorldSet * imatSetL;
	invH2.R = matTransWorldSet * imatSetR;

	float pointRotateSetL[3][3], pointRotateSetR[3][3];
	for (int index = 1; index < 4; index++)
	{
		srcPathL.Format(_T("\\L\\rotate-L-%d.bmp"), index);
		srcPathR.Format(_T("\\R\\rotate-R-%d.bmp"), index);

		srcImagePathL = m_strFileOut + srcPathL;
		srcImagePathR = m_strFileOut + srcPathR;

		string strL(W2A(srcImagePathL));
		string strR(W2A(srcImagePathR));

		Mat srcImageL = imread(strL, 0);
		Mat srcImageR = imread(strR, 0);

		Point2f resultPointL = GetCrossPointL(srcImageL, thresholdValue, erodeSize,
			circleRadiusMax, deltaRadius, CannyThreshold1, CannyThreshold2,
			HoughThreshold1, HoughThreshold2, HoughThreshold3);
		Point2f resultPointR = GetCrossPointR(srcImageR, CannyThreshold1, CannyThreshold2,
			HoughThreshold1, HoughThreshold2, HoughThreshold3);

		pointRotateSetL[0][index - 1] = resultPointL.x;
		pointRotateSetL[1][index - 1] = resultPointL.y;
		pointRotateSetL[2][index - 1] = 1;

		pointRotateSetR[0][index - 1] = resultPointR.x;
		pointRotateSetR[1][index - 1] = resultPointR.y;
		pointRotateSetR[2][index - 1] = 1;

		//cvtColor(srcImageL, srcImageL, COLOR_GRAY2BGR);
		//cvtColor(srcImageR, srcImageR, COLOR_GRAY2BGR);
		//circle(srcImageL, resultPointL, 8, Scalar(0, 0, 255), 8);
		//circle(srcImageR, resultPointR, 8, Scalar(0, 0, 255), 8);
		//namedWindow(srcImagePathR, 0);
		//imshow(srcImagePathR, srcImageR);
		//namedWindow(srcImagePathL, 0);
		//imshow(srcImagePathL, srcImageL);
	}

	Point2f pointL1 = Point2f(pointRotateSetL[0][0], pointRotateSetL[1][0]);
	Point2f pointL2 = Point2f(pointRotateSetL[0][1], pointRotateSetL[1][1]);
	Point2f pointL3 = Point2f(pointRotateSetL[0][2], pointRotateSetL[1][2]);
	Point2f pointR1 = Point2f(pointRotateSetR[0][0], pointRotateSetR[1][0]);
	Point2f pointR2 = Point2f(pointRotateSetR[0][1], pointRotateSetR[1][1]);
	Point2f pointR3 = Point2f(pointRotateSetR[0][2], pointRotateSetR[1][2]);

	Point2f pointLW1 = TransToWorldAxis(pointL1, invH2.L);
	Point2f pointLW2 = TransToWorldAxis(pointL2, invH2.L);
	Point2f pointLW3 = TransToWorldAxis(pointL3, invH2.L);
	
	Point2f pointRW1 = TransToWorldAxis(pointR1, invH2.R);
	Point2f pointRW2 = TransToWorldAxis(pointR2, invH2.R);
	Point2f pointRW3 = TransToWorldAxis(pointR3, invH2.R);

	/*基于固定圆心角约束的最小二乘法计算旋转中心testCenterL,testCenterR*/
	Point2f testCenterLW1 = findCircle1(pointLW1, pointLW2, THETA * PI / 180);
	Point2f testCenterLW2 = findCircle1(pointLW2, pointLW3, THETA * PI / 180);
	//Point2f testCenterL = Point2f((testCenterL1.x + testCenterL2.x) / 2,
	//	(testCenterL1.y + testCenterL2.y) / 2);
	Point2f testCenterLW3 = findCircle1(pointLW1, pointLW3, 2 * THETA * PI / 180);
	Point2f testCenterLW = Point2f((testCenterLW1.x + testCenterLW2.x + testCenterLW3.x) / 3,
		(testCenterLW1.y + testCenterLW2.y + testCenterLW3.y) / 3);

	Point2f testCenterRW1 = findCircle1(pointRW1, pointRW2, THETA * PI / 180);
	Point2f testCenterRW2 = findCircle1(pointRW2, pointRW3, THETA * PI / 180);
	//Point2f testCenterR = Point2f((testCenterR1.x + testCenterR2.x) / 2,
	//	(testCenterR1.y + testCenterR2.y) / 2);
	Point2f testCenterRW3 = findCircle1(pointRW1, pointRW3, 2 * THETA * PI / 180);
	Point2f testCenterRW = Point2f((testCenterRW1.x + testCenterRW2.x + testCenterRW3.x) / 3,
		(testCenterRW1.y + testCenterRW2.y + testCenterRW3.y) / 3);

	centerWorldL2.center = testCenterLW;
	centerWorldR2.center = testCenterRW;
	rotatePoint2 = centerWorldL2.center;

	RotateX2.Format(TEXT("%0.5f"), rotatePoint2.x);
	RotateY2.Format(TEXT("%0.5f"), rotatePoint2.y);

	RotatePointList2.InsertItem(0, RotateX2);
	RotatePointList2.SetItemText(0, 1, RotateY2);
}


void CMFCApplication3Dlg::OnLvnItemchangedList4(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}


void CMFCApplication3Dlg::OnEnChangeCanny1()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void CMFCApplication3Dlg::OnEnChangeHough1()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void CMFCApplication3Dlg::OnEnChangeThreshold()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void CMFCApplication3Dlg::OnEnChangeerodesize()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void CMFCApplication3Dlg::OnEnChangeHough3()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void CMFCApplication3Dlg::OnEnChangeHough2()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void CMFCApplication3Dlg::OnEnChangeHoughcircle()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}
