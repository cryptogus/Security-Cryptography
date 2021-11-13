#include <stdio.h>

typedef unsigned char byte;

int main() {
	
	byte SBox[16] = { 6, 5, 12, 10, 1, 14, 7, 9, 11, 0, 3, 13, 8, 15, 4, 2 };
	//byte Permu[32] = { 18, 23, 25, 20, 16, 3, 21, 6, 24, 19, 22, 13, 12, 26, 27, 9, 4, 1, 31, 10, 2, 29, 15, 8, 30, 17, 7, 0, 28, 11, 5, 14 };
	byte count = 0;
	byte DDT[16][16] = { 0, };
	printf("-----------------------------------------------------------\n");
	printf("|              Differential Distribution Table            |\n");
	printf("-----------------------------------------------------------\n");
	for (int i = 0; i < 16; i++) { //행의 인덱스 i xor j, 열의 인덱스 SBox[i] xor SBox[j]
		for (int j = 0; j < 16; j++) {
			DDT[i ^ j][SBox[i] ^ SBox[j]]++;

		}
		
	}
	printf("\n");
	
	printf("      0  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15\n");
	for (int i = 0; i < 16; i++) { //i 행 j열
		printf("%3d [",i);
		for (int j = 0; j < 16; j++) {
			printf("%2d ", DDT[i][j]);
			if (DDT[i][j] == 4)
				count++;
		}
		printf("]\n");

	}
	
	printf("4의 갯수 : %d", count);
}
//(1) π(x) XOR π(x*) = Sbox(x) XOR Sbox(x*)?
//입력값이 x와 x * 일 때, xxor x* 의 값이 하나로 고정되었을 때 가능한 모든 x, x* 값에 대해
//
//(1)의 식의 값들(출력값의xor)이 0이 몇 개 나오는지, 1이 몇 개 나오는지, ..., 16이 몇 개 나오는지를 계산해주어
//
//만든 표가 DDT(Difference Distribution Table)입니다.
//
//?
//
//행의 인덱스 : x xor x * = x'
//
//열의 인덱스 : y xor y * = y'  -> (1)의 식
//
//?
//
//(x', y')값들은 예를 들어 설명하겠습니다.
//
//x' = 0, y' = 0일 때를 보면
//
//16이라는 값은 x' = 0이 될 수 있는 (x, x*)값들에 대해 y' = 0이 되는(x, x*)값들이 16개라는 말입니다.
