#include "pch.h"
#include "framework.h"
#include "MFCApplication3.h"
#include "MFCApplication3Dlg.h"
#include "afxdialogex.h"
#include "MyFunction.h"
#include "resource.h"
#include<stdio.h>
#include <fstream>
#include <cstdlib>
#include "MyGLobal.h"
#include <string>
#include "LM.h"


using namespace std;

//Mat ML;
//Mat MR;

int CalNum = 9;

//float pointWorldSet[4][9] = {
//-3,  0,  3,  3,  0,    -3,     -3,      0,       3,
// 3,  3,  3,  0,  0,     0,     -3,     -3,      -3,
//0,   0,  0,  0,  0,     0,      0,      0,       0,
//1,   1,  1,  1,  1,     1,      1,      1,       1
//};

float pointWorldSet[4][9] = {
-3,  0,  3,  3,  0,    -3,     -3,      0,       3,
 3,  3,  3,  0,  0,     0,     -3,     -3,      -3
};

//float pointWorldSet[4][9] = {
//0,	1, -2,	2, -3.051900304, -4.069200405, -2.783422733, -3.559973736, -5,
//0,	1, -2,	2, -2.947185867, -3.929581156, -3.201961569, -4.396201428, -5,
//0,	0,	0,	0,	0,	0,	0,	0,	0,
//1,	1,	1,	1,	1,	1,	1,	1,	1
//};
//float pointWorldSet[4][5] = {
//0,	1, -2,	2,  -5,
//0,	1, -2,	2,  -5,
//0,	0,	0,	0,	 0,
//1,	1,	1,	1,	 1
//};


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
public:
	afx_msg void OnBnClickedButton4();
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON4, &CAboutDlg::OnBnClickedButton4)
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
	CString str2[] = { TEXT("X(mm)"),TEXT("Y(mm)"),TEXT("Theta(°)") };
	InstructionCommandList.InsertColumn(0, TEXT("序号"), LVCFMT_CENTER, 40);
	RectifyInstructionCommand.InsertColumn(0, TEXT("序号"), LVCFMT_CENTER, 40);
	for (int i = 1; i < 4; i++)
	{
		InstructionCommandList.InsertColumn(i, str2[i - 1], LVCFMT_CENTER, 80);
		RectifyInstructionCommand.InsertColumn(i, str2[i - 1], LVCFMT_CENTER, 80);
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

	m_threshold.SetWindowTextW(TEXT("100"));
	m_erodeSize.SetWindowTextW(TEXT("1.00"));
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
	CRect rect;
	GetDlgItem(testImageViewL)->GetClientRect(&rect);
	Rect dst2(rect.left, rect.top, rect.right, rect.bottom);
	resize(input, imagedst, cv::Size(rect.Width(), rect.Height()));
	imshow("view3", imagedst);
}

void CMFCApplication3Dlg::ShowPic_testImageR(Mat input)
{
	Mat imagedst;
	CRect rect;
	GetDlgItem(testImageViewR)->GetClientRect(&rect);
	Rect dst2(rect.left, rect.top, rect.right, rect.bottom);
	resize(input, imagedst, cv::Size(rect.Width(), rect.Height()));
	imshow("view4", imagedst);
}

void CMFCApplication3Dlg::ShowPic_bmImageViweL(Mat input)
{
	Mat imagedst;
	CRect rect;
	GetDlgItem(bmImageViewL)->GetClientRect(&rect);
	Rect dst2(rect.left, rect.top, rect.right, rect.bottom);
	resize(input, imagedst, cv::Size(rect.Width(), rect.Height()));
	imshow("view5", imagedst);
}

void CMFCApplication3Dlg::ShowPic_bmImageViweR(Mat input)
{
	Mat imagedst;
	CRect rect;
	GetDlgItem(bmImageViewR)->GetClientRect(&rect);
	Rect dst2(rect.left, rect.top, rect.right, rect.bottom);
	resize(input, imagedst, cv::Size(rect.Width(), rect.Height()));
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
	ransacDistance = (float)(parametersValue[6]);

	cout << "save parameters" << "\n" << endl;
}


void CMFCApplication3Dlg::OnStnClickedPictureviewer1()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CMFCApplication3Dlg::OnStnClickedPictureviewer2()
{
	// TODO: 在此添加控件通知处理程序代码
}


//template <class Type>
//Type stringToNum(const string& str)
//{
//	istringstream iss(str);
//	Type num;
//	iss >> num;
//	return num;
//}



