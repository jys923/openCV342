#include "stdafx.h"

//Contour ���� ���� �ؽ�Ʈ ���� 
//https://github.com/bsdnoobz/opencv-code/blob/master/shape-detect.cpp
void setLabel(Mat& image, string str, vector<Point> contour)
{
	int fontface = FONT_HERSHEY_SIMPLEX;
	double scale = 0.5;
	int thickness = 1;
	int baseline = 0;

	Size text = getTextSize(str, fontface, scale, thickness, &baseline);
	Rect r = boundingRect(contour);

	Point pt(r.x + ((r.width - text.width) / 2), r.y + ((r.height + text.height) / 2));
	rectangle(image, pt + Point(0, baseline), pt + Point(text.width, -text.height), CV_RGB(200, 200, 200), CV_FILLED);
	putText(image, str, pt, fontface, scale, CV_RGB(0, 0, 0), thickness, 8);
}

int FindPolygon()
{
	Mat img_input, img_result, img_gray;
	String path = "./../../[00Images]/eyes/sample/";
	String fileName = "test.bmp";
	//�̹��������� �ε��Ͽ� image�� ����  
	img_input = imread(path+fileName, IMREAD_COLOR);
	if (img_input.empty())
	{
		cout << "Could not open or find the image" << std::endl;
		return -1;
	}


	//�׷��̽����� �̹����� ��ȯ  
	cvtColor(img_input, img_gray, COLOR_BGR2GRAY);

	//����ȭ �̹����� ��ȯ
	Mat binary_image;
	binary_image = img_gray.clone();
	//threshold(img_gray, img_gray, 250, 255, THRESH_BINARY_INV);
	for (size_t i = 0; i < 255; i++)
	{
		cout << "why:" << i << endl;
		Mat binary_image2;
		threshold(binary_image, binary_image2, i, 255, THRESH_BINARY_INV);
		imshow("test", binary_image2);
		waitKey(0);
		Mat canny_image;
		blur(binary_image2, canny_image, Size(5, 5));
		Canny(canny_image, canny_image, 125, 125 * 3, 3);
		imshow("Canny", canny_image);
		waitKey(0);
		vector<Vec3f> circles;
		//HoughCircles(canny_image, circles, HOUGH_GRADIENT, 1, canny_image.rows / 4, 200, 100, 0, 0);
		HoughCircles(canny_image, circles, HOUGH_GRADIENT, 2, canny_image.rows / 12, 200, 100, 20, canny_image.rows / 8);
		for (size_t j = 0; j < circles.size(); j++)
		{
			Point center(cvRound(circles[j][0]), cvRound(circles[j][1]));
			int radius(cvRound(circles[j][2]));
			circle(img_input, center, 3, Scalar(0, 255, 0), -1, 8, 0);
			circle(img_input, center, radius, Scalar(0, 0, 255), 3, 8, 0);
		}
		imshow("circles", img_input);
		waitKey(0);
		Point center(cvRound(circles[0][0]), cvRound(circles[0][1]));
		int radius(cvRound(circles[0][2]));

		//Rect(cvRound(circles[0][0]) - cvRound(circles[0][2]), cvRound(circles[0][1]) - cvRound(circles[0][2])*2.5, cvRound(circles[0][2]) *2,;


	}
	adaptiveThreshold(img_gray,img_gray,255, ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY, 55, 10);
	imshow("threshold", img_gray);
	/*erode(img_gray, img_gray, Mat());
	dilate(img_gray, img_gray, Mat());
	erode(img_gray, img_gray, Mat());
	dilate(img_gray, img_gray, Mat());
	erode(img_gray, img_gray, Mat());
	dilate(img_gray, img_gray, Mat());	
	erode(img_gray, img_gray, Mat());
	dilate(img_gray, img_gray, Mat());
	erode(img_gray, img_gray, Mat());
	dilate(img_gray, img_gray, Mat());
	erode(img_gray, img_gray, Mat());
	dilate(img_gray, img_gray, Mat());*/

	// Create the images that will use to extract the horizontal and vertical lines
	Mat horizontal = img_gray.clone();
	Mat vertical = img_gray.clone();
	// Specify size on horizontal axis
	int horizontalsize = horizontal.cols / 30;
	// Create structure element for extracting horizontal lines through morphology operations
	Mat horizontalStructure = getStructuringElement(MORPH_RECT, Size(horizontalsize, 2));
	// Apply morphology operations
	erode(horizontal, horizontal, horizontalStructure, Point(-1, -1));
	dilate(horizontal, horizontal, horizontalStructure, Point(-1, -1));
	// Show extracted horizontal lines
	imshow("horizontal", horizontal);

	Mat elements5(7,7, CV_8U, Scalar(1));
	cv::morphologyEx(img_gray, img_gray, cv::MORPH_CLOSE, elements5);
	cv::morphologyEx(img_gray, img_gray, cv::MORPH_OPEN, elements5);
	
	
	
	imshow("morphologyEx", img_gray);
	//contour�� ã�´�.
	vector<vector<Point> > contours;
	findContours(horizontal, contours, RETR_LIST, CHAIN_APPROX_SIMPLE);

	//contour�� �ٻ�ȭ�Ѵ�.
	vector<Point2f> approx;
	img_result = img_input.clone();

	for (size_t i = 0; i < contours.size(); i++)
	{
		approxPolyDP(Mat(contours[i]), approx, arcLength(Mat(contours[i]), true)*0.02, true);

		if (fabs(contourArea(Mat(approx))) > 1000)  //������ ����ũ�� �̻��̾�� �Ѵ�. 
		{

			int size = approx.size();

			//Contour�� �ٻ�ȭ�� ������ �׸���.
			if (size % 2 == 0) {
				line(img_result, approx[0], approx[approx.size() - 1], Scalar(0, 255, 0), 3);

				for (int k = 0; k < size - 1; k++)
					line(img_result, approx[k], approx[k + 1], Scalar(0, 255, 0), 3);

				for (int k = 0; k < size; k++)
					circle(img_result, approx[k], 3, Scalar(0, 0, 255));
			}
			else {
				line(img_result, approx[0], approx[approx.size() - 1], Scalar(0, 255, 0), 3);

				for (int k = 0; k < size - 1; k++)
					line(img_result, approx[k], approx[k + 1], Scalar(0, 255, 0), 3);

				for (int k = 0; k < size; k++)
					circle(img_result, approx[k], 3, Scalar(0, 0, 255));
			}



			//������ �����Ѵ�.
			if (size == 3)
				setLabel(img_result, "triangle", contours[i]); //�ﰢ��

															   //���ϴ� �ش� �������� ���� convex��� ã�� ����
			else if (size == 4 && isContourConvex(Mat(approx)))
				setLabel(img_result, "rectangle", contours[i]); //�簢��

			else if (size == 5 && isContourConvex(Mat(approx)))
				setLabel(img_result, "pentagon", contours[i]); //������

			else if (size == 6 && isContourConvex(Mat(approx)))
				setLabel(img_result, "hexagon", contours[i]);  //������

			else if (size == 10 && isContourConvex(Mat(approx)))
				setLabel(img_result, "decagon", contours[i]);    //�ʰ���

																 //�� ���ǿ� �ش� �ȵǴ� ���� ã�Ƴ� ������ ������ ǥ��
			else setLabel(img_result, to_string(approx.size()), contours[i]);
		}

	}


	imshow("input", img_input);
	imshow("result", img_result);


	waitKey(0);


	return 0;
}

