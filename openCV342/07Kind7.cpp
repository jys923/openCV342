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
		//Canny(canny_image, canny_image, 125, 125 * 3, 3);
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
		/*Point center(cvRound(circles[0][0]), cvRound(circles[0][1]));
		int radius(cvRound(circles[0][2]));*/

		//Rect(cvRound(circles[0][0]) - cvRound(circles[0][2]), cvRound(circles[0][1]) - cvRound(circles[0][2])*2.5, cvRound(circles[0][2]) *2,;


	}
	adaptiveThreshold(img_gray,img_gray,255, ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY_INV, 55, 10);
	imshow("threshold", img_gray);
	waitKey(0);
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
	cv::morphologyEx(img_gray, img_gray, MORPH_OPEN, elements5);
	
	
	
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

//Mat src; Mat src_gray;
//int thresh = 100;
//int max_thresh = 255;
//RNG rng(12345);
//void thresh_callback(int, void*);
//int testContours()
//{
//	src = imread("./../../[00Images]/eyes/sample/test.bmp");
//	if (src.empty())
//	{
//		cerr << "No image supplied ..." << endl;
//		return -1;
//	}
//	cvtColor(src, src_gray, COLOR_BGR2GRAY);
//	blur(src_gray, src_gray, Size(3, 3));
//	const char* source_window = "Source";
//	namedWindow(source_window, WINDOW_AUTOSIZE);
//	imshow(source_window, src);
//	createTrackbar(" Canny thresh:", "Source", &thresh, max_thresh, thresh_callback);
//	thresh_callback(0, 0);
//	waitKey(0);
//	return(0);
//}
//void thresh_callback(int, void*)
//{
//	Mat canny_output;
//	vector<vector<Point> > contours;
//	vector<Vec4i> hierarchy;
//	Canny(src_gray, canny_output, thresh, thresh * 2, 3);
//	findContours(canny_output, contours, hierarchy, RETR_TREE, CHAIN_APPROX_NONE, Point(0, 0));
//	Mat drawing = Mat::zeros(canny_output.size(), CV_8UC3);
//	for (size_t i = 0; i< contours.size(); i++)
//	{
//		Scalar color = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
//		drawContours(drawing, contours, (int)i, color, 2, 8, hierarchy, 0, Point());
//	}
//	namedWindow("Contours", WINDOW_AUTOSIZE);
//	imshow("Contours", drawing);
//}

bool lineIntersection(cv::Point2f &c1, cv::Point2f &c2, cv::Point2f &d1, cv::Point2f &d2, cv::Point2f &intersection) {
	/*

	두 점 A(x1, y1), B(x2, y2)을 잇는 직선의 방정식
	y = ax + b (a : 기울기 = y증가량/x증가량, b : 상수)
	a = (y2-y1)/(x2-x1)
	y = (y2-y1)/(x2-x1)x + b
	b = y - (y2-y1)/(x2-x1)x
	b = y1 - (y2-y1)/(x2-x1)x1

	!!!!! y = (y2-y1)/(x2-x1)x + (y1 - (y2-y1)/(x2-x1)x1) !!!!!

	방정식 1 : y = a1x + b1
	방정식 2 : y = a2x + b2
	(a1-a2)x = (b2-b1)
	x = (b2-b1)/(a1-a2)
	방정식 1에 대입하면
	y = a1((b2-b1)/(a1-a2)) + b1
	 
	교점의 좌표 (x,y) = ( (b2-b1)/(a1-a2), a1((b2-b1)/(a1-a2)) + b1)

	 */

	float a1, b1, a2, b2;
	a1 = (c2.y - c1.y) / (c2.x - c1.x);
	//b1 = c1.y - (((c2.y - c1.y) / (c2.x - c1.x))*c1.x);
	b1 = c1.y - (a1*c1.x);
	//cout << "test:x:" << intersection.x << endl;

	a2 = (d2.y - d1.y) / (d2.x - d1.x);
	//b2 = d1.y - (((d2.y - d1.y) / (d2.x - d1.x))*d1.x);
	b2 = d1.y - (a2*d1.x);

	if (a1 == a2) return false;//평행이나 일치인 경우

	intersection.x = (b2- b1) / (a1 - a2);
	intersection.y = a1*(intersection.x) + b1;
	cout << "test:x:" << intersection.x << endl;
	cout << "test:y:" << intersection.y << endl;
	return true;

}