void CMFCApplication3Dlg::OnBnClickedButton4()
{
	FileStorage fs(".\\标定结果.xml", FileStorage::READ);

	Mat invHL, invHR;
	Mat ML, MR;
	Mat matSetL, matSetR;
	Mat matWorldSet;
	Point2f rotatePoint1, rotatePoint2;
	fs["invHL"] >> invHL;
	fs["invHR"] >> invHR;
	fs["ML"] >> ML;
	fs["MR"] >> MR;
	fs["rotatePoint1"] >> rotatePoint1;
	fs["rotatePoint2"] >> rotatePoint2;
	fs["matsetL"] >> matSetL;
	fs["matsetR"] >> matSetR;
	fs["matTransWorldSet"] >> matWorldSet;

	/*LM算法实现开始*/
	//Solution x;
	//vector<Solution> historyX;
	//x.bx = 5*PI / 180;
	//x.by = 5*PI / 180;
	//x.bz = 5*PI / 180;
	//x.px = 5;
	//x.py = 5;
	////x.k = 1 / 0.01086;
	//x.k = 1 ;
	//float mu =200;
	//LM(x, mu, historyX, matSetL, matWorldSet);
	/*LM算法实现结束*/

	/*存储角点信息实验开始*/
	string csvPathL(".\\实验结果\\1-7-对位实验-直接求逆-左相机角点信息.csv");
	vector<CrossPointInfo> resultLVector;
	vector<Point2f>pixelAxisSetL;
	RestoreInfo(csvPathL, resultLVector, pixelAxisSetL);
	/*存储角点信息实验结束*/

	cout << "pause at OnBnClickedButton4" << endl;
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
		USES_CONVERSION;
		strTestL = W2A(m_strFilePath);
		testImageL = imread(strTestL, 0);
		ShowPic_testImageL(testImageL);
	}
	else
	{
		//return;
	}


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
		USES_CONVERSION;
		strTestR = W2A(m_strFilePath);
		testImageR = imread(strTestR, 0);
		ShowPic_testImageR(testImageR);
	}
	else
	{
		//return;
	}

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

		USES_CONVERSION;
		strBmL = W2A(m_strFilePath);
		bmImageL = imread(strBmL, 0);
		ShowPic_bmImageViweL(bmImageL);
	}
	else
	{
		//return;
	}

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
		USES_CONVERSION;
		strBmR = W2A(m_strFilePath);
		bmImageR = imread(strBmR, 0);

		ShowPic_bmImageViweR(bmImageR);
	}
	else
	{
		//return;
	}

}


