#include <stdio.h>

int main()
{
	/* �츮�� �Ҽ����� �Ǻ��ϰ� �ִ� �� */
	int guess = 5; /* �Ҽ��� �迭 */
	int prime[1000]; /* ������� ã�� (�Ҽ��� ���� - 1) �Ʒ� �� ���� �Ҽ���
	�̸� ã�����Ƿ� �ʱⰪ�� 1 �� �ȴ�. */
	int index = 1; /* for �� ���� */
	int i; /* �Ҽ����� �Ǻ����� ���̴� ����*/
	int ok; /* ó�� �� �Ҽ��� Ư���� ���� ģ�� */
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
			printf("�Ҽ� : %d \n", prime[index]);
			if (index == 999) break;
		}
		guess += 2;
	}
	return 0;
}