#include "targetver.h"

#define TWOTWO	0
#define SWE		1
#define CRF		2


void wavelet_encoder_jty(const char* ifile, char* ofile, char filter, int label);
//void wavelet_encoder_jty( const unsigned char* ifile, unsigned char* ofile, char filter, int label );
void wavelet_decoder_jty(unsigned char* ifile, unsigned char* ofile, char filter, int label);