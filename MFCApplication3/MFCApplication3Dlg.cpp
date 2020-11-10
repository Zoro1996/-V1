
// MFCApplication3Dlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "MFCApplication3.h"
#include "MFCApplication3Dlg.h"
#include "afxdialogex.h"
#include "MyFunction.h"
#include "resource.h"
#include<stdio.h>
#include <fstream>
using namespace std;



#define FLAG 0

#define PI 3.14159265

//float pointWorldSet[4][9] = {
//	0, 4, 8, 8,   4,   0,   0, 4, 8,
//	0, 0, 0, 4.5, 4.5, 4.5, 9, 9, 9,
//	0, 0, 0, 0,   0,   0,   0, 0, 0,
//	1, 1, 1, 1,   1,   1,   1, 1, 1
//};
float pointWorldSet[4][9] = {
	  -4,    0,    4, 4, 0, -4,  -4,   0,   4,
	-4.5, -4.5, -4.5, 0, 0,  0, 4.5, 4.5, 4.5,
	   0,    0,    0, 0, 0,  0,   0,   0,   0,
	   1,    1,    1, 1, 1,  1,   1,   1,   1
};

//float pointWorldSet[4][9] = {
//	  -3,   0,   3,  3,  0,  -3,  -3,   0,   3,
//	  -3,  -3,  -3,  0,  0,   0,   3,   3,   3,
//	   0,   0,   0,  0,  0,   0,   0,   0,   0,
//	   1,   1,   1,  1,  1,   1,   1,   1,   1
//};

#ifdef _DEBUG
#define new DEBUG_NEW
#endif



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
	namedWindow("view1", WINDOW_AUTOSIZE);
	HWND hWnd = (HWND)cvGetWindowHandle("view1");
	HWND hParent = ::GetParent(hWnd);
	::SetParent(hWnd, GetDlgItem(PictureViewer1)->m_hWnd);
	::ShowWindow(hParent, SW_HIDE);

	namedWindow("view2", WINDOW_AUTOSIZE);
	HWND hWnd2 = (HWND)cvGetWindowHandle("view2");
	HWND hParent2 = ::GetParent(hWnd2);
	::SetParent(hWnd2, GetDlgItem(PictureViewer2)->m_hWnd);
	::ShowWindow(hParent2, SW_HIDE);

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
	CString str2[] = {TEXT("X"),TEXT("Y"),TEXT("Theta") };
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
	maskL = imread(str, 0);
	maskRGBL = imread(str, 1);
	ShowPic_MaskL(maskL);
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
	maskR = imread(str, 0);
	maskRGBR = imread(str, 1);
	ShowPic_MaskR(maskR);
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
	ShowPic_bmImageViweR(bmImageR);
}


