#include "stdafx.h"
#include "04HighPassFilter.h"

// Ŭ���� ����
HighPassFilter::HighPassFilter(int _Width, int _Height)
{
	Width = _Width;
	Height = _Height;
	Orig = new unsigned char[Width*Height];
	Result = new unsigned char[Width*Height];
	temp = new int[Width*Height];
}
//Ŭ���� �Ҹ�
HighPassFilter::~HighPassFilter()
{
	delete[]Orig;
	delete[]Result;
	delete[]temp;
}

// Main �Լ�
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


// ���۴�(Sharpening) �� ��Ÿ ���� ó�� �Լ�
void HighPassFilter::Masking()
{
	int m, n;
	double norm = 0;
	char sharpening[20] = "result.raw";

	// Ŀ�ΰ� ����
	double kernel[3][3] = 
	{ 
		{ -1, -1, -1 },
		{ -1,  12, -1 },
		{ -1, -1, -1 } 
	};

	// Ŀ���� ���԰�(Normalization)�� ���ϱ� ���� ����
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

	// ����ŷ ����: ������� ����
	for (Row = 1; Row<Height - 1; Row++) {
		for (Col = 1; Col<Width - 1; Col++) {
			for (m = 0; m<3; m++) {
				for (n = 0; n<3; n++) {
					temp[Row*Width + Col] += (kernel[m][n] * (double)Orig[(Row - 1 + m)*Width + (Col - 1 + n)]) * norm;
				}
			}
		}
	}

	// ����ŷ �۾� �� ���� �������� ���� �ܰ��κ� �޿��
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

// ó�� ����� �����ϴ� temp�迭 �ʱ�ȭ �Լ�
void HighPassFilter::Initialize()
{
	for (Row = 0; Row<Height; Row++) {
		for (Col = 0; Col<Width; Col++) {
			temp[Row*Width + Col] = 0;
		}
	}
}

// �̹��� �Է� �Լ�
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

// �̹��� ��� �Լ�
void HighPassFilter::WriteHighPassFilter(char *f_name)
{
	ofstream outfile;
	outfile.open(f_name, ios::binary);

	outfile.write((const char *)Result, Width*Height);

	outfile.close();
}

// ���� ������ ������ ���� �Լ�
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