
#include <stdio.h>



int main() {
	
	CPA();
}

/****************trace���� �ҷ��ö� ������ ex)ASCII���ڸ� ����� ��� ��ȯ???? 0x96������
fseek(trace, 20, SEEK_SET);//ó�� 20byte ���������� ���� ������ �̵�

char tr[4];//��������(���ڿ��� ���� ����)
char p[4];//����Ʈ��(���ڿ��� ���� ����)
unsigned int tr2 = 0;//��������(���������� ���� ����)
unsigned int p2 = 0; //point ��

fgets(tr, 4, trace); // (4����Ʈ) ������ ������

//printf("%s\n", tr);d(ASCII��ȯ�� 0x64) �� �����°ɷ� ���� �� ����
for (int i = 3; i >= 0; i--) {
	tr2 ^= tr[i];//���ڿ� ���������� ��ȯ
	//printf("%x\n", tr2);
	tr2 <<= 8;
}
fgets(p, 4, trace);
for (int i = 3; i >= 0; i--) {
	printf("%x\n", p[i]); //ASCII���ڸ� ����� ��� ��ȯ????
}

for (int i = 3; i >= 0; i--) {
	p2 ^= p[i];//���ڿ� ���������� ��ȯ
	printf("%x\n", p2);
	p2 <<= 8;
}

fseek(trace, 4, SEEK_SET);//4����Ʈ ��� ����****************/