void CMFCApplication3Dlg::OnBnClickedAlignmentWo()
{
	index++;//界面按index从小到大顺序显示对位结果

	/*对位开始*/
	/*计算基准位姿*/
	bmPosition = CalPosition(bmImageL, bmImageR, strBmL, strBmR);

	/*计算待测工件位姿*/
	testPosition = CalPosition(testImageL, testImageR, strTestL, strTestR);

	/*运动指令*/
	instruction1 = GetInstruction(bmPosition, testPosition);

	/*界面显示运动控制指令*/
	CString  indexToText, X, Y, Theta;
	indexToText.Format(TEXT("%d"), index);
	X.Format(TEXT("%0.5f"), instruction1.commandX);
	Y.Format(TEXT("%0.5f"), instruction1.commandY);
	Theta.Format(TEXT("%f"), instruction1.commandTheta * 180 / PI);
	InstructionCommandList.SetItemText(index - 1, 1, X);
	InstructionCommandList.SetItemText(index - 1, 2, Y);
	InstructionCommandList.SetItemText(index - 1, 3, Theta);
	 
	/*保存数据 -> vector::resultText1 -> result.txt*/
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
		if (SUCCEEDED(SHGetPathFromIDList(pidl, szSelected)))
		{
			m_strFileOut = szSelected;  	//获得文件夹的全路径

			/*计算单相机的平移标定角点的图像像素坐标*/
			maskImageL = imread(".\\L-12-8.bmp", 0);
			maskImageR = imread(".\\R-12-8.bmp", 0);
			//maskImageL = imread("E:\\数据集\\3号台直角盖板图像\\maskImageL.bmp", 0);
			//maskImageR = imread("E:\\数据集\\3号台直角盖板图像\\maskImageR.bmp", 0);


			USES_CONVERSION;

			CString srcImagePathL, srcImagePathR;
			CString srcPathL, srcPathR;
			Mat srcImageRectL, srcImageRectR;
			Rect rectL, rectR;

			float pointTransSetL[3][9], pointTransSetR[3][9];//角点图像像素坐标
			//float pointTransSetL[3][5], pointTransSetR[3][5];//角点图像像素坐标
			Point2f resultPointL;

			Point2f resultPointR;
			for (int index = 1; index <= 9; index++)
			{
				srcPathL.Format(_T("\\L\\T-L-%d.bmp"), index);
				srcPathR.Format(_T("\\R\\T-R-%d.bmp"), index);

				srcImagePathL = m_strFileOut + srcPathL;
				srcImagePathR = m_strFileOut + srcPathR;

				string strL(W2A(srcImagePathL));
				string strR(W2A(srcImagePathR));

				/*加载图像*/
				Mat srcImageL = imread(strL, 0);
				Mat srcImageR = imread(strR, 0);

				/*检测角点*/
				RansacTest rl, rr;//后续实验调用，暂无用处
				CrossPointInfo resultL, resultR;
				Point2f resultPointL, resultPointR;
				resultL = GetCrossBaseFastShapeL(srcImageL, maskImageL, rl, &strL[0]);
				resultR = GetCrossBaseFastShapeR(srcImageR, maskImageR, rr, &strR[0]);
				resultPointL = resultL.crossPoint;
				resultPointR = resultR.crossPoint;

				/*存储角点*/
				pointTransSetL[0][index - 1] = resultPointL.x;
				pointTransSetL[1][index - 1] = resultPointL.y;
				pointTransSetL[2][index - 1] = 1;

				pointTransSetR[0][index - 1] = resultPointR.x;
				pointTransSetR[1][index - 1] = resultPointR.y;
				pointTransSetR[2][index - 1] = 1;
			}

			/*单相机标定，计算单应性矩阵H*/
			//图像像素坐标以Mat形式存储
			Mat matSetL(3, 9, CV_32FC1);
			Mat matSetR(3, 9, CV_32FC1);
			Mat AL(2 * 9, 8, CV_32FC1);
			Mat AR(2 * 9, 8, CV_32FC1);
			Mat BL(2 * 9, 1, CV_32FC1);
			Mat BR(2 * 9, 1, CV_32FC1);

			/*method2 计算单目相机标定矩阵*/
			for (int x = 0; x < 9; ++x)
			{
				for (int y = 0; y < 3; ++y)
				{
					matSetL.at<float>(y, x) = pointTransSetL[y][x];
					matSetR.at<float>(y, x) = pointTransSetR[y][x];
				}

				float Xw = pointWorldSet[0][x];
				float Yw = pointWorldSet[1][x];
				float uL = pointTransSetL[0][x];
				float vL = pointTransSetL[1][x];
				float uR = pointTransSetR[0][x];
				float vR = pointTransSetR[1][x];

				BL.at<float>(2 * x, 0) = uL;
				BL.at<float>(2 * x + 1, 0) = vL;
				BR.at<float>(2 * x, 0) = uR;
				BR.at<float>(2 * x + 1, 0) = vR;

				AL.at<float>(2 * x, 0) = Xw;//Xw
				AL.at<float>(2 * x, 1) = Yw;//Yw
				AL.at<float>(2 * x, 2) = 1;
				AL.at<float>(2 * x, 3) = 0;//Xw
				AL.at<float>(2 * x, 4) = 0;//Yw
				AL.at<float>(2 * x, 5) = 0;
				AL.at<float>(2 * x, 6) = -uL * Xw;//-uXw
				AL.at<float>(2 * x, 7) = -uL * Yw;//-vYw

				AR.at<float>(2 * x, 0) = Xw;//Xw
				AR.at<float>(2 * x, 1) = Yw;//Yw
				AR.at<float>(2 * x, 2) = 1;
				AR.at<float>(2 * x, 3) = 0;//Xw
				AR.at<float>(2 * x, 4) = 0;//Yw
				AR.at<float>(2 * x, 5) = 0;
				AR.at<float>(2 * x, 6) = -uR * Xw;//-uXw
				AR.at<float>(2 * x, 7) = -uR * Yw;//-vYw

				AL.at<float>(2 * x + 1, 0) = 0;//Xw
				AL.at<float>(2 * x + 1, 1) = 0;//Yw
				AL.at<float>(2 * x + 1, 2) = 0;
				AL.at<float>(2 * x + 1, 3) = Xw;//Xw
				AL.at<float>(2 * x + 1, 4) = Yw;//Yw
				AL.at<float>(2 * x + 1, 5) = 1;
				AL.at<float>(2 * x + 1, 6) = -vL * Xw;//-uXw
				AL.at<float>(2 * x + 1, 7) = -vL * Yw;//-vYw

				AR.at<float>(2 * x + 1, 0) = 0;//Xw
				AR.at<float>(2 * x + 1, 1) = 0;//Yw
				AR.at<float>(2 * x + 1, 2) = 0;
				AR.at<float>(2 * x + 1, 3) = Xw;//Xw
				AR.at<float>(2 * x + 1, 4) = Yw;//Yw
				AR.at<float>(2 * x + 1, 5) = 1;
				AR.at<float>(2 * x + 1, 6) = -vR * Xw;//-uXw
				AR.at<float>(2 * x + 1, 7) = -vR * Yw;//-vYw
			}


			Mat ALT = AL.t();
			Mat ART = AR.t();
			Mat AL_part1 = (ALT*AL).inv();
			Mat AR_part1 = (ART*AR).inv();

			Mat ML = AL_part1 * ALT * BL;
			Mat MR = AR_part1 * ART * BR;

			vector<Point2f>ptWL, ptWR;
			for (int i = 0; i < 9; i++)
			{
				Point2f ptPixelL = Point2f(pointTransSetL[0][i], pointTransSetL[1][i]);
				Point2f ptWorldL = CalWorldPoint(ptPixelL, ML);
				Point2f ptPixelR = Point2f(pointTransSetR[0][i], pointTransSetR[1][i]);
				Point2f ptWorldR = CalWorldPoint(ptPixelR, MR);

				ptWL.push_back(ptWorldL);
				ptWR.push_back(ptWorldR);
			}

			//计算图像像素坐标矩阵的伪逆
			Mat imatSetL(9, 3, CV_32FC1);
			Mat imatSetR(9, 3, CV_32FC1);
			invert(matSetL, imatSetL, DECOMP_SVD);
			invert(matSetR, imatSetR, DECOMP_SVD);
			//标定点的物理坐标以Mat形式存储
			Mat matTransWorldSet(2, 9, CV_32FC1);
			for (int y = 0; y < 2; ++y)
			{
				for (int x = 0; x < 9; ++x)
				{
					matTransWorldSet.at<float>(y, x) = pointWorldSet[y][x];
				}
			}

			/*计算单应性矩阵*/
			invH1.L.convertTo(invH1.L, CV_32FC1);
			invH1.R.convertTo(invH1.R, CV_32FC1);
			invH1.L = matTransWorldSet * imatSetL;
			invH1.R = matTransWorldSet * imatSetR;

			/*相机标定计算精度验证*/
			worldL = invH1.L*matSetL;
			worldR = invH1.R*matSetR;


			/*旋转中心标定*/
			float pointRotateSetL[2][3], pointRotateSetR[2][3];
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

				RansacTest rl, rr;//后续实验调用，暂无用处
				CrossPointInfo resultL, resultR;
				Point2f resultPointL, resultPointR;
				resultL = GetCrossBaseFastShapeL(srcImageL, maskImageL, rl, &strL[0]);
				resultR = GetCrossBaseFastShapeR(srcImageR, maskImageR, rr, &strR[0]);
				resultPointL = resultL.crossPoint;
				resultPointR = resultR.crossPoint;

				pointRotateSetL[0][index - 1] = resultPointL.x;
				pointRotateSetL[1][index - 1] = resultPointL.y;

				pointRotateSetR[0][index - 1] = resultPointR.x;
				pointRotateSetR[1][index - 1] = resultPointR.y;
			}

			Point2f pointL1 = Point2f(pointRotateSetL[0][0], pointRotateSetL[1][0]);
			Point2f pointL2 = Point2f(pointRotateSetL[0][1], pointRotateSetL[1][1]);
			Point2f pointL3 = Point2f(pointRotateSetL[0][2], pointRotateSetL[1][2]);

			Point2f pointR1 = Point2f(pointRotateSetR[0][0], pointRotateSetR[1][0]);
			Point2f pointR2 = Point2f(pointRotateSetR[0][1], pointRotateSetR[1][1]);
			Point2f pointR3 = Point2f(pointRotateSetR[0][2], pointRotateSetR[1][2]);

			/*旋转拟合点变换至世界坐标系*/
#if	CalibrationMethod ==1
			Point2f pointLW1 = TransToWorldAxis(pointL1, invH1.L);
			Point2f pointLW2 = TransToWorldAxis(pointL2, invH1.L);
			Point2f pointLW3 = TransToWorldAxis(pointL3, invH1.L);

			Point2f pointRW1 = TransToWorldAxis(pointR1, invH1.R);
			Point2f pointRW2 = TransToWorldAxis(pointR2, invH1.R);
			Point2f pointRW3 = TransToWorldAxis(pointR3, invH1.R);
#elif CalibrationMethod ==2
			Point2f pointLW1 = CalWorldPoint(pointL1, ML);
			Point2f pointLW2 = CalWorldPoint(pointL2, ML);
			Point2f pointLW3 = CalWorldPoint(pointL3, ML);

			Point2f pointRW1 = CalWorldPoint(pointR1, MR);
			Point2f pointRW2 = CalWorldPoint(pointR2, MR);
			Point2f pointRW3 = CalWorldPoint(pointR3, MR);

#endif

			/*圆心角约束的旋转中心坐标计算*/
			Point2f rotatePoint1, rotatePoint2;
			//左旋转中心
			rotatePoint1 = GetAccuracyCirclePoint(pointLW1, pointLW2, pointLW3, THETA);
			//右旋转中心
			rotatePoint2 = GetAccuracyCirclePoint(pointRW1, pointRW2, pointRW3, THETA);

			/*存储标定结果*/
			FileStorage fs(".\\标定结果.xml", FileStorage::WRITE);
			fs << "invHL" << invH1.L << "invHR" << invH1.R
				<< "ML" << ML << "MR" << MR
				<< "rotatePoint1" << rotatePoint1 << "rotatePoint2" << rotatePoint2
				<< "matsetL" << matSetL << "matsetR" << matSetR
				<< "matTransWorldSet" << matTransWorldSet;
			fs.release();

			/*软件界面显示旋转中心坐标*/
			RotateX1.Format(TEXT("%0.5f"), rotatePoint1.x);
			RotateY1.Format(TEXT("%0.5f"), rotatePoint1.y);
			RotateX2.Format(TEXT("%0.5f"), rotatePoint2.x);
			RotateY2.Format(TEXT("%0.5f"), rotatePoint2.y);
			RotatePointList1.InsertItem(0, RotateX1);
			RotatePointList1.SetItemText(0, 1, RotateY1);
			RotatePointList1.InsertItem(1, RotateX2);
			RotatePointList1.SetItemText(1, 1, RotateY2);

			cout << "相机标定完成" << "\n" << endl;
		}
	}
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


