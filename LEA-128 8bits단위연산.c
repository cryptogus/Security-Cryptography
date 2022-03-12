/****************************************************************************/
/*								  2022.03.10								*/
/*								LEA - 128bits								*/
/*							  덧셈 8비트 단위 연산							*/
/*						  국민대학교 정보보안암호수학과						*/
/*																			*/
/*									이현호									*/
/*																			*/
/****************************************************************************/



#include <stdio.h>
#include <stdint.h>

typedef unsigned char byte;
typedef uint32_t word;

//Little Endian
#define GETU32(pt) (((word)(pt)[3] << 24) ^ ((word)(pt)[2] << 16) ^ ((word)(pt)[1] <<  8) ^ ((word)(pt)[0]))
#define PUTU32(ct, st) { (ct)[3] = (byte)((st) >> 24); (ct)[2] = (byte)((st) >> 16); (ct)[1] = (byte)((st) >>  8); (ct)[0] = (byte)(st); }

//=====
// 바이트 b[16] --> 워드 state[4]
void byte2state(byte b[16], word state[4]) {
	state[0] = GETU32(b);
	state[1] = GETU32(b + 4);
	state[2] = GETU32(b + 8);
	state[3] = GETU32(b + 12);
}
void byte2state2(byte b[4], word *state) {
	*state = GETU32(b);
	
}
//=====
// 워드 state[4] --> 바이트 b[16]
void state2byte(word state[4], byte b[16]) {
	PUTU32(b, state[0]);
	PUTU32(b + 4, state[1]);
	PUTU32(b + 8, state[2]);
	PUTU32(b + 12, state[3]);
}
void state2byte2(word state, byte b[4]) {
	PUTU32(b, state);
	
}

/*32 비트 열 x의 i비트 좌,우 순환이동*/
word ROL(word x, word i) {
	return ((x) << (i)) | ((x) >> (32 - (i)));
}
word ROR(word x, word i) {
	return ((x) >> (i)) | ((x) << (32 - (i)));
}
//#define ROL(x,i)  ((x)<<(i)) | ((x)>>(32 - (i)))
//#define ROR(x,i)  ((x)>>(i)) | ((x)<<(32 - (i)))

void round_func(word X[]/*input*/, word rk[]/*해당 라운드키*/, word state[]/*output*/) {

	byte carry = 0;
	byte A[4] = { 0, };
	byte B[4] = { 0, };
	byte C[4] = { 0, };
	word D = 0;

	state2byte2((X[0] ^ rk[0]),A );
	state2byte2((X[1] ^ rk[1]),B );
	for (int i = 0; i < 4; i++) {
	
		C[i] = A[i] + B[i] + carry;
		if (A[i] + B[i] + carry > 0xff)
			carry = 1;
		else
			carry = 0;
	}
	byte2state2(C, &D);
	state[0] = ROL(D, 9);
	carry = 0;
	
	state2byte2((X[1] ^ rk[2]), A);
	state2byte2((X[2] ^ rk[3]), B);
	for (int i = 0; i < 4; i++) {

		C[i] = A[i] + B[i] + carry;
		if (A[i] + B[i] + carry > 0xff)
			carry = 1;
		else
			carry = 0;
	}
	byte2state2(C, &D);
	state[1] = ROR(D, 5);
	carry = 0;

	state2byte2((X[2] ^ rk[4]), A);
	state2byte2((X[3] ^ rk[5]), B);
	for (int i = 0; i < 4; i++) {

		C[i] = A[i] + B[i] + carry;
		if (A[i] + B[i] + carry > 0xff)
			carry = 1;
		else
			carry = 0;
	}
	byte2state2(C, &D);
	state[2] = ROR(D, 3);
	carry = 0;

	state[3] = X[0];
}

