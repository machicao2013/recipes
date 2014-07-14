#ifndef SD_BASE_64_CODE_H
#define SD_BASE_64_CODE_H

class SDBase64Code
{
public:
	static void encode(unsigned char *out, const unsigned char *in, int inlen);
	static int decode(char *out, const char *in);
};

#endif // SD_BASE_64_CODE_H

