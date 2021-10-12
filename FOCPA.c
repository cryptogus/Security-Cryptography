#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
//AES - SBox
const unsigned int S_Box[256] = {
	0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5, 0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76,
	0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0, 0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0,
	0xb7, 0xfd, 0x93, 0x26, 0x36, 0x3f, 0xf7, 0xcc, 0x34, 0xa5, 0xe5, 0xf1, 0x71, 0xd8, 0x31, 0x15,
	0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a, 0x07, 0x12, 0x80, 0xe2, 0xeb, 0x27, 0xb2, 0x75,
	0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0, 0x52, 0x3b, 0xd6, 0xb3, 0x29, 0xe3, 0x2f, 0x84,
	0x53, 0xd1, 0x00, 0xed, 0x20, 0xfc, 0xb1, 0x5b, 0x6a, 0xcb, 0xbe, 0x39, 0x4a, 0x4c, 0x58, 0xcf,
	0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85, 0x45, 0xf9, 0x02, 0x7f, 0x50, 0x3c, 0x9f, 0xa8,
	0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5, 0xbc, 0xb6, 0xda, 0x21, 0x10, 0xff, 0xf3, 0xd2,
	0xcd, 0x0c, 0x13, 0xec, 0x5f, 0x97, 0x44, 0x17, 0xc4, 0xa7, 0x7e, 0x3d, 0x64, 0x5d, 0x19, 0x73,
	0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88, 0x46, 0xee, 0xb8, 0x14, 0xde, 0x5e, 0x0b, 0xdb,
	0xe0, 0x32, 0x3a, 0x0a, 0x49, 0x06, 0x24, 0x5c, 0xc2, 0xd3, 0xac, 0x62, 0x91, 0x95, 0xe4, 0x79,
	0xe7, 0xc8, 0x37, 0x6d, 0x8d, 0xd5, 0x4e, 0xa9, 0x6c, 0x56, 0xf4, 0xea, 0x65, 0x7a, 0xae, 0x08,
	0xba, 0x78, 0x25, 0x2e, 0x1c, 0xa6, 0xb4, 0xc6, 0xe8, 0xdd, 0x74, 0x1f, 0x4b, 0xbd, 0x8b, 0x8a,
	0x70, 0x3e, 0xb5, 0x66, 0x48, 0x03, 0xf6, 0x0e, 0x61, 0x35, 0x57, 0xb9, 0x86, 0xc1, 0x1d, 0x9e,
	0xe1, 0xf8, 0x98, 0x11, 0x69, 0xd9, 0x8e, 0x94, 0x9b, 0x1e, 0x87, 0xe9, 0xce, 0x55, 0x28, 0xdf,
	0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68, 0x41, 0x99, 0x2d, 0x0f, 0xb0, 0x54, 0xbb, 0x16 };

//해밍웨이트 함수
//unsigned int HW(unsigned long long x)
//{
//	const unsigned long long m1 = 0x5555555555555555;
//	const unsigned long long m2 = 0x3333333333333333;
//	const unsigned long long m4 = 0x0f0f0f0f0f0f0f0f;
//	x -= (x >> 1) & m1;             //put count of each 2 bits into those 2 bits
//	x = (x & m2) + ((x >> 2) & m2); //put count of each 4 bits into those 4 bits 
//	x = (x + (x >> 4)) & m4;        //put count of each 8 bits into those 8 bits 
//	x += x >> 8;  //put count of each 16 bits into their lowest 8 bits
//	x += x >> 16;  //put count of each 32 bits into their lowest 8 bits
//	x += x >> 32;  //put count of each 64 bits into their lowest 8 bits
//	return x & 0x7f;
//}
int HW[256] = { //해밍웨이트 테이블
  0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2, 3, 2, 3, 3, 4, 1, 2,
  2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5, 1, 2, 2, 3,
  2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5, 2, 3, 3, 4, 3, 4,
  4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 1, 2, 2, 3, 2, 3, 3, 4,
  2, 3, 3, 4, 3, 4, 4, 5, 2, 3, 3, 4, 3, 4, 4, 5, 3, 4,
  4, 5, 4, 5, 5, 6, 2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5,
  4, 5, 5, 6, 3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6,
  6, 7, 1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5,
  2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 2, 3,
  3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 3, 4, 4, 5,
  4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7, 2, 3, 3, 4, 3, 4,
  4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 3, 4, 4, 5, 4, 5, 5, 6,
  4, 5, 5, 6, 5, 6, 6, 7, 3, 4, 4, 5, 4, 5, 5, 6, 4, 5,
  5, 6, 5, 6, 6, 7, 4, 5, 5, 6, 5, 6, 6, 7, 5, 6, 6, 7,
  6, 7, 7, 8 };


typedef struct TRACE_HEADER {

	unsigned char strID[20];//처음 20byte 정보 날리기
	unsigned int trace_no; // 파형갯수
	unsigned int point_no; //포인트 수
	unsigned char strEND[4]; //4byte 띄고 시작
}trace_HEADER;


