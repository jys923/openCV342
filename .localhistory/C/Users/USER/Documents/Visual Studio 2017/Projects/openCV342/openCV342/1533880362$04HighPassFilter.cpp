#include "stdafx.h"
#include "04HighPassFilter.h"

// 클래스 생성
HighPassFilter::HighPassFilter(int _Width, int _Height)
{
	Width = _Width;
	Height = _Height;
	Orig = new unsigned char[Width*Height];
	Result = new unsigned char[Width*Height];
	temp = new int[Width*Height];
}
//클래스 소멸
HighPassFilter::~HighPassFilter()
{
	delete[]Orig;
	delete[]Result;
	delete[]temp;
}

// Main 함수
void main()
{
	HighPassFilter HighPassFilter;

	char in_name[20];

	cout << "Digital HighPassFilter Processing - High Pass Filter\n" << endl;
	cout << "Enter the Input HighPassFilter Name : ";
	cin >> in_name;

	HighPassFilter.ReadHighPassFilter(in_name);
	HighPassFilter.Masking();
}


// 샤퍼닝(Sharpening) 및 기타 과정 처리 함수
void HighPassFilter::Masking()
{
	int m, n;
	double norm = 0;
	char sharpening[20] = "result.raw";

	// 커널값 설정
	double kernel[3][3] = 
	{ 
		{ -1, -1, -1 },
		{ -1,  12, -1 },
		{ -1, -1, -1 } 
	};

	// 커널의 정규값(Normalization)을 구하기 위한 연산
	for (m = 0; m<3; m++) {
		for (n = 0; n<3; n++) {
			norm += kernel[m][n];
		}
	}
	if (norm == 0)
		norm = 1;
	else
		norm = 1 / norm;

	Initialize();

	// 마스킹 과정: 컨벌루션 진행
	for (Row = 1; Row<Height - 1; Row++) {
		for (Col = 1; Col<Width - 1; Col++) {
			for (m = 0; m<3; m++) {
				for (n = 0; n<3; n++) {
					temp[Row*Width + Col] += (kernel[m][n] * (double)Orig[(Row - 1 + m)*Width + (Col - 1 + n)]) * norm;
				}
			}
		}
	}

	// 마스킹 작업 후 값이 정해지지 않은 외곽부분 메우기
	for (Row = 0; Row<Height; Row++) {
		for (Col = 0; Col<Width; Col++) {
			switch (Row) {
			case 0:
				temp[Row*Width + Col] = temp[(Row + 1)*Width + Col];
				break;
			case 255:
				temp[Row*Width + Col] = temp[(Row - 1)*Width + Col];
				break;
			}
		}
	}
	for (Row = 0; Row<Height; Row++) {
		for (Col = 0; Col<Width; Col++) {
			switch (Col) {
			case 0:
				temp[Row*Width + Col] = temp[Row*Width + Col + 1];
				break;
			case 255:
				temp[Row*Width + Col] = temp[Row*Width + Col - 1];
				break;
			}
		}
	}

	Satur();
	WriteHighPassFilter(sharpening);
}

// 처리 결과를 저장하는 temp배열 초기화 함수
void HighPassFilter::Initialize()
{
	for (Row = 0; Row<Height; Row++) {
		for (Col = 0; Col<Width; Col++) {
			temp[Row*Width + Col] = 0;
		}
	}
}

// 이미지 입력 함수
void HighPassFilter::ReadHighPassFilter(char *f_name)
{
	ifstream infile;
	infile.open(f_name, ios::binary);

	if (infile.fail()) {
		cout << "Input HighPassFilter not Exist.." << endl;
		exit(1);
	}

	infile.read((char *)Orig, Width*Height);
	infile.close();
}

// 이미지 출력 함수
void HighPassFilter::WriteHighPassFilter(char *f_name)
{
	ofstream outfile;
	outfile.open(f_name, ios::binary);

	outfile.write((const char *)Result, Width*Height);

	outfile.close();
}

// 영상 데이터 사이즈 제한 함수
void HighPassFilter::Satur()
{
	for (Row = 0; Row<Height; Row++) {
		for (Col = 0; Col<Width; Col++) {
			if (temp[Row*Width + Col] < 0) Result[Row*Width + Col] = 0;
			else if (temp[Row*Width + Col] > 255) Result[Row*Width + Col] = 255;
			else Result[Row*Width + Col] = temp[Row*Width + Col];
		}
	}
}