#include "stdafx.h"
void myFilter2D(const cv::Mat &image, cv::Mat &result, int filter);


int myFilter2DMain()
{
	Mat image = cv::imread("./../../[00Images]/etc/waveletTest.png", IMREAD_GRAYSCALE);
	Mat result;

	namedWindow("Image");
	imshow("Image", image);

	myFilter2D(image, result, 0);
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

}

void myFilter2D(const cv::Mat &image, cv::Mat &result, int filter) {
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
		- 1,0,1,
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
	case 0:
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
	//// 커널 생성(모든 값을 0으로 초기화)
	//kernel.at<float>(1, 1) = 5.0; // 커널 값에 할당
	//kernel.at<float>(0, 1) = -1.0;
	//kernel.at<float>(2, 1) = -1.0;
	//kernel.at<float>(1, 0) = -1.0;
	//kernel.at<float>(1, 2) = -1.0;

	cv::filter2D(image, result, image.depth(), kernel);
	// 영상 필터링
}