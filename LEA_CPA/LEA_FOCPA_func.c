/*----------------------------------------------------------------------------------*/
/*	Visual Studio 2019 ���� ���â ����                                           */
/*----------------------------------------------------------------------------------*/
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "LEA_FOCPA.h"

//Little Endian
#define GETU32(pt) (((word)(pt)[3] << 24) ^ ((word)(pt)[2] << 16) ^ ((word)(pt)[1] <<  8) ^ ((word)(pt)[0]))
#define PUTU32(ct, st) { (ct)[3] = (byte)((st) >> 24); (ct)[2] = (byte)((st) >> 16); (ct)[1] = (byte)((st) >>  8); (ct)[0] = (byte)(st); }

//=====
// ����Ʈ b[16] --> ���� state[4]
void byte2state(byte b[16], word state[4]) {
	state[0] = GETU32(b);
	state[1] = GETU32(b + 4);
	state[2] = GETU32(b + 8);
	state[3] = GETU32(b + 12);
}

//=====
// ���� state[4] --> ����Ʈ b[16]
void state2byte(word state[4], byte b[16]) {
	PUTU32(b, state[0]);
	PUTU32(b + 4, state[1]);
	PUTU32(b + 8, state[2]);
	PUTU32(b + 12, state[3]);
}
word ROR(word x, word i) {
	return ((x) >> (i)) | ((x) << (32 - (i)));
}

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


