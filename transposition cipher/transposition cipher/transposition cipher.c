#include <stdio.h>

#define BLOCK_SIZE 6

int main()
{
	int i, j, size, block_num;
	int key[64] = { 3,5,1,6,4,2 }; // �� ��ġ�� ���ϴ� Ű 1,2,3,4,5,6�� ���ڼ����� �̷��� �ٲ۴�. ���� 6�ڸ��� �Ѿ�� 6�ڸ��� ��� �̷��� ��ȣ���� ����
	char p_text[64], c_text[64], d_text[64];

	printf("* �� �Է� : "); //11 ~ 12 : ���� �Է� �޴´�.
	scanf_s("%s", p_text, 64);
	
	size = strlen(p_text); // �� ���̸� ���Ѵ�

	if (size % BLOCK_SIZE > 0) { //16 ~ 23: ���� ����� ũ��� ���� ������ ����� ���̿� �°� ������ ���ڸ� �߰��Ѵ�. ���⼭ ���ڴ� 'x'�� ��� �Ͽ���.(padding)
		block_num = strlen(p_text) / BLOCK_SIZE + 1;

		for (i = strlen(p_text); i < block_num * BLOCK_SIZE; i++)
			p_text[i] = 'x';
	}
	else
		block_num = strlen(p_text) / BLOCK_SIZE;

	for (i = 0; i < block_num; i++) //25 ~ 27 : ��ġ ��ȣ�� �����Ѵ�. ���ǵ� Ű ���� ���� ���� ��ġ�� �ٲٱ� ���� Ű ���� �迭�� �ε����� Ȱ���Ͽ� ��ġ�� �ٲ��ش�.
		for (j = 0; j < BLOCK_SIZE; j++)
			c_text[i * BLOCK_SIZE + j] = p_text[(key[j] - 1) + i * BLOCK_SIZE];

	printf("* ��ȣ�� : "); //29 ~ 32 : ��ȣ���� ����Ѵ�.
	for (i = 0; i < block_num * BLOCK_SIZE; i++)
		printf("%c", c_text[i]);
	printf("\n");

	for (i = 0; i < block_num; i++) //��ȣ���� ��ȣȭ�Ѵ�. ��ȣȭ������ ����� ���� �迭�� �ε����� Ȱ���Ͽ� �ٲ�� ��ġ�� �ٽ� �ǵ�����.
		for (j = 0; j < BLOCK_SIZE; j++)
			d_text[(key[j] - 1) + i * BLOCK_SIZE] = c_text[i * BLOCK_SIZE + j];

	printf("* ��ȣ�� : "); // ��ȣ�� ���
	for (i = 0; i < size; i++)
		printf("%c", d_text[i]);
	printf("\n");

}