void CPA(){
	FILE* plain = fopen("C:/Users/hyen/chipwhisperer/projects/tmp/default_data/traces/AES_100tr_10900p_plain.txt", "r");
	FILE* trace = fopen("C:/Users/hyen/chipwhisperer/projects/tmp/default_data/traces/AES_100tr_10900p.trace", "rb");

	int byte = 16;// byte 갯수
	
	trace_HEADER header;
	fread(&header, sizeof(header), 1, trace);
	
	/*파형정보 동적할당 2차원 배열 포인트[파형개수][포인트개수]
	double **po_trace = (double**)calloc(sizeof(double*), header.trace_no);
	for (int i = 0; i < header.trace_no; i++) {
		po_trace[i] = (double*)calloc(sizeof(double), header.point_no);
	}*/
	
	/////// 평문정보 동적할당 2차원 배열
	//char **plaintext = (char**)calloc(sizeof(char*) , header.trace_no);//평문
	//for (int i = 0; i < header.trace_no; i++) {
	//	plaintext[i] = (char*)calloc(sizeof(char), byte);
	//}
	//
	/////////////////////////////////////////////////////////////////
	//
	//for (int i = 0; i < header.trace_no; i++) {
	//	for (int j = 0; j < byte; j++) {
	//		fscanf(plain, "%hhx", &plaintext[i][j]);
	//	}
	//}
	//plaintext파일 잘 받아왔는지 확인
	/*for (int i = 0; i < header.trace_no; i++) {
		for (int j = 0; j < byte; j++) {
			printf("%hhx ", plaintext[i][j]);
		}
		printf("\n");
	}*/

	
	//////////////////////중간값 동적할당////////////////////////////////
	unsigned int *middle = (unsigned int*)calloc(sizeof(unsigned int),256);
	
	/////////////////////////////////////////////////////////////////////
	
	/////////////////////상관계수의 절댓값을 저장할 2차원 동적할당///////
	float*	Corr = (float*)calloc(sizeof(float), header.point_no);
	
	/////////////////////////////////////////////////////////////////////
	
	///////////////////추측한 비밀키 저장////////////////////////////////
	unsigned int *index = (unsigned int*)calloc(sizeof(unsigned int),byte);
	////////////////////////////////////////////////////////////////////

	////////////////////상관계수들의 최댓값///////////////////////////////
	float* maxCorrs = (float*)calloc(sizeof(float), byte);
	//////////////////////////////////////////////////////////////////////
	float *po_trace = (float*)calloc(sizeof(float),header.point_no);
	unsigned char *plaintext = (unsigned char*)calloc(sizeof(unsigned char), byte);
	float* sum_x = (float*)calloc(sizeof(float), header.point_no);
	float* sum_y = (float*)calloc(sizeof(float), 256);

	float** sum_xy = (float**)calloc(sizeof(float*), 256);

	for (int i = 0; i < 256; i++) {
		sum_xy[i] = (float*)calloc(sizeof(float), header.point_no);
	}

	float* sum_x2 = (float*)calloc(sizeof(float), header.point_no);
	float* sum_y2 = (float*)calloc(sizeof(float), 256);
	float X;
	float Y;
	float XY;

	for (int i = 0; i < byte; i++) {
		//변수 초기화 부분
		unsigned int point;
		float max = 0;
		fseek(plain, 0, SEEK_SET);
		fseek(trace, 32, SEEK_SET);
		for (int i = 0; i < 256; i++) {
			sum_y[i] = 0;
			sum_y2[i] = 0;
			for (point = 0; point < header.point_no; point++) {
				sum_xy[i][point] = 0;
			}
		}
		for (point = 0; point < header.point_no; point++) {
			sum_x[point] = 0;
			sum_x2[point] = 0;
		}
		for (unsigned int j = 0; j < header.trace_no; j++) {
			
			for (int j = 0; j < byte; j++) {
				fscanf(plain, "%hhx", &plaintext[j]);
			}//평문 받아오기

			fread(po_trace, sizeof(float), header.point_no, trace); //파형정보 불러오기

			for (point = 0; point < header.point_no; point++) {

				sum_x[point] = sum_x[point] + po_trace[point]; //상관계수 X변수 값들의 합
				sum_x2[point] = sum_x2[point] + po_trace[point] *po_trace[point]; //제곱
			}
			
			for (unsigned int key = 0; key < 0x100; key++) {

				middle[key] = HW[S_Box[plaintext[i] ^ key]]; //subbyte 해밍웨이트값
				sum_y[key] = sum_y[key] + middle[key];
				for (point = 0; point < header.point_no; point++) {
					sum_xy[key][point] = sum_xy[key][point] + po_trace[point] * middle[key]; //xy의 합
				}

				sum_y2[key] = sum_y2[key] + middle[key] * middle[key];
			}
			//최대 상관계수값 구하기
		}
		for (unsigned int key = 0; key < 0x100; key++) {
			int k = 0;
			
			for (point = 0; point < header.point_no; point++) {
				//n은 분석할 파형 범위(전체 갯수)
				X = (header.point_no) * sum_x2[point] - (sum_x[point] * sum_x[point]);
				Y = (header.point_no) * sum_y2[key] - (sum_y[key] * sum_y[key]);
				XY = (header.point_no) * sum_xy[key][point] - (sum_x[point] * sum_y[key]);
				Corr[k] = fabs(XY / sqrt( X * Y));// 상관관계 절댓값

				if (Corr[k] > max) {
					max = Corr[k++];
					maxCorrs[i] = max;
					index[i] = key;
				}
			}
			
		}
	
	}
	for (int i = 0; i < 16; i++) {
		printf("%02x ", index[i]);
	}
	free(sum_x), free(sum_y), free(sum_x2), free(sum_y2);
	for (int i = 0; i < header.point_no; i++) {
		free(sum_xy[i]);
	}
	free(sum_xy);
	free(maxCorrs), free(Corr);
	free(po_trace);
	free(plaintext);
	free(middle);
	free(index);
	
	fclose(plain);
	fclose(trace);
}

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