class HighPassFilter {
private:
	int Width;
	int Height;
	int Row, Col;
	unsigned char *Orig;
	unsigned char *Result;
	int *temp;

	// 사용할 함수 선언
public:
	HighPassFilter(int _Width = 256, int _Height = 256);
	~HighPassFilter();
	void ReadHighPassFilter(char *);
	void WriteHighPassFilter(char *);
	void Initialize();
	void Masking();
	void Satur();
};