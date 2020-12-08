#include <stdio.h>																		  /**************************����*****************************/
#include <string.h>																		  //��ȣȭ�������  ������ padding�� �ߴٴ� �����Ͽ� �ڵ带 «.
#include <stdlib.h>																		  //
#include <time.h>																		  //
																						  //
int Byte;

//CTR���� ���� key, IV test vector�� �ִ� , vector���� ����Ʈhttps://www.cnblogs.com/shangdawei/p/4589924.html

unsigned char key[16] = { 0x2b,0x7e,0x15,0x16,0x28,0xae,0xd2,0xa6,0xab,0xf7,0x15,0x88,0x09,0xcf,0x4f,0x3c };
unsigned char IV[16] = { 0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0a,0x0b,0x0c,0x0d,0x0e,0x0f };

/////////////////////////////////ECB��� test vetor////////////////////////////////////////////////////////////
unsigned char ECB_plainText[16] = { 0x6b,0xc1,0xbe,0xe2,0x2e,0x40,0x9f,0x96,0xe9,0x3d,0x7e,0x11,0x73,0x93,0x17,0x2a };
unsigned char ECB_CipherText[16] = { 0x3a,0xd7,0x7b,0xb4,0x0d,0x7a,0x36,0x60,0xa8,0x9e,0xca,0xf3,0x24,0x66,0xef,0x97 };

/////////////////////////////CBC��� test vector////////////////////////////////
unsigned char CBC_plainText[16] = { 0x6b,0xc1,0xbe,0xe2,0x2e,0x40,0x9f,0x96,0xe9,0x3d,0x7e,0x11,0x73,0x93,0x17,0x2a };
unsigned char CBC_CipherText[16] = { 0x76,0x49,0xab,0xac,0x81,0x19,0xb2,0x46,0xce,0xe9,0x8e,0x9b,0x12,0xe9,0x19,0x7d };

///////////////////////////////CFB TEST VECTOR////////////////////////////////////////
unsigned char CFB_plainText[16] = { 0x6b,0xc1,0xbe,0xe2,0x2e,0x40,0x9f,0x96,0xe9,0x3d,0x7e,0x11,0x73,0x93,0x17,0x2a };
unsigned char CFB_CipherText[16] = { 0x3b,0x3f,0xd9,0x2e,0xb7,0x2d,0xad,0x20,0x33,0x34,0x49,0xf8,0xe8,0x3c,0xfb,0x4a };

///////////////////////////////OFB test vector/////////////////////////////////////////////////////
unsigned char OFB_plainText[16] = { 0x6b,0xc1,0xbe,0xe2,0x2e,0x40,0x9f,0x96,0xe9,0x3d,0x7e,0x11,0x73,0x93,0x17,0x2a };
unsigned char OFB_CipherText[16] = { 0x3b,0x3f,0xd9,0x2e,0xb7,0x2d,0xad,0x20,0x33,0x34,0x49,0xf8,0xe8,0x3c,0xfb,0x4a };


///////////////////////////////////CTR����� TEST Vector//////////////////////////////////////////////////////////////
unsigned char key_ctr[16] = { 0x2b,0x7e,0x15,0x16,0x28,0xae,0xd2,0xa6,0xab,0xf7,0x15,0x88,0x09,0xcf,0x4f,0x3c };		 
unsigned char IV_ctr[16] = { 0xf0,0xf1,0xf2,0xf3,0xf4,0xf5,0xf6,0xf7,0xf8,0xf9,0xfa,0xfb,0xfc,0xfd,0xfe,0xff };
unsigned char CTR_plainText[16] = { 0x6b,0xc1,0xbe,0xe2,0x2e,0x40,0x9f,0x96,0xe9,0x3d,0x7e,0x11,0x73,0x93,0x17,0x2a };
unsigned char CTR_CipherText[16] = { 0x87,0x4d,0x61,0x91,0xb6,0x20,0xe3,0x26,0x1b,0xef,0x68,0x64,0x99,0x0d,0xb6,0xce };
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*************************�е� �԰�*************************/
unsigned char* PKCS_7(unsigned char* text) {


	//////�߰��� ����Ʈ ��/////////////
	unsigned char pad;
	pad = 16 - (Byte % 16);

	///////////////////////////////////
	unsigned char* test1 = malloc(pad + Byte);

	memcpy(test1, text, Byte);

	for (int i = Byte; i < Byte + pad; i++) {
		test1[i] = pad;
	}
	printf("�е� : ");
	for (int i = 0; i < Byte + pad; i++) {
		printf("%x ", test1[i]);
	}
	printf("\n");
	return test1;
}

