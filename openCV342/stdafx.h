// stdafx.h : ���� ��������� ���� ��������� �ʴ�
// ǥ�� �ý��� ���� ���� �Ǵ� ������Ʈ ���� ���� ������
// ��� �ִ� ���� �����Դϴ�.
//

#pragma once

#include "targetver.h"
#include <math.h>
#include <stdio.h>
#include <tchar.h>
#include <iostream>


// TODO: ���α׷��� �ʿ��� �߰� ����� ���⿡�� �����մϴ�.

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