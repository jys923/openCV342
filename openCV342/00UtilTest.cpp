#include "stdafx.h"

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
	rectangle(src, Point(rect.x, rect.y), Point(rect.x + rect.width, rect.y + rect.height), Scalar(0, 0, 255), 2);
	imshow("src", src);
	imshow("result", result);

	cntBlackPixel = countNonZero(result);
	cntWhitePixel = cntTotalPixel - cntBlackPixel;
	cout << "total:" << rect.width * rect.height << endl;//03
	cout << "cntW:" << cntWhitePixel << endl;//03
	waitKey();
	//RIO 해제

	return cntWhitePixel;
}

int GetIrisData(cv::Mat &image, cv::Mat &dest, cv::Point2f center, int radius)
{
	Mat src, ldest;
	Point2f centerL((float)src.cols / 2, (float)src.rows / 2);
	src = image;
	//ldest = createMat
	return -1;
}

class jp2kTest {
private:
	int num;
public:
	void fun1(int a) {

	};
};