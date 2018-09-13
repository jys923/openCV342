#include "stdafx.h"

//Contour 영역 내에 텍스트 쓰기 
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
	//이미지파일을 로드하여 image에 저장  
	img_input = imread(path+fileName, IMREAD_COLOR);
	if (img_input.empty())
	{
		cout << "Could not open or find the image" << std::endl;
		return -1;
	}


	//그레이스케일 이미지로 변환  
	cvtColor(img_input, img_gray, COLOR_BGR2GRAY);

	//이진화 이미지로 변환
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
	//contour를 찾는다.
	vector<vector<Point> > contours;
	findContours(horizontal, contours, RETR_LIST, CHAIN_APPROX_SIMPLE);

	//contour를 근사화한다.
	vector<Point2f> approx;
	img_result = img_input.clone();

	for (size_t i = 0; i < contours.size(); i++)
	{
		approxPolyDP(Mat(contours[i]), approx, arcLength(Mat(contours[i]), true)*0.02, true);

		if (fabs(contourArea(Mat(approx))) > 1000)  //면적이 일정크기 이상이어야 한다. 
		{

			int size = approx.size();

			//Contour를 근사화한 직선을 그린다.
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



			//도형을 판정한다.
			if (size == 3)
				setLabel(img_result, "triangle", contours[i]); //삼각형

															   //이하는 해당 꼭지점을 가진 convex라면 찾는 도형
			else if (size == 4 && isContourConvex(Mat(approx)))
				setLabel(img_result, "rectangle", contours[i]); //사각형

			else if (size == 5 && isContourConvex(Mat(approx)))
				setLabel(img_result, "pentagon", contours[i]); //오각형

			else if (size == 6 && isContourConvex(Mat(approx)))
				setLabel(img_result, "hexagon", contours[i]);  //육각형

			else if (size == 10 && isContourConvex(Mat(approx)))
				setLabel(img_result, "decagon", contours[i]);    //십각형

																 //위 조건에 해당 안되는 경우는 찾아낸 꼭지점 갯수를 표시
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
	Mat img_input, img_gray, canny_image;
	String path = "./../../[00Images]/eyes/libs/";
	String fileName = "(12).bmp";
	//이미지파일을 로드하여 image에 저장  
	img_input = imread(path + fileName, IMREAD_COLOR);
	if (img_input.empty())
	{
		cout << "Could not open or find the image" << std::endl;
		return -1;
	}

	imshow("img_input", img_input);
	waitKey(0);
	//그레이스케일 이미지로 변환  
	cvtColor(img_input, img_gray, COLOR_BGR2GRAY);

	//이진화 이미지로 변환
	Mat binary_image;
	binary_image = img_gray.clone();
	//threshold(img_gray, img_gray, 250, 255, THRESH_BINARY_INV);
	
	Mat binary_image2 , img_result;
	//canny_image = img_input. .clone();
	//threshold(binary_image, canny_image, 100, 255, THRESH_BINARY_INV + THRESH_OTSU);
	adaptiveThreshold(binary_image, canny_image, 230, ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY, 11, 10);
	imshow("Threshold", canny_image);
	waitKey(0);

	/*int horizontalsize = canny_image.cols / 8;

	Mat structure = getStructuringElement(MORPH_RECT, Size(horizontalsize, 1));

	erode(canny_image, canny_image, structure, Point(-1, -1));
	dilate(canny_image, canny_image, structure, Point(-1, -1));
	imshow("horizontalsize", canny_image);*/

	// Specify size on vertical axis
	int verticalsize = canny_image.rows / 8;
	// Create structure element for extracting vertical lines through morphology operations
	Mat verticalStructure = getStructuringElement(MORPH_RECT, Size(1, verticalsize));
	// Apply morphology operations
	erode(canny_image, canny_image, verticalStructure, Point(-1, -1));
	dilate(canny_image, canny_image, verticalStructure, Point(-1, -1));
	// Show extracted vertical lines
	imshow("vertical", canny_image);
	// Inverse vertical image
	bitwise_not(canny_image, canny_image);
	imshow("vertical_bit", canny_image);
	waitKey(0);

	blur(canny_image, canny_image, Size(7, 7));
	Canny(canny_image, canny_image, 30, 30 * 3, 3,true);
	imshow("Canny", canny_image);
	waitKey(0);
	//직선 성분을 검출합니다.  
		
	/*vector<Vec2f> linesL, linesR, lines;
	HoughLines(canny_image, linesL, 1, 1 * CV_PI / 180, 20);*/

	// 왼쪽 
	//HoughLines(canny_image, linesL, 1, 1 * CV_PI / 180, 10, 0, 0);
		//0, CV_PI / 2);
	// 오른쪽 
	//HoughLines(canny_image, linesR, 1, 1 * CV_PI / 180, 10, 0, 0, CV_PI / 2, CV_PI);
	//linesL.insert(linesL.end(), linesR.begin(), linesR.end());


	vector<Vec4i> linesL, linesR, lines;
	HoughLinesP(canny_image, linesL, 1, 1 * CV_PI / 180, 20, 0, 0);
	//검출한 직선을 영상에 그려줍니다.  
	for (int j = 0; j<linesL.size(); j++)
	{
		//Vec4i L = linesL[j];
		Vec4i L = linesL[j];
		line(img_gray, Point(L[0], L[1]), Point(L[2], L[3]),
			Scalar(0, 0, 255), 1, LINE_AA);
	}
	//cvNamedWindow("result", WINDOW_AUTOSIZE);
	imshow("line", img_gray);
	cout << "a:" << img_input.depth() << ",b:" << canny_image.depth() << endl;
	waitKey(0);
	hconcat(img_gray, canny_image, img_result); //두 이미지의 높이(row)가 같아야함.
	imshow("result", img_result);
	waitKey(0);
	
	return 0;

	//for (size_t i = 0; i < 255; i++)
	//{
	//	cout << "why:" << i << endl;
	//	Mat binary_image2, canny_image, img_result;
	//	//threshold(binary_image, canny_image, 100, 255, THRESH_BINARY_INV + THRESH_OTSU);
	//	adaptiveThreshold(binary_image, canny_image, 230, ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY_INV, 55, 10);
	//	imshow("Threshold", canny_image);
	//	waitKey(0);

	//	int horizontalsize = canny_image.cols / 30;

	//	Mat structure = getStructuringElement(MORPH_RECT, Size(horizontalsize, 1));

	//	erode(canny_image, canny_image, structure, Point(-1, -1));
	//	dilate(canny_image, canny_image, structure, Point(-1, -1));
	//	imshow("horizontalsize", canny_image);

	//	blur(canny_image, canny_image, Size(7, 7));
	//	Canny(canny_image, canny_image, 30, 30 * 3, 3);
	//	imshow("Canny", canny_image);
	//	waitKey(0);
	//	//직선 성분을 검출합니다.  

	//	/*vector<Vec2f> linesL, linesR, lines;
	//	HoughLines(canny_image, linesL, 1, 1 * CV_PI / 180, 20);*/

	//	// 왼쪽 
	//	//HoughLines(canny_image, linesL, 1, 1 * CV_PI / 180, 10, 0, 0);
	//	//0, CV_PI / 2);
	//	// 오른쪽 
	//	//HoughLines(canny_image, linesR, 1, 1 * CV_PI / 180, 10, 0, 0, CV_PI / 2, CV_PI);
	//	//linesL.insert(linesL.end(), linesR.begin(), linesR.end());


	//	vector<Vec4i> linesL, linesR, lines;
	//	HoughLinesP(canny_image, linesL, 1, 1 * CV_PI / 180, 20, 0, 0);
	//	//검출한 직선을 영상에 그려줍니다.  
	//	for (int j = 0; j<linesL.size(); j++)
	//	{
	//		//Vec4i L = linesL[j];
	//		Vec4i L = linesL[j];
	//		line(img_input, Point(L[0], L[1]), Point(L[2], L[3]),
	//			Scalar(0, 0, 255), 1, LINE_AA);
	//	}
	//	//cvNamedWindow("result", WINDOW_AUTOSIZE);
	//	imshow("line", img_input);
	//	cout << "a:" << img_input.depth() << ",b:" << canny_image.depth() << endl;
	//	waitKey(0);
	//	//hconcat(img_input, canny_image, img_result); //두 이미지의 높이(row)가 같아야함.
	//	//imshow("result", img_result);
	//	//waitKey(0);
	//}
	//return 0;
}