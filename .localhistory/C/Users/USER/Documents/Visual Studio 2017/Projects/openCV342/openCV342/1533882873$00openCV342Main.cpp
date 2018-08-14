#include "stdafx.h"
#include "03Wavelet2.h"
#include "03Wavelet3.h"
#include "04HighPassFilter.h"
#include "05LowPassFilter.h"

int polarTransforms(int camNumber);
int histogram03(String filePath);
int logPolarTest(String filePath);
int process(VideoCapture& capture);
void sharpen2D(const cv::Mat &image, cv::Mat &result);

int main()
{
	Mat image = cv::imread("./../../[00Images]/etc/lena.png", IMREAD_GRAYSCALE);
	Mat result;

	sharpen2D(image, result);

	namedWindow("Image");
	imshow("Image", image);

	namedWindow("Result");
	imshow("Result", result);

	cv::waitKey();

	return 0;

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

	/*VideoCapture capture(0);
	if (!capture.isOpened())
	{
		return 1;
	}
	result = process(capture);*/
	
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

void sharpen2D(const cv::Mat &image, cv::Mat &result) {
	float data[] = {
		0,-1,0,
		-1,5,-1,
		0,-1,0
	};

	float sobelvertical[] = {
		-1,0,1,
		-2,0,2,
		-1,0,1
	};

	Mat kernel(3, 3, CV_32F, sobelvertical);
	//Mat kernel(3, 3, CV_32F, cv::Scalar(0));
	//// 커널 생성(모든 값을 0으로 초기화)
	//kernel.at<float>(1, 1) = 5.0; // 커널 값에 할당
	//kernel.at<float>(0, 1) = -1.0;
	//kernel.at<float>(2, 1) = -1.0;
	//kernel.at<float>(1, 0) = -1.0;
	//kernel.at<float>(1, 2) = -1.0;

	cv::filter2D(image, result, image.depth(), kernel);
	// 영상 필터링
}