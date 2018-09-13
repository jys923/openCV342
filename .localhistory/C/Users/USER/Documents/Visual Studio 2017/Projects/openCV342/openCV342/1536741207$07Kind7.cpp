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
	Mat img_input, img_gray, canny_image, img_result3;
	String path = "./../../[00Images]/eyes/libs/";
	String fileName = "(7).bmp";
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
	Mat binary_image, binary_image2, img_result, img_result2, canny_image2, canny_image3, canny_image4;
	binary_image = img_gray.clone();
	img_result3 = img_gray.clone();
	//threshold(img_gray, img_gray, 250, 255, THRESH_BINARY_INV);
	
	//canny_image = img_input. .clone();
	//threshold(binary_image, canny_image, 100, 255, THRESH_BINARY_INV + THRESH_OTSU);
	adaptiveThreshold(binary_image, canny_image, 230, ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY, 21, 5);
	imshow("Threshold", canny_image);
	waitKey(0);
	canny_image2 = canny_image.clone();
	canny_image3 = canny_image.clone();
	canny_image4 = canny_image.clone();

	// Specify size on vertical axis
	int verticalsize = canny_image.rows / 15;
	// Create structure element for extracting vertical lines through morphology operations
	Mat verticalStructure = getStructuringElement(MORPH_RECT, Size(1, verticalsize));
	// Apply morphology operations
	erode(canny_image, canny_image, verticalStructure, Point(-1, -1));
	dilate(canny_image, canny_image, verticalStructure, Point(-1, -1));
	// Show extracted vertical lines
	imshow("vertical", canny_image);
	// Inverse vertical image
	//bitwise_not(canny_image, canny_image);
	bitwise_xor(canny_image, canny_image2, img_result2);
	bitwise_not(img_result2, img_result2);
	imshow("vertical_bit", img_result2);
	waitKey(0);


	int horizontalsize = img_result2.cols / 8;

	Mat structure = getStructuringElement(MORPH_RECT, Size(horizontalsize, 1));

	erode(img_result2, img_result2, structure, Point(-1, -1));
	dilate(img_result2, img_result2, structure, Point(-1, -1));
	imshow("horizontalsize", img_result2);
	waitKey(0);

	hconcat(img_gray, img_result2, img_result); //두 이미지의 높이(row)가 같아야함.
	imshow("result", img_result);
	waitKey(0);

	blur(img_result2, img_result2, Size(7, 7));
	Canny(img_result2, img_result2, 30, 30 * 3, 3,true);
	imshow("Canny", img_result2);
	waitKey(0);

	//직선 성분을 검출합니다.  
	// 왼쪽 차선 검출
	//vector<Vec2f> linesL, linesR;

	//for (int i = 10; i > 0; i--)
	//{
	//	int threshold = (canny_image3.rows + canny_image3.cols) * i / 10;
	//	HoughLines(canny_image3, linesL, 1, CV_PI / 180, threshold, 0, 0);// , CV_PI / 8, CV_PI);
	//	if (linesL.size() > 0)
	//	{
	//		for (size_t i = 0; i < linesL.size(); i++)
	//		{
	//			float rho = linesL[i][0];
	//			float theta = linesL[i][1];
	//			double a = cos(theta), b = sin(theta);
	//			double x0 = a * rho, y0 = b * rho;
	//			Point pt1(cvRound(x0 + (canny_image3.rows + canny_image3.cols) * (-b)),
	//				cvRound(y0 + (canny_image3.rows + canny_image3.cols) * (a)) + canny_image3.rows / 2);
	//			Point pt2(cvRound(x0 - (canny_image3.rows + canny_image3.cols) * (-b)),
	//				cvRound(y0 - (canny_image3.rows + canny_image3.cols) * (a)) + canny_image3.rows / 2);

	//			cv::line(img_input, pt1, pt2, Scalar(0, 0, 255));
	//		}
	//		break;
	//	}
	//}

	//imshow("right", img_input);
	//waitKey(0);

	// 오른쪽 차선 검출
	/*for (int i = 10; i > 0; i--)
	{
		int threshold = (grayImg.rows + grayImg.cols) * i / 10;
		HoughLines(cannyImg, linesR, 1, CV_PI / 180, threshold, 0, 0, CV_PI / 2, CV_PI);
		if (linesR.size() > 0)
		{
			for (size_t i = 0; i < linesR.size(); i++)
			{
				float rho = linesR[i][0];
				float theta = linesR[i][1];
				double a = cos(theta), b = sin(theta);
				double x0 = a * rho, y0 = b * rho;
				Point pt1(cvRound(x0 + (grayImg.rows + grayImg.cols) * (-b)),
					cvRound(y0 + (grayImg.rows + grayImg.cols) * (a)) + grayImg.rows / 2);
				Point pt2(cvRound(x0 - (grayImg.rows + grayImg.cols) * (-b)),
					cvRound(y0 - (grayImg.rows + grayImg.cols) * (a)) + grayImg.rows / 2);

				cv::line(originImg, pt1, pt2, COLOR_RED);
			}
			break;
		}
	}*/

	//선 감지 위한 허프 변환



	vector<Vec2f> lines;
	HoughLines(canny_image4, lines, 1, CV_PI / 180, 80);
	//선그리기
	Mat result(canny_image4.rows, canny_image4.cols, CV_8U, Scalar(255));
	cout << "Lines detected: " << lines.size() << endl;
	//선 벡터를 반복해 선 그리기
	//vector<Vec2f>::const_iterator it = lines.begin();
	//while (it != lines.end()) {
	//	float rho = (*it)[0]; // 0번째 rho거리
	//	float theta = (*it)[1]; //1번째 세타 각도
	//	if ((theta > 0.8) && (theta < 0.9)) {
	//		Point pt1(rho / cos(theta), 0); // 첫 행에서 해당선 교차점
	//		Point pt2((rho - result.rows*sin(theta)) / cos(theta), result.rows); // 마지막 행에서 해당 선의 교차점
	//		line(img_input, pt1, pt2, Scalar(0, 0, 255), 1); // 하얀선으로 그리기
	//	}
	//	else if ((theta > 2.2) && (theta < 2.35)) { //수평행
	//		Point pt1(0, rho / sin(theta));
	//		Point pt2(result.cols, (rho - result.cols*cos(theta) / sin(theta)));
	//		line(img_input, pt1, pt2, Scalar(0, 255), 1);
	//	}
	//	//cout << "line: (" << rho << "," << theta << ")\n";
	//	++it;
	//}
	std::vector<cv::Vec2f>::const_iterator it = lines.begin();
	while (it != lines.end()) {
		float rho = (*it)[0];   // 첫 번째 요소는 rho 거리
		float theta = (*it)[1]; // 두 번째 요소는 델타 각도
		if (theta < CV_PI / 4. || theta > CV_PI / 2) { // 수직 행
			cv::Point pt1(rho / cos(theta), 0); // 첫 행에서 해당 선의 교차점   
			cv::Point pt2((rho - result.rows*sin(theta)) / cos(theta), result.rows);
			// 마지막 행에서 해당 선의 교차점
			cv::line(img_input, pt1, pt2, cv::Scalar(0,255,0), 1); // 하얀 선으로 그리기

		}
		//else { // 수평 행
		//	cv::Point pt1(0, rho / sin(theta)); // 첫 번째 열에서 해당 선의 교차점  
		//	cv::Point pt2(result.cols, (rho - result.cols*cos(theta)) / sin(theta));
		//	// 마지막 열에서 해당 선의 교차점
		//	cv::line(img_input, pt1, pt2, cv::Scalar(255,0,0), 1); // 하얀 선으로 그리기
		//}
		std::cout << "line: (" << rho << "," << theta << ")\n";
		++it;
	}
	imshow("Detected Lines with Hough", img_input);
	waitKey(0);



	//vector<Vec4i> lines;
	//HoughLinesP(canny_image, lines, 1, 1 * CV_PI / 180, 20, 0, 0);
	////검출한 직선을 영상에 그려줍니다.  
	//for (int j = 0; j<lines.size(); j++)
	//{
	//	//Vec4i L = linesL[j];
	//	Vec4i L = lines[j];
	//	line(img_gray, Point(L[0], L[1]), Point(L[2], L[3]),
	//		Scalar(0, 0, 255), 1, LINE_AA);
	//}
	////cvNamedWindow("result", WINDOW_AUTOSIZE);
	//imshow("line", img_gray);
	//cout << "a:" << img_input.depth() << ",b:" << canny_image.depth() << endl;
	//waitKey(0);
	//hconcat(img_gray, canny_image, img_result); //두 이미지의 높이(row)가 같아야함.
	//imshow("result", img_result);
	//waitKey(0);
	
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