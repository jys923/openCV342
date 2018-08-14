#include "stdafx.h"
#include "05LowPassFilter.h"

class LowPassFilter {
private:
	int Width;
	int Height;
	int Row, Col;
	unsigned char *Orig;
	unsigned char *Result;
	int *temp;

	// ����� �Լ� ����
public:
	LowPassFilter(int _Width = 256, int _Height = 256);
	~LowPassFilter();
	void ReadLowPassFilter(char *);
	void WriteLowPassFilter(char *);
	void Initialize();
	void Masking();
	void Satur();
};

// Ŭ���� ����
LowPassFilter::LowPassFilter(int _Width, int _Height)
{
	Width = _Width;
	Height = _Height;
	Orig = new unsigned char[Width*Height];
	Result = new unsigned char[Width*Height];
	temp = new int[Width*Height];
}
//Ŭ���� �Ҹ�
LowPassFilter::~LowPassFilter()
{
	delete[]Orig;
	delete[]Result;
	delete[]temp;
}

// Main �Լ�
void main()
{
	LowPassFilter LowPassFilter;

	char in_name[20];

	cout << "Digital LowPassFilter Processing - Low Pass Filter\n" << endl;
	cout << "Enter the Input LowPassFilter Name : ";
	cin >> in_name;

	LowPassFilter.ReadLowPassFilter(in_name);
	LowPassFilter.Masking();
}


// ����ũ ó�� �Լ� - �����������(LPF)
void LowPassFilter::Masking()
{
	int m, n;
	double norm = 0;
	char blurring[20] = "result.raw";

	// Ŀ�ΰ� ����
	double kernel[3][3] = { { 1, 1, 1 },
	{ 1, 1, 1 },
	{ 1, 1, 1 } };

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
	WriteLowPassFilter(blurring);

}

// ó�� ����� �����ϴ� temp�迭 �ʱ�ȭ �Լ�
void LowPassFilter::Initialize()
{
	for (Row = 0; Row<Height; Row++) {
		for (Col = 0; Col<Width; Col++) {
			temp[Row*Width + Col] = 0;
		}
	}
}


// �̹��� �Է� �Լ�
void LowPassFilter::ReadLowPassFilter(char *f_name)
{
	ifstream infile;
	infile.open(f_name, ios::binary);

	if (infile.fail()) {
		cout << "Input LowPassFilter not Exist.." << endl;
		exit(1);
	}

	infile.read((char *)Orig, Width*Height);
	infile.close();
}

// �̹��� ��� �Լ�
void LowPassFilter::WriteLowPassFilter(char *f_name)
{
	ofstream outfile;
	outfile.open(f_name, ios::binary);

	outfile.write((const char *)Result, Width*Height);

	outfile.close();
}

// ���� ������ ������ ���� �Լ�
void LowPassFilter::Satur()
{
	for (Row = 0; Row<Height; Row++) {
		for (Col = 0; Col<Width; Col++) {
			if (temp[Row*Width + Col] < 0) Result[Row*Width + Col] = 0;
			else if (temp[Row*Width + Col] > 255) Result[Row*Width + Col] = 255;
			else Result[Row*Width + Col] = temp[Row*Width + Col];
		}
	}
}