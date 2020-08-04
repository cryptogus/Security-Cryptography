#include <stdio.h>

int GCD_operation(int x, int y); //최대 공약수를 구하는 함수

int main()
{
	int num1, num2, gcd;

	printf("Enter two integers : ");
	scanf_s("%d %d", &num1, &num2);

	//두 수 중에 큰 수를 함수의 첫번째 인자로 한다
	if (num1 > num2)
		gcd = GCD_operation(num1, num2);
	else
		gcd = GCD_operation(num2, num1);

	//결과를 출력
	printf("* %d, %d의 최대 공약수: %d", num1, num2, gcd);
}

//최대 공약수를 구하는 함수(유클리드 알고리즘 사용)
int GCD_operation(int x, int y)
{
	int r;
	// y가  0이 될 때 x가 최대 공약수가 됨
	while (y)
	{
		r = x % y;
		x = y; //다음 연산에서 r = y%r 수행
		y = r; //x에 y를 대입하고 y에 r을 대입 한다
	}
	return x; //최대 공약수를 반환 한다
}