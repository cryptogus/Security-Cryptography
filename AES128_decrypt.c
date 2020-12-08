const unsigned char inv_SBox[256] = {
	0x52, 0x09, 0x6a, 0xd5, 0x30, 0x36, 0xa5, 0x38, 0xbf, 0x40, 0xa3, 0x9e, 0x81, 0xf3, 0xd7, 0xfb,
	0x7c, 0xe3, 0x39, 0x82, 0x9b, 0x2f, 0xff, 0x87, 0x34, 0x8e, 0x43, 0x44, 0xc4, 0xde, 0xe9, 0xcb,
	0x54, 0x7b, 0x94, 0x32, 0xa6, 0xc2, 0x23, 0x3d, 0xee, 0x4c, 0x95, 0x0b, 0x42, 0xfa, 0xc3, 0x4e,
	0x08, 0x2e, 0xa1, 0x66, 0x28, 0xd9, 0x24, 0xb2, 0x76, 0x5b, 0xa2, 0x49, 0x6d, 0x8b, 0xd1, 0x25,
	0x72, 0xf8, 0xf6, 0x64, 0x86, 0x68, 0x98, 0x16, 0xd4, 0xa4, 0x5c, 0xcc, 0x5d, 0x65, 0xb6, 0x92,
	0x6c, 0x70, 0x48, 0x50, 0xfd, 0xed, 0xb9, 0xda, 0x5e, 0x15, 0x46, 0x57, 0xa7, 0x8d, 0x9d, 0x84,
	0x90, 0xd8, 0xab, 0x00, 0x8c, 0xbc, 0xd3, 0x0a, 0xf7, 0xe4, 0x58, 0x05, 0xb8, 0xb3, 0x45, 0x06,
	0xd0, 0x2c, 0x1e, 0x8f, 0xca, 0x3f, 0x0f, 0x02, 0xc1, 0xaf, 0xbd, 0x03, 0x01, 0x13, 0x8a, 0x6b,
	0x3a, 0x91, 0x11, 0x41, 0x4f, 0x67, 0xdc, 0xea, 0x97, 0xf2, 0xcf, 0xce, 0xf0, 0xb4, 0xe6, 0x73,
	0x96, 0xac, 0x74, 0x22, 0xe7, 0xad, 0x35, 0x85, 0xe2, 0xf9, 0x37, 0xe8, 0x1c, 0x75, 0xdf, 0x6e,
	0x47, 0xf1, 0x1a, 0x71, 0x1d, 0x29, 0xc5, 0x89, 0x6f, 0xb7, 0x62, 0x0e, 0xaa, 0x18, 0xbe, 0x1b,
	0xfc, 0x56, 0x3e, 0x4b, 0xc6, 0xd2, 0x79, 0x20, 0x9a, 0xdb, 0xc0, 0xfe, 0x78, 0xcd, 0x5a, 0xf4,
	0x1f, 0xdd, 0xa8, 0x33, 0x88, 0x07, 0xc7, 0x31, 0xb1, 0x12, 0x10, 0x59, 0x27, 0x80, 0xec, 0x5f,
	0x60, 0x51, 0x7f, 0xa9, 0x19, 0xb5, 0x4a, 0x0d, 0x2d, 0xe5, 0x7a, 0x9f, 0x93, 0xc9, 0x9c, 0xef,
	0xa0, 0xe0, 0x3b, 0x4d, 0xae, 0x2a, 0xf5, 0xb0, 0xc8, 0xeb, 0xbb, 0x3c, 0x83, 0x53, 0x99, 0x61,
	0x17, 0x2b, 0x04, 0x7e, 0xba, 0x77, 0xd6, 0x26, 0xe1, 0x69, 0x14, 0x63, 0x55, 0x21, 0x0c, 0x7d
};
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


const unsigned char roundConstant[10] = { 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1b, 0x36 };//key확장시 g함수 구현



