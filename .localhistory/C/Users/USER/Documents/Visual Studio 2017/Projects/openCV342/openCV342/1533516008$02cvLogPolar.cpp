#include "stdafx.h"

IplImage *src, *src2, *dst;

void onTrackbar(int pos)
{
	if (src == NULL)
		return;

	double M;

	if (pos == 0)	//0이면 함수 에러나기때문
		M = 0.001;

	else
		M = (double)(pos*0.01);

	cvLogPolar(src, dst, cvPoint2D32f(src->width / 4, src->height / 2),
		M, CV_INTER_LINEAR + CV_WARP_FILL_OUTLIERS);

	cvLogPolar(dst, src2, cvPoint2D32f(src->width / 4, src->height / 2),
		M, CV_INTER_LINEAR | CV_WARP_INVERSE_MAP);

	cvShowImage("log-polar", dst);
	cvShowImage("inverse log-polar", src2);
	system("cls");
	printf("M val is %f\n", M);

}

int logPolarTest(String filePath)
{

	src = cvLoadImage(filePath.c_str(), 1);
	if (src == NULL)
		return 1;

	src2 = cvCreateImage(cvGetSize(src), 8, 3);
	dst = cvCreateImage(cvGetSize(src), 8, 3);

	int val = 0.1;

	cvNamedWindow("source", 1);
	cvNamedWindow("log-polar", 1);
	cvNamedWindow("inverse log-polar", 1);
	cvShowImage("source", src);
	cvCreateTrackbar("LogPolar M value", "log-polar", &val, 10000, onTrackbar);

	cvWaitKey();

	cvReleaseImage(&src);
	cvReleaseImage(&dst);
	cvReleaseImage(&src2);
	cvDestroyWindow("source");
	cvDestroyWindow("log-polar");
	cvDestroyWindow("inverse log-polar");
	return 0;
}
