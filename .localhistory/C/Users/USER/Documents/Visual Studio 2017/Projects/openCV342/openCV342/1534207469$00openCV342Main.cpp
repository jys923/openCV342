#include "stdafx.h"
#include "03Wavelet2.h"
#include "03Wavelet3.h"
#include "04HighPassFilter.h"
#include "05LowPassFilter.h"

int polarTransforms(int camNumber);
int histogram03(String filePath);
int logPolarTest(String filePath);
int process(VideoCapture& capture);
void myFilter2D(const cv::Mat &image, cv::Mat &result , int filter);

int main()
{
	Mat image = cv::imread("./../../[00Images]/etc/waveletTest.png", IMREAD_GRAYSCALE);
	Mat result;

	namedWindow("Image");
	imshow("Image", image);

	myFilter2D(image, result,0);
	namedWindow("sobelVertical");
	imshow("sobelVertical", image);
	
	myFilter2D(image, result, 1);
	namedWindow("sobelHorizental");
	imshow("sobelHorizental", result);

	myFilter2D(image, result, 6);
	namedWindow("sobelLT");
	imshow("sobelLT", result);

	myFilter2D(image, result, 7);
	namedWindow("sobelLL");
	imshow("sobelLL", result);

	myFilter2D(image, result, 2);
	namedWindow("Result2");
	imshow("Result2", result);

	myFilter2D(image, result, 3);
	namedWindow("Result3");
	imshow("Result3", result);

	myFilter2D(image, result, 4);
	namedWindow("Result4");
	imshow("Result4", result);

	namedWindow("Result5");
	GaussianBlur(image, result, Size(3, 3), 0);
	imshow("Result5", result);


	waitKey();
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

void myFilter2D(const cv::Mat &image, cv::Mat &result,int filter) {
	float *pData = NULL;
	float data[] = {
		0,-1,0,
		-1,5,-1,
		0,-1,0
	};

	float sobelLTtoRL[] = {
		0,1,2,
		-1,0,1,
		-2,-1,0
	};

	float sobelLLtoRT[] = {
		-2,-1,0
		-1,0,1,
		0,1,2
	};
	
	float sobelVertical[] = {
		-1,0,1,
		-2,0,2,
		-1,0,1
	};

	float sobelHorizental[] = {
		-1,-2,-1,
		0,0,0,
		1,2,1
	};

	float Laplacian[] = {
		-1,-1,-1,
		-1,8,-1,
		-1,-1,-1
	};

	float lowPass[] = {
		1 / 9,1 / 9,1 / 9,
		1 / 9,1 / 9,1 / 9,
		1 / 9,1 / 9,1 / 9,
	};

	float highPass[] = {
		-1 / 9,-1 / 9,-1 / 9,
		-1 / 9,1,-1 / 9,
		-1 / 9,-1 / 9,-1 / 9,
	};

	float Gaussian[] = {
		1 / 16,2 / 16,1 / 16,
		2 / 16,4 / 16,1 / 16,
		1 / 16,2 / 16,1 / 16
	};

	switch (filter)
	{
		case 0 :
			pData = sobelVertical;
			break;
		case 1:
			pData = sobelHorizental;
			break;
		case 2:
			pData = Laplacian;
			break;
		case 3:
			pData = lowPass;
			break;
		case 4:
			pData = highPass;
			break;
		case 5:
			pData = Gaussian;
			break;
		case 6:
			pData = sobelLTtoRL;
			break;
		case 7:
			pData = sobelLLtoRT;
			break;

		default:
			pData = data;
			break;
	}

	Mat kernel(3, 3, CV_32F, pData);
	//Mat kernel(3, 3, CV_32F, cv::Scalar(0));
	//// Ŀ�� ����(��� ���� 0���� �ʱ�ȭ)
	//kernel.at<float>(1, 1) = 5.0; // Ŀ�� ���� �Ҵ�
	//kernel.at<float>(0, 1) = -1.0;
	//kernel.at<float>(2, 1) = -1.0;
	//kernel.at<float>(1, 0) = -1.0;
	//kernel.at<float>(1, 2) = -1.0;

	cv::filter2D(image, result, image.depth(), kernel);
	// ���� ���͸�
}