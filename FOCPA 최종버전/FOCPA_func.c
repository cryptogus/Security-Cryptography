/*----------------------------------------------------------------------------------*/
/*	Visual Studio 2019 ���� ���â ����                                           */
/*----------------------------------------------------------------------------------*/
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "FOCPA.h"

//�عֿ���Ʈ �Լ�
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
//int HW[256] = { //AES SBox���� �عֿ���Ʈ ���̺�
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
	
	//�����Ҵ��� ���� ����
	unsigned int byte = last_byte - start_byte + 1; 
	unsigned long long point_num = _END_POINT_ - _START_POINT_;
	
	trace_HEADER header;
	fread(&header, sizeof(header), 1, trace); //���� �� �о����
	printf(" -------------------------------���� ����-------------------------------\n");
	printf("|	��������	:	%d				|\n", header.trace_no);
	printf("|	����Ʈ��	:	%d				|\n", header.point_no);
	printf(" -----------------------------------------------------------------------\n");
	/*�������� �����Ҵ� 2���� �迭 ����Ʈ[��������][����Ʈ����]
	double **po_trace = (double**)calloc(sizeof(double*), header.trace_no);
	for (int i = 0; i < header.trace_no; i++) {
		po_trace[i] = (double*)calloc(sizeof(double), header.point_no);
	}*/

	/////// ������ �����Ҵ� 2���� �迭
	//char **plaintext = (char**)calloc(sizeof(char*) , header.trace_no);//��
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
	//plaintext���� �� �޾ƿԴ��� Ȯ��
	/*for (int i = 0; i < header.trace_no; i++) {
		for (int j = 0; j < byte; j++) {
			printf("%hhx ", plaintext[i][j]);
		}
		printf("\n");
	}*/

	/************************************************************************************/
	/*                                   ���� �����Ҵ�                                   /
	/************************************************************************************/
	
	// �м� ����Ʈ ����
	double* po_trace = (double*)calloc(sizeof(double), point_num);
	//float* po_trace = (float*)calloc(sizeof(float), header.point_no); -> ���� ����Ʈ ���θ� �̿��Ҷ� header.point_no ������ �־��ش�
	
	// �� ����
	unsigned char* plaintext = (unsigned char*)calloc(sizeof(unsigned char), byte); //16 ����Ʈ ����

	// �߰���
	unsigned int* middle = (unsigned int*)calloc(sizeof(unsigned int), 256);
	
	// ������ ���Ű ����
	unsigned int* index = (unsigned int*)calloc(sizeof(unsigned int), byte);

	//�ĺ�Ű�� ���������� �ִ�
	double* keymaxCorrs = (double*)calloc(sizeof(double), 256);

	double* MaxCorrs = (double*)calloc(sizeof(double), byte);
	
	//1�� �������� 2�� �������� ����
	double* ratio = (double*)calloc(sizeof(double), byte);

	// ���� ������ E[X] ����
	double* sum_x = (double*)calloc(sizeof(double), point_num);
	
	// �߰��� E[Y] ����
	double* sum_y = (double*)calloc(sizeof(double), 256);
	
	// E[XY] ����
	double** sum_xy = (double**)calloc(sizeof(double*), 256);
	for (int i = 0; i < 256; i++) {
		sum_xy[i] = (double*)calloc(sizeof(double), point_num);
	}

	// E[X^2] ����
	double* sum_x2 = (double*)calloc(sizeof(double), point_num);
	
	// E[Y^2] ����
	double* sum_y2 = (double*)calloc(sizeof(double), 256);
	unsigned int point;
	float pointer;
	double under_Corr = 0;
	double up_Corr = 0;
	double Corr = 0;
	for (int i = 0; i < byte; i++) {
		//���� �ʱ�ȭ �κ�
		//Corr = 0;
		int second_key = 0;
		fseek(plain, 3 * (start_byte - 1), SEEK_SET); //��.txt ������ ������� �� 3�� �ǳʶپ���� ex)�о� �� �� ĳ���� ��ġ ������ ���°� 0xff��� "ff "��ŭ �ǳ� �پ����
 		fseek(trace, 32  + sizeof(float) * (_START_POINT_ - 1), SEEK_SET);
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
		for (unsigned int j = 0; j < _TRACE_NUM_; j++) {
			
			for (int j = 0; j < byte; j++) {
				fscanf(plain, "%hhx", &plaintext[j]);
			}//�� �޾ƿ���
			fseek(plain, 3*(Block_Size - byte + 1), SEEK_CUR);	//���� ���� start_byte ��ġ�� �ű�� �Լ�(�� ������� �� 3�� �ǳʶپ����)
			
			//�������� �ҷ�����
			for (int pi = 0; pi < point_num; pi++) {
				fread(&pointer, sizeof(float), 1, trace);//�������� �ҷ�����
				po_trace[pi] = (double)pointer;
			}
																																
			fseek(trace, sizeof(float)*(header.point_no - point_num), SEEK_CUR);
																																  
			for (point = 0; point < point_num; point++) {

				sum_x[point] = sum_x[point] + po_trace[point]; //������ X���� ������ ��
				sum_x2[point] = sum_x2[point] + po_trace[point] * po_trace[point]; //����
			}

			for (unsigned int key = 0; key < 0x100; key++) {

				middle[key] = HW(S_Box[plaintext[i] ^ key]); //subbyte �عֿ���Ʈ��
				sum_y[key] = sum_y[key] + middle[key];
				for (point = 0; point < point_num; point++) {
					sum_xy[key][point] = sum_xy[key][point] + po_trace[point] * middle[key]; //xy�� ��
				}

				sum_y2[key] = sum_y2[key] + (double)middle[key] * middle[key];
			}
			//�ִ� �������� ���ϱ�
		}
		for (unsigned int key = 0; key < 0x100; key++) {
			
			for (point = 0; point < point_num; point++) {
				under_Corr = ((_TRACE_NUM_ * sum_x2[point]) - (sum_x[point] * sum_x[point]))* ((_TRACE_NUM_ * sum_y2[key]) - (sum_y[key] * sum_y[key]));
				up_Corr = (_TRACE_NUM_ * sum_xy[key][point]) - (sum_x[point] * sum_y[key]);
				//Corr = fabs(((_TRACE_NUM_ *sum_xy[key][point]) - (sum_x[point] * sum_y[key]))/ sqrt(((_TRACE_NUM_ *sum_x2[point]) - (sum_x[point] * sum_x[point])) * ((_TRACE_NUM_ * sum_y2[key]) - (sum_y[key] * sum_y[key]))));// ������� ����
				if (under_Corr <= (double)0) {
					under_Corr = (double)0;
				}
				else {
					Corr = up_Corr / sqrt(under_Corr);
					Corr = fabs(Corr);
				}
				//Ű �� ���ϱ�
				if (MaxCorrs[i] < Corr) {
					MaxCorrs[i] = Corr;
					index[i] = key;
				}
				//Ű �ĺ��� �ִ� ������
				if (keymaxCorrs[key] < Corr) {
					keymaxCorrs[key] = Corr;
				}
			}

		}
		for (int a = 0; a < 256; a++)
		{
			if ((keymaxCorrs[a] > ratio[i]) && (a != index[i]))
			{
				second_key = a;
				ratio[i] = keymaxCorrs[a];
			}
		}
		ratio[i] = MaxCorrs[i] / ratio[i];

	}
	printf("������ Ű��: ");
	for (int i = 0; i < byte; i++) {
		printf("%02x ", index[i]);
	}
	printf("\n\n");
	for (int i = 0; i < byte; i++) {
		printf("%02d��° ����Ʈ �ִ� ������ %g \n", start_byte + i ,MaxCorrs[i]);
	}
	printf("\n\n");
	for (int i = 0; i < byte; i++) {
		printf("%02d��° ����Ʈ ratio %g\n", start_byte + i, ratio[i]);
	}
	free(sum_x), free(sum_y), free(sum_x2), free(sum_y2);
	for (int i = 0; i < point_num; i++) {
		free(sum_xy[i]);
	}
	free(sum_xy);
	free(ratio);
	free(MaxCorrs);
	free(keymaxCorrs);
	free(po_trace);
	free(plaintext);
	free(middle);
	free(index);

	fclose(plain);
	fclose(trace);
}