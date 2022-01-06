
#include <stdio.h>



int main() {
	
	CPA();
}

/****************trace파일 불러올때 실패작 ex)ASCII문자를 벗어나면 어떻게 변환???? 0x96같은거
fseek(trace, 20, SEEK_SET);//처음 20byte 날리기위해 지정 포인터 이동

char tr[4];//파형갯수(문자열로 담을 변수)
char p[4];//포인트수(문자열로 담을 변수)
unsigned int tr2 = 0;//파형갯수(정수형으로 담을 변수)
unsigned int p2 = 0; //point 수

fgets(tr, 4, trace); // (4바이트) 파형수 얻어오기

//printf("%s\n", tr);d(ASCII변환시 0x64) 가 나오는걸로 보아 잘 얻어옴
for (int i = 3; i >= 0; i--) {
	tr2 ^= tr[i];//문자열 정수형으로 변환
	//printf("%x\n", tr2);
	tr2 <<= 8;
}
fgets(p, 4, trace);
for (int i = 3; i >= 0; i--) {
	printf("%x\n", p[i]); //ASCII문자를 벗어나면 어떻게 변환????
}

for (int i = 3; i >= 0; i--) {
	p2 ^= p[i];//문자열 정수형으로 변환
	printf("%x\n", p2);
	p2 <<= 8;
}

fseek(trace, 4, SEEK_SET);//4바이트 띄고 시작****************/