unsigned char mix_2(unsigned char b) {
	unsigned char x;
	if (b >> 7 == 0) {
		x = b << 1;
	}
	else {
		x = (b << 1) ^ 0b00011011;
	}
	return x;
}
unsigned char mix_3(unsigned char a) {
	unsigned char x;
	if (a >> 7 == 1) {
		x = (a << 1) ^ 0b00011011 ^ a;
	}
	else {
		x = (a << 1) ^ a;
	}
	return x;
}
unsigned char mix4(unsigned char b) {
	unsigned char x;
	if (mix_2(b) >> 7 == 0) {
		x = mix_2(b) << 1;
	}
	else {
		x = (mix_2(b) << 1) ^ 0b00011011;
	}
	return x;
}
unsigned char mix8(unsigned char b) {
	unsigned char x;
	if (mix4(b) >> 7 == 0) {
		x = mix4(b) << 1;
	}
	else {
		x = (mix4(b) << 1) ^ 0b00011011;
	}
	return x;

}
unsigned char mix9(unsigned char b) {
	unsigned char x;
	x = mix8(b) ^ b;
	return x;
}
unsigned char mix_b(unsigned char b) {
	unsigned char x;
	x = mix8(b) ^ mix_3(b);
	return x;
}
unsigned char mix_d(unsigned char b) {
	unsigned char x;
	x = mix8(b) ^ mix4(b) ^ b;
	return x;
}
unsigned char mix_e(unsigned char b) {
	unsigned char x;
	x = mix8(b) ^ mix4(b) ^ mix_2(b);
	return x;
}
void AES_De(unsigned char plainText[16], unsigned char cipherText[16], unsigned char key[16])
{
	unsigned char roundKey[11][16] = { 0, };

	//Round Key를 미리 만들어둠
	for (int j = 0; j < 16; j++) //word 0~3
		roundKey[0][j] = key[j];

	roundKey[1][0] = roundKey[0][0] ^ roundConstant[0] ^ SBox[roundKey[0][13]];//G func
	roundKey[1][1] = roundKey[0][1] ^ SBox[roundKey[0][14]];
	roundKey[1][2] = roundKey[0][2] ^ SBox[roundKey[0][15]];
	roundKey[1][3] = roundKey[0][3] ^ SBox[roundKey[0][12]];

	for (int i = 0; i < 12; i++)//word4~7
		roundKey[1][i + 4] = roundKey[1][i] ^ roundKey[0][i + 4];

	roundKey[2][0] = roundKey[1][0] ^ roundConstant[1] ^ SBox[roundKey[1][13]];
	roundKey[2][1] = roundKey[1][1] ^ SBox[roundKey[1][14]];
	roundKey[2][2] = roundKey[1][2] ^ SBox[roundKey[1][15]];
	roundKey[2][3] = roundKey[1][3] ^ SBox[roundKey[1][12]];

	for (int i = 0; i < 12; i++)//word8~11
		roundKey[2][i + 4] = roundKey[2][i] ^ roundKey[1][i + 4];

	roundKey[3][0] = roundKey[2][0] ^ roundConstant[2] ^ SBox[roundKey[2][13]];
	roundKey[3][1] = roundKey[2][1] ^ SBox[roundKey[2][14]];
	roundKey[3][2] = roundKey[2][2] ^ SBox[roundKey[2][15]];
	roundKey[3][3] = roundKey[2][3] ^ SBox[roundKey[2][12]];

	for (int i = 0; i < 12; i++)//word 12~15
		roundKey[3][i + 4] = roundKey[3][i] ^ roundKey[2][i + 4];

	roundKey[4][0] = roundKey[3][0] ^ roundConstant[3] ^ SBox[roundKey[3][13]];
	roundKey[4][1] = roundKey[3][1] ^ SBox[roundKey[3][14]];
	roundKey[4][2] = roundKey[3][2] ^ SBox[roundKey[3][15]];
	roundKey[4][3] = roundKey[3][3] ^ SBox[roundKey[3][12]];

	for (int i = 0; i < 12; i++)//word 16~19
		roundKey[4][i + 4] = roundKey[4][i] ^ roundKey[3][i + 4];

	roundKey[5][0] = roundKey[4][0] ^ roundConstant[4] ^ SBox[roundKey[4][13]];
	roundKey[5][1] = roundKey[4][1] ^ SBox[roundKey[4][14]];
	roundKey[5][2] = roundKey[4][2] ^ SBox[roundKey[4][15]];
	roundKey[5][3] = roundKey[4][3] ^ SBox[roundKey[4][12]];

	for (int i = 0; i < 12; i++)//word 20~23
		roundKey[5][i + 4] = roundKey[5][i] ^ roundKey[4][i + 4];

	roundKey[6][0] = roundKey[5][0] ^ roundConstant[5] ^ SBox[roundKey[5][13]];
	roundKey[6][1] = roundKey[5][1] ^ SBox[roundKey[5][14]];
	roundKey[6][2] = roundKey[5][2] ^ SBox[roundKey[5][15]];
	roundKey[6][3] = roundKey[5][3] ^ SBox[roundKey[5][12]];

	for (int i = 0; i < 12; i++)//word 24~27
		roundKey[6][i + 4] = roundKey[6][i] ^ roundKey[5][i + 4];

	roundKey[7][0] = roundKey[6][0] ^ roundConstant[6] ^ SBox[roundKey[6][13]];
	roundKey[7][1] = roundKey[6][1] ^ SBox[roundKey[6][14]];
	roundKey[7][2] = roundKey[6][2] ^ SBox[roundKey[6][15]];
	roundKey[7][3] = roundKey[6][3] ^ SBox[roundKey[6][12]];

	for (int i = 0; i < 12; i++)//word 28~31
		roundKey[7][i + 4] = roundKey[7][i] ^ roundKey[6][i + 4];

	roundKey[8][0] = roundKey[7][0] ^ roundConstant[7] ^ SBox[roundKey[7][13]];
	roundKey[8][1] = roundKey[7][1] ^ SBox[roundKey[7][14]];
	roundKey[8][2] = roundKey[7][2] ^ SBox[roundKey[7][15]];
	roundKey[8][3] = roundKey[7][3] ^ SBox[roundKey[7][12]];

	for (int i = 0; i < 12; i++)//word 32~35
		roundKey[8][i + 4] = roundKey[8][i] ^ roundKey[7][i + 4];

	roundKey[9][0] = roundKey[8][0] ^ roundConstant[8] ^ SBox[roundKey[8][13]];
	roundKey[9][1] = roundKey[8][1] ^ SBox[roundKey[8][14]];
	roundKey[9][2] = roundKey[8][2] ^ SBox[roundKey[8][15]];
	roundKey[9][3] = roundKey[8][3] ^ SBox[roundKey[8][12]];

	for (int i = 0; i < 12; i++)//word 36~39
		roundKey[9][i + 4] = roundKey[9][i] ^ roundKey[8][i + 4];

	roundKey[10][0] = roundKey[9][0] ^ roundConstant[9] ^ SBox[roundKey[9][13]];
	roundKey[10][1] = roundKey[9][1] ^ SBox[roundKey[9][14]];
	roundKey[10][2] = roundKey[9][2] ^ SBox[roundKey[9][15]];
	roundKey[10][3] = roundKey[9][3] ^ SBox[roundKey[9][12]];

	for (int i = 0; i < 12; i++)//word 40~43
		roundKey[10][i + 4] = roundKey[10][i] ^ roundKey[9][i + 4];

	//////////////키 저장 끝///////////

	unsigned char state[16] = { 0, };
	unsigned char x, y, z;
	unsigned char state2[16] = { 0, };


	//---------------------------------------------------------------------------------
	for (int i = 0; i < 16; i++)
	{
		state[i] = cipherText[i] ^ roundKey[10][i];
	}
	//----------------------------------------------------------------------------
	for (int j = 1; j < 10; j++)// 1~9라운드
	{


		//Inv ShiftRows
		x = state[1];
		state[1] = state[13];
		state[13] = state[9];
		state[9] = state[5];
		state[5] = x;
		x = state[2], y = state[6];
		state[2] = state[10];
		state[6] = state[14];
		state[10] = x;
		state[14] = y;

		x = state[3], y = state[7], z = state[11];
		state[3] = y;
		state[7] = z;
		state[11] = state[15];
		state[15] = x;

		/////////Inv sbox///////////////////

		for (int i = 0; i < 16; i++)
			state[i] = inv_SBox[state[i]];

		//AddRound
		for (int i = 0; i < 16; i++)
		{
			state[i] = state[i] ^ roundKey[10 - j][i];
		}


		for (int k = 0; k < 16; k++)
			state2[k] = state[k];

		//InvMixColumns
		state[0] = mix_e(state2[0]) ^ mix_b(state2[1]) ^ mix_d(state2[2]) ^ mix9(state2[3]);
		state[4] = mix_e(state2[4]) ^ mix_b(state2[5]) ^ mix_d(state2[6]) ^ mix9(state2[7]);
		state[8] = mix_e(state2[8]) ^ mix_b(state2[9]) ^ mix_d(state2[10]) ^ mix9(state2[11]);
		state[12] = mix_e(state2[12]) ^ mix_b(state2[13]) ^ mix_d(state2[14]) ^ mix9(state2[15]);
		state[1] = mix9(state2[0]) ^ mix_e(state2[1]) ^ mix_b(state2[2]) ^ mix_d(state2[3]);
		state[5] = mix9(state2[4]) ^ mix_e(state2[5]) ^ mix_b(state2[6]) ^ mix_d(state2[7]);
		state[9] = mix9(state2[8]) ^ mix_e(state2[9]) ^ mix_b(state2[10]) ^ mix_d(state2[11]);
		state[13] = mix9(state2[12]) ^ mix_e(state2[13]) ^ mix_b(state2[14]) ^ mix_d(state2[15]);
		state[2] = mix_d(state2[0]) ^ mix9(state2[1]) ^ mix_e(state2[2]) ^ mix_b(state2[3]);
		state[6] = mix_d(state2[4]) ^ mix9(state2[5]) ^ mix_e(state2[6]) ^ mix_b(state2[7]);
		state[10] = mix_d(state2[8]) ^ mix9(state2[9]) ^ mix_e(state2[10]) ^ mix_b(state2[11]);
		state[14] = mix_d(state2[12]) ^ mix9(state2[13]) ^ mix_e(state2[14]) ^ mix_b(state2[15]);
		state[3] = mix_b(state2[0]) ^ mix_d(state2[1]) ^ mix9(state2[2]) ^ mix_e(state2[3]);
		state[7] = mix_b(state2[4]) ^ mix_d(state2[5]) ^ mix9(state2[6]) ^ mix_e(state2[7]);
		state[11] = mix_b(state2[8]) ^ mix_d(state2[9]) ^ mix9(state2[10]) ^ mix_e(state2[11]);
		state[15] = mix_b(state2[12]) ^ mix_d(state2[13]) ^ mix9(state2[14]) ^ mix_e(state2[15]);

	}
	//10 라운드

//Inv ShiftRows
	x = state[1];
	state[1] = state[13];
	state[13] = state[9];
	state[9] = state[5];
	state[5] = x;
	x = state[2], y = state[6];
	state[2] = state[10];
	state[6] = state[14];
	state[10] = x;
	state[14] = y;

	x = state[3], y = state[7], z = state[11];
	state[3] = y;
	state[7] = z;
	state[11] = state[15];
	state[15] = x;

	/////////Inv sbox///////////////////

	for (int i = 0; i < 16; i++)
		state[i] = inv_SBox[state[i]];

	//AddRound
	for (int i = 0; i < 16; i++)
	{
		plainText[i] = state[i] ^ roundKey[0][i];
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
