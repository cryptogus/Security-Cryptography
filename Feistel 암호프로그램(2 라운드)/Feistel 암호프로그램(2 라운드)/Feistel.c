#include <stdio.h>
/* Alt + Ctrl = 어러군데 커서가 생김
서브 키 K1에 의한 f함수 출력을 아래와 같이 정의한다.			서브 키 K2에 의한 f함수 출력을 아래와 같이 정의한다
f : (000) -> (101)												f :	(000) -> (100)
	(001) -> (010)													(001) -> (000)
	(010) -> (011)													(010) -> (011)
	(011) -> (110)													(011) -> (111)
	(100) -> (100)													(100) -> (110)
	(101) -> (001)													(101) -> (101)
	(110) -> (111)													(110) -> (001)
	(111) -> (000)													(111) -> (010)
*/
#define BLOCK_SIZE 6 //블록 크기(bit)
#define ROUND_NUM 2 //라운드 수

char F1(char input); //F함수 1
char F2(char input); //F함수 2
char Feistel_Enc(char in); //Feistel 암호화 함수
char Feistel_Dec(char in); //Feistel 복호화 함수

int main()
{
	char p_bit = 0x2B;
	char c_bit, d_bit;
	int temp = 0, i = 0;
	

	printf("평문 : "); //27 ~ 33 : 평문을 상위 비트부터 1비트씩 출력한다.
	for (i = BLOCK_SIZE - 1; i >= 0; i--)
	{
		temp = (p_bit >> i) & 0x01;
		printf("%d", temp);
	}
	printf("\n");

	c_bit = Feistel_Enc(p_bit); //암호화 함수를 호출한다.

	printf("암호문 : "); //37 ~ 43 : 암호문을 상위 비트부터 1비트씩 출력한다.
	for (i = BLOCK_SIZE - 1; i >= 0; i--)
	{
		temp = (c_bit >> 1) & 0x01;
		printf("%d", temp);
	}
	printf("\n");

	d_bit = Feistel_Dec(c_bit); //복호화 함수를 호출한다.

	printf("복호문 : "); // 47 ~53 : 복호문을 상위 비트부터 1비트씩 출력한다.
	for (i = BLOCK_SIZE - 1; i >= 0; i--)
	{
		temp = (d_bit >> i) & 0x01;
		printf("%d", temp);
	}
	printf("\n");

}
char Feistel_Enc(char in) //Feistel 암호화를 수행하는 함수다.
{
	int i;
	char temp, left, right;

	left = (in >> 3) & 0x07; //61 ~ 62 : 입력돈 평문 블록 6비트를 left와 right로 각각 3비트씩 나누어 저장한다.
	right - in & 0x07;

	for (i = 0; i < ROUND_NUM; i++) /*64 ~ 77 : Feistel 라운드를 수행한다. 라운드의 수행 과정은 라운드에 따라 F1,F2 함수를 수행하여 결과 값을 left와 XOR연산을
									한 뒤 left에 저장하고, 그 다음에 left와 right의 값을 서로 바꾸는 자리바꿈을 수행한다. 이 때 마지막 라운드는 자리바꿈을 수행
									하지 않는다. */
	{
		if (i == 0)
			left = left ^ F1(right);
		else if (i == 1)
			left = left ^ F2(right);

		if (i != ROUND_NUM - 1)
		{
			temp = left;
			left = right;
			right = temp;
		}
	}
	return (left << 3) | right; // 모든 라운들를 수행하고 나온 결과 값을 6비트로 만든다.
}

char Feistel_Dec(char in) //Feistel 복호화를 수행하는 함수이다.
{
	int i;
	char temp, left, right;

	left = (in >> 3) & 0x07; //입력된 암호문 블록 6비트를 left와 right로 각각 3비트 씩 나누어 저장한다.
	right = in & 0x07;

	for (i = 0; i < ROUND_NUM; i++) /*91 ~ 106 : Feistel 라운드를 수행한다. 라운드의 수행 과정은 라운드에 따라 F1,F2 함수를 수행하여 결과 값을 left와 XOR연산을
									한 뒤 left에 저장하고, 그 다음에 left와 right의 값을 서로 바꾸는 자리바꿈을 수행한다. 이 때 마지막 라운드는 자리바꿈을 수행
									하지 않는다. */
	{
		if (i == 0)
			left = left ^ F2(right);
		else if (i == 1)
			left = left ^ F1(right);

		if (i != ROUND_NUM - 1)
		{
			temp = left;
			left = right;
			right = temp;
		}
	}
	return (left << 3) | right;
}

char F1(char input) //F1 함수
{
	if (input == 0x00)
		return 0x05;
	else if (input == 0x01)
		return 0x02;
	else if (input == 0x02)
		return 0x03;
	else if (input == 0x03)
		return 0x06;
	else if (input == 0x04)
		return 0x04;
	else if (input == 0x05)
		return 0x01;
	else if (input == 0x06)
		return 0x07;
	else if (input == 0x07)
		return 0x00;

	return 0;
}

char F2(charinput) //F2 함수
{
	if (input == 0x00)
		return 0x04;
	else if (input == 0x01)
		return 0x00;
	else if (input == 0x02)
		return 0x03;
	else if (input == 0x03)
		return 0x07;
	else if (input == 0x04)
		return 0x06;
	else if (input == 0x05)
		return 0x05;
	else if (input == 0x06)
		return 0x01;
	else if (input == 0x07)
		return 0x02;

	return 0;
}