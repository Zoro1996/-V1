#pragma once
#include <iostream>  
#include <fstream>
#include <string>
#include <vector>
#include <iterator>
#include "afxwin.h"

extern double CannyThreshold1;
extern double CannyThreshold2;
extern double HoughThreshold1;
extern double HoughThreshold2;
extern double HoughThreshold3;
extern double thresholdValue;
extern double ransacDistance;

extern Mat maskImageL;
extern Mat maskImageR;
extern Mat cosImage;
extern Mat sinImage;
extern Mat eWorldL;
extern Mat eWorldR;
//extern Mat ML;
//extern Mat MR;

/*�ŵ�궨*/
#define CalibrationMethod 1//1:ֱ������   2:��Ŀ�궨

/*CrossMethod=1:GetCrossPoint 
CrossMethod=2:GetCrossBasedShape 
CrossMethod=3:GetCrossBaseFastShape*/
#define CrossMethod 3

/*CrossDetectionMode=1:Sobel��ȡ��Ե
CrossDetectionMode=2:Sobel��ȡ��Ե+ransac�޳��������+fitline����˾�汾������������
CrossDetectionMode=3:LSD��ȡֱ�ߣ�opencvv4.10���ٿ���*/
#define CrossDetectionMode 2

/*SubPixelMethod=1:�ҶȾ��������㷨 
SubPixelMethod=2:Zernik���������㷨*/
#define SubPixelMethod 1

/*��״ƥ����ͼ�����������ָ��*/
#define factor 5

#define  roiOffset 100

/*�궨ʱ��ת�Ƕ�*/
#define THETA -3 * PI / 180
//#define THETA 2 * PI / 180