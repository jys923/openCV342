#include "stdafx.h"

//void OnWavelet()
//{
//	// TODO: 여기에 명령 처리기 코드를 추가합니다.
//	static double Low[5] = { 0.602949f, 0.266864, -0.078223f, -0.016864f, 0.026749f };
//	static double High[4] = { 1.115086f, -0.591272f, -0.057544f, 0.091272f };
//	int i, j, k;
//	double *buffer;
//	double *DWT;
//	buffer = new double[4 + 256 + 4];
//	DWT = new double[256 * 256];
//	memset(DWT, 0, sizeof(double)*(256 * 256));
//	memset(buffer, 0, sizeof(double) * (4 + 256 + 4));
//	double temp, Max_L = -10e10, Min_L = 10e10;
//	double Max_H = -10e10, Min_H = 10e10;
//	//////////////////////////////////////////
//	for (i = 0; i<256; i++) {
//		for (k = 0; k<256; k++) buffer[k + 4] = m_InputImage[i][k];
//
//		for (j = 0; j<256; j += 2) {
//			temp = Low[0] * buffer[j + 4]
//				+ Low[1] * (buffer[j + 3] + buffer[j + 5])
//				+ Low[2] * (buffer[j + 2] + buffer[j + 6])
//				+ Low[3] * (buffer[j + 1] + buffer[j + 7])
//				+ Low[4] * (buffer[j] + buffer[j + 8]);
//			DWT[i * 256 + (int)j / 2] = temp;
//
//			if (temp>Max_L) Max_L = temp;
//			if (temp<Min_L) Min_L = temp;
//		}
//		/////////////////////////////
//		for (j = 0; j<256; j += 2) {
//			temp = High[0] * buffer[j + 4]
//				+ High[1] * (buffer[j + 3] + buffer[j + 5])
//				+ High[2] * (buffer[j + 2] + buffer[j + 6])
//				+ High[3] * (buffer[j + 1] + buffer[j + 7]);
//
//			DWT[i * 256 + (int)j / 2 + 128] = temp;
//		}
//	}
//	memset(buffer, 0, sizeof(double) * (256 + 4 + 4));
//	double Max_LL = -10e10, Min_LL = 10e10;
//	double Max_LH = -10e10, Min_LH = 10e10;
//	double Max_HL = -10e10, Min_HL = 10e10;
//	double Max_HH = -10e10, Min_HH = 10e10;
//
//	for (j = 0; j<128; j++)
//	{
//		for (k = 0; k<256; k++) buffer[k + 4] = DWT[k * 256 + j];
//		for (i = 0; i<256; i += 2) {
//			temp = Low[0] * buffer[j + 4]
//				+ Low[1] * (buffer[j + 3] + buffer[j + 5])
//				+ Low[2] * (buffer[j + 2] + buffer[j + 6])
//				+ Low[3] * (buffer[j + 1] + buffer[j + 7])
//				+ Low[4] * (buffer[j] + buffer[j + 8]);
//			DWT[i * 256 + (int)j / 2] = temp;
//
//			if (temp>Max_LL) Max_LL = temp;
//			if (temp<Min_LL) Min_LL = temp;
//		}
//		for (i = 0; i<256; i += 2) {
//			temp = High[0] * buffer[i + 4]
//				+ High[1] * (buffer[i + 3] + buffer[i + 5])
//				+ High[2] * (buffer[i + 2] + buffer[i + 6])
//				+ High[3] * (buffer[i + 1] + buffer[i + 7]);
//			DWT[((int)(i / 2) + 128) * 256 + j] = temp;
//			if (temp>Max_LH) Max_LH = temp;
//			if (temp>Min_LH) Min_LH = temp;
//		}
//	}
//
//	for (j = 128; j<256; j++)
//	{
//		for (k = 0; k<256; k++) buffer[k + 4] = DWT[k * 256 + j];
//		for (i = 0; i<256; i += 2) {
//			temp = Low[0] * buffer[i + 4]
//				+ Low[1] * (buffer[i + 3] + buffer[i + 5])
//				+ Low[2] * (buffer[i + 2] + buffer[i + 6])
//				+ Low[3] * (buffer[i + 1] + buffer[i + 7])
//				+ Low[4] * (buffer[i] + buffer[i + 8]);
//
//			DWT[(int)(i / 2) * 256 + j] = temp;
//			if (temp>Max_HL) Max_HL = temp;
//			if (temp<Min_HL) Min_HL = temp;
//		}
//		for (i = 0; i<256; i += 2) {
//			temp = High[0] * buffer[i + 4]
//				+ High[1] * (buffer[i + 3] + buffer[i + 5])
//				+ High[2] * (buffer[i + 2] + buffer[i + 6])
//				+ High[3] * (buffer[i + 1] + buffer[i + 7]);
//
//			DWT[((int)(i / 2) + 128) * 256 + j] = temp;
//			if (temp>Max_HH) Max_HH = temp;
//			if (temp<Min_HH) Min_HH = temp;
//		}
//	}
//	double C1 = (double)(255.0 / (Max_LL - Min_LL));
//	double C2 = (double)(-255.0*Min_LL / (Max_LL - Min_LL));
//	for (i = 0; i<128; i++) {
//		for (j = 0; j<128; j++)
//			m_OutputImage[i][j] = (unsigned char)(C1*DWT[i * 256 + j] + C2);
//	}
//	C1 = (double)(255.0 / (Max_HL - Min_HL));
//	C2 = (double)(-255.0*Min_HL / (Max_HL - Min_HL));
//	for (i = 0; i<128; i++) {
//		for (j = 128; j<256; j++)
//			m_OutputImage[i][j] = (unsigned char)(C1*DWT[i * 256 + j] + C2);
//	}
//	C1 = (double)(255.0 / (Max_HH - Min_HH));
//	C2 = (double)(-255.0*Min_HH / (Max_HH - Min_HH));
//
//	for (i = 128; i<256; i++) {
//		for (j = 128; j<256; j++)
//			m_OutputImage[i][j] = (unsigned char)(C1*DWT[i * 256 + j] + C2);
//	}
//	delete[] buffer;
//	delete[] DWT;
//	UpdateAllViews(NULL);
//}