int testLib2()
{
	// Declare the output variables
	Mat dst, cdst, cdstP,gau;
	//const char* default_file = "../data/sudoku.png";
	//const char* filename = argc >= 2 ? argv[1] : default_file;
	String filename = "./../../[00Images]/eyes/libs/(8).bmp";
	// Loads an image
	Mat src = imread(filename, IMREAD_COLOR);
	// Check if image is loaded fine
	if (src.empty()) {
		printf(" Error opening image\n");
		//printf(" Program Arguments: [image_name -- default %s] \n", default_file);
		return -1;
	}
	imshow("src", src);
	waitKey(0);
	if (false)
	{
		//교점
		Point2f c1(40.0, 20.0);
		Point2f c2(60.0, 10.0);
		Point2f d1(35.0, 40.0);
		Point2f d2(70.0, 100.0);
		Point2f inter;

		//void circle(Mat& img, Point center, int radius, const Scalar& color, int thickness = 1, int lineType = 8, int shift = 0)
		circle(src, c1, 2, Scalar(255, 0, 0), -1, LINE_8);
		circle(src, c2, 2, Scalar(255, 0, 0), -1, LINE_8);
		circle(src, d1, 2, Scalar(255, 0, 0), -1, LINE_8);
		circle(src, d2, 2, Scalar(255, 0, 0), -1, LINE_8);
		line(src, c1, c2, Scalar(0, 0, 255), 1, LINE_8);
		line(src, d1, d2, Scalar(0, 0, 255), 1, LINE_8);
		imshow("draw", src);
		waitKey(0);

		bool test = lineIntersection(c1, c2, d1, d2, inter);
		cout << "test:" << test << endl;
		cout << "test:x:" << inter.x << endl;
		cout << "test:y:" << inter.y << endl;
		circle(src, inter, 2, Scalar(0, 255, 0), -1, LINE_8);
		imshow("draw", src);
		waitKey(0);
	}

	int GBi = 9;
	//GaussianBlur(src, gau, Size(GBi, GBi), 0.0, 0.0);
	medianBlur(src, gau, GBi);
	imshow("gau", gau);
	waitKey(0);
	//
	//adaptiveThreshold(gau, gau, 230, ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY_INV, 7, 5);
	imshow("Thr", gau);
	waitKey(0);

	/*GaussianBlur(gau, gau, Size(GBi, GBi), 0.0, 0.0);
	imshow("gau", gau);
	waitKey(0);*/
	// Edge detection
	int Ci = 50;
	Canny(gau, dst, Ci, Ci*3, 3);
	// Copy edges to the images that will display the results in BGR
	cvtColor(dst, cdst, COLOR_GRAY2BGR);
	cdstP = cdst.clone();
	// Standard Hough Line Transform
	vector<Vec2f> lines; // will hold the results of the detection
	HoughLines(dst, lines, 1, CV_PI / 180, 27, 0, 0); // runs the actual detection
													   // Draw the lines
	for (size_t i = 0; i < lines.size(); i++)
	{
		float rho = lines[i][0], theta = lines[i][1];

		/*Point pt1, pt2;
		double a = cos(theta), b = sin(theta);
		double x0 = a * rho, y0 = b * rho;
		pt1.x = cvRound(x0 + 1000 * (-b));
		pt1.y = cvRound(y0 + 1000 * (a));
		pt2.x = cvRound(x0 - 1000 * (-b));
		pt2.y = cvRound(y0 - 1000 * (a));
		line(cdst, pt1, pt2, Scalar(0, 0, 255), 3, CV_AA);*/

		if (theta < CV_PI / 3.0 || theta > CV_PI *2. / 3.) { // 수직 행
			Point pt1(rho / cos(theta), 0); // 첫 행에서 해당 선의 교차점   
			Point pt2((rho - cdst.rows*sin(theta)) / cos(theta), cdst.rows);
			// 마지막 행에서 해당 선의 교차점
			//line(cdst, pt1, pt2, Scalar(255,0,0), 3); // 하얀 선으로 그리기
		}
		else if (CV_PI / 3.0 <theta && theta < CV_PI *2. / 3.){ // 수평 행
			Point pt1(0, rho / sin(theta)); // 첫 번째 열에서 해당 선의 교차점  
			Point pt2(cdst.cols, (rho - cdst.cols*cos(theta)) / sin(theta));
			// 마지막 열에서 해당 선의 교차점
			line(cdst, pt1, pt2, Scalar(0,0,255), 3); // 하얀 선으로 그리기
		}
	}

	imshow("line", cdst);
	waitKey(0);
	// Probabilistic Line Transform
	vector<Vec4i> linesP; // will hold the results of the detection
	HoughLinesP(dst, linesP, 1, CV_PI / 180, 50, 50, 10); // runs the actual detection
														  // Draw the lines
	for (size_t i = 0; i < linesP.size(); i++)
	{
		Vec4i l = linesP[i];
		line(cdstP, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0, 0, 255), 3, LINE_AA);
	}
	// Show results
	imshow("Source", src);
	imshow("Detected Lines (in red) - Standard Hough Line Transform", cdst);
	imshow("Detected Lines (in red) - Probabilistic Line Transform", cdstP);
	// Wait and Exit
	waitKey();
	return 0;
}