void LEA_Key_Schedule(word Key[], word rk[][6]) {
	word T[4] = { 0, };
	//상수
	const word delta[8] = { 0xc3efe9db, 0x44626b02, 0x79e27c8a, 0x78df30ec, 0x715ea49e, 0xc785da0a, 0xe04ef22a,0xe5c40957 };

	T[0] = Key[0];
	T[1] = Key[1];
	T[2] = Key[2];
	T[3] = Key[3];
	for (int i = 0; i < 24; i++) {
		T[0] = ROL((T[0] + ROL(delta[i % 4], i)) & 0xffffffff, 1);
		T[1] = ROL((T[1] + ROL(delta[i % 4], i + 1)) & 0xffffffff, 3);
		T[2] = ROL((T[2] + ROL(delta[i % 4], i + 2)) & 0xffffffff, 6);
		T[3] = ROL((T[3] + ROL(delta[i % 4], i + 3)) & 0xffffffff, 11);

		rk[i][0] = T[0];
		rk[i][1] = T[1];
		rk[i][2] = T[2];
		rk[i][3] = T[1];
		rk[i][4] = T[3];
		rk[i][5] = T[1];

	}
}
void LEA_Enc_8(byte plaintext[], byte Key[], byte ciphertext[]) {
	//라운드 키
	word rk[24][6] = { 0, };
	word WKey[4] = { 0, };
	word state[4] = { 0, };
	word state2[4] = { 0, };

	byte2state(plaintext, state2);
	byte2state(Key, WKey);
	LEA_Key_Schedule(WKey, rk);


	round_func(state2, rk[0], state);
	round_func(state, rk[1], state2);
	round_func(state2, rk[2], state);
	round_func(state, rk[3], state2);
	round_func(state2, rk[4], state);
	round_func(state, rk[5], state2);
	round_func(state2, rk[6], state);
	round_func(state, rk[7], state2);
	round_func(state2, rk[8], state);
	round_func(state, rk[9], state2);
	round_func(state2, rk[10], state);
	round_func(state, rk[11], state2);
	round_func(state2, rk[12], state);
	round_func(state, rk[13], state2);
	round_func(state2, rk[14], state);
	round_func(state, rk[15], state2);
	round_func(state2, rk[16], state);
	round_func(state, rk[17], state2);
	round_func(state2, rk[18], state);
	round_func(state, rk[19], state2);
	round_func(state2, rk[20], state);
	round_func(state, rk[21], state2);
	round_func(state2, rk[22], state);
	round_func(state, rk[23], state2);

	state2byte(state2, ciphertext);

}
int main() {

	

	/******************************8 - bit 단위 Test Vector********************************/
	byte Plaintext2[16] = { 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f };
	byte Key2[16] = { 0x0f, 0x1e, 0x2d, 0x3c, 0x4b, 0x5a, 0x69, 0x78, 0x87, 0x96, 0xa5, 0xb4, 0xc3, 0xd2, 0xe1, 0xf0 };
	//byte Key2[16] = { 0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6, 0xab, 0xf7, 0x15, 0x88, 0x09, 0xcf, 0x4f, 0x3c };
	byte Ciphertext2[16] = { 0, };
	/**************************************************************************************/

	/*******************************************TEST***************************************/
	/*LEA_Enc_32(Plaintext, Key, Ciphertext);
	printf("%08x ", Ciphertext[0]);
	printf("%08x ", Ciphertext[1]);
	printf("%08x ", Ciphertext[2]);
	printf("%08x ", Ciphertext[3]);*/

	LEA_Enc_8(Plaintext2, Key2, Ciphertext2);
	for (int i = 0; i < 16; i++)
		printf("%02x ", Ciphertext2[i]);

	/*word rk[24][6] = { 0, };
	LEA_Key_Schedule(Key2, rk);
	for (int i = 0; i < 24; i++) {
		for (int j = 0; j < 6; j++) {
			printf("%08x\n", rk[i][j]);
		}
	}*/

	/**************************************************************************************/

	/*라운드 함수 테스트*/
	//word rk[24][6] = { 0, };
	//LEA_Key_Schedule(Key, rk);
	//word TRUE_ROUND_KEY[24][6] = {
	//		0x003a0fd4 ,0x02497010 ,0x194f7db1 ,0x02497010 ,0x090d0883 ,0x02497010,
	//		0x11fdcbb1 ,0x9e98e0c8 ,0x18b570cf ,0x9e98e0c8 ,0x9dc53a79 ,0x9e98e0c8,
	//		0xf30f7bb5 ,0x6d6628db ,0xb74e5dad ,0x6d6628db ,0xa65e46d0 ,0x6d6628db,
	//		0x74120631 ,0xdac9bd17 ,0xcd1ecf34 ,0xdac9bd17 ,0x540f76f1 ,0xdac9bd17,
	//		0x662147db ,0xc637c47a ,0x46518932 ,0xc637c47a ,0x23269260 ,0xc637c47a,
	//		0xe4dd5047 ,0xf694285e ,0xe1c2951d ,0xf694285e ,0x8ca5242c ,0xf694285e,
	//		0xbaf8e5ca ,0x3e936cd7 ,0x0fc7e5b1 ,0x3e936cd7 ,0xf1c8fa8c ,0x3e936cd7,
	//		0x5522b80c ,0xee22ca78 ,0x8a6fa8b3 ,0xee22ca78 ,0x65637b74 ,0xee22ca78,
	//		0x8a19279e ,0x6fb40ffe ,0x85c5f092 ,0x6fb40ffe ,0x92cc9f25 ,0x6fb40ffe,
	//		0x9dde584c ,0xcb00c87f ,0x4780ad66 ,0xcb00c87f ,0xe61b5dcb ,0xcb00c87f,
	//		0x4fa10466 ,0xf728e276 ,0xd255411b ,0xf728e276 ,0x656839ad ,0xf728e276,
	//		0x9250d058 ,0x51bd501f ,0x1cb40dae ,0x51bd501f ,0x1abf218d ,0x51bd501f,
	//		0x21dd192d ,0x77c644e2 ,0xcabfaa45 ,0x77c644e2 ,0x681c207d ,0x77c644e2,
	//		0xde7ac372 ,0x9436afd0 ,0x10331d80 ,0x9436afd0 ,0xf326fe98 ,0x9436afd0,
	//		0xfb3ac3d4 ,0x93df660e ,0x2f65d8a3 ,0x93df660e ,0xdf92e761 ,0x93df660e,
	//		0x27620087 ,0x265ef76e ,0x4fb29864 ,0x265ef76e ,0x2656ed1a ,0x265ef76e,
	//		0x227b88ec ,0xd0b3fa6f ,0xc86a08fd ,0xd0b3fa6f ,0xa864cba9 ,0xd0b3fa6f,
	//		0xf1002361 ,0xe5e85fc3 ,0x1f0b0408 ,0xe5e85fc3 ,0x488e7ac4 ,0xe5e85fc3,
	//		0xc65415d5 ,0x51e176b6 ,0xeca88bf9 ,0x51e176b6 ,0xedb89ece ,0x51e176b6,
	//		0x9b6fb99c ,0x0548254b ,0x8de9f7c2 ,0x0548254b ,0xb6b4d146 ,0x0548254b,
	//		0x7257f134 ,0x06051a42 ,0x36bcef01 ,0x06051a42 ,0xb649d524 ,0x06051a42,
	//		0xa540fb03 ,0x34b196e6 ,0xf7c80dad ,0x34b196e6 ,0x71bc7dc4 ,0x34b196e6,
	//		0x8fbee745 ,0xcf744123 ,0x907c0a60 ,0xcf744123 ,0x8215ec35 ,0xcf744123,
	//		0x0bf6adba ,0xdf69029d ,0x5b72305a ,0xdf69029d ,0xcb47c19f ,0xdf69029d
	//};
	//
	//for (int i = 0; i < 24; i++) {
	//	for (int j = 0; j < 6; j++) {
	//		if (rk[i][j] != TRUE_ROUND_KEY[i][j]) {
	//			//system(1);
	//			printf("WORNG KEY\n");
	//		}
	//	}
	//}
}