int testUpperLib()
{
	Mat img_input, img_result, img_gray;
	String path = "./../../[00Images]/eyes/sample/";
	String fileName = "660lib01.bmp";
	//�̹��������� �ε��Ͽ� image�� ����  
	img_input = imread(path + fileName, IMREAD_COLOR);
	if (img_input.empty())
	{
		cout << "Could not open or find the image" << std::endl;
		return -1;
	}


	//�׷��̽����� �̹����� ��ȯ  
	cvtColor(img_input, img_gray, COLOR_BGR2GRAY);

	//����ȭ �̹����� ��ȯ
	Mat binary_image;
	binary_image = img_gray.clone();
	//threshold(img_gray, img_gray, 250, 255, THRESH_BINARY_INV);
	for (size_t i = 0; i < 255; i++)
	{
		cout << "why:" << i << endl;
		Mat binary_image2;
		threshold(binary_image, binary_image2, i, 255, THRESH_BINARY_INV);
		imshow("test", binary_image2);
		waitKey(0);
		Mat canny_image;
		blur(binary_image, canny_image, Size(5, 5));
		Canny(canny_image, canny_image, 125, 125 * 3, 3);
		imshow("Canny", canny_image);
		waitKey(0);
		//���� ������ �����մϴ�.  
		vector<Vec4i> lines;
		HoughLinesP(canny_image, lines, 1, CV_PI / 180, 30, 30, 3);

		//������ ������ ���� �׷��ݴϴ�.  
		for (int j = 0; j<lines.size(); j++)
		{
			Vec4i L = lines[j];
			line(img_input, Point(L[0], L[1]), Point(L[2], L[3]),
				Scalar(0, 0, 255), 1, LINE_AA);
		}
		

		cvNamedWindow("result", WINDOW_AUTOSIZE);
		imshow("result", img_input);

		waitKey(0);

	}
	adaptiveThreshold(img_gray, img_gray, 255, ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY, 55, 10);
	imshow("threshold", img_gray);

	return 0;
}