/*----------------------------------------------------------------------------------*/
/*	Visual Studio 2019 사용시 경고창 제거                                           */
/*----------------------------------------------------------------------------------*/
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "SOCPA.h"

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



void SOCPA() {
	/*FILE* plain = fopen("C:/Users/hyen/chipwhisperer/projects/tmp/default_data/traces/AES_100tr_10900p_plain.txt", "r");
	FILE* trace = fopen("C:/Users/hyen/chipwhisperer/projects/tmp/default_data/traces/AES_100tr_10900p.trace", "rb");*/

	FILE* trace = fopen(trace_path, "rb");
	FILE* plain = fopen(plain_path, "r");

	//동적할당을 위한 변수
	unsigned long long point_num1 = (__int64)_END_POINT_1 - (__int64)_START_POINT_1 + (__int64)1;
	unsigned long long point_num2 = (__int64)_END_POINT_2 - (__int64)_START_POINT_2 + (__int64)1;
	unsigned long long point_count = point_num1 * point_num2;
	//unsigned int guess_KEY_num = 65536; //추측 키 갯수 256 * 256 = 65536


	float pointer = 0;
	double Correlation = 0.;
	double Correlation_L = 0.;
	double Correlation_R = 0.;
	unsigned int Right_Key = 0;
	double Max = 0;

	trace_HEADER header;
	fread(&header, sizeof(header), 1, trace); //앞의 값 읽어오기
	printf(" -------------------------------파형 정보-------------------------------\n");
	printf("|	파형갯수	:	%d				|\n", header.trace_no);
	printf("|	포인트수	:	%d				|\n", header.point_no);
	printf(" -----------------------------------------------------------------------\n");
	

	/************************************************************************************/
	/*                                   변수 동적할당                                  */
	/************************************************************************************/

	// 분석 포인트 저장
	double* po_trace = (double*)calloc(sizeof(double), point_num1 + point_num2);

	// 평문 저장
	unsigned char* plaintext = (unsigned char*)calloc(sizeof(unsigned char), Block_Size); //16 바이트 저장

	// 중간값
	//unsigned int* middle = (unsigned int*)calloc(sizeof(unsigned int), GUESS_KEY_NUM);
	unsigned int middle = 0;

	// 키(인덱스)값에 따른 최대 상관계수 저장할 변수
	double* Corr = (double*)calloc(sizeof(double), GUESS_KEY_NUM);

#if !_PREPROCESSING_
	float* average = (float*)calloc(sizeof(float), (point_num1 + point_num2));
	float* AT1 = (float*)calloc(sizeof(float), point_num1);
	float* AT2 = (float*)calloc(sizeof(float), point_num2);
#endif

	// E[XY] 저장
	double** sum_xy = (double**)calloc(sizeof(double*), GUESS_KEY_NUM);
	for (unsigned int i = 0; i < GUESS_KEY_NUM; i++) {
		sum_xy[i] = (double*)calloc(sizeof(double), point_count);
	}


	//// 추측한 비밀키 저장
	//unsigned int* index = (unsigned int*)calloc(sizeof(unsigned int), byte);

	//// 상관계수들의 최댓값
	//float* maxCorrs = (float*)calloc(sizeof(float), byte);

	// 중간값 E[X] 저장
	double* sum_x = (double*)calloc(sizeof(double), GUESS_KEY_NUM);

	// 파형 측정값 E[Y] 저장
	double* sum_y = (double*)calloc(sizeof(double), point_count);

	// 중간값 E[X^2] 저장
	double* sum_x2 = (double*)calloc(sizeof(double), GUESS_KEY_NUM);

	// 파형 측정값 E[Y^2] 저장
	double* sum_y2 = (double*)calloc(sizeof(double), point_count);

	
#if !_PREPROCESSING_
	// 포인트별 평균 구하기
	_fseeki64(trace, 32 + sizeof(float) *_START_POINT_1, SEEK_SET);
	for (unsigned int tn = 0; tn < _TRACE_NUM_; tn++)
	{
		fread(AT1, sizeof(float), point_num1, trace);
		_fseeki64(trace, sizeof(float) * ((__int64)_START_POINT_2 - (__int64)_START_POINT_1 - (__int64)point_num1), SEEK_CUR);
		fread(AT2, sizeof(float), point_num2, trace);
		_fseeki64(trace, sizeof(float) * ((__int64)header.point_no - (__int64)_START_POINT_2 - (__int64)point_num2 + (__int64)_START_POINT_1), SEEK_CUR);
		
		for (unsigned int i = 0; i < point_num1; i++)
			average[i] += (float)AT1[i];

		for (unsigned int k = 0; k < point_num2; k++)
			average[point_num1 + k] += (float)AT2[k];

	}
	
	
	for (unsigned int i = 0; i < point_num1 + point_num2; i++) {
		average[i] /= (float)_TRACE_NUM_;
		//printf("%g\n", average[i]);
	}
		

#endif
	for (int i = 0; i < _TRACE_NUM_; i++) {
		
		//평문 받아오기
		_fseeki64(plain, ((__int64)Block_Size * (__int64)3 + (__int64)2) * (__int64)i, SEEK_SET);
		for (int j = 0; j < Block_Size; j++) {
			fscanf(plain, "%hhx", &plaintext[j]);
		}
		
		//포안트 값 읽어오기
		_fseeki64(trace, 32 + ((__int64)header.point_no * (__int64)i + (__int64)_START_POINT_1 - (__int64)1) * (__int64)4, SEEK_SET);
		for (int j = 0; j < point_num1; j++) {
			fread(&pointer, sizeof(float), 1, trace);//파형의 첫번쩨 포인트정보 불러오기
			fread(&pointer, sizeof(float), 1, trace);//파형의 첫번쩨 포인트정보 불러오기
			po_trace[j] = (double)pointer;
		}
		_fseeki64(trace, 32 + ((__int64)header.point_no * (__int64)i + (__int64)_START_POINT_2 - (__int64)1) * (__int64)4, SEEK_SET);
		for (int j = 0; j < point_num2; j++) {
			fread(&pointer, sizeof(float), 1, trace);//같은 파형의 다음 포인트 정보 불러오기
			po_trace[j + point_num1] = (double)pointer;
			//printf("po_trace = %g\n",po_trace[j]);
		}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		
	
		    // E[Y], E[Y^2] 계산
#if !_PREPROCESSING_
		for (unsigned int j = 0; j < point_num1; j++) {
			for (unsigned int k = 0; k < point_num2; k++) {
				sum_y[j * point_num2 + k] += (po_trace[j] - average[j]) * (po_trace[point_num1 + k] - average[point_num1 + k]);
				sum_y2[j * point_num2+ k] += (po_trace[j] - average[j]) * (po_trace[point_num1 + k] - average[point_num1 + k])
					* (po_trace[j] - average[j]) * (po_trace[point_num1 + k] - average[point_num1 + k]);
				//printf("sum_y = %g\n", sum_y[j * point_num2 + k]);
			}
		}
#else
		for (int j = 0; j < point_num1; j++) {
			for (int k = 0; k < point_num2; k++) {
				sum_y[j * point_num2 + k] += fabs(po_trace[j] - po_trace[point_num1 + k]);
				sum_y2[j * point_num2 + k] += (po_trace[j] - po_trace[point_num1 + k]) * (po_trace[j] - po_trace[point_num1 + k]);
			}
		}
#endif

		

		for (unsigned int key = 0; key < GUESS_KEY_NUM; key++) {
			// Hamming Weight 계산

			middle = HW(S_Box[plaintext[byte1 - 1] ^ (key >> 8)] ^ S_Box[plaintext[byte2 - 1] ^ (key & 0xFF)]);
			//printf("middle = %d\n", middle);
			
			// E[X], E[X^2] 계산
			sum_x[key] += (double)middle;
			sum_x2[key] += (double)middle * middle;

			//printf("sum_x = %lf\n", sum_x[key]);
			//printf("sum_x2 = %lf\n", sum_x2[key]);

			// E[XY] 계산
#if !_PREPROCESSING_
			for (int x = 0; x < point_num1; x++) {
				for (int y = 0; y < point_num2; y++) {
					sum_xy[key][x * point_num2 + y] += (double)middle * (po_trace[x] - average[x]) * (po_trace[point_num1 + y] - average[point_num1 + y]);
					//printf("sum_xy = %g\n", sum_xy[key][x * point_num2 + y]);
				}
			}
#else
			for (int x = 0; x < point_num1; x++) {
				for (int y = 0; y < point_num2; y++) {
					sum_xy[key][x * point_num2 + y] += (double)middle * fabs(po_trace[x] - po_trace[point_num1 + y]);
				}
			}
#endif
		}

	}

	// 키에 대한 상관계수 계산 및 결과 값 저장
	for (unsigned int Guess_Key = 0; Guess_Key < GUESS_KEY_NUM; Guess_Key++) {

		for (unsigned long long x = 0; x < point_count; x++) {
			Correlation_L = (double)_TRACE_NUM_ * sum_xy[Guess_Key][x] - sum_y[x] * (double)sum_x[Guess_Key];
			Correlation_R = ((double)_TRACE_NUM_ * (double)sum_x2[Guess_Key] - (double)sum_x[Guess_Key] * (double)sum_x[Guess_Key]) * ((double)_TRACE_NUM_ * sum_y2[x] - sum_y[x] * sum_y[x]);

			if (Correlation_R <= (double)0) {
				Correlation = (double)0;
			}
			else {
				Correlation = Correlation_L / sqrt(Correlation_R);
				Correlation = fabs(Correlation);
			}
			if (Corr[Guess_Key] < Correlation) {
				Corr[Guess_Key] = Correlation;
			}

		}
	}
	for (unsigned int Guess_Key = 0; Guess_Key < GUESS_KEY_NUM; Guess_Key++) {

		if (Max < Corr[Guess_Key]) {
			Max = Corr[Guess_Key];
			Right_Key = Guess_Key;
		}

	}

	printf("추측키: %04x 상관계수: %g\n", Right_Key, Max);

#if !_PREPROCESSING_
		// Product Combine 전처리 수행시 사용하는 포인트별 평균 저장
		free(average);
		free(AT1);
		free(AT2);
#endif
	free(sum_x), free(sum_y), free(sum_x2), free(sum_y2);
	for (int i = 0; i < point_count; i++) {
		free(sum_xy[i]);
	}
	free(sum_xy);
	/*free(maxCorrs),*/ free(Corr);
	free(po_trace);
	free(plaintext);
	//free(middle);
	/*free(index);*/

	fclose(plain);
	fclose(trace);
}