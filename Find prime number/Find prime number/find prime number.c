#include <stdio.h>

int main()
{
	/* 우리가 소수인지 판별하고 있는 수 */
	int guess = 5; /* 소수의 배열 */
	int prime[1000]; /* 현재까지 찾은 (소수의 개수 - 1) 아래 두 개의 소수를
	미리 찾았으므로 초기값은 1 이 된다. */
	int index = 1; /* for 문 변수 */
	int i; /* 소수인지 판별위해 쓰이는 변수*/
	int ok; /* 처음 두 소수는 특별한 경우로 친다 */
	prime[0] = 2;
	prime[1] = 3;
	printf("prime[0] = 2, prime[1] = 3 \n");
	for (;;) {
		ok = 0;
		for (i = 0; i <= index; i++) {
			if (guess % prime[i] != 0) {
				ok++;
			}
			else {
				break;
			}
		}
		if (ok == (index + 1)) {
			index++;
			prime[index] = guess;
			printf("소수 : %d \n", prime[index]);
			if (index == 999) break;
		}
		guess += 2;
	}
	return 0;
}