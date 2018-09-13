#include "stdafx.h"
#include "03Wavelet2.h"
#include "03Wavelet3.h"
#include "04HighPassFilter.h"
#include "05LowPassFilter.h"
//#include <jasper\jasper.h>
#include "opencv2/imgcodecs.hpp"

int polarTransforms(int camNumber);

int histogram03(String filePath);
int logPolarTest(String filePath);
int process(VideoCapture& capture);
//void myFilter2D(const cv::Mat &image, cv::Mat &result , int filter);
int myFilter2DMain();
int cntPixel(cv::Mat &image, cv::Rect rect, int min, int max);
int GetIrisData(cv::Mat &image, cv::Mat &dest);
void Sweap(int &a, int &b);
void Sweap2(int &a, int &b);
int FindPolygon();
int testUpperLib();

void Sweap2(int *a, int *b) {
	int tmp;
	tmp = *a;
	cout << "sweap2:tmp" << tmp << endl;
	*a = *b;
	*b = tmp;
}

void Sweap(int &a, int &b) {
	int tmp = 0;
	tmp = a;
	cout << "sweap:tmp" << tmp << endl;
	a = b;
	b = tmp;
}

int main()
{
	int resultMain = 0;

	//Mat src, src2;
	//src = imread("./../../[00Images]/etc/test.bmp");
	//imshow("test.jp2", src);
	//imwrite("./../../[00Images]/etc/test.jp2", src);
	
	//FindPolygon();
	//testUpperLib();
	myFilter2DMain();
//	int a = 1;
//	int b = 2;
//
//	cout << "out a:" << a << "out b:" << b << endl;
//
//	Sweap(a, b);
//
//	cout << "out a:" << a << "out b:" << b << endl;
//
//	int *a2; a2 = &a;
//	int *b2; b2 = &b;
//
//	cout << "out2 a:" << *a2 << "out b:" << *b2 << endl;
//
//	Sweap2(a2, b2);
//
//	cout << "out2 a:" << *a2 << "out b:" << *b2 << endl;
//
//	Mat src, src2;
//	//src = imread("./../../[00Images]/etc/relax.jp2", IMREAD_ANYDEPTH | IMREAD_ANYCOLOR);
//	//src = imread("./../../[00Images]/etc/example.jp2", IMREAD_ANYDEPTH | IMREAD_ANYCOLOR);
//	src = imread("./../../[00Images]/etc/example.jp2", IMREAD_COLOR);
////	jp2_encode
//	
//
//	imshow("jp2", src);

	/*vector<int> compression_params;
	compression_params.push_back(CV_IMWRITE_PNG_COMPRESSION);
	compression_params.push_back(9);
	imwrite("./../../[00Images]/etc/harris.jp2", , src, compression_params);*/

	waitKey();
	return resultMain;
	//resultMain = polarTransforms(0);
	//Mat src, lin_polar_img, log_polar_img;
	//src = imread("./../../[00Images]/etc/visualcone_stereographic2.png", IMREAD_GRAYSCALE);
	//Point2f center((float)src.cols / 2, (float)src.rows / 2);
	//double M = (float)src.rows / 2;
	////double M = 70;
	//logPolar(src, log_polar_img, center, M, INTER_LINEAR + WARP_FILL_OUTLIERS);
	//linearPolar(src, lin_polar_img, center, M, INTER_LINEAR + WARP_FILL_OUTLIERS);
	//imshow("src", src);
	//imshow("log_polar_img", log_polar_img);
	//imshow("lin_polar_img", lin_polar_img);
	//waitKey();

	//Mat src = imread("./../../[00Images]/etc/lena.png", IMREAD_GRAYSCALE);
	//int cntW = cntPixel(src, Rect(15, 20, 140, 150), 0, 150);
	//cout << "cntW:" << cntW << endl;//03

	////시프트 연산
	//int a = 6;
	//cout << "shift>>:" << (a >> 1) << endl;//03
	//cout << "shift<<:" << (a << 1) << endl;//12
	//system("pause");

	/*VideoCapture capture(0);
	if (!capture.isOpened())
	{
	return 1;
	}
	resultMain = process(capture);*/

	//Filter 테스트
	//resultMain = myFilter2DMain();
	//return resultMain;

	/*HighPassFilter HighPassFilter;
	
	char in_name[100];
	
	cout << "Digital HighPassFilter Processing - High Pass Filter\n" << endl;
	cout << "Enter the Input HighPassFilter Name : ";
	cin >> in_name;
	
	HighPassFilter.ReadHighPassFilter(in_name);
	HighPassFilter.Masking();*/



	//result = polarTransforms(0);
	//result = histogram03("./../../[00Images]/etc/lena.png");
	//result = logPolarTest("./../../[00Images]/etc/lena.png");

	/*int array[1][1] = { 0 };
	printf_s("test0:%d\n", array[0][0]);
	array[0][0] = 100;
	printf_s("test1:%d\n", array[0][0]);
	array[0][0]++;
	printf_s("test2:%d\n", array[0][0]);
	int tmp = 100;
	array[0][0] += tmp;
	printf_s("test3:%d\n", array[0][0]);
	array[0][0] /= 5 * 4;
	printf_s("test4:%d\n", array[0][0]);
	system("pause");*/

	
	
	//Mat im = imread("./../../[00Images]/etc/lena.png", 0); //Load image in Gray Scale
	//imshow("good?", im);
	//waitKey();

	/*image my;
	result = my.getim("./../../[00Images]/etc/lena.jpg");*/


	//int i;
	//char buf[512];
	//for (i = 0; i < 7; i++) {
	//	//sprintf(buf, "wavelet_lena512_22_%d.raw", i + 1);
	//	wavelet_encoder_jty("./lena512.raw", buf, 'a', i + 1);

	//	//sprintf(buf, "wavelet_lena512_swe_%d.raw", i + 1);
	//	wavelet_encoder_jty("./lena512.raw", buf, 'b', i + 1);

	//	//sprintf(buf, "wavelet_lena512_crf_%d.raw", i + 1);
	//	wavelet_encoder_jty("./lena512.raw", buf, 'c', i + 1);
	//}

	//int i1[10] = { 0 };
	//int i2[2] = { 3,6 };
	//for (size_t i = 0; i < sizeof(i); i++)
	//{
	//	cout << i1[i];// << endl;
	//}
	//cout << "" << endl;
	//cout << i1 << endl;
	//cout << i2 << endl;
	//memcpy(i1, i2, sizeof(int)*2);
	//for (size_t i = 0; i < sizeof(i); i++)
	//{
	//	cout << i1[i];// << endl;
	//}
	//cout << "" << endl;
	//cout << i1 << endl;

	/*int a, b, c, d = 10;
	cout << a << " " << b << " " << c << " " << d << " " << endl;*/
	
	//system("pause");
	//waitKey();
	//return result;
}