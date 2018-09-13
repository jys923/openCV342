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
	String fileName = "406.bmp";
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