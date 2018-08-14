#include "stdafx.h"

int polarTransforms(int camNumber);
int histogram03(String filePath);
int logPolarTest(String filePath);

int main()
{
	int result = polarTransforms(0);
	//int result = histogram03("./../../[00Images]/etc/lena.png");
	//int result = logPolarTest("./../../[00Images]/etc/lena.png");
	return result;
}