unsigned char* IEC(unsigned char* text) {

	unsigned char pad;
	pad = 16 - (Byte % 16);

	unsigned char* test1 = malloc(pad + Byte);

	memcpy(test1, text, Byte);
	test1[Byte] = 0x80;
	for (int i = Byte + 1; i < Byte + pad; i++) {
		test1[i] = 0x00;
	}
	printf("�е� : ");
	for (int i = 0; i < Byte + pad; i++) {
		printf("%x ", test1[i]);
	}

	printf("\n");
	return test1;

}

unsigned char* ANSI(unsigned char* text) {

	unsigned char pad;
	pad = 16 - (Byte % 16);

	unsigned char* test1 = malloc(pad + Byte);
	memcpy(test1, text, Byte);

	for (int i = Byte; i < Byte + pad; i++) {
		test1[i] = 0x00;
	}

	test1[Byte + pad - 1] = pad;

	printf("�е� : ");
	for (int i = 0; i < Byte + pad; i++) {
		printf("%x ", test1[i]);
	}
	return test1;

}

unsigned char* ISO(unsigned char* text) {

	unsigned char pad;

	//////�߰��� ����Ʈ ��/////////////

	pad = 16 - (Byte % 16);
	unsigned char* test1 = malloc(pad + Byte);

	///////////////////////////////////
	memcpy(test1, text, Byte);


	for (int i = Byte; i < Byte + pad; i++) {
		srand(time(NULL) * i); //�������� �ٸ��� ���ֱ� ����
		test1[i] = rand() % 256;
	}
	test1[Byte + pad - 1] = pad;
	printf("�е� : ");
	for (int i = 0; i < Byte + pad; i++) {
		printf("%x ", test1[i]);
	}
	return test1;
}
void Del(unsigned char* text) { //PKCS_7, ANSI, ISO, IEC �԰� �е� ����


	//////������ ����Ʈ ��/////////////
	unsigned char del;
	del = text[15]; // ��ȣ�� decrypt���� ���� ���ڸ� �е��� ����Ʈ ũ��

	////////////////////////////////////////


	////IEC padding ���Ž� ����� ���� - �� �е��� ���� ���� 0�̱⶧���� 0�� �ƴ� �е����� ������ ����
	for (int a = 0; ; a++) {																	   //
		if (text[15 - a] == 0)																   //
			del++;																				   //
		else																					   //
			break;																				   //
		if (text[15 - a] == 0x80) {															   //
			del++;																				   //
			break;																				   //
		}																						   //
	}																						   //
	////////////////////////////////////////////////////////////////////////////////////////////////

	unsigned char* test1 = malloc(15 - del);

	memcpy(test1, text, Byte - del);


	for (int i = 0; i < Byte - del; i++) {
		printf("%x ", test1[i]);

	}
}



void ECB(unsigned char* text);
void CBC_en(unsigned char* text);
void CBC_de(unsigned char* text);
void OFB(unsigned char* text);
void CFB(unsigned char* text);
void CTR(unsigned char* text);
void AES_En(unsigned char cipherText[16], unsigned char plainText[16], unsigned char key[16]);
void AES_De(unsigned char cipherText[16], unsigned char plainText[16], unsigned char key[16]);

