#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int testFilter00() {
	Mat bilateral = imread("./../../[00Images]/eyes/libs/(13).bmp", IMREAD_COLOR);
	Mat b = bilateral.clone();
	Mat gaussian = bilateral.clone();
	Mat median = bilateral.clone();
	Mat result;
	imshow("original image", bilateral);


	blur(b, result, Size(5, 5));
	imshow("blur result", result);

	GaussianBlur(gaussian, result, Size(5, 5), 1.5, 1.5);
	imshow("GaussianBlur result", result);

	medianBlur(median, result, 7);
	imshow("medianBlur result", result);

	bilateralFilter(bilateral, result, 10, 50, 50);
	imshow("bilateralFilter result", result);

	/*
	bilateralFilter (1, 2, 3, 4, 5);

	argument 1 : Source image
	argument 2 : Destination image
	argument 3 : the diameter of each pixel neighborhood
	argument 4 : Standard deviation in the color space
	argument 5 : Standard deviation in the coordinate space
	*/


	waitKey(0);
	return 0;
}