#include <stdio.h>
#include <string.h>

int main()
{
	int i = 0, key = 0, str_size = 0;
	char str[50] = { 0, };

	printf("�� �Ǵ� ��ȣ���� �Է��Ͻÿ� : ");
	gets(str);

	printf("Ű ���� �Է��Ͻÿ� :");
	scanf_s("%d", &key);

	str_size = strlen(str);

	for (i = 0; i < str_size; i++)
	{
		if ((str[i] >= 'a') && (str[i] <= 'z'))
		{
			str[i] -= 'a';

			if ((str[i] + key) < 0)
				str[i] += 26;

			str[i] = (str[i] + key) % 26;
			str[i] += 'a';
		}
		if ((str[i] >= 'A') && (str[i] <= 'Z'))
		{
			str[i] -= 'A';

			if ((str[i] + key) < 0)
				str[i] += 26;
			str[i] = (str[i] + key) % 26;
			str[i] += 'A';
		}
	}
	printf("\n��ȣȭ �Ǵ� ��ȣȭ�� ��� ��� : ");
	puts(str);
}