int main() {
	printf("�Է��� TEXT�� BYTEũ�� �Է�(test vector�� 16 byte) : ");
	scanf_s("%hd", &Byte);
																														 
	/*unsigned char* plaintext = (char*)malloc(sizeof(char) * Byte);														 
	printf("���� 16������ �Է� : ");																					 
	for (int i = 0; i < Byte; i++) {																					 
																														 
		scanf_s("%hhx", &plaintext[i]);																					 
	}
	printf("IV�� �Է� : ");
	for (int i = 0; i < Byte; i++) {															    
																									
		scanf_s("%hhx", &IV[i]);																    
	}*/																						        
																									
	

	/*���� ������� �Ϻ�ȣȭ�� ���� ������ ����*/ 
	// ��ȣȭ�� padding�� �Ǿ��ٴ� �ߴٴ� �����Ͽ� 16byte�Է½� 1���� �� ����
	
	ECB(ECB_plainText);									 //-- ��ȣȭ �׽�Ʈ
	printf("\n���� Text Vector�� : ");
	for (int i = 0; i < 16; i++) {
		printf("%x ",ECB_CipherText[i]);
	}
	/*
	ECB(ECB_CipherText);										//--��ȣȭ �׽�Ʈ
	printf("\nText Vector�� : ");
	for (int i = 0; i < 16; i++) {
		printf("%x ", ECB_plainText[i]);
	}*/
	
	/*CBC_en(CBC_plainText);
	printf("\nText Vector�� : ");									 //-- ��ȣȭ �׽�Ʈ
	for (int i = 0; i < 16; i++) {
		printf("%x ", CBC_CipherText[i]);
	}*/
	
	/*
	CBC_de(CBC_CipherText);													//--��ȣȭ �׽�Ʈ
	printf("\nText Vector�� : ");
	for (int i = 0; i < 16; i++) {
		printf("%x ", CBC_plainText[i]);
	}*/
	
	/*
	CFB(CFB_plainText);														  // -- ��ȣȭ �׽�Ʈ
	printf("\nText Vector�� : ");
	for (int i = 0; i < 16; i++) {
		printf("%x ", CFB_CipherText[i]);
	}*/

	/*
	CFB(CFB_CipherText);														//  --��ȣȭ �׽�Ʈ
	printf("\nText Vector�� : ");
	for (int i = 0; i < 16; i++) {
		printf("%x ", CFB_plainText[i]);
	}*/
	/*
	OFB(OFB_plainText);
	printf("\nText Vector�� : ");
	for (int i = 0; i < 16; i++) {
		printf("%x ", OFB_CipherText[i]);
	}*/
	
	/*
	OFB(OFB_CipherText);
	printf("\nText Vector�� : ");
	for (int i = 0; i < 16; i++) {
		printf("%x ", OFB_plainText[i]);
	}*/
	
	/*CTR(CTR_plainText); 
	printf("\nCTR cipher Vector�� : ");
	for (int i = 0; i < 16; i++) {
		printf("%x ", CTR_CipherText[i]);
	}
	/*
	CTR(CTR_CipherText);
	printf("\nCTR decrypt Vector�� : ");
	for (int i = 0; i < 16; i++) {
		printf("%x ", CTR_plainText[i]);
	}*/

}

void ECB(unsigned char* text) { //ECB����� ��ȣȭ
	unsigned char cipher[16] = { 0, };
	unsigned char plain[16] = { 0, };
	int choose;
	printf("ECB encrypt - 1, decrypt - 2 �� �Է� : ");
	scanf_s("%d", &choose);

	if (choose == 1) {

		//Byte / 16 + 1 �� �е� ����� �� ��
		printf("ECB ��ȣ�� : ");
		for (int i = 0; i < Byte / 16 + 1; i++) {
			for (int k = 0; k < 16; k++)
				plain[k] = text[k + 16 * i];

			AES_En(cipher, plain, key);
			for (int j = 0; j < 16; j++) {

				printf("%x ", cipher[j]);
			}
		}
		
	}
	else if (choose == 2) {

		printf("ECB ��ȣ�� : ");
		//��ȣ���� 16byte ������ ���ͼ� Byte / 16 �� ������ ��
		for (int i = 0; i < Byte / 16; i++) {
			for (int j = 0; j < 16; j++) {
				cipher[j] = text[j + 16 * i];
			}
			AES_De(plain, cipher, key);
			if (i == (Byte / 16 - 1) && Byte > 16) { //&& Byte > 16 ������ test vector���� �е��� �ȵǾ� �־ ���� ������ ������
				Del(plain); //  padding �����Լ�
				break;
			}
			for (int j = 0; j < 16; j++) {

				printf("%x ",plain[j]);
			}
		}
	}
	
}


void CBC_en(unsigned char* text) {

	unsigned char cipher[16] = { 0, };
	unsigned char plain[16] = { 0, };
	printf("CBC ��ȣ�� : ");
	for (int i = 0; i < Byte / 16 + 1; i++) {

		for(int k = 0; k < 16; k++)
			plain[k] = text[k + 16 * i];
		for (int k = 0; k < 16; k++)
			plain[k] ^= IV[k];
		AES_En(cipher, plain, key);

		for (int j = 0; j < 16; j++) {

			printf("%x ", cipher[j]);
			IV[j] = cipher[j];
		}

		
	}
}

