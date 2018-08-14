#include "stdafx.h"
#include "03Wavelet2.h"
#include "03Wavelet3.h"
#include "04HighPassFilter.h"
#include "05LowPassFilter.h"

int polarTransforms(int camNumber);
int histogram03(String filePath);
int logPolarTest(String filePath);
int process(VideoCapture& capture);

int main()
{
	int result = 1;

	imshow("raw", imread("GIRL.RAW", 1));
	waitKey();
	/*HighPassFilter HighPassFilter;
	
	char in_name[100];
	
	cout << "Digital HighPassFilter Processing - High Pass Filter\n" << endl;
	cout << "Enter the Input HighPassFilter Name : ";
	cin >> in_name;
	
	HighPassFilter.ReadHighPassFilter(in_name);
	HighPassFilter.Masking();*/



	//result = polarTransforms(0);
	//result = histogram03("./../../[00Images]/etc/lena.png");
	//result = logPolarTest("./../../[00Images]/etc/lena.png");

	/*int array[1][1] = { 0 };
	printf_s("test0:%d\n", array[0][0]);
	array[0][0] = 100;
	printf_s("test1:%d\n", array[0][0]);
	array[0][0]++;
	printf_s("test2:%d\n", array[0][0]);
	int tmp = 100;
	array[0][0] += tmp;
	printf_s("test3:%d\n", array[0][0]);
	array[0][0] /= 5 * 4;
	printf_s("test4:%d\n", array[0][0]);
	system("pause");*/

	/*VideoCapture capture(0);
	if (!capture.isOpened())
	{
		return 1;
	}
	result = process(capture);*/
	
	//Mat im = imread("./../../[00Images]/etc/lena.png", 0); //Load image in Gray Scale
	//imshow("good?", im);
	//waitKey();

	/*image my;
	result = my.getim("./../../[00Images]/etc/lena.jpg");*/


	//int i;
	//char buf[512];
	//for (i = 0; i < 7; i++) {
	//	//sprintf(buf, "wavelet_lena512_22_%d.raw", i + 1);
	//	wavelet_encoder_jty("./lena512.raw", buf, 'a', i + 1);

	//	//sprintf(buf, "wavelet_lena512_swe_%d.raw", i + 1);
	//	wavelet_encoder_jty("./lena512.raw", buf, 'b', i + 1);

	//	//sprintf(buf, "wavelet_lena512_crf_%d.raw", i + 1);
	//	wavelet_encoder_jty("./lena512.raw", buf, 'c', i + 1);
	//}

	//int i1[10] = { 0 };
	//int i2[2] = { 3,6 };
	//for (size_t i = 0; i < sizeof(i); i++)
	//{
	//	cout << i1[i];// << endl;
	//}
	//cout << "" << endl;
	//cout << i1 << endl;
	//cout << i2 << endl;
	//memcpy(i1, i2, sizeof(int)*2);
	//for (size_t i = 0; i < sizeof(i); i++)
	//{
	//	cout << i1[i];// << endl;
	//}
	//cout << "" << endl;
	//cout << i1 << endl;

	/*int a, b, c, d = 10;
	cout << a << " " << b << " " << c << " " << d << " " << endl;*/
	
	//system("pause");
	//waitKey();
	return result;
}