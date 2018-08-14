#include "stdafx.h"
#include "03Wavelet2.h"

int polarTransforms(int camNumber);
int histogram03(String filePath);
int logPolarTest(String filePath);
int process(VideoCapture& capture);

int main()
{
	int result = 1;
	//result = polarTransforms(0);
	//int result = histogram03("./../../[00Images]/etc/lena.png");
	//int result = logPolarTest("./../../[00Images]/etc/lena.png");

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

	VideoCapture capture(0);
	if (!capture.isOpened())
	{
		return 1;
	}
	result = process(capture);
	//return result;
	
	image my;
	result = my.getim("./../../[00Images]/etc/lena.png");
	system("pause"); 
	return result;
}