void CBC_de(unsigned char* text) {

	unsigned char cipher[16] = { 0, };
	unsigned char plain[16] = { 0, };
	printf("CBC ��ȣ�� : ");
	for (int i = 0; i < Byte / 16; i++) {
		for (int j = 0; j < 16; j++) {
			cipher[j] = text[j + 16 * i];
		}
		AES_De(plain, cipher, key);
		for (int j = 0; j < 16; j++) {
			plain[j] = plain[j] ^ IV[j];
		}
		//i == (Byte / 16 - 1)�� ��ȣ���� ������ ��
		if (i == (Byte / 16 - 1) && Byte > 16) {//&&  Byte > 16 ������ test vector���� �е��� �ȵǾ� �־ ���� ������ ������
			Del(plain); // padding ����
			break;
		}
		for (int j = 0; j < 16; j++) {

			printf("%x ", plain[j]);
			IV[j] = cipher[j];
		}
	}
}

void OFB(unsigned char* text) {

	int choose;
	printf("OFB encrypt - 1, decrypt - 2 �� �Է� : ");;
	scanf_s("%d", &choose);
	unsigned char text2[16] = { 0, };

	for (int i = 0; i < Byte / 16 + 1; i++) {
		
		
		AES_En(IV, IV, key);

		for (int j = 0; j < 16; j++) 
			text2[j] = text[j + 16 * i] ^ IV[j];

		if (i == Byte / 16 -1 && choose == 2 && Byte > 16) {//&&  Byte > 16 ������ test vector���� �е��� �ȵǾ� �־ ���� ������ ������
			Del(text2); // padding ����
			break;
		}
		for (int j = 0; j < 16; j++) {
			printf("%x ", text2[j]);
		}
		
	}
}
void CFB(unsigned char* text) {
	unsigned char cipher[16] = { 0, };
	unsigned char plain[16] = { 0, };
	int choose;
	printf("encrypt - 1, decrypt - 2 �� �Է� : ");
	scanf_s("%d", &choose);
	if (choose == 1) {
		printf("CFB ��ȣ�� : ");
		for (int i = 0; i < Byte / 16 + 1; i++) {
			for (int k = 0; k < 16; k++)
				plain[k] = text[k + 16 * i];

			AES_En(IV, IV, key);

			for (int j = 0; j < 16; j++) {
				cipher[j] = plain[j] ^ IV[j];
				printf("%x ", cipher[j]);
				IV[j] = cipher[j];
			}
		}
	}
	else if(choose == 2){
		printf("CFB ��ȣ�� : ");
		for (int i = 0; i < Byte / 16; i++) {
			for (int k = 0; k < 16; k++)
				cipher[k] = text[k + 16 * i];

			AES_En(IV, IV, key);

			for (int j = 0; j < 16; j++) {
				plain[j] = cipher[j] ^ IV[j];

				if (i == Byte / 16 - 1 && Byte > 16) {//&&  Byte > 16������ test vector���� �е��� �ȵǾ� �־ ���� ������ ������
					Del(plain); // padding ����
					break;
				}
				printf("%x ", plain[j]);
				IV[j] = cipher[j];
			}
		}
	}

	
}

void CTR(unsigned char* text) {
	
	unsigned char cipher[16] = { 0, };
	unsigned char plain[16] = { 0, };
	unsigned int sum = 0;
	int choose;
	printf("encrypt -  0, decrypt - 1 �� �Է� : ");
	scanf_s("%d", &choose);
	for (int i = 0; i < Byte / 16 + 1; i++) {
		
		AES_En(IV_ctr, IV_ctr, key_ctr);
		
		for (int j = 0; j < 16; j++) {
			plain[j] = text[j + 16 * i];
			cipher[j] = plain[j] ^ IV_ctr[j];
			if (i == Byte / 16 && choose && Byte > 16) {//&& Byte > 16 ������ test vector���� �е��� �ȵǾ� �־ ���� ������ ������
				Del(cipher); // padding ����
				break;
			}
			printf("%x ", cipher[j]);
			
		}
		if (choose && Byte == 16)				   //1�� ��ȣȭ�� �е��� �� �Ǿ��ִ� test vector������ ����� ���ǹ�(������ ��������)
			break;

		for (int k = 0; k < 15; k++) { // CTR������ ���� -- sum������ ����
			sum += IV_ctr[k];
			sum *= 2;
		}
		sum += IV_ctr[15]+1;// ---- CTR + 1
		sum %= (2048 * 2 * 2 * 2 * 2 * 2);
		for (int k = 15; k >= 0; k--) { // CTR���� ��Ʈ�� �ٲ�
			IV_ctr[k] = sum & 0x01;
			sum = sum >> 1;
		}
	}
}
