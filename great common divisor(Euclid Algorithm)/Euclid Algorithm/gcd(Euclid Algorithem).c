#include <stdio.h>

int GCD_operation(int x, int y); //�ִ� ������� ���ϴ� �Լ�

int main()
{
	int num1, num2, gcd;

	printf("Enter two integers : ");
	scanf_s("%d %d", &num1, &num2);

	//�� �� �߿� ū ���� �Լ��� ù��° ���ڷ� �Ѵ�
	if (num1 > num2)
		gcd = GCD_operation(num1, num2);
	else
		gcd = GCD_operation(num2, num1);

	//����� ���
	printf("* %d, %d�� �ִ� �����: %d", num1, num2, gcd);
}

//�ִ� ������� ���ϴ� �Լ�(��Ŭ���� �˰��� ���)
int GCD_operation(int x, int y)
{
	int r;
	// y��  0�� �� �� x�� �ִ� ������� ��
	while (y)
	{
		r = x % y;
		x = y; //���� ���꿡�� r = y%r ����
		y = r; //x�� y�� �����ϰ� y�� r�� ���� �Ѵ�
	}
	return x; //�ִ� ������� ��ȯ �Ѵ�
}