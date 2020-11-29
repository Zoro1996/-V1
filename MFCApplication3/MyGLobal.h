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
extern int erodeSize;

extern Mat maskImageL;
extern Mat maskImageR;

#define CrossMethod 3//1:GetCrossPoint 2:GetCrossBasedShape 3:GetCrossBasedFastShape
#define factor 5
#define THETA -3
#define PI 3.141592636

//double M00[5][5] = { { 0.0219, 0.1231, 0.1573, 0.1231, 0.0219 },
//{ 0.1231, 0.1600, 0.1600, 0.1600, 0.1231 },
//{ 0.1573, 0.1600, 0.1600, 0.1600, 0.1573 },
//{ 0.1231, 0.1600, 0.1600, 0.1600, 0.1231 },
//{ 0.0219, 0.1231, 0.1573, 0.1231, 0.0219 } };
//
//double M10[5][5] = { { -0.0147, -0.0469, 0.0000, 0.0469, 0.0147 },
//{ -0.0933, -0.0640, 0.0000, 0.0640, 0.0933 },
//{ -0.1253, -0.0640, 0.0000, 0.0640, 0.1253 },
//{ -0.0933, -0.0640, 0.0000, 0.0640, 0.0933 },
//{ -0.0147, -0.0469, 0.0000, 0.0469, 0.0147 } };
//
//double M20[5][5] = { { 0.0099, 0.0194, 0.0021, 0.0194, 0.0099 },
//{ 0.0719, 0.0277, 0.0021, 0.0277, 0.0719 },
//{ 0.1019, 0.0277, 0.0021, 0.0277, 0.1019 },
//{ 0.0719, 0.0277, 0.0021, 0.0277, 0.0719 },
//{ 0.0099, 0.0194, 0.0021, 0.0194, 0.0099 } };
//
//double M11[5][5] = { { -0.0098, -0.0352, 0.0000, 0.0352, 0.0098 },
//{ -0.0352, -0.0256, 0.0000, 0.0256, 0.0352 },
//{ 0.0000, 0.0000, 0.0000, 0.0000, 0.0000 },
//{ 0.0352, 0.0256, 0.0000, -0.0256, -0.0352 },
//{ 0.0098, 0.0352, 0.0000, -0.0352, -0.0098 } };
//
//double M01[5][5] = { { 0.0147, 0.0933, 0.1253, 0.0933, 0.0147 },
//{ 0.0469, 0.0640, 0.0640, 0.0640, 0.0469 },
//{ 0.0000, 0.0000, 0.0000, 0.0000, 0.0000 },
//{ -0.0469, -0.0640, -0.0640, -0.0640, -0.0469 },
//{ -0.0147, -0.0933, -0.1253, -0.0933, -0.0147 } };
//
//double M02[5][5] = { { 0.0099, 0.0719, 0.1019, 0.0719, 0.0099 },
//{ 0.0194, 0.0277, 0.0277, 0.0277, 0.0194 },
//{ 0.0021, 0.0021, 0.0021, 0.0021, 0.0021 },
//{ 0.0194, 0.0277, 0.0277, 0.0277, 0.0194 },
//{ 0.0099, 0.0719, 0.1019, 0.0719, 0.0099 } };
