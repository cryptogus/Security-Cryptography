#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include<string.h>

int text[100000];

int is_prime(int prime) //�Ҽ� �Ǻ� �Լ� (Sieve of Eratosthenes)
{
	int i = 2, j = prime - 1;
	for (; i <= j; i++) {
		if (prime % i==0) {
			return 0;
		}
	}
	if (i == prime)
		return 1;
}
int GCD(int a, int Eul) //�ִ����� ���ϴ� �Լ� BY E.A
{	
	int b=1;
	while (b != 0) {
		b = Eul % a;
		Eul = a;
		a = b;
	}
	return Eul;
}

int EEA(int a, int b) 
{
	
	int r1 = a, r2 = b, s1 = 1, s2 = 0, t1 = 0, t2 = 1;
	int r, s, t, q;
	while (r2) {
		q = r1 / r2;
		// gcd ���
		r = r1 % r2;
		r1 = r2, r2 = r;

		// s ���
		s = s1 - q * s2;
		s1 = s2, s2 = s;

		// t ���
		t = t1 - q * t2;
		t1 = t2, t2 = t;
	}
	r = r1, s = s1, t = t1;

	if (r == 1) {
		if (t < 0) {
			t += a;
		}
		return t;
	}
}
int bits_len(int e) {
	int sum = 0;
	while (e != 1) {
		if (e % 2 == 1) {
			e = e / 2;
			sum += 1;
		}
		else {
			e = e / 2;
			sum += 1;
		}
	}
	return sum;
}
int power_mod(int p, int e, int n) {
	
	int r2 = 1;
	int r1 = 0;
	int Q = 0;
	int R = 0;

	while (e != 0) {
		R = (e % 2);
		Q = ((e - R) / 2);

		r1 = ((p * p) % n);

		if (R == 1) {
			r2 = ((r2 * p) % n);
		}
		p = r1;
		e = Q;
	}
	return r2;
}

void encode(e, n) {
	int i = 0;

	int c = getchar();
	do {
		c = getchar();
		text[i] = power_mod(c, e, n);
		i++;
	} while (c != '\n');

	
	printf("\n*************************************\n");
	printf("��ȣ�� : ");
	for (int j = 0; j < i-1;j++) {
		printf("%c", text[j]);
	}
	printf("\n��ȣ�� ���� : %d\n", i - 1);
}

void decode(d, n) {
	printf("\n");
	int a = 0;
	printf("��ȣ�� ���̸� �Է����ּ��� : ");
	scanf_s("%d", &a);
	for (int i = 0; i < a; i++) {
		printf("Ciphered text C%d: ", i + 1);
		scanf_s("%c", &text[i]);
		text[i] = power_mod(text[i], d, n);
	}

	printf("\n*************************************");
	printf("\n   Deciphered text: ");
	for (int i = 0; i < a; i++) {
		printf("%c", text[i]);
	}
}

int main()
{
	int prime1, prime2, Eul, select;
	int N ,e, d=0;//��ȣȭ, ��ȣȭ �� �ʿ��� key;
	int m = 0;
	int c = 0;
	srand((unsigned)time(NULL));
	
	//////////////Ű���� ����////////////////////////////////////
	while (1) 
	{
		prime1 = rand();
		prime2 = rand();
		
		if (is_prime(prime1) && is_prime(prime2))
			break;
	}
	printf("�Ҽ�p = %d, �Ҽ� q = %d\n", prime1, prime2);
	Eul = (prime1 - 1) * (prime2 - 1);//euler function
	printf("Euler Function = %d\n\n", Eul);
	N = prime1 * prime2;
	while (1) {
		printf("����Ű(e)�� �����ϼ���.(���� 2 ~ Euler Function-1 �� �ϳ��� ����) :");
		scanf_s("%d", &e);
		if (GCD(e, Eul) != 1)
			printf("\nGCD�� 1�� �ƴմϴ�. �ٽ� ����Ű�� �������ּ���.\n");
		if (GCD(e, Eul) == 1) // Eul��e�� ���μ��̿�����
			break;
	}

	d = EEA(e, Eul); //private key
	printf("\n����Ű e = %x, N = %x\n���Ű d = %x\n", e, N, d);
	
	////////////////////////////////////////��ȣȭ ����//////////////////////////////////////////////////
	printf("\n1.��ȣȭ\n2.��ȣȭ\n\n");
	printf("�Է� :");
	scanf_s("%d", &select);
	if (select == 1) {
		printf("���� �Է��Ͻÿ� : ");
		encode(e, N);
		printf("��ȣȭ�� ���� ��ȣ���� ���Űd,N�� ������ּ���\n");
	}
	else {
		printf("���Ű ���� �Է����ּ���\n");
		getchar();
		printf("d :");
		scanf_s("%d", &d);
		getchar();
		printf("N :");
		scanf_s("%d", &N);
		decode(d, N);
	}
	

	
	return 0;
}
