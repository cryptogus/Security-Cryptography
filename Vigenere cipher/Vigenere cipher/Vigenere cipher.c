#include <stdio.h>
#include <string.h>

int main()
{
	int i = 0, j = 0, Key_Size = 0, str_size = 0, select = 1;
	char str[50] = { 0, }, key[16] = { 0, };

	printf("암호문 또는 평문을 입력: ");
	
	gets(str);

	printf("암호는 1번, 복호는 2번 선택: ");
	scanf_s("%d", &select);
	fflush(stdin);
	getchar();
	printf("키 값 입력(4자) : ");
	
	gets(key);

	str_size = strlen(str);
	Key_Size = strlen(key);

	for (i = 0; i < str_size; i++)
	{
		j = i % Key_Size;

		if (select == 1)
		{
			if ((str[i] >= 'a') && (str[i] <= 'z'))
			{
				str[i] -= 'a'; key[j] -= 'a';
				if ((str[i] + key[j]) < 0) {
					str[i] += 26;
				}
				str[i] = (str[i] + key[j]) % 26;
				str[i] += 'a'; key[j] += 'a';

			}
			if ((str[i] >= 'A') && (str[i] <= 'Z'))
			{
				str[i] -= 'A'; key[j] -= 'A';

				if ((str[i] + key[j]) < 0) {
					str[i] += 26;
				}
				str[i] = (str[i] + key[j]) % 26;
				str[i] += 'A'; key[j] += 'A';
				
			}
		}
		if (select == 2)
		{
			if ((str[i] >= 'a') && (str[i] <= 'z')) {
				str[i] -= 'a'; key[j] -= 'a';

				if ((str[i] - key[j]) < 0)
					str[i] += 26;

				str[i] = (str[i] - key[j]) % 26;
				str[i] += 'a'; key[j] += 'a';

			}
			if ((str[i] >= 'A') && (str[i] <= 'Z'))
			{
				str[i] -= 'A'; key[j] -= 'A';

				if ((str[i] - key[j]) < 0)
					str[i] += 26;

				str[i] = (str[i] - key[j]) % 26;
				str[i] += 'A'; key[j] += 'A';
			}
		}
	}
	printf("\n암호화 또는 복호화된 결과 출력 : ");
	puts(str);
}