/*批量计算+单相机对位*/
void CMFCApplication3Dlg::OnBnClickedButton1()
{
	maskImageL = imread(".\\L-12-8.bmp", 0);
	maskImageR = imread(".\\R-12-8.bmp", 0);

	FileStorage fs(".\\数据存储\\标定结果.xml", FileStorage::READ);
	Mat invHL, invHR;
	Mat ML, MR;
	Point2f rotatePoint1, rotatePoint2;
	fs["invHL"] >> invHL;
	fs["invHR"] >> invHR;
	fs["ML"] >> ML;
	fs["MR"] >> MR;
	fs["rotatePoint1"] >> rotatePoint1;
	fs["rotatePoint2"] >> rotatePoint2;

	Mat imagePixelCrossPointL;
	Mat imagePixelCrossPointR;
	//FileStorage fs2(".\\对位实验角点计算结果.xml", FileStorage::READ);
	//fs2["imagePixelCrossPointL"] >> imagePixelCrossPointL;
	//fs2["imagePixelCrossPointR"] >> imagePixelCrossPointR;


	/*对位实验*/
	int bmIndex = 1;
	vector<CrossPointInfo> resultLVector, resultRVector;
	vector<Point2f>pixelAxisSetL, pixelAxisSetR;
	vector<Point2f>worldAxisSetL, worldAxisSetR;

	//基准位置选择第1张图
	Mat bmL, bmR;
	//bmL = imread("E:\\数据集\\对位实验\\12-1.bmp", 0);
	//bmR = imread("E:\\数据集\\对位实验\\12-2.jpeg", 0);
	bmL = imread("E:\\数据集\\对位数据集\\对位2\\1-1.bmp", 0);
	bmR = imread("E:\\数据集\\对位数据集\\对位2\\1-2.jpeg", 0);

	string bmLStr = "基准图像左";
	string bmRStr = "基准图像右";
	RansacTest rl, rr;//后续实验调用，暂无用处
	Point2f bmCrossL = GetCrossBaseFastShapeL(bmL, maskImageL, rl, &bmLStr[0]).crossPoint;
	Point2f bmCrossR = GetCrossBaseFastShapeR(bmR, maskImageR, rr, &bmRStr[0]).crossPoint;

#if	CalibrationMethod ==1
	Point2f bmUniformCrossPointL = TransToWorldAxis(bmCrossL, invHL) - rotatePoint1;//左角点-左局部世界坐标系旋转中心坐标
	Point2f bmUniformCrossPointR = TransToWorldAxis(bmCrossR, invHR) - rotatePoint2;//右角点-右局部世界坐标系旋转中心坐标
#elif CalibrationMethod ==2
	Point2f bmUniformCrossPointL = CalWorldPoint(bmCrossL, ML) - rotatePoint1;//左角点-左局部世界坐标系旋转中心坐标
	Point2f bmUniformCrossPointR = CalWorldPoint(bmCrossR, MR) - rotatePoint2;//右角点-右局部世界坐标系旋转中心坐标
#endif

	Point2f bmUniformCenterPoint = (bmUniformCrossPointL + bmUniformCrossPointR) / 2;

	float bmTheta = atan((bmUniformCrossPointR.y - bmUniformCrossPointL.y)
		/ (bmUniformCrossPointR.x - bmUniformCrossPointL.x));


	CString pathSingleCameraTransError = CString(".\\实验结果\\1-7-对位2-直接求逆-单相机平移对位误差.csv");
	CString pathAlignmentError = CString(".\\实验结果\\1-7-对位2-直接求逆-对位误差.csv");
	CString pathResultLVector = CString(".\\实验结果\\1-7-对位2-直接求逆-左相机角点信息.csv");
	CString pathResultRVector = CString(".\\实验结果\\1-7-对位2-直接求逆-右相机角点信息.csv");
	CString pathPixelAxisSetL = CString(".\\实验结果\\1-7-对位2-直接求逆-左相机像素坐标.csv");
	CString pathPixelAxisSetR = CString(".\\实验结果\\1-7-对位2-直接求逆-右相机像素坐标.csv");
	CString pathWorldAxisSetL = CString(".\\实验结果\\1-7-对位2-直接求逆-左相机世界坐标.csv");
	CString pathWorldAxisSetR = CString(".\\实验结果\\1-7-对位2-直接求逆-右相机世界坐标.csv");
	CString pathInstruction = CString(".\\实验结果\\1-7-对位2-直接求逆-对位指令.csv");
//	char srcImagePathL[500], srcImagePathR[500];
//	for (int index = 1; index <= 34; index++)
//	{
//		//sprintf_s(srcImagePathL, "E:\\数据集\\对位实验\\%d-1.bmp", index);
//		//sprintf_s(srcImagePathR, "E:\\数据集\\对位实验\\%d-2.jpeg", index);
//		//sprintf_s(srcImagePathL, "E:\\数据集\\对位2\\%d-1.bmp", index);
//		//sprintf_s(srcImagePathR, "E:\\数据集\\对位2\\%d-2.jpeg", index);
//		//sprintf_s(srcImagePathL, "E:\\数据集\\后盖标定采图\\BD\\%d-1.bmp", index);
//		//sprintf_s(srcImagePathR, "E:\\数据集\\后盖标定采图\\BD\\%d-2.bmp", index);
//		//sprintf_s(srcImagePathL, "E:\\数据集\\3号台直角盖板图像\\2\\%d-1.bmp", index);
//		//sprintf_s(srcImagePathR, "E:\\数据集\\3号台直角盖板图像\\2\\%d-2.jpeg", index);
//		sprintf_s(srcImagePathL, "E:\\数据集\\对位数据集\\对位2\\%d-1.bmp", index);
//		sprintf_s(srcImagePathR, "E:\\数据集\\对位数据集\\对位2\\%d-2.jpeg", index);
//		//sprintf_s(srcImagePathL, "E:\\数据集\\对位数据集\\对位实验\\%d-1.bmp", index);
//		//sprintf_s(srcImagePathR, "E:\\数据集\\对位数据集\\对位实验\\%d-2.jpeg", index);
//	
//		Mat srcImageL = imread(srcImagePathL, 0);
//		Mat srcImageR = imread(srcImagePathR, 0);
//
//		RansacTest rl, rr;//后续实验调用，暂无用处
//		CrossPointInfo resultL, resultR;
//		Point2f resultPointL, resultPointR;
//		resultL = GetCrossBaseFastShapeL(srcImageL, maskImageL, rl, srcImagePathL);
//		resultR = GetCrossBaseFastShapeR(srcImageR, maskImageR, rr, srcImagePathR);
//		resultL.index = index;
//		resultR.index = index;
//		resultPointL = resultL.crossPoint;
//		resultPointR = resultR.crossPoint;
//		//角点像素坐标变换至局部世界坐标系
//#if	CalibrationMethod ==1
//		Point2f crossPointWorldL = TransToWorldAxis(resultPointL, invHL);
//		Point2f crossPointWorldR = TransToWorldAxis(resultPointR, invHR);
//#elif CalibrationMethod ==2
//		Point2f crossPointWorldL = CalWorldPoint(resultPointL, ML);
//		Point2f crossPointWorldR = CalWorldPoint(resultPointR, MR);
//#endif
//		//角点信息
//		resultLVector.push_back(resultL);
//		resultRVector.push_back(resultR);
//		//角点像素坐标存储
//		pixelAxisSetL.push_back(resultPointL);
//		pixelAxisSetR.push_back(resultPointR);
//		//角点世界坐标存储
//		worldAxisSetL.push_back(crossPointWorldL);
//		worldAxisSetR.push_back(crossPointWorldR);
//	}
//
	string csvPathL(".\\实验结果\\1-7-对位2-直接求逆-左相机角点信息.csv");
	string csvPathR(".\\实验结果\\1-7-对位2-直接求逆-右相机角点信息.csv");
	RestoreInfo(csvPathL, resultLVector, pixelAxisSetL);
	RestoreInfo(csvPathR, resultRVector, pixelAxisSetR);
	for (int i = 0; i < resultLVector.size(); i++)
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

	SaveCrossInfo(resultLVector, pathResultLVector);
	SaveCrossInfo(resultRVector, pathResultRVector);
	SavePointSet(pixelAxisSetL, pathPixelAxisSetL);
	SavePointSet(pixelAxisSetR, pathPixelAxisSetR);
	SavePointSet(worldAxisSetL, pathWorldAxisSetL);
	SavePointSet(worldAxisSetR, pathWorldAxisSetR);


	vector<tuple<float, float, int, int>>errorInfo;
	vector<tuple<float, float, float, int, int>>instruction;
	for (int i = 0; i < worldAxisSetL.size(); i++)
	{
		/*分别减去各自的旋转中心坐标，变换至以旋转中心为原点的统一世界坐标系*/
		Point2f testUniformCrossPointL = worldAxisSetL[i] - rotatePoint1;//左角点-左局部世界坐标系旋转中心坐标
		Point2f testUniformCrossPointR = worldAxisSetR[i] - rotatePoint2;//右角点-右局部世界坐标系旋转中心坐标
		Point2f testUniformCenterPoint = (testUniformCrossPointL + testUniformCrossPointR) / 2;

		float testTheta = atan((testUniformCrossPointR.y - testUniformCrossPointL.y)
			/ (testUniformCrossPointR.x - testUniformCrossPointL.x));

		float theta = -bmTheta + testTheta;


		float rotateBmLX = cos(theta)*bmUniformCrossPointL.x - sin(theta)*bmUniformCrossPointL.y;
		float rotateBmLY = sin(theta)*bmUniformCrossPointL.x + cos(theta)*bmUniformCrossPointL.y;

		float rotateBmRX = cos(theta)*bmUniformCrossPointR.x - sin(theta)*bmUniformCrossPointR.y;
		float rotateBmRY = sin(theta)*bmUniformCrossPointR.x + cos(theta)*bmUniformCrossPointR.y;

		float rotateBmCX = cos(theta)*bmUniformCenterPoint.x - sin(theta)*bmUniformCenterPoint.y;
		float rotateBmCY = sin(theta)*bmUniformCenterPoint.x + cos(theta)*bmUniformCenterPoint.y;

		Point2f rbmL(rotateBmLX, rotateBmLY);
		Point2f rbmR(rotateBmRX, rotateBmRY);
		Point2f rbmC(rotateBmCX, rotateBmCY);

		Point2f commandL = rbmL - testUniformCrossPointL;
		Point2f commandR = rbmR - testUniformCrossPointR;
		Point2f commandC = rbmC - testUniformCenterPoint;

		/*计算控制指令*/
		float errorLX = commandL.x - round(commandL.x);
		float errorLY = commandL.y - round(commandL.y);
		float errorRX = commandR.x - round(commandR.x);
		float errorRY = commandR.y - round(commandR.y);
		float errorCX = commandC.x - round(commandC.x);
		float errorCY = commandC.y - round(commandC.y);

		float commandX, commandY;
		commandX = commandC.x;
		commandY = commandC.y;

		tuple<float, float, int, int>temp;
		get<0>(temp) = commandX - round(commandX);
		get<1>(temp) = commandY - round(commandY);
		get<2>(temp) = bmIndex;
		get<3>(temp) = resultLVector[i].index ;
		errorInfo.push_back(temp);

		tuple<float, float, float, int, int>tempInstruction;
		get<0>(tempInstruction) = commandX;
		get<1>(tempInstruction) = commandY;
		get<2>(tempInstruction) = theta * 180 / PI;
		get<3>(tempInstruction) = bmIndex;
		get<4>(tempInstruction) = resultLVector[i].index;
		instruction.push_back(tempInstruction);
	}


	/*单相机对位*/
#if	CalibrationMethod ==1
	Point2f bmUniformCrossPointL_U = TransToWorldAxis(resultLVector[bmIndex - 1].ptU2, invHL) - rotatePoint1;
	Point2f bmUniformCrossPointR_U = TransToWorldAxis(resultRVector[bmIndex - 1].ptU2, invHR) - rotatePoint2;
#elif CalibrationMethod ==2
	Point2f bmUniformCrossPointL_U = CalWorldPoint(resultLVector[bmIndex - 1].ptU2, ML) - rotatePoint1;
	Point2f bmUniformCrossPointR_U = CalWorldPoint(resultRVector[bmIndex - 1].ptU2, MR) - rotatePoint2;
#endif

	float bmThetaL = atan((bmUniformCrossPointL_U.y - bmUniformCrossPointL.y)
		/ (bmUniformCrossPointL_U.x - bmUniformCrossPointL.x));
	float bmThetaR = atan((bmUniformCrossPointR_U.y - bmUniformCrossPointR.y)
		/ (bmUniformCrossPointR_U.x - bmUniformCrossPointR.x));


	//左相机对位
	//vector<tuple<float, float>>errorInfoL;
	vector<tuple<CrossPointInfo, CrossPointInfo, float, float>>errorInfoL;
	for (int i = 0; i < worldAxisSetL.size(); i++)
	{
		Point2f testUniformCrossPointL = worldAxisSetL[i] - rotatePoint1;

#if	CalibrationMethod ==1
		Point2f testUniformCrossPointL_U = TransToWorldAxis(resultLVector[i].ptU2, invHL) - rotatePoint1;
#elif CalibrationMethod ==2
		Point2f testUniformCrossPointL_U = CalWorldPoint(resultLVector[i].ptU2, ML) - rotatePoint1;
#endif

		float testThetaL = atan((testUniformCrossPointL_U.y - testUniformCrossPointL.y)
			/ (testUniformCrossPointL_U.x - testUniformCrossPointL.x));

		float thetaL = -bmThetaL + testThetaL;

		//计算偏移量
		//@1:左角点
		float uTCRotatePointLX = cos(thetaL)*(bmUniformCrossPointL.x) - sin(thetaL)*(bmUniformCrossPointL.y);
		float uTCRotatePointLY = sin(thetaL)*(bmUniformCrossPointL.x) + cos(thetaL)*(bmUniformCrossPointL.y);

		float commandXL = -uTCRotatePointLX + bmUniformCrossPointL.x;
		float commandYL = -uTCRotatePointLY + bmUniformCrossPointL.y;

		float errorXL = commandXL - round(commandXL);
		float errorYL = commandYL - round(commandYL);

		tuple<CrossPointInfo, CrossPointInfo, float, float>temp;
		get<0>(temp) = resultLVector[i];
		get<1>(temp) = resultLVector[bmIndex-1];
		get<2>(temp) = errorXL;
		get<3>(temp) = errorYL;

		errorInfoL.push_back(temp);
	}

	//右相机对位误差
	//vector<tuple<float, float>>errorInfoR;
	vector<tuple<CrossPointInfo, CrossPointInfo,float,float>>errorInfoR;
	for (int i = 0; i < resultRVector.size(); i++)
	{
		Point2f testUniformCrossPointR = worldAxisSetR[i] - rotatePoint2;

#if	CalibrationMethod ==1
		Point2f testUniformCrossPointR_U = TransToWorldAxis(resultRVector[i].ptU2, invHR) - rotatePoint2;
#elif CalibrationMethod ==2
		Point2f testUniformCrossPointR_U = CalWorldPoint(resultRVector[i].ptU2, MR) - rotatePoint2;
#endif

		float testThetaR = atan((testUniformCrossPointR_U.y - testUniformCrossPointR.y)
			/ (testUniformCrossPointR_U.x - testUniformCrossPointR.x));

		float thetaR = -bmThetaR + testThetaR;

		//计算偏移量
		float uTCRotatePointRX = cos(thetaR)*(bmUniformCrossPointR.x) - sin(thetaR)*(bmUniformCrossPointR.y);
		float uTCRotatePointRY = sin(thetaR)*(bmUniformCrossPointR.x) + cos(thetaR)*(bmUniformCrossPointR.y);


		float commandXR = -uTCRotatePointRX + bmUniformCrossPointR.x;
		float commandYR = -uTCRotatePointRY + bmUniformCrossPointR.y;

		float errorXR = commandXR - round(commandXR);
		float errorYR = commandYR - round(commandYR);

		tuple<CrossPointInfo, CrossPointInfo, float, float>temp;
		get<0>(temp) = resultRVector[i];
		get<1>(temp) = resultRVector[bmIndex-1];
		get<2>(temp) = errorXR;
		get<3>(temp) = errorYR;

		errorInfoR.push_back(temp);
	}


	/*单相机平移位置组的误差计算*/
	vector<tuple<int, int, float, float,float,float, float, float>>errorTranslationL, errorTranslationR;
	//left
	for (int i = 0; i < resultLVector.size(); i++)
	{
		CrossPointInfo positionI = resultLVector[i];
		Point2f ptWI = worldAxisSetL[i];
		Point2f ptPixelI = pixelAxisSetL[i];
		for (int j = i + 1; j < resultLVector.size(); j++)
		{
			CrossPointInfo positionJ = resultLVector[j];
			if (abs(positionI.thetaU - positionJ.thetaU) < 0.5)
			{
				Point2f ptWJ = worldAxisSetL[j];
				Point2f ptPixelJ = pixelAxisSetL[j];

				Point2f deltaW = ptWI - ptWJ;
				Point2f deltaP = ptPixelJ - ptPixelI;

				tuple<int, int, float, float, float, float, float, float> temp;
				get<0>(temp) = positionI.index;
				get<1>(temp) = positionJ.index;
				get<2>(temp) = deltaW.x;
				get<3>(temp) = deltaW.y;
				get<4>(temp) = deltaP.x;
				get<5>(temp) = deltaP.y;
				get<6>(temp) = positionI.thetaD;
				get<7>(temp) = positionJ.thetaD;

				errorTranslationL.push_back(temp);
			}
		}
	}

	//right
	for (int i = 0; i < resultRVector.size(); i++)
	{
		CrossPointInfo positionI = resultRVector[i];
		Point2f ptWI = worldAxisSetR[i];
		Point2f ptPixelI = pixelAxisSetR[i];
		for (int j = i + 1; j < resultRVector.size(); j++)
		{
			CrossPointInfo positionJ = resultRVector[j];
			if (abs(positionI.thetaU - positionJ.thetaU) < 0.5)
			{
				Point2f ptWJ = worldAxisSetR[j];
				Point2f ptPixelJ = pixelAxisSetR[j];

				Point2f deltaW = ptWI - ptWJ;
				Point2f deltaP = ptPixelJ - ptPixelI;

				tuple<int, int, float,float,float, float,float,float> temp;
				get<0>(temp) = positionI.index;
				get<1>(temp) = positionJ.index;
				get<2>(temp) = deltaW.x;
				get<3>(temp) = deltaW.y;
				get<4>(temp) = deltaP.x;
				get<5>(temp) = deltaP.y;
				get<6>(temp) = positionI.thetaD;
				get<7>(temp) = positionJ.thetaD;

				errorTranslationR.push_back(temp);
			}
		}
	}

	saveSingleCameraTransError(errorTranslationL, errorTranslationR, pathSingleCameraTransError);
	saveAlignmentError(errorInfo, errorInfoL, errorInfoR, pathAlignmentError);
	saveInstruction(instruction, pathInstruction);

	cout << "finish all calculation" << "\n" << endl;
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

	ofstream outfile;
	outfile.open(strPathName, ios::trunc);
	//tuple<int, float, float, float> curResult1;
	for (int i = 0; i < resultText1.size(); i++)
	{
		outfile << "index:" << get<0>(resultText1[i]) <<
			"  " << "X: " << get<1>(resultText1[i]) <<
			"  " << "Y: " << get<2>(resultText1[i]) <<
			"  " << "Theta: " << get<3>(resultText1[i]) << "\n";
	}
	outfile.close();//关闭文件，保存文件

	cout << "save result" << "\n" << endl;
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


void CAboutDlg::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码
}
