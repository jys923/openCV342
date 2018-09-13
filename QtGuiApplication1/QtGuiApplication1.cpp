#include "QtGuiApplication1.h"
#include "opencv2/opencv.hpp"
using namespace cv;

QtGuiApplication1::QtGuiApplication1(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
}

void QtGuiApplication1::LoadImage()
{
	VideoCapture cap(0);
	Mat img;
	cap >> img;
	QImage qimg(img.data, img.cols, img.rows, QImage::Format_RGB888);
	ui.label->setPixmap(QPixmap::fromImage(qimg));
}