void CMFCApplication3Dlg::OnBnClickedAlignmentWo()
{
	index++;

	/*对位开始*/
	/*计算基准位姿*/
	bmPosition = CalPosition(bmImageL, bmImageR, maskL, maskR, invH1, deltaX1, deltaY1);

	/*计算待测工件位姿*/
	Rect rectTestL, rectTestR;

	rectTestL = Rect(0, 0, 3086, testImageL.rows);
	testImageL(rectTestL).copyTo(testImageL);

	rectTestR = Rect(0, 0, 2400, testImageR.rows);
	testImageR(rectTestR).copyTo(testImageR);
	testPosition = CalPosition(testImageL, testImageR, maskL, maskR, invH1, deltaX1, deltaY1);

	/*运动指令*/
	instruction1 = GetInstruction(bmPosition, testPosition, rotatePoint1);

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


void CMFCApplication3Dlg::OnBnClickedCameracalibation()
{
	char srcImagePathL[500], srcImagePathR[500];

	/*计算单相机的平移标定角点的图像像素坐标*/
	Mat srcImageRectL, srcImageRectR;
	Rect rectL, rectR;
	float pointTransSetL[3][9], pointTransSetR[3][9];//角点图像像素坐标
	for (int index = 1; index < 10; index++)
	{
		sprintf_s(srcImagePathL, "F:\\数据集\\标定\\TEST-BD\\BD\\ImgsL\\T-L-%d.jpeg", index);
		sprintf_s(srcImagePathR, "F:\\数据集\\标定\\TEST-BD\\BD\\ImgsR\\T-R-%d.jpeg", index);

		//Mat srcImageL = imread(srcImagePathL, 0);
		//Point2f resultPointL = CrossInAlignmentSystem(srcImageL, maskL);
		//Mat srcImageR = imread(srcImagePathR, 0);
		//Point2f resultPointR = CrossInAlignmentSystem(srcImageR, maskR);

		Mat srcL = imread(srcImagePathL, 0);
		rectL = Rect(0, 0, 3000, srcL.rows);
		srcL(rectL).copyTo(srcImageRectL);
		Point2f resultPointL = GetCrossPoint(srcImageRectL);
		Mat srcR = imread(srcImagePathR, 0);
		rectR = Rect(0, 0, 3000, srcR.rows);
		srcR(rectR).copyTo(srcImageRectR);
		Point2f resultPointR = GetCrossPoint(srcImageRectR);

		pointTransSetL[0][index - 1] = resultPointL.x;
		pointTransSetL[1][index - 1] = resultPointL.y;
		pointTransSetL[2][index - 1] = 1;


		pointTransSetR[0][index - 1] = resultPointR.x;
		pointTransSetR[1][index - 1] = resultPointR.y;
		pointTransSetR[2][index - 1] = 1;

		//cvtColor(srcImageR, srcImageR, COLOR_GRAY2BGR);
		//circle(srcImageR, resultPoint, 8, Scalar(0, 0, 255), 8);
		//cvtColor(srcImageL, srcImageL, COLOR_GRAY2BGR);
		//circle(srcImageL, resultPoint, 8, Scalar(0, 0, 255), 8);
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
	//cvtColor(matTransWorldSet, matTransWorldSet, CV_BGR2GRAY);
	for (int y = 0; y < 4; ++y) {
		for (int x = 0; x < 9; ++x) {
			matTransWorldSet.at<float>(y, x) = pointWorldSet[y][x];
		}
	}

	/*计算单应性矩阵*/
	invH1.L = matTransWorldSet * imatSetL;
	invH1.R = matTransWorldSet * imatSetR;

	float pointRotateSetL[3][3], pointRotateSetR[3][3];
	for (int index = 1; index < 4; index++)
	{
		sprintf_s(srcImagePathL, "F:\\数据集\\标定\\TEST-BD\\BD\\ImgsL\\rotate-L-%d.jpeg", index);
		sprintf_s(srcImagePathR, "F:\\数据集\\标定\\TEST-BD\\BD\\ImgsR\\rotate-R-%d.jpeg", index);

		Mat srcL = imread(srcImagePathL, 0);
		rectL = Rect(0, 0, 3000, srcL.rows);
		srcL(rectL).copyTo(srcImageRectL);
		Point2f resultPointL = GetCrossPoint(srcImageRectL);
		Mat srcR = imread(srcImagePathR, 0);
		rectR = Rect(0, 0, 3000, srcR.rows);
		srcR(rectR).copyTo(srcImageRectR);
		Point2f resultPointR = GetCrossPoint(srcImageRectR);

		//Mat srcImageL = imread(srcImagePathL, 0);
		//Point2f resultPointL = CrossInAlignmentSystem(srcImageL, maskL);
		//Mat srcImageR = imread(srcImagePathR, 0);
		//Point2f resultPointR = CrossInAlignmentSystem(srcImageR, maskR);

		//circle(srcL, resultPointL, 8, Scalar(0), 8);
		//circle(srcR, resultPointR, 8, Scalar(0), 8);
		//srcL.at<uchar>(resultPointL.y, resultPointL.x) = 0;
		//srcR.at<uchar>(resultPointR.y, resultPointR.x) = 0;

		pointRotateSetL[0][index - 1] = resultPointL.x;
		pointRotateSetL[1][index - 1] = resultPointL.y;
		pointRotateSetL[2][index - 1] = 1;

		pointRotateSetR[0][index - 1] = resultPointR.x;
		pointRotateSetR[1][index - 1] = resultPointR.y;
		pointRotateSetR[2][index - 1] = 1;

		//cvtColor(srcL, srcL, COLOR_GRAY2BGR);
		//circle(srcL, resultPointL, 8, Scalar(0, 0, 255), 8);
		//cvtColor(srcR, srcR, COLOR_GRAY2BGR);
		//circle(srcR, resultPointR, 8, Scalar(0, 0, 255), 8);
		//namedWindow(srcImagePathL, 0);
		//imshow(srcImagePathL, srcL);
		//namedWindow(srcImagePathR, 0);
		//imshow(srcImagePathR, srcR);
	}

	Point2f pointL1 = Point2f(pointRotateSetL[0][0], pointRotateSetL[1][0]);
	Point2f pointL2 = Point2f(pointRotateSetL[0][1], pointRotateSetL[1][1]);
	Point2f pointL3 = Point2f(pointRotateSetL[0][2], pointRotateSetL[1][2]);
	Point2f pointR1 = Point2f(pointRotateSetR[0][0], pointRotateSetR[1][0]);
	Point2f pointR2 = Point2f(pointRotateSetR[0][1], pointRotateSetR[1][1]);
	Point2f pointR3 = Point2f(pointRotateSetR[0][2], pointRotateSetR[1][2]);

	/*根据最小二乘法计算旋转中心centerL,centerR*/
	CircleData centerL = findCircle2(pointL1, pointL2, pointL3);
	CircleData centerR = findCircle2(pointR1, pointR2, pointR3);

	circlePoint1.L = centerL.center;
	circlePoint1.R = centerR.center;

	centerWorldL1.center = TransToWorldAxis(circlePoint1.L, invH1.L);
	centerWorldR1.center = TransToWorldAxis(circlePoint1.R, invH1.R);
	rotatePoint1 = centerWorldL1.center;

	deltaX1 = centerWorldR1.center.x - centerWorldL1.center.x;
	deltaY1 = centerWorldR1.center.y - centerWorldL1.center.y;
	
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
	// TODO: 在此添加控件通知处理程序代码
	//resultPosition2 = CalPosition(secImageResultL, secImageResultR, maskL, maskR, invH1, deltaX, deltaY);
	//deltaXeWorld = bmPosition.uniformCenterPoint.x - resultPosition2.uniformCenterPoint.x;
	//deltaYeWorld = bmPosition.uniformCenterPoint.y - resultPosition2.uniformCenterPoint.y;
	//deltaThetaeWorld = bmPosition.theta - resultPosition2.theta;
	//CString X, Y, Theta;
	//X.Format(TEXT("%0.5f"), deltaXeWorld);
	//Y.Format(TEXT("%0.5f"), deltaYeWorld);
	//Theta.Format(TEXT("%0.5f"), deltaThetaeWorld);
	//RectifyErrorList.InsertItem(0, X);
	//RectifyErrorList.SetItemText(0, 1, Y);
	//RectifyErrorList.SetItemText(0, 2, Theta);
}


void CMFCApplication3Dlg::OnBnClickedButton1()
{
	/*对位开始*/
	/*计算基准位姿*/
	bmPosition = CalPosition(bmImageL, bmImageR, maskL, maskR, invH2, deltaX2, deltaY2);

	/*计算待测工件位姿*/
	Rect rectTestL, rectTestR;

	rectTestL = Rect(0, 0, 3086, testImageL.rows);
	testImageL(rectTestL).copyTo(testImageL);

	rectTestR = Rect(0, 0, 2400, testImageR.rows);
	testImageR(rectTestR).copyTo(testImageR);
	testPosition = CalPosition(testImageL, testImageR, maskL, maskR, invH2, deltaX2, deltaY2);

	/*运动指令*/
	instruction2 = GetInstruction(bmPosition, testPosition, rotatePoint2);

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
	ofstream outfile1,outfile2;
	//outfile1.open("C:\\Users\\dell\\Desktop\\result1.txt", ios::binary | ios::app | ios::in | ios::out);
	//outfile2.open("C:\\Users\\dell\\Desktop\\result2.txt", ios::binary | ios::app | ios::in | ios::out);

	outfile1.open("C:\\Users\\dell\\Desktop\\result1.txt", ios::trunc);
	outfile2.open("C:\\Users\\dell\\Desktop\\result2.txt", ios::trunc);

	tuple<int, float, float, float> curResult1, curResult2;
	for (int i = 0; i < resultText1.size(); i++)
	{
		outfile1 << "index:" << get<0>(resultText1[i]) <<
			"  " << "X: " << get<1>(resultText1[i]) <<
			"  " << "Y: " << get<2>(resultText1[i]) <<
			"  " << "Theta: " << get<3>(resultText1[i]) <<"\n";

		outfile2 << "index:" << get<0>(resultText2[i]) <<
			"  " << "X: " << get<1>(resultText2[i]) <<
			"  " << "Y: " << get<2>(resultText2[i]) <<
			"  " << "Theta: " << get<3>(resultText2[i]) <<"\n";
	}
	outfile1.close();//关闭文件，保存文件。
	outfile2.close();//关闭文件，保存文件。
}


void CMFCApplication3Dlg::OnBnClickedButton7()
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
	secTestImageL = imread(str, 0);
	ShowPic_secTestViewL(secTestImageL);
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
	secTestImageR = imread(str, 0);
	ShowPic_secTestViewR(secTestImageR);
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
	char srcImagePathL[500], srcImagePathR[500];

	/*计算单相机的平移标定角点的图像像素坐标*/
	Mat srcImageL, srcImageRectL, srcImageR, srcImageRectR;
	Rect rectL, rectR;
	float pointTransSetL[3][9], pointTransSetR[3][9];//角点图像像素坐标
	for (int index = 1; index < 10; index++)
	{
		sprintf_s(srcImagePathL, "F:\\数据集\\标定\\TEST-BD\\BD\\ImgsL\\T-L-%d.jpeg", index);
		sprintf_s(srcImagePathR, "F:\\数据集\\标定\\TEST-BD\\BD\\ImgsR\\T-R-%d.jpeg", index);

		Mat srcL = imread(srcImagePathL, 0);
		rectL = Rect(0, 0, 3000, srcL.rows);
		srcL(rectL).copyTo(srcImageRectL);
		Mat srcR = imread(srcImagePathR, 0);
		rectR = Rect(0, 0, 3000, srcR.rows);
		srcR(rectR).copyTo(srcImageRectR);

		Point2f resultPointL = GetCrossPoint(srcImageRectL);
		pointTransSetL[0][index - 1] = resultPointL.x;
		pointTransSetL[1][index - 1] = resultPointL.y;
		pointTransSetL[2][index - 1] = 1;

		Point2f resultPointR = GetCrossPoint(srcImageRectR);
		pointTransSetR[0][index - 1] = resultPointR.x;
		pointTransSetR[1][index - 1] = resultPointR.y;
		pointTransSetR[2][index - 1] = 1;

		//cvtColor(srcImageR, srcImageR, COLOR_GRAY2BGR);
		//circle(srcImageR, resultPoint, 8, Scalar(0, 0, 255), 8);
		//cvtColor(srcImageL, srcImageL, COLOR_GRAY2BGR);
		//circle(srcImageL, resultPoint, 8, Scalar(0, 0, 255), 8);

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
	//cvtColor(matTransWorldSet, matTransWorldSet, CV_BGR2GRAY);
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
		sprintf_s(srcImagePathL, "F:\\数据集\\标定\\TEST-BD\\BD\\ImgsL\\rotate-L-%d.jpeg", index);
		sprintf_s(srcImagePathR, "F:\\数据集\\标定\\TEST-BD\\BD\\ImgsR\\rotate-R-%d.jpeg", index);

		Mat srcL = imread(srcImagePathL, 0);
		rectL = Rect(0, 0, 3000, srcL.rows);
		srcL(rectL).copyTo(srcImageL);
		Point2f resultPointL = GetCrossPoint(srcImageL);
		Mat srcR = imread(srcImagePathR, 0);
		rectR = Rect(0, 0, 3000, srcR.rows);
		srcR(rectR).copyTo(srcImageR);
		Point2f resultPointR = GetCrossPoint(srcImageR);

		//circle(srcL, resultPointL, 8, Scalar(0), 8);
		//circle(srcR, resultPointR, 8, Scalar(0), 8);
		//srcL.at<uchar>(resultPointL.y, resultPointL.x) = 0;
		//srcR.at<uchar>(resultPointR.y, resultPointR.x) = 0;

		pointRotateSetL[0][index - 1] = resultPointL.x;
		pointRotateSetL[1][index - 1] = resultPointL.y;
		pointRotateSetL[2][index - 1] = 1;

		pointRotateSetR[0][index - 1] = resultPointR.x;
		pointRotateSetR[1][index - 1] = resultPointR.y;
		pointRotateSetR[2][index - 1] = 1;

		//cvtColor(srcL, srcL, COLOR_GRAY2BGR);
		//circle(srcL, resultPointL, 8, Scalar(0, 0, 255), 8);
		//cvtColor(srcR, srcR, COLOR_GRAY2BGR);
		//circle(srcR, resultPointR, 8, Scalar(0, 0, 255), 8);

		//namedWindow(srcImagePathL, 0);
		//imshow(srcImagePathL, srcL);
		//namedWindow(srcImagePathR, 0);
		//imshow(srcImagePathR, srcR);
	}

	Point2f pointL1 = Point2f(pointRotateSetL[0][0], pointRotateSetL[1][0]);
	Point2f pointL2 = Point2f(pointRotateSetL[0][1], pointRotateSetL[1][1]);
	Point2f pointL3 = Point2f(pointRotateSetL[0][2], pointRotateSetL[1][2]);
	Point2f pointR1 = Point2f(pointRotateSetR[0][0], pointRotateSetR[1][0]);
	Point2f pointR2 = Point2f(pointRotateSetR[0][1], pointRotateSetR[1][1]);
	Point2f pointR3 = Point2f(pointRotateSetR[0][2], pointRotateSetR[1][2]);

	/*基于固定圆心角约束的最小二乘法计算旋转中心testCenterL,testCenterR*/
	Point2f testCenterL1 = findCircle1(pointL1, pointL2, 4 * PI / 180);
	Point2f testCenterL2 = findCircle1(pointL2, pointL3, 4 * PI / 180);
	Point2f testCenterL = Point2f((testCenterL1.x + testCenterL2.x) / 2,
		(testCenterL1.y + testCenterL2.y) / 2);
	//Point2f testCenterL3 = findCircle1(pointL1, pointL3, 8 * PI / 180);
	//Point2f testCenterL = Point2f((testCenterL1.x + testCenterL2.x + testCenterL3.x) / 3,
	//	(testCenterL1.y + testCenterL2.y + testCenterL3.y) / 3);

	Point2f testCenterR1 = findCircle1(pointR1, pointR2, 4 * PI / 180);
	Point2f testCenterR2 = findCircle1(pointR2, pointR3, 4 * PI / 180);
	Point2f testCenterR = Point2f((testCenterR1.x + testCenterR2.x) / 2,
		(testCenterR1.y + testCenterR2.y) / 2);
	//Point2f testCenterR3 = findCircle1(pointR1, pointR3, 8 * PI / 180);
	//Point2f testCenterR = Point2f((testCenterR1.x + testCenterR2.x + testCenterR3.x) / 3,
	//	(testCenterR1.y + testCenterR2.y + testCenterR3.y) / 3);

	circlePoint2.L = testCenterL;
	circlePoint2.R = testCenterR;

	centerWorldL2.center = TransToWorldAxis(circlePoint2.L, invH2.L);
	centerWorldR2.center = TransToWorldAxis(circlePoint2.R, invH2.R);
	rotatePoint2 = centerWorldL2.center;

	deltaX2 = centerWorldR2.center.x - centerWorldL2.center.x;
	deltaY2 = centerWorldR2.center.y - centerWorldL2.center.y;

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
