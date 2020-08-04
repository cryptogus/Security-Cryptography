#include <stdio.h>

#define BLOCK_SIZE 6

int main()
{
	int i, j, size, block_num;
	int key[64] = { 3,5,1,6,4,2 }; // 평문 위치를 정하는 키 1,2,3,4,5,6의 문자순서를 이렇게 바꾼다. 평문이 6자리가 넘어가면 6자리씩 끊어서 이렇게 암호문을 만듬
	char p_text[64], c_text[64], d_text[64];

	printf("* 평문 입력 : "); //11 ~ 12 : 평문을 입력 받는다.
	scanf_s("%s", p_text, 64);
	
	size = strlen(p_text); // 평문 길이를 구한다

	if (size % BLOCK_SIZE > 0) { //16 ~ 23: 평문이 블록의 크기와 맞지 않으면 블록의 길이에 맞게 임의의 문자를 추가한다. 여기서 문자는 'x'를 사용 하였다.(padding)
		block_num = strlen(p_text) / BLOCK_SIZE + 1;

		for (i = strlen(p_text); i < block_num * BLOCK_SIZE; i++)
			p_text[i] = 'x';
	}
	else
		block_num = strlen(p_text) / BLOCK_SIZE;

	for (i = 0; i < block_num; i++) //25 ~ 27 : 전치 암호를 수행한다. 정의된 키 값에 따라 평문의 위치를 바꾸기 위해 키 값을 배열의 인덱스로 활용하여 위치를 바꿔준다.
		for (j = 0; j < BLOCK_SIZE; j++)
			c_text[i * BLOCK_SIZE + j] = p_text[(key[j] - 1) + i * BLOCK_SIZE];

	printf("* 암호문 : "); //29 ~ 32 : 암호문을 출력한다.
	for (i = 0; i < block_num * BLOCK_SIZE; i++)
		printf("%c", c_text[i]);
	printf("\n");

	for (i = 0; i < block_num; i++) //암호문을 복호화한다. 암호화에서의 방법과 같이 배열의 인덱스를 활용하여 바꿨던 위치를 다시 되돌린다.
		for (j = 0; j < BLOCK_SIZE; j++)
			d_text[(key[j] - 1) + i * BLOCK_SIZE] = c_text[i * BLOCK_SIZE + j];

	printf("* 복호문 : "); // 복호문 출력
	for (i = 0; i < size; i++)
		printf("%c", d_text[i]);
	printf("\n");

}