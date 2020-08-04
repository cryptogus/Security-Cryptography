#include <stdio.h>
/* Alt + Ctrl = ����� Ŀ���� ����
���� Ű K1�� ���� f�Լ� ����� �Ʒ��� ���� �����Ѵ�.			���� Ű K2�� ���� f�Լ� ����� �Ʒ��� ���� �����Ѵ�
f : (000) -> (101)												f :	(000) -> (100)
	(001) -> (010)													(001) -> (000)
	(010) -> (011)													(010) -> (011)
	(011) -> (110)													(011) -> (111)
	(100) -> (100)													(100) -> (110)
	(101) -> (001)													(101) -> (101)
	(110) -> (111)													(110) -> (001)
	(111) -> (000)													(111) -> (010)
*/
#define BLOCK_SIZE 6 //��� ũ��(bit)
#define ROUND_NUM 2 //���� ��

char F1(char input); //F�Լ� 1
char F2(char input); //F�Լ� 2
char Feistel_Enc(char in); //Feistel ��ȣȭ �Լ�
char Feistel_Dec(char in); //Feistel ��ȣȭ �Լ�

int main()
{
	char p_bit = 0x2B;
	char c_bit, d_bit;
	int temp = 0, i = 0;
	

	printf("�� : "); //27 ~ 33 : ���� ���� ��Ʈ���� 1��Ʈ�� ����Ѵ�.
	for (i = BLOCK_SIZE - 1; i >= 0; i--)
	{
		temp = (p_bit >> i) & 0x01;
		printf("%d", temp);
	}
	printf("\n");

	c_bit = Feistel_Enc(p_bit); //��ȣȭ �Լ��� ȣ���Ѵ�.

	printf("��ȣ�� : "); //37 ~ 43 : ��ȣ���� ���� ��Ʈ���� 1��Ʈ�� ����Ѵ�.
	for (i = BLOCK_SIZE - 1; i >= 0; i--)
	{
		temp = (c_bit >> 1) & 0x01;
		printf("%d", temp);
	}
	printf("\n");

	d_bit = Feistel_Dec(c_bit); //��ȣȭ �Լ��� ȣ���Ѵ�.

	printf("��ȣ�� : "); // 47 ~53 : ��ȣ���� ���� ��Ʈ���� 1��Ʈ�� ����Ѵ�.
	for (i = BLOCK_SIZE - 1; i >= 0; i--)
	{
		temp = (d_bit >> i) & 0x01;
		printf("%d", temp);
	}
	printf("\n");

}
char Feistel_Enc(char in) //Feistel ��ȣȭ�� �����ϴ� �Լ���.
{
	int i;
	char temp, left, right;

	left = (in >> 3) & 0x07; //61 ~ 62 : �Էµ� �� ��� 6��Ʈ�� left�� right�� ���� 3��Ʈ�� ������ �����Ѵ�.
	right - in & 0x07;

	for (i = 0; i < ROUND_NUM; i++) /*64 ~ 77 : Feistel ���带 �����Ѵ�. ������ ���� ������ ���忡 ���� F1,F2 �Լ��� �����Ͽ� ��� ���� left�� XOR������
									�� �� left�� �����ϰ�, �� ������ left�� right�� ���� ���� �ٲٴ� �ڸ��ٲ��� �����Ѵ�. �� �� ������ ����� �ڸ��ٲ��� ����
									���� �ʴ´�. */
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
	return (left << 3) | right; // ��� ���鸦 �����ϰ� ���� ��� ���� 6��Ʈ�� �����.
}

char Feistel_Dec(char in) //Feistel ��ȣȭ�� �����ϴ� �Լ��̴�.
{
	int i;
	char temp, left, right;

	left = (in >> 3) & 0x07; //�Էµ� ��ȣ�� ��� 6��Ʈ�� left�� right�� ���� 3��Ʈ �� ������ �����Ѵ�.
	right = in & 0x07;

	for (i = 0; i < ROUND_NUM; i++) /*91 ~ 106 : Feistel ���带 �����Ѵ�. ������ ���� ������ ���忡 ���� F1,F2 �Լ��� �����Ͽ� ��� ���� left�� XOR������
									�� �� left�� �����ϰ�, �� ������ left�� right�� ���� ���� �ٲٴ� �ڸ��ٲ��� �����Ѵ�. �� �� ������ ����� �ڸ��ٲ��� ����
									���� �ʴ´�. */
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

char F1(char input) //F1 �Լ�
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

char F2(charinput) //F2 �Լ�
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