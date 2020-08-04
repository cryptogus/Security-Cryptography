#include <stdio.h>

int main()
{
	unsigned char x;
	scanf_s("%hhd", &x);
	int H_W = 0;
	for (int i = 0; i < 8 * sizeof(x); i++)
		H_W += (x >> i) & 0x01;
	printf("Hamming weight : %d", H_W);
	return 0;
}