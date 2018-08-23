#include "stdafx.h"
#include "03Wavelet2.h"
#include "03Wavelet3.h"
#include "04HighPassFilter.h"
#include "05LowPassFilter.h"

int polarTransforms(int camNumber);

int histogram03(String filePath);
int logPolarTest(String filePath);
int process(VideoCapture& capture);
//void myFilter2D(const cv::Mat &image, cv::Mat &result , int filter);
int myFilter2DMain();
int cntPixel(cv::Mat &image, cv::Rect rect, int min, int max);
int GetIrisData(cv::Mat &image, cv::Mat &dest);

int main()
{
	int resultMain = 0;
	//resultMain = polarTransforms(0);
	Mat src, lin_polar_img, log_polar_img;
	src = imread("./../../[00Images]/etc/visualcone_stereographic2.png", IMREAD_GRAYSCALE);
	Point2f center((float)src.cols / 2, (float)src.rows / 2);
	double M = (float)src.rows / 2;
	//double M = 70;
	logPolar(src, log_polar_img, center, M, INTER_LINEAR + WARP_FILL_OUTLIERS);
	linearPolar(src, lin_polar_img, center, M, INTER_LINEAR + WARP_FILL_OUTLIERS);
	imshow("src", src);
	imshow("log_polar_img", log_polar_img);
	imshow("lin_polar_img", lin_polar_img);
	waitKey();

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
	return resultMain;

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
//min~max 사이면 255 아니면 0 //사이 픽셀수 출력
int cntPixel(cv::Mat &image, Rect rect, int min, int max)
{
	Mat src = image;
	Mat RIO = src(rect);
	imshow("RIO", RIO);
	Mat result;
	int cntWhitePixel, cntTotalPixel, cntBlackPixel;
	cntTotalPixel = rect.width * rect.height;
	inRange(RIO, min, max, result);
	rectangle(src,  Point(rect.x, rect.y), Point(rect.x+rect.width, rect.y + rect.height), Scalar(0, 0, 255), 2);
	imshow("src", src);
	imshow("result", result);
	
	cntBlackPixel = countNonZero(result);
	cntWhitePixel = cntTotalPixel - cntBlackPixel;
	cout << "total:"<< rect.width * rect.height << endl;//03
	cout << "cntW:" << cntWhitePixel << endl;//03
	waitKey();
	//RIO 해제
	
	return cntWhitePixel;
}

int GetIrisData(cv::Mat &image, cv::Mat &dest)
{
	Mat src, ldest;
	Point2f center((float)src.cols / 2, (float)src.rows / 2);
	src = image;
	return -1;
}