void LEA_CPA() {


	FILE* trace = fopen(trace_path, "rb");
	FILE* plain = fopen(plain_path, "r");
#if target == 2
	FILE* cipher = fopen(cipher_path, "r");
#endif
	//�����Ҵ��� ���� ����
	unsigned int byte = last_byte - start_byte + 1;
	unsigned long long point_num = _END_POINT_ - _START_POINT_;

	trace_HEADER header;
	fread(&header, sizeof(header), 1, trace); //���� �� �о����
	printf(" -------------------------------���� ����-------------------------------\n");
	printf("|	��������	:	%d				|\n", header.trace_no);
	printf("|	����Ʈ��	:	%d				|\n", header.point_no);
	printf(" -----------------------------------------------------------------------\n");

	/************************************************************************************/
	/*                                   ���� �����Ҵ�                                   /
	/************************************************************************************/

	// �м� ����Ʈ ����
	double* po_trace = (double*)calloc(sizeof(double), point_num);
	//float* po_trace = (float*)calloc(sizeof(float), header.point_no); -> ���� ����Ʈ ���θ� �̿��Ҷ� header.point_no ������ �־��ش�

#if target == 0 || target == 2	// 0 - �� ����(ù��° XOR ����), 2 - �� ��ȣ�� ����
	unsigned char* plaintext = (unsigned char*)calloc(sizeof(unsigned char), 16); 
	// �߰���
	unsigned int* middle = (unsigned int*)calloc(sizeof(unsigned int), Guess_key);

	// ������ ���Ű ����
	unsigned int* index = (unsigned int*)calloc(sizeof(unsigned int), byte);

	//�ĺ�Ű�� ���������� �ִ�
	double* keymaxCorrs = (double*)calloc(sizeof(double), Guess_key);

	//1�� Ű�� ������
	double* MaxCorrs = (double*)calloc(sizeof(double), byte);

	//1�� �������� 2�� �������� ����
	double* ratio = (double*)calloc(sizeof(double), byte);

	// ���� ������ E[X] ����
	double* sum_x = (double*)calloc(sizeof(double), point_num);

	// �߰��� E[Y] ����
	double* sum_y = (double*)calloc(sizeof(double), Guess_key);

	// E[XY] ����
	double** sum_xy = (double**)calloc(sizeof(double*), Guess_key);
	for (unsigned int i = 0; i < Guess_key; i++) {
		sum_xy[i] = (double*)calloc(sizeof(double), point_num);
	}


	// E[X^2] ����
	double* sum_x2 = (double*)calloc(sizeof(double), point_num);

	// E[Y^2] ����
	double* sum_y2 = (double*)calloc(sizeof(double), Guess_key);

	//�ι�° �ĺ�Ű
	unsigned int* second_key = (unsigned int*)calloc(sizeof(unsigned int), byte);
#elif target == 1 //(ù��° ��ⷯ ���� ����)
	unsigned char* plaintext = (unsigned char*)calloc(sizeof(unsigned char), Block_Size);//16 ����Ʈ ����
	unsigned int** middle = (unsigned int**)calloc(sizeof(unsigned int*), 256);
	for (int i = 0; i < 256; i++) {
		middle[i] = (unsigned int*)calloc(sizeof(unsigned int), 256);
	}

	// ������ ���Ű ����
	unsigned int* index = (unsigned int*)calloc(sizeof(unsigned int), byte);

	//�ĺ�Ű�� ���������� �ִ�
	double* keymaxCorrs = (double*)calloc(sizeof(double), 256);

	//1�� Ű�� ������
	double* MaxCorrs = (double*)calloc(sizeof(double), byte);

	//1�� �������� 2�� �������� ����
	double* ratio = (double*)calloc(sizeof(double), byte);

	// ���� ������ E[X] ����
	double* sum_x = (double*)calloc(sizeof(double), point_num);

	// �߰��� E[Y] ����
	double** sum_y = (double**)calloc(sizeof(double*), 256);
	for (int i = 0; i < 256; i++) {
		sum_y[i] = (double*)calloc(sizeof(double), 256);
	}

	// E[XY] ����
	double*** sum_xy = (double***)calloc(sizeof(double**), 256);
	for (int i = 0; i < 256; i++) {
		sum_xy[i] = (double**)calloc(sizeof(double*), 256);
		for (int j = 0; j < 256; j++) {
			sum_xy[i][j] = (double*)calloc(sizeof(double), point_num);
		}
	}


	// E[X^2] ����
	double* sum_x2 = (double*)calloc(sizeof(double), point_num);

	// E[Y^2] ����
	double** sum_y2 = (double**)calloc(sizeof(double*), 256);
	for (int i = 0; i < 256; i++) {
		sum_y2[i] = (double*)calloc(sizeof(double), 256);
	}

	//�ι�° �ĺ�Ű
	unsigned int* second_key = (unsigned int*)calloc(sizeof(unsigned int), byte);
#endif
	


	unsigned int point;
	float pointer;
	double under_Corr = 0;
	double up_Corr = 0;
	double Corr = 0;
	unsigned int delta[8] = { 0xc3efe9db, 0x44626b02, 0x79e27c8a, 0x78df30ec, 0x715ea49e, 0xc785da0a, 0xe04ef22a,0xe5c40957 };
	unsigned int Plaintext[4] = { 0, };
	
	for (int i = 0; i < byte; i++) {
		//���� �ʱ�ȭ �κ�
		//Corr = 0;
		for (int a = 0; a < Guess_key; a++)
		{
			keymaxCorrs[a] = 0;
		}
#if target == 2
		_fseeki64(cipher, 0, SEEK_SET);
#endif
		_fseeki64(plain, 3 * (start_byte - 1), SEEK_SET); //��.txt ������ ������� �� 3�� �ǳʶپ���� ex)�о� �� �� ĳ���� ��ġ ������ ���°� 0xff��� "ff "��ŭ �ǳ� �پ����
		_fseeki64(trace, 32 + sizeof(float) * (_START_POINT_ - 1), SEEK_SET);
#if target == 0 || target == 2
		//���� �ʱ�ȭ
		for (int i = 0; i < Guess_key; i++) {
			sum_y[i] = 0;
			sum_y2[i] = 0;
			for (point = 0; point < point_num; point++) {
				sum_xy[i][point] = 0;
			}
		}
#elif target == 1
		for (int i = 0; i < 256; i++) {
			for (int j = 0; j < 256; j++) {
				sum_y[i][j] = 0;
				sum_y2[i][j] = 0;
				for (point = 0; point < point_num; point++) {
					sum_xy[i][j][point] = 0;
				}
			}
		}
#endif
		for (point = 0; point < point_num; point++) {
			sum_x[point] = 0;
			sum_x2[point] = 0;
		}
		for (unsigned int j = 0; j < _TRACE_NUM_; j++) {
#if target == 0
			for (int j = 0; j < byte; j++) {
				fscanf(plain, "%hhx", &plaintext[j]);
				//printf("%02x ", plaintext[j]);
			}//�� �޾ƿ���
			//printf("\n");
			_fseeki64(plain, 3 * (Block_Size - byte + 1), SEEK_CUR); //���� ���� start_byte ��ġ�� �ű�� �Լ�(�� ������� �� 3�� �ǳʶپ����)
#elif target == 1
			for (int j = 0; j < 16; j++) {
				fscanf(plain, "%hhx", &plaintext[j]);
			}//�� �޾ƿ���
			_fseeki64(plain, 0, SEEK_CUR);
#elif target == 2
			for (int j = 0; j < 16; j++) {
				fscanf(cipher, "%hhx", &plaintext[j]); //���� �̸��� plaintext
				//printf("%02x ", plaintext[j]);
			}//��ȣ�� �޾ƿ���
			//printf("\n");
			_fseeki64(cipher, 0, SEEK_CUR);
#endif
			
			//�������� �ҷ�����
			for (int pi = 0; pi < point_num; pi++) {
				fread(&pointer, sizeof(float), 1, trace);//�������� �ҷ����� fraed�� floatũ�⸸ŭ �޾ƿ��⿡ ���� pointer�� �ڷ����� float(double ���̸� ������ �ս��� �Ͼ)
				po_trace[pi] = (double)pointer;
				//printf("%g\n", po_trace[pi]);
			}

			_fseeki64(trace, sizeof(float) * (header.point_no - point_num), SEEK_CUR);

			for (point = 0; point < point_num; point++) {

				sum_x[point] = sum_x[point] + po_trace[point]; //������ X���� ������ ��
				sum_x2[point] = sum_x2[point] + po_trace[point] * po_trace[point]; //����
			}

			for (unsigned int key = 0; key < Guess_key; key++) {
#if target == 0
				//Xor ���ݽ� ���� ����Ű rk[0][0] = 0xb40ad00d
				middle[key] = HW(plaintext[i] ^ key);
				sum_y[key] = sum_y[key] + middle[key];
				for (point = 0; point < point_num; point++) {
					sum_xy[key][point] = sum_xy[key][point] + po_trace[point] * middle[key]; //xy�� ��
				}

				sum_y2[key] = sum_y2[key] + (double)middle[key] * middle[key];
#elif target == 1
				//LEA���� �� modulo addtion�� ��°� �عֿ���Ʈ
				for (int guesskey2 = 0; guesskey2 < 0x100; guesskey2++) {
					middle[key][guesskey2] = HW(((plaintext[i] ^ key) + (plaintext[i + 4] ^ guesskey2)) & 0xff);
					sum_y[key][guesskey2] = sum_y[key][guesskey2] + middle[key][guesskey2];

					for (point = 0; point < point_num; point++) {
						sum_xy[key][guesskey2][point] = sum_xy[key][guesskey2][point] + po_trace[point] * middle[key][guesskey2]; //xy�� ��
					}

					sum_y2[key][guesskey2] = sum_y2[key][guesskey2] + (double)middle[key][guesskey2] * middle[key][guesskey2];
				}

#elif target == 2
				byte2state(plaintext, Plaintext);
				//printf("%08x\n", Plaintext[3]);
				middle[key] = HW((ROR(Plaintext[0], 9) - (Plaintext[3] ^ key)) & 0xff);
				//middle[key] = HW(plaintext[1] - (plaintext[12] ^ key));
				sum_y[key] = sum_y[key] + middle[key];
				for (point = 0; point < point_num; point++) {
					sum_xy[key][point] = sum_xy[key][point] + po_trace[point] * middle[key]; //xy�� ��
				}
				sum_y2[key] = sum_y2[key] + (double)middle[key] * middle[key];
#endif
				
			}
			//�ִ� �������� ���ϱ�
		}
		for (unsigned int key = 0; key < Guess_key; key++) {
#if target == 0	|| 2
			for (point = 0; point < point_num; point++) {
				under_Corr = ((_TRACE_NUM_ * sum_x2[point]) - (sum_x[point] * sum_x[point])) * ((_TRACE_NUM_ * sum_y2[key]) - (sum_y[key] * sum_y[key]));
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



#elif target == 1
			for (unsigned int key2 = 0; key2 < 0x100; key2++){
				for (point = 0; point < point_num; point++) {
					under_Corr = ((_TRACE_NUM_ * sum_x2[point]) - (sum_x[point] * sum_x[point])) * ((_TRACE_NUM_ * sum_y2[key][key2]) - (sum_y[key][key2] * sum_y[key][key2]));
					up_Corr = (_TRACE_NUM_ * sum_xy[key][key2][point]) - (sum_x[point] * sum_y[key][key2]);
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
#endif
			}
		}


		for (int a = 0; a < Guess_key; a++)
		{
			if ((keymaxCorrs[a] > ratio[i]) && (a != index[i]))
			{
				second_key[i] = a;
				ratio[i] = keymaxCorrs[a];
			}
		}
		ratio[i] = MaxCorrs[i] / ratio[i];

	}
	printf("������ ���� Ű��: ");
	for (int i = 0; i < byte; i++) {
		printf("%02x ", index[i]);
	}
	printf("\n\n");
	for (int i = 0; i < byte; i++) {
		printf("%02d��° ����Ʈ �ִ� ������ %g \n", start_byte + i, MaxCorrs[i]);
	}
	printf("\n\n");
	for (int i = 0; i < byte; i++) {
		printf("%02d��° ����Ʈ ratio %g   �ι�° �ĺ�Ű: 0x%02x\n", start_byte + i, ratio[i], second_key[i]);
	}
#if target == 0 || 2
	free(sum_x), free(sum_y), free(sum_x2), free(sum_y2);
	for (int i = 0; i < Guess_key; i++) {
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
	free(second_key);
	
#elif target == 1
	for (int i = 0; i < 256; i++) {
		free(sum_y[i]);
		free(sum_y2[i]);
		free(middle[i]);
	}
	free(sum_x), free(sum_y), free(sum_x2), free(sum_y2);
	for (int i = 0; i < 256; i++) {
		for (int j = 0; j < point_num; j++) {
			free(sum_xy[i][j]);
		}
	}
	for (int i = 0; i < 256; i++) {
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
	free(second_key);
#endif
#if target == 2
	fclose(cipher);
#endif
	fclose(plain);
	fclose(trace);
}