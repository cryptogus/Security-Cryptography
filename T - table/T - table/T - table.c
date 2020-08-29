

#include <stdio.h>
#include <stdlib.h>

#define True	1
#define False	0

int compare(char testName[100], unsigned char userOutput[16], unsigned char standardOutput[16])
{
	printf("[ %s\tTest ]\t", testName);

	int result = True;
	for (int i = 0; i < 16; i++)
		if (userOutput[i] != standardOutput[i])
			result = False;

	if (!result)
	{
		printf("Fail\n");
		printf("| Index\t\t|\tYour Output\tStandard Output\n");
		for (int i = 0; i < 16; i++)
			if (userOutput[i] != standardOutput[i])
				printf("| %02d byte\t|\t%02x\t\t%02x\n", i, userOutput[i], standardOutput[i]);
		printf("\n");
	}
	else
		printf("Success\n");

	return result;
}

const unsigned char SBox[256] = {
	0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5, 0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76,
	0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0, 0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0,
	0xb7, 0xfd, 0x93, 0x26, 0x36, 0x3f, 0xf7, 0xcc, 0x34, 0xa5, 0xe5, 0xf1, 0x71, 0xd8, 0x31, 0x15,
	0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a, 0x07, 0x12, 0x80, 0xe2, 0xeb, 0x27, 0xb2, 0x75,
	0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0, 0x52, 0x3b, 0xd6, 0xb3, 0x29, 0xe3, 0x2f, 0x84,
	0x53, 0xd1, 0x00, 0xed, 0x20, 0xfc, 0xb1, 0x5b, 0x6a, 0xcb, 0xbe, 0x39, 0x4a, 0x4c, 0x58, 0xcf,
	0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85, 0x45, 0xf9, 0x02, 0x7f, 0x50, 0x3c, 0x9f, 0xa8,
	0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5, 0xbc, 0xb6, 0xda, 0x21, 0x10, 0xff, 0xf3, 0xd2,
	0xcd, 0x0c, 0x13, 0xec, 0x5f, 0x97, 0x44, 0x17, 0xc4, 0xa7, 0x7e, 0x3d, 0x64, 0x5d, 0x19, 0x73,
	0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88, 0x46, 0xee, 0xb8, 0x14, 0xde, 0x5e, 0x0b, 0xdb,
	0xe0, 0x32, 0x3a, 0x0a, 0x49, 0x06, 0x24, 0x5c, 0xc2, 0xd3, 0xac, 0x62, 0x91, 0x95, 0xe4, 0x79,
	0xe7, 0xc8, 0x37, 0x6d, 0x8d, 0xd5, 0x4e, 0xa9, 0x6c, 0x56, 0xf4, 0xea, 0x65, 0x7a, 0xae, 0x08,
	0xba, 0x78, 0x25, 0x2e, 0x1c, 0xa6, 0xb4, 0xc6, 0xe8, 0xdd, 0x74, 0x1f, 0x4b, 0xbd, 0x8b, 0x8a,
	0x70, 0x3e, 0xb5, 0x66, 0x48, 0x03, 0xf6, 0x0e, 0x61, 0x35, 0x57, 0xb9, 0x86, 0xc1, 0x1d, 0x9e,
	0xe1, 0xf8, 0x98, 0x11, 0x69, 0xd9, 0x8e, 0x94, 0x9b, 0x1e, 0x87, 0xe9, 0xce, 0x55, 0x28, 0xdf,
	0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68, 0x41, 0x99, 0x2d, 0x0f, 0xb0, 0x54, 0xbb, 0x16 };

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
unsigned char mix2(unsigned char b) {
	
	unsigned char x;
	
	if (b >> 7 == 0) {
		x = b << 1;
	}
	else {
		x = (b << 1) ^ 0b00011011;
	}
	return x;
}
unsigned char mix3(unsigned char a) {
	
	unsigned char x;
	
	if (a >> 7 == 1) {
		x = (a << 1) ^ 0b00011011 ^ a;
	}
	else {
		x = (a << 1) ^ a;
	}
	return x;
}

///////////////////////////////// T - table 함수 //////////////////////////////////
unsigned int T1(unsigned int a0) {
	unsigned int x;
	x = mix2(a0) << 24 ^ a0 << 16 ^ a0 << 8 ^ mix3(a0);
	return x;
}

unsigned int T2(unsigned int a1) {
	unsigned int x;
	x = mix3(a1) << 24 ^ mix2(a1) << 16 ^ a1 << 8 ^ a1;
	return x;
}

unsigned int T3(unsigned int a2) {
	unsigned int x;
	x = a2 << 24 ^ mix3(a2) << 16 ^ mix2(a2) << 8 ^ a2;
	return x;
}

