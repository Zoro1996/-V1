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
#define CrossDetectionMode 2
#define factor 5
#define THETA -3
#define PI 3.141592636