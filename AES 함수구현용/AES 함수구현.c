
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

const unsigned char roundConstant[10] = { 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1b, 0x36 };

//각 함수에 입력된 state[16]를 연산 후 다시 state[16]에 다시 저장하세요//
//Ex) 바뀌기전 state[2]={0x02, 0x07} -> 연산 후 state[2]={0x05, 0x7a}  //

void AddRoundKey(unsigned char state[16], const unsigned char roundKey[16])
{

}

void SubBytes(unsigned char state[16])
{

}


void ShiftRows(unsigned char state[16])
{

}

void MixColumns(unsigned char state[16])
{

}

void KeyExpansion(unsigned char roundKey[11][16], const unsigned char masterKey[16]) //AES - 128 KeyExpansion 구현
{

}





#include <stdio.h>
#include <stdlib.h>

int main()
{
	unsigned char plainText[16] = { 0x32, 0x43, 0xf6, 0xa8, 0x88, 0x5a, 0x30, 0x8d, 0x31, 0x31, 0x98, 0xa2, 0xe0, 0x37, 0x07, 0x34 };
	unsigned char key[16] = { 0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6, 0xab, 0xf7, 0x15, 0x88, 0x09, 0xcf, 0x4f, 0x3c }; //마스터 키

	printf("[ plain text ] - ");
	for (int i = 0; i < 16; i++) {
		printf("%02x ", plainText[i]);
	}
	printf("\n\n");

	printf("[     key    ] - ");
	for (int i = 0; i < 16; i++) {
		printf("%02x ", key[i]);
	}
	printf("\n\n\n");

	unsigned char state[16] = { 0, };
	for (int i = 0; i < 16; i++)
		state[i] = plainText[i];

	AddRoundKey(state, key);
	unsigned char AddRoundKeyOutput[16] = { 0x19, 0x3d, 0xe3, 0xbe, 0xa0, 0xf4, 0xe2, 0x2b, 0x9a, 0xc6, 0x8d, 0x2a, 0xe9, 0xf8, 0x48, 0x08 };
	for (int i = 0; i < 16; i++) {
		if (state[i] != AddRoundKeyOutput[i]) {
			printf("----- AddRoundKey Fail -----\n");
			system("pause");
			return 0;
		}
	}
	printf("**** AddRoundKey Success!!! ****\n\n");

	SubBytes(state);
	unsigned char SubBytesOutput[16] = { 0xd4, 0x27, 0x11, 0xae, 0xe0, 0xbf, 0x98, 0xf1, 0xb8, 0xb4, 0x5d, 0xe5, 0x1e, 0x41, 0x52, 0x30 };
	for (int i = 0; i < 16; i++) {
		if (state[i] != SubBytesOutput[i]) {
			printf("----- SubBytes Fail -----\n");
			system("pause");
			return 0;
		}
	}
	printf("**** SubBytes Success!!! ****\n\n");

	ShiftRows(state);
	unsigned char ShiftRowsOutput[16] = { 0xd4, 0xbf, 0x5d, 0x30, 0xe0, 0xb4, 0x52, 0xae, 0xb8, 0x41, 0x11, 0xf1, 0x1e, 0x27, 0x98, 0xe5 };
	for (int i = 0; i < 16; i++) {
		if (state[i] != ShiftRowsOutput[i]) {
			printf("----- ShiftRows Fail -----\n");
			system("pause");
			return 0;
		}
	}
	printf("**** ShiftRows Success!!! ****\n\n");


	MixColumns(state);
	unsigned char MixColumnsOutput[16] = { 0x04, 0x66, 0x81, 0xe5, 0xe0, 0xcb, 0x19, 0x9a, 0x48, 0xf8, 0xd3, 0x7a, 0x28, 0x06, 0x26, 0x4c };
	for (int i = 0; i < 16; i++) {
		if (state[i] != MixColumnsOutput[i]) {
			printf("----- MixColumns Fail -----\n");
			system("pause");
			return 0;
		}
	}
	printf("**** MixColumns Success!!! *****\n\n");


	// test key expansion

	unsigned char standardRoundKey[11][16] = { 0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6, 0xab, 0xf7, 0x15, 0x88, 0x09, 0xcf, 0x4f, 0x3c,
												0xa0, 0xfa, 0xfe, 0x17, 0x88, 0x54, 0x2c, 0xb1, 0x23, 0xa3, 0x39, 0x39, 0x2a, 0x6c, 0x76, 0x5,
												0xf2, 0xc2, 0x95, 0xf2, 0x7a, 0x96, 0xb9, 0x43, 0x59, 0x35, 0x80, 0x7a, 0x73, 0x59, 0xf6, 0x7f,
												0x3d, 0x80, 0x47, 0x7d, 0x47, 0x16, 0xfe, 0x3e, 0x1e, 0x23, 0x7e, 0x44, 0x6d, 0x7a, 0x88, 0x3b,
												0xef, 0x44, 0xa5, 0x41, 0xa8, 0x52, 0x5b, 0x7f, 0xb6, 0x71, 0x25, 0x3b, 0xdb, 0x0b, 0xad, 0x00,
												0xd4, 0xd1, 0xc6, 0xf8, 0x7c, 0x83, 0x9d, 0x87, 0xca, 0xf2, 0xb8, 0xbc, 0x11, 0xf9, 0x15, 0xbc,
												0x6d, 0x88, 0xa3, 0x7a, 0x11, 0xb, 0x3e, 0xfd, 0xdb, 0xf9, 0x86, 0x41, 0xca, 0x0, 0x93, 0xfd,
												0x4e, 0x54, 0xf7, 0xe, 0x5f, 0x5f, 0xc9, 0xf3, 0x84, 0xa6, 0x4f, 0xb2, 0x4e, 0xa6, 0xdc, 0x4f,
												0xea, 0xd2, 0x73, 0x21, 0xb5, 0x8d, 0xba, 0xd2, 0x31, 0x2b, 0xf5, 0x60, 0x7f, 0x8d, 0x29, 0x2f,
												0xac, 0x77, 0x66, 0xf3, 0x19, 0xfa, 0xdc, 0x21, 0x28, 0xd1, 0x29, 0x41, 0x57, 0x5c, 0x0, 0x6e,
												0xd0, 0x14, 0xf9, 0xa8, 0xc9, 0xee, 0x25, 0x89, 0xe1, 0x3f, 0xc, 0xc8, 0xb6, 0x63, 0xc, 0xa6 };

	unsigned char userRoundKey[11][16] = { 0, };
	KeyExpansion(userRoundKey, key);
	for (int i = 0; i < 11; i++) {
		for (int j = 0; j < 16; j++) {
			if (standardRoundKey[i][j] != userRoundKey[i][j]) {
				printf("---- KeyExpansion Fail ----\n\n");
				printf("---------> standardRoundKey: %#x != userRoundKey: %#x \n---------> 틀린 위치 : userRoundKey[%d][%d]\n", standardRoundKey[i][j], userRoundKey[i][j], i, j);

				system("pause");
				return 0;
			}
		}
	}
	printf("**** KeyExpansion Success!!!! ****\n\n     수고하셨습니다~~~~~ :)");
}