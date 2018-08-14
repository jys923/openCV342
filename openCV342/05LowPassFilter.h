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
