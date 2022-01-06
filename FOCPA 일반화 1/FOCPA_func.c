/*----------------------------------------------------------------------------------*/
/*	Visual Studio 2019 사용시 경고창 제거                                           */
/*----------------------------------------------------------------------------------*/
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "FOCPA.h"

//해밍웨이트 함수
unsigned int HW(unsigned long long x)
{
	const unsigned long long m1 = 0x5555555555555555;
	const unsigned long long m2 = 0x3333333333333333;
	const unsigned long long m4 = 0x0f0f0f0f0f0f0f0f;
	x -= (x >> 1) & m1;             //put count of each 2 bits into those 2 bits
	x = (x & m2) + ((x >> 2) & m2); //put count of each 4 bits into those 4 bits 
	x = (x + (x >> 4)) & m4;        //put count of each 8 bits into those 8 bits 
	x += x >> 8;  //put count of each 16 bits into their lowest 8 bits
	x += x >> 16;  //put count of each 32 bits into their lowest 8 bits
	x += x >> 32;  //put count of each 64 bits into their lowest 8 bits
	return x & 0x7f;
}
//int HW[256] = { //AES SBox기준 해밍웨이트 테이블
//  0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2, 3, 2, 3, 3, 4, 1, 2,
//  2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5, 1, 2, 2, 3,
//  2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5, 2, 3, 3, 4, 3, 4,
//  4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 1, 2, 2, 3, 2, 3, 3, 4,
//  2, 3, 3, 4, 3, 4, 4, 5, 2, 3, 3, 4, 3, 4, 4, 5, 3, 4,
//  4, 5, 4, 5, 5, 6, 2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5,
//  4, 5, 5, 6, 3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6,
//  6, 7, 1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5,
//  2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 2, 3,
//  3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 3, 4, 4, 5,
//  4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7, 2, 3, 3, 4, 3, 4,
//  4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 3, 4, 4, 5, 4, 5, 5, 6,
//  4, 5, 5, 6, 5, 6, 6, 7, 3, 4, 4, 5, 4, 5, 5, 6, 4, 5,
//  5, 6, 5, 6, 6, 7, 4, 5, 5, 6, 5, 6, 6, 7, 5, 6, 6, 7,
//  6, 7, 7, 8 };




