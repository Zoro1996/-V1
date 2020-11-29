
// MFCApplication3Dlg.h: 头文件
//

#pragma once
#include "pch.h"
#include "MyFunction.h"
#include <iostream>  
#include <fstream>
#include <string>
#include <vector>
#include <iterator>
#include "afxwin.h"

using namespace std;

// CMFCApplication3Dlg 对话框
class CMFCApplication3Dlg : public CDialogEx
{
// 构造
public:
	CMFCApplication3Dlg(CWnd* pParent = nullptr);	// 标准构造函数

	//AllocConsole();
	//freopen("CON", "r", stdin);
	//freopen("CON", "w", stdout);
	//freopen("CON", "w", stderr);

	//cout << "启动控制台/n/n";

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCAPPLICATION3_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:

	Mat maskL;
	Mat maskRGBL;
	Mat maskR;
	Mat maskRGBR;
	Mat srcImageL;
	Mat srcImageR;
	Mat testImageL;
	Mat testImageR;
	Mat bmImageL;
	Mat bmImageR;
	Mat resultImageL, resultImageR;

	Mat maskL1;
	Mat maskL2;
	Mat maskR1;
	Mat maskR2;

	//Mat maskImageL;
	//Mat maskImageR;

	Mat secTestImageL;
	Mat secTestImageR;

	Mat secImageResultL;
	Mat secImageResultR;

	Mat HL, HR;

	CString RotateX1, RotateY1;
	CString RotateX2, RotateY2;

	CircleData centerWorldL1, centerWorldR1;
	CircleData centerWorldL2, centerWorldR2;

	int index = 0;

	float deltaXeWorld;
	float deltaYeWorld;
	float deltaThetaeWorld;
	float deltaX1, deltaY1;
	float deltaX2, deltaY2;

	vector<tuple<int, float, float, float>> resultText1, resultText2;

	Point2f rotatePoint1, rotatePoint2;

	HomographyStruct invH1,invH2;
	//Position bmPosition, testPosition, resultPosition, resultPosition2;

	CenterPoint circlePoint1,circlePoint2;
	//CircleData circlePointWorldL1, circlePointWorldR1;
	//CircleData circlePointWorldL2, circlePointWorldR2;
	ControlInstruction instruction1, instruction2;

	Point2f RectifiedRCenter;

	void ShowPic_MaskL(Mat input_1);
	void ShowPic_MaskR(Mat input_2);
	void ShowPic_testImageL(Mat input);
	void ShowPic_testImageR(Mat input);
	void ShowPic_bmImageViweL(Mat input);
	void ShowPic_bmImageViweR(Mat input);
	void ShowPic_resultImageViweL(Mat input);
	void ShowPic_resultImageViweR(Mat input);
	void ShowPic_secResultViewL(Mat input);
	void ShowPic_secResultViewR(Mat input);
	void ShowPic_secTestViewL(Mat input);
	void ShowPic_secTestViewR(Mat input);


	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnStnClickedPictureviewer1();
	afx_msg void OnStnClickedPictureviewer2();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedtestimagel();
	afx_msg void OnBnClickedtestimager();

	afx_msg void OnBnClickedbmimagel();
	afx_msg void OnBnClickedbmimager();
	CListCtrl Instruction_Command;
private:
	CListCtrl InstructionCommandList;
public:
	afx_msg void OnBnClickedAlignmentWo();
	afx_msg void OnBnClickedCameracalibation();
	afx_msg void OnLvnItemchangedList3(NMHDR *pNMHDR, LRESULT *pResult);
private:
	CListCtrl ErrorList;
public:
	afx_msg void OnBnClickedRectifyrotatecenter();
	afx_msg void OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult);
private:
	CListCtrl RectifyInstructionCommand;
public:
//	CListCtrl RectifyErrorList;
private:
	CListCtrl RectifyErrorList;
public:
	afx_msg void OnBnClickedRectifyimagel();
	afx_msg void OnBnClickedRectifyimager();
	afx_msg void OnBnClickedButton6();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton7();
	afx_msg void OnStnClickedRectifyimageviewr();
	afx_msg void OnBnClickedButton8();
	afx_msg void OnBnClickedButton9();
	afx_msg void OnBnClickedButton10();
	afx_msg void OnBnClickedResultimagel();
	afx_msg void OnBnClickedResultimager();
	afx_msg void OnBnClickedButton11();
private:
	CListCtrl RotatePointList1;
	CListCtrl RotatePointList2;
public:
	afx_msg void OnLvnItemchangedList4(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnEnChangeCanny1();
	afx_msg void OnEnChangeHough1();
	afx_msg void OnEnChangeThreshold();
	afx_msg void OnEnChangeerodesize();
	afx_msg void OnEnChangeHough3();
	afx_msg void OnEnChangeHough2();
	afx_msg void OnEnChangeHoughcircle();
	CEdit m_threshold;
	CEdit m_erodeSize;
	CEdit m_cannt1;
	CEdit m_canny2;
	CEdit m_hough1;
	CEdit m_hough2;
	CEdit m_hough3;
};