unsigned int T4(unsigned int a3) {
	unsigned int x;
	x = a3 << 24 ^ a3 << 16 ^ mix3(a3) << 8 ^ mix2(a3);
	return x;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
unsigned char userCipherText[16] = { 0, };
unsigned char standardCipherText[16] = { 0x39, 0x25, 0x84, 0x1d, 0x02, 0xdc, 0x09, 0xfb, 0xdc, 0x11, 0x85, 0x97, 0x19, 0x6a, 0x0b, 0x32 };

const unsigned char roundConstant[10] = { 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1b, 0x36 };

int main()
{
	unsigned char plainText[16] = { 0x32, 0x43, 0xf6, 0xa8, 0x88, 0x5a, 0x30, 0x8d, 0x31, 0x31, 0x98, 0xa2, 0xe0, 0x37, 0x07, 0x34 },x,y,z;
	unsigned int roundKey[16] = { 0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6, 0xab, 0xf7, 0x15, 0x88, 0x09, 0xcf, 0x4f, 0x3c };  /*마스터키*/
	unsigned int A, B, C, D, key32[4] = { 0, };

	//////////////////첫번째 Add Round////////////////////
	for (int i = 0; i < 16; i++)
	{
		plainText[i] = plainText[i] ^ roundKey[i];
	}
	///////////////////////////////////////////////////
	

	/*1~9라운드*/

	for (int k = 0; k < 9; k++) {

		/*Keyschedule*/

		roundKey[0] = roundKey[0] ^ roundConstant[k] ^ SBox[roundKey[13]];//G func
		roundKey[1] = roundKey[1] ^ SBox[roundKey[14]];
		roundKey[2] = roundKey[2] ^ SBox[roundKey[15]];
		roundKey[3] = roundKey[3] ^ SBox[roundKey[12]];

		for (int i = 0; i < 12; i++)
			roundKey[i + 4] = roundKey[i] ^ roundKey[i + 4];
		//////////////////////////////////////////////////////////

		//key를 32bit로 합친다.
		for (int u = 0; u <= 3; u++)
			key32[u] = roundKey[4*u] << 24 ^ roundKey[4*u + 1] << 16 ^ roundKey[4*u + 2] << 8 ^ roundKey[4*u + 3];

		/*T - table*/
		A = T1(SBox[plainText[0]]) ^ T2(SBox[plainText[5]]) ^ T3(SBox[plainText[10]]) ^ T4(SBox[plainText[15]]) ^ key32[0];
		B = T1(SBox[plainText[4]]) ^ T2(SBox[plainText[9]]) ^ T3(SBox[plainText[14]]) ^ T4(SBox[plainText[3]]) ^ key32[1];
		C = T1(SBox[plainText[8]]) ^ T2(SBox[plainText[13]]) ^ T3(SBox[plainText[2]]) ^ T4(SBox[plainText[7]]) ^ key32[2];
		D = T1(SBox[plainText[12]]) ^ T2(SBox[plainText[1]]) ^ T3(SBox[plainText[6]]) ^ T4(SBox[plainText[11]]) ^ key32[3];
		

		plainText[0] = A >> 24 & 0xff;											/*반복문이용도 가능*/
		plainText[1] = A >> 16 & 0xff;
		plainText[2] = A >> 8 & 0xff;
		plainText[3] = A & 0xff;

		plainText[4] = B >> 24 & 0xff;
		plainText[5] = B >> 16 & 0xff;
		plainText[6] = B >> 8 & 0xff;
		plainText[7] = B & 0xff;

		plainText[8] = C >> 24 & 0xff;
		plainText[9] = C >> 16 & 0xff;
		plainText[10] = C >> 8 & 0xff;
		plainText[11] = C & 0xff;

		plainText[12] = D >> 24 & 0xff;
		plainText[13] = D >> 16 & 0xff;
		plainText[14] = D >> 8 & 0xff;
		plainText[15] = D & 0xff;
	}

	/*10Round*/
	roundKey[0] = roundKey[0] ^ roundConstant[9] ^ SBox[roundKey[13]];
	roundKey[1] = roundKey[1] ^ SBox[roundKey[14]];
	roundKey[2] = roundKey[2] ^ SBox[roundKey[15]];
	roundKey[3] = roundKey[3] ^ SBox[roundKey[12]];

	for (int i = 0; i < 12; i++)//word 40~43
		roundKey[i + 4] = roundKey[i] ^ roundKey[i + 4];

	for (int i = 0; i < 16; i++)
		plainText[i] = SBox[plainText[i]];

	//ShiftRows
	x = plainText[1];
	plainText[1] = plainText[5];
	plainText[5] = plainText[9];
	plainText[9] = plainText[13];
	plainText[13] = x;
	x = plainText[2], y = plainText[6];
	plainText[2] = plainText[10];
	plainText[6] = plainText[14];
	plainText[10] = x;
	plainText[14] = y;

	x = plainText[3], y = plainText[7], z = plainText[11];
	plainText[3] = plainText[15];
	plainText[7] = x;
	plainText[11] = y;
	plainText[15] = z;

	//AddRound
	for (int i = 0; i < 16; i++)
	{
		userCipherText[i] = plainText[i] ^ roundKey[i];
	}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	if (!compare("AES T - table", userCipherText, standardCipherText))
	{
		system("pause");
		return 1;
	}


	printf("\n");
	printf("\t*******************\n");
	printf("\t* Test Success!!! *\n");
	printf("\t*******************\n\n");

	for (int a = 0; a < 16; a++) {

		printf("userCipherText[%d] = %d,  standardCipherText[%d] = %d \n", a, userCipherText[a], a, standardCipherText[a]);
	}

	system("pause");
	return 0;
}