void CPA() {
	/*FILE* plain = fopen("C:/Users/hyen/chipwhisperer/projects/tmp/default_data/traces/AES_100tr_10900p_plain.txt", "r");
	FILE* trace = fopen("C:/Users/hyen/chipwhisperer/projects/tmp/default_data/traces/AES_100tr_10900p.trace", "rb");*/
	
	FILE* trace = fopen(trace_path, "rb");
	FILE* plain = fopen(plain_path, "r");
	
	//동적할당을 위한 변수
	unsigned int byte = last_byte - start_byte + 1; 
	unsigned long long point_num = _END_POINT_ - _START_POINT_;
	
	trace_HEADER header;
	fread(&header, sizeof(header), 1, trace); //앞의 값 읽어오기
	printf(" -------------------------------파형 정보-------------------------------\n");
	printf("|	파형갯수	:	%d				|\n", header.trace_no);
	printf("|	포인트수	:	%d				|\n", header.point_no);
	printf(" -----------------------------------------------------------------------\n");
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

	/************************************************************************************/
	/*                                   변수 동적할당                                   /
	/************************************************************************************/
	
	// 분석 포인트 저장
	float* po_trace = (float*)calloc(sizeof(float), point_num);
	//float* po_trace = (float*)calloc(sizeof(float), header.point_no); -> 파형 포인트 전부를 이용할때 header.point_no 변수를 넣어준다
	
	// 평문 저장
	unsigned char* plaintext = (unsigned char*)calloc(sizeof(unsigned char), 16); //16 바이트 저장

	// 중간값
	unsigned int* middle = (unsigned int*)calloc(sizeof(unsigned int), 256);

	// 상관계수의 절댓값을 저장할 변수
	float* Corr = (float*)calloc(sizeof(float),point_num);
	
	// 추측한 비밀키 저장
	unsigned int* index = (unsigned int*)calloc(sizeof(unsigned int), byte);

	// 상관계수들의 최댓값
	float* maxCorrs = (float*)calloc(sizeof(float), byte);
	
	// 중간값 E[X] 저장
	float* sum_x = (float*)calloc(sizeof(float), point_num);
	
	// 파형 측정값 E[Y] 저장
	float* sum_y = (float*)calloc(sizeof(float), 256);
	
	// E[XY] 저장
	float** sum_xy = (float**)calloc(sizeof(float*), 256);
	for (int i = 0; i < 256; i++) {
		sum_xy[i] = (float*)calloc(sizeof(float), point_num);
	}

	// 중간값 E[X^2] 저장
	float* sum_x2 = (float*)calloc(sizeof(float), point_num);
	
	// 파형 측정값 E[Y^2] 저장
	float* sum_y2 = (float*)calloc(sizeof(float), 256);
	float X;
	float Y;
	float XY;
	unsigned int point;

	for (int i = start_byte - 1; i < last_byte; i++) {
		//변수 초기화 부분
		float max = 0;
		fseek(plain, 0, SEEK_SET);
		fseek(trace, 32, SEEK_SET);
		for (int i = 0; i < 256; i++) {
			sum_y[i] = 0;
			sum_y2[i] = 0;
			for (point = 0; point < point_num; point++) {
				sum_xy[i][point] = 0;
			}
		}
		for (point = 0; point < point_num; point++) {
			sum_x[point] = 0;
			sum_x2[point] = 0;
		}
		for (unsigned int j = 0; j < _TRACE_NUM_;/*전체 파형수를 쓸때 header.trace_no*/ j++) {

			for (int j = 0; j < 16; j++) {
				fscanf(plain, "%hhx", &plaintext[j]);
			}//평문 받아오기

			fread(po_trace, sizeof(float), header.point_no, trace); //파형정보 불러오기

			for (point = _START_POINT_; point < _END_POINT_; point++) {

				sum_x[point - _START_POINT_] = sum_x[point- _START_POINT_] + po_trace[point]; //상관계수 X변수 값들의 합
				sum_x2[point - _START_POINT_] = sum_x2[point - _START_POINT_] + po_trace[point] * po_trace[point]; //제곱
			}

			for (unsigned int key = 0; key < 0x100; key++) {

				middle[key] = HW(S_Box[plaintext[i] ^ key]); //subbyte 해밍웨이트값
				sum_y[key] = sum_y[key] + middle[key];
				for (point = _START_POINT_; point < _END_POINT_; point++) {
					sum_xy[key][point - _START_POINT_] = sum_xy[key][point - _START_POINT_] + po_trace[point] * middle[key]; //xy의 합
				}

				sum_y2[key] = sum_y2[key] + middle[key] * middle[key];
			}
			//최대 상관계수값 구하기
		}
		for (unsigned int key = 0; key < 0x100; key++) {
			int k = 0;
			
			for (point = 0; point < point_num; point++) {
				//n은 분석할 파형 범위(전체 갯수)
				X = (_TRACE_NUM_) * sum_x2[point] - (sum_x[point] * sum_x[point]);
				Y = (_TRACE_NUM_) * sum_y2[key] - (sum_y[key] * sum_y[key]);
				XY = (_TRACE_NUM_) * sum_xy[key][point] - (sum_x[point] * sum_y[key]);
				Corr[k] = fabs(XY / sqrt((float)X * Y));// 상관관계 절댓값

				if (Corr[k] > max) {
					max = Corr[k];
					maxCorrs[i] = max;
					index[i] = key;
				}
				k++;
			}

		}

	}

	printf("추측한 키값: ");
	for (int i = (start_byte - 1); i < last_byte; i++) {
		printf("%02x ", index[i]);
	}
	free(sum_x), free(sum_y), free(sum_x2), free(sum_y2);
	for (int i = 0; i < point_num; i++) {
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