int testUpperLib()
{
	Mat img_input, img_gray, canny_image, img_result3;
	String path = "./../../[00Images]/eyes/libs/";
	String fileName = "line2.jpg";
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



	//vector<Vec2f> lines;
	//HoughLines(canny_image4, lines, 1, CV_PI / 180, 80);
	////선그리기
	//Mat result(canny_image4.rows, canny_image4.cols, CV_8U, Scalar(255));
	//cout << "Lines detected: " << lines.size() << endl;
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

	vector<Vec2f> lines;
	HoughLines(canny_image4, lines, 1, CV_PI / 180, 80);
	//선그리기
	Mat result(canny_image4.rows, canny_image4.cols, CV_8U, Scalar(255));
	cout << "Lines detected: " << lines.size() << endl;
	std::vector<cv::Vec2f>::const_iterator it = lines.begin();
	while (it != lines.end()) {
		float rho = (*it)[0];   // 첫 번째 요소는 rho 거리
		float theta = (*it)[1]; // 두 번째 요소는 델타 각도
		//if (theta < CV_PI && theta > CV_PI / 2) { // 수직 행
		//if (0 < theta && theta < CV_PI/6) { // 수직 행
		//if (0 < theta && theta < CV_PI/12) { // 수직 행
		if (CV_PI * 11 / 12  < theta && theta < CV_PI) { // 수직 행
		//if (theta == 3) { // 수직 행
			cv::Point pt1(rho / cos(theta), 0); // 첫 행에서 해당 선의 교차점   
			cv::Point pt2((rho - result.rows*sin(theta)) / cos(theta), result.rows);
			// 마지막 행에서 해당 선의 교차점
			cv::line(img_input, pt1, pt2, cv::Scalar(0,255,0), 1); // 하얀 선으로 그리기

		}
		//else if (CV_PI * 11 / 12  < theta && theta < CV_PI) { // 수직 행
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

void CCVController::MakeKind7Imag(IplImage* pImage, int pupilCenterX, int pupilCenterY, int IrisCenterX, int IrisCenterY, int pupilRadius, int IrisRadius)
{
	//1 샘플이미지 추출

	//1-1 Kind3 생성  
	int crop_x = IrisCenterX - IrisRadius - (IrisRadius * 0.6);
	int crop_y = IrisCenterY - IrisRadius - (IrisRadius * 0.2);
	int crop_w = (2 * IrisRadius) + ((IrisRadius * 0.6) * 2);
	int crop_h = (2 * IrisRadius) + ((IrisRadius * 0.2) * 2);

	CString size = "";
	size.Format("x %d y %d w %d h %d r %d w %d h %d", crop_x, crop_y, crop_w, crop_h, IrisRadius, pImage->width, pImage->height);
	AfxMessageBox(size);

	if (crop_x < 0)
		crop_x = 0;
	if (crop_y < 0)
		crop_y = 0;
	if (crop_w < 0)
		crop_w = 0;
	if (crop_x < 0)
		crop_h = 0;

	Mat imgMat(pImage);
	Mat kind3_ROI(imgMat, Rect(crop_x, crop_y, crop_w, crop_h));
	Mat kind3;
	//Copy the data into new matrix
	kind3_ROI.copyTo(kind3);

#ifdef DEBUG_MAKE_KIND7_IMAGE
	//IplImage *kind3_trans = &IplImage(kind3);
	//cvShowImage("kind3", kind3_trans);
	//cvWaitKey(0);
#endif


	int sample1_crop_x = pupilCenterX - pupilRadius;
	int sample1_crop_y = pupilCenterY - IrisRadius;
	int sample1_crop_w = pupilRadius * 2;
	int sample1_crop_h = IrisRadius - pupilRadius;


	Mat sample1_ROI(imgMat, Rect(sample1_crop_x, sample1_crop_y, sample1_crop_w, sample1_crop_h));
	//Mat sample1;
	//Copy the data into new matrix
	//sample1_ROI.copyTo(sample1);


#ifdef DEBUG_MAKE_KIND7_IMAGE
	//IplImage *smaple1_trans = &IplImage(sample1_ROI);
	//cvShowImage("sample1", smaple1_trans);
	//cvWaitKey(0);
#endif

	//2 눈꺼플 경계 좌표 획득 
	FindEyelid(sample1_ROI, 0); // Mode :: 0 - upper center , 1 - lower center , 3 - other 
}

bool CCVController::FindEyelid(Mat sampleImg, int mode)
{

	//AfxMessageBox("FindEyelid");
	int found_point = 0; // upper center 
	if (mode == 0)
	{

	}
	else if (mode == 1) // lower center 
	{

	}
	else // other
	{

	}

	Mat sampleImg_GB;
	//Reduce Iris feature 
	GaussianBlur(sampleImg, sampleImg_GB, Size(15, 15), 0, 0);

	//Remove eyelid skin and Iris 
	//Find eyelid
	Mat retImg(sampleImg.size(), CV_8UC1, Scalar(0, 0, 0));
	int threshold_value = 10;
	double PI = 3.1415926;
	bool d_state = false;
	Mat sampleImg_TH;
	Mat sampleImg_CN;
	while (threshold_value <= 250)
	{
		threshold(sampleImg_GB, sampleImg_TH, threshold_value, 255, 0); // 0: Binary 1: Binary Inverted 2: Threshold Truncated 3: Threshold to Zero 4: Threshold to Zero Inverted
		threshold_value = threshold_value + 10;

		//#ifdef DEBUG_MAKE_KIND7_IMAGE
		//      IplImage *sampleImg_TH_trans = &IplImage(sampleImg_TH);
		//      cvShowImage("smaple1_trans", sampleImg_TH_trans);
		//      cvWaitKey(0);
		//#endif

		//convert to canny edge
		Canny(sampleImg_TH, sampleImg_CN, 10, 150);

		//std::vector<Vec2f> lines;
		//cv::HoughLines(sampleImg_CN, NULL, 1, PI / 180, 30);

		//Mat dst; Canny(sampleImg_TH, dst, 50, 200, 3);
		//Mat cdst; cvtColor(dst, cdst, CV_GRAY2BGR);

		//vector<Vec2f> lines;
		//HoughLines(dst, lines, 1, CV_PI / 180, 30, 0, 0);

		//CString lsize = "";
		//lsize.Format("size : %d", lines.size());
		//AfxMessageBox(lsize);



		//Mat colorCannyThresh = sampleImg_CN.clone();
		//cvtColor(colorCannyThresh, colorCannyThresh, CV_GRAY2BGR);


		//IplImage *sampleImg_trans8 = &IplImage(colorCannyThresh);
		//cvShowImage("sampleImg_trans8", sampleImg_trans8);
		//cvWaitKey(0);

		//eyelid detection(line detection)
		//lines = cv2.HoughLines(canny, 1, np.pi / 180, 15)


		vector<Vec2f> lines;
		HoughLines(sampleImg_CN, lines, 1, PI / 180, 30);
		//HoughLines(sampleImg_CN, lines, 1, CV_PI / 180, 25, 0, 0);

		//decide eyelid line among the lines 
		std::vector<cv::Vec2f>::const_iterator it = lines.begin();
		int sum = 0;
		//if lines is not None: 
		//for i in xrange(len(lines)) :


		//CString lsize = "";
		//lsize.Format("size : %d", lines.size());
		//AfxMessageBox(lsize);


		while (it != lines.end())
		{
			CString lsize = "";
			lsize.Format("size2 : %d", lines.size());
			//AfxMessageBox(lsize);

			//for rho, theta in lines[i] :
			float rho = (*it)[0];   // 첫 번째 요소는 rho 거리
			float theta = (*it)[1]; // 두 번째 요소는 델타 각도
									//a = np.cos(theta) b = np.sin(theta) x0 = a*rho y0 = b*rho
			float a = cos(theta);
			float b = sin(theta);
			float x0 = a * rho;
			float y0 = b * rho;
			//x1 = int(x0 + 1000 * (-b)) y1 = int(y0 + 1000 * (a)) x2 = int(x0 - 1000 * (-b)) y2 = int(y0 - 1000 * (a))
			int x1 = int(x0 + 1000 * (-b));
			int y1 = int(y0 + 1000 * (a));
			int x2 = int(x0 - 1000 * (-b));
			int y2 = int(y0 - 1000 * (a));
			//if abs(y2 - y1) < 1000 :
			found_point = abs(y2 - y1);
			CString s_val = "";
			s_val.Format("%d", abs(y2 - y1));

			if (abs(y2 - y1) < 800)
			{
				AfxMessageBox("find : " + s_val);
				d_state = true;
				sum++;
				//cv2.line(img, (x1, y1), (x2, y2), (0, 0, 255), 2)
				cv::line(sampleImg, Point(x1, y1), Point(x2, y2), Scalar(255, 255, 255), 1, 8, 0);

				//break;
			}

			//if (theta < PI / 4. || theta > 3.*PI / 4.) //수직 
			//{
			//cv::Point pt1(rho / cos(theta), 0); // 첫 행에서 해당 선의 교차점   
			//}

			++it; //Next
		}

		if (d_state)
		{
			IplImage *sampleImg_trans1 = &IplImage(sampleImg);
			cvShowImage("sampleImg_trans5", sampleImg_trans1);
			cvWaitKey(0);
			//CString str_line = "";
			//str_line.Format("last sum : %d", sum);
			//AfxMessageBox(str_line);
			break;
		}


#ifdef DEBUG_MAKE_KIND7_IMAGE
		//IplImage *retImg_trans = &IplImage(retImg);
		IplImage *sampleImg_trans = &IplImage(sampleImg);
		IplImage *sampleImg_CN_trans = &IplImage(sampleImg_CN);
		//cvShowImage("retImg_trans", retImg_trans);
		cvShowImage("sampleImg_trans", sampleImg_trans);
		cvShowImage("sampleImg_CN_trans", sampleImg_CN_trans);
		cvWaitKey(0);
		cvDestroyAllWindows();
#endif

	}


	return found_point;
}