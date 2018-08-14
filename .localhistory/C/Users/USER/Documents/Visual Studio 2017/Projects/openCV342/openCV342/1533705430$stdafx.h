// stdafx.h : 자주 사용하지만 자주 변경되지는 않는
// 표준 시스템 포함 파일 또는 프로젝트 관련 포함 파일이
// 들어 있는 포함 파일입니다.
//

#pragma once

#include "targetver.h"
#include <math.h>
#include <stdio.h>
#include <tchar.h>
#include <iostream>
#include <conio.h>

// TODO: 프로그램에 필요한 추가 헤더는 여기에서 참조합니다.

#include "opencv2/opencv.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
//#include <opencv2/legacy/legacy.hpp>

#include <opencv/cv.h>;

#ifdef _DEBUG
//#pragma comment(lib, "opencv_core2410d.lib")
//#pragma comment(lib, "opencv_highgui2410d.lib")
//#pragma comment(lib, "opencv_imgproc2410d.lib")
//#pragma comment(lib, "opencv_legacy2410d.lib")
#pragma comment(lib, "opencv_world342d.lib")
#else
//#pragma comment(lib, "opencv_core249.lib")
//#pragma comment(lib, "opencv_highgui249.lib")
//#pragma comment(lib, "opencv_imgproc249.lib")
//#pragma comment(lib, "opencv_legacy249.lib")
#pragma comment(lib, "opencv_world342.lib")
#endif

using namespace	cv;
using namespace	std;

class image
{
public:
	Mat im, im1, im2, im3, im4, im5, im6, temp, im11, im12, im13, im14, imi, imd, imr;
	float a, b, c, d;
	int getim(String filePath);
};