#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include<string.h>

int text[100000];

int is_prime(int prime) //소수 판별 함수 (Sieve of Eratosthenes)
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
int GCD(int a, int Eul) //최대공약수 구하는 함수 BY E.A
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
		// gcd 계산
		r = r1 % r2;
		r1 = r2, r2 = r;

		// s 계산
		s = s1 - q * s2;
		s1 = s2, s2 = s;

		// t 계산
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
	printf("암호문 : ");
	for (int j = 0; j < i-1;j++) {
		printf("%c", text[j]);
	}
	printf("\n암호문 길이 : %d\n", i - 1);
}

void decode(d, n) {
	printf("\n");
	int a = 0;
	printf("암호문 길이를 입력해주세요 : ");
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
	int N ,e, d=0;//암호화, 복호화 시 필요한 key;
	int m = 0;
	int c = 0;
	srand((unsigned)time(NULL));
	
	//////////////키생성 과정////////////////////////////////////
	while (1) 
	{
		prime1 = rand();
		prime2 = rand();
		
		if (is_prime(prime1) && is_prime(prime2))
			break;
	}
	printf("소수p = %d, 소수 q = %d\n", prime1, prime2);
	Eul = (prime1 - 1) * (prime2 - 1);//euler function
	printf("Euler Function = %d\n\n", Eul);
	N = prime1 * prime2;
	while (1) {
		printf("공개키(e)를 선택하세요.(범위 2 ~ Euler Function-1 중 하나의 정수) :");
		scanf_s("%d", &e);
		if (GCD(e, Eul) != 1)
			printf("\nGCD가 1이 아닙니다. 다시 공개키를 지정해주세요.\n");
		if (GCD(e, Eul) == 1) // Eul와e는 서로소이여야함
			break;
	}

	d = EEA(e, Eul); //private key
	printf("\n공개키 e = %x, N = %x\n비밀키 d = %x\n", e, N, d);
	
	////////////////////////////////////////암호화 과정//////////////////////////////////////////////////
	printf("\n1.암호화\n2.복호화\n\n");
	printf("입력 :");
	scanf_s("%d", &select);
	if (select == 1) {
		printf("평문을 입력하시오 : ");
		encode(e, N);
		printf("복호화를 위해 암호문과 비밀키d,N을 기억해주세요\n");
	}
	else {
		printf("비밀키 값을 입력해주세요\n");
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
